// SPDX-License-Identifier: ODbL-1.0

#include "unittest.hpp"

static const library_list database_full = {
    REGISTER_SYMBOL_INLINE(CXo_XOnlineLogon, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(XOnlineLogon, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSearch, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(XOnlineMatchSearch, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSearchResultsLen, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(XOnlineMatchSearchResultsLen, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSearchGetResults, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(XOnlineMatchSearchGetResults, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSessionUpdate, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(XOnlineMatchSessionUpdate, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSessionCreate, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(XOnlineMatchSessionCreate, VER_RANGE(4721)),
    REGISTER_SYMBOLS(XoUpdateLaunchNewImageInternal,
                     REGISTER_SYMBOL(XoUpdateLaunchNewImageInternal_12, VER_RANGE(4627, 5028)),
                     REGISTER_SYMBOL(XoUpdateLaunchNewImageInternal_16, VER_RANGE(5028))),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xonline.def>
#undef XREF_SYMBOL
    LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(CXo_XOnlineLogon)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

static const subcategory_db xonline_db = {
    .name = "general",
    .optional = nullptr,
    .min = nullptr, //&database_min,
    .full = &database_full,
};

void getLibraryXONLINE(library_db& lib_db)
{
    lib_db.subcategories = { &xonline_db };
    lib_db.xref_offset = XREF_OFFSET;
    lib_db.xref_total = LOCAL_COUNT;
    lib_db.xref_exclude = 0;
}
