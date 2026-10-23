// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMinDistance,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMinDistance+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetMinDistance+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetMinDistance+0x11 : mov [eax+38h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x38 }, // SetMinDistance 0x38 VS SetMaxDistance 0x3C

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x02 },

    // CDirectSoundVoice_SetMinDistance+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetDistanceFactor,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetDistanceFactor+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetDistanceFactor+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetDistanceFactor+0x11 : mov [eax+44h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x44 },

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x02 },

    // CDirectSoundVoice_SetDistanceFactor+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetDopplerFactor,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetDopplerFactor+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetDopplerFactor+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetDopplerFactor+0x12 : mov [eax+4Ch], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x4C },

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x03 },

    // CDirectSoundVoice_SetDopplerFactor+0x31 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMaxDistance
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMaxDistance,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMaxDistance+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetMaxDistance+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetMaxDistance+0x11 : mov [eax+3Ch], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x3C }, // SetMinDistance 0x38 VS SetMaxDistance 0x3C

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x02 },

    // CDirectSoundVoice_SetMaxDistance+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// CDirectSoundVoice::SetMode
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMode,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMode+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    { 0x00, 0x8B },

    { 0x09, 0xB4 },
    { 0x10, 0x08 },

    { 0x13, 0x40 },

    { 0x14, 0x8B },
    { 0x15, 0x41 },

    { 0x1D, 0x80 },
    { 0x1F, 0x02 },
    { 0x20, 0x40 },

    { 0x2E, 0x33 },

    { 0x30, 0xC2 },
    { 0x31, 0x0C },
    //
);

// ******************************************************************
// * CDirectSound_SetPosition
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetPosition,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSound_SetPosition+0x00 : push ebp; mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // CDirectSound_SetPosition+0x2B : mov ecx, [ebp+0x08]
    OV_MATCH(0x2B, 0x8B, 0x4D, 0x08),

    // CDirectSound_SetPosition+0x37 : mov [edx+0x3C],edi
    OV_MATCH(0x37, 0x89, 0x7A, 0x3C),

    // CDirectSound_SetPosition+0x3F : mov [edx+0x40],edi
    OV_MATCH(0x3F, 0x89, 0x7A, 0x40),

    // CDirectSound_SetPosition+0x47 : mov [edx+0x44],edi
    OV_MATCH(0x47, 0x89, 0x7A, 0x44),

    //
);

