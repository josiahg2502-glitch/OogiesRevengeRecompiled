// Runtime pieces shared between the loader, memory and kernel.
#pragma once
#include "x86.h"

// Guest address map (our choice where the Xbox kernel would have decided)
constexpr u32 CONTIGUOUS_BASE = 0x80000000;  // MmAllocateContiguousMemory: 0x80000000 | physical
constexpr u32 RAM_SIZE = 64u << 20;
constexpr u32 VIRTUAL_BASE = 0x00500000;     // NtAllocateVirtualMemory, after the image
constexpr u32 KERNEL_BASE = 0xB0000000;      // HLE kernel objects, pool, data exports
constexpr u32 STACK_BASE = 0xD0000000;       // thread stacks
constexpr u32 KTHUNK_BASE = 0xFFFE0000;      // kernel import slots point at KTHUNK_BASE + ordinal
constexpr u32 HLE_THUNK_BASE = 0xFFFD0000;   // guest-callable addresses of C++ functions (vtables, callbacks)

// Xbox KPCR / KTHREAD offsets the XDK libraries read through fs
constexpr u32 KPCR_SELF = 0x18, KPCR_SELFPCR = 0x1C, KPCR_PRCB = 0x20, KPCR_IRQL = 0x24,
              KPCR_CURRENT_THREAD = 0x28;
constexpr u32 KTHREAD_STACK_BASE = 0x1C, KTHREAD_STACK_LIMIT = 0x20, KTHREAD_TLS_DATA = 0x28;
constexpr u32 ETHREAD_UNIQUE_THREAD = 0x12C;  // what XAPI GetCurrentThreadId returns
constexpr u32 KPCR_SIZE = 0x300, ETHREAD_SIZE = 0x200;

[[noreturn]] void fatal(const char* fmt, ...);
void dump_guest_stack(u32 esp);  // prints the guest return addresses above esp
extern u64 g_io_bytes, g_io_ns;  // file reads and writes done for the guest, for the frame statistics
void trace(const char* fmt, ...);
extern bool g_trace;

void mem_init();
u32 kalloc(u32 size, u32 align = 16);  // kernel pool, zeroed
u32 contiguous_alloc(u32 size, u32 align);
u32 contiguous_size(u32 va);  // 0 if va is not the start of an allocation
u32 virtual_alloc(u32 size);
u32 stack_alloc(u32 size);
void guest_commit(u32 addr, u32 len);  // before handing guest memory to Windows APIs              // returns the top

struct XbeInfo {
    u32 base, entry, tls_dir;
};
XbeInfo xbe_load(const char* path);

void kernel_init();
void kernel_call(Ctx& c, u32 ordinal);
u32 kernel_export_address(u32 ordinal);
u32 thread_setup(Ctx& c, u32 stack_size, u32 tls_size);  // fresh KPCR + ETHREAD; returns the thread
