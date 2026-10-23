// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Discontinuity,
                      4531,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x24, XREF_CMcpxStream_Stop_Ex),

    // CMcpxStream_Discontinuity+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CMcpxStream_Discontinuity+0x12 : mov dx,0x800
    { 0x12, 0x66 },
    { 0x13, 0xBA },
    { 0x14, 0x00 },
    { 0x15, 0x08 },

    // CMcpxStream_Discontinuity+0x23 : call Stop@CMcpxStream@DirectSound@@QAEJ_JK@Z
    { 0x23, 0xE8 },

    // CMcpxStream_Discontinuity+0x2D : pop esi; ret
    { 0x2D, 0x5E },
    { 0x2E, 0xC3 },
    //
);
