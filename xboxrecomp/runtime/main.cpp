// Loads default.xbe into guest memory and runs the recompiled entry point.
#include <windows.h>
#include <timeapi.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "hle.h"
#include "menu/menu.h"
#include "kernel.h"

bool g_trace;

void fatal(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    std::fputs("[fatal] ", stderr);
    std::vfprintf(stderr, fmt, ap);
    std::fputc('\n', stderr);
    va_end(ap);
    std::fflush(stderr);
    if (!std::getenv("OOGIE_NO_DIALOGS")) {  // a player sees why the game stopped (automated runs set the variable)
        char text[1024];
        va_start(ap, fmt);
        std::vsnprintf(text, sizeof text, fmt, ap);
        va_end(ap);
        MessageBoxA(nullptr, text, "Oogie's Revenge stopped", MB_OK | MB_ICONERROR);
    }
    std::_Exit(1);
}

void trace(const char* fmt, ...) {
    if (!g_trace) return;
    va_list ap;
    va_start(ap, fmt);
    std::vfprintf(stderr, fmt, ap);
    std::fputc('\n', stderr);
    va_end(ap);
}

// ---- dispatch ----
static std::vector<void (*)(Ctx&)> g_lookup;
static u32 g_lookup_base;

static void build_lookup() {
    u32 lo = g_func_table[0].addr, hi = g_func_table[g_func_count - 1].addr;
    g_lookup_base = lo;
    g_lookup.assign(hi - lo + 1, nullptr);
    for (unsigned k = 0; k < g_func_count; ++k) g_lookup[g_func_table[k].addr - lo] = g_func_table[k].fn;
}

void dispatch(Ctx& c, u32 t) {
    if (t - g_lookup_base < g_lookup.size())
        if (auto fn = g_lookup[t - g_lookup_base]) return fn(c);
    if ((t & 0xFFFF0000) == KTHUNK_BASE) return kernel_call(c, t & 0xFFFF);
    if ((t & 0xFFFF0000) == HLE_THUNK_BASE) return hle_thunk_call(c, t & 0xFFFF);
    fatal("call to %08X, which is not a known function (return address %08X)", t, ld<u32>(c.esp));
}

void unimplemented(Ctx& c, u32 pc, const char* text) {
    fatal("untranslated instruction at %08X: %s (esp %08X)", pc, text, c.esp);
}

// Return addresses found on the guest stack (values in code right after a call), innermost first.
void dump_guest_stack(u32 esp) {
    std::fprintf(stderr, "[stack]");
    for (u32 k = 0, shown = 0; k < 1024 && shown < 16; ++k) {
        u32 v = ld<u32>(esp + 4 * k);
        if (v < 0x11000 || v >= 0x260000) continue;
        bool after_call = ld<u8>(v - 5) == 0xE8 || (ld<u8>(v - 6) == 0xFF && (ld<u8>(v - 5) & 0x38) == 0x10) ||
                          (ld<u8>(v - 2) == 0xFF && (ld<u8>(v - 1) & 0x38) == 0x10) ||
                          (ld<u8>(v - 3) == 0xFF && (ld<u8>(v - 2) & 0x38) == 0x10);
        if (after_call) std::fprintf(stderr, " %08X", v), ++shown;
    }
    std::fprintf(stderr, "\n");
}

void guest_fault(Ctx& c, const char* what, u32 pc) {
    dump_guest_stack(c.esp);
    fatal("guest fault at %08X: %s", pc, what);
}

void guest_int(Ctx& c, u32 vector, u32 pc) {
    if (vector == 0x2C) return;  // debug service interrupt (DbgPrint path): no debugger attached
    fatal("int %u at %08X (eax %08X)", vector, pc, c.eax);
}

void guest_cpuid(Ctx& c) {
    // the Xbox CPU: Pentium III (Coppermine), family 6 model 8
    switch (c.eax) {
    case 0: c.eax = 2; c.ebx = 0x756E6547; c.edx = 0x49656E69; c.ecx = 0x6C65746E; break;  // GenuineIntel
    case 1: c.eax = 0x683; c.ebx = 0; c.ecx = 0; c.edx = 0x0383F9FF; break;  // FPU..SSE, no SSE2
    default: c.eax = c.ebx = c.ecx = c.edx = 0; break;
    }
}

