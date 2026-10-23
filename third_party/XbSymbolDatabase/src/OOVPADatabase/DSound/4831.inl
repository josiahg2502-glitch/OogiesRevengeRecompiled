// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// CMcpxAPU::SynchPlayback
// ******************************************************************
// Generic OOVPA as of 4831 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_SynchPlayback,
                         4831)
OOVPA_SIG_MATCH(
    { 0x00, 0x55 },

    //{ 0x0C, 0x74 }, // vs 5344 0x3C
    { 0x1A, 0x1A },
    { 0x25, 0x53 },
    { 0x37, 0xF2 },
    //{ 0x58, 0xBC }, // vs 5344 0x84

    { 0x7F, 0x47 },
    { 0x80, 0x04 },

    { 0x84, 0x43 },

    { 0x9E, 0x64 },
    { 0xFF, 0x00 },
    //
);

// ******************************************************************
// * CDirectSound::SynchPlayback
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SynchPlayback,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x08, XREF_CMcpxAPU_SynchPlayback),

    // CDirectSound_SynchPlayback+0x00 : mov eax, [esp+0x04]
    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // CDirectSound_SynchPlayback+0x04 : mov ecx, [eax+0x0C]
    { 0x04, 0x8B },
    { 0x05, 0x48 },
    { 0x06, 0x0C },

    // CDirectSound_SynchPlayback+0x0C : retn 0x04
    { 0x0C, 0xC2 },
    { 0x0D, 0x04 },
    //
);

// ******************************************************************
// * IDirectSound::SynchPlayback
// ******************************************************************
// Generic OOVPA as of 4831 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_SynchPlayback,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x11, XREF_CDirectSound_SynchPlayback),

    // IDirectSound_SynchPlayback+0x06 : add eax, 0xFFFFFFF8
    { 0x06, 0x83 },
    { 0x07, 0xC0 },
    { 0x08, 0xF8 },

    // IDirectSound_SynchPlayback+0x0B : sbb ecx, ecx
    { 0x0B, 0x1B },
    { 0x0C, 0xC9 },

    // IDirectSound_SynchPlayback+0x15 : retn 0x04
    { 0x15, 0xC2 },
    { 0x16, 0x04 },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetStatus
// ******************************************************************
// Generic OOVPA as of 4831 and newer
OOVPA_NO_XREF(CMcpxBuffer_GetStatus, 4831, 11)
    {

        // CMcpxBuffer_GetStatus+0x00 : movzx eax,word [ecx+0x12]
        { 0x00, 0x0F },
            { 0x01, 0xB7 },
        //{ 0x02, 0x41 },
        //{ 0x03, 0x12 },

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

            // This asm code is unique.
            // CMcpxBuffer_GetStatus+0x12 : test ax, 0x0444
            { 0x12, 0x66 },
            { 0x13, 0xA9 },
            { 0x14, 0x44 },
            { 0x15, 0x04 },

            { 0x3F, 0xC2 },
            { 0x40, 0x04 },
    }
OOVPA_END;

// ******************************************************************
// * CMcpxBuffer::Play(unsigned long)
// ******************************************************************
// Generic OOVPA as of 4831 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Play,
                         4831)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Play+0x00 : push ebx
    { 0x00, 0x53 },

    // CMcpxBuffer_Play+0x32 : test byte ptr [esi+12h], 42h
    { 0x32, 0xF6 },
    { 0x33, 0x46 },
    { 0x34, 0x12 },
    { 0x35, 0x42 },

    // CMcpxBuffer_Play+0x4D : test byte ptr [eax+9], 20h
    { 0x4D, 0xF6 },
    { 0x4E, 0x40 },
    { 0x4F, 0x09 },
    { 0x50, 0x20 },

    // CMcpxBuffer_Play+0x71 : xor eax, eax
    { 0x71, 0x33 },
    { 0x72, 0xC0 },
    //
);

// ******************************************************************
// * CMcpxStream_Pause
// ******************************************************************
// Generic OOVPA as of ____? and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Pause,
                         4831)
OOVPA_SIG_MATCH(

    // CMcpxStream_Pause+0x17 : and ax, 0xFFDF
    { 0x17, 0x66 },
    { 0x18, 0x25 },
    { 0x19, 0xDF },

    // CMcpxStream_Pause+0x32 : jmp +0x56
    { 0x32, 0xEB },
    { 0x33, 0x56 },

    // CMcpxStream_Pause+0x39 : movzx eax, word ptr [esi+0x12]
    { 0x39, 0x0F },
    { 0x3A, 0xB7 },
    { 0x3B, 0x46 },
    { 0x3C, 0x12 },

    // CMcpxStream_Pause+0x8B : retn 0x04
    { 0x8B, 0xC2 },
    { 0x8C, 0x04 },
    //
);

// ******************************************************************
// * CMcpxBuffer::Pause(unsigned long)
// ******************************************************************
// Generic OOVPA as of 4831 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Pause,
                         4831)
OOVPA_SIG_MATCH(

    // CMcpxBuffer::Pause+0x00 : push ebp
    { 0x00, 0x55 },

    // Offset is unique for this asm code.
    // CMcpxBuffer::Pause+0x27 : and eax, -0xBB
    { 0x27, 0x83 },
    { 0x28, 0xE0 },
    { 0x29, 0xBB },

    // CMcpxBuffer::Pause+0x2D : call [?]
    { 0x2D, 0xE8 },

    // Offset is unique for this asm code.
    // CMcpxBuffer::Pause+0x40 : and eax, -0xBF
    { 0x40, 0x83 },
    { 0x41, 0xE0 },
    { 0x42, 0xBF },

    // CMcpxBuffer::Pause+0x70 : ret 4
    { 0x70, 0xC2 },
    { 0x71, 0x04 },

    //
);
