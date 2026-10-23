// xboxkrnl.exe, reimplemented: the subset Oogie's Revenge imports.
#include <windows.h>

#include <atomic>
#include <chrono>
#include <map>
#include <cstdio>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "kernel.h"

constexpr u32 X_STATUS_SUCCESS = 0, X_STATUS_NO_MEMORY = 0xC0000017, X_STATUS_INVALID_PARAMETER = 0xC000000D;

static const KernelExport* g_export[512];
static u32 g_data[512];  // guest address of each data export


// ---- recent kernel calls, printed when we stop ----
static struct { u32 ordinal, ret, a0, a1; } g_ring[32];
static std::atomic<unsigned> g_ring_pos;

static void print_recent() {
    unsigned end = g_ring_pos.load();
    std::fprintf(stderr, "recent kernel calls (oldest first):\n");
    for (unsigned k = end > 32 ? end - 32 : 0; k < end; ++k) {
        auto& r = g_ring[k % 32];
        std::fprintf(stderr, "  %-34s from %08X  (%08X, %08X)\n", g_export[r.ordinal]->name, r.ret, r.a0, r.a1);
    }
}

// ---- implementations: each returns eax; argument popping is done by kernel_call ----

static std::string ansi(u32 str) {  // ANSI_STRING { u16 Length, MaximumLength; char* Buffer }
    return std::string(reinterpret_cast<char*>(g_mem + ld<u32>(str + 4)), ld<u16>(str));
}

K(DbgPrint) {
    std::string s = reinterpret_cast<char*>(g_mem + arg(c, 0));
    std::fprintf(stderr, "[DbgPrint] %s", s.c_str());
    return X_STATUS_SUCCESS;
}

// pool: a size word before each block so ExQueryPoolBlockSize works
K(ExAllocatePoolWithTag) {
    u32 size = arg(c, 0);
    u32 p = kalloc(size + 16, 16) + 16;
    st<u32>(p - 4, size);
    return p;
}
K(ExFreePool) { return 0; }  // shortcut: pool is never reused; fine until the game churns allocations
K(ExQueryPoolBlockSize) { return ld<u32>(arg(c, 0) - 4); }

K(ExQueryNonVolatileSetting) {
    u32 index = arg(c, 0), type = arg(c, 1), value = arg(c, 2), len = arg(c, 3), result_len = arg(c, 4);
    u32 v = 0;
    switch (index) {
    case 0x007: v = 1; break;           // language: English
    case 0x103: v = 0x00400100; break;  // AV region: NTSC-M, 60 Hz
    case 0x104: v = 1; break;           // game region: North America
    }
    if (type) st<u32>(type, 4);  // REG_DWORD
    if (value && len >= 4) st<u32>(value, v);
    if (result_len) st<u32>(result_len, 4);
    return X_STATUS_SUCCESS;
}

K(AvGetSavedDataAddress) { return 0; }
K(AvSetSavedDataAddress) { return 0; }
K(HalIsResetOrShutdownPending) { return 0; }
K(HalReturnToFirmware) { fatal("game asked to return to the dashboard (HalReturnToFirmware %u)", arg(c, 0)); }
K(KeBugCheck) { fatal("KeBugCheck %08X", arg(c, 0)); }

K(KeRaiseIrqlToDpcLevel) {
    u8 old = ld<u8>(c.fs_base + KPCR_IRQL);
    st<u8>(c.fs_base + KPCR_IRQL, 2);
    return old;
}
K(KfRaiseIrql) {
    u8 old = ld<u8>(c.fs_base + KPCR_IRQL);
    st<u8>(c.fs_base + KPCR_IRQL, u8(c.ecx));
    return old;
}
K(KfLowerIrql) {
    st<u8>(c.fs_base + KPCR_IRQL, u8(c.ecx));
    return 0;
}

