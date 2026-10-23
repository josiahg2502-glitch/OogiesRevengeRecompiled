// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XMountUtilityDrive
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XMountUtilityDrive,
                         4134)
OOVPA_SIG_MATCH(

    // XMountUtilityDrive+0x03 : sub esp, 0x0114
    { 0x03, 0x81 },
    { 0x04, 0xEC },
    { 0x05, 0x14 },
    { 0x06, 0x01 },

    // XMountUtilityDrive+0x45 : push 0x0104
    { 0x45, 0x68 },
    { 0x46, 0x04 },
    { 0x47, 0x01 },

    // XMountUtilityDrive+0xAA : lea eax, [ebp-0x10]
    { 0xAA, 0x8D },
    { 0xAB, 0x45 },
    { 0xAC, 0xF0 },
    //
);

// ******************************************************************
// * XSetProcessQuantumLength
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XSetProcessQuantumLength,
                         4134)
OOVPA_SIG_MATCH(

    { 0x01, 0xA1 },
    { 0x04, 0x00 },
    { 0x07, 0x4C },
    { 0x0A, 0x8B },
    { 0x0D, 0x8D },
    { 0x10, 0x89 },
    { 0x13, 0xC2 },
    //
);
