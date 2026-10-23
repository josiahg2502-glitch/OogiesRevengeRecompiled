// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * DirectSoundEnterCriticalSection
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(DirectSoundEnterCriticalSection,
                         3911)
OOVPA_SIG_MATCH(

    { 0x02, 0xB6 },
    { 0x06, 0x00 },
    { 0x0A, 0x74 },
    { 0x0E, 0xC3 },
    { 0x14, 0xFF },
    { 0x1A, 0x33 },
    { 0x1B, 0xC0 },
    //
);

// ******************************************************************
// * DirectSoundCreate
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DirectSoundCreate,
                         3911)
OOVPA_SIG_MATCH(

    // DirectSoundCreate+0x23 : add eax, 8
    { 0x23, 0x83 },
    { 0x24, 0xC0 },
    { 0x25, 0x08 },

    // DirectSoundCreate+0x34 : push 0x1C
    { 0x34, 0x6A },
    { 0x35, 0x1C },

    // DirectSoundCreate+0x75 : sbb eax, eax
    { 0x75, 0x1B },
    { 0x76, 0xC0 },

    // DirectSoundCreate+0x9B : retn 0x0C
    { 0x9B, 0xC2 },
    { 0x9C, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU_ServiceDeferredCommandsLow
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_ServiceDeferredCommandsLow,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_ServiceDeferredCommandsLow+0x00 : push ebx; push ebp
    OV_MATCH(0x00, 0x53, 0x55),

    // CMcpxAPU_ServiceDeferredCommandsLow+0x06 : lea edi, [ebx+0x664]
    OV_MATCH(0x0C, 0xBD, 0x00, 0x02, 0x00, 0x00),

    // CMcpxAPU_ServiceDeferredCommandsLow+0x20 : mov eax, [ecx]
    OV_MATCH(0x20, 0x8B, 0x01),

    // CMcpxAPU_ServiceDeferredCommandsLow+0x33 : add edi, 4; dec ebp
    OV_MATCH(0x33, 0x83, 0xC7, 0x04, 0x4D),

    //
);

// ******************************************************************
// * CDirectSound_DoWork
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_DoWork,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_DoWork+0x0F : call [CMcpxAPU_ServiceDeferredCommandsLow]
    XREF_ENTRY(0x10, XREF_CMcpxAPU_ServiceDeferredCommandsLow),

    // CDirectSound_DoWork+0x08 : mov eax, [esp+0x08]
    { 0x08, 0x8B },
    { 0x09, 0x44 },
    { 0x0A, 0x24 },
    { 0x0B, 0x08 },

    // CDirectSound_DoWork+0x17 : jz +0x0B
    { 0x17, 0x74 },
    { 0x18, 0x0B },

    // CDirectSound_DoWork+0x24 : retn 0x04
    { 0x24, 0xC2 },
    { 0x25, 0x04 },
    //
);

// ******************************************************************
// * DirectSoundDoWork
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundDoWork,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundDoWork+0x12 : call [CDirectSound_DoWork]
    XREF_ENTRY(0x13, XREF_CDirectSound_DoWork),

    // DirectSoundDoWork+0x0D : test eax, eax;jz +0x06
    { 0x0D, 0x85 },
    { 0x0E, 0xC0 },
    { 0x0F, 0x74 },
    { 0x10, 0x06 },

    // DirectSoundDoWork+0x19 : pop esi; jz +0x0B
    { 0x19, 0x5E },
    { 0x1A, 0x74 },
    { 0x1B, 0x0B },

    // DirectSoundDoWork+0x27 : retn
    { 0x27, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSound::CreateSoundBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CreateSoundBuffer,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_CreateSoundBuffer+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_CreateSoundBuffer+0x2D : and esi, 0x7FF8FFF2
    { 0x2D, 0x81 },
    { 0x2E, 0xE6 },
    { 0x2F, 0xF2 },
    { 0x30, 0xFF },
    { 0x31, 0xF8 },
    { 0x32, 0x7F },

    // CDirectSound_CreateSoundBuffer+0x33 : add esi, 0x8007000E
    { 0x33, 0x81 },
    { 0x34, 0xC6 },
    { 0x35, 0x0E },
    { 0x36, 0x00 },
    { 0x37, 0x07 },
    { 0x38, 0x80 },

    // CDirectSound_CreateSoundBuffer+0x3C : js +0x21
    { 0x3C, 0x78 },
    { 0x3D, 0x21 },

    // CDirectSound_CreateSoundBuffer+0x7D : retn 0x10
    { 0x7D, 0xC2 },
    { 0x7E, 0x10 },
    //
);

// ******************************************************************
// * IDirectSound_CreateSoundBuffer
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_CreateSoundBuffer,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_CreateSoundBuffer+0x1C : call [CDirectSound::CreateSoundBuffer]
    XREF_ENTRY(0x1D, XREF_CDirectSound_CreateSoundBuffer),

    // IDirectSound_CreateSoundBuffer+0x04 : mov eax, [esp+8]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSound_CreateSoundBuffer+0x12 : add eax, 0xFFFFFFF8
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xF8 },

    // IDirectSound_CreateSoundBuffer+0x17 : sbb ecx, ecx
    { 0x17, 0x1B },
    { 0x18, 0xC9 },

    // IDirectSound_CreateSoundBuffer+0x21 : retn 0x10
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * DirectSoundCreateBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundCreateBuffer,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundCreateBuffer+0x27 : call [IDirectSound::CreateSoundBuffer]
    XREF_ENTRY(0x28, XREF_IDirectSound_CreateSoundBuffer),

    // DirectSoundCreateBuffer+0x04 : and [ebp-0x04], 0
    { 0x04, 0x83 },
    { 0x05, 0x65 },
    { 0x06, 0xFC },

    { 0x20, 0x0C },
    { 0x23, 0x08 },
    { 0x26, 0xFC },

    // DirectSoundCreateBuffer+0x2E : lea eax, [ebp-0x04]
    { 0x2E, 0x8D },
    { 0x2F, 0x45 },
    { 0x30, 0xFC },

    // DirectSoundCreateBuffer+0x3B : retn 0x08
    { 0x3B, 0xC2 },
    { 0x3C, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound::CreateSoundStream
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CreateSoundStream,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_CreateSoundStream+0x2D : and esi, 0x7FF8FFF2
    { 0x2D, 0x81 },
    { 0x2E, 0xE6 },
    { 0x2F, 0xF2 },
    { 0x30, 0xFF },
    { 0x31, 0xF8 },
    { 0x32, 0x7F },

    // CDirectSound_CreateSoundStream+0x33 : add esi, 0x8007000E
    { 0x33, 0x81 },
    { 0x34, 0xC6 },
    { 0x35, 0x0E },
    { 0x36, 0x00 },
    { 0x37, 0x07 },
    { 0x38, 0x80 },

    // CDirectSound_CreateSoundStream+0x3C : js +0x16
    { 0x3C, 0x78 },
    { 0x3D, 0x16 },

    // CDirectSound_CreateSoundStream+0x72 : retn 0x10
    { 0x72, 0xC2 },
    { 0x73, 0x10 },
    //
);

// ******************************************************************
// * IDirectSound_CreateSoundStream
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_CreateSoundStream,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_CreateSoundStream+0x1C : call [CDirectSound::CreateSoundStream]
    XREF_ENTRY(0x1D, XREF_CDirectSound_CreateSoundStream),

    // IDirectSound_CreateSoundStream+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSound_CreateSoundStream+0x12 : and eax, 0xFFFFFFF8
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xF8 },

    // IDirectSound_CreateSoundStream+0x21 : retn 0x10
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * DirectSoundCreateStream
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundCreateStream,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundCreateStream+0x27 : call [IDirectSound::CreateSoundStream]
    XREF_ENTRY(0x28, XREF_IDirectSound_CreateSoundStream),

    // DirectSoundCreateStream+0x04 : and [ebp-0x04], 0
    { 0x04, 0x83 },
    { 0x05, 0x65 },
    { 0x06, 0xFC },

    { 0x20, 0x0C },
    { 0x23, 0x08 },
    { 0x26, 0xFC },

    // DirectSoundCreateStream+0x2E : lea eax, [ebp-0x04]
    { 0x2E, 0x8D },
    { 0x2F, 0x45 },
    { 0x30, 0xFC },

    // DirectSoundCreateStream+0x3B : retn 0x08
    { 0x3B, 0xC2 },
    { 0x3C, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_AddRef
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(IDirectSoundBuffer_AddRef,
                         3911)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_AddRef+0x04 : lea ecx, [eax-0x1C]
    { 0x04, 0x8D },
    { 0x05, 0x48 },
    { 0x06, 0xE4 },

    // IDirectSoundBuffer_AddRef+0x07 : neg eax; sbb eax, eax
    { 0x07, 0xF7 },
    { 0x08, 0xD8 },
    { 0x09, 0x1B },
    { 0x0A, 0xC0 },

    // IDirectSoundBuffer_AddRef+0x10 : call dword ptr [ecx+0x04]
    { 0x10, 0xFF },
    { 0x11, 0x51 },
    { 0x12, 0x04 },

    // IDirectSoundBuffer_AddRef+0x13 : ret 4
    { 0x13, 0xC2 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_Release
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(IDirectSoundBuffer_Release,
                         3911)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_Release+0x04 : lea ecx, [eax-0x1C]
    { 0x04, 0x8D },
    { 0x05, 0x48 },
    { 0x06, 0xE4 },

    // IDirectSoundBuffer_Release+0x07 : neg eax; sbb eax, eax
    { 0x07, 0xF7 },
    { 0x08, 0xD8 },
    { 0x09, 0x1B },
    { 0x0A, 0xC0 },

    // IDirectSoundBuffer_Release+0x10 : call dword ptr [ecx+0x08]
    { 0x10, 0xFF },
    { 0x11, 0x51 },
    { 0x12, 0x08 },

    // IDirectSoundBuffer_Release+0x13 : ret 4
    { 0x13, 0xC2 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_Unlock
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(IDirectSoundBuffer_Unlock,
                         3911)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_Unlock+0x00 : xor eax, eax
    { 0x00, 0x33 },
    { 0x01, 0xC0 },

    // IDirectSoundBuffer_Unlock+0x02 : ret 14h
    { 0x02, 0xC2 },
    { 0x03, 0x14 },
    { 0x04, 0x00 },
    //
);

#if 0 // Cannot be used since this OOVPA does produce false detection. Use it only for as a model understanding.
// ******************************************************************
// * IDirectSound_SetCooperativeLevel
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(IDirectSound_SetCooperativeLevel,
                         3911)
OOVPA_SIG_MATCH(

    // IDirectSound_SetCooperativeLevel+0x00 : xor eax, eax
    { 0x00, 0x33 },
    { 0x01, 0xC0 },

    // IDirectSound_SetCooperativeLevel+0x02 : ret 0Ch
    { 0x02, 0xC2 },
    { 0x03, 0x0C },
    { 0x04, 0x00 }
    //
);
#endif

// ******************************************************************
// * CMcpxVoiceClient_SetVolume
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetVolume,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetVolume+0x26 : mov ecx, [esi+0xE0]
    { 0x26, 0x8B },
    { 0x27, 0x8E },
    { 0x28, 0xE0 },
    { 0x29, 0x00 },

    // CMcpxVoiceClient_SetVolume+0x2F : movzx ecx, word ptr [ecx+2]
    { 0x2F, 0x0F },
    { 0x30, 0xB7 },
    { 0x31, 0x49 },
    { 0x32, 0x02 },

    // CMcpxVoiceClient_SetVolume+0x35 : dec ecx; sar ecx, 1
    { 0x35, 0x49 },
    { 0x36, 0xD1 },
    { 0x37, 0xF9 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1E, XREF_CMcpxVoiceClient_SetVolume),

    //CDirectSoundVoice_SetVolume+0x00 : push esi
    { 0x00, 0x56 },

    //CDirectSoundVoice_SetVolume+0x11 : mov eax, dword ptr [ecx+18h]
    { 0x11, 0x8B },
    { 0x12, 0x41 },
    { 0x13, 0x18 },

    //CDirectSoundVoice_SetVolume+0x1A : mov ecx, dword ptr [ecx+14h]
    { 0x1A, 0x8B },
    { 0x1B, 0x49 },
    { 0x1C, 0x14 },

    //CDirectSoundVoice_SetVolume+0x1D : call CMcpxVoiceClient_SetVolume
    { 0x1D, 0xE8 },

    //CDirectSoundVoice_SetVolume+0x37 : ret 8
    { 0x37, 0xC2 },
    { 0x38, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetVolume+0x15 : call [CDirectSoundVoice_SetVolume]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetVolume),

    // IDirectSoundBuffer_SetVolume+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetVolume+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetVolume+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CMcpxBuffer_Stop
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Stop,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Stop+0x08 : or eax, dword ptr [esp+10h]
    { 0x08, 0x0B },
    { 0x09, 0x44 },
    { 0x0A, 0x24 },
    { 0x0B, 0x10 },

    // CMcpxBuffer_Stop+0x19 : push 3
    { 0x19, 0x6A },
    { 0x1A, 0x03 },

    // CMcpxBuffer_Stop+0x24 : test [esp+10h], 2
    { 0x24, 0x8B },
    { 0x25, 0xCE },

    // CMcpxBuffer_Stop+0x31 : retn 0x08
    { 0x31, 0xC2 },
    { 0x32, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_StopEx
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_StopEx,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x39, XREF_CMcpxBuffer_Stop),

    // CDirectSoundBuffer_StopEx+0x0F : test al, 3
    { 0x0F, 0xA8 },
    { 0x10, 0x03 },

    // CDirectSoundBuffer_StopEx+0x15 : and eax, 1
    { 0x15, 0x83 },
    { 0x16, 0xE0 },
    { 0x17, 0x01 },

    // CDirectSoundBuffer_StopEx+0x32 : push dword ptr [ebp+0Ch]
    { 0x32, 0xFF },
    { 0x33, 0x75 },
    { 0x34, 0x0C },

    // CDirectSoundBuffer_StopEx+0x53 : retn 0x10
    { 0x53, 0xC2 },
    { 0x54, 0x10 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_StopEx
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_StopEx,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_StopEx+0x1D : call [CDirectSoundBuffer::StopEx]
    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_StopEx),

    { 0x03, 0x10 },
    { 0x08, 0xFF },
    { 0x0D, 0xC8 },
    { 0x12, 0x83 },
    { 0x17, 0x1B },
    { 0x1C, 0xE8 },
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Stop
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Stop,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x14, XREF_CDirectSoundBuffer_StopEx),

    // CDirectSoundBuffer_Stop+0x07 : mov eax, 0x80004005
    { 0x07, 0x6A },
    { 0x08, 0x00 },
    { 0x09, 0x6A },
    { 0x0A, 0x00 },
    { 0x0B, 0x6A },
    { 0x0C, 0x00 },

    // CDirectSoundBuffer_Stop+0x1A : mov ebx, eax; jz +0x0B
    { 0x1A, 0x8B },
    { 0x1B, 0xD8 },
    { 0x1C, 0x74 },
    { 0x1D, 0x0B },

    // CDirectSoundBuffer_Stop+0x2D : retn 0x04
    { 0x2D, 0xC2 },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_Stop
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_Stop,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_Stop+0x11 : call [CDirectSoundBuffer::Stop]
    XREF_ENTRY(0x11, XREF_CDirectSoundBuffer_Stop),

    // IDirectSoundBuffer_Stop+0x00 : mov eax, [esp+arg_0]
    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // IDirectSoundBuffer_Stop+0x04 : mov ecx, eax
    { 0x04, 0x8B },
    { 0x05, 0xC8 },

    // IDirectSoundBuffer_Stop+0x06 : add eax, 0x0FFFFFFE4
    { 0x06, 0x83 },
    { 0x07, 0xC0 },
    { 0x08, 0xE4 },

    // IDirectSoundBuffer_Stop+0x15 : retn 4
    { 0x16, 0x04 },
    { 0x17, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetLoopRegion
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetLoopRegion,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetLoopRegion+0x20 : cmp edx, [ecx+0x54]
    { 0x20, 0x3B },
    { 0x21, 0x51 },
    { 0x22, 0x54 },

    // CDirectSoundBuffer_SetLoopRegion+0x2C : mov ecx, [esi+0x20]
    { 0x2C, 0x8B },
    { 0x2D, 0x4E },
    { 0x2E, 0x20 },

    // CDirectSoundBuffer_SetLoopRegion+0x38 : jz +0x0B
    { 0x38, 0x74 },
    { 0x39, 0x0B },

    // CDirectSoundBuffer_SetLoopRegion+0x4A : retn 0x0C
    { 0x4A, 0xC2 },
    { 0x4B, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetLoopRegion
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetLoopRegion,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetLoopRegion+0x19 : call [CDirectSoundBuffer_SetLoopRegion]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetLoopRegion),

    // IDirectSoundBuffer_SetLoopRegion+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetLoopRegion+0x0E : add eax, 0xFFFFFFE4
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_SetLoopRegion+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CMcpxBuffer_Play
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Play,
                         3911)
OOVPA_SIG_MATCH(

    { 0x06, 0x56 },
    { 0x0E, 0xF1 },
    { 0x18, 0x75 },
    { 0x19, 0x08 },
    { 0x1A, 0x6A },
    { 0x1B, 0x02 },
    { 0x26, 0x75 },
    { 0x2F, 0x8B },
    { 0x36, 0xC2 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_PlayEx
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_PlayEx,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x21, XREF_CMcpxBuffer_Play),

    { 0x08, 0xF0 },

    { 0x13, 0x24 },
    { 0x17, 0x24 },
    { 0x1B, 0x24 },

    { 0x25, 0x85 },
    { 0x27, 0x8B },

    { 0x3A, 0xC2 },
    { 0x3B, 0x10 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Play
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Play,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x16, XREF_CDirectSoundBuffer_PlayEx),

    { 0x07, 0xFF },
    { 0x0C, 0xF0 },
    { 0x13, 0x24 },
    { 0x1A, 0x85 },
    { 0x25, 0xFF },
    { 0x2B, 0x8B },
    { 0x2F, 0xC2 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_Play
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_Play,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_Play+0x1D : call CDirectSoundBuffer::Play
    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_Play),

    // IDirectSoundBuffer_Play+0x00 : push [esp+0x10]
    { 0x00, 0xFF },
    { 0x01, 0x74 },
    { 0x02, 0x24 },
    { 0x03, 0x10 },

    // IDirectSoundBuffer_Play+0x04 : mov eax, [esp+4+arg_0]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_Play+0x12 : and eax, [0xFFFFFFE4]
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xE4 },

    // IDirectSoundBuffer_Play+0x17 : sbb ecx, ecx
    { 0x17, 0x1B },
    { 0x18, 0xC9 },

    // IDirectSoundBuffer_Play+0x21 : retn 0x10
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_PlayEx
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_PlayEx,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_PlayEx),

    { 0x03, 0x10 },
    { 0x08, 0xFF },
    { 0x0D, 0xC8 },
    { 0x12, 0x83 },
    { 0x17, 0x1B },
    { 0x1C, 0xE8 },
    { 0x21, 0xC2 },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_GetCurrentPosition,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_GetCurrentPosition+0x12 : mov eax, [esi+XX]
    { 0x12, 0x8B },
    { 0x13, 0x46 },
    //{ 0x14, 0x18 }, //3911 has 0x18 while 3936 has 0x08

    // CMcpxBuffer_GetCurrentPosition+0x15 : and eax, 3
    { 0x15, 0x83 },
    { 0x16, 0xE0 },
    { 0x17, 0x03 },

    // CMcpxBuffer_GetCurrentPosition+0x18 : cmp al, 3
    { 0x18, 0x3C },
    { 0x19, 0x03 },

    // CMcpxBuffer_GetCurrentPosition+0x1A : jnz +0x79
    { 0x1A, 0x75 },
    { 0x1B, 0x79 },

    // CMcpxBuffer_GetCurrentPosition+0x8E : div dword ptr [ecx+0x4C]
    { 0x8E, 0xF7 },
    { 0x8F, 0x71 },
    { 0x90, 0x4C },

    // CMcpxBuffer_GetCurrentPosition+0xC8 : retn 0x08
    { 0xC8, 0xC2 },
    { 0xC9, 0x08 },
    { 0xCA, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetCurrentPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_GetCurrentPosition+0x19 : call [CMcpxBuffer::GetCurrentPosition]
    XREF_ENTRY(0x19, XREF_CMcpxBuffer_GetCurrentPosition),

    // CDirectSoundBuffer_GetCurrentPosition+0x0D : mov eax, [esp+0x10]
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x10 },

    // CDirectSoundBuffer_GetCurrentPosition+0x21 : jz +0x0B
    { 0x21, 0x74 },
    { 0x22, 0x0B },

    // CDirectSoundBuffer_GetCurrentPosition+0x32 : retn 0x0C
    { 0x32, 0xC2 },
    { 0x33, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_GetCurrentPosition
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_GetCurrentPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_GetCurrentPosition+0x19 : call [CDirectSoundBuffer::GetCurrentPosition]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_GetCurrentPosition),

    // IDirectSoundBuffer_GetCurrentPosition+0x0E : add eax, 0xFFFFFFE4
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_GetCurrentPosition+0x13 : sbb ecx, ecx
    { 0x13, 0x1B },
    { 0x14, 0xC9 },

    // IDirectSoundBuffer_GetCurrentPosition+0x15 : and ecx, eax
    { 0x15, 0x23 },
    { 0x16, 0xC8 },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_GetStatus,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_GetStatus+0x10 : mov eax, [ebp+0x08]
    { 0x10, 0x8B },
    { 0x11, 0x45 },
    { 0x12, 0x08 },

    // CMcpxBuffer_GetStatus+0x16 : xor ecx, ecx; inc ecx
    { 0x16, 0x33 },
    { 0x17, 0xC9 },
    { 0x18, 0x41 },

    // CMcpxBuffer_GetStatus+0x1C : jz +0x17
    { 0x1C, 0x74 },
    { 0x1D, 0x17 },

    // CMcpxBuffer_GetStatus+0x2F : mov [eax], 5
    { 0x2F, 0xC7 },
    { 0x30, 0x00 },
    { 0x31, 0x05 },

    // CMcpxBuffer_GetStatus+0x48 : retn 0x04
    { 0x48, 0xC2 },
    { 0x49, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetStatus,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_GetStatus+0x15 : call [CMcpxBuffer::GetStatus]
    XREF_ENTRY(0x15, XREF_CMcpxBuffer_GetStatus),

    // CDirectSoundBuffer_GetStatus+0x07 : push [esp+0x10]
    { 0x07, 0xFF },
    { 0x08, 0x74 },
    { 0x09, 0x24 },
    { 0x0A, 0x10 },

    // CDirectSoundBuffer_GetStatus+0x11 : mov ecx, [eax+0x20]
    { 0x11, 0x8B },
    { 0x12, 0x48 },
    { 0x13, 0x20 },

    // CDirectSoundBuffer_GetStatus+0x2E : retn 0x08
    { 0x2E, 0xC2 },
    { 0x2F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_GetStatus
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_GetStatus,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_GetStatus+0x15 : call [CDirectSoundBuffer::GetStatus]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_GetStatus),

    // IDirectSoundBuffer_GetStatus+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_GetStatus+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_GetStatus+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetFilter,
                         3911)
