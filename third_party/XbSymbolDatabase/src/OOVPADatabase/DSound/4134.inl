// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * DirectSoundCreate
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(DirectSoundCreate,
                         4134)
OOVPA_SIG_MATCH(

    // DirectSoundCreate+0x0B : movzx esi, al
    { 0x0B, 0x0F },
    { 0x0C, 0xB6 },
    { 0x0D, 0xF0 },

    // DirectSoundCreate+0x12 : call [addr]
    { 0x12, 0xE8 },

    // DirectSoundCreate+0x1B : jl +0x13
    { 0x1B, 0x7C },
    { 0x1C, 0x13 },

    // DirectSoundCreate+0x27 : sbb ecx, ecx
    { 0x27, 0x1B },
    { 0x28, 0xC9 },

    // DirectSoundCreate+0x43 : leave
    { 0x43, 0xC9 },
    //
);

// ******************************************************************
// * DirectSoundDoWork
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(DirectSoundDoWork,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundDoWork+0x13 : call [CDirectSound::DoWork]
    XREF_ENTRY(0x14, XREF_CDirectSound_DoWork),

    { 0x00, 0x56 },

    { 0x06, 0x0F },
    { 0x07, 0xB6 },
    { 0x08, 0xF0 },
    { 0x09, 0xA1 },

    { 0x0E, 0x85 },
    { 0x10, 0x74 },
    { 0x18, 0x85 },
    { 0x1C, 0x0B },
    { 0x22, 0xFF },
    { 0x28, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSound::CreateSoundBuffer
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CreateSoundBuffer,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_CreateSoundBuffer+0x23 : mov eax, 0x80004005
    { 0x23, 0xB8 },
    { 0x24, 0x05 },
    { 0x25, 0x40 },
    { 0x27, 0x80 },

    // CDirectSound_CreateSoundBuffer+0x2A : push 0x24
    { 0x2A, 0x6A },
    { 0x2B, 0x24 },

    // CDirectSound_CreateSoundBuffer+0x4A : add esi, 0x7FF8FFF2
    { 0x4A, 0x81 },
    { 0x4B, 0xE6 },
    { 0x4C, 0xF2 },
    { 0x4D, 0xFF },
    { 0x4E, 0xF8 },
    { 0x4F, 0x7F },

    // CDirectSound_CreateSoundBuffer+0x99 : retn 0x10
    { 0x99, 0xC2 },
    { 0x9A, 0x10 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetLoopRegion
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetLoopRegion,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetLoopRegion+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetLoopRegion+0x24 : mov eax, 0x80004005
    { 0x24, 0xB8 },
    { 0x25, 0x05 },
    { 0x26, 0x40 },
    { 0x27, 0x00 },
    { 0x28, 0x80 },

    // CDirectSoundBuffer_SetLoopRegion+0x29 : jmp +0x55
    { 0x29, 0xEB },
    { 0x2A, 0x55 },

    // CDirectSoundBuffer_SetLoopRegion+0x56 : sub ecx, esi
    { 0x56, 0x2B },
    { 0x57, 0xCE },

    // CDirectSoundBuffer_SetLoopRegion+0x82 : retn 0x0C
    { 0x82, 0xC2 },
    { 0x83, 0x0C },
    //
);

// ******************************************************************
// * CDirectSound::SetI3DL2Listener
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetI3DL2Listener,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_SetI3DL2Listener+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CDirectSound_SetI3DL2Listener+0x34 : mov __x,[eax+0x08]
    { 0x31, 0x8B },
    //{ 0x32, 0x }, // change over time
    { 0x33, 0x08 },

    // CDirectSound_SetI3DL2Listener+0x34 : cmp [__x+0xXX],-1
    { 0x34, 0x83 },
    //{ 0x35, 0x }, // change over time
    //{ 0x36, 0x }, // change over time
    { 0x37, 0xFF },

    // CDirectSound_SetI3DL2Listener+0x38 : jne +0x0A
    { 0x38, 0x75 },
    { 0x39, 0x0A },

    // Offset is unique for this asm code.
    // CDirectSound_SetI3DL2Listener+0x3A : mov edi, 0x88780032 (unchanged since 3911)
    { 0x3A, 0xBF },
    { 0x3B, 0x32 },
    { 0x3C, 0x00 },
    { 0x3D, 0x78 },
    { 0x3E, 0x88 },

    // After offset 0x44, asm code does shift around in 5344 and 5455.

    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetHeadroom
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetHeadroom,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetHeadroom),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x12, 0x85 },
    { 0x1C, 0x15 },
    { 0x26, 0xEB },
    { 0x30, 0x10 },
    { 0x3A, 0x74 },
    { 0x47, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMixBins
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSoundBuffer_SetMixBins, 4134, 1 + 12, XRefOne)
    {

        // CDirectSoundBuffer_SetMixBins+0x32 : call [CDirectSoundVoice::SetMixBins]
        XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetMixBins),

            // CDirectSoundBuffer_SetMixBins+0x00 : push esi
            { 0x00, 0x56 },

#if 0
        // CDirectSoundBuffer_SetMixBins+0x21 : mov eax, 0x80004005
        { 0x21, 0xB8 },
        { 0x22, 0x05 },
        { 0x23, 0x40 },
        { 0x24, 0x00 },
        { 0x25, 0x80 },
#endif

            // CDirectSoundBuffer_SetMixBins+0x29 : push [esp+0x10]; push [esp+0x10]
            { 0x29, 0xFF },
            { 0x2A, 0x74 },
            { 0x2B, 0x24 },
            { 0x2C, 0x10 },
            { 0x2D, 0xFF },
            { 0x2E, 0x74 },
            { 0x2F, 0x24 },
            { 0x30, 0x10 },

            // CDirectSoundBuffer_SetMixBins+0x49 : pop edi
            { 0x49, 0x5F },

            // CDirectSoundBuffer_SetMixBins+0x4B : retn 0x08
            { 0x4B, 0xC2 },
            { 0x4C, 0x08 },
    }
OOVPA_END;

// ******************************************************************
// * CDirectSound_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetPosition,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_SetPosition+0x00 : push ebp; mov ebp, esp
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },

    // CDirectSound_SetPosition+0x2B : mov ecx, [ebp+0x08]
    { 0x2B, 0x8B },
    { 0x2C, 0x4D },
    { 0x2D, 0x08 },

    // CDirectSound_SetPosition+0x37 : mov [edx+0x38],edi
    { 0x37, 0x89 },
    { 0x38, 0x7A },
    { 0x39, 0x38 },

    // CDirectSound_SetPosition+0x3F : mov [edx+0x3C],edi
    { 0x3F, 0x89 },
    { 0x40, 0x7A },
    { 0x41, 0x3C },

    // CDirectSound_SetPosition+0x47 : mov [edx+0x40],edi
    { 0x47, 0x89 },
    { 0x48, 0x7A },
    { 0x49, 0x40 },

    // After offset 0x4A, asm code does change in 4627 and later.

    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetFrequency
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSoundBuffer_SetFrequency, 4134, 1 + 12, XRefOne)
    {

        // CDirectSoundBuffer_SetFrequency+0x32 : call [CDirectSoundVoice::SetFrequency]
        XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetFrequency),

            // CDirectSoundBuffer_SetFrequency+0x00 : push esi
            { 0x00, 0x56 },

#if 0
        // CDirectSoundBuffer_SetFrequency+0x21 : mov eax, 0x80004005
        { 0x21, 0xB8 },
        { 0x22, 0x05 },
        { 0x23, 0x40 },
        { 0x24, 0x00 },
        { 0x25, 0x80 },
#endif

            // CDirectSoundBuffer_SetFrequency+0x29 : push [esp+0x10]; push [esp+0x10]
            { 0x29, 0xFF },
            { 0x2A, 0x74 },
            { 0x2B, 0x24 },
            { 0x2C, 0x10 },
            { 0x2D, 0xFF },
            { 0x2E, 0x74 },
            { 0x2F, 0x24 },
            { 0x30, 0x10 },

            // CDirectSoundBuffer_SetFrequency+0x49 : pop edi
            { 0x49, 0x5F },

            // CDirectSoundBuffer_SetFrequency+0x4B : retn 0x08
            { 0x4B, 0xC2 },
            { 0x4C, 0x08 },
    }
OOVPA_END;

// ******************************************************************
// * CMcpxVoiceClient_SetVolume
// ******************************************************************
// Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetVolume,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetVolume+0x2A : lea eax, [ecx+ecx*2]
    { 0x2A, 0x8D },
    { 0x2B, 0x04 },
    { 0x2C, 0x49 },

    // CMcpxVoiceClient_SetVolume+0x45 : movzx edx, word ptr [ecx]
    { 0x45, 0x0F },
    { 0x46, 0xB7 },
    { 0x47, 0x11 },

    // CMcpxVoiceClient_SetVolume+0x6C : mov edx, [ebp+eax*4-0x14]
    { 0x6C, 0x8B },
    { 0x6D, 0x54 },
    { 0x6E, 0x85 },
    { 0x6F, 0xEC },

    // CMcpxVoiceClient_SetVolume+0x84 : inc eax; inc ecx, inc ecx
    { 0x84, 0x40 },
    { 0x85, 0x41 },
    { 0x86, 0x41 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetVolume
// ******************************************************************
// Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetVolume,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetVolume+0x15 : call [CMcpxVoiceClient::SetVolume]
    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetVolume),

    // CDirectSoundVoice_SetVolume+0x00 : mov ecx, [esp+0x04]
    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // CDirectSoundVoice_SetVolume+0x0B : sub edx, [eax+0x20]
    { 0x0B, 0x2B },
    { 0x0C, 0x50 },
    { 0x0D, 0x20 },

    // CDirectSoundVoice_SetVolume+0x11 : mov ecx, [ecx+0x0C]
    { 0x11, 0x8B },
    { 0x12, 0x49 },
    { 0x13, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVolume
// ******************************************************************
// Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetVolume,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetVolume),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Lock
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Lock,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x48, XREF_CDirectSoundBuffer_GetCurrentPosition),

    { 0x00, 0x55 },

    // CDirectSoundBuffer_Lock+0x37 : test [ebp+0x24], 1
    { 0x37, 0xF6 },
    { 0x38, 0x45 },
    { 0x39, 0x24 },
    { 0x3A, 0x01 },

    // CDirectSoundBuffer_Lock+0x5C : test byte ptr [ebp+24h],2
    { 0x53, 0xF6 },
    { 0x54, 0x45 },
    { 0x55, 0x24 },
    { 0x56, 0x02 },

    // CDirectSoundBuffer_Lock+0x81 : sub ecx,dword ptr [ebp+0Ch]
    { 0x81, 0x2B },
    { 0x82, 0x4D },
    { 0x83, 0x0C },

    // Major changes occur at 0x84 and later
    //
);

