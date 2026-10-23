// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CXo::XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineLogon,
                         4361)
OOVPA_SIG_MATCH(

    { 0x02, 0xEC },

    { 0x0D, 0xFC },
    { 0x0E, 0x75 },
    { 0x0F, 0x07 },
    { 0x10, 0xB8 },
    { 0x11, 0x05 },
    { 0x12, 0x00 },
    { 0x13, 0x15 },
    { 0x14, 0x80 },
    { 0x15, 0xEB },

    { 0x24, 0xA8 },
    { 0x32, 0x33 },
    //
);

// ******************************************************************
// * XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XOnlineLogon,
                      4361,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_CXo_XOnlineLogon),

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x0A, 0xE9 },
    //
);
