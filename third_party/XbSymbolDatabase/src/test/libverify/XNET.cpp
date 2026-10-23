// SPDX-License-Identifier: ODbL-1.0

#include "unittest.hpp"

static const library_list database_min = {};

static const library_list database_full = {
    REGISTER_SYMBOLS(XnInit,
                     REGISTER_SYMBOL(XnInit_8, VER_RANGE(3911, 4361)),
                     REGISTER_SYMBOL(XnInit_24, VER_RANGE(4361))),
    REGISTER_SYMBOL_INLINE(WSAStartup, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(XNetStartup, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(XNetGetEthernetLinkStatus, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(bind, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(connect, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(ioctlsocket, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(listen, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(recv, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(send, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(socket, VER_RANGE(3911)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xnet.def>
#undef XREF_SYMBOL
    LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(XnInit)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

static const subcategory_db xnet_db = {
    .name = "general",
    .optional = nullptr,
    .min = nullptr, //&database_min,
    .full = &database_full,
};

void getLibraryXNET(library_db& lib_db)
{
    lib_db.subcategories = { &xnet_db };
    lib_db.xref_offset = XREF_OFFSET;
    lib_db.xref_total = LOCAL_COUNT;
    lib_db.xref_exclude = 0;
}