// ******************************************************************
// * CDirectSound::SetVelocity
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetVelocity,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSound_SetVelocity+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_SetVelocity+0x2B : mov ecx, [ebp+0x08]
    { 0x2B, 0x8B },
    { 0x2C, 0x4D },
    { 0x2D, 0x08 },

    // CDirectSound_SetVelocity+0x2E : lea eax, [ecx+0x08]
    { 0x2E, 0x8D },
    { 0x2F, 0x41 },
    { 0x30, 0x08 },

    // CDirectSound_SetVelocity+0x37 : mov [edx+0x__], edi
    { 0x37, 0x89 },
    { 0x38, 0x7A },
    //{ 0x39, 0x48 }, vs 5455 0x44

    // CDirectSound_SetVelocity+0x4C : or dword ptr [eax+0x__], 2
    { 0x4C, 0x83 },
    { 0x4D, 0x48 },
    //{ 0x4E, 0x34 }, vs 5455 0x30
    { 0x4F, 0x02 },

    // CDirectSound_SetVelocity+0x70 : retn 0x14
    { 0x70, 0xC2 },
    { 0x71, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetPosition
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetPosition,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetPosition+0x0F : mov edx, [ebp+arg_4]
    { 0x0F, 0x8B },
    { 0x10, 0x55 },
    { 0x11, 0x0C },

    // CDirectSoundVoice_SetPosition+0x12 : mov [ecx+04h], edx
    { 0x12, 0x89 },
    { 0x13, 0x51 },
    { 0x14, 0x08 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetPosition+0x21 : mov [ecx+08h], edx
    { 0x21, 0x89 },
    { 0x22, 0x51 },
    { 0x23, 0x0C }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetPosition+0x30 : mov [ecx+0Ch], edx
    { 0x30, 0x89 },
    { 0x31, 0x51 },
    { 0x32, 0x10 }, // SetConeOrientation vs SetPosition vs SetVelocity
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetVelocity
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetVelocity,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetVelocity+0x0F : mov edx, [ebp+arg_4]
    { 0x0F, 0x8B },
    { 0x10, 0x55 },
    { 0x11, 0x0C },

    // CDirectSoundVoice_SetVelocity+0x12 : mov [ecx+14h], edx
    { 0x12, 0x89 },
    { 0x13, 0x51 },
    { 0x14, 0x14 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetVelocity+0x21 : mov [ecx+18h], edx
    { 0x21, 0x89 },
    { 0x22, 0x51 },
    { 0x23, 0x18 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetVelocity+0x30 : mov [ecx+1Ch], edx
    { 0x30, 0x89 },
    { 0x31, 0x51 },
    { 0x32, 0x1C }, // SetConeOrientation vs SetPosition vs SetVelocity
    //
);

// ******************************************************************
// * CDirectSound::SynchPlayback
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSound_SynchPlayback,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x31, XREF_CMcpxAPU_SynchPlayback),

    { 0x00, 0x56 },

    { 0x07, 0x3D },
    { 0x0C, 0x00 },
    { 0x16, 0x68 },
    { 0x2D, 0x48 },
    { 0x2E, 0x0C },
    { 0x2F, 0x57 },
    { 0x36, 0xF6 },
    { 0x3B, 0x68 },
    //
);

// ******************************************************************
// * CDirectSound::CommitDeferredSettings
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_CommitDeferredSettings,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSound_CommitDeferredSettings+0x46 : call [CDirectSound3DCalculator::Calculate3D]
    XREF_ENTRY(0x47, XREF_CDirectSound3DCalculator_Calculate3D),

    // CDirectSound_CommitDeferredSettings+0x5E : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x5F, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSound_CommitDeferredSettings+0x00 : push ebp; mov ebp,esp
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },

    // CDirectSound_CommitDeferredSettings+0x27 : mov eax, 0x80004005
    { 0x28, 0xB8 },
    { 0x29, 0x05 },
    { 0x2A, 0x40 },
    { 0x2C, 0x80 },

    // CDirectSound_CommitDeferredSettings+0x97 : leave
    { 0x97, 0xC9 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSound::EnableHeadphones
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_EnableHeadphones,
                         5344)
