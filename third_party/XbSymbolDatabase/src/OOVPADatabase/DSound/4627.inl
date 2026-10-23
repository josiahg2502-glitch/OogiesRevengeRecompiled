// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CDirectSound::SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetVelocity,
                         4627)
OOVPA_SIG_MATCH(

    // CDirectSound_SetVelocity+0x24 : mov eax, 0x80004005
    { 0x24, 0xB8 },
    { 0x25, 0x05 },
    { 0x26, 0x40 },
    { 0x27, 0x00 },
    { 0x28, 0x80 },

    // CDirectSound_SetVelocity+0x37 : mov [edx+0x44], edi
    { 0x37, 0x89 },
    { 0x38, 0x7A },
    { 0x39, 0x44 },

    // CDirectSound_SetVelocity+0x4C : or byte ptr [eax+0x0x00A4], 0x80
    { 0x4C, 0x80 },
    { 0x4D, 0x88 },
    { 0x4E, 0xA4 },
    { 0x4F, 0x00 },
    { 0x52, 0x80 },

    // CDirectSound_SetVelocity+0x73 : retn 0x14
    { 0x73, 0xC2 },
    { 0x74, 0x14 },
    //
);

// ******************************************************************
// * CMcpxBuffer_Play_Ex
// ******************************************************************
#define CMcpxBuffer_Play_Ex_4627 CMcpxBuffer_Play_Ex_4361

// ******************************************************************
// * CDirectSound::SetDistanceFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDistanceFactor,
                         4627)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDistanceFactor+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSound_SetDistanceFactor+0x33 : mov [eax+68h], edx
    { 0x33, 0x89 },
    { 0x34, 0x50 },
    { 0x35, 0x68 },

    // CDirectSound_SetDistanceFactor+0x36 : mov eax, [ecx+8]
    { 0x36, 0x8B },
    { 0x37, 0x41 },
    { 0x38, 0x08 },

    // CDirectSound_SetDistanceFactor+0x39 : or byte ptr[eax+0xA4], 0xE0
    { 0x39, 0x80 },
    { 0x3A, 0x88 },
    { 0x3B, 0xA4 },
    { 0x3F, 0xE0 },

    // CDirectSound_SetDistanceFactor+0x4F : jz +0x0B
    { 0x4F, 0x74 },
    { 0x50, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::SetDopplerFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDopplerFactor,
                         4627)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDopplerFactor+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSound_SetDopplerFactor+0x33 : mov [eax+0x70], edx
    { 0x33, 0x89 },
    { 0x34, 0x50 },
    { 0x35, 0x70 },

    // CDirectSound_SetDopplerFactor+0x39 : or byte ptr[eax+0xA4], 0x80
    { 0x39, 0x80 },
    { 0x3A, 0x88 },
    { 0x3B, 0xA4 },
    { 0x3F, 0x80 },

    // CDirectSound_SetDopplerFactor+0x4F : jz +0x0B
    { 0x4F, 0x74 },
    { 0x50, 0x0B },
    //
);

// ******************************************************************
// * DirectSound::CMemoryManager::MemAlloc
// ******************************************************************
// * FOR DEBUGGING USE ONLY!
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMemoryManager_MemAlloc,
                         4627)
OOVPA_SIG_MATCH(

    // DirectSound::CMemoryManager::PoolAlloc + 0x1B: cmp [esp+4+0xC], 0
    { 0x1B, 0x83 },
    { 0x1C, 0x7C },
    { 0x1D, 0x24 },
    { 0x1E, 0x10 },
    { 0x1F, 0x00 },
    // DirectSound::CMemoryManager::PoolAlloc + 0x33: and ecx, 3
    { 0x33, 0x83 },
    { 0x34, 0xE1 },
    { 0x35, 0x03 },
    // DirectSound::CMemoryManager::PoolAlloc + 0x65: retn 0xC
    { 0x65, 0xC2 },
    { 0x66, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetDistanceFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetDistanceFactor,
                         4627)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetDistanceFactor+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetDistanceFactor+0x11 : mov [eax+40h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x40 },

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x78 },

    // CDirectSoundVoice_SetDistanceFactor+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetDopplerFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetDopplerFactor,
                         4627)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetDopplerFactor+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetDopplerFactor+0x12 : mov [eax+48h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x48 },

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x78 },

    // CDirectSoundVoice_SetDopplerFactor+0x31 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Commit3dSettings_0,
                         4627)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x42 : cmp edi, 0x02
    { 0x42, 0x83 },
    { 0x43, 0xFF },
    { 0x44, 0x02 },

    // CMcpxVoiceClient::Commit3dSettings+0x68 : mov e__,[e__+0x000000B4]
    { 0x68, 0x8B },
    //{ 0x69, 0x__ },
    { 0x6A, 0xB4 },
    { 0x6B, 0x00 },
    //{ 0x6C, 0x00 },
    { 0x6D, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x77 : mov eax,[eax+0x000000B4]
    { 0x77, 0x8B },
    //{ 0x78, 0x80 },
    { 0x79, 0xB4 },
    { 0x7A, 0x00 },
    //{ 0x7B, 0x00 },
    { 0x7C, 0x00 },

    //
);
