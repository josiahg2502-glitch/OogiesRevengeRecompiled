// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XGSetVertexBufferHeader
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_NO_XREF(XGSetVertexBufferHeader,
                         4134)
OOVPA_SIG_MATCH(

    { 0x01, 0x44 },
    { 0x04, 0x8B },
    { 0x07, 0x18 },
    { 0x0A, 0x08 },

    { 0x0C, 0xC7 },
    { 0x0D, 0x00 },
    { 0x0E, 0x01 },
    { 0x0F, 0x00 },
    { 0x10, 0x00 }, // XGSetVertexBufferHeader 0x00 vs XGSetIndexBufferHeader 0x01
    { 0x11, 0x00 },
    { 0x12, 0x89 },
    { 0x13, 0x48 },
    { 0x14, 0x04 },
    { 0x15, 0xC2 },
    { 0x16, 0x18 },
    //
);

// ******************************************************************
// * XGSetIndexBufferHeader
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_NO_XREF(XGSetIndexBufferHeader,
                         4134)
OOVPA_SIG_MATCH(

    { 0x01, 0x44 },
    { 0x04, 0x8B },
    { 0x07, 0x18 },
    { 0x0A, 0x08 },

    { 0x0C, 0xC7 },
    { 0x0D, 0x00 },
    { 0x0E, 0x01 },
    { 0x0F, 0x00 },
    { 0x10, 0x01 }, // XGSetVertexBufferHeader 0x00 vs XGSetIndexBufferHeader 0x01
    { 0x11, 0x00 },
    { 0x12, 0x89 },
    { 0x13, 0x48 },
    { 0x14, 0x04 },
    { 0x15, 0xC2 },
    { 0x16, 0x18 },
    //
);
