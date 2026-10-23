// Tables emitted by codegen.py, read by the runtime.
#pragma once
#include "x86.h"

struct FuncEntry {
    u32 addr;
    void (*fn)(Ctx&);
};
struct KernelThunk {
    u32 slot;     // guest address of the import slot
    u32 ordinal;  // xboxkrnl.exe export number
};
extern const FuncEntry g_func_table[];
extern const unsigned g_func_count;
extern const KernelThunk g_kernel_thunks[];
extern const unsigned g_kernel_thunk_count;

struct KernelExport {
    u32 ordinal;
    const char* name;
    int argbytes;  // -1: cdecl (caller pops)
    bool fastcall;
    bool data;
};
extern const KernelExport g_kernel_exports[];
extern const unsigned g_kernel_export_count;

// XDK library functions named by XbSymbolDatabase; each one's entry checks g_xdk_hook[index].
enum XdkCall { XDK_STDCALL, XDK_CDECL, XDK_FASTCALL, XDK_THISCALL };
struct XdkSymbol {
    u32 addr;
    const char* lib;
    const char* name;
    int call;         // XdkCall
    int stack_bytes;  // arguments passed on the stack
};
extern const XdkSymbol g_xdk_symbols[];
extern const unsigned g_xdk_symbol_count;
