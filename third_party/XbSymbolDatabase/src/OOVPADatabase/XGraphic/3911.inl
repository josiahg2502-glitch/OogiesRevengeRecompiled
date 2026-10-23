// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XGIsSwizzledFormat
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGIsSwizzledFormat,
                         3911)
OOVPA_SIG_MATCH(

    { 0x07, 0x7F },
    { 0x10, 0x7C },
    { 0x19, 0x0B },
    { 0x22, 0xF8 },
    { 0x2B, 0x83 },
    { 0x34, 0x0A },
    { 0x3D, 0x7F },
    //
);

// ******************************************************************
// * XGSwizzleRect
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGSwizzleRect,
                         3911)
OOVPA_SIG_MATCH(

    { 0x1E, 0x03 },
    { 0x3E, 0x89 },
    { 0x5E, 0x83 },
    { 0x7E, 0x6C },
    { 0x9E, 0xFF },
    { 0xBE, 0xFF },
    { 0xDE, 0x89 },
    { 0xFE, 0x89 },
    //
);

// ******************************************************************
// * XGSwizzleBox
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGSwizzleBox,
                         3911)
OOVPA_SIG_MATCH(

    { 0x1E, 0x75 },
    { 0x3E, 0x4D },
    { 0x5E, 0x48 },
    { 0x7E, 0x04 },
    { 0x9E, 0xD8 },
    { 0xC0, 0x83 },
    { 0xDE, 0xAF },
    { 0xFE, 0x45 },
    //
);

// ******************************************************************
// * XGUnswizzleRect
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGUnswizzleRect,
                         3911)
OOVPA_SIG_MATCH(

    { 0x1E, 0x03 },
    { 0x3E, 0x00 },
    { 0x5E, 0xD2 },
    { 0x7E, 0x75 },
    { 0x9E, 0x70 },
    { 0xC1, 0xE9 },
    { 0xDE, 0x89 },
    { 0xFE, 0x60 },
    //
);

// ******************************************************************
// * XGWriteSurfaceOrTextureToXPR
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGWriteSurfaceOrTextureToXPR,
                         3911)
OOVPA_SIG_MATCH(

    { 0x0C, 0x08 },
    { 0x1E, 0x3D },

    { 0x21, 0x05 },
    { 0x22, 0x00 },
    { 0x23, 0x74 },
    { 0x24, 0x0A },
    { 0x25, 0xB8 },
    { 0x26, 0x05 },
    { 0x27, 0x40 },
    { 0x28, 0x00 },

    { 0x2E, 0x00 },
    { 0x47, 0x03 },

    /*
    { 0x1E, 0x3D },
    { 0x3E, 0xE0 },
    { 0x5E, 0x75 },
    { 0x7E, 0x33 },
    { 0x9E, 0xC2 },
    { 0xAE, 0x4D },
    { 0xBE, 0xF0 },*/
    //
);

// ******************************************************************
// * XGSetTextureHeader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGSetTextureHeader,
                         3911)
OOVPA_SIG_MATCH(

    { 0x04, 0x75 },
    { 0x0A, 0x00 },
    { 0x10, 0xFF },
    { 0x16, 0xFF },
    { 0x1C, 0x75 },
    { 0x26, 0x5D },
    { 0x28, 0x24 },
    //
);

// ******************************************************************
// * XGUnswizzleBox
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGUnswizzleBox,
                         3911)
OOVPA_SIG_MATCH(

    { 0x1E, 0x26 },
    { 0x3E, 0x55 },
    { 0x5E, 0x58 },
    { 0x7E, 0x89 },
    { 0xA0, 0xFF },
    { 0xBE, 0x2C },
    { 0xDE, 0x24 },
    { 0xFE, 0x20 },
    //
);

// ******************************************************************
// * XGCompressRect
// ******************************************************************
//Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(XGCompressRect,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8D },

    { 0x14, 0x83 },
    { 0x15, 0x7D },
    { 0x16, 0x6C },
    { 0x17, 0x00 },
    { 0x18, 0x56 },
    { 0x19, 0x57 },
    { 0x1A, 0xC7 },
    { 0x1B, 0x45 },

    { 0xC0, 0x7E },
    { 0xC1, 0x01 },
    //
);

// ******************************************************************
// * XGSetIndexBufferHeader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGSetIndexBufferHeader,
                         3911)
OOVPA_SIG_MATCH(

    { 0x01, 0x44 },
    { 0x04, 0x8B },

    { 0x06, 0x24 },
    { 0x07, 0x18 },
    { 0x08, 0xC7 },
    { 0x09, 0x00 },
    { 0x0A, 0x01 },
    { 0x0B, 0x00 },
    { 0x0C, 0x01 },
    { 0x0D, 0x00 },

    { 0x10, 0x04 },
    { 0x11, 0xC2 },
    { 0x12, 0x18 },
    //
);

// ******************************************************************
// * XGSetVertexBufferHeader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGSetVertexBufferHeader,
                         3911)
OOVPA_SIG_MATCH(

    { 0x01, 0x44 },
    { 0x04, 0x8B },

    { 0x07, 0x18 },
    { 0x08, 0xC7 },
    { 0x09, 0x00 },
    { 0x0A, 0x01 },
    { 0x0B, 0x00 },
    { 0x0C, 0x00 },
    { 0x0D, 0x00 },
    { 0x0E, 0x89 },

    { 0x10, 0x04 },
    { 0x11, 0xC2 },
    { 0x12, 0x18 },
    //
);

// ******************************************************************
// * XGSetSurfaceHeader
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(XGSetSurfaceHeader,
                         3911)
OOVPA_SIG_MATCH(
    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov e??, [e?? + param_4]
    OV_MATCH(0x04, 0x8B),
    OV_MATCH(0x06, 0x14),

    // lea e??, [e?? + 0x10]
    OV_MATCH(0x07, 0x8D),
    OV_MATCH(0x09, 0x10),

    // push 0x00
    // push 0x00
    OV_MATCH(0x0F, 0x6A, 0x00, 0x6A, 0x00),
    //
);