OOVPA_SIG_MATCH(

    { 0x0E, 0xE8 },
    { 0x1F, 0x6A },

    { 0x73, 0x00 },
    { 0x74, 0xF6 },
    { 0x75, 0x47 },
    { 0x76, 0x0C },
    { 0x77, 0x10 },
    { 0x78, 0x8B },
    { 0x79, 0x7D },
    { 0x7A, 0xE0 },

    { 0xA6, 0x8B },
    { 0xA7, 0xE0 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetFilter,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetFilter),

    { 0x01, 0x57 },
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x10 },
    { 0x11, 0x8B },
    { 0x12, 0x48 },
    { 0x2E, 0xC2 },
    { 0x2F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetFilter,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetFilter+0x15 : call [CDirectSoundVoice_SetFilter]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetFilter),

    // IDirectSoundBuffer_SetFilter+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetFilter+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetFilter+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetLFO,
                         3911)
OOVPA_SIG_MATCH(

    { 0x10, 0x8B },
    { 0x21, 0xEB },

    { 0x7D, 0x75 },
    { 0x7E, 0x28 },
    { 0x7F, 0x39 },
    { 0x80, 0x05 },
    { 0x81, 0x10 },
    { 0x82, 0x00 },
    { 0x83, 0x82 },
    { 0x84, 0xFE },

    { 0xA1, 0x89 },
    { 0xB7, 0x6C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetLFO,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetLFO),

    { 0x01, 0x57 },
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x10 },
    { 0x11, 0x8B },
    { 0x12, 0x48 },

    { 0x2E, 0xC2 },
    { 0x2F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetLFO,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetLFO),

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
// * CMcpxVoiceClient::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetEG,
                         3911)
OOVPA_SIG_MATCH(

    { 0x10, 0x8B },
    { 0x21, 0xEB },

    { 0x6B, 0x82 },
    { 0x6C, 0xFE },

    { 0x95, 0x8B },
    { 0x96, 0x96 },
    { 0x97, 0x8C },
    { 0x98, 0x00 },
    { 0x99, 0x00 },
    { 0x9A, 0x00 },
    { 0x9B, 0x89 },
    { 0x9C, 0x15 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetEG,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetEG),

    { 0x01, 0x57 },
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x10 },
    { 0x11, 0x8B },
    { 0x12, 0x48 },
    { 0x2E, 0xC2 },
    { 0x2F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetEG,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetEG),

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
// * IDirectSoundBuffer_SetOutputBuffer
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetOutputBuffer,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetOutputBuffer),

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
// * CDirectSoundVoice::SetMixBinVolumes
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMixBinVolumes_12,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x54, XREF_CMcpxVoiceClient_SetVolume),

    { 0x0D, 0x65 },
    { 0x1C, 0x53 },
    { 0x2B, 0xC0 },
    { 0x3A, 0xC7 },
    { 0x49, 0xFC },
    { 0x58, 0x83 },
    { 0x67, 0x15 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMixBinVolumes_12
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMixBinVolumes_12,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSoundVoice_SetMixBinVolumes),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0xFF },
    { 0x0E, 0x83 },
    { 0x12, 0xD9 },
    { 0x16, 0xC8 },
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetMixBinVolumes
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMixBinVolumes_12,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetMixBinVolumes),

    { 0x01, 0x74 },
    { 0x04, 0x8B },
    { 0x07, 0x08 },
    { 0x0A, 0x24 },
    { 0x0D, 0xC0 },
    { 0x10, 0xE8 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU_Commit3dSettings
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Commit3dSettings,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_Commit3dSettings+0x56 : fld dword ptr [eax+0x174]
    { 0x56, 0xD9 },
    { 0x57, 0x80 },
    { 0x58, 0x74 },
    { 0x59, 0x01 },
    { 0x5A, 0x00 },
    { 0x5B, 0x00 },

    // CMcpxAPU_Commit3dSettings+0xA8 : fsubp st(1), st
    { 0xA8, 0xDE },
    { 0xA9, 0xE9 },

    // CMcpxAPU_Commit3dSettings+0xD4 : mov esi, 0x118
    { 0xD4, 0xBE },
    { 0xD5, 0x18 },
    { 0xD6, 0x01 },
    //
);

// ******************************************************************
// * CDirectSound_CommitDeferredSettings
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_CommitDeferredSettings,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_CommitDeferredSettings+0x12 : call [CMcpxAPU_Commit3dSettings]
    XREF_ENTRY(0x12, XREF_CMcpxAPU_Commit3dSettings),

    // CDirectSound_CommitDeferredSettings+0x0C : mov ecx, [eax+0x0C]
    { 0x0C, 0x8B },
    { 0x0D, 0x48 },
    { 0x0E, 0x0C },

    // CDirectSound_CommitDeferredSettings+0x0F : push 0
    { 0x0F, 0x6A },
    { 0x10, 0x00 },

    // CDirectSound_CommitDeferredSettings+0x19 : jz +0x0B
    { 0x19, 0x74 },
    { 0x1A, 0x0B },

    // CDirectSound_CommitDeferredSettings+0x28 : retn 0x04
    { 0x28, 0xC2 },
    { 0x29, 0x04 },
    //
);

// ******************************************************************
// * IDirectSound_CommitDeferredSettings
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_CommitDeferredSettings,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_CommitDeferredSettings+0x11 : call [CDirectSound_CommitDeferredSettings]
    XREF_ENTRY(0x11, XREF_CDirectSound_CommitDeferredSettings),

    // IDirectSound_CommitDeferredSettings+0x06 : and eax, 0xFFFFFFF8
    { 0x06, 0x83 },
    { 0x07, 0xC0 },
    { 0x08, 0xF8 },

    // IDirectSound_CommitDeferredSettings+0x09 : neg ecx
    { 0x09, 0xF7 },
    { 0x0A, 0xD9 },

    // IDirectSound_CommitDeferredSettings+0x15 : retn 0x04
    { 0x15, 0xC2 },
    { 0x16, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound_SetOrientation
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetOrientation,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_SetOrientation+0x00 : push ebp
    { 0x00, 0x55 },

    { 0x0F, 0x8B },
    { 0x11, 0x0C },
    { 0x15, 0x8B },
    { 0x17, 0x10 },
    { 0x1B, 0x8B },
    { 0x1D, 0x14 },
    { 0x21, 0x8B },
    { 0x23, 0x18 },
    { 0x27, 0x8B },
    { 0x29, 0x1C },
    { 0x2D, 0x8B },
    { 0x2F, 0x20 },
    //
);

// ******************************************************************
// * IDirectSound_SetOrientation
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_SetOrientation,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_CommitDeferredSettings+0x11 : call [CDirectSound_CommitDeferredSettings]
    XREF_ENTRY(0x42, XREF_CDirectSound_SetOrientation),

    // IDirectSound_SetOrientation+0x00 : push ebp
    { 0x00, 0x55 },

    // IDirectSound_SetOrientation+0x06 : fld [ebp+0x20]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x20 },

    // IDirectSound_SetOrientation+0x0C : sub esp, 0x18
    { 0x0C, 0x83 },
    { 0x0D, 0xEC },
    { 0x0E, 0x18 },

    // IDirectSound_SetOrientation+0x18 : add eax, 0xFFFFFFF8
    { 0x18, 0x83 },
    { 0x19, 0xC0 },
    { 0x1A, 0xF8 },

    // IDirectSound_SetOrientation+0x1F : neg ecx
    { 0x1F, 0xF7 },
    { 0x20, 0xD9 },

    // IDirectSound_SetOrientation+0x47 : retn 0x20
    { 0x47, 0xC2 },
    { 0x48, 0x20 },
    //
);

// ******************************************************************
// * IDirectSound_AddRef
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(IDirectSound_AddRef,
                         3911)
OOVPA_SIG_MATCH(

    // IDirectSound_AddRef+0x04 : lea ecx, [eax-8]
    { 0x04, 0x8D },
    { 0x05, 0x48 },
    { 0x06, 0xF8 },

    // IDirectSound_AddRef+0x07 : neg eax
    { 0x07, 0xF7 },
    { 0x08, 0xD8 },

    // IDirectSound_AddRef+0x09 : sbb eax, eax
    { 0x09, 0x1B },
    { 0x0A, 0xC0 },

    // IDirectSound_AddRef+0x0D : mov ecx, [eax]
    { 0x0D, 0x8B },
    { 0x0E, 0x08 },

    // IDirectSound_AddRef+0x10 : call dword ptr [ecx+4]
    { 0x10, 0xFF },
    { 0x11, 0x51 },
    { 0x12, 0x04 },
    //
);

// ******************************************************************
// * IDirectSound_Release
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(IDirectSound_Release,
                         3911)