// ******************************************************************
// * CDirectSoundBufferSettings::SetBufferData
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_NO_XREF(CDirectSoundBufferSettings_SetBufferData, 4134, 12)
    {

        // CDirectSoundBufferSettings::SetBufferData+0x00 : push ebp
        { 0x00, 0x55 },

            // CDirectSoundBufferSettings::SetBufferData+0x0B : mov edi,0x80000000
            { 0x0B, 0xBF },
            { 0x0C, 0x00 },
            //{ 0x0D, 0x00 },
            { 0x0E, 0x00 },
            { 0x0F, 0x80 },

            // CDirectSoundBufferSettings::SetBufferData+0x20 : jz +0x0C
            { 0x20, 0x74 },
            { 0x21, 0x0C },

#if 0
        // CDirectSoundBufferSettings::SetBufferData+0x45 : mov [esi+0xB8], ecx
        { 0x45, 0x89 },
        { 0x46, 0x8E },
        //{ 0x47, 0xB8 }, // 4134 0xB8 vs 5455 0xBC
#endif

            // This offset is unique.
            // CDirectSoundBufferSettings::SetBufferData+0x4D : and byte [esi+0x0B],0x7F
            { 0x4D, 0x80 },
            { 0x4E, 0x66 },
            //{ 0x4F, 0x0B },
            { 0x50, 0x7F },

            // CDirectSoundBufferSettings::SetBufferData+0x89 : ret 8
            { 0x89, 0xC2 },
            { 0x8A, 0x08 },
    }
OOVPA_END;

// ******************************************************************
// * CDirectSoundBuffer::SetBufferData
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSoundBuffer_SetBufferData, 4134, 2 + 7, XRefTwo)
    {

        // CDirectSoundBuffer::SetBufferData+0x79 : call [CDirectSoundBufferSettings::SetBufferData]
        XREF_ENTRY(0x7A, XREF_CDirectSoundBufferSettings_SetBufferData),

            // CDirectSoundBuffer::SetBufferData+0x8D : call [CMcpxBuffer::SetBufferData]
            XREF_ENTRY(0x8E, XREF_CMcpxBuffer_SetBufferData),

            // CDirectSoundBuffer::SetBufferData+0x00 : push ebp
            { 0x00, 0x55 },

            // CDirectSoundBuffer::SetBufferData+0x0F : cmp dword ptr [ebp+10h],edi
            { 0x0F, 0x39 },
            { 0x10, 0x7D },
            { 0x11, 0x10 },

#if 0
        // CDirectSoundBuffer::SetBufferData+0x12 : mov dword ptr [ebp+0Ch],edi
        { 0x12, 0x89 },
        { 0x13, 0x7D },
        { 0x14, 0x0C },

        // CDirectSoundBuffer::SetBufferData+0x4B : mov eax,dword ptr [esi+1Ch]
        { 0x4B, 0x8B },
        { 0x4C, 0x46 },
        { 0x4D, 0x1C },

        // CDirectSoundBuffer::SetBufferData+0x64 : mov ecx,dword ptr [esi+20h]
        { 0x64, 0x8B },
        { 0x65, 0x4E },
        { 0x66, 0x20 },

        // CDirectSoundBuffer::SetBufferData+0x8A : mov ecx,dword ptr [esi+20h]
        { 0x8A, 0x8B },
        { 0x8B, 0x4E },
        { 0x8C, 0x20 },
#endif

            // CDirectSoundBuffer_SetBufferData+0xAB : retn 0x0C
            { 0xAB, 0xC2 },
            { 0xAC, 0x0C },
            { 0xAD, 0x00 },
    }
OOVPA_END;

