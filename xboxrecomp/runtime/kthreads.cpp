// Threads, scheduling and dispatcher objects.
//
// The Xbox has one CPU and its code relies on that (plain `inc [x]` is atomic, raising IRQL stops
// everyone else), so only one guest thread runs at a time: it holds the guest lock. Like the Xbox
// kernel, the lock goes to the highest-priority thread that wants to run (first come first served
// among equals): a waiting thread of higher priority preempts the running one at its next safepoint
// (function entry or backward branch), one of equal priority after a quantum, a lower one never.
// Nothing is preempted at DISPATCH_LEVEL. Guest code depends on this: Oogie's Revenge builds each
// frame on a priority +2 thread that the priority 0 render thread must not interleave with.
#include <windows.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <condition_variable>
#include <cstdio>
#include <mutex>
#include <string>
#include <unordered_map>
#include <thread>
#include <vector>

#include "kernel.h"

volatile u32 g_yield_request;
DWORD g_boot_thread;

static std::mutex g_m;
static std::condition_variable g_cv;
static u64 g_signal_epoch;  // bumped whenever any object may have become signaled

constexpr int SERVICE_PRIORITY = 32;  // DPC, vblank and audio service threads: above every game thread
static const DWORD QUANTUM_MS = std::getenv("OOGIE_QUANTUM_MS") ? std::strtoul(std::getenv("OOGIE_QUANTUM_MS"), nullptr, 10) : 20;  // round robin slice between equal priorities

struct Waiter {
    u64 ticket;
    int priority;
    bool yielded;  // came from NtYieldExecution: steps aside for any ready thread until a quantum passes
};
static std::vector<Waiter> g_waiting;  // threads wanting the guest lock (under g_m)
static u64 g_next_ticket;
static bool g_held;
static int g_running_priority;
static DWORD g_running_since;
// time each guest thread held the lock (ran), for guest_cpu_report (under g_m)
static std::unordered_map<u32, u64> g_run_ns;
static std::chrono::steady_clock::time_point g_held_since;
static u32 g_holder;


// SuspendThread: a suspended thread parks the next time it takes the guest lock.
static std::unordered_map<u32, int> g_suspend_count;  // thread object -> count (under g_m)
static std::unordered_map<u32, int> g_priority;       // thread object -> priority (under g_m)
static int priority_of(u32 thread);
static thread_local u32 t_self;                       // this host thread's guest thread object

void set_guest_thread(u32 thread) { t_self = thread; }
int thread_priority(u32 thread) {
    std::lock_guard<std::mutex> l(g_m);
    return priority_of(thread);
}

static int priority_of(u32 thread) {  // under g_m
    if (!thread) return SERVICE_PRIORITY;
    auto it = g_priority.find(thread);
    return it == g_priority.end() ? 8 : it->second;  // Xbox threads start at priority 8
}

static u64 next_owner() {  // ticket of the waiter that gets the lock next (under g_m)
    const Waiter* best = nullptr;
    for (const Waiter& w : g_waiting)
        if (!best || (best->yielded && !w.yielded) ||
            (w.yielded == best->yielded &&
             (w.priority > best->priority || (w.priority == best->priority && w.ticket < best->ticket))))
            best = &w;
    return best ? best->ticket : ~0ull;
}

// Should the running thread give way to a waiter? (under g_m)
static bool should_yield() {
    bool quantum_over = GetTickCount() - g_running_since >= QUANTUM_MS;
    for (const Waiter& w : g_waiting)
        if ((w.priority > g_running_priority && (!w.yielded || quantum_over)) ||
            (w.priority == g_running_priority && quantum_over))
            return true;
    return false;
}

static void lock_held(std::unique_lock<std::mutex>& l, bool yielded = false) {
    for (;;) {
        u64 t = g_next_ticket++;
        int prio = priority_of(t_self);
        g_waiting.push_back({t, prio, yielded});
        g_cv.wait(l, [&] { return !g_held && next_owner() == t; });
        for (auto it = g_waiting.begin(); it != g_waiting.end(); ++it)
            if (it->ticket == t) {
                g_waiting.erase(it);
                break;
            }
        auto s = g_suspend_count.find(t_self);
        if (t_self && s != g_suspend_count.end() && s->second > 0) {
            g_cv.notify_all();  // suspended: let the others run and wait for NtResumeThread
            g_cv.wait(l, [&] { return g_suspend_count[t_self] <= 0; });
            continue;
        }
        g_held = true, g_holder = t_self, g_held_since = std::chrono::steady_clock::now();
        for (Waiter& w : g_waiting) w.yielded = false;  // they stepped aside once; now they compete normally
        g_running_priority = prio;
        g_running_since = GetTickCount();
        return;
    }
}