K(KeQuerySystemTime) {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    st<u32>(arg(c, 0), ft.dwLowDateTime);
    st<u32>(arg(c, 0) + 4, ft.dwHighDateTime);
    return 0;
}
K(KeStallExecutionProcessor) { return 0; }
K(KeSaveFloatingPointState) { return X_STATUS_SUCCESS; }
K(KeRestoreFloatingPointState) { return X_STATUS_SUCCESS; }
K(NtYieldExecution) { SwitchToThread(); return X_STATUS_SUCCESS; }
K(KeDelayExecutionThread) {
    s64 interval = ld<s64>(arg(c, 2));  // 100 ns units; negative = relative
    Sleep(interval < 0 ? DWORD(-interval / 10000) : 0);
    return X_STATUS_SUCCESS;
}

K(MmAllocateContiguousMemory) { return contiguous_alloc(arg(c, 0), 0x1000); }
K(MmAllocateContiguousMemoryEx) {
    u32 size = arg(c, 0), align = arg(c, 3);
    return contiguous_alloc(size, align ? align : 0x1000);
}
K(MmFreeContiguousMemory) { return 0; }  // see contiguous_alloc
K(MmPersistContiguousMemory) { return 0; }
K(MmQueryAllocationSize) { return contiguous_size(arg(c, 0)); }
K(MmGetPhysicalAddress) {
    u32 va = arg(c, 0);
    return va >= CONTIGUOUS_BASE && va < CONTIGUOUS_BASE + RAM_SIZE ? va - CONTIGUOUS_BASE : va;
}
K(MmClaimGpuInstanceMemory) {
    // the GPU's instance memory sits at the top of RAM
    if (arg(c, 1)) st<u32>(arg(c, 1), 0x10000);
    return CONTIGUOUS_BASE + RAM_SIZE - 0x10000;
}
K(MmQueryAddressProtect) { return PAGE_READWRITE; }
K(MmSetAddressProtect) { return 0; }
K(MmLockUnlockBufferPages) { return 0; }
K(MmLockUnlockPhysicalPage) { return 0; }

K(NtAllocateVirtualMemory) {
    u32 base_ptr = arg(c, 0), size_ptr = arg(c, 2);
    u32 base = ld<u32>(base_ptr), size = ld<u32>(size_ptr);
    if (size >= 0x40000000) {  // more than the Xbox has: report who asked
        std::fprintf(stderr, "[kernel] NtAllocateVirtualMemory size %08X type %X from %08X (stack %08X %08X %08X %08X)\n",
                     size, arg(c, 3), ld<u32>(c.esp), ld<u32>(c.esp + 0x20), ld<u32>(c.esp + 0x24), ld<u32>(c.esp + 0x28),
                     ld<u32>(c.esp + 0x2C));
        dump_guest_stack(c.esp);
    }
    static const bool trace_vm = std::getenv("OOGIE_TRACE_VM") != nullptr;
    u32 asked = base;
    if (!base) {  // a fresh region; committing inside a reserved one needs nothing (pages fault in)
        base = virtual_alloc(size);
        st<u32>(base_ptr, base);
    }
    st<u32>(size_ptr, (size + 0xFFF) & ~0xFFFu);
    if (trace_vm)
        std::fprintf(stderr, "[vm] alloc asked %08X size %08X type %X protect %X -> %08X from %08X\n", asked, size, arg(c, 3),
                     arg(c, 4), base, ld<u32>(c.esp));
    return X_STATUS_SUCCESS;
}
K(NtFreeVirtualMemory) {  // shortcut: address space is never reused
    static const bool trace_vm = std::getenv("OOGIE_TRACE_VM") != nullptr;
    if (trace_vm)
        std::fprintf(stderr, "[vm] free %08X size %08X type %X from %08X\n", ld<u32>(arg(c, 0)), ld<u32>(arg(c, 1)), arg(c, 2),
                     ld<u32>(c.esp));
    return X_STATUS_SUCCESS;
}

K(XeLoadSection) { return X_STATUS_SUCCESS; }  // every section is loaded up front
K(XeUnloadSection) { return X_STATUS_SUCCESS; }

