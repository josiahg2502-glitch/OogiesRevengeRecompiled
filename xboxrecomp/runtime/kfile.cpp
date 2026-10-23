// File system: Xbox paths mapped onto folders next to the executable.
#include <windows.h>

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

#include "kernel.h"

constexpr u32 X_STATUS_OBJECT_NAME_NOT_FOUND = 0xC0000034, X_STATUS_OBJECT_PATH_NOT_FOUND = 0xC000003A,
              X_STATUS_OBJECT_NAME_COLLISION = 0xC0000035, X_STATUS_END_OF_FILE = 0xC0000011,
              X_STATUS_ACCESS_DENIED = 0xC0000022, X_STATUS_INVALID_HANDLE = 0xC0000008,
              X_STATUS_NOT_IMPLEMENTED = 0xC0000002, X_STATUS_INVALID_PARAMETER = 0xC000000D;

struct GuestFile {
    HANDLE h;
    std::string path;  // host path
    bool dir;
    bool async = false;  // opened without FILE_SYNCHRONOUS_IO_*: reads and writes complete later, as on the Xbox
};
static std::unordered_map<u32, GuestFile> g_files;  // guest file object -> host file
u64 g_io_bytes, g_io_ns;
static const char RAW_DISK[] = "<raw disk>";

static std::string ansi(u32 str) {  // ANSI_STRING { u16 Length, MaximumLength; char* Buffer }
    return std::string(reinterpret_cast<char*>(g_mem + ld<u32>(str + 4)), ld<u16>(str));
}

static bool starts(const std::string& s, const char* prefix, std::string& rest) {
    size_t n = std::strlen(prefix);
    if (s.size() < n || _strnicmp(s.c_str(), prefix, n) != 0) return false;
    rest = s.substr(n);
    return true;
}

// Drive letters are symlinks XAPI creates (\??\U: -> \Device\Harddisk0\Partition1\UDATA\<title>).
static std::unordered_map<std::string, std::string> g_links = {{"\\??\\d:", "\\Device\\CdRom0"}};

static std::string lower(std::string s) {
    for (char& ch : s) ch = char(std::tolower(u8(ch)));
    return s;
}

// The enabled mods' files folders, the one that wins first: UserData\mods\<mod>\files, a mod switched off by a
// file named "disabled" in its folder (the launcher's Mods page), later names winning like the other ports
static const std::vector<std::string>& mod_dirs() {
    static const std::vector<std::string> dirs = [] {
        std::vector<std::string> names;
        WIN32_FIND_DATAA f;
        HANDLE h = FindFirstFileA("UserData\\mods\\*", &f);
        if (h != INVALID_HANDLE_VALUE) {
            do {
                std::string n = f.cFileName;
                if ((f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && n != "." && n != ".." && n != "files" &&
                    GetFileAttributesA(("UserData\\mods\\" + n + "\\disabled").c_str()) == INVALID_FILE_ATTRIBUTES)
                    names.push_back(n);
            } while (FindNextFileA(h, &f));
            FindClose(h);
        }
        std::sort(names.begin(), names.end(), [](const std::string& a, const std::string& b) { return _stricmp(a.c_str(), b.c_str()) > 0; });
        std::vector<std::string> out;
        for (auto& n : names) out.push_back("UserData\\mods\\" + n + "\\files");
        out.push_back("UserData\\mods\\files");  // loose files straight in mods\files count as the lowest mod
        for (auto& n : names) std::fprintf(stderr, "[file] mod %s\n", n.c_str());
        return out;
    }();
    return dirs;
}

// Xbox object name -> host path, or "" if it is not somewhere we serve
static std::string host_path(std::string name) {
    for (char& ch : name)
        if (ch == '/') ch = '\\';
    if (name.size() >= 6 && name.compare(0, 4, "\\??\\") == 0 && name[5] == ':') {
        auto it = g_links.find(lower(name.substr(0, 6)));
        if (it != g_links.end()) name = it->second + name.substr(6);
    }
    static const struct { const char* xbox; const char* host; } roots[] = {
        {"\\Device\\CdRom0", "Disc\\files"},
        {"\\Device\\Harddisk0\\Partition1", "UserData\\hdd\\Partition1"},  // saves
        {"\\Device\\Harddisk0\\Partition2", "UserData\\hdd\\Partition2"},
        {"\\Device\\Harddisk0\\Partition3", "UserData\\hdd\\Partition3"},  // 3-7: cache partitions
        {"\\Device\\Harddisk0\\Partition4", "UserData\\hdd\\Partition4"},
        {"\\Device\\Harddisk0\\Partition5", "UserData\\hdd\\Partition5"},
        {"\\Device\\Harddisk0\\Partition6", "UserData\\hdd\\Partition6"},
        {"\\Device\\Harddisk0\\Partition7", "UserData\\hdd\\Partition7"},
    };
    std::string rest;
    for (auto& r : roots)
        if (starts(name, r.xbox, rest) && (rest.empty() || rest[0] == '\\')) {
            // the game cannot leave its folders
            if (rest.find("\\..") != std::string::npos) return "";
            if (r.host[0] == 'D')  // a mod's files\<path> replaces that disc file (upscaled movies etc.)
                for (const std::string& dir : mod_dirs()) {
                    std::string mod = dir + rest;
                    DWORD attrs = GetFileAttributesA(mod.c_str());
                    if (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY)) return mod;
                }
            return r.host + rest;
        }
    return "";
}