// OOGIE_HITCH_TRACE: who held the guest lock and when, so a long frame can show where its time went (testing)
struct Slice {
    u32 thread;
    int priority;
    std::chrono::steady_clock::time_point from, to;
};
static const bool g_slice_trace = std::getenv("OOGIE_HITCH_TRACE") != nullptr;
static std::vector<Slice> g_slices;

static void unlock_held() {
    if (g_held && g_slice_trace && g_slices.size() < 100000)
        g_slices.push_back({g_holder, g_running_priority, g_held_since, std::chrono::steady_clock::now()});
    if (g_held)
        g_run_ns[g_holder] += u64(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - g_held_since).count());
    g_held = false;
    g_cv.notify_all();
}

std::string guest_slices_since(std::chrono::steady_clock::time_point t0) {  // " thread(prio)@start+ms" since t0, then forgets them
    std::lock_guard<std::mutex> l(g_m);
    std::string out;
    for (const Slice& s : g_slices) {
        if (s.to < t0) continue;
        double at = std::chrono::duration<double, std::milli>(s.from - t0).count(), ms = std::chrono::duration<double, std::milli>(s.to - s.from).count();
        if (ms < 0.2) continue;
        char b[64];
        std::snprintf(b, sizeof b, " %08X(%d)@%.1f+%.1f", s.thread, s.priority, at, ms);
        out += b;
    }
    g_slices.clear();
    return out;
}

std::string guest_cpu_report() {  // " thread:ms(priority)" per guest thread that ran since the last report
    std::lock_guard<std::mutex> l(g_m);
    std::string out;
    for (auto& [t, ns] : g_run_ns) {
        if (ns < 1000000) continue;
        char b[48];
        std::snprintf(b, sizeof b, " %08X:%.0fms(%d)", t, ns / 1e6, priority_of(t));
        out += b;
    }
    g_run_ns.clear();
    return out;
}

void guest_lock() {
    std::unique_lock<std::mutex> l(g_m);
    lock_held(l);
}

void guest_unlock() {
    std::lock_guard<std::mutex> l(g_m);
    unlock_held();
}

void guest_yield(Ctx& c, u32 pc) {
    g_yield_request = 0;
    if (g_trace) {  // where each thread is when preempted: shows what a stuck thread spins on
        static thread_local DWORD last;
        static const DWORD every = std::getenv("OOGIE_SAMPLE_MS") ? std::strtoul(std::getenv("OOGIE_SAMPLE_MS"), nullptr, 10) : 1000;
        if (GetTickCount() - last > every) {
            last = GetTickCount();
            trace("[sched] thread %08X at %08X", ld<u32>(c.fs_base + KPCR_CURRENT_THREAD), pc);
        }
    }
    if (ld<u8>(c.fs_base + KPCR_IRQL) >= 2) return;
    std::unique_lock<std::mutex> l(g_m);
    if (!should_yield()) return;
    unlock_held();
    lock_held(l);
}

void signal_any() {
    std::lock_guard<std::mutex> l(g_m);
    ++g_signal_epoch;
    g_cv.notify_all();
}

void preempt_tick() {
    std::lock_guard<std::mutex> l(g_m);
    if (g_held && should_yield()) g_yield_request = 1;
}

// Release the guest lock until something is signaled or `deadline` passes.
static void wait_for_signal(u64 seen_epoch, std::chrono::steady_clock::time_point deadline) {
    std::unique_lock<std::mutex> l(g_m);
    unlock_held();
    g_cv.wait_until(l, deadline, [&] { return g_signal_epoch != seen_epoch; });
    lock_held(l);
}

static u64 epoch() {
    std::lock_guard<std::mutex> l(g_m);
    return g_signal_epoch;
}