K(HalRegisterShutdownNotification) { return 0; }
K(HalGetInterruptVector) {
    u32 level = arg(c, 0);
    if (arg(c, 1)) st<u8>(arg(c, 1), u8(26 - level));
    return 0x30 + level;
}
K(HalReadWritePCISpace) {
    if (!(arg(c, 5) & 0xFF)) std::memset(g_mem + arg(c, 3), 0, arg(c, 4));  // reads see nothing
    return 0;
}

// KINTERRUPT: ServiceRoutine @0, ServiceContext @4, BusInterruptLevel @8, Irql @0xC, Connected @0x10
// shortcut: interrupts are recorded but never delivered; the GPU vblank one comes with the renderer.
K(KeInitializeInterrupt) {
    u32 i = arg(c, 0);
    std::memset(g_mem + i, 0, 0x70);
    st<u32>(i, arg(c, 1)), st<u32>(i + 4, arg(c, 2)), st<u32>(i + 8, arg(c, 3) - 0x30);
    st<u32>(i + 0xC, arg(c, 4));
    return 0;
}
K(KeConnectInterrupt) {
    std::fprintf(stderr, "[k] interrupt %u connected: routine %08X\n", ld<u32>(arg(c, 0) + 8), ld<u32>(arg(c, 0)));
    st<u8>(arg(c, 0) + 0x10, 1);
    return 1;
}
K(KeDisconnectInterrupt) {
    st<u8>(arg(c, 0) + 0x10, 0);
    return 1;
}
K(KeSynchronizeExecution) {
    u8 old = ld<u8>(c.fs_base + KPCR_IRQL);
    st<u8>(c.fs_base + KPCR_IRQL, u8(ld<u32>(arg(c, 0) + 0xC)));
    u32 r = call_guest(c, arg(c, 1), {arg(c, 2)});
    st<u8>(c.fs_base + KPCR_IRQL, old);
    return r;
}

K(AvSendTVEncoderOption) {
    u32 option = arg(c, 1), result = arg(c, 3);
    if (result) st<u32>(result, option == 6 ? 0x00400104 : 0);  // 6: AV capabilities: HDTV pack, NTSC-M, 60 Hz
    return 0;
}
K(AvSetDisplayMode) {
    std::fprintf(stderr, "[k] AvSetDisplayMode mode %08X format %08X pitch %u framebuffer %08X\n", arg(c, 2),
                 arg(c, 3), arg(c, 4), arg(c, 5));
    return 0;
}

K(RtlAnsiStringToUnicodeString) {  // (UNICODE_STRING* dst, ANSI_STRING* src, BOOLEAN allocate)
    u32 dst = arg(c, 0), src = arg(c, 1);
    u16 n = ld<u16>(src);
    if (arg(c, 2) & 0xFF) {
        st<u32>(dst + 4, kalloc(2u * n + 2));
        st<u16>(dst + 2, u16(2 * n + 2));
    } else if (ld<u16>(dst + 2) < 2 * n) {
        return 0x80000005;  // STATUS_BUFFER_OVERFLOW
    }
    u32 in = ld<u32>(src + 4), out = ld<u32>(dst + 4);
    for (u16 k = 0; k < n; ++k) st<u16>(out + 2 * k, u16(ld<u8>(in + k)));  // Latin-1
    if (2 * n + 2 <= ld<u16>(dst + 2)) st<u16>(out + 2 * n, 0);
    st<u16>(dst, u16(2 * n));
    return X_STATUS_SUCCESS;
}

