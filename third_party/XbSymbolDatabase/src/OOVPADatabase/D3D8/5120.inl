// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         5120)
OOVPA_SIG_MATCH(

    { 0x0B, 0x57 },
    { 0x10, 0xE8 },

    { 0x15, 0x8B },
    { 0x1F, 0x01 },

    { 0x8D, 0x8B },
    { 0x8E, 0x4E },
    { 0x8F, 0x30 },
    { 0x90, 0x8B },
    { 0x91, 0x11 },
    { 0x92, 0x8B },
    { 0x93, 0x4E },
    { 0x94, 0x2C },
    { 0x95, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         5120)
OOVPA_SIG_MATCH(
    // sub esp, 0x__ (always 0x34)
    OV_MATCH(0x00, 0x83, 0xEC),

    // mov eax, [esp + param_1]
    OV_MATCH(0x03, 0x8B, 0x44, 0x24),

    // movzx ebp, [eax + 0x0D]
    OV_MATCH(0x09, 0x0F, 0xB6, 0x68, 0x0D),
    // mov bl, [ebp + 0x____]
    OV_MATCH(0x0D, 0x8A, 0x9D),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);