OOVPA_SIG_MATCH(

    { 0x04, 0x51 },
    { 0x05, 0x83 },
    { 0x06, 0x65 },
    { 0x07, 0xFC },
    { 0x08, 0x00 },

    { 0x09, 0xE8 },

    { 0x2D, 0x05 },
    { 0x3D, 0x08 },
    { 0x4D, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetConeOutsideVolume
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetConeOutsideVolume,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetConeOutsideVolume+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetConeOutsideVolume+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x11 : mov [eax+34h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x34 },

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x02 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x30 : retn 0Ch
    { 0x31, 0x0C },
    { 0x32, 0x00 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetRolloffFactor,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetConeOutsideVolume+0x29 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x2A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice_SetRolloffFactor+0x00 : mov ecx,dword ptr [esp+4]
    { 0x00, 0x8B },

    // CDirectSoundVoice_SetRolloffFactor+0x0D : mov edx, [esp+arg_4]
    { 0x0D, 0x8B },
    { 0x0E, 0x54 },
    { 0x0F, 0x24 },
    { 0x10, 0x08 },

    // CDirectSoundVoice_SetRolloffFactor+0x11 : mov [eax+48h], edx
    { 0x11, 0x89 },
    { 0x12, 0x50 },
    { 0x13, 0x48 },

    { 0x14, 0x8B },
    { 0x1D, 0x80 },
    { 0x1F, 0x03 },

    // CDirectSoundVoice_SetRolloffFactor+0x30 : retn 0Ch
    { 0x30, 0xC2 },
    { 0x31, 0x0C },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetRolloffCurve
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetRolloffCurve,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    { 0x10, 0x08 },
    { 0x11, 0x89 },
    { 0x12, 0x51 },
    { 0x13, 0x50 }, // SetConeAngles 0x20 vs SetRolloffCurve 0x50
    { 0x14, 0x8B },
    { 0x15, 0x48 },
    { 0x16, 0x10 },
    { 0x17, 0x8B },
    { 0x18, 0x89 },

    { 0x23, 0x54 }, // SetConeAngles 0x24 vs SetRolloffCurve 0x54
    { 0x30, 0x01 }, // SetConeAngles 0x04 vs SetRolloffCurve 0x01
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetConeAngles
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeAngles,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    { 0x10, 0x08 },
    { 0x11, 0x89 },
    { 0x12, 0x51 },
    { 0x13, 0x20 }, // SetConeAngles 0x20 vs SetRolloffCurve 0x50
    { 0x14, 0x8B },
    { 0x15, 0x48 },
    { 0x16, 0x10 },
    { 0x17, 0x8B },
    { 0x18, 0x89 },

    { 0x23, 0x24 }, // SetConeAngles 0x24 vs SetRolloffCurve 0x54
    { 0x30, 0x04 }, // SetConeAngles 0x04 vs SetRolloffCurve 0x01
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetConeOrientation
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeOrientation,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetConeOrientation+0x0F : mov edx, [ebp+arg_4]
    { 0x0F, 0x8B },
    { 0x10, 0x55 },
    { 0x11, 0x0C },

    // CDirectSoundVoice_SetConeOrientation+0x12 : mov [ecx+28h], edx
    { 0x12, 0x89 },
    { 0x13, 0x51 },
    { 0x14, 0x28 }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetConeOrientation+0x21 : mov [ecx+2Ch], edx
    { 0x21, 0x89 },
    { 0x22, 0x51 },
    { 0x23, 0x2C }, // SetConeOrientation vs SetPosition vs SetVelocity

    // CDirectSoundVoice_SetConeOrientation+0x30 : mov [ecx+30h], edx
    { 0x30, 0x89 },
    { 0x31, 0x51 },
    { 0x32, 0x30 }, // SetConeOrientation vs SetPosition vs SetVelocity
    //
);

// ******************************************************************
// * CMcpxStream_Flush
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Flush,
                         5344)
OOVPA_SIG_MATCH(

    // CMcpxStream_Flush+0x00 : push ebp; mov ebp, esp; sub esp, 10h
    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x10 },

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
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetI3DL2Source
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetI3DL2Source,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetI3DL2Source+0xC0 : call [CDirectSoundVoice::SetI3DL2Source]
    XREF_ENTRY(0xC1, XREF_CDirectSoundVoice_CommitDeferredSettings),

    { 0x00, 0x8B },

    // CDirectSoundVoice_SetI3DL2Source+0x12 : mov esi, [ecx]
    { 0x12, 0x8B },
    { 0x13, 0x31 },

    // CDirectSoundVoice_SetI3DL2Source+0x14 : mov [edx+80h], esi
    { 0x14, 0x89 },
    { 0x15, 0xB2 },
    { 0x16, 0x80 },

    // CDirectSoundVoice_SetI3DL2Source+0xB3 : or byte ptr [ecx+7Eh],7Fh
    { 0xB3, 0x80 },
    { 0xB4, 0x49 },
    //{ 0xB5, 0x7E }, //0x7E is known for 5344 and later
    { 0xB6, 0x7F },

    // CDirectSoundVoice_SetI3DL2Source+0xC7 : retn 0Ch
    { 0xC7, 0xC2 },
    { 0xC8, 0x0C },
    //
);