// TIME_FIELDS { Year, Month, Day, Hour, Minute, Second, Milliseconds, Weekday } as u16
K(RtlTimeToTimeFields) {
    FILETIME ft;
    u64 t = ld<u64>(arg(c, 0));
    ft.dwLowDateTime = DWORD(t), ft.dwHighDateTime = DWORD(t >> 32);
    SYSTEMTIME s;
    FileTimeToSystemTime(&ft, &s);
    u32 out = arg(c, 1);
    u16 f[8] = {s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, s.wMilliseconds, s.wDayOfWeek};
    std::memcpy(g_mem + out, f, 16);
    return 0;
}
K(RtlTimeFieldsToTime) {
    u32 in = arg(c, 0);
    SYSTEMTIME s = {};
    s.wYear = ld<u16>(in), s.wMonth = ld<u16>(in + 2), s.wDay = ld<u16>(in + 4), s.wHour = ld<u16>(in + 6);
    s.wMinute = ld<u16>(in + 8), s.wSecond = ld<u16>(in + 10), s.wMilliseconds = ld<u16>(in + 12);
    FILETIME ft;
    if (!SystemTimeToFileTime(&s, &ft)) return 0;  // FALSE: invalid fields
    st<u64>(arg(c, 1), (u64(ft.dwHighDateTime) << 32) | ft.dwLowDateTime);
    return 1;
}

K(RtlInitAnsiString) {
    u32 dst = arg(c, 0), src = arg(c, 1);
    u16 n = src ? u16(std::strlen(reinterpret_cast<char*>(g_mem + src))) : 0;
    st<u16>(dst, n);
    st<u16>(dst + 2, src ? n + 1 : 0);
    st<u32>(dst + 4, src);
    return 0;
}
K(RtlEqualString) {
    std::string a = ansi(arg(c, 0)), b = ansi(arg(c, 1));
    if (arg(c, 2)) return _stricmp(a.c_str(), b.c_str()) == 0;
    return a == b;
}
K(RtlCompareMemoryUlong) {
    u32 p = arg(c, 0), len = arg(c, 1), v = arg(c, 2), n = 0;
    while (n + 4 <= len && ld<u32>(p + n) == v) n += 4;
    return n;
}
K(RtlNtStatusToDosError) { return nt_to_dos_error(arg(c, 0)); }

// XAPI's APC routine for ReadFileEx/WriteFileEx: calls the game's completion routine
// (error, bytes, OVERLAPPED*); the OVERLAPPED starts with the IO_STATUS_BLOCK.
K(NtUserIoApcDispatcher) {
    u32 routine = arg(c, 0), iosb = arg(c, 1);
    call_guest(c, routine, {nt_to_dos_error(ld<u32>(iosb)), ld<u32>(iosb + 4), iosb});
    return 0;
}

u32 nt_to_dos_error(u32 s) {
    switch (s) {
    case 0: return 0;
    case 0xC0000034: return ERROR_FILE_NOT_FOUND;
    case 0xC000003A: return ERROR_PATH_NOT_FOUND;
    case 0xC0000017: return ERROR_NOT_ENOUGH_MEMORY;
    case 0xC0000008: return ERROR_INVALID_HANDLE;
    case 0xC000000D: return ERROR_INVALID_PARAMETER;
    case 0x80000006: return ERROR_NO_MORE_FILES;
    case 0xC0000011: return ERROR_HANDLE_EOF;
    }
    return (s & 0xF0000000) == 0xC0000000 ? ERROR_GEN_FAILURE : 0;
}