// ******************************************************************
// * CMcpxBuffer_GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_GetStatus,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_GetStatus+0x0A : mov esi, ecx
    { 0x0A, 0x8B },
    { 0x0B, 0xF1 },

    // CMcpxBuffer_GetStatus+0x20 : jz +0x18
    { 0x20, 0x74 },
    { 0x21, 0x18 },

    // CMcpxBuffer_GetStatus+0x22 : test word ptr [esi+0x12], 0x8002
    { 0x22, 0x66 },
    { 0x23, 0xF7 },
    { 0x24, 0x46 },
    { 0x25, 0x12 },

    // CMcpxBuffer_GetStatus+0x2C : test word ptr [esi+0x12], 0x200
    { 0x2C, 0x66 },
    { 0x2D, 0xF7 },
    { 0x2E, 0x46 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetStatus
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetStatus,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_GetStatus+0x35 : call [CMcpxBuffer::GetStatus]
    XREF_ENTRY(0x35, XREF_CMcpxBuffer_GetStatus),

    // CDirectSoundBuffer_GetStatus+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_GetStatus+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_GetStatus+0x3D : jz +0x0B
    { 0x3D, 0x74 },
    { 0x3E, 0x0B },

    // CDirectSoundBuffer_GetStatus+0x4E : retn 0x08
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * CMcpxBuffer_SetCurrentPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_SetCurrentPosition,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_SetCurrentPosition+0x11 : mov al, [esi+12]
    { 0x11, 0x8A },
    { 0x12, 0x46 },
    { 0x13, 0x12 },

    // CMcpxBuffer_SetCurrentPosition+0x5F : jb +0x10
    { 0x5F, 0x72 },
    { 0x60, 0x10 },

    // CMcpxBuffer_SetCurrentPosition+0x86 : movzx eax, byte ptr [esi+0x64]
    { 0x86, 0x0F },
    { 0x87, 0xB6 },
    { 0x88, 0x46 },
    { 0x89, 0x64 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetCurrentPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetCurrentPosition,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetCurrentPosition+0x35 : call [CMcpxBuffer::SetCurrentPosition]
    XREF_ENTRY(0x35, XREF_CMcpxBuffer_SetCurrentPosition),

    // CDirectSoundBuffer_SetCurrentPosition+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetCurrentPosition+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetCurrentPosition+0x3D : jz +0x0B
    { 0x3D, 0x74 },
    { 0x3E, 0x0B },

    // CDirectSoundBuffer_SetCurrentPosition+0x3D : retn 0x08
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetCurrentPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_GetCurrentPosition,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_GetCurrentPosition+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxBuffer_GetCurrentPosition+0x0E : lea ecx, [ebp-0x08]
    { 0x0E, 0x8D },
    { 0x0F, 0x4D },
    { 0x10, 0xF8 },

    { 0x25, 0xE8 },

    // CMcpxBuffer_GetCurrentPosition+0x31 : jz +0x02
    { 0x31, 0x74 },
    { 0x32, 0x02 },

    { 0x44, 0xE8 },

    // CMcpxBuffer_GetCurrentPosition+0x5C : test word ptr [esi+12h],200h
    { 0x5C, 0x66 },
    { 0x5D, 0xF7 },
    { 0x5E, 0x46 },
    { 0x5F, 0x12 },
    { 0x60, 0x00 },
    { 0x61, 0x02 },

    // Offset 0x62 and later has changes.

    // CMcpxBuffer_GetCurrentPosition+0xA0 : div dword ptr [ecx+0xBC]
    //{ 0xA0, 0xF7 },
    //{ 0xA1, 0xB1 },
    //{ 0xA2, 0xBC },

    // CMcpxBuffer_GetCurrentPosition+0xD6 : retn 0x08
    //{ 0xD6, 0xC2 },
    //{ 0xD7, 0x08 },
    //{ 0xD8, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetCurrentPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetCurrentPosition,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_GetCurrentPosition+0x39 : call [CMcpxBuffer::GetCurrentPosition]
    XREF_ENTRY(0x39, XREF_CMcpxBuffer_GetCurrentPosition),

    // CDirectSoundBuffer_GetCurrentPosition+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_GetCurrentPosition+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_GetCurrentPosition+0x41 : jz +0x0B
    { 0x41, 0x74 },
    { 0x42, 0x0B },

    // CDirectSoundBuffer_GetCurrentPosition+0x52 : retn 0x08
    { 0x52, 0xC2 },
    { 0x53, 0x0C },
    //
);

// ******************************************************************
// * CDirectSound::SetDistanceFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDistanceFactor,
                         4134)
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

    // CDirectSound_SetDistanceFactor+0x39 : or dword ptr[eax+0xA4], 0x60
    { 0x39, 0x83 },
    { 0x3A, 0x88 },
    { 0x3B, 0xA4 },
    { 0x3F, 0x60 },

    // CDirectSound_SetDistanceFactor+0x4F : jz +0x0B
    { 0x4F, 0x74 },
    { 0x50, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::SetRolloffFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetRolloffFactor,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_SetRolloffFactor+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSound_SetRolloffFactor+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // This asm code is unique.
    // CDirectSound_SetRolloffFactor+0x33 : mov [eax+6Ch], edx
    { 0x33, 0x89 },
    { 0x34, 0x50 },
    //{ 0x35, 0x6C }, vs 5344 (0x70) then revert back.

    // CDirectSound_SetRolloffFactor+0x36 : mov eax, [ecx+8]
    { 0x36, 0x8B },
    { 0x37, 0x41 },
    { 0x38, 0x08 },

    // Offset 0x3B and later has change in 5344,
    // however offset 0x35 is a requirement.

    // CDirectSound_SetRolloffFactor+0x39 : or dword ptr[eax+0xA4], 0x04
    { 0x39, 0x83 },
    { 0x3A, 0x88 },
    //{ 0x3B, 0xA4 },
    { 0x3F, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound::SetDopplerFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDopplerFactor,
                         4134)
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

    // CDirectSound_SetDopplerFactor+0x39 : or dword ptr[eax+0xA4], 0x40
    { 0x39, 0x83 },
    { 0x3A, 0x88 },
    { 0x3B, 0xA4 },
    { 0x3F, 0x40 },

    // CDirectSound_SetDopplerFactor+0x4F : jz +0x0B
    { 0x4F, 0x74 },
    { 0x50, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::CommitDeferredSettings
// ******************************************************************
OOVPA_XREF(CDirectSound_CommitDeferredSettings, 4134, 1 + 9, XRefOne)
    {

        // CDirectSound_CommitDeferredSettings+0x49 : call [CDirectSoundVoice::CommitDeferredSettings]
        XREF_ENTRY(0x4A, XREF_CDirectSoundVoice_CommitDeferredSettings),

            // CDirectSound_CommitDeferredSettings+0x00 : push ebp
            { 0x00, 0x55 },

#if 0
        // CDirectSound_CommitDeferredSettings+0x10 : movzx eax, al
        { 0x10, 0x0F },
        { 0x11, 0xB6 },
        { 0x12, 0xC0 },
#endif

            // CDirectSound_CommitDeferredSettings+0x27 : mov eax, 0x80004005
            { 0x27, 0xB8 },
            { 0x28, 0x05 },
            { 0x29, 0x40 },
            { 0x2B, 0x80 },

            // CDirectSound_CommitDeferredSettings+0x5C : and [eax+0xA4], esi
            { 0x5C, 0x21 },
            { 0x5D, 0xB0 },
            { 0x5E, 0xA4 },

            // CDirectSound_CommitDeferredSettings+0x78 : leave
            { 0x78, 0xC9 },
        //
    }
OOVPA_END;

// ******************************************************************
// * CDirectSoundVoice::SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMaxDistance,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMaxDistance+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetMaxDistance+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetMaxDistance+0x11 : mov [eax+38h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x38 }, // SetMaxDistance 0x38 VS SetMinDistance 0x34

    { 0x14, 0x8B },
    { 0x1D, 0x83 },
    { 0x1F, 0x70 }, // 4134 0x70 vs 4361 0x78

    // CDirectSoundVoice_SetMaxDistance+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMaxDistance
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMaxDistance,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMaxDistance+0x39 : call [CDirectSoundVoice::SetMaxDistance]
    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetMaxDistance),

    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMaxDistance+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetMaxDistance+0x32 : fstp    [esp+0Ch+var_C]
    { 0x32, 0xD9 },
    { 0x33, 0x1C },
    { 0x34, 0x24 },

    // CDirectSoundBuffer_SetMaxDistance+0x53 : retn 0Ch
    { 0x54, 0x0C },
    { 0x55, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMaxDistance
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMaxDistance,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3E, XREF_CDirectSoundVoice_SetMaxDistance),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x3D, 0xE8 },
    { 0x48, 0x68 },
    { 0x53, 0x8B },

    { 0x57, 0xC2 },
    { 0x58, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMinDistance,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMinDistance+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetMinDistance+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetMinDistance+0x11 : mov [eax+34h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x34 }, // SetMaxDistance 0x38 VS SetMinDistance 0x34

    { 0x14, 0x8B },
    { 0x1D, 0x83 },
    { 0x1F, 0x70 }, // 4134 0x70 vs 4361 0x78

    // CDirectSoundVoice_SetMinDistance+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMinDistance
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMinDistance,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMinDistance+0x39 : call [CDirectSoundVoice::SetMinDistance]
    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetMinDistance),

    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMinDistance+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetMinDistance+0x32 : fstp [esp+0Ch+var_C]
    { 0x32, 0xD9 },
    { 0x33, 0x1C },
    { 0x34, 0x24 },

    // CDirectSoundBuffer_SetMinDistance+0x53 : retn 0Ch
    { 0x54, 0x0C },
    { 0x55, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetMinDistance
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMinDistance,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3E, XREF_CDirectSoundVoice_SetMinDistance),

    { 0x00, 0x56 },

    // CDirectSoundStream_SetMinDistance+0x21 : mov eax, 80004005h
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundStream_SetMinDistance+0x39 : fstp [esp]
    { 0x39, 0xD9 },
    { 0x3A, 0x1C },
    { 0x3B, 0x24 },

    { 0x57, 0xC2 },
    { 0x58, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetRolloffFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetRolloffFactor,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetRolloffFactor+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetRolloffFactor+0x11 : mov [eax+44h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x44 },

    { 0x14, 0x8B },
    { 0x1D, 0x83 },
    { 0x1F, 0x70 },

    // CDirectSoundVoice_SetRolloffFactor+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetRolloffFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetRolloffFactor+0x39 : call [CDirectSoundVoice::SetRolloffFactor]
    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetRolloffFactor),

    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetRolloffFactor+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetRolloffFactor+0x32 : fstp    [esp+0Ch+var_C]
    { 0x32, 0xD9 },
    { 0x33, 0x1C },
    { 0x34, 0x24 },

    // CDirectSoundBuffer_SetRolloffFactor+0x53 : retn 0Ch
    { 0x54, 0x0C },
    { 0x55, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetRolloffFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetRolloffFactor+0x1C : call [CDirectSoundBuffer::SetRolloffFactor]
    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_SetRolloffFactor),

    // IDirectSoundBuffer_SetRolloffFactor+0x00 : push dword ptr [esp+0Ch]
    { 0x02, 0x24 },

    // IDirectSoundBuffer_SetRolloffFactor+0x04 : fld [esp+4+arg_4]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetRolloffFactor+0x12 : add eax, 0FFFFFFE4
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xE4 },

    // IDirectSoundBuffer_SetRolloffFactor+0x21 : retn 0Ch
    { 0x22, 0x0C },
    { 0x23, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetRolloffFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3E, XREF_CDirectSoundVoice_SetRolloffFactor),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x3D, 0xE8 },
    { 0x48, 0x68 },
    { 0x53, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetDistanceFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetDistanceFactor,
                         4134)
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
    { 0x1D, 0x83 },
    { 0x1F, 0x70 },

    // CDirectSoundVoice_SetDistanceFactor+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetDistanceFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetDistanceFactor+0x39 : call [CDirectSoundVoice::SetDistanceFactor]
    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetDistanceFactor),

    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetDistanceFactor+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetDistanceFactor+0x32 : fstp    [esp+0Ch+var_C]
    { 0x32, 0xD9 },
    { 0x33, 0x1C },
    { 0x34, 0x24 },

    // CDirectSoundBuffer_SetDistanceFactor+0x53 : retn 0Ch
    { 0x54, 0x0C },
    { 0x55, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetDistanceFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetDistanceFactor+0x1C : call [CDirectSoundBuffer::SetDistanceFactor]
    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_SetDistanceFactor),

    // IDirectSoundBuffer_SetDistanceFactor+0x04 : fld [esp+4+arg_4]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetDistanceFactor+0x12 : add eax, 0FFFFFFE4
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xE4 },

    // IDirectSoundBuffer_SetSetDistanceFactor+0x21 : retn 0Ch
    { 0x22, 0x0C },
    { 0x23, 0x00 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetConeAngles
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeAngles,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    { 0x10, 0x08 },
    { 0x11, 0x89 },
    { 0x12, 0x51 },
    { 0x13, 0x1C }, // SetConeAngles 0x1C vs SetRolloffCurve 0x70
    { 0x14, 0x8B },
    { 0x15, 0x48 },
    { 0x16, 0x10 },
    { 0x17, 0x8B },
    { 0x18, 0x89 },

    { 0x23, 0x20 }, // SetConeAngles 0x20 vs SetRolloffCurve 0x74
    { 0x30, 0x10 }, // SetConeAngles 0x10 vs SetRolloffCurve 0x04
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeAngles
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeAngles,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetConeAngles+0x39 : call [CDirectSoundVoice::SetConeAngles]
    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetConeAngles),

    // CDirectSoundBuffer_SetConeAngles+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetConeAngles+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetConeAngles+0x31 : push [esp+0Ch+arg_4]
    { 0x31, 0xFF },
    { 0x32, 0x74 },
    { 0x33, 0x24 },
    { 0x34, 0x18 },

    // CDirectSoundBuffer_SetConeAngles+0x53 : retn 10h
    { 0x54, 0x10 },
    { 0x55, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetConeOrientation
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeOrientation,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetConeOrientation+0x0F : mov edx, [ebp+arg_4]
    { 0x0F, 0x8B },
    { 0x10, 0x55 },
    { 0x11, 0x0C },

    // CDirectSoundVoice_SetConeOrientation+0x12 : mov [ecx+24h], edx
    { 0x12, 0x89 },
    { 0x13, 0x51 },
    { 0x14, 0x24 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetConeOrientation+0x21 : mov [ecx+28h], edx
    { 0x21, 0x89 },
    { 0x22, 0x51 },
    { 0x23, 0x28 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetConeOrientation+0x30 : mov [ecx+2Ch], edx
    { 0x30, 0x89 },
    { 0x31, 0x51 },
    { 0x32, 0x2C }, // SetConeOrientation vs SetPosition vs SetVelocity
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeOrientation
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeOrientation,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetConeOrientation+0x49 : call [CDirectSoundVoice::SetConeOrientation]
    XREF_ENTRY(0x4A, XREF_CDirectSoundVoice_SetConeOrientation),

    // CDirectSoundBuffer_SetConeOrientation+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetConeOrientation+0x2B : fld [ebp+arg_C]
    { 0x2B, 0xD9 },
    { 0x2C, 0x45 },
    { 0x2D, 0x14 },

    // CDirectSoundBuffer_SetConeOrientation+0x43 : fstp [esp+18h+var_18]
    { 0x43, 0xD9 },
    { 0x44, 0x1C },
    { 0x45, 0x24 },

    // CDirectSoundBuffer_SetConeOrientation+0x64 : retn 14h
    { 0x65, 0x14 },
    { 0x66, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeOrientation
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeOrientation,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4E, XREF_CDirectSoundVoice_SetConeOrientation),

    { 0x00, 0x55 },
    { 0x0F, 0x00 },
    { 0x17, 0x74 },
    { 0x24, 0xB8 },
    { 0x2A, 0x3B },
    { 0x39, 0xEC },
    { 0x44, 0x24 },
    { 0x4D, 0xE8 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeOutsideVolume,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetConeOutsideVolume+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x11 : mov [eax+30h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x30 },

    { 0x14, 0x8B },
    { 0x1D, 0x83 },
    { 0x1F, 0x70 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeOutsideVolume
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeOutsideVolume,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetConeOutsideVolume+0x35 : call [CDirectSoundVoice::SetConeOutsideVolume]
    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    // CDirectSoundBuffer_SetConeOutsideVolume+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetConeOutsideVolume+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetConeOutsideVolume+0x31 : push [esp+0Ch+arg_0]
    { 0x31, 0xFF },
    { 0x32, 0x74 },
    { 0x33, 0x24 },
    { 0x34, 0x14 },

    // CDirectSoundBuffer_SetConeOutsideVolume+0x4F : retn 0Ch
    { 0x50, 0x0C },
    { 0x51, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeOutsideVolume
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeOutsideVolume,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x21, 0xB8 },
    { 0x24, 0x00 },
    { 0x39, 0xE8 },
    { 0x3E, 0x85 },
    { 0x4F, 0x8B },
    { 0x53, 0xC2 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetPosition,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetPosition+0x0F : mov edx, [ebp+arg_4]
    { 0x0F, 0x8B },
    { 0x10, 0x55 },
    { 0x11, 0x0C },

    // CDirectSoundVoice_SetPosition+0x12 : mov [ecx+04h], edx
    { 0x12, 0x89 },
    { 0x13, 0x51 },
    { 0x14, 0x04 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetPosition+0x21 : mov [ecx+08h], edx
    { 0x21, 0x89 },
    { 0x22, 0x51 },
    { 0x23, 0x08 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetPosition+0x30 : mov [ecx+0Ch], edx
    { 0x30, 0x89 },
    { 0x31, 0x51 },
    { 0x32, 0x0C }, // SetConeOrientation vs SetPosition vs SetVelocity
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetPosition,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetPosition+0x49 : call [CDirectSoundVoice::SetPosition]
    XREF_ENTRY(0x4A, XREF_CDirectSoundVoice_SetPosition),

    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetPosition+0x2B : fld [ebp+arg_C]
    { 0x2B, 0xD9 },
    { 0x2C, 0x45 },
    { 0x2D, 0x14 },

    // CDirectSoundBuffer_SetPosition+0x43 : fstp [esp+18h+var_18]
    { 0x43, 0xD9 },
    { 0x44, 0x1C },
    { 0x45, 0x24 },

    // CDirectSoundBuffer_SetPosition+0x64 : retn 14h
    { 0x65, 0x14 },
    { 0x66, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetPosition
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetPosition,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4E, XREF_CDirectSoundVoice_SetPosition),

    { 0x00, 0x55 },
    { 0x0F, 0x00 },
    { 0x17, 0x74 },
    { 0x24, 0xB8 },
    { 0x2A, 0x3B },
    { 0x39, 0xEC },
    { 0x58, 0x68 },
    { 0x63, 0x8B },

    { 0x68, 0xC2 },
    { 0x69, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetVelocity
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetVelocity,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetVelocity+0x0F : mov edx, [ebp+arg_4]
    { 0x0F, 0x8B },
    { 0x10, 0x55 },
    { 0x11, 0x0C },

    // CDirectSoundVoice_SetVelocity+0x12 : mov [ecx+10h], edx
    { 0x12, 0x89 },
    { 0x13, 0x51 },
    { 0x14, 0x10 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetVelocity+0x21 : mov [ecx+14h], edx
    { 0x21, 0x89 },
    { 0x22, 0x51 },
    { 0x23, 0x14 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetVelocity+0x30 : mov [ecx+18h], edx
    { 0x30, 0x89 },
    { 0x31, 0x51 },
    { 0x32, 0x18 }, // SetConeOrientation vs SetPosition vs SetVelocity
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetVelocity
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetVelocity,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetVelocity+0x49 : call [CDirectSoundVoice::SetVelocity]
    XREF_ENTRY(0x4A, XREF_CDirectSoundVoice_SetVelocity),

    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetVelocity+0x2B : fld [ebp+arg_C]
    { 0x2B, 0xD9 },
    { 0x2C, 0x45 },
    { 0x2D, 0x14 },

    // CDirectSoundBuffer_SetVelocity+0x43 : fstp [esp+18h+var_18]
    { 0x43, 0xD9 },
    { 0x44, 0x1C },
    { 0x45, 0x24 },

    // CDirectSoundBuffer_SetVelocity+0x64 : retn 14h
    { 0x65, 0x14 },
    { 0x66, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVelocity
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetVelocity,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4E, XREF_CDirectSoundVoice_SetVelocity),

    { 0x00, 0x55 },
    { 0x0F, 0x00 },
    { 0x17, 0x74 },
    { 0x24, 0xB8 },
    { 0x2A, 0x3B },
    { 0x35, 0x83 },
    { 0x40, 0x45 },
    { 0x63, 0x8B },

    { 0x68, 0xC2 },
    { 0x69, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetDopplerFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetDopplerFactor,
                         4134)
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
    { 0x1D, 0x83 },
    { 0x1F, 0x70 },

    // CDirectSoundVoice_SetDopplerFactor+0x31 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetDopplerFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetDopplerFactor+0x39 : call [CDirectSoundVoice::SetDopplerFactor]
    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetDopplerFactor),

    // CDirectSoundBuffer_SetDopplerFactor+0x2D : push    [esp+4+arg_8]
    { 0x2D, 0xFF },
    { 0x2E, 0x74 },
    { 0x2F, 0x24 },
    { 0x30, 0x14 },

    // CDirectSoundBuffer_SetDopplerFactor+0x32 : fstp [esp+0Ch+var_C]
    { 0x32, 0xD9 },
    { 0x33, 0x1C },
    { 0x34, 0x24 },

    // CDirectSoundBuffer_SetDopplerFactor+0x53 : retn 0Ch
    { 0x54, 0x0C },
    { 0x55, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetDopplerFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetDopplerFactor+0x1C : call [CDirectSoundBuffer::SetDopplerFactor]
    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_SetDopplerFactor),

    // IDirectSoundBuffer_SetDopplerFactor+0x08 : mov eax, [esp+4+arg_0]
    { 0x08, 0x8B },
    { 0x09, 0x44 },
    { 0x0A, 0x24 },
    { 0x0B, 0x08 },

    // IDirectSoundBuffer_SetDopplerFactor+0x19 : and ecx, eax
    { 0x19, 0x23 },
    { 0x1A, 0xC8 },

    // IDirectSoundBuffer_SetDopplerFactor+0x21 : retn 0Ch
    { 0x22, 0x0C },
    { 0x23, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetI3DL2Source,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetI3DL2Source+0xA5 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0xA6, XREF_CDirectSoundVoice_CommitDeferredSettings),

    { 0x00, 0x8B },

    // CDirectSoundVoice_SetI3DL2Source+0x12 : mov esi, [ecx]
    { 0x12, 0x8B },
    { 0x13, 0x31 },

    // CDirectSoundVoice_SetI3DL2Source+0x14 : mov [edx+4Ch], esi
    { 0x14, 0x89 },
    { 0x15, 0x72 },
    { 0x16, 0x4C },

    // CDirectSoundVoice_SetI3DL2Source+0x44 : fld dword ptr [ecx+10h] (not advise to use)
    { 0x44, 0xD9 },
    { 0x45, 0x41 },
    { 0x46, 0x10 },

    // CDirectSoundVoice_SetI3DL2Source+0xAC : retn 0Ch
    { 0xAD, 0x0C },
    { 0xAE, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetI3DL2Source
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetI3DL2Source,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetI3DL2Source+0x35 : call [CDirectSoundVoice::SetI3DL2Source]
    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetI3DL2Source),

    // CDirectSoundBuffer_SetI3DL2Source+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetI3DL2Source+0x21 : mov eax, 80004005h
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_SetI3DL2Source+0x31 : push [esp+0Ch+arg_0]
    { 0x31, 0xFF },
    { 0x32, 0x74 },
    { 0x33, 0x24 },
    { 0x34, 0x14 },

    // CDirectSoundBuffer_SetI3DL2Source+0x4F : retn 0Ch
    { 0x50, 0x0C },
    { 0x51, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetI3DL2Source
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetI3DL2Source,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetI3DL2Source),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x39, 0xE8 },
    { 0x44, 0x68 },
    { 0x4F, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetAllParameters
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetAllParameters,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x04, 0x8B },

    { 0x63, 0x8B },
    { 0x66, 0x8B },

    { 0x83, 0x24 },

    // CDirectSoundVoice::SetAllParameters+0x84 : mov edx,[eax+0x10]
    { 0x84, 0x8B },
    { 0x85, 0x50 },
    { 0x86, 0x10 },

    // CDirectSoundVoice::SetAllParameters+0x87 : mov edx,[edx+0x000000B4]
    { 0x87, 0x8B },
    { 0x88, 0x92 },
    { 0x89, 0xB4 },
    { 0x8A, 0x00 },
    { 0x8B, 0x00 },
    { 0x8C, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetAllParameters
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetAllParameters,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetAllParameters),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x74 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetAllParameters
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetAllParameters,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetAllParameters),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x39, 0xE8 },
    { 0x44, 0x68 },
    { 0x4F, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMode,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMode+0x1C : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x1D, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice::SetMode+0x00 : test byte [esp+0x0C],0x01
    { 0x00, 0xF6 },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x0C },
    { 0x04, 0x01 },

    // CDirectSoundVoice::SetMode+0x05 : mov eax,[esp+0x__]
    { 0x05, 0x8B },
    { 0x06, 0x44 },
    { 0x07, 0x24 },

    // CDirectSoundVoice::SetMode+0x19 : jne 0x__
    { 0x19, 0x75 },

    // CDirectSoundVoice::SetMode+0x1C : call [CDirectSoundVoice::CommitDeferredSettings]
    { 0x1C, 0xE8 },

    { 0x23, 0xC2 },
    { 0x24, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMode
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMode,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetMode),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x74 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMode
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMode,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3A, XREF_CDirectSoundVoice_SetMode),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x39, 0xE8 },
    { 0x44, 0x68 },
    { 0x4F, 0x8B },

    { 0x53, 0xC2 },
    { 0x54, 0x0C },
    //
);

// ******************************************************************
// * DirectSound::CMcpxVoiceClient::SetFilter
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetFilter,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    { 0x23, 0x6A },
    { 0x24, 0x06 },

    { 0x47, 0x83 },
    { 0x48, 0xE0 },
    { 0x49, 0x03 },

    { 0x50, 0xC1 },
    { 0x51, 0xE8 },
    { 0x52, 0x12 },

    { 0x53, 0x83 },
    { 0x54, 0xE0 },
    { 0x55, 0x07 },

    //NOTE: Before offset 0x65, there has been no changes throughout all revisions.
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetFilter
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFilter,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetFilter),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x12, 0x85 },
    { 0x1C, 0x15 },
    { 0x26, 0xEB },
    { 0x30, 0x10 },
    { 0x3A, 0x74 },
    { 0x47, 0x8B },
    //
);

// ******************************************************************
// * CDirectSound::SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetVelocity,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_SetVelocity+0x00 : push ebp
    { 0x00, 0x55 },

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

    // CDirectSound_SetVelocity+0x4C : or dword ptr [eax+0x0A4], 0x40
    { 0x4C, 0x83 },
    { 0x4D, 0x88 },
    { 0x4E, 0xA4 },
    { 0x4F, 0x00 },
    { 0x52, 0x40 },

    // CDirectSound_SetVelocity+0x73 : retn 0x14
    { 0x73, 0xC2 },
    { 0x74, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPitch
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetPitch,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetPitch),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x12, 0x85 },
    { 0x1C, 0x15 },
    { 0x26, 0xEB },
    { 0x30, 0x10 },
    { 0x3A, 0x74 },
    { 0x47, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetPitch
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetPitch,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetPitch),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    { 0x51, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetVolume,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetVolume+0x32 : call [CDirectSoundVoice::SetVolume]
    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetVolume),

    // CDirectSoundBuffer_SetVolume+0x0D : movzx esi, al
    { 0x0D, 0x0F },
    { 0x0E, 0xB6 },
    { 0x0F, 0xF0 },

    // CDirectSoundBuffer_SetVolume+0x26 : jmp +0x22
    { 0x26, 0xEB },
    { 0x27, 0x22 },

    // CDirectSoundBuffer_SetVolume+0x2D : push [esp+0x10]
    { 0x2D, 0xFF },
    { 0x2E, 0x74 },
    { 0x2F, 0x24 },
    { 0x30, 0x10 },

    // CDirectSoundBuffer_SetVolume+0x4B : retn 0x08
    { 0x4B, 0xC2 },
    { 0x4C, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound::CreateSoundStream
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CreateSoundStream,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_CreateSoundStream+0x23 : mov eax, 0x80004005
    { 0x23, 0xB8 },
    { 0x24, 0x05 },
    { 0x25, 0x40 },
    { 0x27, 0x80 },

    // CDirectSound_CreateSoundStream+0x2A : push 0x28
    { 0x2A, 0x6A },
    { 0x2B, 0x28 },

    // CDirectSound_CreateSoundStream+0x4A : add esi, 0x7FF8FFF2
    { 0x4A, 0x81 },
    { 0x4B, 0xE6 },
    { 0x4C, 0xF2 },
    { 0x4D, 0xFF },
    { 0x4E, 0xF8 },
    { 0x4F, 0x7F },

    // CDirectSound_CreateSoundStream+0x8E : retn 0x10
    { 0x8E, 0xC2 },
    { 0x8F, 0x10 },
    //
);

