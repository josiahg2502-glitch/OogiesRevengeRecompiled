// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CDirectSound::CommitDeferredSettings
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_XREF(CDirectSound_CommitDeferredSettings,
                      5455,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSound_CommitDeferredSettings+0x45 : call [CDirectSound3DCalculator::Calculate3D]
    XREF_ENTRY(0x46, XREF_CDirectSound3DCalculator_Calculate3D),

    // CDirectSound_CommitDeferredSettings+0x5D : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x5E, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSound_CommitDeferredSettings+0x00 : push ebp; mov ebp,esp
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },

    // CDirectSound_CommitDeferredSettings+0x27 : mov eax, 0x80004005
    { 0x27, 0xB8 },
    { 0x28, 0x05 },
    { 0x29, 0x40 },
    { 0x2B, 0x80 },

    // CDirectSound_CommitDeferredSettings+0x96 : leave
    { 0x96, 0xC9 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSound::EnableHeadphones
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_EnableHeadphones,
                         5455)
OOVPA_SIG_MATCH(

    // CDirectSound_EnableHeadphones+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_EnableHeadphones+0x16 : movzx eax, al
    { 0x16, 0x0F },
    { 0x17, 0xB6 },
    { 0x18, 0xC0 },

    // CDirectSound_EnableHeadphones+0x3E : shr e__, 0x1F
    { 0x3E, 0xC1 },
    //{ 0x3F, 0xE8 }, // 5344 0xEA vs 5455 0xE8
    { 0x40, 0x1F },

    // CDirectSound_EnableHeadphones+0x53 : mov edi, 0x80000000
    { 0x53, 0xBF },
    { 0x54, 0x00 },
    { 0x55, 0x00 },
    { 0x56, 0x00 },
    { 0x57, 0x80 },

    // CDirectSound_EnableHeadphones+0xC4 : cmp dword ptr [ebp+0x0C],0
    { 0xC4, 0x83 },
    { 0xC5, 0x7D },
    { 0xC6, 0x0C },
    { 0xC7, 0x00 },

    // CDirectSound_EnableHeadphones+0x117 : leave; ret 8
    //{ 0x117, 0xC9 },
    { 0x118, 0xC2 },
    { 0x119, 0x08 },
    //
);

// ******************************************************************
// * DSound_CRefCount_Release
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_NO_XREF(DSound_CRefCount_Release,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    // DSound_CRefCount_Release+0x0B : dec eax
    { 0x0B, 0x48 },

    // DSound_CRefCount_Release+0x0E : mov dword ptr [ecx+4], eax
    { 0x0C, 0x89 },
    { 0x0D, 0x41 },
    { 0x0E, 0x04 },

    // DSound_CRefCount_Release+0x1D : mov, dword ptr [ecx+4]
    { 0x1B, 0x8B },
    { 0x1C, 0x41 },
    { 0x1D, 0x04 },

    // DSound_CRefCount_Release+0x20 : retn 0x04
    { 0x1E, 0xC2 },
    { 0x1F, 0x04 },
    //
);