REGISTER(DbgPrint)
REGISTER(ExAllocatePoolWithTag)
REGISTER(ExFreePool)
REGISTER(ExQueryPoolBlockSize)
REGISTER(ExQueryNonVolatileSetting)
REGISTER(AvGetSavedDataAddress)
REGISTER(AvSetSavedDataAddress)
REGISTER(HalIsResetOrShutdownPending)
REGISTER(HalReturnToFirmware)
REGISTER(KeBugCheck)
REGISTER(KeRaiseIrqlToDpcLevel)
REGISTER(KfRaiseIrql)
REGISTER(KfLowerIrql)
REGISTER(KeQuerySystemTime)
REGISTER(KeStallExecutionProcessor)
REGISTER(KeSaveFloatingPointState)
REGISTER(KeRestoreFloatingPointState)
REGISTER(MmAllocateContiguousMemory)
REGISTER(MmAllocateContiguousMemoryEx)
REGISTER(MmFreeContiguousMemory)
REGISTER(MmPersistContiguousMemory)
REGISTER(MmQueryAllocationSize)
REGISTER(MmGetPhysicalAddress)
REGISTER(MmClaimGpuInstanceMemory)
REGISTER(MmQueryAddressProtect)
REGISTER(MmSetAddressProtect)
REGISTER(MmLockUnlockBufferPages)
REGISTER(MmLockUnlockPhysicalPage)
REGISTER(NtAllocateVirtualMemory)
REGISTER(NtFreeVirtualMemory)
REGISTER(XeLoadSection)
REGISTER(XeUnloadSection)
REGISTER(HalRegisterShutdownNotification)
REGISTER(HalGetInterruptVector)
REGISTER(HalReadWritePCISpace)
REGISTER(KeInitializeInterrupt)
REGISTER(KeConnectInterrupt)
REGISTER(KeDisconnectInterrupt)
REGISTER(KeSynchronizeExecution)
REGISTER(AvSendTVEncoderOption)
REGISTER(AvSetDisplayMode)
REGISTER(RtlAnsiStringToUnicodeString)
REGISTER(RtlTimeToTimeFields)
REGISTER(RtlTimeFieldsToTime)
REGISTER(RtlInitAnsiString)
REGISTER(RtlEqualString)
REGISTER(RtlCompareMemoryUlong)
REGISTER(RtlNtStatusToDosError)
REGISTER(NtUserIoApcDispatcher)

static KFn g_impl[512];

// ---- data exports ----
static u32 data_export(const char* name, u32 size) {
    for (unsigned k = 0; k < g_kernel_export_count; ++k)
        if (std::strcmp(g_kernel_exports[k].name, name) == 0) return g_data[g_kernel_exports[k].ordinal];
    fatal("no data export %s (size %u)", name, size);
}

static void tick_thread() {
    u32 tick = data_export("KeTickCount", 4);
    DWORD start = GetTickCount();
    // OOGIE_PEEK=3e0db4,3e0db0: print those guest words every 2 s (debugging game state)
    std::vector<u32> peek;
    if (const char* p = std::getenv("OOGIE_PEEK"))
        for (char* e; *p; p = *e ? e + 1 : e) peek.push_back(std::strtoul(p, &e, 16));
    for (unsigned n = 1;; ++n) {
        st<u32>(tick, GetTickCount() - start);
        preempt_tick();
        if (!peek.empty() && n % 2000 == 0) {
            std::string line = "[peek]";
            for (u32 a : peek) {
                char buf[32];
                std::snprintf(buf, sizeof buf, " %08X=%08X", a, ld<u32>(a));
                line += buf;
            }
            std::fprintf(stderr, "%s\n", line.c_str());
        }
        Sleep(1);
    }
}

static bool g_thread_dump = std::getenv("OOGIE_THREADS") != nullptr;
void thread_dump_loop();

std::vector<std::pair<const char*, KFn>>& kernel_impls() {
    static std::vector<std::pair<const char*, KFn>> v;
    return v;
}

void kernel_init() {
    for (unsigned k = 0; k < g_kernel_export_count; ++k) {
        const KernelExport& e = g_kernel_exports[k];
        g_export[e.ordinal] = &e;
        if (e.data) g_data[e.ordinal] = kalloc(0x100);  // every Xbox data export fits in 256 bytes
    }
    for (auto& i : kernel_impls()) {
        bool found = false;
        for (unsigned k = 0; k < g_kernel_export_count; ++k)
            if (std::strcmp(g_kernel_exports[k].name, i.first) == 0)
                g_impl[g_kernel_exports[k].ordinal] = i.second, found = true;
        if (!found) fatal("kernel implementation %s has no export", i.first);
    }
    u32 v = data_export("XboxKrnlVersion", 8);
    st<u16>(v, 1), st<u16>(v + 2, 0), st<u16>(v + 4, 5838), st<u16>(v + 6, 1);
    st<u32>(data_export("HalDiskCachePartitionCount", 4), 3);
    u32 idex = data_export("IdexChannelObject", 0x30);  // CancelIo (0x1D11C3) walks its request list at +0x28
    st<u32>(idex + 0x28, idex + 0x28), st<u32>(idex + 0x2C, idex + 0x28);
    u32 name = data_export("XeImageFileName", 8);
    static const char path[] = "\\Device\\CdRom0\\default.xbe";
    st<u16>(name, sizeof path - 1), st<u16>(name + 2, sizeof path), st<u32>(name + 4, name + 8);
    std::memcpy(g_mem + name + 8, path, sizeof path);
    std::thread(tick_thread).detach();
    if (g_thread_dump) std::thread(thread_dump_loop).detach();
    start_dpc_thread();
}

