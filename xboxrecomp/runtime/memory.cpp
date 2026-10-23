// Guest address space: one 4 GB host reservation, pages committed on first touch.
#include <windows.h>

#include <cstdio>
#include <mutex>
#include <map>
#include <set>

#include "runtime.h"

u8* g_mem;

static const char* hw_region(u32 a) {
    if (a >= 0xFD000000 && a < 0xFE000000) return "NV2A (GPU)";
    if (a >= 0xFE800000 && a < 0xFE880000) return "APU (audio)";
    if (a >= 0xFEC00000 && a < 0xFEC01000) return "ACI (AC97)";
    if (a >= 0xFED00000 && a < 0xFED01000) return "USB";
    if (a >= 0xFEF00000 && a < 0xFEF00400) return "NIC";
    if (a >= 0xFF000000) return "flash";
    return nullptr;
}

static std::mutex g_guard_lock;
static std::map<u32, u32> g_guards;  // guard page below each guest stack -> that stack's top

static LONG CALLBACK on_fault(EXCEPTION_POINTERS* e) {
    auto* r = e->ExceptionRecord;
    if (r->ExceptionCode != EXCEPTION_ACCESS_VIOLATION) return EXCEPTION_CONTINUE_SEARCH;
    u8* host = reinterpret_cast<u8*>(r->ExceptionInformation[1]);
    if (host < g_mem || host >= g_mem + (1ull << 32) + 0x10000) return EXCEPTION_CONTINUE_SEARCH;
    u32 a = u32(host - g_mem);
    {
        std::lock_guard<std::mutex> lock(g_guard_lock);
        auto it = g_guards.find(a & ~0xFFFu);
        if (it != g_guards.end())  // a guest stack ran past its bottom: on the Xbox this page is a guard too
            fatal("guest stack overflow: %s at %08X, below the stack with top %08X", r->ExceptionInformation[0] ? "write" : "read",
                  a, it->second);
    }
    if (const char* hw = hw_region(a)) {
        static std::mutex m;
        static std::set<u32> seen;
        std::lock_guard<std::mutex> lock(m);
        if (seen.insert(a & ~0xFFFu).second)
            std::fprintf(stderr, "[mem] first touch of %s at %08X (%s)\n", hw, a,
                         r->ExceptionInformation[0] ? "write" : "read");
    }
    if (!VirtualAlloc(g_mem + (u64(a) & ~0xFFFull), 0x1000, MEM_COMMIT, PAGE_READWRITE))
        return EXCEPTION_CONTINUE_SEARCH;
    return EXCEPTION_CONTINUE_EXECUTION;
}

// Physical RAM is one 64 MB section seen at two addresses, as on the Xbox: CONTIGUOUS_BASE (cached)
// and WRITE_COMBINED_BASE (D3D locks resources there: Lock2DSurface ORs 0xF0000000 into the address).
// Everything else in the 4 GB space is a plain reservation whose pages commit on first touch.
constexpr u32 WRITE_COMBINED_BASE = 0xF0000000;

void mem_init() {
    typedef PVOID(WINAPI * VirtualAlloc2Fn)(HANDLE, PVOID, SIZE_T, ULONG, ULONG, void*, ULONG);
    typedef PVOID(WINAPI * MapViewOfFile3Fn)(HANDLE, HANDLE, PVOID, ULONG64, SIZE_T, ULONG, ULONG, void*, ULONG);
    HMODULE kb = GetModuleHandleW(L"kernelbase.dll");
    auto va2 = kb ? reinterpret_cast<VirtualAlloc2Fn>(GetProcAddress(kb, "VirtualAlloc2")) : nullptr;
    auto map3 = kb ? reinterpret_cast<MapViewOfFile3Fn>(GetProcAddress(kb, "MapViewOfFile3")) : nullptr;
    if (!va2 || !map3) fatal("Windows 10 version 1803 or newer is required (VirtualAlloc2)");
    constexpr ULONG RESERVE_PLACEHOLDER = 0x00040000, REPLACE_PLACEHOLDER = 0x00004000, PRESERVE_PLACEHOLDER = 0x2;

    // +64 KB so an access that wraps past 0xFFFFFFFF stays inside the reservation
    const u64 total = (1ull << 32) + 0x10000;
    g_mem = static_cast<u8*>(va2(GetCurrentProcess(), nullptr, total, MEM_RESERVE | RESERVE_PLACEHOLDER,
                                 PAGE_NOACCESS, nullptr, 0));
    if (!g_mem) fatal("could not reserve 4 GB of address space");
    // split the placeholder around the two RAM views
    for (u32 view : {CONTIGUOUS_BASE, WRITE_COMBINED_BASE})
        if (!VirtualFree(g_mem + view, RAM_SIZE, MEM_RELEASE | PRESERVE_PLACEHOLDER))
            fatal("could not split the guest address space (%lu)", GetLastError());
    HANDLE ram = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, RAM_SIZE, nullptr);
    if (!ram) fatal("could not allocate 64 MB of guest RAM");
    for (u32 view : {CONTIGUOUS_BASE, WRITE_COMBINED_BASE})
        if (!map3(ram, GetCurrentProcess(), g_mem + view, 0, RAM_SIZE, REPLACE_PLACEHOLDER, PAGE_READWRITE, nullptr, 0))
            fatal("could not map guest RAM at %08X (%lu)", view, GetLastError());
    // the remaining placeholders become ordinary reservations
    const u64 gaps[3][2] = {{0, CONTIGUOUS_BASE},
                            {u64(CONTIGUOUS_BASE) + RAM_SIZE, WRITE_COMBINED_BASE},
                            {u64(WRITE_COMBINED_BASE) + RAM_SIZE, total}};
    for (auto& gap : gaps)
        if (!va2(GetCurrentProcess(), g_mem + gap[0], gap[1] - gap[0], MEM_RESERVE | REPLACE_PLACEHOLDER,
                 PAGE_READWRITE, nullptr, 0))
            fatal("could not reserve guest range %08llX (%lu)", (unsigned long long)gap[0], GetLastError());
    AddVectoredExceptionHandler(1, on_fault);
}