OOVPA_SIG_MATCH(

    // IDirectSound_Release+0x04 : lea ecx, [eax-8]
    { 0x04, 0x8D },
    { 0x05, 0x48 },
    { 0x06, 0xF8 },

    // IDirectSound_Release+0x07 : neg eax
    { 0x07, 0xF7 },
    { 0x08, 0xD8 },

    // IDirectSound_Release+0x10 : call dword ptr [ecx+8]
    { 0x10, 0xFF },
    { 0x11, 0x51 },
    { 0x12, 0x08 },

    // IDirectSound_Release+0x13 : retn 0x04
    { 0x13, 0xC2 },
    { 0x14, 0x04 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetPitch,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetPitch+0x21 : lea edi, [esi+0xB4]
    { 0x21, 0x8D },
    { 0x22, 0xBE },
    { 0x23, 0xB4 },
    { 0x24, 0x00 },

    // CMcpxVoiceClient_SetPitch+0x58 : movzx eax, word ptr [eax+2]
    { 0x58, 0x0F },
    { 0x59, 0xB7 },
    { 0x5A, 0x40 },
    { 0x5B, 0x02 },

    // CMcpxVoiceClient_SetPitch+0x5E : dec eax; sar eax, 1
    { 0x5E, 0x48 },
    { 0x5F, 0xD1 },
    { 0x60, 0xF8 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetPitch,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetPitch+0x1B : call [CMcpxVoiceClient_SetPitch]
    XREF_ENTRY(0x1B, XREF_CMcpxVoiceClient_SetPitch),

    // CDirectSoundVoice_SetPitch+0x07 : mov edx, [esp+0x10]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x10 },

    // CDirectSoundVoice_SetPitch+0x11 : mov ecx, [eax+0x18]
    { 0x11, 0x8B },
    { 0x12, 0x48 },
    { 0x13, 0x18 },

    // CDirectSoundVoice_SetPitch+0x23 : jz +0x0B
    { 0x23, 0x74 },
    { 0x24, 0x0B },

    // CDirectSoundVoice_SetPitch+0x34 : retn 0x08
    { 0x34, 0xC2 },
    { 0x35, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetPitch,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetPitch+0x15 : call [CDirectSoundVoice_SetPitch]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetPitch),

    // IDirectSoundBuffer_SetPitch+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetPitch+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetPitch+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * XAudioCalculatePitch
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XAudioCalculatePitch,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // XAudioCalculatePitch+0x08 : cmp esi, 0xBB80
    { 0x08, 0x81 },
    { 0x09, 0xFE },
    { 0x0A, 0x80 },
    { 0x0B, 0xBB },

    // XAudioCalculatePitch+0x1D : jmp +0x2B
    { 0x1D, 0xEB },
    { 0x1E, 0x2B },

    // XAudioCalculatePitch+0x1F : lea ecx, [ebp+0x08]
    { 0x1F, 0x8D },
    { 0x20, 0x4D },
    { 0x21, 0x08 },

    // XAudioCalculatePitch+0x4E : retn 0x04
    { 0x4E, 0xC2 },
    { 0x4F, 0x04 },
    //
);

// ******************************************************************
// * DirectSoundGetSampleTime
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DirectSoundGetSampleTime,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x01, 0x0C },
    { 0x02, 0x20 },
    { 0x03, 0x80 },
    { 0x04, 0xFE },
    { 0x05, 0xC3 },
    //
);

// ******************************************************************
// * CSensaura3d::GetFullHRTFFilterPair
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CSensaura3d_GetFullHRTFFilterPair,
                         3911)
OOVPA_SIG_MATCH(

    { 0x1E, 0xEB },
    { 0x2E, 0x6A },
    { 0x3E, 0x40 },
    { 0x5E, 0x7E },
    { 0x7E, 0x1E },
    { 0xA2, 0xD9 },
    { 0xBE, 0x09 },
    //
);

// ******************************************************************
// * DirectSoundUseFullHRTF
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundUseFullHRTF,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0D, XREF_CSensaura3d_GetFullHRTFFilterPair),

    { 0x05, 0x85 },
    { 0x06, 0xC0 },
    { 0x11, 0x74 },
    { 0x12, 0x0B },
    { 0x13, 0x68 },
    { 0x18, 0xFF },
    { 0x1E, 0xC3 },
    //
);

// ******************************************************************
// * CSensaura3d_GetLiteHRTFFilterPair
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(CSensaura3d_GetLiteHRTFFilterPair,
                         3911)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // push ecx
    OV_MATCH(0x15, 0x51),

    // call ...
    OV_MATCH(0x19, 0xE8),
    // cdq
    // push 3
    // pop ecx
    OV_MATCH(0x1E, 0x99, 0x6A, 0x03, 0x59),

    // idiv eax, ecx
    OV_MATCH(0x22, 0xF7, 0xF9),
    //
);