// ******************************************************************
// * CDirectSound::SetDistanceFactor
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDistanceFactor,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDistanceFactor+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSound_SetDistanceFactor+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSound_SetDistanceFactor+0x33 : mov [eax+0x__], edx
    { 0x33, 0x89 },
    { 0x34, 0x50 },
    //{ 0x35, 0x74 }, vs 5455 0x70

    // CDirectSound_SetDistanceFactor+0x39 : or dword ptr[eax+0x__], 0x08
    { 0x39, 0x83 },
    { 0x3A, 0x48 },
    //{ 0x3B, 0x34 }, vs 5455 0x30
    { 0x3C, 0x08 },

    { 0x3F, 0x24 },

    // CDirectSound_SetDistanceFactor+0x4C : jz +0x0B
    { 0x4C, 0x74 },
    { 0x4D, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::SetDopplerFactor
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDopplerFactor,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDopplerFactor+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSound_SetDopplerFactor+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSound_SetDopplerFactor+0x33 : mov [eax+0x__], edx
    { 0x33, 0x89 },
    { 0x34, 0x50 },
    //{ 0x35, 0x74 }, vs 5455 0x70

    // CDirectSound_SetDopplerFactor+0x39 : or dword ptr[eax+0x__], 0x20
    { 0x39, 0x83 },
    { 0x3A, 0x48 },
    //{ 0x3B, 0x34 }, vs 5455 0x30
    { 0x3C, 0x20 },

    { 0x3F, 0x24 },

    // CDirectSound_SetDopplerFactor+0x4C : jz +0x0B
    { 0x4C, 0x74 },
    { 0x4D, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::SetRolloffFactor
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetRolloffFactor,
                         5344)
OOVPA_SIG_MATCH(

    // CDirectSound_SetRolloffFactor+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSound_SetRolloffFactor+0x21 : mov eax, 0x80004005
    { 0x21, 0xB8 },
    { 0x22, 0x05 },
    { 0x23, 0x40 },
    { 0x24, 0x00 },
    { 0x25, 0x80 },

    // CDirectSound_SetRolloffFactor+0x33 : mov [eax+0x__], edx
    { 0x33, 0x89 },
    { 0x34, 0x50 },
    //{ 0x35, 0x70 }, vs 5455 0x6C

    // CDirectSound_SetRolloffFactor+0x39 : or dword ptr[eax+0x__], 0x10
    { 0x39, 0x83 },
    { 0x3A, 0x48 },
    //{ 0x3B, 0x34 }, vs 5455 0x30
    { 0x3C, 0x10 },

    { 0x3F, 0x24 },

    // CDirectSound_SetRolloffFactor+0x4C : jz +0x0B
    { 0x4C, 0x74 },
    { 0x4D, 0x0B },
    //
);

// ******************************************************************
// * CFullHRTFSource::GetCenterVolume
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(CFullHRTFSource_GetCenterVolume,
                         5344)
OOVPA_SIG_MATCH(

    { 0x13, 0xD9 },
    { 0x29, 0xDF },
    { 0x3D, 0x2D },
    { 0x54, 0xC1 },
    { 0x67, 0x4D },
    { 0x7E, 0xD9 },
    { 0x91, 0x10 },
    //
);

// ******************************************************************
// * LightHRTFSource::GetCenterVolume
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(CLightHRTFSource_GetCenterVolume,
                         5344)
OOVPA_SIG_MATCH(

    // CLightHRTFSource::GetCenterVolume+0x00 : push ebp
    OV_MATCH(0x00, 0x55),

    // CLightHRTFSource::GetCenterVolume+0x13 : fchs
    OV_MATCH(0x13, 0xD9, 0xE0),

    // CLightHRTFSource::GetCenterVolume+0x3B : fld1
    OV_MATCH(0x3B, 0xD9, 0xE8),

    // CLightHRTFSource::GetCenterVolume+0x5F : mov [e__+__],0xFFFFD8F0
    OV_MATCH(0x61, 0xF0, 0xD8, 0xFF, 0xFF),

    // CLightHRTFSource::GetCenterVolume+0x66 : ret 0x0010
    OV_MATCH(0x66, 0xC2, 0x10),
    //
);

// ******************************************************************
// * CHRTFSource::SetFullHRTF5Channel
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(CHRTFSource_SetFullHRTF5Channel,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4C, XREF_CFullHRTFSource_GetCenterVolume),

    { 0x00, 0xC7 },
    { 0x0A, 0xC7 },
    { 0x14, 0xC7 },
    { 0x1E, 0xC7 },
    { 0x28, 0xC7 },
    { 0x32, 0xC7 },
    { 0x3C, 0xC7 },
    { 0x46, 0xC7 },
    { 0x50, 0xC7 },
    { 0x5A, 0xC7 },
    { 0x64, 0xC7 },

    { 0x6A, 0x03 },
    { 0x6B, 0x00 },
    { 0x6C, 0x00 },
    { 0x6D, 0x00 },

    { 0x6E, 0xC3 },
    //
);