// ******************************************************************
// * DirectSoundCreateStream
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(DirectSoundCreateStream,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundCreateStream+0x2F : call [CDirectSound::CreateSoundStream]
    XREF_ENTRY(0x2F, XREF_CDirectSound_CreateSoundStream),

    // DirectSoundCreateStream+0x04 : and [ebp-0x04], 0
    { 0x04, 0x83 },
    { 0x05, 0x65 },
    { 0x06, 0xFC },

    // DirectSoundCreateStream+0x08 : push ebx; push esi; push edi
    { 0x08, 0x53 },
    { 0x09, 0x56 },
    { 0x0A, 0x57 },

    // DirectSoundCreateStream+0x3C : call dword ptr [eax+8]
    { 0x3C, 0xFF },
    { 0x3D, 0x50 },
    { 0x3E, 0x08 },

    // DirectSoundCreateStream+0x54 : retn 0x08
    { 0x54, 0xC2 },
    { 0x55, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoiceSettings::SetMixBinVolumes
// ******************************************************************
// Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoiceSettings_SetMixBinVolumes,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x09 : jbe +0x16
    { 0x09, 0x76 },
    { 0x0A, 0x16 },

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x18 : mov [ecx+edi*4+0x30], eax
    { 0x18, 0x89 },
    { 0x19, 0x44 },
    { 0x1A, 0xB9 },
    { 0x1B, 0x30 },

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x1E : jb +0xEC
    { 0x1E, 0x72 },
    { 0x1F, 0xEC },

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x22 : retn 0x04
    { 0x22, 0xC2 },
    { 0x23, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMixBinVolumes
// ******************************************************************
//Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSoundBuffer_SetMixBinVolumes_8, 4134, 1 + 12, XRefOne)
    {

        // CDirectSoundBuffer_SetMixBinVolumes+0x32 : call [CDirectSoundVoice::SetMixBinVolumes]
        XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetMixBinVolumes),

            // CDirectSoundBuffer_SetMixBinVolumes+0x00 : push esi
            { 0x00, 0x56 },

#if 0
        // CDirectSoundBuffer_SetMixBinVolumes+0x21 : mov eax, 0x80004005
        { 0x21, 0xB8 },
        { 0x22, 0x05 },
        { 0x23, 0x40 },
        { 0x24, 0x00 },
        { 0x25, 0x80 },
#endif

            // CDirectSoundBuffer_SetMixBinVolumes+0x29 : push [esp+0x10]; push [esp+0x10]
            { 0x29, 0xFF },
            { 0x2A, 0x74 },
            { 0x2B, 0x24 },
            { 0x2C, 0x10 },
            { 0x2D, 0xFF },
            { 0x2E, 0x74 },
            { 0x2F, 0x24 },
            { 0x30, 0x10 },

            // CDirectSoundBuffer_SetMixBinVolumes+0x49 : pop edi
            { 0x49, 0x5F },

            // CDirectSoundBuffer_SetMixBinVolumes+0x4B : retn 0x08
            { 0x4B, 0xC2 },
            { 0x4C, 0x08 },
        //
    }
OOVPA_END;

// ******************************************************************
// * CDirectSound_SetEffectData
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetEffectData,
                         4134) // Also for 5849
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0F, 0x00 },

    { 0x24, 0xB8 },
    { 0x25, 0x05 },
    { 0x26, 0x40 },
    { 0x27, 0x00 },
    { 0x28, 0x80 },

    { 0x29, 0xEB },
    { 0x2A, 0x32 },

    { 0x2B, 0x8B },
    { 0x2C, 0x45 },

    { 0x44, 0xE8 },

    { 0x5F, 0xC2 },
    { 0x60, 0x18 },
    //
);