// ---- dispatcher objects (DISPATCHER_HEADER: Type @0, SignalState @4) ----
enum { NOTIFICATION_EVENT = 0, SYNCHRONIZATION_EVENT = 1, MUTANT = 2, SEMAPHORE = 5, THREAD = 6,
       NOTIFICATION_TIMER = 8, SYNCHRONIZATION_TIMER = 9 };
constexpr u32 X_STATUS_TIMEOUT = 0x102, X_STATUS_ABANDONED = 0x80, X_STATUS_MUTANT_NOT_OWNED = 0xC0000046,
              X_STATUS_SEMAPHORE_LIMIT_EXCEEDED = 0xC0000047, X_STATUS_INVALID_HANDLE = 0xC0000008;
// Timers keep their due time (host ms) and period (ms) where the kernel keeps DueTime/Period.
// Only the DPC thread advances armed timers, so a timer's DPC is never skipped.
constexpr u32 TIMER_DUE = 0x10, TIMER_DPC = 0x20, TIMER_PERIOD = 0x24, TIMER_SIZE = 0x28;
static std::vector<u32> g_timers;

static void arm_timer(u32 timer, u64 due_ms, u32 period, u32 dpc) {
    st<u64>(timer + TIMER_DUE, due_ms);
    st<u32>(timer + TIMER_PERIOD, period);
    st<u32>(timer + TIMER_DPC, dpc);
    st<s32>(timer + 4, 0);
    for (u32 t : g_timers)
        if (t == timer) return;
    g_timers.push_back(timer);
}

static u32 current_thread(Ctx& c) { return ld<u32>(c.fs_base + KPCR_CURRENT_THREAD); }

u32 object_from_handle(Ctx& c, u32 h) {
    if (h == 0xFFFFFFFE) return current_thread(c);  // NtCurrentThread()
    return h;  // handles are object addresses
}

static u64 now_ms() { return GetTickCount64(); }

static bool signaled(Ctx& c, u32 obj) {
    u8 type = ld<u8>(obj);
    if (type == MUTANT) return ld<s32>(obj + 4) > 0 || ld<u32>(obj + 0x18) == current_thread(c);
    return ld<s32>(obj + 4) > 0;
}

static void satisfy(Ctx& c, u32 obj) {
    switch (ld<u8>(obj)) {
    case SYNCHRONIZATION_EVENT:
    case SYNCHRONIZATION_TIMER: st<s32>(obj + 4, 0); break;
    case SEMAPHORE: st<s32>(obj + 4, ld<s32>(obj + 4) - 1); break;
    case MUTANT:
        st<s32>(obj + 4, ld<s32>(obj + 4) - 1);
        st<u32>(obj + 0x18, current_thread(c));
        break;
    }
}