// ******************************************************************
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Discontinuity,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x22, XREF_CMcpxStream_Stop),

    // CMcpxStream_Discontinuity+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CMcpxStream_Discontinuity+0x12 : mov dx,0x800
    { 0x12, 0x66 },
    { 0x13, 0xBA },
    { 0x14, 0x00 },
    { 0x15, 0x08 },

    // CMcpxStream_Discontinuity+0x21 : call Stop@CMcpxStream@DirectSound@@QAEJK@Z
    { 0x21, 0xE8 },

    // CMcpxStream_Discontinuity+0x2B : pop esi; ret
    { 0x2B, 0x5E },
    { 0x2C, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSound_GetSpeakerConfig
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetSpeakerConfig,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0xE8 },

    { 0x0B, 0x00 },
    { 0x14, 0x0B },
    { 0x20, 0xB8 },
    { 0x30, 0x08 },

    { 0x31, 0x81 },
    //{ 0x32, 0xE1 }, (This value has changed, commented out for generic support.)
    { 0x33, 0xFF },
    { 0x34, 0xFF },
    { 0x35, 0xFF },
    { 0x36, 0x7F },

    { 0x3C, 0x0B },

    { 0x48, 0x33 },

    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_Set3DVoiceData,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x04, 0x8B },

    { 0x28, 0x01 },
    { 0x3C, 0x02 },
    { 0x50, 0x04 },
    { 0x73, 0x08 },
    { 0x96, 0x10 },
    { 0xB9, 0x20 },
    { 0xCD, 0x40 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundBuffer::Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Set3DVoiceData,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_Set3DVoiceData),

    { 0x00, 0x56 },
    { 0x11, 0x16 },
    { 0x16, 0x68 },
    { 0x36, 0x85 },
    { 0x3A, 0x74 },
    { 0x3C, 0x68 },
    { 0x4B, 0xC2 },
    { 0x4C, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer::Set3DVoiceData
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_Set3DVoiceData,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_Set3DVoiceData),

    { 0x06, 0x24 },
    { 0x08, 0x8B },
    { 0x0C, 0xE4 },
    { 0x0E, 0xD9 },
    { 0x11, 0x23 },
    { 0x14, 0xE8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Set3DVoiceData,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_Set3DVoiceData),

    { 0x00, 0x56 },
    { 0x11, 0x16 },
    { 0x16, 0x68 },
    { 0x35, 0xE8 },
    { 0x3E, 0x74 },
    { 0x40, 0x68 },
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer (note: is not introduced in 5344)
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_Set3DVoiceData,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_Set3DVoiceData+0x00 : jmp [CDirectSoundStream_Set3DVoiceData]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_Set3DVoiceData),

    // IDirectSoundStream_Set3DVoiceData+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * XAudioCalculatePitch
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_NO_XREF(XAudioCalculatePitch,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // XAudioCalculatePitch+0x0F : cmp eax, 0xBB80
    { 0x0F, 0x3D },
    { 0x10, 0x80 },
    { 0x11, 0xBB },
    { 0x12, 0x00 },

    // XAudioCalculatePitch+0x18 : jmp +0x21
    { 0x18, 0xEB },
    { 0x19, 0x21 },

    // XAudioCalculatePitch+0x3B : lea ecx, [ebp+08]
    { 0x3B, 0x8D },
    { 0x3C, 0x4D },
    { 0x3D, 0x08 },

    // XAudioCalculatePitch+0x47 : retn 0x04
    { 0x47, 0xC2 },
    { 0x48, 0x04 },
    //
);

// ******************************************************************
// * DirectSound::CMcpxAPU::ServiceDeferredCommandsLow
// ******************************************************************
// Generic OOVPA as of 5455 and newer; whole asm had not been changed since.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_ServiceDeferredCommandsLow,
                         5455)
OOVPA_SIG_MATCH(

    // CMcpxAPU_ServiceDeferredCommandsLow+0x00: push ebp; mov ebp,esp
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },

    // CMcpxAPU_ServiceDeferredCommandsLow+0x11: lea ecx,[ebp-10]
    { 0x11, 0x8D },
    { 0x12, 0x4D },
    { 0x13, 0xF0 },

    // CMcpxAPU_ServiceDeferredCommandsLow+0x17: mov [ebp-08],eax
    { 0x17, 0x89 },
    { 0x18, 0x45 },
    { 0x19, 0xF8 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_Commit3dSettings_0,
                      5455,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient::Commit3dSettings+0x2B : call [CDirectSound3DCalculator::Calculate3D]
    XREF_ENTRY(0x2C, XREF_CDirectSound3DCalculator_Calculate3D),

    // CMcpxVoiceClient::Commit3dSettings+0x55 : call [CDirectSound3DCalculator::GetVoiceData]
    XREF_ENTRY(0x56, XREF_CDirectSound3DCalculator_GetVoiceData),

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x5D : mov e__,[e__+0x000000B4]
    { 0x5D, 0x8B },
    //{ 0x5E, 0x__ },
    { 0x5F, 0xB4 },
    { 0x60, 0x00 },
    //{ 0x61, 0x00 },
    { 0x62, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x69 : mov eax,[eax+0x000000B4]
    { 0x69, 0x8B },
    //{ 0x6A, 0x80 },
    { 0x6B, 0xB4 },
    { 0x6C, 0x00 },
    //{ 0x6D, 0x00 },
    { 0x6E, 0x00 },

    //
);