// ******************************************************************
// * DirectSoundUseLightHRTF
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundUseLightHRTF,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0D, XREF_CSensaura3d_GetLiteHRTFFilterPair),

    { 0x05, 0x85 },
    { 0x06, 0xC0 },
    { 0x11, 0x74 },
    { 0x12, 0x0B },
    { 0x13, 0x68 },
    { 0x18, 0xFF },
    { 0x1E, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetFrequency
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetFrequency,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetFrequency+0x1F : call [XAudioCalculatePitch]
    XREF_ENTRY(0x20, XREF_XAudioCalculatePitch),

    // CDirectSoundVoice_SetFrequency+0x15 : mov eax, [esi+0x18]
    { 0x15, 0x8B },
    { 0x16, 0x46 },
    { 0x17, 0x18 },

    // CDirectSoundVoice_SetFrequency+0x18 : mov eax, [eax+0x10]
    { 0x18, 0x8B },
    { 0x19, 0x40 },
    { 0x1A, 0x10 },

    // CDirectSoundVoice_SetFrequency+0x40 : retn 0x08
    { 0x40, 0xC2 },
    { 0x41, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetFrequency
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetFrequency,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetFrequency+0x14 : call [CDirectSoundVoice_SetFrequency]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetFrequency),

    // IDirectSoundBuffer_SetFrequency+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetFrequency+0x0F : sbb ecx, ecx
    { 0x0F, 0x1B },
    { 0x10, 0xC9 },

    // IDirectSoundBuffer_SetFrequency+0x11 : and ecx, eax
    { 0x11, 0x23 },
    { 0x12, 0xC8 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetMixBins
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetMixBins,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetMixBins+0x1D : lea eax, [esi+0x84]
    { 0x1D, 0x86 },
    { 0x1E, 0x84 },
    { 0x21, 0x00 },

    // CMcpxVoiceClient_SetMixBins+0x2E : mov eax, [esi+0xE0]
    { 0x2E, 0x8B },
    { 0x30, 0xE0 },
    { 0x31, 0x00 },

    // CMcpxVoiceClient_SetMixBins+0x41 : jz +0x7F
    { 0x41, 0x74 },
    { 0x42, 0x7F },

    // CMcpxVoiceClient_SetMixBins+0x5A : mov ds:[0xFE8202F8], eax
    { 0x5A, 0xA3 },
    { 0x5B, 0xF8 },
    { 0x5C, 0x02 },
    { 0x5D, 0x82 },
    { 0x5E, 0xFE },

    // CMcpxVoiceClient_SetMixBins+0xBF : jb +0x8C
    { 0xBF, 0x72 },
    { 0xC0, 0x8C },

    // CMcpxVoiceClient_SetMixBins+0xD6 : retn
    { 0xD6, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMixBins
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMixBins,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMixBins+0x28 : call [CMcpxVoiceClient::SetMixBins]
    XREF_ENTRY(0x29, XREF_CMcpxVoiceClient_SetMixBins),

    // CDirectSoundVoice_SetMixBins+0x11 : mov ecx, [esi+0x18]
    { 0x11, 0x8B },
    { 0x12, 0x4E },
    { 0x13, 0x18 },

    // CDirectSoundVoice_SetMixBins+0x25 : mov ecx, [esi+0x14]
    { 0x25, 0x8B },
    { 0x26, 0x4E },
    { 0x27, 0x14 },

    // CDirectSoundVoice_SetMixBins+0x55 : retn 0x08
    { 0x55, 0xC2 },
    { 0x56, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMixBins
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMixBins,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetMixBins+0x14 : call [CDirectSoundVoice::SetMixBins]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetMixBins),

    // IDirectSoundBuffer_SetMixBins+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetMixBins+0x0F : sbb ecx, ecx
    { 0x0F, 0x1B },
    { 0x10, 0xC9 },

    // IDirectSoundBuffer_SetMixBins+0x11 : and ecx, eax
    { 0x11, 0x23 },
    { 0x12, 0xC8 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetOutputBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetOutputBuffer,
                         3911)
OOVPA_SIG_MATCH(

    { 0x0B, 0xF7 },
    { 0x19, 0x8B },
    { 0x25, 0x3B },
    { 0x30, 0xE8 },
    { 0x35, 0x8B },
    { 0x46, 0x74 },
    { 0x51, 0xD8 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetOutputBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetOutputBuffer,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetOutputBuffer+0x11 : call [XREF_CDirectSoundVoice_SetOutputBuffer]
    XREF_ENTRY(0x12, XREF_CDirectSoundVoice_SetOutputBuffer),

    // CDirectSoundBuffer_SetOutputBuffer+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetOutputBuffer+0x07 : push [esp+0x10]
    { 0x07, 0xFF },
    { 0x08, 0x74 },
    { 0x09, 0x24 },
    { 0x0A, 0x10 },

    // CDirectSoundBuffer_SetOutputBuffer+0x0D : push [esp+0x10]
    { 0x0D, 0xFF },
    { 0x0E, 0x74 },
    { 0x0F, 0x24 },
    { 0x10, 0x10 },

    // CDirectSoundBuffer_SetOutputBuffer+0x29 : pop edi
    { 0x29, 0x5F },

    // CDirectSoundBuffer_SetOutputBuffer+0x2B : retn 0x08
    { 0x2B, 0xC2 },
    { 0x2C, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetBufferData
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetBufferData,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetBufferData+0x3C : call [CDirectSoundBufferSettings::SetBufferData]
    XREF_ENTRY(0x3D, XREF_CDirectSoundBufferSettings_SetBufferData),

    // CDirectSoundBuffer::SetBufferData+0x54 : call [CMcpxBuffer::SetBufferData]
    XREF_ENTRY(0x55, XREF_CMcpxBuffer_SetBufferData),

    // CDirectSoundBuffer::SetBufferData+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer::SetBufferData+0x22 : cmp ecx, [eax+0x4C]
    { 0x22, 0x3B },
    { 0x23, 0x48 },
    { 0x24, 0x4C },

    // CDirectSoundBuffer::SetBufferData+0x38 : mov ecx, [esi+0x1C]
    { 0x38, 0x8B },
    { 0x39, 0x4E },
    { 0x3A, 0x1C },

    // CDirectSoundBuffer::SetBufferData+0x71 : leave; retn 0xC
    { 0x71, 0xC9 },
    { 0x72, 0xC2 },
    { 0x73, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetBufferData
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetBufferData,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetBufferData+0x18 : call [CDirectSoundBuffer_SetBufferData]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetBufferData),

    // IDirectSoundBuffer_SetBufferData+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetBufferData+0x0E : add eax, 0xFFFFFFE4
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_SetBufferData+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetNotificationPositions
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetNotificationPositions,
                         3911)
OOVPA_SIG_MATCH(

    { 0x09, 0x24 },
    { 0x14, 0x24 },
    { 0x1F, 0x74 },
    { 0x2A, 0x50 },
    { 0x35, 0xF6 },
    { 0x40, 0x07 },
    { 0x4D, 0x5F },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetNotificationPositions
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetNotificationPositions,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetNotificationPositions),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0xFF },
    { 0x0E, 0x83 },
    { 0x12, 0xD9 },
    { 0x16, 0xC8 },
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetHeadroom,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetHeadroom+0x22 : call [CMcpxVoiceClient::SetVolume]
    XREF_ENTRY(0x23, XREF_CMcpxVoiceClient_SetVolume),

    // CDirectSoundVoice_SetHeadroom+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CDirectSoundVoice_SetHeadroom+0x07 : mov edx, [esp+0x0C]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x0C },

    // CDirectSoundVoice_SetHeadroom+0x11 : mov eax, [edx+0x18]
    { 0x11, 0x8B },
    { 0x12, 0x42 },
    { 0x13, 0x18 },

    // CDirectSoundVoice_SetHeadroom+0x3C : retn 0x08
    { 0x3C, 0xC2 },
    { 0x3D, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetHeadroom,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetHeadroom+0x15 : call [CDirectSoundVoice_SetHeadroom]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetHeadroom),

    // IDirectSoundBuffer_SetHeadroom+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetHeadroom+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetHeadroom+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Pause
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Pause,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_CMcpxStream_Pause),

    { 0x01, 0x44 },
    { 0x04, 0xFF },
    { 0x07, 0x08 },
    { 0x0A, 0x24 },
    { 0x10, 0xC2 },
    { 0x11, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Process (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Process,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream_Process
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Process,
                         3911)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x04, 0x08 },

    { 0x05, 0x8B },
    { 0x07, 0x24 },

    { 0x0D, 0x85 },
    { 0x0E, 0xC0 },

    //CDirectSoundStream_Process+0x11 : mov eax, 88780032h
    { 0x12, 0x32 },
    { 0x13, 0x00 },
    { 0x14, 0x78 },
    { 0x15, 0x88 },

    { 0x18, 0xFF },
    { 0x1B, 0x0C },

    { 0x1C, 0x8B },
    { 0x1E, 0x24 },

    { 0x25, 0xC2 },
    { 0x26, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream::GetStatus (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetStatus,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream::GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetStatus,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 }, //Prevent false detection & check if is at beginning of function.

    { 0x08, 0x8B },
    { 0x0B, 0x08 },

    { 0x0C, 0x8B },
    { 0x0E, 0x24 },

    { 0x14, 0x8B },
    { 0x17, 0x0C },

    { 0x18, 0xF7 },
    { 0x1A, 0x1B },
    { 0x1C, 0xF7 },

    //CDirectSoundStream_GetStatus+0x20 : mov dword ptr [ecx], eax
    { 0x20, 0x89 },
    { 0x21, 0x01 },

    { 0x32, 0xC2 },
    { 0x33, 0x08 },
    //
);

// ******************************************************************
// * CMcpxStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Flush,
                         3911)
OOVPA_SIG_MATCH(

    { 0x0D, 0x03 },
    { 0x0F, 0x03 },

    { 0x20, 0x33 },
    { 0x22, 0x33 },

    { 0x2D, 0x83 },
    { 0x2E, 0xFF },
    { 0x2F, 0x03 },

    { 0x4B, 0xE8 },

    //CMcpxStream_Flush+0x57  : e__,0x80004004 (unique value)
    { 0x58, 0x04 },
    { 0x59, 0x40 },
    { 0x5A, 0x00 },
    { 0x5B, 0x80 },

    { 0x62, 0xE8 },

    { 0x9D, 0xC9 },
    { 0x9E, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Flush (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Flush,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Flush,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream::Flush+0x10 : call [CMcpxStream::Flush]
    XREF_ENTRY(0x11, XREF_CMcpxStream_Flush),

    { 0x00, 0x56 },

    { 0x09, 0x8B },
    { 0x0C, 0x0C },

    { 0x0D, 0x8B },
    { 0x0F, 0x24 },

    // CDirectSoundStream::Flush+0x10 : call [CMcpxStream::Flush]
    { 0x10, 0xE8 },

    // CDirectSoundStream::Flush+0x2A : ret 4
    { 0x2A, 0xC2 },
    { 0x2B, 0x04 },
    //
);

// ******************************************************************
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Discontinuity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CMcpxStream_Discontinuity+0x66 : call [CMcpxStream_Flush]
    XREF_ENTRY(0x67, XREF_CMcpxStream_Flush),

    { 0x0D, 0x03 },
    { 0x0F, 0x03 },

    { 0x1B, 0x33 },
    { 0x1D, 0x8D },

    { 0x25, 0x0F },
    { 0x26, 0x94 },
    { 0x27, 0xC1 },

    { 0x64, 0x8B },

    { 0x66, 0xE8 },

    { 0x6E, 0xC9 },
    { 0x6F, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Discontinuity (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Discontinuity,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream::Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Discontinuity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CDirectSoundStream_Discontinuity+0x10 : call [CMcpxStream_Discontinuity]
    XREF_ENTRY(0x11, XREF_CMcpxStream_Discontinuity),

    { 0x00, 0x56 },

    { 0x09, 0x8B },
    { 0x0C, 0x0C },

    { 0x0D, 0x8B },
    { 0x0F, 0x24 },

    //CDirectSoundStream::Discontinuity+0x10 : call [CMcpxStream_Discontinuity]
    { 0x10, 0xE8 },

    //CDirectSoundStream_Discontinuity+0x2A : ret 4
    { 0x2A, 0xC2 },
    { 0x2B, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream::GetInfo (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetInfo,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream::GetInfo
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetInfo,
                         3911)
OOVPA_SIG_MATCH(

    //CDirectSoundStream_GetInfo+0x00 : push ebx
    { 0x00, 0x53 },

    //CDirectSoundStream_GetInfo+0x0C : mov edi, dword ptr [esp + 10h]
    { 0x0C, 0x8B },
    { 0x0D, 0x7C },
    { 0x0E, 0x24 },
    { 0x0F, 0x10 },

    //CDirectSoundStream_GetInfo+0x16 : mov, dword ptr [edi + 24h]
    { 0x16, 0x8B },
    { 0x17, 0x4F },
    { 0x18, 0x24 },

    //CDirectSoundStream_GetInfo+0x23 : mov eax, dword ptr [edi + 20h]
    { 0x23, 0x8B },
    { 0x24, 0x47 },
    { 0x25, 0x20 },

    //CDirectSoundStream_GetInfo+0x2D : and dword ptr [esi + 8], 0
    { 0x2D, 0x83 },
    { 0x2E, 0x66 },
    { 0x2F, 0x08 },
    { 0x30, 0x00 },

    //CDirectSoundStream_GetInfo+0x48 : ret 8
    { 0x48, 0xC2 },
    { 0x49, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dMaxDistance
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dMaxDistance,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dMaxDistance+0x04 : or byte ptr [ecx+0x80], 0x04
    { 0x04, 0x83 },
    { 0x05, 0x89 },
    { 0x06, 0x80 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x04 },

    // CMcpxVoiceClient_Set3dMaxDistance+0x10 : mov [ecx+0x54], eax
    { 0x10, 0x89 },
    { 0x11, 0x41 },
    { 0x12, 0x54 },

    // CMcpxVoiceClient_Set3dMaxDistance+0x1E : retn 0x08
    { 0x1E, 0xC2 },
    { 0x1F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMaxDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMaxDistance+0x23 : call [CMcpxVoiceClient_Set3dMaxDistance]
    XREF_ENTRY(0x23, XREF_CMcpxVoiceClient_Set3dMaxDistance),

    // CDirectSoundVoice_SetMaxDistance+0x0D : mov eax, [esp+0x14]
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x14 },

    // CDirectSoundVoice_SetMaxDistance+0x11 : not eax
    { 0x11, 0xF7 },
    { 0x12, 0xD0 },

    // CDirectSoundVoice_SetMaxDistance+0x13 : and eax, 1
    { 0x13, 0x83 },
    { 0x14, 0xE0 },
    { 0x15, 0x01 },

    // CDirectSoundVoice_SetMaxDistance+0x1C : mov ecx, [eax+0x14]
    { 0x1C, 0x8B },
    { 0x1D, 0x48 },
    { 0x1E, 0x14 },

    // CDirectSoundVoice_SetMaxDistance+0x3C : retn 0x0C
    { 0x3C, 0xC2 },
    { 0x3D, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMaxDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetMaxDistance),

    { 0x01, 0x74 },
    { 0x04, 0xD9 },
    { 0x07, 0x0C },
    { 0x0A, 0x1C },
    { 0x0D, 0x74 },
    { 0x10, 0xE8 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMaxDistance
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMaxDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_SetMaxDistance),

    { 0x03, 0x0C },
    { 0x08, 0x8B },
    { 0x0D, 0x8B },
    { 0x12, 0x83 },
    { 0x17, 0x1B },
    { 0x1C, 0xE8 },
    { 0x21, 0xC2 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMaxDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetMaxDistance+0x15 : call [CDirectSoundVoice_SetMaxDistance]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetMaxDistance),

    // CDirectSoundStream_SetMaxDistance+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // CDirectSoundStream_SetMaxDistance+0x0D : add eax, 0x04
    { 0x0D, 0x83 },
    { 0x0E, 0xC0 },
    { 0x0F, 0x04 },

    // CDirectSoundStream_SetMaxDistance+0x19 : retn 0x0C
    { 0x19, 0xC2 },
    { 0x1A, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMaxDistance
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetMaxDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetMaxDistance+0x11 : call [CDirectSoundStream_SetMaxDistance]
    XREF_ENTRY(0x11, XREF_CDirectSoundStream_SetMaxDistance),

    // CDirectSoundStream_SetMaxDistance+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // CDirectSoundStream_SetMaxDistance+0x0C : push [esp+0x0C]
    { 0x0C, 0xFF },
    { 0x0D, 0x74 },
    { 0x0E, 0x24 },
    { 0x0F, 0x0C },

    // CDirectSoundStream_SetMaxDistance+0x15 : retn 0x0C
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dMinDistance
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dMinDistance,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dMinDistance+0x04 : or byte ptr [ecx+0x80], 0x04
    { 0x04, 0x83 },
    { 0x05, 0x89 },
    { 0x06, 0x80 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x04 },

    // CMcpxVoiceClient_Set3dMinDistance+0x10 : mov [ecx+0x50], eax
    { 0x10, 0x89 },
    { 0x11, 0x41 },
    { 0x12, 0x50 },

    // CMcpxVoiceClient_Set3dMinDistance+0x1E : retn 0x08
    { 0x1E, 0xC2 },
    { 0x1F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMinDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMinDistance+0x23 : call [CMcpxVoiceClient_Set3dMinDistance]
    XREF_ENTRY(0x23, XREF_CMcpxVoiceClient_Set3dMinDistance),

    // CDirectSoundVoice_SetMinDistance+0x0D : mov eax, [esp+0x14]
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x14 },

    // CDirectSoundVoice_SetMinDistance+0x11 : not eax
    { 0x11, 0xF7 },
    { 0x12, 0xD0 },

    // CDirectSoundVoice_SetMinDistance+0x13 : and eax, 1
    { 0x13, 0x83 },
    { 0x14, 0xE0 },
    { 0x15, 0x01 },

    // CDirectSoundVoice_SetMinDistance+0x1C : mov ecx, [eax+0x14]
    { 0x1C, 0x8B },
    { 0x1D, 0x48 },
    { 0x1E, 0x14 },

    // CDirectSoundVoice_SetMinDistance+0x3C : retn 0x0C
    { 0x3C, 0xC2 },
    { 0x3D, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMinDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetMinDistance),

    { 0x01, 0x74 },
    { 0x04, 0xD9 },
    { 0x07, 0x0C },
    { 0x0A, 0x1C },
    { 0x0D, 0x74 },
    { 0x10, 0xE8 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMinDistance
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMinDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_SetMinDistance),

    { 0x03, 0x0C },
    { 0x08, 0x8B },
    { 0x0D, 0x8B },
    { 0x12, 0x83 },
    { 0x17, 0x1B },
    { 0x1C, 0xE8 },
    { 0x21, 0xC2 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMinDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetMinDistance+0x15 : call [CDirectSoundVoice_SetMinDistance]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetMinDistance),

    // CDirectSoundStream_SetMinDistance+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // CDirectSoundStream_SetMinDistance+0x0D : add eax, 0x04
    { 0x0D, 0x83 },
    { 0x0E, 0xC0 },
    { 0x0F, 0x04 },

    // CDirectSoundStream_SetMinDistance+0x19 : retn 0x0C
    { 0x19, 0xC2 },
    { 0x1A, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMinDistance
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetMinDistance,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetMinDistance+0x11 : call [CDirectSoundStream_SetMinDistance]
    XREF_ENTRY(0x11, XREF_CDirectSoundStream_SetMinDistance),

    // CDirectSoundStream_SetMinDistance+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // CDirectSoundStream_SetMinDistance+0x0C : push [esp+0x0C]
    { 0x0C, 0xFF },
    { 0x0D, 0x74 },
    { 0x0E, 0x24 },
    { 0x0F, 0x0C },

    // CDirectSoundStream_SetMinDistance+0x15 : retn 0x0C
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dConeOutsideVolume
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dConeOutsideVolume,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dConeOutsideVolume+0x04 : or dword ptr [eax+0x80], 0x10
    { 0x04, 0x83 },
    { 0x05, 0x89 },
    { 0x06, 0x80 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x10 },

    // CMcpxVoiceClient_Set3dConeOutsideVolume+0x10 : mov [ecx+0x4C], eax
    { 0x10, 0x89 },
    { 0x11, 0x41 },
    { 0x12, 0x4C },

    // CMcpxVoiceClient_Set3dConeOutsideVolume+0x1E : retn 0x08
    { 0x1E, 0xC2 },
    { 0x1F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetConeOutsideVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetConeOutsideVolume+0x1F : call [CMcpxVoiceClient_Set3dConeOutsideVolume]
    XREF_ENTRY(0x1F, XREF_CMcpxVoiceClient_Set3dConeOutsideVolume),

    // CDirectSoundVoice_SetConeOutsideVolume+0x09 : mov eax, [esp+0x14]
    { 0x09, 0x8B },
    { 0x0A, 0x44 },
    { 0x0B, 0x24 },
    { 0x0C, 0x14 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x0D : not eax; and eax, 1
    { 0x0D, 0xF7 },
    { 0x0E, 0xD0 },
    { 0x0F, 0x83 },
    { 0x10, 0xE0 },
    { 0x11, 0x01 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x38 : retn 0x0C
    { 0x38, 0xC2 },
    { 0x39, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeOutsideVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetConeOutsideVolume+0x00 : jmp CDirectSoundVoice::SetConeOutsideVolume
    XREF_ENTRY(0x1, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    // CDirectSoundBuffer::SetConeOutsideVolume+0x00 : jmp
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetConeOutsideVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetConeOutsideVolume+0x18 : call [CDirectSoundVoice_SetConeOutsideVolume]
    XREF_ENTRY(0x19, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    // IDirectSoundBuffer_SetConeOutsideVolume+0x0A : push [esp+4+arg_4]
    { 0x0A, 0xFF },
    { 0x0B, 0x74 },
    { 0x0C, 0x24 },
    { 0x0D, 0x0C },

    // IDirectSoundBuffer_SetConeOutsideVolume+0x15 : and ecx, eax
    { 0x15, 0x23 },
    { 0x16, 0xC8 },

    // IDirectSoundBuffer_SetConeOutsideVolume+0x1D : retn 0Ch
    { 0x1E, 0x0C },
    { 0x1F, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeOutsideVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetConeOutsideVolume+0x11 : call [CDirectSoundVoice_SetConeOutsideVolume]
    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    // CDirectSoundStream_SetConeOutsideVolume+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetConeOutsideVolume+0x0C : add eax, 0x04
    { 0x0C, 0x83 },
    { 0x0D, 0xC0 },
    { 0x0E, 0x04 },

    // CDirectSoundStream_SetConeOutsideVolume+0x15 : retn 0x0C
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_Commit3dSettings_4,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient::Commit3dSettings+0x65 : call [CMcpxVoiceClient_SetVolume]
    XREF_ENTRY(0x66, XREF_CMcpxVoiceClient_SetVolume),

    // CMcpxVoiceClient::Commit3dSettings+0x83 : call [CMcpxVoiceClient_SetFilter]
    XREF_ENTRY(0x84, XREF_CMcpxVoiceClient_SetFilter),

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x17 : or [eax+0x80],ecx
    { 0x17, 0x09 },
    { 0x18, 0x88 },
    { 0x19, 0x80 },
    { 0x1A, 0x00 },
    // CMcpxVoiceClient::Commit3dSettings+0x2B : add eax, 0x80
    { 0x2B, 0x05 },
    { 0x2C, 0x80 },
    { 0x2D, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x3D : cmpxchg [ecx],edx
    { 0x3D, 0x0F },
    { 0x3E, 0xB1 },
    { 0x3F, 0x11 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dParameters
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_Set3dParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x25, XREF_CMcpxVoiceClient_Commit3dSettings),

    { 0x02, 0x74 },
    { 0x08, 0x6A },
    { 0x09, 0x10 },
    { 0x0A, 0x59 },
    { 0x0B, 0x8D },
    { 0x0C, 0x78 },
    { 0x0D, 0x1C },
    { 0x0E, 0xF3 },
    { 0x14, 0x00 },
    { 0x18, 0x7C },
    { 0x1F, 0x09 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetAllParameters+0x25 : call [CMcpxVoiceClient_Set3dParameters]
    XREF_ENTRY(0x1F, XREF_CMcpxVoiceClient_Set3dParameters),

    // CDirectSoundVoice_SetAllParameters+0x09 : mov eax, [esp+0x14]
    { 0x09, 0x8B },
    { 0x0A, 0x44 },
    { 0x0B, 0x24 },
    { 0x0C, 0x14 },

    // CDirectSoundVoice_SetAllParameters+0x0D : not eax; and eax, 1
    { 0x0D, 0xF7 },
    { 0x0E, 0xD0 },
    { 0x0F, 0x83 },
    { 0x10, 0xE0 },
    { 0x11, 0x01 },

    // CDirectSoundVoice_SetAllParameters+0x38 : retn 0x0C
    { 0x38, 0xC2 },
    { 0x39, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetAllParameters+0x11 : call [CDirectSoundVoice_SetAllParameters]
    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetAllParameters),

    // CDirectSoundStream_SetAllParameters+0x04 : push eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetAllParameters+0x0C : add eax, 0x04
    { 0x0C, 0x83 },
    { 0x0D, 0xC0 },
    { 0x0E, 0x04 },

    // CDirectSoundStream_SetAllParameters+0x15 : retn 0x0C
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSoundVoice_SetAllParameters),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0xFF },
    { 0x0E, 0x83 },
    { 0x12, 0xD9 },
    { 0x16, 0xC8 },
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeAngles,
                         3911)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x0E, 0xD0 },
    { 0x16, 0x18 },
    { 0x1E, 0x18 },
    { 0x27, 0x85 },
    { 0x32, 0xFF },
    { 0x38, 0x8B },
    { 0x3E, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetConeAngles,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1D, XREF_CDirectSoundVoice_SetConeAngles),

    { 0x03, 0x10 },
    { 0x08, 0xFF },
    { 0x0D, 0xC8 },
    { 0x12, 0x83 },
    { 0x17, 0x1B },
    { 0x1C, 0xE8 },
    { 0x21, 0xC2 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeAngles,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetConeAngles+0x15 : call [CDirectSoundVoice_SetConeAngles]
    XREF_ENTRY(0x15, XREF_CDirectSoundVoice_SetConeAngles),

    // CDirectSoundStream_SetConeAngles+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetConeAngles+0x0C : add eax, 0x04
    { 0x0C, 0x83 },
    { 0x0D, 0xC0 },
    { 0x0E, 0x04 },

    // CDirectSoundStream_SetConeAngles+0x19 : retn 0x10
    { 0x19, 0xC2 },
    { 0x1A, 0x10 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dConeOrientation
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dConeOrientation,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dConeOrientation+0x0C : or byte ptr [ecx+0x80], 0x18
    { 0x0C, 0x83 },
    { 0x0D, 0x89 },
    { 0x0E, 0x80 },
    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0x00 },
    { 0x12, 0x18 },

    // CMcpxVoiceClient_Set3dConeOrientation+0x1A : jz +0x07
    { 0x1A, 0x74 },
    { 0x1B, 0x07 },

    // CMcpxVoiceClient_Set3dConeOrientation+0x25 : retn 0x08
    { 0x25, 0xC2 },
    { 0x26, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetConeOrientation,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetConeOrientation+0x34 : call [CMcpxVoiceClient_Set3dConeOrientation]
    XREF_ENTRY(0x35, XREF_CMcpxVoiceClient_Set3dConeOrientation),

    // CDirectSoundVoice_SetConeOrientation+0x21 : mov eax, [ebp+0x18]
    { 0x21, 0x8B },
    { 0x22, 0x45 },
    { 0x23, 0x18 },

    // CDirectSoundVoice_SetConeOrientation+0x24 : not eax
    { 0x24, 0xF7 },
    { 0x25, 0xD0 },

    // CDirectSoundVoice_SetConeOrientation+0x26 : and eax, 1
    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0x01 },

    // CDirectSoundVoice_SetConeOrientation+0x31 : mov ecx, [eax+0x14]
    { 0x31, 0x8B },
    { 0x32, 0x48 },
    { 0x33, 0x14 },

    // CDirectSoundVoice_SetConeOrientation+0x4F : retn 0x14
    { 0x4F, 0xC2 },
    { 0x50, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeOrientation,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x21, XREF_CDirectSoundVoice_SetConeOrientation),

    // CDirectSoundBuffer_SetConeOrientation+0x1A : fstp [esp+8h]
    { 0x0C, 0xD9 },
    { 0x0D, 0x5C },
    { 0x0E, 0x24 },
    { 0x0F, 0x08 },

    // CDirectSoundBuffer_SetConeOrientation+0x1A : fstp [esp]
    { 0x1A, 0xD9 },
    { 0x1B, 0x1C },
    { 0x1C, 0x24 },

    // CDirectSoundBuffer_SetConeOrientation+0x26 : ret 14h
    { 0x26, 0xC2 },
    { 0x27, 0x14 },
    { 0x28, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetConeOrientation
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetConeOrientation,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetConeOrientation+0x2C : call [CDirectSoundBuffer::SetConeOrientation]
    XREF_ENTRY(0x2D, XREF_CDirectSoundBuffer_SetConeOrientation),

    // IDirectSoundBuffer_SetConeOrientation+0x06 : fld [ebp+arg_C]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // IDirectSoundBuffer_SetConeOrientation+0x28 : fstp [esp+10h+var_10]
    { 0x28, 0xD9 },
    { 0x29, 0x1C },
    { 0x2A, 0x24 },

    // IDirectSoundBuffer_SetConeOrientation+0x32 : retn 14h
    { 0x33, 0x14 },
    { 0x34, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeOrientation,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetConeOrientation+0x25 : call [CDirectSoundVoice_SetConeOrientation]
    XREF_ENTRY(0x25, XREF_CDirectSoundVoice_SetConeOrientation),

    // CDirectSoundStream_SetConeOrientation+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // CDirectSoundStream_SetConeOrientation+0x0C : sub esp, 0x0C
    { 0x0C, 0x83 },
    { 0x0D, 0xEC },
    { 0x0E, 0x0C },

    // CDirectSoundStream_SetConeOrientation+0x2A : retn 0x14
    { 0x2A, 0xC2 },
    { 0x2B, 0x14 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetConeOrientation,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetConeOrientation+0x21 : call [CDirectSoundStream_SetConeOrientation]
    XREF_ENTRY(0x21, XREF_CDirectSoundStream_SetConeOrientation),

    // IDirectSoundStream_SetConeOrientation+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // IDirectSoundStream_SetConeOrientation+0x1A : fstp [esp]
    { 0x1A, 0xD9 },
    { 0x1B, 0x1C },
    { 0x1C, 0x24 },

    // IDirectSoundStream_SetConeOrientation+0x26 : retn 0x14
    { 0x26, 0xC2 },
    { 0x27, 0x14 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Set3dMode
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dMode,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dMode+0x04 : or byte ptr [ecx+0x80], 0xFF
    { 0x04, 0x80 },
    { 0x05, 0x89 },
    { 0x06, 0x80 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0xFF },

    // CMcpxVoiceClient_Set3dMode+0x10 : cmp [ecx+0x58], eax
    { 0x10, 0x89 },
    { 0x11, 0x41 },
    { 0x12, 0x58 },

    // CMcpxVoiceClient_Set3dMode+0x1E : retn 0x08
    { 0x1E, 0xC2 },
    { 0x1F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMode,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMode+0x1E : call [CMcpxVoiceClient::Set3dMode]
    XREF_ENTRY(0x1F, XREF_CMcpxVoiceClient_Set3dMode),

    // CDirectSoundVoice_SetMode+0x17 : push [esp+0x14]
    { 0x17, 0xFF },
    { 0x18, 0x74 },
    { 0x19, 0x24 },
    { 0x1A, 0x14 },

    // CDirectSoundVoice_SetMode+0x1B : mov ecx, [eax+0x14]
    { 0x1B, 0x8B },
    { 0x1C, 0x48 },
    { 0x1D, 0x14 },

    // CDirectSoundVoice_SetMode+0x38 : retn 0x0C
    { 0x38, 0xC2 },
    { 0x39, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMode,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetMode+0x18 : call [CDirectSoundVoice::SetMode]
    XREF_ENTRY(0x19, XREF_CDirectSoundVoice_SetMode),

    // IDirectSoundBuffer_SetMode+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetMode+0x0E : add eax, 0xFFFFFFE4
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_SetMode+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMode,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetMode+0x10 : call [CDirectSoundVoice::SetMode]
    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetMode),

    // CDirectSoundStream_SetMode+0x0C : add eax, 4
    { 0x0C, 0x83 },
    { 0x0D, 0xC0 },
    { 0x0E, 0x04 },

    // CDirectSoundStream_SetMode+0x0F : push eax
    { 0x0F, 0x50 },

    // CDirectSoundBuffer8_SetMode+0x15 : retn 0x0C
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dPosition
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dPosition,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dPosition+0x0C : or byte ptr [ecx+0x80], 0xFF
    { 0x0C, 0x80 },
    { 0x0D, 0x89 },
    { 0x0E, 0x80 },
    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0x00 },
    { 0x12, 0xFF },

    // CMcpxVoiceClient_Set3dPosition+0x1A : jz +0x07
    { 0x1A, 0x74 },
    { 0x1B, 0x07 },

    // CMcpxVoiceClient_Set3dPosition+0x25 : retn 0x08
    { 0x25, 0xC2 },
    { 0x26, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetPosition+0x35 : call [CMcpxVoiceClient_Set3dPosition]
    XREF_ENTRY(0x35, XREF_CMcpxVoiceClient_Set3dPosition),

    // CDirectSoundVoice_SetPosition+0x21 : mov eax, [ebp+0x18]
    { 0x21, 0x8B },
    { 0x22, 0x45 },
    { 0x23, 0x18 },

    // CDirectSoundVoice_SetPosition+0x24 : not eax
    { 0x24, 0xF7 },
    { 0x25, 0xD0 },

    // CDirectSoundVoice_SetPosition+0x26 : and eax, 1
    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0x01 },

    // CDirectSoundVoice_SetPosition+0x31 : mov ecx, [eax+0x14]
    { 0x31, 0x8B },
    { 0x32, 0x48 },
    { 0x33, 0x14 },

    // CDirectSoundVoice_SetPosition+0x4F : retn 0x14
    { 0x4F, 0xC2 },
    { 0x50, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetPosition+0x24 : call [CDirectSoundVoice_SetPosition]
    XREF_ENTRY(0x25, XREF_CDirectSoundVoice_SetPosition),

    // CDirectSoundStream_SetPosition+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // CDirectSoundStream_SetPosition+0x0C : sub esp, 0x0C
    { 0x0C, 0x83 },
    { 0x0D, 0xEC },
    { 0x0E, 0x0C },

    // CDirectSoundStream_SetPosition+0x2A : retn 0x14
    { 0x2A, 0xC2 },
    { 0x2B, 0x14 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetPosition+0x20 : call [CDirectSoundStream_SetPosition]
    XREF_ENTRY(0x21, XREF_CDirectSoundStream_SetPosition),

    // IDirectSoundStream_SetPosition+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // IDirectSoundStream_SetPosition+0x1A : fstp [esp]
    { 0x1A, 0xD9 },
    { 0x1B, 0x1C },
    { 0x1C, 0x24 },

    // IDirectSoundStream_SetPosition+0x26 : retn 0x14
    { 0x26, 0xC2 },
    { 0x27, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetPosition+0x20 : call [CDirectSoundVoice_SetPosition]
    XREF_ENTRY(0x21, XREF_CDirectSoundVoice_SetPosition),

    // CDirectSoundBuffer_SetPosition+0x06 : fld [ebp+arg_C]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // CDirectSoundBuffer_SetPosition+0x1A : fstp [esp+0x10+var_10]
    { 0x1A, 0xD9 },
    { 0x1B, 0x1C },
    { 0x1C, 0x24 },

    // CDirectSoundBuffer_SetPosition+0x26 : retn 0x14
    { 0x27, 0x14 },
    { 0x28, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetPosition
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetPosition+0x2C : call [CDirectSoundBuffer::SetPosition]
    XREF_ENTRY(0x2D, XREF_CDirectSoundBuffer_SetPosition),

    // IDirectSoundBuffer_SetPosition+0x09 : mov eax, [ebp+arg_0]
    { 0x09, 0x8B },
    { 0x0A, 0x45 },
    { 0x0B, 0x08 },

    // IDirectSoundBuffer_SetPosition+0x28 : fstp [esp+0x10+var_10]
    { 0x28, 0xD9 },
    { 0x29, 0x1C },
    { 0x2A, 0x24 },

    // IDirectSoundBuffer_SetPosition+0x32 : retn 0x14
    { 0x33, 0x14 },
    { 0x34, 0x00 },
    //
);

// ******************************************************************
// * CMcpxAPU::Set3dPosition
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Set3dPosition,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_Set3dPosition+0x0C : movsd; movsd; movsd
    { 0x0C, 0xA5 },
    { 0x0D, 0xA5 },
    { 0x0E, 0xA5 },

    // CMcpxAPU_Set3dPosition+0x0F : or byte ptr [ecx+0x01B4], 0xFF
    { 0x0F, 0x80 },
    { 0x10, 0x89 },
    { 0x11, 0xB4 },
    { 0x12, 0x01 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0xFF },

    // CMcpxAPU_Set3dPosition+0x28 : retn 0x08
    { 0x28, 0xC2 },
    { 0x29, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_SetPosition+0x35 : call [CMcpxAPU_Set3dPosition]
    XREF_ENTRY(0x35, XREF_CMcpxAPU_Set3dPosition),

    // CDirectSound_SetPosition+0x06 : push esi; push edi
    { 0x06, 0x56 },
    { 0x07, 0x57 },

    // CDirectSound_SetPosition+0x24 : not eax; and eax, 1
    { 0x24, 0xF7 },
    { 0x25, 0xD0 },
    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0x01 },

    // CDirectSound_SetPosition+0x4F : retn 0x14
    { 0x4F, 0xC2 },
    { 0x50, 0x14 },
    //
);

// ******************************************************************
// * IDirectSound_SetPosition
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_SetPosition+0x2D : call [CDirectSound_SetPosition]
    XREF_ENTRY(0x2D, XREF_CDirectSound_SetPosition),

    // IDirectSound_SetPosition+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // IDirectSound_SetPosition+0x0C : sub esp, 0x0C
    { 0x0C, 0x83 },
    { 0x0D, 0xEC },
    { 0x0E, 0x0C },

    // IDirectSound_SetPosition+0x1B : neg ecx
    { 0x1B, 0xF7 },
    { 0x1C, 0xD9 },

    // IDirectSound_SetPosition+0x32 : retn 0x14
    { 0x32, 0xC2 },
    { 0x33, 0x14 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_Set3dVelocity
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Set3dVelocity,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_Set3dVelocity+0x09 : movsd; movsd; movsd
    { 0x09, 0xA5 },
    { 0x0A, 0xA5 },
    { 0x0B, 0xA5 },

    // CMcpxVoiceClient_Set3dVelocity+0x0C : or byte ptr [ecx+0x80], 0x40
    { 0x0C, 0x83 },
    { 0x0D, 0x89 },
    { 0x0E, 0x80 },
    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0x00 },
    { 0x12, 0x40 },

    // CMcpxVoiceClient_Set3dVelocity+0x25 : retn 0x08
    { 0x25, 0xC2 },
    { 0x26, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetVelocity+0x35 : call [CMcpxVoiceClient_Set3dVelocity]
    XREF_ENTRY(0x35, XREF_CMcpxVoiceClient_Set3dVelocity),

    // CDirectSoundVoice_SetVelocity+0x21 : mov eax, [ebp+0x18]
    { 0x21, 0x8B },
    { 0x22, 0x45 },
    { 0x23, 0x18 },

    // CDirectSoundVoice_SetVelocity+0x24 : not eax
    { 0x24, 0xF7 },
    { 0x25, 0xD0 },

    // CDirectSoundVoice_SetVelocity+0x26 : and eax, 1
    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0x01 },

    // CDirectSoundVoice_SetVelocity+0x31 : mov ecx, [eax+0x14]
    { 0x31, 0x8B },
    { 0x32, 0x48 },
    { 0x33, 0x14 },

    // CDirectSoundVoice_SetVelocity+0x4F : retn 0x14
    { 0x4F, 0xC2 },
    { 0x50, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetVelocity+0x24 : call [CDirectSoundVoice_SetVelocity]
    XREF_ENTRY(0x25, XREF_CDirectSoundVoice_SetVelocity),

    // CDirectSoundStream_SetVelocity+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // CDirectSoundStream_SetVelocity+0x0C : sub esp, 0x0C
    { 0x0C, 0x83 },
    { 0x0D, 0xEC },
    { 0x0E, 0x0C },

    // CDirectSoundStream_SetVelocity+0x2A : retn 0x14
    { 0x2A, 0xC2 },
    { 0x2B, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetVelocity+0x21 : call [CDirectSoundStream_SetVelocity]
    XREF_ENTRY(0x21, XREF_CDirectSoundStream_SetVelocity),

    // CDirectSoundStream_SetVelocity+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // CDirectSoundStream_SetVelocity+0x1A : fstp [esp]
    { 0x1A, 0xD9 },
    { 0x1B, 0x1C },
    { 0x1C, 0x24 },

    // CDirectSoundStream_SetVelocity+0x26 : retn 0x14
    { 0x26, 0xC2 },
    { 0x27, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetVelocity+0x20 : call [CDirectSoundVoice_SetVelocity]
    XREF_ENTRY(0x21, XREF_CDirectSoundVoice_SetVelocity),

    // CDirectSoundBuffer_SetVelocity+0x06 : fld [ebp+arg_C]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // CDirectSoundBuffer_SetVelocity+0x1A : fstp [esp+0x10+var_10]
    { 0x1A, 0xD9 },
    { 0x1B, 0x1C },
    { 0x1C, 0x24 },

    // CDirectSoundBuffer_SetVelocity+0x26 : retn 0x14
    { 0x27, 0x14 },
    { 0x28, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetVelocity
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetVelocity+0x2C : call [CDirectSoundBuffer::SetVelocity]
    XREF_ENTRY(0x2D, XREF_CDirectSoundBuffer_SetVelocity),

    // IDirectSoundBuffer_SetVelocity+0x09 : mov eax, [ebp+arg_0]
    { 0x09, 0x8B },
    { 0x0A, 0x45 },
    { 0x0B, 0x08 },

    // IDirectSoundBuffer_SetVelocity+0x28 : fstp [esp+0x10+var_10]
    { 0x28, 0xD9 },
    { 0x29, 0x1C },
    { 0x2A, 0x24 },

    // IDirectSoundBuffer_SetVelocity+0x32 : retn 0x14
    { 0x33, 0x14 },
    { 0x34, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetOutputBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetOutputBuffer,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetOutputBuffer+0x22 : call [CDirectSoundVoice_SetOutputBuffer]
    XREF_ENTRY(0x23, XREF_CDirectSoundVoice_SetOutputBuffer),

    // CDirectSoundStream_SetOutputBuffer+0x00 : push ebx
    { 0x00, 0x53 },

    // CDirectSoundStream_SetOutputBuffer+0x08 : mov esi, dword ptr[esp+10h]
    { 0x08, 0x8B },
    { 0x09, 0x74 },
    { 0x0A, 0x24 },
    { 0x0B, 0x10 },

    // CDirectSoundStream_SetOutputBuffer+0x1A : push dword ptr[esp+14h]
    { 0x1A, 0xFF },
    { 0x1B, 0x74 },
    { 0x1C, 0x24 },
    { 0x1D, 0x14 },

    // CDirectSoundStream_SetOutputBuffer+0x3D : retn 0x14
    { 0x3D, 0xC2 },
    { 0x3E, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetI3DL2Source
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetI3DL2Source,
                         3911)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },
    { 0x0A, 0x59 },
    { 0x10, 0x80 },
    { 0x16, 0x80 },
    { 0x1C, 0x5F },
    { 0x22, 0x8B },
    { 0x29, 0x33 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetI3DL2Source,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_CMcpxVoiceClient_SetI3DL2Source),

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x0E, 0xD0 },
    { 0x16, 0x10 },
    { 0x1E, 0xE8 },
    { 0x26, 0xF8 },
    { 0x2E, 0xFF },
    { 0x36, 0x5F },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetI3DL2Source,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSoundVoice_SetI3DL2Source),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0xFF },
    { 0x0E, 0x83 },
    { 0x12, 0xD9 },
    { 0x16, 0xC8 },
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetI3DL2Source,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSoundVoice_SetI3DL2Source),

    { 0x01, 0x74 },
    { 0x04, 0x8B },
    { 0x07, 0x08 },
    { 0x0A, 0x24 },
    { 0x0D, 0xC0 },
    { 0x10, 0xE8 },
    { 0x15, 0xC2 },
    { 0x16, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Lock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Lock,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x23, XREF_CDirectSoundBuffer_GetCurrentPosition),

    { 0x00, 0x55 },

    // CDirectSoundBuffer_Lock+0x37 : mov eax, [eax+0x4C]
    { 0x37, 0x8B },
    { 0x38, 0x40 },
    { 0x39, 0x4C },

    // CDirectSoundBuffer_Lock+0x68 : mov [edi], ebx; jz +0x1F
    { 0x68, 0x89 },
    { 0x69, 0x1F },
    { 0x6A, 0x74 },
    { 0x6B, 0x1F },

    // CDirectSoundBuffer_Lock+0x85 : and dword ptr [edx], 0
    { 0x85, 0x83 },
    { 0x86, 0x22 },
    { 0x87, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_Lock
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_Lock,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_Lock+0x28 : call [CDirectSoundBuffer_Lock]
    XREF_ENTRY(0x28, XREF_CDirectSoundBuffer_Lock),

    // IDirectSoundBuffer_Lock+0x03 : push [esp+0x24]
    { 0x03, 0xFF },
    { 0x04, 0x75 },
    { 0x05, 0x24 },

    // IDirectSoundBuffer_Lock+0x11 : add eax, 0xFFFFFFE4
    { 0x11, 0x83 },
    { 0x12, 0xC0 },
    { 0x13, 0xE4 },

    // IDirectSoundBuffer_Lock+0x2D : retn 0x20
    { 0x2D, 0xC2 },
    { 0x2E, 0x20 },
    //
);

// ******************************************************************
// * CMcpxBuffer_SetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_SetCurrentPosition,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_SetCurrentPosition+0x25 : mov eax, [esi+0x148]
    { 0x25, 0x8B },
    { 0x26, 0x86 },
    { 0x27, 0x48 },
    { 0x28, 0x01 },

    // CMcpxBuffer_SetCurrentPosition+0x4A : push edi; push 4
    { 0x4A, 0x57 },
    { 0x4B, 0x6A },
    { 0x4C, 0x04 },

    // CMcpxBuffer_SetCurrentPosition+0x71 : movzx eax, word ptr [eax+2]
    { 0x71, 0x0F },
    { 0x72, 0xB7 },
    { 0x73, 0x40 },
    { 0x74, 0x02 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetCurrentPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetCurrentPosition+0x15 : call [CMcpxBuffer_SetCurrentPosition]
    XREF_ENTRY(0x15, XREF_CMcpxBuffer_SetCurrentPosition),

    // CDirectSoundBuffer_SetCurrentPosition+0x0D : mov eax, [esp+0x10]
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x10 },

    // CDirectSoundBuffer_SetCurrentPosition+0x11 : mov ecx, [eax+0x20]
    { 0x11, 0x8B },
    { 0x12, 0x48 },
    { 0x13, 0x20 },

    // CDirectSoundBuffer_SetCurrentPosition+0x1D : jz +0x0B
    { 0x1D, 0x74 },
    { 0x1E, 0x0B },

    // CDirectSoundBuffer_SetCurrentPosition+0x2E : retn 0x08
    { 0x2E, 0xC2 },
    { 0x2F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetCurrentPosition
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetCurrentPosition,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetCurrentPosition+0x15 : call [CDirectSoundBuffer_SetCurrentPosition]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetCurrentPosition),

    // IDirectSoundBuffer_SetCurrentPosition+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetCurrentPosition+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetCurrentPosition+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * DSound_CRefCount_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DSound_CRefCount_AddRef,
                         3911)
OOVPA_SIG_MATCH(

    // DSound_CRefCount_AddRef+0x04 : add eax, 4
    { 0x00, 0x56 },

    // DSound_CRefCount_AddRef+0x0A : inc dword ptr [ecx+4]
    { 0x0A, 0xFF },
    { 0x0B, 0x41 },
    { 0x0C, 0x04 },

    // DSound_CRefCount_AddRef+0x0A : mov, dword ptr [ecx+4]
    { 0x0F, 0x8B },
    { 0x10, 0x71 },
    { 0x11, 0x04 },

    { 0x19, 0xFF },
    { 0x1A, 0x15 },

    // DSound_CRefCount_AddRef+0x22 : retn 0x04
    { 0x22, 0xC2 },
    { 0x23, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream::AddRef (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_AddRef,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream::AddRef
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_AddRef,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_AddRef+0x08 : call [CRefCount_AddRef]
    XREF_ENTRY(0x09, XREF_DSound_CRefCount_AddRef),

    // CDirectSoundStream_AddRef+0x04 : add eax, 4
    { 0x04, 0x83 },
    { 0x05, 0xC0 },
    { 0x06, 0x04 },

    // CDirectSoundStream_AddRef+0x0A : push eax
    { 0x07, 0x50 },

    // CDirectSoundStream_AddRef+0x08 : call [CRefCount_AddRef]
    { 0x08, 0xE8 },

    // CDirectSoundStream_AddRef+0x0D : retn 0x04
    { 0x0D, 0xC2 },
    { 0x0E, 0x04 },
    //
);

// ******************************************************************
// * DSound_CRefCount_Release
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DSound_CRefCount_Release,
                         3911)
OOVPA_SIG_MATCH(

    // DSound_CRefCount_Release+0x04 : add eax, 4
    { 0x00, 0x56 },

    // DSound_CRefCount_Release+0x0A : dec dword ptr [ecx+4]
    { 0x0B, 0xFF },
    { 0x0C, 0x49 },
    { 0x0D, 0x04 },

    // DSound_CRefCount_Release+0x0A : mov, dword ptr [ecx+4]
    { 0x0E, 0x8B },
    { 0x0F, 0x71 },
    { 0x10, 0x04 },

    { 0x26, 0xFF },
    { 0x27, 0x15 },

    // DSound_CRefCount_Release+0x30 : retn 0x04
    { 0x30, 0xC2 },
    { 0x31, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Release (dummy)
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Release,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * CDirectSoundStream_Release
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Release,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_Release+0x08 : call [CRefCount_Release]
    XREF_ENTRY(0x09, XREF_DSound_CRefCount_Release),

    // CDirectSoundStream_Release+0x04 : add eax, 4
    { 0x04, 0x83 },
    { 0x05, 0xC0 },
    { 0x06, 0x04 },

    // CDirectSoundStream_Release+0x0A : push eax
    { 0x07, 0x50 },

    // CDirectSoundStream_Release+0x08 : call [CRefCount_Release]
    { 0x08, 0xE8 },

    // CDirectSoundStream_Release+0x0D : retn 0x04
    { 0x0D, 0xC2 },
    { 0x0E, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound::GetCaps
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetCaps,
                         3911)
OOVPA_SIG_MATCH(

    { 0x08, 0x8B },
    { 0x12, 0x8D },
    { 0x1C, 0x0C },
    { 0x26, 0xFF },
    { 0x34, 0x03 },
    { 0x3A, 0xDB },
    { 0x48, 0x8B },
    { 0x4E, 0x08 },
    //
);

// ******************************************************************
// * IDirectSound_GetCaps
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_GetCaps,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSound_GetCaps),

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
// * CDirectSound_GetSpeakerConfig
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetSpeakerConfig,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x03, 0x04 },

    { 0x04, 0x8B },
    { 0x06, 0x08 },

    { 0x07, 0x8B },
    { 0x09, 0x08 },

    { 0x0A, 0x8B },
    { 0x0D, 0x08 },

    // CDirectSound_GetSpeakerConfig+0x0E : and eax, 7FFFFFFFh
    { 0x0E, 0x25 },
    { 0x0F, 0xFF },
    { 0x10, 0xFF },
    { 0x11, 0xFF },
    { 0x12, 0x7F },

    // CDirectSound_GetSpeakerConfig+0x17 : ret 8
    { 0x17, 0xC2 },
    { 0x18, 0x08 },
    //
);

// ******************************************************************
// * IDirectSound_GetSpeakerConfig
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_GetSpeakerConfig,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSound_GetSpeakerConfig),

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
// * CDirectSound_DownloadEffectsImage
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_DownloadEffectsImage,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_DownloadEffectsImage+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_DownloadEffectsImage+0x0A : mov esi,dword ptr [ebp+8]
    { 0x0A, 0x8B },
    { 0x0B, 0x75 },
    { 0x0C, 0x08 },

    // CDirectSound_DownloadEffectsImage+0x0D : push dword ptr [ebp+14h]
    { 0x0D, 0xFF },
    { 0x0E, 0x75 },
    { 0x0F, 0x14 },

    // CDirectSound_DownloadEffectsImage+0x10 : mov ecx,dword ptr [esi+8]
    { 0x10, 0x8B },
    { 0x11, 0x4E },
    { 0x12, 0x08 },

    // CDirectSound_DownloadEffectsImage+0x1A :  push dword ptr [ebp+18h]
    { 0x1A, 0xFF },
    //{ 0x1B, 0x75 },
    { 0x1C, 0x18 },

    // CDirectSound_DownloadEffectsImage+0x20 : push dword ptr [ebp+10h]
    { 0x20, 0xFF },
    //{ 0x21, 0x75 },
    { 0x22, 0x10 },

    // CDirectSound_DownloadEffectsImage+0x23 : push dword ptr [ebp+0Ch]
    { 0x23, 0xFF },
    //{ 0x24, 0x75 },
    { 0x25, 0x0C },

    // CDirectSound_DownloadEffectsImage+0x41 : ret 14h
    { 0x41, 0xC2 },
    { 0x42, 0x14 },
    //
);

// ******************************************************************
// * IDirectSound_DownloadEffectsImage
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_DownloadEffectsImage,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_CDirectSound_DownloadEffectsImage),

    // IDirectSound_DownloadEffectsImage+0x03 : push [ebp+0x18]
    { 0x03, 0xFF },
    { 0x04, 0x75 },
    { 0x05, 0x18 },

    // IDirectSound_DownloadEffectsImage+0x06 : mov eax, [ebp+0x08]
    { 0x06, 0x8B },
    { 0x07, 0x45 },
    { 0x08, 0x08 },

    // IDirectSound_DownloadEffectsImage+0x11 : add eax, 0xFFFFFFF8
    { 0x11, 0x83 },
    { 0x12, 0xC0 },
    { 0x13, 0xF8 },

    // IDirectSound_DownloadEffectsImage+0x24 : retn 0x14
    { 0x24, 0xC2 },
    { 0x25, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound_GetEffectData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetEffectData,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_GetEffectData+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_GetEffectData+0x0A : push dword ptr [ebp+18h]
    { 0x0A, 0xFF },
    { 0x0B, 0x75 },
    { 0x0C, 0x18 },

    // CDirectSound_GetEffectData+0x0F : push dword ptr [ebp+14h]
    { 0x0F, 0xFF },
    { 0x10, 0x75 },
    { 0x11, 0x14 },

    // CDirectSound_GetEffectData+0x12 : mov eax, dword ptr [ebp+8]
    { 0x12, 0x8B },
    { 0x13, 0x45 },
    { 0x14, 0x08 },

    // CDirectSound_GetEffectData+0x15 :  push dword ptr [ebp+10h]
    { 0x15, 0xFF },
    //{ 0x16, 0x75 },
    { 0x17, 0x10 },

    // CDirectSound_GetEffectData+0x18 : mov eax, dword ptr [eax+0Ch]
    { 0x18, 0x8B },
    //{ 0x19, 0x40 },
    { 0x1A, 0x0C },

    // CDirectSound_GetEffectData+0x1B : push dword ptr [ebp+0Ch]
    { 0x1B, 0xFF },
    //{ 0x1C, 0x75 },
    { 0x1D, 0x0C },

    // CDirectSound_GetEffectData+0x3F : ret 14h
    { 0x3F, 0xC2 },
    { 0x40, 0x14 },
    //
);

// ******************************************************************
// * IDirectSound_GetEffectData
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_GetEffectData,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_CDirectSound_GetEffectData),

    // IDirectSound_GetEffectData+0x03 : push [ebp+0x18]
    { 0x03, 0xFF },
    { 0x04, 0x75 },
    { 0x05, 0x18 },

    // IDirectSound_GetEffectData+0x06 : mov eax, [ebp+0x08]
    { 0x06, 0x8B },
    { 0x07, 0x45 },
    { 0x08, 0x08 },

    // IDirectSound_GetEffectData+0x11 : add eax, 0xFFFFFFF8
    { 0x11, 0x83 },
    { 0x12, 0xC0 },
    { 0x13, 0xF8 },

    // IDirectSound_GetEffectData+0x24 : retn 0x14
    { 0x24, 0xC2 },
    { 0x25, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound_SetEffectData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetEffectData,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_GetEffectData+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_GetEffectData+0x0A : mov ecx,dword ptr [ebp+1Ch]
    { 0x0A, 0x8B },
    { 0x0B, 0x4D },
    { 0x0C, 0x1C },

    // CDirectSound_GetEffectData+0x0A : push dword ptr [ebp+18h]
    { 0x13, 0xFF },
    { 0x14, 0x75 },
    { 0x15, 0x18 },

    // CDirectSound_GetEffectData+0x0F : push dword ptr [ebp+14h]
    { 0x18, 0xFF },
    { 0x19, 0x75 },
    { 0x1A, 0x14 },

    // CDirectSound_GetEffectData+0x12 : mov eax, dword ptr [ebp+8]
    { 0x1B, 0x8B },
    { 0x1C, 0x45 },
    { 0x1D, 0x08 },

    // CDirectSound_GetEffectData+0x15 :  push dword ptr [ebp+10h]
    { 0x1E, 0xFF },
    //{ 0x1F, 0x75 },
    { 0x20, 0x10 },

    // CDirectSound_GetEffectData+0x18 : mov eax, dword ptr [eax+0Ch]
    { 0x21, 0x8B },
    //{ 0x22, 0x40 },
    { 0x23, 0x0C },

    // CDirectSound_GetEffectData+0x1B : push dword ptr [ebp+0Ch]
    { 0x24, 0xFF },
    //{ 0x25, 0x75 },
    { 0x26, 0x0C },

    // CDirectSound_GetEffectData+0x3F : ret 18h
    { 0x48, 0xC2 },
    { 0x49, 0x18 },
    //
);

// ******************************************************************
// * IDirectSound_SetEffectData
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetEffectData,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x22, XREF_CDirectSound_SetEffectData),

    // IDirectSound_SetEffectData+0x03 : push [ebp+0x1C]
    { 0x03, 0xFF },
    { 0x04, 0x75 },
    { 0x05, 0x1C },

    // IDirectSound_SetEffectData+0x06 : mov eax, [ebp+0x08]
    { 0x06, 0x8B },
    { 0x07, 0x45 },
    { 0x08, 0x08 },

    // IDirectSound_SetEffectData+0x11 : add eax, 0xFFFFFFF8
    { 0x11, 0x83 },
    { 0x12, 0xC0 },
    { 0x13, 0xF8 },

    // IDirectSound_SetEffectData+0x27 : retn 0x18
    { 0x27, 0xC2 },
    { 0x28, 0x18 },
    //
);

// ******************************************************************
// * CDirectSound_CommitEffectData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CommitEffectData,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_CommitEffectData+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSound_CommitEffectData+0x08 : mov eax, dword ptr [esp+8]
    { 0x08, 0x8B },
    { 0x0B, 0x08 },

    // CDirectSound_CommitEffectData+0x0C : mov eax, dword ptr [esp+0Ch]
    { 0x0C, 0x8B },
    { 0x0E, 0x0C },

    // CDirectSound_CommitEffectData+0x15 : push 0; push 0
    { 0x15, 0x6A },
    { 0x16, 0x00 },
    { 0x17, 0x6A },
    { 0x18, 0x00 },

    // CDirectSound_CommitEffectData+0x20 : pop esi
    { 0x20, 0x5E },

    // CDirectSound_CommitEffectData+0x30 : retn 0x04
    { 0x30, 0xC2 },
    { 0x31, 0x04 },
    //
);

// ******************************************************************
// * IDirectSound_CommitEffectData
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_CommitEffectData,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSound_CommitEffectData),

    // IDirectSound_CommitEffectData+0x04 : mov ecx, eax
    { 0x04, 0x8B },
    { 0x05, 0xC8 },

    // IDirectSound_CommitEffectData+0x06 : add eax, 0xFFFFFFF8
    { 0x06, 0x83 },
    { 0x07, 0xC0 },
    { 0x08, 0xF8 },

    // IDirectSound_CommitEffectData+0x15 : retn 0x04
    { 0x15, 0xC2 },
    { 0x16, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound::EnableHeadphones
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_EnableHeadphones,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    { 0x25, 0x0F },
    { 0x26, 0x95 },
    { 0x27, 0xC2 },

    { 0x38, 0x81 },
    { 0x39, 0xCB },
    { 0x3A, 0x00 },
    { 0x3B, 0x00 },
    { 0x3C, 0x00 },
    { 0x3D, 0x80 },

    { 0x40, 0x81 },
    { 0x41, 0xE3 },
    { 0x42, 0xFF },
    { 0x43, 0xFF },
    { 0x44, 0xFF },
    { 0x45, 0x7F },

    { 0xCB, 0xC2 },
    { 0xCC, 0x08 },
    //
);

// ******************************************************************
// * IDirectSound_EnableHeadphones
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_EnableHeadphones,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSound_EnableHeadphones),

    // IDirectSound_EnableHeadphones+0x04 : push dword ptr [esp+8]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSound_EnableHeadphones+0x0A : add eax, 0xFFFFFFF8
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xF8 },

    // IDirectSound_EnableHeadphones+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CMcpxAPU_SetMixBinHeadroom
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_SetMixBinHeadroom_8,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_SetMixBinHeadroom+0x04 : cmp dword ptr ds:[0xFE820010], 4
    { 0x12, 0x83 },
    { 0x13, 0x3D },
    { 0x14, 0x10 },
    { 0x15, 0x00 },
    { 0x16, 0x82 },
    { 0x17, 0xFE },
    { 0x18, 0x04 },

    // CMcpxAPU_SetMixBinHeadroom+0x1F : and edx, 7
    { 0x1F, 0x83 },
    { 0x20, 0xE2 },
    { 0x21, 0x07 },

    // CMcpxAPU_SetMixBinHeadroom+0x2D : jl +0xD8
    { 0x2D, 0x7C },
    { 0x2E, 0xD8 },
    //
);

// ******************************************************************
// * CDirectSound_SetMixBinHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetMixBinHeadroom,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_SetMixBinHeadroom+0x18 : call [CMcpxAPU_SetMixBinHeadroom]
    XREF_ENTRY(0x19, XREF_CMcpxAPU_SetMixBinHeadroom),

    // CDirectSound_SetMixBinHeadroom+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CDirectSound_SetMixBinHeadroom+0x07 : push [esp+0x14]
    { 0x07, 0xFF },
    { 0x08, 0x74 },
    { 0x09, 0x24 },
    { 0x0A, 0x14 },

    // CDirectSound_SetMixBinHeadroom+0x21 : jz +0x0B
    { 0x21, 0x74 },
    { 0x22, 0x0B },
    //
);

// ******************************************************************
// * IDirectSound_SetMixBinHeadroom
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetMixBinHeadroom,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_SetMixBinHeadroom+0x19 : call [CDirectSound_SetMixBinHeadroom]
    XREF_ENTRY(0x19, XREF_CDirectSound_SetMixBinHeadroom),

    // IDirectSound_SetMixBinHeadroom+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSound_SetMixBinHeadroom+0x08 : mov ecx, eax
    { 0x08, 0x8B },
    { 0x09, 0xC8 },

    // IDirectSound_SetMixBinHeadroom+0x0E : add eax, 0xFFFFFFF8
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xF8 },

    // IDirectSound_SetMixBinHeadroom+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU::Set3dParameters
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
// TODO:
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Set3dParameters,
                         3911)
OOVPA_SIG_MATCH(

    { 0x05, 0x57 },
    { 0x0C, 0xB8 },
    { 0x13, 0x80 },
    { 0x1A, 0x83 },
    { 0x21, 0x74 },
    { 0x2C, 0x33 },
    { 0x2F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound::SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_CMcpxAPU_Set3dParameters),

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x0E, 0xD0 },
    { 0x16, 0x10 },
    { 0x1E, 0xE8 },
    { 0x26, 0xF8 },
    { 0x2E, 0xFF },
    { 0x36, 0x5F },
    //
);

// ******************************************************************
// * IDirectSound_SetAllParameters
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSound_SetAllParameters),

    // IDirectSound_SetAllParameters+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSound_SetAllParameters+0x08 : mov ecx, eax
    { 0x08, 0x8B },
    { 0x09, 0xC8 },

    // IDirectSound_SetAllParameters+0x0E : add eax, 0xFFFFFFF8
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xF8 },

    // IDirectSound_SetAllParameters+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU::Set3dDistanceFactor
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Set3dDistanceFactor,
                         3911)
OOVPA_SIG_MATCH(

    // Unique value difference against CMcpxAPU_Set3dDopperFactor's unique value.
    // CMcpxAPU_Set3dDistanceFactor+0x04 : or dword ptr [ecx+0x01B4], 0x60
    { 0x04, 0x83 },
    { 0x05, 0x89 },
    { 0x06, 0xB4 },
    { 0x07, 0x01 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x60 },

    // CMcpxAPU_Set3dDistanceFactor+0x0B : cmp [esp+0x08], 0
    { 0x0B, 0x83 },
    { 0x0C, 0x7C },
    { 0x0D, 0x24 },
    { 0x0E, 0x08 },

    // Unique value difference against CMcpxAPU_Set3dDopperFactor's unique value.
    // CMcpxAPU_Set3dDistanceFactor+0x12 : mov [ecx+0x0178], eax
    { 0x12, 0x78 },
    { 0x13, 0x01 },
    //
);

// ******************************************************************
// * CDirectSound_SetDistanceFactor
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetDistanceFactor,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDistanceFactor+0x23 : call [CMcpxAPU_Set3dDistanceFactor]
    XREF_ENTRY(0x23, XREF_CMcpxAPU_Set3dDistanceFactor),

    // CDirectSound_SetDistanceFactor+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CDirectSound_SetDistanceFactor+0x07 : fld [esp+0x10]
    { 0x07, 0xD9 },
    { 0x08, 0x44 },
    { 0x09, 0x24 },
    { 0x0A, 0x10 },

    // CDirectSound_SetDistanceFactor+0x11 : not eax; and eax, 1
    { 0x11, 0xF7 },
    { 0x12, 0xD0 },
    { 0x13, 0x83 },
    { 0x14, 0xE0 },
    { 0x15, 0x01 },
    //
);

// ******************************************************************
// * IDirectSound_SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetDistanceFactor,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_SetDistanceFactor+0x1D : call [CDirectSound_SetDistanceFactor]
    XREF_ENTRY(0x1D, XREF_CDirectSound_SetDistanceFactor),

    // IDirectSound_SetDistanceFactor+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSound_SetDistanceFactor+0x0C : push ecx
    { 0x0C, 0x51 },

    // IDirectSound_SetDistanceFactor+0x12 : add eax, 0xFFFFFFF8
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xF8 },

    // IDirectSound_SetDistanceFactor+0x21 : retn 0x0C
    { 0x21, 0xC2 },
    { 0x22, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU::Set3dDopplerFactor
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Set3dDopplerFactor,
                         3911)
OOVPA_SIG_MATCH(

    // Unique value difference against CMcpxAPU_Set3dDistanceFactor's unique value.
    // CMcpxAPU_Set3dDopplerFactor+0x04 : or dword ptr [ecx+0x01B4], 0x40
    { 0x04, 0x83 },
    { 0x05, 0x89 },
    { 0x06, 0xB4 },
    { 0x07, 0x01 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x40 },

    // CMcpxAPU_Set3dDopplerFactor+0x0B : cmp [esp+0x08], 0
    { 0x0B, 0x83 },
    { 0x0C, 0x7C },
    { 0x0D, 0x24 },
    { 0x0E, 0x08 },

    // Unique value difference against CMcpxAPU_Set3dDistanceFactor's unique value.
    // CMcpxAPU_Set3dDopplerFactor+0x12 : mov [ecx+0x0180], eax
    { 0x12, 0x80 },
    { 0x13, 0x01 },
    //
);

// ******************************************************************
// * CDirectSound::SetDopplerFactor
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetDopplerFactor,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x23, XREF_CMcpxAPU_Set3dDopplerFactor),

    { 0x07, 0xD9 },
    { 0x0E, 0x44 },
    { 0x16, 0x50 },
    { 0x1E, 0x0C },
    { 0x27, 0x85 },
    { 0x32, 0xFF },
    { 0x38, 0x8B },
    { 0x3E, 0x00 },
    //
);