// ******************************************************************
// * CMcpxBuffer_Stop
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Stop,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Stop+0x0B : cmp al, 3
    { 0x0B, 0x3C },
    { 0x0C, 0x03 },

    // CMcpxBuffer_Stop+0x1A : jne +0x59
    { 0x1A, 0x75 },
    { 0x1B, 0x59 },

    // CMcpxBuffer_Stop+0x1C : test [esp+0Ch], 2
    { 0x1C, 0xF6 },
    { 0x1D, 0x44 },
    { 0x1E, 0x24 },
    { 0x1F, 0x0C },
    { 0x20, 0x02 },
    //
);

// ******************************************************************
// * CMcpxBuffer::Stop(__int64, unsigned long)
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxBuffer_Stop_Ex,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Stop_Ex+0x2B : call [CMcpxBuffer::Stop]
    XREF_ENTRY(0x2B, XREF_CMcpxBuffer_Stop),

    // CMcpxBuffer_Stop_Ex+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxBuffer_Stop_Ex+0x11 : push [ebp+arg_8]
    { 0x11, 0xFF },
    { 0x12, 0x75 },
    { 0x13, 0x10 },

    // CMcpxBuffer_Stop_Ex+0x23 : jnz +0x0C
    { 0x23, 0x75 },
    { 0x24, 0x0C },

    // CMcpxBuffer_Stop_Ex+0x36 : push esi
    { 0x36, 0xC2 },
    { 0x37, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Stop
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Stop,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_Stop+0x33 : call [CMcpxBuffer::Stop]
    XREF_ENTRY(0x33, XREF_CMcpxBuffer_Stop),

    // CDirectSoundBuffer_Stop+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_Stop+0x2C : mov ecx,[eax+20]
    { 0x2C, 0x8B },
    { 0x2D, 0x48 },
    { 0x2E, 0x20 },

    // CDirectSoundBuffer_Stop+0x3B : jz +0x0B
    { 0x3B, 0x74 },
    { 0x3C, 0x0B },

    // CDirectSoundBuffer_Stop+0x4C : retn 0x04
    { 0x4C, 0xC2 },
    { 0x4D, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetEG
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetEG,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetEG),

    { 0x00, 0x56 }, //Prevent incorrect offset difference from 4039 revision.

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetFilter
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetFilter,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetFilter),

    { 0x00, 0x56 }, //Prevent incorrect offset difference from 4039 revision.

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetLFO
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetLFO,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetLFO),

    { 0x00, 0x56 }, //Prevent incorrect offset difference from 4039 revision.

    { 0x0C, 0x00 },
    { 0x0F, 0xF0 },
    { 0x12, 0x85 },
    { 0x15, 0x0B },
    { 0x3A, 0x85 },
    { 0x3D, 0xF8 },
    { 0x40, 0x68 },
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound_SetOrientation
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetOrientation,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_SetOrientation+0x00 : push ebp
    { 0x00, 0x55 },

    { 0x31, 0x8B },
    { 0x33, 0x0C },
    { 0x3A, 0x8B },
    { 0x3C, 0x10 },
    { 0x43, 0x8B },
    { 0x45, 0x14 },
    { 0x4C, 0x8B },
    { 0x4E, 0x18 },
    { 0x55, 0x8B },
    { 0x57, 0x1C },
    { 0x5E, 0x8B },
    { 0x60, 0x20 },
    //
);

// ******************************************************************
// * CDirectSound_DownloadEffectsImage
// ******************************************************************
//Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_DownloadEffectsImage,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSound_DownloadEffectsImage+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_DownloadEffectsImage+0x2C : mov esi,dword ptr [ebp+8]
    { 0x2C, 0x8B },
    { 0x2D, 0x75 },
    { 0x2E, 0x08 },

    // CDirectSound_DownloadEffectsImage+0x2F : push dword ptr [ebp+14h]
    { 0x2F, 0xFF },
    { 0x30, 0x75 },
    { 0x31, 0x14 },

    // CDirectSound_DownloadEffectsImage+0x32 : mov ecx,dword ptr [esi+8]
    { 0x32, 0x8B },
    { 0x33, 0x4E },
    { 0x34, 0x08 },

    // CDirectSound_DownloadEffectsImage+0x3A :  push dword ptr [ebp+18h]
    { 0x3A, 0xFF },
    //{ 0x3B, 0x75 },
    { 0x3C, 0x18 },

    // CDirectSound_DownloadEffectsImage+0x40 : push dword ptr [ebp+10h]
    { 0x40, 0xFF },
    //{ 0x41, 0x75 },
    { 0x42, 0x10 },

    // CDirectSound_DownloadEffectsImage+0x43 : push dword ptr [ebp+0Ch]
    { 0x43, 0xFF },
    //{ 0x44, 0x75 },
    { 0x45, 0x0C },

    // CDirectSound_DownloadEffectsImage+0x61 : ret 14h
    { 0x61, 0xC2 },
    { 0x62, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Release
// ******************************************************************
// Generic OOVPA as of 4134 plus 5344 and newer.
// NOTE: Has identical function to CAc97MediaObject::Release
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Release,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_DSound_CRefCount_Release),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },

    { 0x2D, 0x83 },
    { 0x2E, 0xC0 },
    { 0x2F, 0x04 },

    { 0x47, 0x8B },

    { 0x4B, 0xC2 },
    { 0x4C, 0x04 },
    { 0x4D, 0x00 },
    //
);

// ******************************************************************
// * DirectSound::CFullHRTFSource::GetCenterVolume
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CFullHRTFSource_GetCenterVolume,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    { 0x22, 0xD9 },
    { 0x62, 0xDF },

    { 0xB6, 0xF0 },
    { 0xB7, 0xD8 },
    { 0xB8, 0xFF },
    { 0xB9, 0xFF },

    { 0xBC, 0xC2 },
    { 0xBD, 0x04 },
    //
);