void guest_rdtsc(Ctx& c) {
    static LARGE_INTEGER freq = [] { LARGE_INTEGER f; QueryPerformanceFrequency(&f); return f; }();
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    u64 t = u64(double(now.QuadPart) * 733333333.0 / double(freq.QuadPart));  // 733 MHz
    c.eax = u32(t);
    c.edx = u32(t >> 32);
}

void guest_out(u32 port, u32 value, int size) { trace("[port] out %04X <- %0*X", port, size * 2, value); }
u32 guest_in(u32 port, int size) {
    trace("[port] in %04X (%d bytes)", port, size);
    return 0;
}

// ---- XBE ----
XbeInfo xbe_load(const char* path) {
    FILE* f = std::fopen(path, "rb");
    if (!f) fatal("cannot open %s", path);
    std::vector<u8> d;
    std::fseek(f, 0, SEEK_END);
    d.resize(std::ftell(f));
    std::fseek(f, 0, SEEK_SET);
    if (std::fread(d.data(), 1, d.size(), f) != d.size()) fatal("cannot read %s", path);
    std::fclose(f);
    auto u = [&](u32 off) { u32 v; std::memcpy(&v, &d[off], 4); return v; };
    if (d.size() < 0x180 || std::memcmp(d.data(), "XBEH", 4) != 0) fatal("%s is not an XBE", path);

    XbeInfo x;
    x.base = u(0x104);
    u32 headers = u(0x108), nsec = u(0x11C), sec_hdr = u(0x120);
    x.entry = u(0x128) ^ 0xA8FC57AB;
    x.tls_dir = u(0x12C);
    if (headers > d.size()) fatal("bad XBE header size");
    std::memcpy(g_mem + x.base, d.data(), headers);
    for (u32 k = 0; k < nsec; ++k) {
        u32 h = sec_hdr - x.base + k * 56;
        u32 va = u(h + 4), raw_off = u(h + 12), raw_size = u(h + 16);
        if (u64(raw_off) + raw_size > d.size()) fatal("section %u runs past the file", k);
        std::memcpy(g_mem + va, d.data() + raw_off, raw_size);
    }
    // the build already knows each import slot; check it against this XBE
    u32 thunk = u(0x158) ^ 0x5B6D40B6;
    if (g_kernel_thunk_count == 0 || g_kernel_thunks[0].slot != thunk)
        fatal("this default.xbe does not match the recompiled one");
    for (unsigned k = 0; k < g_kernel_thunk_count; ++k)
        st<u32>(g_kernel_thunks[k].slot, kernel_export_address(g_kernel_thunks[k].ordinal));
    return x;
}

// Laptops with two GPUs run this on the fast one (the drivers look for these exports in the program)
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 1;
extern "C" __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

