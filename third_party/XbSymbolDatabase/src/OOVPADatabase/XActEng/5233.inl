// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XACT::CEngine::RegisterStreamedWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_RegisterStreamedWaveBank,
                         5233)
OOVPA_SIG_MATCH(

    { 0x04, 0x10 }, //RegisterStreamedWaveBank 0x10 vs RegisterWaveBank 0x14
    { 0x25, 0x8B },

    { 0x3A, 0x2E }, //RegisterStreamedWaveBank 0x2E vs RegisterWaveBank 0x32
    { 0x3B, 0xFF },
    { 0x3C, 0x74 },
    { 0x3D, 0x24 },
    { 0x3E, 0x14 },
    { 0x3F, 0x8B },
    { 0x40, 0xCE },
    { 0x41, 0xE8 },

    { 0x67, 0xEB },
    //
);

// ******************************************************************
// * XACT::CEngine::RegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_RegisterWaveBank,
                         5233)
OOVPA_SIG_MATCH(

    { 0x04, 0x14 }, //RegisterStreamedWaveBank 0x10 vs RegisterWaveBank 0x14
    { 0x1A, 0x3B },

    { 0x3A, 0x32 },
    { 0x3B, 0xFF },
    { 0x3C, 0x74 },
    { 0x3D, 0x24 },
    { 0x3E, 0x18 },
    { 0x3F, 0x8B },
    { 0x40, 0xCE },
    { 0x41, 0xFF },

    { 0x7C, 0xC2 },
    { 0x7D, 0x10 },
    //
);