// ******************************************************************
// * DirectSoundUseFullHRTF
// ******************************************************************
// Generic OOVPA as of 4134 plus 5344 and newer.
OOVPA_SIG_HEADER_XREF(DirectSoundUseFullHRTF,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0A, XREF_CHRTFSource_SetFullHRTF5Channel),

    { 0x06, 0x0F },
    { 0x07, 0xB6 },
    { 0x0E, 0x85 },
    { 0x0F, 0xF6 },
    { 0x12, 0x0B },
    { 0x18, 0xFF },
    { 0x1E, 0xC3 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetMixBins
// ******************************************************************
// Generic OOVPA as of 4134 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMixBins,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetMixBins),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },

    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },

    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * CMcpxStream_Pause
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Pause,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxStream_Pause+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxStream_Pause+0x1E : or eax, 4
    { 0x1E, 0x83 },
    { 0x1F, 0xC8 },
    { 0x20, 0x04 },

    // CMcpxStream_Pause+0x21 : jmp +0x0D
    { 0x21, 0xEB },
    { 0x22, 0x0D },

    // CMcpxStream_Pause+0x2D : and eax,-05
    { 0x2D, 0x83 },
    { 0x2E, 0xE0 },
    { 0x2F, 0xFB },

    // CMcpxStream_Pause+0x44 : retn 0x04
    { 0x44, 0xC2 },
    { 0x45, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Pause
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Pause,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_Pause+0x34 : call [CMcpxStream::Pause]
    XREF_ENTRY(0x35, XREF_CMcpxStream_Pause),

    // CDirectSoundStream_Pause+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundStream_Pause+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundStream_Pause+0x2C : mov ecx, [eax+0x24]
    { 0x2C, 0x8B },
    { 0x2D, 0x48 },
    { 0x2E, 0x24 },

    // CDirectSoundStream_Pause+0x4E : retn 0x08
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetLFO,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetLFO+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxVoiceClient_SetLFO+0x38 : jz +0x71
    { 0x38, 0x74 },
    { 0x39, 0x71 },

    // CMcpxVoiceClient_SetLFO+0x3A : movzx ecx, byte ptr [esi+64h]
    { 0x3A, 0x0F },
    { 0x3B, 0xB6 },
    { 0x3C, 0x4E },
    { 0x3D, 0x64 },

    // CMcpxVoiceClient_SetLFO+0x59 : movzx ecx, word ptr [eax]
    { 0x59, 0x0F },
    { 0x5A, 0xB7 },
    { 0x5B, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetEG,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x25, 0xEB },

    { 0x38, 0x74 },
    { 0x39, 0x7B },

    { 0x3E, 0x8D },
    { 0x3F, 0x0C },
    { 0x40, 0xC0 },

    { 0xAE, 0x41 },
    { 0xAF, 0x40 },
    { 0xB0, 0x40 },

    { 0xC1, 0xC2 },
    { 0xC2, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetEG
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetEG,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetEG),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x12, 0x85 },
    { 0x1C, 0x15 },
    { 0x26, 0xEB },
    { 0x30, 0x10 },
    { 0x3A, 0x74 },
    { 0x47, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetLFO
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetLFO,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetLFO),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x12, 0x85 },
    { 0x1C, 0x15 },
    { 0x26, 0xEB },
    { 0x30, 0x10 },
    { 0x3A, 0x74 },
    { 0x47, 0x8B },
    //
);

// ******************************************************************
// * CDirectSound::SetAllParameters
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSound_SetAllParameters,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_SetAllParameters+0x01 : call [DirectSoundEnterCriticalSection]
    XREF_ENTRY(0x02, XREF_DirectSoundEnterCriticalSection),

    { 0x00, 0x56 },
    { 0x01, 0xE8 },

    // CDirectSound_SetAllParameters+0x06 : cmp [DirectSoundCriticalSection], 0
    { 0x0C, 0x00 },

    // CDirectSound_SetAllParameters+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },

    // CDirectSound_SetAllParameters+0x2B : mov XXX, [esp+X]
    { 0x2B, 0x8B },
    { 0x2D, 0x24 },

    // Offset is unique for this asm code.
    // CDirectSound_SetAllParameters+0x32 : mov XXX, [esp+X]
    { 0x32, 0x8B },
    //{ 0x33, 0x44 }, // 4134 0x44 vs 5558 0x4C
    { 0x34, 0x24 },
    //
);

// ******************************************************************
// * CDirectSoundStream_GetInfo
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetInfo,
                         4134)
OOVPA_SIG_MATCH(

    //CDirectSoundStream::GetInfo+0x00 : push ebx
    { 0x00, 0x53 },

    // This asm code is unique.
    //CDirectSoundStream::GetInfo+0x32 : mov [esi],5
    { 0x32, 0xC7 },
    { 0x33, 0x06 },
    { 0x34, 0x05 },
    { 0x35, 0x00 },
    { 0x36, 0x00 },
    { 0x37, 0x00 },

    //CDirectSoundStream::GetInfo+0x49 : and [esi + 0x08],0
    { 0x49, 0x83 },
    { 0x4A, 0x66 },
    { 0x4B, 0x08 },
    { 0x4C, 0x00 },

    //CDirectSoundStream::GetInfo+0x64 : ret 8
    { 0x64, 0xC2 },
    { 0x65, 0x08 },
    //
);

// ******************************************************************
// * CMcpxStream_Flush
// ******************************************************************
OOVPA_NO_XREF(CMcpxStream_Flush, 4134, 13 /*15 total*/)
    {

        // CMcpxStream_Flush+0x00 : push ebp
        { 0x00, 0x55 },
#if 0
        // CMcpxStream_Flush+0x00 : mov ebp, esp
        { 0x01, 0x8B },
        { 0x02, 0xEC },
#endif
            // CMcpxStream_Flush+0x00 : sub esp, 10h
            { 0x03, 0x83 },
            { 0x04, 0xEC },
            { 0x05, 0x10 },
#if 1
            // Offset is unique for this asm code.
            // CMcpxStream_Flush+0x0A : movzx eax,byte ptr fs:[24h]
            { 0x0A, 0x64 },
            { 0x0B, 0x0F },
            { 0x0C, 0xB6 },
            { 0x0D, 0x05 },
            { 0x0E, 0x24 },
            { 0x0F, 0x00 },
            { 0x10, 0x00 },
            { 0x11, 0x00 },
#endif
            // CMcpxStream_Flush+0x12 : xor ???,???
            { 0x12, 0x33 },

        // NOTE: Offset 0x14 and later are different in some revisions.
    }
OOVPA_END;

// ******************************************************************
// * CDirectSoundStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Flush,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream::Flush+0x30 : call [CMcpxStream::Flush]
    XREF_ENTRY(0x31, XREF_CMcpxStream_Flush),

    { 0x00, 0x56 },

    { 0x28, 0x8B },
    { 0x2B, 0x08 },

    { 0x2C, 0x8B },
    { 0x2E, 0x24 },

    // CDirectSoundStream::Flush+0x30 : call [CMcpxStream::Flush]
    { 0x30, 0xE8 },

    // CDirectSoundStream::Flush+0x4A : ret 4
    { 0x4A, 0xC2 },
    { 0x4B, 0x04 },
    //
);

// ******************************************************************
// * CMcpxStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_GetStatus,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    // Added 2 OVs to enable support 4242 titles and later (if any has occurred).
    { 0x2F, 0x03 },
    { 0x32, 0x03 },

    // Just a note, this asm code is unique
    { 0x3D, 0x80 },
    { 0x3E, 0x48 },
    { 0x3F, 0x02 },
    { 0x40, 0x02 },

    { 0x4B, 0x81 },
    { 0x4C, 0xC9 },
    { 0x4D, 0x00 },
    { 0x4E, 0x00 },
    { 0x4F, 0x04 },
    { 0x50, 0x00 },

    // Removed due to 4242 has a return asm code at offset 0x75.
    //{ 0x65, 0xC2 },
    //{ 0x66, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream_GetStatus
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_GetStatus,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_GetStatus+0x34 : call [CMcpxStream::GetStatus]
    XREF_ENTRY(0x35, XREF_CMcpxStream_GetStatus),

    // CDirectSoundStream_GetStatus+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundStream_GetStatus+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundStream_GetStatus+0x2C : mov ecx, [eax+0x24]
    { 0x2C, 0x8B },
    { 0x2D, 0x48 },
    { 0x2E, 0x24 },

    // CDirectSoundStream_GetStatus+0x4E : retn 0x08
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Process
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSoundStream_Process, 4134, 1 + 11, XRefOne)
    {

        // CDirectSoundStream::Process+0x38 : call [CMcpxStream::GetStatus]
        XREF_ENTRY(0x39, XREF_CMcpxStream_GetStatus),

            { 0x00, 0x55 },

            { 0x2D, 0x8B },
            { 0x2F, 0x08 },

#if 0
        { 0x30, 0x8B },
        { 0x32, 0x24 },
#endif

            // CDirectSoundStream::Process+0x49 : mov eax, 88780032h
            { 0x4A, 0x32 },
            { 0x4B, 0x00 },
            { 0x4C, 0x78 },
            { 0x4D, 0x88 },

#if 0
        { 0x52, 0xFF },
        { 0x54, 0x0C },
#endif

            { 0x55, 0x8B },
            { 0x57, 0x24 },

            { 0x74, 0xC2 },
            { 0x75, 0x0C },
    }
OOVPA_END;

// ******************************************************************
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Discontinuity,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CMcpxStream_Discontinuity+0x1C : call [CMcpxStream_Flush]
    XREF_ENTRY(0x1D, XREF_CMcpxStream_Flush),

    { 0x00, 0x56 },

    { 0x01, 0x8B },

    { 0x1A, 0x8B },

    { 0x1C, 0xE8 },

    { 0x23, 0x5E },

    { 0x24, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Discontinuity
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Discontinuity,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CDirectSoundStream_Discontinuity+0x30 : call [CMcpxStream_Discontinuity]
    XREF_ENTRY(0x31, XREF_CMcpxStream_Discontinuity),

    { 0x00, 0x56 },

    { 0x28, 0x8B },
    { 0x2B, 0x08 },

    { 0x2C, 0x8B },
    { 0x2E, 0x24 },

    //CDirectSoundStream::Discontinuity+0x30 : call [CMcpxStream_Discontinuity]
    { 0x30, 0xE8 },

    //CDirectSoundStream_Discontinuity+0x4A : ret 4
    { 0x4A, 0xC2 },
    { 0x4B, 0x04 },
    //
);

