// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XnInit
// ******************************************************************
//Generic OOVPA as of 4361 and newer.
OOVPA_SIG_HEADER_NO_XREF(XnInit_24,
                         4361)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0F, 0xB9 },

    { 0x14, 0xBA },
    { 0x15, 0x01 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x00 },

    { 0x19, 0x0F },
    { 0x1A, 0xB1 },
    { 0x1B, 0x11 },

    { 0x1C, 0x33 },
    //{ 0x1D, 0xF6 },
    { 0x1E, 0x3B },
    //{ 0x1F, 0xC6 },

    { 0x23, 0xE8 },
    { 0x28, 0xEB },
    { 0x3F, 0x54 },
    //
);

// ******************************************************************
// * WSAStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(WSAStartup,
                      4361,
                      XRefOne)
OOVPA_SIG_MATCH(

    // WSAStartup+0x0F : call [XnInit]
    XREF_ENTRY(0x14, XREF_XnInit),

    // WSAStartup+0x00 : push [esp+0x08]
    { 0x00, 0xFF },
    { 0x01, 0x74 },
    { 0x02, 0x24 },
    { 0x03, 0x08 },

    // WSAStartup+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },
    //
);

// ******************************************************************
// * XNetStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XNetStartup,
                      4361,
                      XRefOne)
OOVPA_SIG_MATCH(

    // XNetStartup+0x0F : call [XnInit]
    XREF_ENTRY(0x10, XREF_XnInit),

    // XNetStartup+0x00 : xor eax, eax
    { 0x00, 0x33 },
    { 0x01, 0xC0 },

    // XNetStartup+0x02 : push eax
    { 0x02, 0x50 },

    // XNetStartup+0x03 : push eax
    { 0x03, 0x50 },

    // XNetStartup+0x04 : push eax
    { 0x04, 0x50 },

    // XNetStartup+0x14 : retn 0x04
    { 0x14, 0xC2 },
    { 0x15, 0x04 },
    //
);