// ******************************************************************
// * IDirectSound_SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetDopplerFactor,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1D, XREF_CDirectSound_SetDopplerFactor),

    // IDirectSound_SetDopplerFactor+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSound_SetDopplerFactor+0x0C : push ecx
    { 0x0C, 0x51 },

    // IDirectSound_SetDopplerFactor+0x12 : add eax, 0xFFFFFFF8
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xF8 },

    // IDirectSound_SetDopplerFactor+0x21 : retn 0x0C
    { 0x21, 0xC2 },
    { 0x22, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU::Set3dVelocity
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Set3dVelocity,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_Set3dVelocity+0x0C : movsd; movsd; movsd
    { 0x0C, 0xA5 },
    { 0x0D, 0xA5 },
    { 0x0E, 0xA5 },

    // CMcpxAPU_Set3dVelocity+0x0F : or dword ptr [ecx+0x01B4], 0x40
    { 0x0F, 0x83 },
    { 0x10, 0x89 },
    { 0x11, 0xB4 },
    { 0x12, 0x01 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x40 },

    // CMcpxAPU_Set3dVelocity+0x28 : retn 0x08
    { 0x28, 0xC2 },
    { 0x29, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound_SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_SetVelocity+0x35 : call [CMcpxAPU_Set3dVelocity]
    XREF_ENTRY(0x35, XREF_CMcpxAPU_Set3dVelocity),

    // CDirectSound_SetVelocity+0x06 : push esi; push edi
    { 0x06, 0x56 },
    { 0x07, 0x57 },

    // CDirectSound_SetVelocity+0x24 : not eax; and eax, 1
    { 0x24, 0xF7 },
    { 0x25, 0xD0 },
    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0x01 },

    // CDirectSound_SetVelocity+0x4F : retn 0x14
    { 0x4F, 0xC2 },
    { 0x50, 0x14 },
    //
);