// ******************************************************************
// * DirectSound::CMemoryManager::PoolAlloc
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DSound_CMemoryManager_PoolAlloc,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x22, 0x83 },
    { 0x23, 0x7C },
    { 0x24, 0x24 },
    { 0x25, 0x10 },
    { 0x26, 0x00 },

    { 0x35, 0xF3 },
    { 0x36, 0xAB },

    { 0x42, 0xC2 },
    { 0x43, 0x0C },
    { 0x44, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_AddRef
// ******************************************************************
// Generic OOVPA as of 4134 and newer
// NOTE: Has identical function to DirectSound::CAc97MediaObject::AddRef
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_AddRef,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundStream::AddRef+0x00 : call DirectSoundEnterCriticalSection
    { 0x00, 0xE8 },

    // CDirectSoundStream::AddRef+0x27 : mov eax,[esp+0x04]
    { 0x27, 0x8B },
    { 0x28, 0x44 },

    // CDirectSoundStream::AddRef+0x2B : inc [eax+0x08]
    { 0x2B, 0xFF },
    { 0x2C, 0x40 },
    { 0x2D, 0x08 },

    // CDirectSoundStream::AddRef+0x31 : esi,[eax+0x08]
    { 0x31, 0x8B },
    { 0x32, 0x70 },
    { 0x33, 0x08 },

    // CDirectSoundStream::AddRef+0x44 : ret 4
    { 0x44, 0xC2 },
    { 0x45, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound::GetCaps
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetCaps,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x57 },
    { 0x16, 0x68 },

    { 0x37, 0x44 },
    { 0x38, 0x24 },
    { 0x39, 0x18 },
    { 0x3A, 0x8B },
    { 0x3B, 0x48 },
    { 0x3C, 0x0C },
    { 0x3D, 0x56 },
    { 0x3E, 0xE8 },

    { 0x6D, 0xC2 },
    { 0x6E, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetOutputBuffer
// ******************************************************************
OOVPA_XREF(CDirectSoundBuffer_SetOutputBuffer, 4134, 1 + 12, XRefOne)
    {

        // CDirectSoundBuffer::SetOutputBuffer+0x31 : call [CDirectSoundVoice::SetOutputBuffer]
        XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetOutputBuffer),

            // CDirectSoundBuffer::SetOutputBuffer+0x00 : push esi
            { 0x00, 0x56 },

#if 0
        // CDirectSoundBuffer::SetOutputBuffer+0x21 : mov eax, 0x80004005
        { 0x21, 0xB8 },
        { 0x22, 0x05 },
        { 0x23, 0x40 },
        { 0x24, 0x00 },
        { 0x25, 0x80 },
#endif

            // CDirectSoundBuffer::SetOutputBuffer+0x29 : push [esp+0x10]; push [esp+0x10]
            { 0x29, 0xFF },
            { 0x2A, 0x74 },
            { 0x2B, 0x24 },
            { 0x2C, 0x10 },
            { 0x2D, 0xFF },
            { 0x2E, 0x74 },
            { 0x2F, 0x24 },
            { 0x30, 0x10 },

            // CDirectSoundBuffer::SetOutputBuffer+0x49 : pop edi
            { 0x49, 0x5F },

            // CDirectSoundBuffer::SetOutputBuffer+0x4B : retn 0x08
            { 0x4B, 0xC2 },
            { 0x4C, 0x08 },
    }
OOVPA_END;

// ******************************************************************
// * CDirectSound::SetMixBinHeadroom
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSound_SetMixBinHeadroom, 4134, 1 + 12, XRefOne)
    {

        // CDirectSound_SetMixBinHeadroom+0x41 : call [CMcpxAPU_SetMixBinHeadroom]
        XREF_ENTRY(0x42, XREF_CMcpxAPU_SetMixBinHeadroom),

            // CDirectSound_SetMixBinHeadroom+0x00 : push esi
            { 0x00, 0x56 },

            // CDirectSound_SetMixBinHeadroom+0x21 : mov eax, 0x80004005
            { 0x21, 0xB8 },
            { 0x22, 0x05 },
            { 0x23, 0x40 },
            { 0x24, 0x00 },
            { 0x25, 0x80 },

            // CDirectSound_SetMixBinHeadroom+0x34 : mov bl, [esp+0x14]
            { 0x34, 0x8A },
            { 0x35, 0x5C },
            { 0x36, 0x24 },
            { 0x37, 0x14 },

#if 0
        // CDirectSound_SetMixBinHeadroom+0x39 : mov [edx+ecx+0x__], bl
        { 0x39, 0x88 },
        { 0x3A, 0x5C },
        { 0x3B, 0x0A },
        //{ 0x3C, 0x14 }, was changed to 0x10 for 5455 and later

        // CDirectSound_SetMixBinHeadroom+0x3E : mov ecx, dword ptr [eax+0x0C]
        { 0x3E, 0x8B },
        { 0x3F, 0x48 },
        { 0x40, 0x0C },
#endif

            // CDirectSound_SetMixBinHeadroom+0x5C : retn 0x0C
            { 0x5C, 0xC2 },
            { 0x5D, 0x0C },
    }
OOVPA_END;

// ******************************************************************
// * CDirectSoundStream::SetFrequency
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetFrequency,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetFrequency),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },

    // je XXXXXXXX + 0x0B
    { 0x14, 0x74 },
    { 0x15, 0x0B },

    // jmp XXXXXXXX + 0x26
    { 0x26, 0xEB },
    { 0x27, 0x26 },

    { 0x2A, 0x24 },

    // je XXXXXXXX + 0x0B
    { 0x3E, 0x74 },
    { 0x3F, 0x0B },

    // ret 8
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetOutputBuffer
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetOutputBuffer,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetOutputBuffer),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeAngles
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeAngles,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3E, XREF_CDirectSoundVoice_SetConeAngles),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },

    { 0x30, 0x18 },
    { 0x33, 0x04 },
    { 0x37, 0x18 },

    { 0x3D, 0xE8 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetHeadroom
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetHeadroom,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetHeadroom),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CMcpxBuffer::Play(unsigned long)
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Play,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Play+0x00 : push ebx
    { 0x00, 0x53 },

    // CMcpxBuffer_Play+0x0E : cmp ebx, edi
    { 0x0E, 0x3B },
    { 0x0F, 0xDF },

    // CMcpxBuffer_Play+0x18 : test byte ptr [eax+09],0x20
    { 0x18, 0xF6 },
    { 0x19, 0x40 },
    { 0x1A, 0x09 },
    { 0x1B, 0x20 },

    // CMcpxBuffer_Play+0x1C : jz +0x09
    { 0x1C, 0x74 },
    { 0x1D, 0x09 },

    // CMcpxBuffer_Play+0x30 : test byte ptr [esi+0x12], 2
    { 0x30, 0xF6 },
    { 0x31, 0x46 },
    { 0x32, 0x12 },
    { 0x33, 0x02 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Play
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Play,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_Play+0x35 : call [CMcpxBuffer::Play]
    XREF_ENTRY(0x35, XREF_CMcpxBuffer_Play),

    // CDirectSoundBuffer_Play+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_Play+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSoundBuffer_Play+0x3D : jz +0x0B
    { 0x3D, 0x74 },
    { 0x3E, 0x0B },

    // CDirectSoundBuffer_Play+0x4E : retn 0x10
    { 0x4E, 0xC2 },
    { 0x4F, 0x10 },
    //
);

// ******************************************************************
// * CDirectSound_GetEffectData
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetEffectData,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0F, 0x00 },

    { 0x24, 0xB8 },
    { 0x25, 0x05 },
    { 0x26, 0x40 },
    { 0x27, 0x00 },
    { 0x28, 0x80 },

    { 0x29, 0xEB },
    { 0x2A, 0x2F },

    { 0x2B, 0x8B },
    { 0x2C, 0x45 },

    { 0x41, 0xE8 },

    { 0x5C, 0xC2 },
    { 0x5D, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound_CommitEffectData
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CommitEffectData,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x0C, 0x00 },

    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    { 0x26, 0xEB },
    { 0x27, 0x24 },

    { 0x28, 0x8B },
    { 0x29, 0x44 },

    { 0x32, 0x6A },
    { 0x34, 0x6A },

    { 0x36, 0xE8 },

    { 0x4D, 0xC2 },
    { 0x4E, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetDistanceFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3E, XREF_CDirectSoundVoice_SetDistanceFactor),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x3D, 0xE8 },
    { 0x48, 0x68 },
    { 0x53, 0x8B },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetDistanceFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundStream_SetDistanceFactor),

    { 0x00, 0xFF },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x09, 0xD9 },
    { 0x0C, 0xFF },
    { 0x0E, 0x24 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetRolloffFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundStream_SetRolloffFactor),

    { 0x00, 0xFF },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x09, 0xD9 },
    { 0x0C, 0xFF },
    { 0x0E, 0x24 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetDopplerFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3E, XREF_CDirectSoundVoice_SetDopplerFactor),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x3D, 0xE8 },
    { 0x48, 0x68 },
    { 0x53, 0x8B },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetDopplerFactor,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundStream_SetDopplerFactor),

    { 0x00, 0xFF },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x09, 0xD9 },
    { 0x0C, 0xFF },
    { 0x0E, 0x24 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMixBinVolumes_8
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMixBinVolumes_8,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetMixBinVolumes),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x0E, 0xB6 },
    { 0x0F, 0xF0 },
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPlayRegion
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetPlayRegion,
                         4134)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetPlayRegion+0x10 : movzx edi, al
    { 0x10, 0x0F },
    { 0x11, 0xB6 },
    { 0x12, 0xF8 },

    // CDirectSoundBuffer_SetPlayRegion+0x17 : jz +0x0B
    { 0x17, 0x74 },
    { 0x18, 0x0B },

    // CDirectSoundBuffer_SetPlayRegion+0x46 : mov esi, 0x88780032
    { 0x46, 0xBE },
    { 0x47, 0x32 },
    { 0x48, 0x00 },
    { 0x49, 0x78 },
    { 0x4A, 0x88 },
    //
);

// ******************************************************************
// * CDirectSound::EnableHeadphones
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_EnableHeadphones,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x29, 0xB8 },

    { 0x4C, 0x83 },
    { 0x4D, 0x7D },
    { 0x4E, 0x0C },
    { 0x4F, 0x00 },
    { 0x50, 0x74 },
    { 0x51, 0x07 },
    { 0x52, 0x0D },
    { 0x53, 0x00 },

    { 0x63, 0x0C },
    { 0x64, 0xE8 },
    //{ 0x82, 0xC2 }, 4242 Different length
    //{ 0x83, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundBuffer::SetFormat
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFormat,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x32, XREF_CDirectSoundVoice_SetFormat),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x12, 0x85 },
    { 0x1C, 0x15 },
    { 0x26, 0xEB },
    { 0x30, 0x10 },
    { 0x3A, 0x74 },
    { 0x47, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetFormat
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetFormat,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x36, XREF_CDirectSoundVoice_SetFormat),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x35, 0xE8 },
    { 0x40, 0x68 },
    { 0x4B, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::PlayEx
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_PlayEx,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3D, XREF_CMcpxBuffer_Play_Ex),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x16, 0x68 },
    { 0x22, 0x05 },
    { 0x2E, 0x20 },
    { 0x3A, 0x24 },
    { 0x46, 0x0B },
    { 0x52, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundBuffer::StopEx
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_StopEx,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3D, XREF_CMcpxBuffer_Stop_Ex),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x16, 0x68 },
    { 0x22, 0x05 },
    { 0x2E, 0x20 },
    { 0x3A, 0x24 },
    { 0x46, 0x0B },
    { 0x52, 0x8B },
    //
);