u32 kernel_export_address(u32 ordinal) {
    if (ordinal >= 512 || !g_export[ordinal]) fatal("XBE imports unknown kernel ordinal %u", ordinal);
    return g_export[ordinal]->data ? g_data[ordinal] : KTHUNK_BASE + ordinal;
}

static std::mutex g_in_kernel_lock;
static std::map<u32, std::string> g_in_kernel;  // guest thread -> what it is doing

void thread_dump_loop() {  // OOGIE_THREADS: every 5 s, each guest thread's priority and kernel call
    for (;;) {
        Sleep(5000);
        std::lock_guard<std::mutex> l(g_in_kernel_lock);
        for (auto& [t, what] : g_in_kernel)
            std::fprintf(stderr, "[threads] %08X prio %2d  %s\n", t, thread_priority(t), what.c_str());
    }
}

void kernel_call(Ctx& c, u32 ordinal) {
    const KernelExport* e = ordinal < 512 ? g_export[ordinal] : nullptr;
    if (!e || e->data) fatal("call into kernel ordinal %u, which is not a function", ordinal);
    u32 ret = ld<u32>(c.esp);
    u32 a0 = e->fastcall ? c.ecx : arg(c, 0), a1 = e->fastcall ? c.edx : arg(c, 1);
    g_ring[g_ring_pos++ % 32] = {ordinal, ret, a0, a1};
    trace("[k] %s(%08X, %08X) from %08X", e->name, a0, a1, ret);
    if (!g_impl[ordinal]) {
        print_recent();
        fatal("kernel function %s (ordinal %u) is not implemented; called from %08X", e->name, ordinal, ret);
    }
    u32 self = ld<u32>(c.fs_base + KPCR_CURRENT_THREAD);
    if (g_thread_dump) {  // OOGIE_THREADS: remember which kernel call each thread is inside
        char what[160];
        std::snprintf(what, sizeof what, "%s(%08X, %08X) from %08X", e->name, a0, a1, ret);
        std::lock_guard<std::mutex> l(g_in_kernel_lock);
        g_in_kernel[self] = what;
    }
    static const bool slow_log = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // calls that keep the guest lock long (testing)
    auto t0 = slow_log ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
    c.eax = g_impl[ordinal](c);
    if (slow_log) {
        double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        if (ms > 5 && !std::strstr(e->name, "Wait") && !std::strstr(e->name, "Delay") && !std::strstr(e->name, "Yield"))
            std::fprintf(stderr, "[slow] thread %08X in %s took %.1f ms\n", self, e->name, ms);
        else if (ms > 10 && std::strstr(e->name, "Wait"))  // a long wait: on what, and who called
            std::fprintf(stderr, "[wait] thread %08X in %s(%08X, %08X) from %08X: %.1f ms\n", self, e->name, a0, a1, ret, ms);
    }
    if (g_trace && (c.eax & 0xC0000000) == 0xC0000000 && e->name[0] == 'N')  // Nt* calls that failed
        trace("[k]   %s failed: %08X", e->name, c.eax);
    if (g_thread_dump) {
        std::lock_guard<std::mutex> l(g_in_kernel_lock);
        g_in_kernel[self] = "running guest code";
    }
    int pop = e->argbytes < 0 ? 0 : e->fastcall ? (e->argbytes > 8 ? e->argbytes - 8 : 0) : e->argbytes;
    c.esp += 4 + pop;
}