// ******************************************************************
// * IDirectSound_SetVelocity
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetVelocity,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_SetVelocity+0x2D : call [CDirectSound_SetVelocity]
    XREF_ENTRY(0x2D, XREF_CDirectSound_SetVelocity),

    // IDirectSound_SetVelocity+0x06 : fld [ebp+0x14]
    { 0x06, 0xD9 },
    { 0x07, 0x45 },
    { 0x08, 0x14 },

    // IDirectSound_SetVelocity+0x0C : sub esp, 0x0C
    { 0x0C, 0x83 },
    { 0x0D, 0xEC },
    { 0x0E, 0x0C },

    // IDirectSound_SetVelocity+0x1B : neg ecx
    { 0x1B, 0xF7 },
    { 0x1C, 0xD9 },

    // IDirectSound_SetVelocity+0x32 : retn 0x14
    { 0x32, 0xC2 },
    { 0x33, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound_GetTime
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetTime,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSound_GetTime+0x00 : push dword ptr [esp+8]
    { 0x00, 0xFF },
    { 0x02, 0x24 },

    // CDirectSound_GetTime+0x04 : call dword ptr [KeQuerySystemTime]
    { 0x04, 0xFF },
    { 0x05, 0x15 },

    // CDirectSound_GetTime+0x0A : xor eax,eax
    { 0x0A, 0x33 },
    { 0x0B, 0xC0 },

    // CDirectSound_GetTime+0x0C : retn 0x08
    { 0x0C, 0xC2 },
    { 0x0D, 0x08 },
    //
);

