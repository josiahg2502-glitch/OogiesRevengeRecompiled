// SPDX-License-Identifier: ODbL-1.0

#pragma once

#include <xref/list_xref.h>

#include <cassert>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

typedef struct _version_ranges {
    uint16_t intro_start;
    uint16_t intro_end;
    uint32_t revive_start;
    uint32_t revive_end;
} version_ranges;

#define VER_NONE 0x000
#define VER_MAX  0xFFFF

#define STRINGIZEX(x)  #x
#define STRINGIZE(x)   STRINGIZEX(x)
#define XREF_SYMBOL(e) XREF_##e

static constexpr version_ranges VER_RANGE(uint16_t intro_start,
                                          uint16_t intro_end,
                                          uint16_t revive_start,
                                          uint16_t revive_end = VER_MAX)
{
    return version_ranges{
        .intro_start = intro_start,
        .intro_end = intro_end,
        .revive_start = revive_start,
        .revive_end = revive_end
    };
}
static constexpr version_ranges VER_RANGE(uint16_t intro_start,
                                          uint16_t intro_end = VER_MAX)
{
    return VER_RANGE(intro_start, intro_end, VER_NONE, VER_NONE);
}
// clang-format off
#define REGISTER_SYMBOL_INLINE(e, v) { XREF_SYMBOL(e), {{ #e, v}}}
// Below are aliases for XREF usage only.
#define REGISTER_SYMBOL_INLINE_D3D(e, v) { XREF_SYMBOL(D3D_##e), {{ #e, v}}}
#define REGISTER_SYMBOL_INLINE_D3D8(e, v) { XREF_SYMBOL(D3D8_##e), {{ #e, v}}}
#define REGISTER_SYMBOL_INLINE_VAR_OFFSET(e, v) { XREF_SYMBOL(OFFSET_##e), {{ STRINGIZE(e##_OFFSET), v}}}
// Below macros are intended to use multiple symbol names combine with single XREF.
#define REGISTER_SYMBOL(e, v) { #e, v}
#define REGISTER_SYMBOLS(Symbol, ...) { XREF_##Symbol, { __VA_ARGS__ }}
// clang-format on
// NOTE: Using std::map does not check for duplicate xrefs from same variable!
typedef const std::multimap<uint32_t, const std::map<const std::string, version_ranges>>
    library_list;

struct subcategory_db {
    std::string name;
    const library_list* optional = nullptr;
    const library_list* min = nullptr;
    const library_list* full = nullptr;
};

struct library_db {
    std::vector<const subcategory_db*> subcategories;
    uint32_t xref_offset = 0;
    uint32_t xref_total = 0;
    uint32_t xref_exclude = 0;
};

void getLibraryD3D8(library_db& lib_db);

void getLibraryDSOUND(library_db& lib_db);

void getLibraryJVS(library_db& lib_db);

void getLibraryXACTENG(library_db& lib_db);

void getLibraryXAPILIB(library_db& lib_db);

void getLibraryXGRAPHIC(library_db& lib_db);

void getLibraryXNET(library_db& lib_db);

void getLibraryXONLINE(library_db& lib_db);
