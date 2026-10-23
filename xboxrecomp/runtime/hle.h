// High-level replacements for XDK library functions (D3D8, DSOUND, ...), installed by name over the
// recompiled originals through the XDK_ENTRY hook at the top of each function XbSymbolDatabase named.
#pragma once
#include <utility>
#include <vector>

#include "func_table.h"
#include "runtime.h"

typedef u32 (*HleFn)(Ctx&);  // returns eax; hle_hook pops the arguments for the symbol's convention

// HLE(D3DDevice_Clear) { ... }  then  HLE_REGISTER(D3DDevice_Clear)
#define HLE(name) static u32 hle_##name(Ctx& c)
#define HLE_REGISTER(name) static const int hle_reg_##name = (hle_impls().push_back({#name, hle_##name}), 0);
std::vector<std::pair<const char*, HleFn>>& hle_impls();
// HLE_BEFORE(StartChapter) { ... }  then  HLE_BEFORE_REGISTER(StartChapter): runs at the entry of a named function,
// which then runs as recompiled (for adjusting its arguments: test switches)
#define HLE_BEFORE(name) static void hle_before_##name(Ctx& c)
#define HLE_BEFORE_REGISTER(name) static const int hle_before_reg_##name = (hle_befores().push_back({#name, hle_before_##name}), 0);
std::vector<std::pair<const char*, void (*)(Ctx&)>>& hle_befores();
extern bool g_trace_d3d_now;  // while set, every hooked D3D8 call is logged (OOGIE_SNAP's frame)

// i-th stack argument of the call being replaced (esp points at the return address)
inline u32 sarg(Ctx& c, int i) { return ld<u32>(c.esp + 4 + 4 * i); }
inline float sargf(Ctx& c, int i) { return ld<float>(c.esp + 4 + 4 * i); }

void hle_init();

// A guest address that runs fn when called (for vtables and callbacks handed to the game).
// The guest calls it stdcall: fn gets esp at the return address; stack_bytes are popped afterwards.
u32 hle_thunk(HleFn fn, int stack_bytes, const char* name);
void hle_thunk_call(Ctx& c, u32 index);
const char* xdk_name(u32 addr);  // XbSymbolDatabase name of a function start, or nullptr
