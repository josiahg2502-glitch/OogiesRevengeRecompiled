// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CDirectSoundStream_Flush
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Flush,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CDirectSoundStream_Flush+0x31 : call [CMcpxStream_Flush]
    XREF_ENTRY(0x32, XREF_CMcpxStream_Flush),

    { 0x00, 0x56 },

    { 0x28, 0x8B },
    { 0x2B, 0x08 },

    { 0x2C, 0x8B },
    { 0x2E, 0x24 },

    { 0x31, 0xE8 },

    //CDirectSoundStream_Flush+0x48 : ret 4
    { 0x48, 0xC2 },
    { 0x49, 0x04 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_GetVoiceProperties
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_GetVoiceProperties,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x03, 0x83 },
    { 0x06, 0x83 },
    { 0x0A, 0xF6 },

    // CMcpxVoiceClient_GetVoiceProperties+0xB5 : shr esi,6
    { 0xB5, 0xC1 },
    { 0xB6, 0xEE },
    { 0xB7, 0x06 },

    // CMcpxVoiceClient_GetVoiceProperties+0x102 : mov dword ptr [edi],0FFFFD8F0h
    { 0x102, 0xC7 },
    { 0x103, 0x07 },
    { 0x104, 0xF0 },
    { 0x105, 0xD8 },
    { 0x106, 0xFF },
    { 0x107, 0xFF },

    // After offset 0x11C, lots of changes has occurred.
    //
);

// ******************************************************************
// * CDirectSoundVoice_GetVoiceProperties
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_GetVoiceProperties,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_CMcpxVoiceClient_GetVoiceProperties),

    { 0x00, 0x8B },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x08, 0x8B },
    { 0x0B, 0xE8 },
    { 0x10, 0xC2 },
    { 0x11, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetVoiceProperties
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetVoiceProperties,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_GetVoiceProperties),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x2C, 0x10 },
    { 0x30, 0x10 },
    { 0x31, 0xE8 },
    { 0x4B, 0xC2 },
    { 0x4C, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_GetVoiceProperties
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_GetVoiceProperties,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_GetVoiceProperties),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0x83 },
    { 0x0E, 0xD9 },
    { 0x12, 0xC8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_GetVoiceProperties
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_GetVoiceProperties,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_GetVoiceProperties),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x2B, 0x08 },
    { 0x30, 0x10 },
    { 0x35, 0xE8 },
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_GetVoiceProperties
// ******************************************************************
// Generic OOVPA as of 5028 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_GetVoiceProperties,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_GetVoiceProperties+0x00 : jmp [CDirectSoundStream_GetVoiceProperties]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_GetVoiceProperties),

    // IDirectSoundStream_GetVoiceProperties+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Commit3dSettings_0,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x3F : cmp edi, 0x02
    OV_MATCH(0x3F, 0x83, 0xFF, 0x02),

    // CMcpxVoiceClient::Commit3dSettings+0x61 : mov e__,[e__+0x000000B4]
    OV_MATCH(0x61, 0x8B),
    //OV_MATCH(0x62, 0x__),
    OV_MATCH(0x63, 0xB4, 0x00),
    //OV_MATCH(0x65, 0x00),
    OV_MATCH(0x66, 0x00),

    // CMcpxVoiceClient::Commit3dSettings+0x70 : mov eax,[eax+0x000000B4]
    OV_MATCH(0x70, 0x8B),
    //OV_MATCH(0x71, 0x80),
    OV_MATCH(0x72, 0xB4, 0x00),
    //OV_MATCH(0x74, 0x00),
    OV_MATCH(0x75, 0x00),

    //
);

// ******************************************************************
// * CMcpxStream::Stop
// ******************************************************************
// Generic OOVPA as of 5028 and newer;
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Stop,
                         5028)
OOVPA_SIG_MATCH(

    // calls to CIrql_Raise, CIrql_Lower, CMcpxVoiceClient_ReleaseVoice, CMcpxVoiceClient_DeactivateVoice

    // CMcpxStream_Stop+0x00 : push ebp; mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // Offset is unique for this asm code.
    // CMcpxStream_Stop+0x1F : test [ebp+8],6
    OV_MATCH(0x1F, 0xF6, 0x45, 0x08, 0x06),
    //
);

// ******************************************************************
// * XAudioSetEffectData
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XAudioSetEffectData,
                      5028,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // XAudioSetEffectData+0x79 : call [CDirectSound::GetEffectData]
    XREF_ENTRY(0x07A, XREF_CDirectSound_GetEffectData),

    // XAudioSetEffectData+0xD0 : call [CDirectSound::SetEffectData]
    XREF_ENTRY(0x0D1, XREF_CDirectSound_SetEffectData),

    OV_MATCH(0x00, 0x55, 0x8B),
    OV_MATCH(0x03, 0x81),
    //
);