// ******************************************************************
// * DirectSoundCreateBuffer
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(DirectSoundCreateBuffer,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundCreateBuffer+0x2E : call [CDirectSound::CreateSoundBuffer]
    XREF_ENTRY(0x2F, XREF_CDirectSound_CreateSoundBuffer),

    // DirectSoundCreateBuffer+0x04 : and [ebp-0x04], 0
    { 0x04, 0x83 },
    { 0x05, 0x65 },
    { 0x06, 0xFC },

    // DirectSoundCreateBuffer+0x08 : push ebx; push esi; push edi
    { 0x08, 0x53 },
    { 0x09, 0x56 },
    { 0x0A, 0x57 },

    // DirectSoundCreateBuffer+0x3C : call dword ptr [eax+8]
    { 0x3C, 0xFF },
    { 0x3D, 0x50 },
    { 0x3E, 0x08 },

    // DirectSoundCreateBuffer+0x54 : retn 0x08
    { 0x54, 0xC2 },
    { 0x55, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::FlushEx
// ******************************************************************
// Generic OOVPA as of 4134 and newer (introduction)
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_FlushEx,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x42, XREF_CMcpxStream_Stop_Ex),

    //XREF_ENTRY(0x4C, XREF_CMcpxStream_Flush), // valid for 4134 - ?
    //XREF_ENTRY(0x49, XREF_CMcpxStream_Flush), // valid for 5028 and newer

    { 0x00, 0x55 },

    // CDirectSoundStream_FlushEx+0x54 : cmp [ebp+14h],0
    { 0x2B, 0x83 },
    { 0x2C, 0x7D },
    { 0x2D, 0x14 },
    { 0x2E, 0x00 },

    // CDirectSoundStream_FlushEx+0x54 : push [ebp+0Ch]
    { 0x3E, 0xFF },
    { 0x3F, 0x75 },

    // CDirectSoundStream_FlushEx+0x54 : call CMcpxStream::Stop_Ex
    { 0x41, 0xE8 },

    //
);

// ******************************************************************
// * IDirectSoundStream::FlushEx
// ******************************************************************
// Generic OOVPA as of 4134 and newer (introduction)
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_FlushEx,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundStream_FlushEx),

    { 0x01, 0x74 },
    { 0x04, 0xFF },
    { 0x07, 0x10 },
    { 0x0A, 0x24 },
    { 0x0D, 0x74 },
    { 0x10, 0xE8 },
    { 0x15, 0xC2 },
    { 0x16, 0x10 },
    //
);

// ******************************************************************
// * XAudioDownloadEffectsImage
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(XAudioDownloadEffectsImage,
                         4134)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x55),

    OV_MATCH(0x0B, 0x33, 0xFF, 0x89, 0x5D, 0xFC, 0x33, 0xF6, 0xE8),

    OV_MATCH(0x41, 0x83),
    OV_MATCH(0x53, 0xE8),
    OV_MATCH(0x6A, 0x8B),
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetMixBins
// ******************************************************************
// Generic OOVPA as of 4134? and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetMixBins,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetMixBins+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxVoiceClient_SetMixBins+0x24 : lea eax, [ebp-4]
    { 0x24, 0x8D },
    { 0x25, 0x45 },
    { 0x26, 0xFC },

    // CMcpxVoiceClient_SetMixBins+0x2F : lea eax, [esi-0x30]
    { 0x2F, 0x8D },
    { 0x30, 0x45 },
    { 0x31, 0xD0 },

    // CMcpxVoiceClient_SetMixBins+0x5A : mov ds:[0xFE8202F8], eax
    { 0x5E, 0xA3 },
    { 0x5F, 0xF8 },
    { 0x60, 0x02 },
    { 0x61, 0x82 },
    { 0x62, 0xFE },

    // CMcpxVoiceClient_SetMixBins+0xBF : leave; retn
    { 0xBF, 0xC9 },
    { 0xC0, 0xC3 },
    //
);

// ******************************************************************
// * CMcpxStream::Stop
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Stop,
                         4134)
OOVPA_SIG_MATCH(

    // calls to CIrql_Raise, CIrql_Lower, CMcpxVoiceClient_ReleaseVoice, CMcpxVoiceClient_DeactivateVoice

    // CMcpxStream_Stop+0x00 : push ebp; mov ebp,esp
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },

    // Offset is unique for this asm code.
    // CMcpxStream_Stop+0x30 : test [ebp+8],2
    { 0x30, 0xF6 },
    { 0x31, 0x45 },
    { 0x32, 0x08 },
    { 0x33, 0x02 },
    //
);

// ******************************************************************
// * CMcpxStream::Stop_Ex
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Stop_Ex,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CMcpxStream_Stop_Ex+0x2A : call [CMcpxBuffer::Play]
    XREF_ENTRY(0x2B, XREF_CMcpxStream_Stop),

    // CMcpxStream_Stop_Ex+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxStream_Stop_Ex+0x11 : push [ebp+arg_8]
    { 0x11, 0xFF },
    { 0x12, 0x75 },
    { 0x13, 0x10 },

    // CMcpxStream_Stop_Ex+0x23 : jnz +0x0C
    { 0x23, 0x75 },
    { 0x24, 0x0C },

    // CMcpxStream_Stop_Ex+0x36 : push esi
    { 0x36, 0xC2 },
    { 0x37, 0x0C },
    //
);

// ******************************************************************
// * CDirectSound::DoWork
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_XREF(CDirectSound_DoWork, 4134, 1 + 10, XRefOne)
    {

        // CDirectSound_DoWork+0x19 : call [CMcpxAPU::ServiceDeferredCommandsLow]
        XREF_ENTRY(0x1A, XREF_CMcpxAPU_ServiceDeferredCommandsLow),

            // CDirectSound_DoWork+0x0D : mov esi, al
            { 0x0D, 0x0F },
            { 0x0E, 0xB6 },
            { 0x0F, 0xF0 },

            // The rest are identical to 4039 OOVPA with one offset forward.

            // CDirectSound_DoWork+0x10 : jnz +0x0C
            { 0x10, 0x75 },
            { 0x11, 0x0C },

#if 0 // disabled to reduce scan size \
    // CDirectSound_DoWork+0x12 : mov eax, [esp+4+arg_0]
        { 0x12, 0x8B },
        { 0x13, 0x44 },
        { 0x14, 0x24 },
        { 0x15, 0x08 },
#endif

            // CDirectSound_DoWork+0x16 : mov ecx, [eax+0Ch]
            { 0x16, 0x8B },
            { 0x17, 0x48 },
            { 0x18, 0x0C },

            // CDirectSound_DoWork+0x2E : retn 0x04
            { 0x2E, 0xC2 },
            { 0x2F, 0x04 },
    }
OOVPA_END;

// ******************************************************************
// * DirectSound::CMcpxAPU::ServiceDeferredCommandsLow
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_ServiceDeferredCommandsLow,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxAPU_ServiceDeferredCommandsLow+0x00: push ebp; mov ebp,esp
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },

    // CMcpxAPU_ServiceDeferredCommandsLow+0x17: lea ecx,[ebp-10]
    { 0x17, 0x8D },
    { 0x18, 0x4D },
    { 0x19, 0xF0 },

    // CMcpxAPU_ServiceDeferredCommandsLow+0x1A: mov [ebp-08],eax
    { 0x1A, 0x89 },
    { 0x1B, 0x45 },
    { 0x1C, 0xF8 },

    // Generic support over multiple revisions end at offset 0x3A
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Commit3dSettings_0,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x3D : cmp edi, 0x02
    { 0x3D, 0x83 },
    { 0x3E, 0xFF },
    { 0x3F, 0x02 },

    // CMcpxVoiceClient::Commit3dSettings+0x59 : mov e__,[e__+0x000000B4]
    { 0x59, 0x8B },
    //{ 0x5A, 0x__ },
    { 0x5B, 0xB4 },
    { 0x5C, 0x00 },
    //{ 0x5D, 0x00 },
    { 0x5E, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x66 : mov eax,[eax+0x000000B4]
    { 0x66, 0x8B },
    //{ 0x67, 0x80 },
    { 0x68, 0xB4 },
    { 0x69, 0x00 },
    //{ 0x6A, 0x00 },
    { 0x6B, 0x00 },

    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_CommitDeferredSettings,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::CommitDeferredSettings+0x20 : call [CMcpxVoiceClient::Commit3dSettings]
    XREF_ENTRY(0x21, XREF_CMcpxVoiceClient_Commit3dSettings),

    { 0x00, 0x56 },

    // CDirectSoundVoice::CommitDeferredSettings+0x0E : mov ecx,[ecx+0x000000A4]
    { 0x0E, 0x8B },
    { 0x0F, 0x89 },
    { 0x10, 0xA4 },
    { 0x11, 0x00 },
    //{ 0x12, 0x00 },
    //{ 0x13, 0x00 },

    // CDirectSoundVoice::CommitDeferredSettings+0x14 : mov eax,[eax+0x000000B4]
    { 0x14, 0x8B },
    { 0x15, 0x80 },
    { 0x16, 0xB4 },
    { 0x17, 0x00 },
    //{ 0x18, 0x00 },
    //{ 0x19, 0x00 },

    { 0x36, 0xC2 },
    { 0x37, 0x04 },

    //
);

// ******************************************************************
// * CMcpxVoiceClient_SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetPitch,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient_SetPitch+0x22 : lea edi, [esi+0x44]
    { 0x22, 0x8D },
    { 0x23, 0x7E },
    { 0x24, 0x44 },

    // CMcpxVoiceClient_SetPitch+0x4E : lea ecx,[eax+eax]
    { 0x4E, 0x8D },
    { 0x4F, 0x0C },
    { 0x50, 0x00 },

    // CMcpxVoiceClient_SetPitch+0x64 : lea eax,[esi+0x0C]
    { 0x64, 0x8D },
    { 0x65, 0x46 },
    { 0x66, 0x0C },
    //
);

// ******************************************************************
// * CMcpxBuffer::SetBufferData
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_SetBufferData,
                         4134)
OOVPA_SIG_MATCH(

    // CMcpxBuffer::SetBufferData+0x00 : mov edx,[ecx+0x000000XX]
    { 0x00, 0x8B },
    { 0x01, 0x91 },

    // CMcpxBuffer::SetBufferData+0x06 : xor eax, eax
    { 0x06, 0x33 },
    { 0x07, 0xC0 },

    // This asm code is unique.
    // CMcpxBuffer::SetBufferData+0x0E : test byte [edx+0x0A], 4
    { 0x0E, 0xF6 },
    { 0x0F, 0x42 },
    //{ 0x10, 0x0A },
    { 0x11, 0x04 },

    // CMcpxBuffer::SetBufferData+0x14 : jmp
    { 0x14, 0xE9 },

    // CMcpxBuffer::SetBufferData+0x19 : ret
    { 0x19, 0xC3 },
    //
);

// ******************************************************************
// * DirectSoundOverrideSpeakerConfig
// ******************************************************************
// Generic OOVPA as of 4134 and newer
OOVPA_SIG_HEADER_XREF(DirectSoundOverrideSpeakerConfig,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundOverrideSpeakerConfig+0x00 : call [DirectSoundEnterCriticalSection]
    XREF_ENTRY(0x01, XREF_DirectSoundEnterCriticalSection),

    // DirectSoundOverrideSpeakerConfig+0x00 : call [DirectSoundEnterCriticalSection]
    OV_MATCH(0x00, 0xE8),

    // DirectSoundOverrideSpeakerConfig+0x19 : and eax,0x0000FFFF
    OV_MATCH(0x19, 0x25, 0xFF, 0xFF, 0x00, 0x00),

    // DirectSoundOverrideSpeakerConfig+0x32 : retn 0x0004
    OV_MATCH(0x32, 0xC2, 0x04),
    //
);