// ******************************************************************
// * IDirectSound_GetTime
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_GetTime,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_GetTime+0x10 : call [CDirectSound_GetTime]
    XREF_ENTRY(0x15, XREF_CDirectSound_GetTime),

    // IDirectSound_GetTime+0x0A : and eax, 0xFFFFFFF8
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xF8 },

    // IDirectSound_GetTime+0x0D : neg ecx
    { 0x0D, 0xF7 },
    { 0x0E, 0xD9 },

    // IDirectSound_GetTime+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CMcpxAPU::Set3dRolloffFactor
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_Set3dRolloffFactor,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_Set3dRolloffFactor+0x04 : or dword ptr [ecx+0x01B4], 0x04
    { 0x04, 0x83 },
    { 0x05, 0x89 },
    { 0x06, 0xB4 },
    { 0x07, 0x01 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x04 },

    // CMcpxAPU_Set3dRolloffFactor+0x0B : cmp [esp+0x08], 0
    { 0x0B, 0x83 },
    { 0x0C, 0x7C },
    { 0x0D, 0x24 },
    { 0x0E, 0x08 },

    // CMcpxAPU_Set3dRolloffFactor+0x12 : mov [ecx+0x017C], eax
    { 0x12, 0x7C },
    { 0x13, 0x01 },
    //
);

// ******************************************************************
// * CDirectSound_SetRolloffFactor
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetRolloffFactor,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_SetRolloffFactor+0x23 : call [CMcpxAPU_Set3dRolloffFactor]
    XREF_ENTRY(0x23, XREF_CMcpxAPU_Set3dRolloffFactor),

    // CDirectSound_SetRolloffFactor+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CDirectSound_SetRolloffFactor+0x07 : fld [esp+0x10]
    { 0x07, 0xD9 },
    { 0x08, 0x44 },
    { 0x09, 0x24 },
    { 0x0A, 0x10 },

    // CDirectSound_SetRolloffFactor+0x11 : not eax; and eax, 1
    { 0x11, 0xF7 },
    { 0x12, 0xD0 },
    { 0x13, 0x83 },
    { 0x14, 0xE0 },
    { 0x15, 0x01 },
    //
);

// ******************************************************************
// * IDirectSound_SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_SetRolloffFactor,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_SetRolloffFactor+0x1D : call [CDirectSound_SetRolloffFactor]
    XREF_ENTRY(0x1D, XREF_CDirectSound_SetRolloffFactor),

    // IDirectSound_SetRolloffFactor+0x04 : fld [esp+0x0C]
    { 0x04, 0xD9 },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSound_SetRolloffFactor+0x0C : push ecx
    { 0x0C, 0x51 },

    // IDirectSound_SetRolloffFactor+0x12 : add eax, 0xFFFFFFF8
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xF8 },

    // IDirectSound_SetRolloffFactor+0x21 : retn 0x0C
    { 0x21, 0xC2 },
    { 0x22, 0x0C },
    //
);

// ******************************************************************
// * CMcpxAPU::SetI3DL2Listener
// ******************************************************************
// Generic OOVPA as of 3911 to 4039; 4134 and newer no longer have it.
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_SetI3DL2Listener,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxAPU_SetI3DL2Listener+0x08 : push 0x0C; pop ecx
    { 0x08, 0x6A },
    { 0x09, 0x0C },
    { 0x0A, 0x59 },

    // CMcpxAPU_SetI3DL2Listener+0x13 : or word ptr [ecx+0x01B4], 0x0180
    { 0x13, 0x66 },
    { 0x14, 0x81 },
    { 0x15, 0x88 },
    { 0x16, 0xB4 },
    { 0x17, 0x01 },
    { 0x18, 0x00 },
    { 0x1A, 0x80 },
    { 0x1B, 0x01 },

    // CMcpxAPU_SetI3DL2Listener+0x30 : retn 0x08
    { 0x30, 0xC2 },
    { 0x31, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound::SetI3DL2Listener
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetI3DL2Listener,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x2F, XREF_CMcpxAPU_SetI3DL2Listener),

    { 0x08, 0xF8 },
    { 0x12, 0x0C },
    { 0x1C, 0x18 },
    { 0x26, 0x51 },
    { 0x33, 0x8B },
    { 0x3E, 0xFF },
    { 0x44, 0x5F },
    //
);

