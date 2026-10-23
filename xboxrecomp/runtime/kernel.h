// Shared by the kernel implementation files.
#pragma once
#include <chrono>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "func_table.h"
#include "runtime.h"

// Each implementation reads its own arguments and returns eax; kernel_call pops the stack.
typedef u32 (*KFn)(Ctx&);
#define K(name) static u32 k_##name(Ctx& c)
#define REGISTER(name) static const int reg_##name = (kernel_impls().push_back({#name, k_##name}), 0);
std::vector<std::pair<const char*, KFn>>& kernel_impls();

inline u32 arg(Ctx& c, int i) { return ld<u32>(c.esp + 4 + 4 * i); }

void guest_lock();
void guest_unlock();
void set_guest_thread(u32 thread);  // marks a host thread as running this guest thread (scheduling priority)
int thread_priority(u32 thread);
std::string guest_slices_since(std::chrono::steady_clock::time_point t0);  // OOGIE_HITCH_TRACE: lock holders since t0
std::string guest_cpu_report();  // " thread:ms(priority)" run time per guest thread since the last call
void signal_any();
u32 set_event(u32 event_object);  // returns the previous state
void queue_apc(Ctx& c, u32 routine, u32 a1, u32 a2, u32 a3);  // runs in the thread's next alertable wait
void queue_apc_for(u32 thread, u32 routine, u32 a1, u32 a2, u32 a3);  // same, from outside that thread (guest lock held)
u32 current_guest_thread(Ctx& c);
u32 nt_to_dos_error(u32 status);
void preempt_tick();
u32 object_from_handle(Ctx& c, u32 handle);
[[noreturn]] void thread_exit(Ctx& c, u32 status);
extern unsigned long g_boot_thread;  // host thread id running the XBE entry
void start_dpc_thread();
bool close_file(u32 handle);

// Call a guest function from kernel code (stdcall or cdecl: the stack is restored either way).
inline u32 call_guest(Ctx& c, u32 fn, std::initializer_list<u32> args) {
    u32 sp = c.esp;
    for (auto it = args.end(); it != args.begin();) push32(c, *--it);
    push32(c, 0);
    dispatch(c, fn);
    c.esp = sp;
    return c.eax;
}
