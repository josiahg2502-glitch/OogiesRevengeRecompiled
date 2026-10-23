// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XACTEngineCreate
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACTEngineCreate,
                         4928)
OOVPA_SIG_MATCH(

    // XACTEngineCreate+0x09 : movzx ebx, al
    { 0x09, 0x0F },
    { 0x0A, 0xB6 },
    { 0x0B, 0xD8 },

    // XACTEngineCreate+0x2B : push edi
    { 0x2B, 0x57 },

    // XACTEngineCreate+0x2C : push 0x120
    { 0x2C, 0x68 },
    { 0x2D, 0x20 },
    { 0x2E, 0x01 },
    { 0x2F, 0x00 },
    { 0x30, 0x00 },

    // XACTEngineCreate+0x9E : retn 0x8
    { 0x9E, 0xC2 },
    { 0x9F, 0x08 },
    //
);

// ******************************************************************
// * XACT::CEngine::RegisterStreamedWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_RegisterStreamedWaveBank,
                         4928)
OOVPA_SIG_MATCH(

    { 0x04, 0x10 }, //RegisterStreamedWaveBank 0x10 vs RegisterWaveBank 0x14
    { 0x22, 0x8B },

    { 0x37, 0x2E }, //RegisterStreamedWaveBank 0x2E vs RegisterWaveBank 0x32
    { 0x38, 0xFF },
    { 0x39, 0x74 },
    { 0x3A, 0x24 },
    { 0x3B, 0x14 },
    { 0x3C, 0x8B },
    { 0x3D, 0xCE },
    { 0x3E, 0xE8 },

    { 0x64, 0xEB },
    //
);

// ******************************************************************
// * IXACTEngine_RegisterStreamedWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_RegisterStreamedWaveBank,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IXACTEngine_RegisterStreamedWaveBank+0x22 : call XACT::CEngine::RegisterStreamedWaveBank
    XREF_ENTRY(0x23, XREF_XACT_CEngine_RegisterStreamedWaveBank),

    // IXACTEngine_RegisterStreamedWaveBank+0x0B : movzx esi, al
    { 0x0B, 0x0F },
    { 0x0C, 0xB6 },
    { 0x0D, 0xF0 },
    // IXACTEngine_RegisterStreamedWaveBank+0x0E : mov eax, [esp+0x0C+4]
    { 0x0E, 0x8B },
    { 0x0F, 0x44 },
    { 0x10, 0x24 },
    { 0x11, 0x10 },
    // IXACTEngine_RegisterStreamedWaveBank+0x3C : retn 0x0C
    { 0x3C, 0xC2 },
    { 0x3D, 0x0C },
    //
);

// ******************************************************************
// * XACT::CEngine::CreateSoundBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_CreateSoundBank,
                         4928)
OOVPA_SIG_MATCH(

    { 0x0E, 0x85 },
    { 0x1F, 0x8B },
    { 0x42, 0x8B },

    { 0x50, 0xC1 },
    { 0x51, 0x4C },
    { 0x52, 0x89 },
    { 0x53, 0x08 },
    { 0x54, 0x8B },
    { 0x55, 0x49 },
    { 0x56, 0x04 },
    { 0x57, 0x89 },
    //
);

// ******************************************************************
// * IXACTEngine_CreateSoundBank
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_CreateSoundBank,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x27, XREF_XACT_CEngine_CreateSoundBank),

    // IXACTEngine_CreateSoundBank+0x07 : push [ebp+8+0x10]
    { 0x07, 0xFF },
    { 0x08, 0x74 },
    { 0x09, 0x24 },
    { 0x0A, 0x18 },
    // IXACTEngine_CreateSoundBank+0x0B : movzx esi, al
    { 0x0B, 0x0F },
    { 0x0C, 0xB6 },
    { 0x0D, 0xF0 },
    // IXACTEngine_CreateSoundBank+0x40 : retn 0x10
    { 0x40, 0xC2 },
    { 0x41, 0x10 },
    //
);

// ******************************************************************
// * XACT::CEngine::UnRegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_UnRegisterWaveBank,
                         4928)