int main(int argc, char** argv) {
    // the game folder holds Disc\files (the extracted disc) and UserData (settings, saves, mods): the working
    // directory when it has them (development runs), else the data folder next to this executable (a release)
    if (GetFileAttributesA("Disc\\files\\default.xbe") == INVALID_FILE_ATTRIBUTES) {
        wchar_t exe[MAX_PATH];
        DWORD n = GetModuleFileNameW(nullptr, exe, MAX_PATH);
        while (n && exe[n - 1] != L'\\') --n;
        exe[n] = 0;
        if (n) SetCurrentDirectoryW(exe);
        DWORD data = GetFileAttributesA("data");
        if (data != INVALID_FILE_ATTRIBUTES && (data & FILE_ATTRIBUTE_DIRECTORY)) SetCurrentDirectoryA("data");
    }
    if (GetStdHandle(STD_ERROR_HANDLE) == nullptr || GetFileType(GetStdHandle(STD_ERROR_HANDLE)) == FILE_TYPE_UNKNOWN) {
        CreateDirectoryA("UserData", nullptr);
        std::freopen("UserData\\log.txt", "w", stderr);  // no console (started from the launcher): keep a log
    }
    // stderr is unbuffered: every log line became many small writes, and a write held up by the disk or a virus
    // scanner stalled the game (40-60 ms stutters). Buffered, it goes out in one write when the frame statistics
    // flush it every 2 s, or at once on a fatal error (fatal() flushes).
    static char log_buffer[1 << 16];
    std::setvbuf(stderr, log_buffer, _IOFBF, sizeof log_buffer);
    // a crash outside the guest's own fault handling still leaves its cause (and the buffered log) in the log
    SetUnhandledExceptionFilter([](EXCEPTION_POINTERS* e) -> LONG {
        const EXCEPTION_RECORD* r = e->ExceptionRecord;
        HMODULE m = nullptr;
        char name[MAX_PATH] = "?";
        if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                               static_cast<LPCSTR>(r->ExceptionAddress), &m))
            GetModuleFileNameA(m, name, sizeof name);
        std::fprintf(stderr, "[crash] exception %08lX at %p (%s+%llX) on thread %lu (boot thread %lu)", r->ExceptionCode,
                     r->ExceptionAddress, name, (unsigned long long)(static_cast<const char*>(r->ExceptionAddress) - reinterpret_cast<const char*>(m)),
                     GetCurrentThreadId(), g_boot_thread);
        if (r->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && r->NumberParameters >= 2)
            std::fprintf(stderr, ", %s %p", r->ExceptionInformation[0] ? "writing" : "reading", reinterpret_cast<void*>(r->ExceptionInformation[1]));
        std::fprintf(stderr, ", guest thread %08X\n[crash] stack:", guest_thread_self());
        void* frames[40];  // module+offset per frame (build\OogiesRevenge.map names our own)
        for (USHORT i = 0, n = RtlCaptureStackBackTrace(0, 40, frames, nullptr); i < n; ++i) {
            HMODULE fm = nullptr;
            char fn[MAX_PATH] = "?";
            if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                   static_cast<LPCSTR>(frames[i]), &fm))
                GetModuleFileNameA(fm, fn, sizeof fn);
            const char* base = std::strrchr(fn, '\\');
            std::fprintf(stderr, " %s+%llX", base ? base + 1 : fn,
                         (unsigned long long)(static_cast<const char*>(frames[i]) - reinterpret_cast<const char*>(fm)));
        }
        std::fprintf(stderr, "\n");
        std::fflush(stderr);
        return EXCEPTION_CONTINUE_SEARCH;
    });
    for (const char* dir : {"UserData", "UserData\\hdd", "UserData\\mods", "UserData\\mods\\files"}) CreateDirectoryA(dir, nullptr);
    for (int p = 1; p <= 7; ++p) CreateDirectoryA(("UserData\\hdd\\Partition" + std::to_string(p)).c_str(), nullptr);
    bool play = argc > 1 && std::strcmp(argv[1], "--play") == 0;  // straight into the game (the menu restarted it)
    bool setup = argc > 1 && std::strcmp(argv[1], "--setup") == 0;  // choose a disc again
    const char* xbe = argc > 1 && !play && !setup ? argv[1] : "Disc/files/default.xbe";
    // the game's own menu first, asking for the disc on the first start (automated runs, which script the pad from
    // the start, go straight in)
    if (!play && !std::getenv("OOGIE_PRESS") && !std::getenv("OOGIE_NO_MENU")) menu_run(setup);
    if (GetFileAttributesA(xbe) == INVALID_FILE_ATTRIBUTES)
        fatal("The game files were not found (%s).\nStart Oogie's Revenge.exe and choose your disc.", xbe);
    g_trace = std::getenv("OOGIE_TRACE") != nullptr;
    timeBeginPeriod(1);  // Windows sleeps in 15.6 ms steps otherwise: guest waits, vblank and audio ticks run late
    mem_init();
    build_lookup();
    kernel_init();
    hle_init();
    XbeInfo x = xbe_load(xbe);
    std::fprintf(stderr, "[boot] %s loaded, entry %08X, %u functions\n", xbe, x.entry, g_func_count);

    // the boot thread gets the XBE's TLS block with its template copied in
    u32 tls_size = 0, raw = 0, raw_start = 0;
    if (x.tls_dir) {
        raw_start = ld<u32>(x.tls_dir);
        raw = ld<u32>(x.tls_dir + 4) - raw_start;
        tls_size = (raw + ld<u32>(x.tls_dir + 16) + 15) & ~15u;
        if (u32 index = ld<u32>(x.tls_dir + 8)) st<u32>(index, 0);
    }
    Ctx c;
    u32 thread = thread_setup(c, 0x40000, tls_size);
    if (raw) std::memmove(g_mem + ld<u32>(thread + KTHREAD_TLS_DATA), g_mem + raw_start, raw);
    g_boot_thread = GetCurrentThreadId();
    set_guest_thread(thread);
    guest_lock();
    push32(c, 0);  // entry returns here: no caller
    dispatch(c, x.entry);
    std::fprintf(stderr, "[boot] entry point returned (eax %08X)\n", c.eax);
    thread_exit(c, c.eax);
}