// ******************************************************************
// * CHRTFSource::SetLightHRTF5Channel
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(CHRTFSource_SetLightHRTF5Channel,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4C, XREF_CLightHRTFSource_GetCenterVolume),

    { 0x00, 0xC7 },
    { 0x0A, 0xC7 },
    { 0x14, 0xC7 },
    { 0x1E, 0xC7 },
    { 0x28, 0xC7 },
    { 0x32, 0xC7 },
    { 0x3C, 0xC7 },
    { 0x46, 0xC7 },
    { 0x50, 0xC7 },
    { 0x5A, 0xC7 },
    { 0x64, 0xC7 },

    { 0x6A, 0x04 },
    { 0x6B, 0x00 },
    { 0x6C, 0x00 },
    { 0x6D, 0x00 },

    { 0x6E, 0xC3 },
    //
);

// ******************************************************************
// * CHRTFSource::SetFullHRTF4Channel
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(CHRTFSource_SetFullHRTF4Channel,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0xC7 },
    { 0x0A, 0xC7 },
    { 0x14, 0xC7 },
    { 0x1E, 0xC7 },
    { 0x28, 0xC7 },
    { 0x32, 0xC7 },
    { 0x3C, 0xC7 },
    { 0x46, 0xC7 },
    { 0x50, 0xC7 },
    { 0x5A, 0xC7 },
    { 0x64, 0xC7 },

    { 0x6A, 0x01 },
    { 0x6B, 0x00 },
    { 0x6C, 0x00 },
    { 0x6D, 0x00 },

    { 0x6E, 0xC3 },
    //
);

// ******************************************************************
// * CHRTFSource::SetLightHRTF4Channel
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(CHRTFSource_SetLightHRTF4Channel,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0xC7 },
    { 0x0A, 0xC7 },
    { 0x14, 0xC7 },
    { 0x1E, 0xC7 },
    { 0x28, 0xC7 },
    { 0x32, 0xC7 },
    { 0x3C, 0xC7 },
    { 0x46, 0xC7 },
    { 0x50, 0xC7 },
    { 0x5A, 0xC7 },
    { 0x64, 0xC7 },

    { 0x6A, 0x02 },
    { 0x6B, 0x00 },
    { 0x6C, 0x00 },
    { 0x6D, 0x00 },

    { 0x6E, 0xC3 },
    //
);

// ******************************************************************
// * DirectSoundUseLightHRTF
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(DirectSoundUseLightHRTF,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0A, XREF_CHRTFSource_SetLightHRTF5Channel),

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
// * DirectSoundUseFullHRTF4Channel
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(DirectSoundUseFullHRTF4Channel,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0A, XREF_CHRTFSource_SetFullHRTF4Channel),

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
// * DirectSoundUseLightHRTF4Channel
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(DirectSoundUseLightHRTF4Channel,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0A, XREF_CHRTFSource_SetLightHRTF4Channel),

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
// * CDirectSound3DCalculator_GetVoiceData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound3DCalculator_GetVoiceData,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x03, 0x83 },

    // CDirectSound3DCalculator_GetVoiceData+0x2D : test eax,15200010h
    { 0x2D, 0xA9 },
    { 0x2E, 0x10 },
    { 0x2F, 0x00 },
    { 0x30, 0x20 },
    { 0x31, 0x15 },

    // CDirectSound3DCalculator_GetVoiceData+0x8C : test word ptr [ebp+0Ah],4014h
    { 0x8C, 0x66 },
    { 0x8D, 0xF7 },
    { 0x8E, 0x45 },
    { 0x8F, 0x0A },
    { 0x90, 0x14 },
    { 0x91, 0x40 },

    // After offset 0x131, major changes has occur.
    //
);