// ******************************************************************
// * IDirectSound_SetI3DL2Listener
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSound_SetI3DL2Listener,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSound_SetI3DL2Listener),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0xFF },
    { 0x0E, 0x83 },
    { 0x12, 0xD9 },
    { 0x16, 0xC8 },
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVolume
// ******************************************************************
// NOTE: IDirectSoundStream_SetVolume has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetVolume,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetVolume+0x0C : call [CMcpxVoiceClient_SetVolume]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetVolume),

    // CDirectSoundStream_SetVolume+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetVolume+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetVolume+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetVolume
// ******************************************************************
// NOTE: CDirectSoundStream_SetVolume has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetVolume,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetVolume+0x0C : call [CMcpxVoiceClient_SetVolume]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetVolume),

    // IDirectSoundStream_SetVolume+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetVolume+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetVolume+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetPitch
// ******************************************************************
// NOTE: IDirectSoundStream_SetPitch has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetPitch,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetPitch+0x0C : call [CMcpxVoiceClient_SetPitch]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetPitch),

    // CDirectSoundStream_SetPitch+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetPitch+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetPitch+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetPitch
// ******************************************************************
// NOTE: CDirectSoundStream_SetPitch has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetPitch,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetPitch+0x0C : call [CMcpxVoiceClient_SetPitch]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetPitch),

    // IDirectSoundStream_SetPitch+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetPitch+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetPitch+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetLFO
// ******************************************************************
// NOTE: IDirectSoundStream_SetLFO has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetLFO,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetLFO+0x0C : call [CMcpxVoiceClient_SetLFO]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetLFO),

    // CDirectSoundStream_SetLFO+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetLFO+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetLFO+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetLFO
// ******************************************************************
// NOTE: CDirectSoundStream_SetLFO has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetLFO,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetLFO+0x0C : call [CMcpxVoiceClient_SetLFO]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetLFO),

    // IDirectSoundStream_SetLFO+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetLFO+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetLFO+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetEG
// ******************************************************************
// NOTE: IDirectSoundStream_SetEG has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetEG,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetEG+0x0C : call [CMcpxVoiceClient_SetEG]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetEG),

    // CDirectSoundStream_SetEG+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetEG+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetEG+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetEG
// ******************************************************************
// NOTE: CDirectSoundStream_SetEG has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetEG,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetEG+0x0C : call [CMcpxVoiceClient_SetEG]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetEG),

    // IDirectSoundStream_SetEG+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetEG+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetEG+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetFilter
// ******************************************************************
// NOTE: IDirectSoundStream_SetFilter has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetFilter,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetFilter+0x0C : call [CMcpxVoiceClient_SetFilter]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetFilter),

    // CDirectSoundStream_SetFilter+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetFilter+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetFilter+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetFilter,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetFilter+0x0C : call [CMcpxVoiceClient_SetFilter]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetFilter),

    // IDirectSoundStream_SetFilter+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetFilter+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetFilter+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetHeadroom
// ******************************************************************
// NOTE: IDirectSoundStream_SetHeadroom has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetHeadroom,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetHeadroom+0x0C : call [CDirectSoundVoice_SetHeadroom]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetHeadroom),

    // CDirectSoundStream_SetHeadroom+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetHeadroom+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetHeadroom+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetHeadroom
// ******************************************************************
// NOTE: CDirectSoundStream_SetHeadroom has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetHeadroom,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetHeadroom+0x0C : call [CDirectSoundVoice_SetHeadroom]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetHeadroom),

    // IDirectSoundStream_SetHeadroom+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetHeadroom+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetHeadroom+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetFrequency
// ******************************************************************
// NOTE: IDirectSoundStream_SetFrequency has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetFrequency,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetFrequency+0x0C : call [CDirectSoundVoice_SetFrequency]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetFrequency),

    // CDirectSoundStream_SetFrequency+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetFrequency+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetFrequency+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetFrequency
// ******************************************************************
// NOTE: CDirectSoundStream_SetFrequency has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetFrequency,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetFrequency+0x0C : call [CDirectSoundVoice_SetFrequency]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetFrequency),

    // IDirectSoundStream_SetFrequency+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetFrequency+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetFrequency+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMixBins
// ******************************************************************
// NOTE: IDirectSoundStream_SetMixBins has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(CDirectSoundStream_SetMixBins,
                             3911,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_SetMixBins+0x0C : call [CDirectSoundVoice_SetMixBins]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetMixBins),

    // CDirectSoundStream_SetMixBins+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // CDirectSoundStream_SetMixBins+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // CDirectSoundStream_SetMixBins+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMixBins
// ******************************************************************
// NOTE: CDirectSoundStream_SetMixBins has the same asm code as this function.
OOVPA_SIG_HEADER_XREF_DETECT(IDirectSoundStream_SetMixBins,
                             3911,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetMixBins+0x0C : call [CDirectSoundVoice_SetMixBins]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoice_SetMixBins),

    // IDirectSoundStream_SetMixBins+0x04 : mov eax, [esp+0x08]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundStream_SetMixBins+0x08 : add eax, 0x04
    { 0x08, 0x83 },
    { 0x09, 0xC0 },
    { 0x0A, 0x04 },

    // IDirectSoundStream_SetMixBins+0x11 : retn 0x08
    { 0x11, 0xC2 },
    { 0x12, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetOutputBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetOutputBuffer,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetOutputBuffer+0x00 : jmp [CDirectSoundStream_SetOutputBuffer]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetOutputBuffer),

    // IDirectSoundStream_SetOutputBuffer+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMixBinVolumes
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetMixBinVolumes_12,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetMixBinVolumes_12+0x00 : jmp [CDirectSoundStream_SetMixBinVolumes_12]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetMixBinVolumes_12),

    // IDirectSoundStream_SetMixBinVolumes_12+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetAllParameters+0x00 : jmp [CDirectSoundStream_SetAllParameters]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetAllParameters),

    // IDirectSoundStream_SetAllParameters+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetConeAngles,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetConeAngles+0x00 : jmp [CDirectSoundStream_SetConeAngles]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetConeAngles),

    // IDirectSoundStream_SetConeAngles+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetConeOutsideVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetConeOutsideVolume+0x00 : jmp [CDirectSoundStream_SetConeOutsideVolume]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetConeOutsideVolume),

    // IDirectSoundStream_SetConeOutsideVolume+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetMode,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetMode+0x00 : jmp [CDirectSoundStream_SetMode]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetMode),

    // IDirectSoundStream_SetMode+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetI3DL2Source
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetI3DL2Source,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetI3DL2Source+0x00 : jmp [CDirectSoundStream_SetI3DL2Source]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetI3DL2Source),

    // IDirectSoundStream_SetI3DL2Source+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_Pause
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_Pause,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_Pause+0x00 : jmp [CDirectSoundStream_Pause]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_Pause),

    // IDirectSoundStream_Pause+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CMcpxStream_Pause
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Pause,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxStream_Pause+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxStream_Pause+0x16 : mov eax,[esi+XX]
    { 0x16, 0x8B },
    { 0x17, 0x46 },

    // CMcpxStream_Pause+0x19 : or eax,4
    { 0x19, 0x83 },
    { 0x1A, 0xC8 },
    { 0x1B, 0x04 },

    // CMcpxStream_Pause+0x27 : and eax,-5
    { 0x27, 0x83 },
    { 0x28, 0xE0 },
    { 0x29, 0xFB },

    // CMcpxStream_Pause+0x44 : leave; retn 0x04
    { 0x44, 0xC9 },
    { 0x45, 0xC2 },
    { 0x46, 0x04 },
    //
);

// ******************************************************************
// * XAudioCreatePcmFormat
// ******************************************************************
// Generic OOVPA as of 3911 and newer
// NOTE: 4134 and later versions changed to a jmp, then convert into
// class function
OOVPA_SIG_HEADER_NO_XREF(XAudioCreatePcmFormat,
                         3911)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x11, 0x02),
    OV_MATCH(0x18, 0x0E),
    OV_MATCH(0x2E, 0x10),

    //XAudioCreatePcmFormat+0x10 : mov word ptr [ecx],1
    OV_MATCH(0x34, 0x66, 0xC7, 0x01, 0x01, 0x00),

    OV_MATCH(0x47, 0xC2, 0x10),
    //
);

// ******************************************************************
// * XAudioCreateAdpcmFormat
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XAudioCreateAdpcmFormat,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x04, 0x8B },
    { 0x09, 0x8B },

    //XAudioCreateAdpcmFormat+0x10 : mov word ptr [edx],69h
    { 0x10, 0x66 },
    { 0x11, 0xC7 },
    { 0x12, 0x02 },
    { 0x13, 0x69 },
    { 0x14, 0x00 },

    { 0x20, 0x04 },

    { 0x22, 0xE8 },

    { 0x38, 0x02 },

    { 0x3E, 0x40 },

    { 0x41, 0xC2 },
    { 0x42, 0x0C },
    //
);

// ******************************************************************
// * IsValidFormat
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(IsValidFormat,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x04, 0x0F },
    { 0x07, 0x48 },

    //IsValidFormat+0x10 : sub eax,68h
    { 0x0A, 0x83 },
    { 0x0B, 0xE8 },
    { 0x0C, 0x68 },

    { 0x14, 0xE8 },

    { 0x1C, 0xE8 },

    { 0x21, 0xC2 },
    { 0x22, 0x04 },
    //
);

// ******************************************************************
// * XFileCreateMediaObject
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XFileCreateMediaObject,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x08, 0xE8 },

    { 0x0D, 0x85 },
    { 0x0E, 0xC0 },

    { 0x0F, 0x74 },
    { 0x10, 0x16 },

    { 0x11, 0x83 },
    { 0x12, 0x60 },
    { 0x13, 0x04 },
    { 0x14, 0x00 },

    { 0x15, 0xC7 },
    { 0x16, 0x00 },

    { 0x78, 0xC2 },
    { 0x79, 0x18 },
    //
);

// ******************************************************************
// * XWaveFileCreateMediaObject
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XWaveFileCreateMediaObject,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x07, 0x5C },

    { 0x53, 0x8B },
    { 0x54, 0x4D },
    { 0x55, 0x10 },
    { 0x56, 0x89 },
    { 0x57, 0x01 },
    { 0x58, 0x8D },
    { 0x59, 0x45 },
    { 0x5A, 0xFC },
    { 0x5B, 0x50 },
    { 0x5C, 0xE8 },

    { 0x65, 0xC2 },
    { 0x66, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBufferSettings::SetBufferData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBufferSettings_SetBufferData,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSoundBufferSettings::SetBufferData+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBufferSettings::SetBufferData+0x0C : mov edx,0x80000000
    { 0x0C, 0xBB },
    { 0x0D, 0x00 },
    //{ 0x0E, 0x00 },
    { 0x0F, 0x00 },
    { 0x10, 0x80 },

    // CDirectSoundBufferSettings::SetBufferData+0x1D : jmp +0x06
    { 0x1D, 0xEB },
    { 0x1E, 0x06 },

    // This offset is unique.
    // CDirectSoundBufferSettings::SetBufferData+0x3D : and byte [esi+0x0F],0x7F
    { 0x3D, 0x80 },
    { 0x3E, 0x66 },
    //{ 0x3F, 0x0F },
    { 0x40, 0x7F },

    // CDirectSoundBufferSettings::SetBufferData+0x6F : ret 8
    { 0x6F, 0xC2 },
    { 0x70, 0x08 },
    //
);

// ******************************************************************
// * CMcpxBuffer::SetBufferData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_SetBufferData,
                         3911)
OOVPA_SIG_MATCH(

    // CMcpxBuffer::SetBufferData+0x00 : mov edx,[ecx+0x000000XX]
    { 0x00, 0x8B },
    { 0x01, 0x91 },

    // CMcpxBuffer::SetBufferData+0x06 : xor eax, eax
    { 0x06, 0x33 },
    { 0x07, 0xC0 },

    // This asm code is unique.
    // CMcpxBuffer::SetBufferData+0x08 : test byte [edx+0x0E], 4
    { 0x08, 0xF6 },
    { 0x09, 0x42 },
    //{ 0x0A, 0x0E }, 3911 0x0E vs 4039 0x0A
    { 0x0B, 0x04 },

    // CMcpxBuffer::SetBufferData+0x0E : jmp
    { 0x0E, 0xE9 },

    // CMcpxBuffer::SetBufferData+0x13 : ret
    { 0x13, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetAllParameters,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetAllParameters+0x00 : jmp CDirectSoundVoice::SetAllParameters
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetAllParameters),

    // CDirectSoundBuffer::SetAllParameters+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeAngles,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetConeAngles+0x00 : jmp CDirectSoundVoice::SetConeAngles
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetConeAngles),

    // CDirectSoundBuffer::SetConeAngles+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetEG,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetEG+0x00 : jmp CDirectSoundVoice::SetEG
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetEG),

    // CDirectSoundBuffer::SetEG+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFilter,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetFilter+0x00 : jmp CDirectSoundVoice::SetFilter
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetFilter),

    // CDirectSoundBuffer::SetFilter+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetHeadroom,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetHeadroom+0x00 : jmp CDirectSoundVoice::SetHeadroom
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetHeadroom),

    // CDirectSoundBuffer::SetHeadroom+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetFrequency
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFrequency,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetFrequency+0x00 : jmp CDirectSoundVoice::SetFrequency
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetFrequency),

    // CDirectSoundBuffer::SetFrequency+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetI3DL2Source,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetI3DL2Source+0x00 : jmp CDirectSoundVoice::SetI3DL2Source
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetI3DL2Source),

    // CDirectSoundBuffer::SetI3DL2Source+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetLFO,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetLFO+0x00 : jmp CDirectSoundVoice::SetLFO
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetLFO),

    // CDirectSoundBuffer::SetLFO+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMixBins
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMixBins,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetMixBins+0x00 : jmp CDirectSoundVoice::SetMixBins
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetMixBins),

    // CDirectSoundBuffer::SetMixBins+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMixBinVolumes
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMixBinVolumes_12,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetMixBinVolumes+0x00 : jmp CDirectSoundVoice::SetMixBinVolumes
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetMixBinVolumes),

    // CDirectSoundBuffer::SetMixBinVolumes+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMode,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetMode+0x00 : jmp CDirectSoundVoice::SetMode
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetMode),

    // CDirectSoundBuffer::SetMode+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetPitch,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetPitch+0x00 : jmp CDirectSoundVoice::SetPitch
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetPitch),

    // CDirectSoundBuffer:SetPitch:+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetVolume,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer::SetVolume+0x00 : jmp CDirectSoundVoice::SetVolume
    XREF_ENTRY(0x01, XREF_CDirectSoundVoice_SetVolume),

    // CDirectSoundBuffer::SetVolume+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Constructor
// ******************************************************************
// Generic OOVPA as of 3911 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Constructor,
                         3911)
OOVPA_SIG_MATCH(

    // CDirectSoundStream::Constructor+0x00 : push esi; mov esi, ecx; push edi
    OV_MATCH(0x00, 0x56, 0x8B, 0xF1, 0x57),

    // CDirectSoundStream::Constructor+0x08 : lea edi,[esi+0x04]
    OV_MATCH(0x08, 0x8D, 0x7E, 0x04),

    // CDirectSoundStream::Constructor+0x12 : mov [edi], XREF_DSS_VOICE_VTABLE
    OV_MATCH(0x12, 0xC7, 0x07),

    // CDirectSoundStream::Constructor+0x19 : mov [esi], XREF_DSS_STREAM_VTABLE
    OV_MATCH(0x19, 0xC7, 0x06),

    // CDirectSoundStream::Constructor+0x22 : ret 0x0004
    OV_MATCH(0x22, 0xC2, 0x04),
    //
);
