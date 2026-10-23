// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CMcpxStream_GetStatus
// ******************************************************************
// Generic OOVPA as of 4721 and newer;
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_GetStatus,
                         4721)
OOVPA_SIG_MATCH(

    { 0x00, 0x0F },

    { 0x09, 0x00 },
    { 0x0A, 0x33 },
    { 0x0B, 0xC9 },
    { 0x0C, 0x39 },
    { 0x0D, 0x00 },
    { 0x0E, 0x8B },
    { 0x0F, 0x44 },
    { 0x10, 0x24 },
    { 0x11, 0x04 },
    { 0x12, 0x0F },
    { 0x13, 0x95 },

    { 0x1C, 0x80 },
    { 0x41, 0x00 },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetStatus
// ******************************************************************
OOVPA_NO_XREF(CMcpxBuffer_GetStatus, 4721, 11)
    {

        // CMcpxBuffer_GetStatus+0x00 : movzx eax,word [ecx+0x12]
        { 0x00, 0x0F },
            { 0x01, 0xB7 },
            { 0x02, 0x41 },
            { 0x03, 0x12 },

#if 0
        // Offset is unique for this asm code.
        // CMcpxBuffer_GetStatus+0x06 : and ecx, 0x03
        { 0x06, 0x83 },
        { 0x07, 0xE1 },
        { 0x08, 0x03 },
#endif

            // Offset is unique for this asm code.
            // CMcpxBuffer_GetStatus+0x09 : cmp cl, 0x03
            { 0x09, 0x80 },
            { 0x0A, 0xF9 },
            { 0x0B, 0x03 },

            // Offset is unique for this asm code.
            // CMcpxBuffer_GetStatus+0x12 : test al, 0x04
            { 0x12, 0xA8 },
            { 0x13, 0x04 },

            { 0x3D, 0xC2 },
            { 0x3E, 0x04 },
    }
OOVPA_END;

// ******************************************************************
// * CMcpxBuffer::Pause(unsigned long)
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Pause,
                         4721)
OOVPA_SIG_MATCH(

    // CMcpxBuffer::Pause+0x00 : push ebp
    { 0x00, 0x55 },

    { 0x14, 0x8A },
    { 0x20, 0x01 },

    // CMcpxBuffer::Pause+0x21 : jne +0x04
    { 0x21, 0x75 },
    { 0x22, 0x04 },

    // CMcpxBuffer::Pause+0x23 : push 0x04
    { 0x23, 0x6A },
    { 0x24, 0x04 },

    // CMcpxBuffer::Pause+0x25 : jmp +0x08
    { 0x25, 0xEB },
    { 0x26, 0x08 },

    { 0x27, 0x83 },

    // CMcpxBuffer::Pause+0x42 : ret 4
    { 0x42, 0xC2 },
    { 0x43, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::PauseEx
// ******************************************************************
// Generic OOVPA as of 4721 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_PauseEx,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3D, XREF_CMcpxBuffer_Pause_Ex),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x41, 0x85 },
    { 0x4C, 0xFF },
    { 0x53, 0xC7 },

    { 0x56, 0xC2 },
    { 0x57, 0x10 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_PauseEx
// ******************************************************************
// Generic OOVPA as of 4721 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_PauseEx,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_PauseEx),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x12, 0x83 },
    { 0x16, 0xD9 },
    { 0x1A, 0xC8 },
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * CMcpxBuffer::Pause(__int64, unsigned long)
// ******************************************************************
// Generic OOVPA as of 4721 and newer
OOVPA_SIG_HEADER_XREF(CMcpxBuffer_Pause_Ex,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x2B, XREF_CMcpxBuffer_Pause),

    { 0x00, 0x55 },

    { 0x0D, 0x8B },

    { 0x1C, 0x6A },
    { 0x1D, 0x05 },

    { 0x23, 0x75 },

    { 0x2A, 0xE8 },

    { 0x36, 0xC2 },
    { 0x37, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::Pause
// ******************************************************************
// Generic OOVPA as of 4721 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Pause,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CMcpxBuffer_Pause),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x14, 0x74 },
    { 0x21, 0xB8 },
    { 0x2A, 0x24 },
    { 0x39, 0x85 },
    { 0x44, 0xFF },
    { 0x4B, 0xC7 },
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_Pause
// ******************************************************************
// Generic OOVPA as of 4721 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_Pause,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_Pause),

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
// * CMcpxBuffer::Play(unsigned long)
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Play,
                         4721)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Play+0x00 : push ebx
    { 0x00, 0x53 },

    // CMcpxBuffer_Play+0x2E : test byte ptr [eax+9], 20h
    { 0x2E, 0xF6 },
    { 0x2F, 0x40 },
    { 0x30, 0x09 },
    { 0x31, 0x20 },

    // CMcpxBuffer_Play+0x44 : test byte ptr [esi+12h], 2h
    { 0x44, 0xF6 },
    { 0x45, 0x46 },
    { 0x46, 0x12 },
    { 0x47, 0x02 },

    // CMcpxBuffer_Play+0x52 : xor eax, eax
    { 0x52, 0x33 },
    { 0x53, 0xC0 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetFormat
// ******************************************************************
// Generic OOVPA as of 4721 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetFormat,
                      4721,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetFormat+0x2F : call [CMcpxVoiceClient::SetMixBins]
    XREF_ENTRY(0x30, XREF_CMcpxVoiceClient_SetMixBins),

    // CDirectSoundVoice::SetFormat+0x3B : call [CMcpxVoiceClient::SetPitch]
    XREF_ENTRY(0x3C, XREF_CMcpxVoiceClient_SetPitch),

    // CDirectSoundVoice::SetFormat+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundVoice::SetFormat+0x08 : push 0x01
    { 0x08, 0x6A },
    { 0x09, 0x01 },

    // CDirectSoundVoice::SetFormat+0x41 : ret 0x08
    { 0x41, 0xC2 },
    { 0x42, 0x08 },
    //
);
