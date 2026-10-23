// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * Direct3D_CreateDevice
// ******************************************************************
//00000800A1
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x09, 0xC0 },

    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x08 },
    { 0x15, 0x00 },
    { 0x16, 0xA1 },
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
// Generic OOVPA as of 5120 and newer
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset,
                      5120,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x37, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // jnz +0x??
    OV_MATCH(0x33, 0x75),

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x36, 0xE8),
    // mov e??, [esp + param_1]
    OV_MATCH(0x3B, 0x8B),
    OV_MATCH(0x3D, 0x24, 0x14),
    //
);

// ******************************************************************
// * D3DDevice_SetPalette
// ******************************************************************
//000085C05774258B4E
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPalette,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x11, 0x00 },
    { 0x12, 0x00 },
    { 0x13, 0x85 },
    { 0x14, 0xC0 },
    { 0x15, 0x57 },
    { 0x16, 0x74 },
    { 0x17, 0x25 },
    { 0x18, 0x8B },
    { 0x19, 0x4E },
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         5120)
OOVPA_SIG_MATCH(
    // sub esp, 0x___ (always 0x34)
    OV_MATCH(0x00, 0x83, 0xEC),

    // mov esi, [esp + param_1]
    OV_MATCH(0x06, 0x8B, 0x74, 0x24),
    // movzx ebp, [esi + 0x0D]
    OV_MATCH(0x0A, 0x0F, 0xB6, 0x6E, 0x0D),
    // mov bl, [ebp + 0x____]
    OV_MATCH(0x0E, 0x8A, 0x9D),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
// Test case:
// Freaky Flyers (5455)
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         5121)
OOVPA_SIG_MATCH(
    // sub esp, 0x___ (always 0x34)
    OV_MATCH(0x00, 0x83, 0xEC),

    // mov esi, [esp + param_1]
    OV_MATCH(0x06, 0x8B, 0x74, 0x24),
    // movzx ebp, [esi + 0x0D]
    OV_MATCH(0x0A, 0x0F, 0xB6, 0x6E, 0x0D),
    // movzx eax, [ebp + 0x____]
    OV_MATCH(0x0E, 0x0F, 0xB6, 0x85),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);
