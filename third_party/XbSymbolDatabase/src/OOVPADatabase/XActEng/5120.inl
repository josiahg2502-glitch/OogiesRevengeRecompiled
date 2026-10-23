// SPDX-License-Identifier: ODbL-1.0

// *****************************************************************
// * XACTEngineCreate
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACTEngineCreate,
                         5120)
OOVPA_SIG_MATCH(

    { 0x11, 0x85 },
    { 0x29, 0xEB },

    { 0x5F, 0x24 },
    { 0x60, 0xFF },
    { 0x61, 0x74 },
    { 0x62, 0x24 },
    { 0x63, 0x10 },
    { 0x64, 0x8B },
    { 0x65, 0xCF },
    { 0x66, 0xE8 },

    { 0xA2, 0xC2 },
    { 0xA3, 0x08 },
    //
);

// ******************************************************************
// * XACT::CEngine::UnRegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_UnRegisterWaveBank,
                         5120)
OOVPA_SIG_MATCH(

    { 0x0E, 0x51 },
    { 0x1F, 0x00 },

    { 0x25, 0x8B },
    { 0x26, 0x7C },
    { 0x27, 0x24 },
    { 0x28, 0x10 },
    { 0x29, 0x83 },
    { 0x2A, 0xC7 },
    { 0x2B, 0x4C },
    { 0x2C, 0x8B },
    { 0x2D, 0x37 },

    { 0x45, 0xF6 },
    { 0x62, 0xC2 },
    //
);

// ******************************************************************
// * XACT::CEngine::RegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_RegisterWaveBank,
                         5120)
OOVPA_SIG_MATCH(

    { 0x04, 0x14 }, //RegisterStreamedWaveBank 0x10 vs RegisterWaveBank 0x14
    { 0x17, 0x3B },

    { 0x37, 0x32 },
    { 0x38, 0xFF },
    { 0x39, 0x74 },
    { 0x3A, 0x24 },
    { 0x3B, 0x18 },
    { 0x3C, 0x8B },
    { 0x3D, 0xCE },
    { 0x3E, 0xFF },

    { 0x79, 0xC2 },
    { 0x7A, 0x10 },
    //
);

// ******************************************************************
// * IXACTEngine_RegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_RegisterWaveBank,
                      5120,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x27, XREF_XACT_CEngine_RegisterWaveBank),

    // IXACTEngine_RegisterWaveBank+0x07 : push [ebp+8+0x10]
    { 0x07, 0xFF },
    { 0x08, 0x74 },
    { 0x09, 0x24 },
    { 0x0A, 0x18 },

    // IXACTEngine_RegisterWaveBank+0x0B : movzx esi, al
    { 0x0B, 0x0F },
    { 0x0C, 0xB6 },
    { 0x0D, 0xF0 },

    // IXACTEngine_RegisterWaveBank+0x40 : retn 0x10
    { 0x40, 0xC2 },
    { 0x41, 0x10 },
    //
);
