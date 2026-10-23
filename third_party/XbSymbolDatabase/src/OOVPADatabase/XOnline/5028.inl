// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CXo::XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineLogon,
                         5028)
OOVPA_SIG_MATCH(

    { 0x02, 0xEC },

    { 0x15, 0x00 },
    { 0x1C, 0xE8 },

    { 0x21, 0xA8 },
    { 0x22, 0x01 },
    { 0x23, 0x75 },
    { 0x24, 0x0C },
    { 0x25, 0xC7 },
    { 0x26, 0x45 },
    { 0x27, 0xF8 },
    { 0x28, 0x00 },
    { 0x29, 0x10 },
    { 0x2A, 0x15 },
    { 0x2B, 0x80 },
    { 0x2C, 0xE9 },
    //
);

// ******************************************************************
// * XoUpdateLaunchNewImageInternal
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XoUpdateLaunchNewImageInternal_16,
                         5028)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov esi, [ebp + param_1]
    OV_MATCH(0x0B, 0x8B, 0x75, 0x08),

    // mov ebx, [ebp + param_2]
    OV_MATCH(0x17, 0x8B, 0x5D, 0x0C),
    // NOTE: offset 0x1A instruction is local variable usage instead of param_4.
    // test ebx, ebx
    OV_MATCH(0x1D, 0x85, 0xDB),

    // NOTE: Do not include instruction of compare to 0x05 byte due to offset change over time.
);
