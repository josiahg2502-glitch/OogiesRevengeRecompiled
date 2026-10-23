// Installs HLE replacements and call tracing on XDK library functions.
//
// OOGIE_TRACE_XDK=D3D8,DSOUND logs every call into those libraries (name, caller, first arguments),
// whether or not the function is replaced; "all" traces every named library.
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "hle.h"

std::vector<std::pair<const char*, HleFn>>& hle_impls() {
    static std::vector<std::pair<const char*, HleFn>> v;
    return v;
}

static std::vector<HleFn> g_impl;  // by symbol index
static std::vector<bool> g_traced;

bool g_trace_d3d_now;

static bool hook(Ctx& c, u32 k) {
    const XdkSymbol& s = g_xdk_symbols[k];
    if (g_traced[k] || (g_trace_d3d_now && std::strcmp(s.lib, "D3D8") == 0)) {
        u32 a0 = s.call == XDK_FASTCALL || s.call == XDK_THISCALL ? c.ecx : ld<u32>(c.esp + 4);
        std::fprintf(stderr, "[%s] %s%s from %08X (%08X, %08X, %08X, %08X, %08X, %08X)\n", s.lib, s.name,
                     g_impl[k] ? "" : " (original)", ld<u32>(c.esp), a0, ld<u32>(c.esp + 8), ld<u32>(c.esp + 12),
                     ld<u32>(c.esp + 16), ld<u32>(c.esp + 20), ld<u32>(c.esp + 24));
    }
    HleFn fn = g_impl[k];
    if (!fn) return false;
    static const bool slow_log = std::getenv("OOGIE_HITCH_TRACE") != nullptr;  // calls that keep the guest lock long (testing)
    auto t0 = slow_log ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
    c.eax = fn(c);
    if (slow_log) {
        double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        if (ms > 5 && !std::strstr(s.name, "Swap") && !std::strstr(s.name, "BlockUntil") && !std::strstr(s.name, "Present"))
            std::fprintf(stderr, "[slow] thread %08X in %s took %.1f ms\n", ld<u32>(c.fs_base + KPCR_CURRENT_THREAD), s.name, ms);
    }
    c.esp += 4 + (s.call == XDK_CDECL ? 0 : s.stack_bytes);  // return address + callee-popped arguments
    return true;
}

struct Thunk {
    HleFn fn;
    int stack_bytes;
    const char* name;
};
static std::vector<Thunk> g_thunks;

u32 hle_thunk(HleFn fn, int stack_bytes, const char* name) {
    if (g_thunks.size() >= 0x10000) fatal("out of HLE thunks");
    g_thunks.push_back({fn, stack_bytes, name});
    return HLE_THUNK_BASE + u32(g_thunks.size() - 1);
}

void hle_thunk_call(Ctx& c, u32 index) {
    if (index >= g_thunks.size()) fatal("call to unassigned HLE thunk %u", index);
    const Thunk& t = g_thunks[index];
    trace("[hle] %s from %08X", t.name, ld<u32>(c.esp));
    c.eax = t.fn(c);
    c.esp += 4 + t.stack_bytes;
}

const char* xdk_name(u32 addr) {
    for (unsigned k = 0; k < g_xdk_symbol_count; ++k)
        if (g_xdk_symbols[k].addr == addr) return g_xdk_symbols[k].name;
    return nullptr;
}

void hle_init() {
    g_impl.assign(g_xdk_symbol_count, nullptr);
    g_traced.assign(g_xdk_symbol_count, false);
    for (auto& [name, fn] : hle_impls()) {
        bool found = false;
        for (unsigned k = 0; k < g_xdk_symbol_count; ++k)
            if (std::strcmp(g_xdk_symbols[k].name, name) == 0) g_impl[k] = fn, found = true;
        // the database did not find it in this XBE: a replacement for nothing is a bug
        if (!found) fatal("HLE replacement %s has no symbol in this XBE", name);
    }
    std::string libs = std::getenv("OOGIE_TRACE_XDK") ? std::getenv("OOGIE_TRACE_XDK") : "";
    unsigned installed = 0;
    for (unsigned k = 0; k < g_xdk_symbol_count; ++k) {
        std::string lib = g_xdk_symbols[k].lib;
        g_traced[k] = libs == "all" || ("," + libs + ",").find("," + lib + ",") != std::string::npos;
        if (g_impl[k] || g_traced[k]) g_xdk_hook[k] = hook, ++installed;
    }
    std::fprintf(stderr, "[hle] %zu replacements, %u hooks installed (%u named XDK functions)\n", hle_impls().size(),
                 installed, g_xdk_symbol_count);
}
