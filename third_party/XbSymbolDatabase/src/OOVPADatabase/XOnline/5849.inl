// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CXo::XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineLogon,
                         5849)
OOVPA_SIG_MATCH(

    { 0x02, 0xEC },

    { 0x10, 0xFC },
    { 0x18, 0xE9 },

    { 0x37, 0xA8 },
    { 0x38, 0x01 },
    { 0x39, 0x75 },
    { 0x3A, 0x0C },
    { 0x3B, 0xC7 },
    { 0x3C, 0x45 },
    { 0x3D, 0x0C },
    { 0x3E, 0x00 },
    { 0x3F, 0x10 },
    { 0x40, 0x15 },
    { 0x41, 0x80 },
    { 0x42, 0xE9 },
    //
);

// ******************************************************************
// * CXo::XOnlineMatchSessionCreate
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineMatchSessionCreate,
                         5849)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // jnz eip + 0x07
    OV_MATCH(0x0D, 0x75, 0x07),

    // jmp eip + 0x5F
    OV_MATCH(0x14, 0xEB, 0x5F),

    // mov byte ptr [ebp - 0x07], bl
    OV_MATCH(0x18, 0x88, 0x5D, 0xF9),

    // jbe eip + 0x12
    OV_MATCH(0x3E, 0x76, 0x12),
    //
);