// ******************************************************************
// * IDirectSound3DCalculator_GetVoiceData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound3DCalculator_GetVoiceData,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound3DCalculator_GetVoiceData+0x04 : jmp [CDirectSound3DCalculator_GetVoiceData]
    XREF_ENTRY(0x05, XREF_CDirectSound3DCalculator_GetVoiceData),

    // IDirectSound3DCalculator_GetVoiceData+0x00 : push ebp
    { 0x00, 0x55 },

    // IDirectSound3DCalculator_GetVoiceData+0x03 : pop ebp
    { 0x03, 0x5D },

    // IDirectSound3DCalculator_GetVoiceData+0x04 : jmp 0x........
    { 0x04, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSound3DCalculator_GetPanData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound3DCalculator_GetPanData,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x03, 0x83 },

    // CDirectSound3DCalculator_GetPanData+0x52 : or dword ptr [esi],4
    { 0x52, 0x83 },
    { 0x53, 0x0E },
    { 0x54, 0x04 },

    // CDirectSound3DCalculator_GetPanData+0x65 : push eax; push ecx; push ecx
    { 0x65, 0x50 },
    { 0x66, 0x51 },
    { 0x67, 0x51 },

    // CDirectSound3DCalculator_GetPanData+0x87 : or dword ptr [esi],8
    { 0x87, 0x83 },
    { 0x88, 0x0E },
    { 0x89, 0x08 },

    // CDirectSound3DCalculator_GetPanData+0x8D : mov dword ptr [esi+18h],ecx
    { 0x8D, 0x89 },
    { 0x8E, 0x4E },
    { 0x8F, 0x18 },

    // After offset 0x93, major changes has occur.
    //
);

// ******************************************************************
// * IDirectSound3DCalculator_GetPanData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound3DCalculator_GetPanData,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound3DCalculator_GetPanData+0x19 : call [CDirectSound3DCalculator_GetVoiceData]
    XREF_ENTRY(0x1A, XREF_CDirectSound3DCalculator_GetPanData),

    { 0x00, 0xFF },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0x24 },

    { 0x19, 0xE8 },

    // IDirectSound3DCalculator_GetPanData+0x1E : retn 0x10
    { 0x1E, 0xC2 },
    { 0x1F, 0x10 },
    //
);

// ******************************************************************
// * CDirectSound3DCalculator_GetMixBinVolumes
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound3DCalculator_GetMixBinVolumes,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x03, 0x8B },

    // CDirectSound3DCalculator_GetMixBinVolumes+0x0F : mov eax,0FFFFD8F0h
    { 0x0F, 0xB8 },
    { 0x10, 0xF0 },
    { 0x11, 0xD8 },
    { 0x12, 0xFF },
    { 0x13, 0xFF },

    { 0x92, 0x04 },
    { 0x9B, 0x02 },
    { 0xA0, 0x05 },
    { 0xA5, 0x07 },
    { 0xAA, 0x09 },
    { 0xAF, 0x0A },
    //
);

// ******************************************************************
// * IDirectSound3DCalculator_GetMixBinVolumes
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound3DCalculator_GetMixBinVolumes,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound3DCalculator_GetMixBinVolumes+0x00 : jmp [CDirectSound3DCalculator_GetMixBinVolumes]
    XREF_ENTRY(0x01, XREF_CDirectSound3DCalculator_GetMixBinVolumes),

    // IDirectSound3DCalculator_GetMixBinVolumes+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSound3DCalculator_Calculate3D
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound3DCalculator_Calculate3D,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8D },
    { 0x05, 0x81 },

    // CDirectSound3DCalculator_Calculate3D+0x3A : test cl,40h
    { 0x3A, 0xF6 },
    { 0x3B, 0xC1 },
    { 0x3C, 0x40 },

    // CDirectSound3DCalculator_Calculate3D+0xA3 : test dword ptr [ebp+6Ch],410001h
    { 0xA3, 0xF7 },
    { 0xA4, 0x45 },
    { 0xA5, 0x6C },
    { 0xA6, 0x01 },
    { 0xA7, 0x00 },
    { 0xA8, 0x41 },
    { 0xA9, 0x00 },

    { 0xD4, 0x6A },
    { 0xD5, 0x03 },

    // After offset 0xEE, major changes has occur.
    //
);