// Pages normally commit on first guest touch, but Windows APIs writing into guest memory (ReadFile)
// fail with ERROR_NOACCESS on uncommitted pages instead of faulting: commit those ranges up front.
void guest_commit(u32 addr, u32 len) {
    if (!len) return;
    u64 first = addr & ~0xFFFull, last = (u64(addr) + len + 0xFFF) & ~0xFFFull;
    for (u64 page = first; page < last; page += 0x1000)
        VirtualAlloc(g_mem + page, 0x1000, MEM_COMMIT, PAGE_READWRITE);  // no-op on the RAM views (always committed)
}

static std::mutex g_alloc_lock;
static std::map<u32, u32> g_contiguous_sizes;  // MmQueryAllocationSize

static u32 bump(u32& next, u32 limit, u32 size, u32 align, const char* what) {
    std::lock_guard<std::mutex> lock(g_alloc_lock);
    u32 a = (next + align - 1) & ~(align - 1);
    if (u64(a) + size > limit) fatal("out of %s memory (%u bytes requested)", what, size);
    next = a + size;
    return a;
}

u32 kalloc(u32 size, u32 align) {
    static u32 next = KERNEL_BASE;
    u32 a = bump(next, KERNEL_BASE + 0x10000000, size, align, "kernel pool");
    std::memset(g_mem + a, 0, size);
    return a;
}

u32 contiguous_alloc(u32 size, u32 align) {
    // shortcut: bump allocator, MmFreeContiguousMemory never returns space; add a free list
    // when the game runs out of its 64 MB.
    static u32 next = 0x00010000;
    u32 phys = bump(next, RAM_SIZE - 0x10000, size, align < 0x1000 ? 0x1000 : align, "contiguous");
    std::memset(g_mem + CONTIGUOUS_BASE + phys, 0, size);
    std::lock_guard<std::mutex> lock(g_alloc_lock);
    g_contiguous_sizes[CONTIGUOUS_BASE + phys] = size;
    return CONTIGUOUS_BASE + phys;
}

u32 contiguous_size(u32 va) {
    std::lock_guard<std::mutex> lock(g_alloc_lock);
    auto it = g_contiguous_sizes.find(va);
    return it == g_contiguous_sizes.end() ? 0 : it->second;
}

u32 virtual_alloc(u32 size) {
    static u32 next = VIRTUAL_BASE;
    return bump(next, 0x7FFF0000, (size + 0xFFFF) & ~0xFFFFu, 0x10000, "virtual");
}

u32 stack_alloc(u32 size) {
    static u32 next = STACK_BASE;
    u32 a = bump(next, STACK_BASE + 0x08000000, size + 0x1000, 0x1000, "stack");  // 4 KB guard page below
    std::lock_guard<std::mutex> lock(g_guard_lock);
    g_guards[a] = a + 0x1000 + size;
    return a + 0x1000 + size;
}

double ld80(u32 a) {
    u64 mant = ld<u64>(a);
    u16 se = ld<u16>(a + 8);
    int exp = se & 0x7FFF;
    double sign = (se & 0x8000) ? -1.0 : 1.0;
    if (exp == 0 && mant == 0) return sign * 0.0;
    if (exp == 0x7FFF) return (mant << 1) ? NAN : sign * INFINITY;
    return sign * std::ldexp(double(mant), exp - 16383 - 63);
}

void st80(u32 a, double v) {
    u16 se = std::signbit(v) ? 0x8000 : 0;
    u64 mant = 0;
    if (std::isnan(v)) se |= 0x7FFF, mant = 0xC000000000000000ull;
    else if (std::isinf(v)) se |= 0x7FFF, mant = 0x8000000000000000ull;
    else if (v != 0) {
        int e;
        double m = std::frexp(std::fabs(v), &e);  // m in [0.5, 1)
        mant = u64(std::ldexp(m, 64));
        se |= u16(e - 1 + 16383);
    }
    st<u64>(a, mant);
    st<u16>(a + 8, se);
}
