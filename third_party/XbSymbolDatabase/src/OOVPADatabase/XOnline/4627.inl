// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XoUpdateLaunchNewImageInternal
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XoUpdateLaunchNewImageInternal_12,
                         4627)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov esi, [ebp + param_1]
    OV_MATCH(0x0B, 0x8B, 0x75, 0x08),

    // mov ebx, [ebp + param_2]
    // cmp ebx, eax
    OV_MATCH(0x19, 0x8B, 0x5D, 0x0C, 0x3B, 0xD8),

    // cmp [ebx], 0x05
    OV_MATCH(0x27, 0x83, 0x3B, 0x05),
    //
);

// ******************************************************************
// * CXo::XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineLogon,
                         4627)
OOVPA_SIG_MATCH(

    { 0x02, 0xEC },

    { 0x17, 0x04 },
    { 0x1E, 0xE8 },

    { 0x3B, 0x8B },
    { 0x3C, 0x4D },
    { 0x3D, 0xFC },
    { 0x3E, 0x68 },
    { 0x3F, 0x58 },
    { 0x40, 0x4F },
    { 0x41, 0x4E },
    { 0x42, 0x73 },
    { 0x43, 0x68 },
    { 0x44, 0x68 },
    //
);