OOVPA_SIG_MATCH(

    // XACT_CEngine_UnRegisterWaveBank+0x06 : lea eax, [ecx+0x58]
    { 0x06, 0x8D },
    { 0x07, 0x41 },
    { 0x08, 0x58 },
    // XACT_CEngine_UnRegisterWaveBank+0x28 : lea edi, [ebx+0x4C]
    { 0x28, 0x8D },
    { 0x29, 0x7B },
    { 0x2A, 0x4C },
    // XACT_CEngine_UnRegisterWaveBank+0xBF : retn 0x8
    { 0xBF, 0xC2 },
    { 0xC0, 0x08 },
    //
);

// ******************************************************************
// * IXACTEngine_UnRegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_UnRegisterWaveBank,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IXACTEngine_UnRegisterWaveBank+0x1E : call XACT::CEngine::UnRegisterWaveBank
    XREF_ENTRY(0x1F, XREF_XACT_CEngine_UnRegisterWaveBank),

    { 0x07, 0xFF },
    { 0x0E, 0x8B },
    { 0x16, 0xF8 },
    { 0x1E, 0xE8 },
    { 0x26, 0xF8 },
    { 0x2E, 0xFF },
    { 0x36, 0x5F },
    //
);

// ******************************************************************
// * XACT::CEngine::CreateSoundSource
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_CreateSoundSource,
                         4928)
OOVPA_SIG_MATCH(

    { 0x0A, 0x8B },
    { 0x15, 0xE8 },

    { 0x2C, 0x05 },
    { 0x2D, 0x8B },
    { 0x2E, 0x4D },
    { 0x2F, 0x10 },
    { 0x30, 0x89 },
    { 0x31, 0x31 },
    { 0x32, 0x5E },
    { 0x33, 0x5D },
    { 0x34, 0xC2 },
    //
);

// ******************************************************************
// * IXACTEngine_CreateSoundSource
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_CreateSoundSource,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x23, XREF_XACT_CEngine_CreateSoundSource),

    { 0x02, 0xE8 },
    { 0x09, 0x24 },
    { 0x12, 0xFF },
    { 0x18, 0x83 },
    { 0x1C, 0xD9 },
    { 0x20, 0xC8 },
    { 0x3C, 0xC2 },
    { 0x3D, 0x0C },
    //
);

// ******************************************************************
// * IXACTEngine_GetNotification
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_GetNotification,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x23, XREF_XACT_CEngine_GetNotification),

    { 0x02, 0xE8 },
    { 0x09, 0x24 },
    { 0x12, 0xFF },
    { 0x18, 0x83 },
    { 0x1C, 0xD9 },
    { 0x20, 0xC8 },
    { 0x3C, 0xC2 },
    { 0x3D, 0x0C },
    //
);

// ******************************************************************
// * XACT::CSoundBank::GetSoundCueIndexFromFriendlyName
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CSoundBank_GetSoundCueIndexFromFriendlyName,
                         4928)
OOVPA_SIG_MATCH(

    { 0x03, 0x51 },
    { 0x1F, 0x80 },

    { 0x30, 0x8D },
    { 0x31, 0x3C },
    { 0x32, 0xC1 },
    { 0x33, 0x85 },
    { 0x34, 0xFF },
    { 0x35, 0x74 },
    { 0x36, 0x4D },
    { 0x37, 0x53 },
    { 0x38, 0x8B },

    { 0x4A, 0x03 },
    { 0x5F, 0xE8 },
    //
);

// ******************************************************************
// * IXACTSoundBank_GetSoundCueIndexFromFriendlyName
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTSoundBank_GetSoundCueIndexFromFriendlyName,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x17, XREF_XACT_CSoundBank_GetSoundCueIndexFromFriendlyName),

    { 0x02, 0xE8 },
    { 0x09, 0x24 },
    { 0x12, 0xFF },
    { 0x16, 0xE8 },
    { 0x1B, 0x85 },
    { 0x2C, 0x8B },
    { 0x30, 0xC2 },
    { 0x31, 0x0C },
    //
);

// ******************************************************************
// * IXACTEngine_RegisterNotification
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IXACTEngine_RegisterNotification,
                      4928,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_XACT_CEngine_RegisterNotification),

    { 0x02, 0xE8 },
    { 0x09, 0x24 },
    { 0x14, 0x83 },
    { 0x18, 0xD9 },
    { 0x1C, 0xC8 },
    { 0x38, 0xC2 },
    { 0x39, 0x08 },
    //
);