// timeout: guest pointer to a LARGE_INTEGER in 100 ns units (negative = relative), or 0 = forever
static std::chrono::steady_clock::time_point deadline_from(u32 timeout) {
    auto now = std::chrono::steady_clock::now();
    if (!timeout) return std::chrono::steady_clock::time_point::max();
    s64 t = ld<s64>(timeout);
    if (t < 0) return now + std::chrono::microseconds(-t / 10);
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    s64 sys = (s64(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
    return now + std::chrono::microseconds(t > sys ? (t - sys) / 10 : 0);
}

// a due time in the same encoding, as a host GetTickCount64 value
static u64 due_ms(u32 due) {
    auto d = deadline_from(due) - std::chrono::steady_clock::now();
    s64 ms = std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
    return now_ms() + u64(ms > 0 ? ms : 0);
}

// ---- user APCs: queued by I/O completion on the issuing thread, run in its next alertable wait ----
struct Apc {
    u32 routine, a1, a2, a3;
};
static std::unordered_map<u32, std::vector<Apc>> g_apcs;  // thread object -> pending
constexpr u32 X_STATUS_USER_APC = 0xC0;

void queue_apc(Ctx& c, u32 routine, u32 a1, u32 a2, u32 a3) { g_apcs[current_thread(c)].push_back({routine, a1, a2, a3}); }
void queue_apc_for(u32 thread, u32 routine, u32 a1, u32 a2, u32 a3) { g_apcs[thread].push_back({routine, a1, a2, a3}); }
u32 current_guest_thread(Ctx& c) { return current_thread(c); }

// Runs the thread's pending APCs; true if there were any (the wait then returns STATUS_USER_APC).
static bool deliver_apcs(Ctx& c) {
    auto it = g_apcs.find(current_thread(c));
    if (it == g_apcs.end() || it->second.empty()) return false;
    std::vector<Apc> run;
    run.swap(it->second);
    for (const Apc& a : run) call_guest(c, a.routine, {a.a1, a.a2, a.a3});
    return true;
}

static u32 wait_objects(Ctx& c, const std::vector<u32>& objs, bool all, u32 timeout, bool alertable = false) {
    auto deadline = deadline_from(timeout);
    for (;;) {
        if (alertable && deliver_apcs(c)) return X_STATUS_USER_APC;
        u64 e = epoch();
        if (all) {
            bool ok = true;
            for (u32 o : objs) ok = ok && signaled(c, o);
            if (ok) {
                for (u32 o : objs) satisfy(c, o);
                return 0;
            }
        } else {
            for (size_t k = 0; k < objs.size(); ++k)
                if (signaled(c, objs[k])) {
                    satisfy(c, objs[k]);
                    return u32(k);
                }
        }
        if (std::chrono::steady_clock::now() >= deadline) return X_STATUS_TIMEOUT;
        // timers become signaled by time alone, so never sleep past the next millisecond tick
        auto next = std::chrono::steady_clock::now() + std::chrono::milliseconds(1);
        wait_for_signal(e, deadline < next ? deadline : next);
    }
}

K(KeWaitForSingleObject) { return wait_objects(c, {arg(c, 0)}, false, arg(c, 4), arg(c, 3) & 0xFF); }
K(NtWaitForSingleObject) {
    return wait_objects(c, {object_from_handle(c, arg(c, 0))}, false, arg(c, 2), arg(c, 1) & 0xFF);
}
K(NtWaitForSingleObjectEx) {
    return wait_objects(c, {object_from_handle(c, arg(c, 0))}, false, arg(c, 3), arg(c, 2) & 0xFF);
}
K(NtWaitForMultipleObjectsEx) {
    u32 n = arg(c, 0), handles = arg(c, 1);
    std::vector<u32> objs;
    for (u32 k = 0; k < n; ++k) objs.push_back(object_from_handle(c, ld<u32>(handles + 4 * k)));
    return wait_objects(c, objs, arg(c, 2) == 0, arg(c, 5), arg(c, 4) & 0xFF);
}

u32 set_event(u32 obj) {
    s32 prev = ld<s32>(obj + 4);
    st<s32>(obj + 4, 1);
    signal_any();
    return u32(prev);
}

static u32 new_object(u32 size, u8 type, s32 signal) {
    u32 o = kalloc(size);
    st<u8>(o, type);
    st<u8>(o + 2, u8(size / 4));
    st<s32>(o + 4, signal);
    st<u32>(o + 8, o + 8);  // empty WaitListHead
    st<u32>(o + 12, o + 8);
    return o;
}

// shortcut: object names (OBJECT_ATTRIBUTES) are ignored, so two opens of one name get two objects
K(NtCreateEvent) {
    st<u32>(arg(c, 0), new_object(0x10, u8(arg(c, 2)), arg(c, 3) & 0xFF));
    return 0;
}
K(KeSetEvent) { return set_event(arg(c, 0)); }
K(NtSetEvent) {
    u32 prev = set_event(object_from_handle(c, arg(c, 0)));
    if (arg(c, 1)) st<u32>(arg(c, 1), prev);
    return 0;
}
K(NtCreateSemaphore) {
    u32 o = new_object(0x14, SEMAPHORE, s32(arg(c, 2)));
    st<u32>(o + 0x10, arg(c, 3));  // Limit
    st<u32>(arg(c, 0), o);
    return 0;
}
K(NtReleaseSemaphore) {
    u32 o = object_from_handle(c, arg(c, 0));
    s32 prev = ld<s32>(o + 4), n = s32(arg(c, 1));
    if (s64(prev) + n > s64(ld<s32>(o + 0x10))) return X_STATUS_SEMAPHORE_LIMIT_EXCEEDED;
    st<s32>(o + 4, prev + n);
    if (arg(c, 2)) st<s32>(arg(c, 2), prev);
    signal_any();
    return 0;
}
K(NtCreateMutant) {
    bool owned = arg(c, 2) & 0xFF;
    u32 o = new_object(0x20, MUTANT, owned ? 0 : 1);
    if (owned) st<u32>(o + 0x18, current_thread(c));
    st<u32>(arg(c, 0), o);
    return 0;
}
K(NtReleaseMutant) {
    u32 o = object_from_handle(c, arg(c, 0));
    if (ld<u32>(o + 0x18) != current_thread(c)) return X_STATUS_MUTANT_NOT_OWNED;
    s32 prev = ld<s32>(o + 4);
    st<s32>(o + 4, prev + 1);
    if (prev + 1 > 0) st<u32>(o + 0x18, 0);
    if (arg(c, 1)) st<s32>(arg(c, 1), prev);
    signal_any();
    return 0;
}
K(NtCreateTimer) {
    u32 type = arg(c, 2) == 0 ? NOTIFICATION_TIMER : SYNCHRONIZATION_TIMER;
    st<u32>(arg(c, 0), new_object(TIMER_SIZE, u8(type), 0));
    return 0;
}
K(NtSetTimerEx) {
    u32 o = object_from_handle(c, arg(c, 0));
    if (arg(c, 2)) fatal("NtSetTimerEx with an APC is not implemented");
    if (arg(c, 7)) st<u8>(arg(c, 7), u8(ld<s32>(o + 4) != 0));  // PreviousState: a BOOLEAN
    arm_timer(o, due_ms(arg(c, 1)), arg(c, 6), 0);
    return 0;
}
K(KeInitializeTimerEx) {
    u32 o = arg(c, 0);
    std::memset(g_mem + o, 0, TIMER_SIZE);
    st<u8>(o, u8(NOTIFICATION_TIMER + arg(c, 1)));
    st<u8>(o + 2, TIMER_SIZE / 4);
    st<u32>(o + 8, o + 8), st<u32>(o + 12, o + 8);
    return 0;
}
K(KeSetTimer) {  // (Timer, LARGE_INTEGER DueTime passed by value, Dpc)
    u32 o = arg(c, 0);
    bool was_set = ld<u64>(o + TIMER_DUE) != 0;
    u32 due = c.esp + 8;  // the by-value DueTime sits on the stack as args 1 and 2
    arm_timer(o, due_ms(due), 0, arg(c, 3));
    return was_set;
}
K(KeCancelTimer) {
    u32 o = arg(c, 0);
    bool was_set = ld<u64>(o + TIMER_DUE) != 0;
    st<u64>(o + TIMER_DUE, 0);
    return was_set;
}

// ---- DPCs. KDPC: Type @0, Inserted @2, DeferredRoutine @0xC, DeferredContext @0x10,
//      SystemArgument1 @0x14, SystemArgument2 @0x18 ----
static std::vector<u32> g_dpc_queue;

K(KeInitializeDpc) {
    u32 d = arg(c, 0);
    std::memset(g_mem + d, 0, 0x1C);
    st<u16>(d, 19);  // DpcObject
    st<u32>(d + 0xC, arg(c, 1));
    st<u32>(d + 0x10, arg(c, 2));
    return 0;
}
static bool queue_dpc(u32 d, u32 a1, u32 a2) {
    if (ld<u8>(d + 2)) return false;
    st<u8>(d + 2, 1);
    st<u32>(d + 0x14, a1), st<u32>(d + 0x18, a2);
    g_dpc_queue.push_back(d);
    return true;
}
K(KeInsertQueueDpc) { return queue_dpc(arg(c, 0), arg(c, 1), arg(c, 2)); }
K(KeRemoveQueueDpc) {
    u32 d = arg(c, 0);
    if (!ld<u8>(d + 2)) return 0;
    st<u8>(d + 2, 0);
    for (auto it = g_dpc_queue.begin(); it != g_dpc_queue.end(); ++it)
        if (*it == d) {
            g_dpc_queue.erase(it);
            break;
        }
    return 1;
}

// The DPC/timer service: a guest thread that fires timers and runs DPCs at DISPATCH_LEVEL.
static void dpc_thread() {
    Ctx c;
    thread_setup(c, 0x10000, 0);
    guest_lock();
    for (;;) {
        u64 now = now_ms();
        for (u32 t : g_timers) {
            u64 due = ld<u64>(t + TIMER_DUE);
            if (!due || now < due) continue;
            u32 period = ld<u32>(t + TIMER_PERIOD);
            st<u64>(t + TIMER_DUE, period ? due + period : 0);
            st<s32>(t + 4, 1);
            signal_any();
            if (u32 d = ld<u32>(t + TIMER_DPC)) queue_dpc(d, u32(now), 0);
        }
        while (!g_dpc_queue.empty()) {
            u32 d = g_dpc_queue.front();
            g_dpc_queue.erase(g_dpc_queue.begin());
            st<u8>(d + 2, 0);
            st<u8>(c.fs_base + KPCR_IRQL, 2);
            call_guest(c, ld<u32>(d + 0xC), {d, ld<u32>(d + 0x10), ld<u32>(d + 0x14), ld<u32>(d + 0x18)});
            st<u8>(c.fs_base + KPCR_IRQL, 0);
        }
        guest_unlock();
        Sleep(1);
        guest_lock();
    }
}

void start_dpc_thread() { std::thread(dpc_thread).detach(); }
K(NtClose) {  // other objects live in the never-freed kernel pool
    close_file(arg(c, 0));
    return 0;
}
K(ObReferenceObjectByHandle) {
    st<u32>(arg(c, 2), object_from_handle(c, arg(c, 0)));
    return 0;
}
K(ObfDereferenceObject) { return 0; }
K(NtDuplicateObject) {
    st<u32>(arg(c, 1), object_from_handle(c, arg(c, 0)));
    return 0;
}

// ---- threads ----
struct ThreadStart {
    u32 kpcr, thread, esp, routine, context, system_routine;
    HANDLE resume;
};

static DWORD WINAPI thread_main(void* p) {
    ThreadStart s = *static_cast<ThreadStart*>(p);
    delete static_cast<ThreadStart*>(p);
    if (s.resume) WaitForSingleObject(s.resume, INFINITE);
    t_self = s.thread;
    guest_lock();
    Ctx c{};
    c.fs_base = s.kpcr;
    c.esp = s.esp;
    push32(c, s.context);
    if (s.system_routine) {
        push32(c, s.routine);
        push32(c, 0);
        dispatch(c, s.system_routine);  // SystemRoutine(StartRoutine, StartContext)
    } else {
        push32(c, 0);
        dispatch(c, s.routine);
    }
    thread_exit(c, 0);
}

void thread_exit(Ctx& c, u32 status) {
    u32 t = current_thread(c);
    st<s32>(t + 4, 1);  // thread objects signal when they end
    signal_any();
    trace("[thread] %08X exits with %08X", t, status);
    guest_unlock();
    if (GetCurrentThreadId() == g_boot_thread) Sleep(INFINITE);  // ending it would end the process
    ExitThread(status);
}

u32 thread_setup(Ctx& c, u32 stack_size, u32 tls_size) {
    u32 kpcr = kalloc(KPCR_SIZE), thread = new_object(ETHREAD_SIZE, THREAD, 0);
    u32 top = stack_alloc(stack_size + tls_size);
    u32 tls = tls_size ? top - tls_size : 0;
    st<u32>(kpcr + 0, 0xFFFFFFFF);  // NtTib.ExceptionList: end of SEH chain
    st<u32>(kpcr + 4, top);         // NtTib.StackBase
    st<u32>(kpcr + 8, top - tls_size - stack_size);
    st<u32>(kpcr + KPCR_SELF, kpcr);
    st<u32>(kpcr + KPCR_SELFPCR, kpcr);
    st<u32>(kpcr + KPCR_PRCB, kpcr + KPCR_CURRENT_THREAD);
    st<u32>(kpcr + KPCR_CURRENT_THREAD, thread);
    st<u32>(thread + KTHREAD_STACK_BASE, top);
    st<u32>(thread + KTHREAD_STACK_LIMIT, top - tls_size - stack_size);
    st<u32>(thread + KTHREAD_TLS_DATA, tls);
    st<u32>(thread + ETHREAD_UNIQUE_THREAD, thread);  // thread id = object address, as PsCreateSystemThreadEx reports it
    c = Ctx{};
    c.fs_base = kpcr;
    c.esp = (top - tls_size) & ~15u;
    return thread;
}

static std::mutex g_suspend_lock;
static std::vector<std::pair<u32, HANDLE>> g_suspended;  // thread object -> resume event

K(PsCreateSystemThreadEx) {
    u32 handle_out = arg(c, 0), stack = arg(c, 2), tls = arg(c, 3), id_out = arg(c, 4);  // XAPI finds its TLS at StackBase - size exactly
    u32 routine = arg(c, 5), context = arg(c, 6), system_routine = arg(c, 9);
    bool suspended = arg(c, 7) & 0xFF;
    Ctx tc;
    u32 t = thread_setup(tc, stack < 0x4000 ? 0x10000 : (stack + 0xFFF) & ~0xFFFu, tls);
    auto* s = new ThreadStart{tc.fs_base, t, tc.esp, routine, context, system_routine, nullptr};
    if (suspended) {
        s->resume = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        std::lock_guard<std::mutex> l(g_suspend_lock);
        g_suspended.push_back({t, s->resume});
    }
    HANDLE h = CreateThread(nullptr, 1 << 20, thread_main, s, 0, nullptr);
    if (!h) fatal("CreateThread failed");
    CloseHandle(h);
    st<u32>(handle_out, t);
    if (id_out) st<u32>(id_out, t);
    trace("[thread] %08X created: routine %08X context %08X system %08X%s", t, routine, context,
          system_routine, suspended ? " (suspended)" : "");
    return 0;
}
K(PsTerminateSystemThread) { thread_exit(c, arg(c, 0)); }
K(NtResumeThread) {
    u32 t = object_from_handle(c, arg(c, 0));
    {
        std::lock_guard<std::mutex> l(g_suspend_lock);
        for (auto it = g_suspended.begin(); it != g_suspended.end(); ++it)
            if (it->first == t) {  // created suspended: not started yet
                SetEvent(it->second);
                g_suspended.erase(it);
                if (arg(c, 1)) st<u32>(arg(c, 1), 1);
                return 0;
            }
    }
    std::lock_guard<std::mutex> l(g_m);
    int& n = g_suspend_count[t];
    if (arg(c, 1)) st<u32>(arg(c, 1), u32(n));
    if (n > 0 && --n == 0) g_cv.notify_all();
    return 0;
}
K(NtSuspendThread) {
    u32 t = object_from_handle(c, arg(c, 0));
    {
        std::lock_guard<std::mutex> l(g_m);
        int& n = g_suspend_count[t];
        if (arg(c, 1)) st<u32>(arg(c, 1), u32(n));
        ++n;
        g_yield_request = 1;  // make the target reach a safepoint soon
    }
    if (t == current_thread(c)) {  // suspending yourself takes effect at once
        guest_unlock();
        guest_lock();
    }
    return 0;
}
K(KeSetBasePriorityThread) {  // (thread, increment from the base priority 8); returns the old increment
    std::lock_guard<std::mutex> l(g_m);
    u32 t = arg(c, 0);
    int old = priority_of(t) - 8, inc = s32(arg(c, 1));
    g_priority[t] = std::max(1, std::min(31, 8 + inc));
    if (t == current_thread(c)) g_running_priority = g_priority[t];
    g_yield_request = 1;  // a waiter may now outrank the running thread
    return u32(old);
}
K(KeDelayExecutionThread) {
    if ((arg(c, 1) & 0xFF) && deliver_apcs(c)) return X_STATUS_USER_APC;  // SleepEx(..., TRUE)
    auto deadline = deadline_from(arg(c, 2));
    guest_unlock();
    if (deadline <= std::chrono::steady_clock::now()) SwitchToThread();
    else std::this_thread::sleep_until(deadline);
    guest_lock();
    return 0;
}
K(NtYieldExecution) {
    // Like NT, SwitchToThread yields to any ready thread, of any priority (Sleep(0) is the one limited to
    // equal or higher); STATUS_NO_YIELD_PERFORMED when none is ready, which ends the game's end-of-frame
    // "yield while others are busy" loop. Its render loop depends on the lower-priority main thread
    // getting in here.
    std::unique_lock<std::mutex> l(g_m);
    if (g_waiting.empty()) return 0x40000024;
    unlock_held();
    lock_held(l, true);
    return 0;
}

// Critical sections. Xbox RTL_CRITICAL_SECTION: DISPATCHER_HEADER (0x10), LockCount (0x10),
// RecursionCount (0x14), OwningThread (0x18).
K(RtlInitializeCriticalSection) {
    u32 cs = arg(c, 0);
    std::memset(g_mem + cs, 0, 0x1C);
    st<s32>(cs + 0x10, -1);
    return 0;
}
// OOGIE_TRACE_CS=<hex address>: logs who enters and leaves that critical section (debugging)
static u32 traced_cs() {
    static const char* env = std::getenv("OOGIE_TRACE_CS");
    static u32 cs = env ? u32(std::strtoul(env, nullptr, 16)) : 0;
    return cs;
}
K(RtlEnterCriticalSection) {
    u32 cs = arg(c, 0), me = current_thread(c);
    if (cs == traced_cs())
        std::fprintf(stderr, "[cs] %08X enter by %08X (owner %08X recursion %u irql %u) from %08X\n", cs, me, ld<u32>(cs + 0x18),
                     ld<u32>(cs + 0x14), ld<u8>(c.fs_base + KPCR_IRQL), ld<u32>(c.esp));
    for (;;) {
        u64 e = epoch();
        u32 owner = ld<u32>(cs + 0x18);
        if (!owner || owner == me) break;
        wait_for_signal(e, std::chrono::steady_clock::time_point::max());
    }
    st<s32>(cs + 0x10, ld<s32>(cs + 0x10) + 1);
    st<u32>(cs + 0x14, ld<u32>(cs + 0x14) + 1);
    st<u32>(cs + 0x18, me);
    return 0;
}
K(RtlLeaveCriticalSection) {
    u32 cs = arg(c, 0);
    if (cs == traced_cs())
        std::fprintf(stderr, "[cs] %08X leave by %08X (recursion %u) from %08X\n", cs, current_thread(c), ld<u32>(cs + 0x14), ld<u32>(c.esp));
    st<s32>(cs + 0x10, ld<s32>(cs + 0x10) - 1);
    u32 recursion = ld<u32>(cs + 0x14) - 1;
    st<u32>(cs + 0x14, recursion);
    if (recursion == 0) {
        st<u32>(cs + 0x18, 0);
        signal_any();
    }
    return 0;
}

REGISTER(RtlInitializeCriticalSection) REGISTER(RtlEnterCriticalSection) REGISTER(RtlLeaveCriticalSection)

REGISTER(KeWaitForSingleObject) REGISTER(NtWaitForSingleObject) REGISTER(NtWaitForSingleObjectEx)
REGISTER(NtWaitForMultipleObjectsEx) REGISTER(NtCreateEvent) REGISTER(KeSetEvent) REGISTER(NtSetEvent)
REGISTER(NtCreateSemaphore) REGISTER(NtReleaseSemaphore) REGISTER(NtCreateMutant) REGISTER(NtReleaseMutant)
REGISTER(NtCreateTimer) REGISTER(NtSetTimerEx) REGISTER(KeCancelTimer) REGISTER(KeInitializeTimerEx)
REGISTER(KeSetTimer) REGISTER(KeInitializeDpc) REGISTER(KeInsertQueueDpc) REGISTER(KeRemoveQueueDpc) REGISTER(NtClose)
REGISTER(ObReferenceObjectByHandle) REGISTER(ObfDereferenceObject) REGISTER(NtDuplicateObject)
REGISTER(PsCreateSystemThreadEx) REGISTER(PsTerminateSystemThread) REGISTER(NtResumeThread) REGISTER(NtSuspendThread)
REGISTER(KeSetBasePriorityThread) REGISTER(KeDelayExecutionThread) REGISTER(NtYieldExecution)