// ******************************************************************
// * IDirectSound3DCalculator_Calculate3D
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound3DCalculator_Calculate3D,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound3DCalculator_Calculate3D+0x00 : jmp [CDirectSound3DCalculator_Calculate3D]
    XREF_ENTRY(0x01, XREF_CDirectSound3DCalculator_Calculate3D),

    // IDirectSound3DCalculator_Calculate3D+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * XAudioSetEffectData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(XAudioSetEffectData,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // XAudioSetEffectData+0x79 : call [CDirectSound_GetEffectData]
    XREF_ENTRY(0x07A, XREF_CDirectSound_GetEffectData),

    // XAudioSetEffectData+0xC1 : call [CDirectSound_SetEffectData]
    XREF_ENTRY(0x0C2, XREF_CDirectSound_SetEffectData),

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x03, 0x81 },
    //
);

// ******************************************************************
// * CDirectSound_MapBufferData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_MapBufferData,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x0C, 0x00 },

    { 0x2B, 0x08 },
    { 0x2E, 0x0C },

    { 0x34, 0x83 },
    { 0x35, 0xC1 },
    { 0x36, 0x60 },

    { 0x47, 0x18 },

    { 0x66, 0xC2 },
    { 0x67, 0x10 },
    //
);

// ******************************************************************
// * IDirectSound_MapBufferData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_MapBufferData,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_MapBufferData+0x1C : call [CDirectSound_MapBufferData]
    XREF_ENTRY(0x01D, XREF_CDirectSound_MapBufferData),

    { 0x00, 0xFF },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x14, 0xF8 },
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * CDirectSound_UnmapBufferData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_UnmapBufferData,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x0C, 0x00 },

    { 0x2B, 0x08 },
    { 0x2E, 0x0C },
    { 0x32, 0x0C },

    { 0x33, 0x83 },
    { 0x34, 0xC1 },
    { 0x35, 0x60 },

    { 0x4D, 0xC2 },
    { 0x4E, 0x08 },
    //
);

// ******************************************************************
// * IDirectSound_UnmapBufferData
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(IDirectSound_UnmapBufferData,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSound_UmapBufferData+0x14 : call [CDirectSound_UnmapBufferData]
    XREF_ENTRY(0x015, XREF_CDirectSound_UnmapBufferData),

    { 0x00, 0x8B },
    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0C, 0xF8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_Commit3dSettings_0,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient::Commit3dSettings+0x2B : call [CDirectSound3DCalculator::Calculate3D]
    XREF_ENTRY(0x2C, XREF_CDirectSound3DCalculator_Calculate3D),

    // CMcpxVoiceClient::Commit3dSettings+0x56 : call [CDirectSound3DCalculator::GetVoiceData]
    XREF_ENTRY(0x57, XREF_CDirectSound3DCalculator_GetVoiceData),

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x5E : mov e__,[e__+0x000000B4]
    { 0x5E, 0x8B },
    //{ 0x5F, 0x__ },
    { 0x60, 0xB4 },
    { 0x61, 0x00 },
    //{ 0x62, 0x00 },
    { 0x63, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x67 : mov eax,[eax+0x000000B4]
    { 0x6A, 0x8B },
    //{ 0x6B, 0x80 },
    { 0x6C, 0xB4 },
    { 0x6D, 0x00 },
    //{ 0x6E, 0x00 },
    { 0x6F, 0x00 },

    //
);

// ******************************************************************
// * CDirectSoundVoice::CommitDeferredSettings
// ******************************************************************
// Generic OOVPA as of 5344 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_CommitDeferredSettings,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::CommitDeferredSettings+0x07 : call [CMcpxVoiceClient::Commit3dSettings]
    XREF_ENTRY(0x08, XREF_CMcpxVoiceClient_Commit3dSettings),

    { 0x01, 0x44 },
    { 0x04, 0x8B },
    { 0x07, 0xE8 },
    { 0x0C, 0x33 },
    { 0x0D, 0xC0 },
    { 0x10, 0x00 },
    //
);