static std::string object_name(u32 attrs) {  // OBJECT_ATTRIBUTES { RootDirectory, ObjectName*, Attributes }
    std::string name = ansi(ld<u32>(attrs + 4));
    if (u32 root = ld<u32>(attrs)) {
        if (root == 0xFFFFFFFD) return "\\??\\" + name;  // ObDosDevicesDirectory()
        auto it = g_files.find(root);
        if (it == g_files.end()) fatal("relative open against unknown directory handle %08X", root);
        return "\x01" + it->second.path + "\\" + name;  // \x01: already a host path
    }
    return name;
}

static void set_iosb(u32 iosb, u32 status, u32 info) {
    if (!iosb) return;
    st<u32>(iosb, status);
    st<u32>(iosb + 4, info);
}

static u32 create(u32 handle_out, u32 attrs, u32 iosb, u32 disposition, u32 options, bool write) {
    std::string name = object_name(attrs);
    if (_stricmp(name.c_str(), "\\Device\\Harddisk0\\Partition0") == 0) {
        // the raw disk: XAPI reads the partition layout from it; reads see a blank disk
        u32 obj = kalloc(0x20);
        g_files[obj] = {INVALID_HANDLE_VALUE, RAW_DISK, false};
        st<u32>(handle_out, obj);
        std::fprintf(stderr, "[file] raw disk opened -> %08X\n", obj);
        set_iosb(iosb, 0, 1);
        return 0;
    }
    std::string path = name[0] == '\x01' ? name.substr(1) : host_path(name);
    if (path.empty()) {
        std::fprintf(stderr, "[file] no mapping for %s\n", name.c_str());
        set_iosb(iosb, X_STATUS_OBJECT_PATH_NOT_FOUND, 0);
        return X_STATUS_OBJECT_PATH_NOT_FOUND;
    }
    DWORD attr = GetFileAttributesA(path.c_str());
    bool exists = attr != INVALID_FILE_ATTRIBUTES, is_dir = exists && (attr & FILE_ATTRIBUTE_DIRECTORY);
    bool want_dir = options & 1;  // FILE_DIRECTORY_FILE
    u32 info = 1;                 // FILE_OPENED
    if (want_dir && !exists && (disposition == 2 || disposition == 3)) {
        CreateDirectoryA(path.c_str(), nullptr);
        is_dir = true, exists = true, info = 2;  // FILE_CREATED
    }
    if (!exists && (disposition == 1 || disposition == 4)) {  // FILE_OPEN, FILE_OVERWRITE
        // like NT: a missing folder on the way is PATH_NOT_FOUND, only a missing last component NAME_NOT_FOUND
        size_t slash = path.find_last_of('\\');
        DWORD parent = slash == std::string::npos ? FILE_ATTRIBUTE_DIRECTORY : GetFileAttributesA(path.substr(0, slash).c_str());
        u32 status = parent != INVALID_FILE_ATTRIBUTES && (parent & FILE_ATTRIBUTE_DIRECTORY)
                         ? X_STATUS_OBJECT_NAME_NOT_FOUND : X_STATUS_OBJECT_PATH_NOT_FOUND;
        trace("[file] not found: %s", path.c_str());
        set_iosb(iosb, status, 5);
        return status;
    }
    if (exists && disposition == 2) {
        set_iosb(iosb, X_STATUS_OBJECT_NAME_COLLISION, 4);
        return X_STATUS_OBJECT_NAME_COLLISION;
    }
    HANDLE h = INVALID_HANDLE_VALUE;
    if (!is_dir) {
        static const DWORD host_disp[] = {CREATE_ALWAYS, OPEN_EXISTING, CREATE_NEW, OPEN_ALWAYS, TRUNCATE_EXISTING,
                                          CREATE_ALWAYS};
        bool read_only = path.rfind("Disc\\", 0) == 0 || path.rfind("UserData\\mods\\", 0) == 0;
        // the disc is read-only: opening existing files is fine (FILE_OPEN, or FILE_OPEN_IF on a file that exists)
        if (read_only && (write || !(disposition == 1 || (disposition == 3 && exists)))) {
            set_iosb(iosb, X_STATUS_ACCESS_DENIED, 0);
            return X_STATUS_ACCESS_DENIED;
        }
        h = CreateFileA(path.c_str(), GENERIC_READ | (read_only ? 0 : GENERIC_WRITE),
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                        disposition < 6 ? host_disp[disposition] : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (h == INVALID_HANDLE_VALUE) {
            DWORD err = GetLastError();
            trace("[file] cannot open %s (error %lu)", path.c_str(), err);
            u32 status = err == ERROR_PATH_NOT_FOUND ? X_STATUS_OBJECT_PATH_NOT_FOUND
                         : err == ERROR_ACCESS_DENIED ? X_STATUS_ACCESS_DENIED
                                                      : X_STATUS_OBJECT_NAME_NOT_FOUND;
            set_iosb(iosb, status, 5);
            return status;
        }
        if (!exists) info = 2;
        else if (disposition == 0 || disposition >= 4) info = 3;  // FILE_OVERWRITTEN
    }
    u32 obj = kalloc(0x20);  // stands in for the FILE_OBJECT
    g_files[obj] = {h, path, is_dir, !(options & 0x30)};
    st<u32>(handle_out, obj);
    trace("[file] %s -> %08X%s", path.c_str(), obj, is_dir ? " (dir)" : "");
    set_iosb(iosb, 0, info);
    return 0;
}

// Completions of asynchronous transfers: a host thread posts them a millisecond after the call, under the
// guest lock (IO_STATUS_BLOCK, event, APC), so callers see STATUS_PENDING first as on the hardware.
constexpr u32 X_STATUS_PENDING = 0x103;
struct Completion {
    u32 thread, iosb, status, info, event, apc, apc_context;
};
static void complete_later(const Completion& done) {
    static std::mutex m;
    static std::condition_variable cv;
    static std::deque<Completion> queue;
    static bool started = false;
    std::lock_guard<std::mutex> lock(m);
    queue.push_back(done);
    cv.notify_one();
    if (started) return;
    started = true;
    std::thread([] {
        for (;;) {
            Completion x;
            {
                std::unique_lock<std::mutex> l(m);
                cv.wait(l, [] { return !queue.empty(); });
                x = queue.front();
                queue.pop_front();
            }
            Sleep(1);
            guest_lock();
            set_iosb(x.iosb, x.status, x.info);
            if (x.apc) queue_apc_for(x.thread, x.apc, x.apc_context, x.iosb, 0);  // ApcRoutine(ApcContext, IoStatusBlock, 0)
            if (x.event) st<s32>(x.event + 4, 1);
            signal_any();
            guest_unlock();
        }
    }).detach();
}

static GuestFile* file(u32 handle) {
    auto it = g_files.find(handle);
    return it == g_files.end() ? nullptr : &it->second;
}

K(NtOpenFile) { return create(arg(c, 0), arg(c, 2), arg(c, 3), 1, arg(c, 5), arg(c, 1) & 0x40000006); }
K(NtCreateFile) { return create(arg(c, 0), arg(c, 2), arg(c, 3), arg(c, 7), arg(c, 8), arg(c, 1) & 0x40000006); }

static u32 rw(Ctx& c, bool write) {
    u32 handle = arg(c, 0), event = arg(c, 1), apc = arg(c, 2), iosb = arg(c, 4), buf = arg(c, 5),
        len = arg(c, 6), offset = arg(c, 7);
    GuestFile* f = file(handle);
    if (!f) return X_STATUS_INVALID_HANDLE;
    if (f->path == RAW_DISK || f->dir) {  // raw disk, or sectors of a volume opened as a whole
        std::fprintf(stderr, "[file] raw disk %s %u bytes at %llX\n", write ? "write" : "read", len,
                     offset ? (unsigned long long)ld<s64>(offset) : 0ull);
        if (!write) std::memset(g_mem + buf, 0, len);
        set_iosb(iosb, 0, len);
        return 0;
    }
    LARGE_INTEGER pos = {}, zero = {};
    if (offset && ld<s64>(offset) != -2) pos.QuadPart = ld<s64>(offset);  // -2: FILE_USE_FILE_POINTER_POSITION
    else SetFilePointerEx(f->h, zero, &pos, FILE_CURRENT);
    LARGE_INTEGER end;  // the file pointer moves past the transfer now, so a later call on the same handle starts there
    end.QuadPart = pos.QuadPart + len;
    SetFilePointerEx(f->h, end, nullptr, FILE_BEGIN);
    DWORD done = 0;
    guest_commit(buf, len);
    // the transfer runs without the guest lock: a thread waiting on a slow disk (the game streams sound and stage data
    // from its own threads) must not stop every other guest thread, the game's main loop included
    HANDLE h = f->h;
    bool async = f->async;  // f itself may be gone once the lock is released (another thread opens or closes files)
    OVERLAPPED at = {};
    at.Offset = pos.LowPart, at.OffsetHigh = DWORD(pos.HighPart);
    guest_unlock();
    auto t0 = std::chrono::steady_clock::now();
    // OOGIE_IO_DELAY_MS=ms[,after_s]: every read as slow as a cold hard disk, from after_s seconds on (testing)
    static unsigned delay_ms, delay_after_s;
    static const bool delay_set = std::getenv("OOGIE_IO_DELAY_MS") &&
                                  std::sscanf(std::getenv("OOGIE_IO_DELAY_MS"), "%u,%u", &delay_ms, &delay_after_s) >= 1;
    static const ULONGLONG start_ms = GetTickCount64();
    if (delay_set && !write && GetTickCount64() - start_ms >= delay_after_s * 1000ull) Sleep(delay_ms);
    BOOL ok = write ? WriteFile(h, g_mem + buf, len, &done, &at) : ReadFile(h, g_mem + buf, len, &done, &at);
    if (!ok && GetLastError() == ERROR_HANDLE_EOF) ok = TRUE;  // a positioned read past the end: 0 bytes, as before
    auto spent = u64((std::chrono::steady_clock::now() - t0).count());
    guest_lock();
    g_io_ns += spent, g_io_bytes += done;
    if (static const bool log = std::getenv("OOGIE_IO_LOG") != nullptr; log)  // every transfer: thread, size, time (testing)
        std::fprintf(stderr, "[io] thread %08X %s %lu bytes at %lld in %.1f ms\n", current_guest_thread(c), write ? "write" : "read",
                     done, (long long)pos.QuadPart, spent / 1e6);
    if (!ok) trace("[file] %s failed on handle %08X: Windows error %lu", write ? "write" : "read", handle, GetLastError());
    u32 status = !ok ? X_STATUS_ACCESS_DENIED : (!write && len && !done) ? X_STATUS_END_OF_FILE : 0;
    if (async) {  // the transfer is done, but like the Xbox's DMA it reports completion only later
        u32 event_obj = event ? object_from_handle(c, event) : 0;
        set_iosb(iosb, X_STATUS_PENDING, 0);
        complete_later({current_guest_thread(c), iosb, status, done, event_obj, apc, arg(c, 3)});
        return X_STATUS_PENDING;
    }
    set_iosb(iosb, status, done);
    if (apc) queue_apc(c, apc, arg(c, 3), iosb, 0);  // ApcRoutine(ApcContext, IoStatusBlock, 0)
    if (event) {
        if (event & 1) {  // Win32 marks "no completion port notification" in the handle's low bit
            static bool told;
            if (!told) told = true, std::fprintf(stderr, "[file] event handle %08X with bit 0 set\n", event);
        }
        st<s32>(object_from_handle(c, event) + 4, 1);
        signal_any();
    }
    return status;
}
K(NtReadFile) { return rw(c, false); }
K(NtWriteFile) { return rw(c, true); }

static void file_times(GuestFile* f, const std::string& path, u32 out, u64& size, u32& attrs) {
    WIN32_FILE_ATTRIBUTE_DATA a{};
    GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &a);
    auto ft = [](FILETIME t) { return (u64(t.dwHighDateTime) << 32) | t.dwLowDateTime; };
    if (out) {  // the four FILETIMEs (32 bytes); callers whose struct has no room pass 0
        st<u64>(out, ft(a.ftCreationTime));
        st<u64>(out + 8, ft(a.ftLastAccessTime));
        st<u64>(out + 16, ft(a.ftLastWriteTime));
        st<u64>(out + 24, ft(a.ftLastWriteTime));
    }
    size = (u64(a.nFileSizeHigh) << 32) | a.nFileSizeLow;
    attrs = (a.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 0x10 : 0x80;  // DIRECTORY / NORMAL
    (void)f;
}

K(NtQueryInformationFile) {
    u32 handle = arg(c, 0), iosb = arg(c, 1), out = arg(c, 2), len = arg(c, 3), cls = arg(c, 4);
    GuestFile* f = file(handle);
    if (!f) return X_STATUS_INVALID_HANDLE;
    std::memset(g_mem + out, 0, len);
    u64 size;
    u32 attrs;
    switch (cls) {
    case 4:  // FileBasicInformation
        file_times(f, f->path, out, size, attrs);
        st<u32>(out + 32, attrs);
        set_iosb(iosb, 0, 40);
        return 0;
    case 5:  // FileStandardInformation: 24 bytes, so the times must not be written through `out`
        file_times(f, f->path, 0, size, attrs);
        std::memset(g_mem + out, 0, 24);
        st<u64>(out, (size + 4095) & ~4095ull), st<u64>(out + 8, size), st<u32>(out + 16, 1);
        st<u8>(out + 21, f->dir);
        set_iosb(iosb, 0, 24);
        return 0;
    case 14: {  // FilePositionInformation
        LARGE_INTEGER zero{}, pos;
        SetFilePointerEx(f->h, zero, &pos, FILE_CURRENT);
        st<s64>(out, pos.QuadPart);
        set_iosb(iosb, 0, 8);
        return 0;
    }
    case 34:  // FileNetworkOpenInformation
        file_times(f, f->path, out, size, attrs);
        st<u64>(out + 32, (size + 4095) & ~4095ull), st<u64>(out + 40, size), st<u32>(out + 48, attrs);
        set_iosb(iosb, 0, 56);
        return 0;
    }
    fatal("NtQueryInformationFile class %u not implemented", cls);
}

K(NtSetInformationFile) {
    u32 handle = arg(c, 0), iosb = arg(c, 1), in = arg(c, 2), cls = arg(c, 4);
    GuestFile* f = file(handle);
    if (!f) return X_STATUS_INVALID_HANDLE;
    LARGE_INTEGER v;
    switch (cls) {
    case 14:  // FilePositionInformation
        v.QuadPart = ld<s64>(in);
        SetFilePointerEx(f->h, v, nullptr, FILE_BEGIN);
        break;
    case 19:  // FileAllocationInformation
    case 20:  // FileEndOfFileInformation
    {
        LARGE_INTEGER here{}, zero{};
        SetFilePointerEx(f->h, zero, &here, FILE_CURRENT);
        v.QuadPart = ld<s64>(in);
        SetFilePointerEx(f->h, v, nullptr, FILE_BEGIN);
        SetEndOfFile(f->h);
        SetFilePointerEx(f->h, here, nullptr, FILE_BEGIN);
        break;
    }
    case 4:   // FileBasicInformation: timestamps and attributes; nothing to keep
    case 13:  // FileDispositionInformation (delete on close)
        if (cls == 13 && ld<u8>(in)) {
            CloseHandle(f->h);
            f->h = INVALID_HANDLE_VALUE;
            DeleteFileA(f->path.c_str());
        }
        break;
    default: fatal("NtSetInformationFile class %u not implemented", cls);
    }
    set_iosb(iosb, 0, 0);
    return 0;
}

K(NtQueryFullAttributesFile) {
    std::string name = object_name(arg(c, 0));
    std::string path = name[0] == '\x01' ? name.substr(1) : host_path(name);
    if (path.empty() || GetFileAttributesA(path.c_str()) == INVALID_FILE_ATTRIBUTES) {
        trace("[file] attributes: not found: %s", name.c_str());
        return X_STATUS_OBJECT_NAME_NOT_FOUND;
    }
    u64 size;
    u32 attrs, out = arg(c, 1);
    file_times(nullptr, path, out, size, attrs);
    st<u64>(out + 32, (size + 4095) & ~4095ull), st<u64>(out + 40, size), st<u32>(out + 48, attrs);
    return 0;
}

K(NtQueryVolumeInformationFile) {
    u32 iosb = arg(c, 1), out = arg(c, 2), len = arg(c, 3), cls = arg(c, 4);
    std::memset(g_mem + out, 0, len);
    if (cls == 3) {  // FileFsSizeInformation: report a roomy 4 GB volume with 16 KB clusters
        st<u64>(out, 0x40000), st<u64>(out + 8, 0x30000), st<u32>(out + 16, 32), st<u32>(out + 20, 512);
        set_iosb(iosb, 0, 24);
        return 0;
    }
    fatal("NtQueryVolumeInformationFile class %u not implemented", cls);
}

K(NtDeviceIoControlFile) {
    u32 iosb = arg(c, 4), code = arg(c, 5), out = arg(c, 8), out_len = arg(c, 9);
    if (arg(c, 2)) fatal("NtDeviceIoControlFile with an APC routine is not implemented");
    switch (code) {
    case 0x00074004:  // IOCTL_DISK_GET_PARTITION_INFO: a 750 MB cache partition
        std::memset(g_mem + out, 0, out_len);
        st<u64>(out, 0x00080000), st<u64>(out + 8, 0x2EE00000), st<u32>(out + 20, 5);
        st<u8>(out + 24, 0x0E), st<u8>(out + 26, 1);  // type FAT, recognized
        set_iosb(iosb, 0, 32);
        return 0;
    case 0x00070000:  // IOCTL_DISK_GET_DRIVE_GEOMETRY
        std::memset(g_mem + out, 0, out_len);
        st<u64>(out, 0x2EE00000 / (255 * 63 * 512)), st<u32>(out + 8, 12);  // FixedMedia
        st<u32>(out + 12, 255), st<u32>(out + 16, 63), st<u32>(out + 20, 512);
        set_iosb(iosb, 0, 24);
        return 0;
    }
    fatal("NtDeviceIoControlFile code %08X not implemented (handle %08X)", code, arg(c, 0));
}

K(NtFsControlFile) {  // dismount/lock/format requests: a host folder needs none of them
    trace("[file] fs control %08X on %08X", arg(c, 5), arg(c, 0));
    if (arg(c, 2)) fatal("NtFsControlFile with an APC routine is not implemented");
    set_iosb(arg(c, 4), 0, 0);
    return 0;
}

K(NtFlushBuffersFile) {
    if (GuestFile* f = file(arg(c, 0)))
        if (!f->dir) FlushFileBuffers(f->h);
    set_iosb(arg(c, 1), 0, 0);
    return 0;
}

// NtClose for files; other objects need nothing (kernel pool is never freed)
bool close_file(u32 handle) {
    auto it = g_files.find(handle);
    if (it == g_files.end()) return false;
    if (it->second.h != INVALID_HANDLE_VALUE) CloseHandle(it->second.h);
    g_files.erase(it);
    return true;
}

// Symbolic link objects (the link table itself is with host_path)
static std::unordered_map<u32, std::string> g_link_objects;

K(IoCreateSymbolicLink) {
    std::string link = ansi(arg(c, 0)), target = ansi(arg(c, 1));
    std::fprintf(stderr, "[file] symlink %s -> %s\n", link.c_str(), target.c_str());
    g_links[lower(link)] = target;
    return 0;
}
K(IoDeleteSymbolicLink) {
    g_links.erase(lower(ansi(arg(c, 0))));
    return 0;
}
K(NtOpenSymbolicLinkObject) {
    std::string name = object_name(arg(c, 1));
    auto it = g_links.find(lower(name));
    if (it == g_links.end()) {
        std::fprintf(stderr, "[file] no symlink %s\n", name.c_str());
        return X_STATUS_OBJECT_NAME_NOT_FOUND;
    }
    u32 obj = kalloc(0x10);
    g_link_objects[obj] = it->second;
    st<u32>(arg(c, 0), obj);
    return 0;
}
K(NtQuerySymbolicLinkObject) {
    auto it = g_link_objects.find(arg(c, 0));
    if (it == g_link_objects.end()) return X_STATUS_INVALID_HANDLE;
    const std::string& t = it->second;
    u32 str = arg(c, 1), max = ld<u16>(str + 2);
    if (arg(c, 2)) st<u32>(arg(c, 2), u32(t.size()));
    if (t.size() > max) return 0xC0000023;  // STATUS_BUFFER_TOO_SMALL
    std::memcpy(g_mem + ld<u32>(str + 4), t.data(), t.size());
    st<u16>(str, u16(t.size()));
    return 0;
}

REGISTER(NtOpenFile) REGISTER(NtCreateFile) REGISTER(NtReadFile) REGISTER(NtWriteFile)
REGISTER(NtQueryInformationFile) REGISTER(NtSetInformationFile) REGISTER(NtQueryFullAttributesFile)
REGISTER(NtQueryVolumeInformationFile) REGISTER(NtFlushBuffersFile) REGISTER(NtDeviceIoControlFile) REGISTER(NtFsControlFile) REGISTER(IoCreateSymbolicLink)
REGISTER(IoDeleteSymbolicLink) REGISTER(NtOpenSymbolicLinkObject) REGISTER(NtQuerySymbolicLinkObject)
