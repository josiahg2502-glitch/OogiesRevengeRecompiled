// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library version
//   [LibV] Title Name                       |  Verify   |   Comments
//-------------------------------------------------------------------
// * [3925] Cel Damage                       |   100%    | Contain full library.
// * [3936] Silent Hill 2                    |   100%    | Contain 99% library.**
// * [4039] Nightcaster                      |   100%    | Only has 90% of the library compiled with xbe build.
// * [4039] Azurik PAL                       |   100%    | Contain full library.
// * [4134] RaceX (Demo)                     |     -%    | Only has a few library.
// * [4134] Blood Omen 2                     |    80%    | Does not have full library.
// * [4134] JSRF                             |     1%    | Does not have Stream class. DS and Buffer might be full.
// * [4134] Double-S.T.E.A.L                 |   100%    | Contain full library.
// * [4242] NFL Blitz 2002                   |   100%    | Contain full library.
// * [4361] Flight Academy                   |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4432] RedCard 2003                     |   100%    | Contain full library.
// * [4432] Madden NFL 2003                  |   100%    | Contain full library.
// * [4531] Hitman 2: Silent Assassin        |   100%    | Contain full library.
// * [4627] MLB SlugFest 2003                |   100%    | Contain full library.
// * [4721] NFL 2K3                          |   100%    | Contain full library.
// * [4721] Terminator Dawn of Fate          |   100%    | Contain full library.
// * [4831] Whacked!                         |   100%    | Contain full library.
// * [4928] Drihoo                           |   100%    | Contain full library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | Contain full library.
// * [5120] N.U.D.E.@                        |   100%    | Contain full library.
// * [5233] Evil Dead                        |   100%    | Contain full library.
// * [5344] Gladius OXM Demo Disc 20         |   100%    | Contain full library.
// * [5344] The Hulk                         |   100%    | Contain full library.
// * [5455] NCAA Football 2004               |   100%    | Contain full library.
// * [5455] Dinosaur Hunting                 |   100%    | Contain full library.
// * [5558] Dino Crisis 3                    |   100%    | Contain full library.
// * [5558] ESPN NBA Basketball              |   100%    | Contain full library.
// * [5659] Midway Arcade Treasures Paperboy |   100%    | Contain full library.
// * [5788] Digimon Battle Chronicle         |   100%    | Contain full library.
// * [5788] Splinter Cell: Pandora Tomorrow  |   100%    | Contain full library.
// * [5849] Nickelodeon Tak 2                |   100%    | Contain full library.
// * [5849] Def Jam Fight for NY             |   100%    | Contain full library.

// Note records:
// ** Did not compile with XFileCreateMediaObject and XWaveFileCreateMediaObject
//   * Might need further investigation.


// TODO: Known DSound OOVPA issue list
// * 3911 to 5933: Cannot make OOVPAs
//   * IDirectSound_SetCooperativeLevel     (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSound_Compact                 (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSoundBuffer_Restore           (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSoundBuffer_Unlock            (Xbox doesn't use it, however can make OOVPA; NOTE: OOVPA is registered for it)
//   * IDirectSoundStream_AddRef            (Using IUnknown_AddRef)
//   * IDirectSoundStream_Release           (Using IUnknown_Release)
// * 3911 to ????: These functions does not exist until newer XDK revision
//   * IDirectSoundBuffer_Pause                 (Lowest found was 4721)
//   * IDirectSoundBuffer_PauseEx               (Lowest found was 4721)
//   * IDirectSoundStream_FlushEx               (Lowest found was 4134)
//   * DirectSoundDumpMemoryUsage               (Lowest found was 4361)
//   * DirectSoundGetSampleTime                 (Need verify in 4134)
//   * XGetAudioFlags                           (Lowest found was 3911, XAudioGetSpeakerConfig introduced later as alias, is part of Xapi section)
//   * XAudioSetEffectData                      (Lowest found was 5120, likely lowest found will be in 5028)
//     * Except newer segaboot report to have full except for XAudioSetEffectData is not include.
// * 3911 to 3936: Following separater functions has exact asm codes as whole function are...
//   * IDirectSoundStream_SetVolume     & CDirectSoundStream_SetVolume
//   * IDirectSoundStream_SetPitch      & CDirectSoundStream_SetPitch
//   * IDirectSoundStream_SetLFO        & CDirectSoundStream_SetLFO
//   * IDirectSoundStream_SetEG         & CDirectSoundStream_SetEG
//   * IDirectSoundStream_SetFilter     & CDirectSoundStream_SetFilter
//   * IDirectSoundStream_SetHeadroom   & CDirectSoundStream_SetHeadroom
//   * IDirectSoundStream_SetFrequency  & CDirectSoundStream_SetFrequency
//   * IDirectSoundStream_SetMixBins    & CDirectSoundStream_SetMixBins
// * 3911 - Not part of API, yet is a non-member function : (might be useful)
//   * GetFormatSize
//   * CopyFormat
//   * CompareFormats
//   * CalculateXboxAdpcmAlignment
//   * IsValidPcmFormat
//   * IsValidXboxAdpcmFormat
//   * CopyFormatAlloc
// * List of functions might need to be register:
//   * IDirectSoundBuffer_QueryInterface
//   * IDirectSoundBuffer_QueryInterfaceC
// * List of internal functions are not register:
//   * CDirectSoundBuffer_Release   (Is unique, however need multiple OOVPAs to register all revisions)
//     * Using XREF_DSound_CRefCount_Release
//   * CDirectSound_Release         (Is unique, however need multiple OOVPAs to register all revisions)
//     * Using XREF_DSound_CRefCount_Release
// * 4039 verification needed:
//   * DirectSoundUseLightHRTF
//   * CDirectSoundStream_SetRolloffCurve (IDirectSoundStream_SetRolloffCurve is a jmp)
//   * CDirectSoundStream_SetRolloffFactor
// * 4134 verification needed: (Verifying with Double-S.T.E.A.L title is done, need different title to find the remaining...)
//   * DirectSoundUseLightHRTF
//   * XAudioCreateAdpcmFormat
// * 4039 CDirectSoundVoice_SetPitch need to be strengthen by using XREF to CMcpxVoiceClient_SetPitch function.
// * List of OOVPAs may could be lower to include support older titles.
//   * CDirectSoundVoice_SetI3DL2Source (5344)
//   * CDirectSound_SetDopplerFactor (5344)
//   * CDirectSound_SetRolloffFactor (5344)
//   * CDirectSound_SetDistanceFactor (5344)
//   * CDirectSound_SetI3DL2Listener (5344)
//   * CMcpxBuffer_Pause_Ex (4721)
//   * IDirectSoundBuffer_PauseEx (4721)
//   * CDirectSoundBuffer_PauseEx (4721)
// * Missing OOVPAs
//   * DirectSoundUseLightHRTF (4134)
//   * CHRTFSource_SetLightHRTF5Channel (4134)
//   * XAudioCreateAdpcmFormat (4134)
//   * XFileCreateMediaObject (3936 - 4134)
//     * Somehow is excluded?
//   * XWaveFileCreateMediaObject (3936 - 4134)
//     * Somehow is excluded?
// * 4134 & 4361 CDirectSoundVoice_SetMaxDistance + CDirectSoundVoice_SetMinDistance
//   * With XREF, RadWolfie think is possible to remove 0x1F offset for ability to remove 4361 OOVPAs.
// * 4039 (TODO)
//   * CDirectSoundVoice_SetI3DL2Source, need to reduce pairs and at least use an XREF.
//     * Most likely has a call to CDirectSoundVoice_CommitDeferredSettings.
//   * CDirectSoundVoice_SetMixBins
//     * Maybe able to reduce pairs and include another XREF.
//   * CDirectSoundVoice_SetMixBinVolumes
//     * Should be able to reduce pairs since there are two XREFs.
// * (TODO) CDirectSoundBuffer_SetNotificationPositions, add XREF supports.


#ifndef DSOUND_OOVPA_INL
#define DSOUND_OOVPA_INL

#include "OOVPA_databases.h"
#include <xref/list_xref.h>

#include "DSound/3911.inl"
#include "DSound/3936.inl"
#include "DSound/4039.inl"
#include "DSound/4134.inl"
#include "DSound/4242.inl"
#include "DSound/4361.inl"
#include "DSound/4432.inl"
#include "DSound/4531.inl"
#include "DSound/4627.inl"
#include "DSound/4721.inl"
#include "DSound/4831.inl"
#include "DSound/5028.inl"
#include "DSound/5344.inl"
#include "DSound/5455.inl"
#include "DSound/5558.inl"

// ******************************************************************
// * DSound_OOVPA_manual_Table
// ******************************************************************
static OOVPATable DSound_OOVPA_manual_Table[] = {

    // Without xrefs dependency
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                      SYM_SIG(0)), // dummy signature // NOTE: The function and CAc97MediaObject::AddRef are the same asm code.
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Discontinuity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Flush, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_GetInfo, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pInfo))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_GetStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdwStatus))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Process, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pInputBuffer), PARAM(psh, pOutputBuffer))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Constructor, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pdssd))),
                      SYM_SIG(3911)), // NOTE: Does not need to be register in db. Using manual work instead, like D3D8 did.
};
OOVPATableList DSound_OOVPA_manual = { XBSDB_ARRAY_SIZE(DSound_OOVPA_manual_Table), DSound_OOVPA_manual_Table };

// ******************************************************************
// * DSound_OOVPA_Table
// ******************************************************************
static OOVPATable DSound_OOVPA_Table[] = {

    REGISTER_OOVPAS(SYM_FUN(XAudioCalculatePitch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwFrequency))),
                    SYM_SIG(3911, 4039, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundEnterCriticalSection, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(DSound_CRefCount_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DSound_CRefCount_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911, 4039, 5455)), // Final generic OOVPA: 5455; Removed: 0

    REGISTER_OOVPAS(SYM_FUN(DSound_CMemoryManager_PoolAlloc, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PoolTag), PARAM(psh, Size), PARAM(psh, ZeroInitialize))),
                    SYM_SIG(4134, 4361)), // For reference purpose only, does not have XREF value.

    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Commit3dSettings, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_ServiceDeferredCommandsLow, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4134, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dDistanceFactor, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, fDistanceFactor), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dDopplerFactor, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, fDopplerFactor), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dParameters, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pDS3DListenerParameters), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dPosition, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pPosition), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dRolloffFactor, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, fRolloffFactor), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dVelocity, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pVelocity), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetI3DL2Listener, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pds3dl), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetMixBinHeadroom, CALL(thi), STACK(8), PARAMS(PARAM(ecx, this), PARAM(psh, dwMixBinMask), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetMixBinHeadroom, CALL(thi), STACK(4), PARAMS(PARAM(ecx, this), PARAM(psh, dwMixBinMask))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SynchPlayback, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4831)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_Calculate3D, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pUnknown1), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetMixBinVolumes, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, pUnknown3))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetPanData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, flUnknown1), PARAM(psh, flUnknown2), PARAM(psh, unknown3), PARAM(psh, pflUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pUnknown1), PARAM(psh, pUnknown2), PARAM(psh, pUnknown3), PARAM(psh, pUnknown4), PARAM(psh, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_GetVoiceProperties, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dConeOrientation, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pConeOrientation), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dConeOutsideVolume, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, lConeOutsideVolume), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMaxDistance, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, flMaxDistance), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMinDistance, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, flMinDistance), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMode, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwMode), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dPosition, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pPosition), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dVelocity, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pVelocity), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetEG, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetFilter, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetI3DL2Source, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pds3db), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetLFO, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetMixBins, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetPitch, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetVolume, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Commit3dSettings, CALL(thi), STACK(4), PARAMS(PARAM(ecx, this), PARAM(psh, dwParamMask))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+// NOTE: Must be after CMcpxVoiceClient_SetVolume for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Commit3dSettings, CALL(thi), STACK(0), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(4039, 4134, 4242, 4627, 5028, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0// NOTE: Must be after CMcpxVoiceClient_SetVolume for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dParameters, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pc3DBufferParameters), PARAM(psh, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+// NOTE: Must be after CMcpxVoiceClient_Commit3dSettings for one time scan.

    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoiceSettings_SetMixBinVolumes, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)

    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_CommitDeferredSettings, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_GetVoiceProperties, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_Set3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pc3DBufferParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeAngles, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwInsideConeAngle), PARAM(psh, dwOutsideConeAngle), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeOutsideVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lConeOutsideVolume), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134, 4361, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134, 4361, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetEG, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pwfxFormat))),
                    SYM_SIG(4039, 4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetI3DL2Source, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pds3db), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetLFO, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMaxDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fMaxDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMinDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fMinDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBins, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBinVolumes, CALL(std), STACK(12), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMixBinMask), PARAM(psh, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBinVolumes, CALL(std), STACK(8), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMode), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetOutputBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pOutputBuffer))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetPitch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFrequency, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0 // NOTE: Must be after CDirectSoundVoice_SetPitch for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetRolloffCurve, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pflPoints), PARAM(psh, dwPointCount), PARAM(psh, dwApply))),
                    SYM_SIG(4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0 // s+ (from 4134's comment)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_Use3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBufferSettings_SetBufferData, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pvBufferData), PARAM(psh, dwBufferBytes))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0

    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_GetCurrentPosition, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pdwCurrentPlayCursor), PARAM(psh, pdwCurrentWriteCursor))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_GetStatus, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pdwStatus))),
                    SYM_SIG(3911, 4039, 4134, 4721, 4831)), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Pause, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwPause))),
                    SYM_SIG(4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Pause_Ex, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Play, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwFlags))),
                    SYM_SIG(3911, 4039, 4134, 4721, 4831)), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Play_Ex, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_SetBufferData, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_SetCurrentPosition, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwNewPosition))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Stop, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwFlags))),
                    SYM_SIG(3911, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Stop_Ex, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)

    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Stop, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwFlags))),
                    SYM_SIG(4134, 5028)), // Final generic OOVPA: 5233?; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Stop_Ex, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Flush, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 3936, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Discontinuity, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134, 4531, 5455)), // NOTE: Must be after CMcpxStream_Flush for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_GetStatus, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pdwStatus))),
                    SYM_SIG(4134, 4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Pause, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwPause))),
                    SYM_SIG(3911, 4039, 4134, 4831)), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Pause_Ex, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetCurrentPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pdwCurrentPlayCursor), PARAM(psh, pdwCurrentWriteCursor))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pdwStatus))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetVoiceProperties, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Lock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwOffset), PARAM(psh, dwBytes), PARAM(psh, ppvAudioPtr1), PARAM(psh, pdwAudioBytes1), PARAM(psh, ppvAudioPtr2), PARAM(psh, pdwAudioBytes2), PARAM(psh, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Pause, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_PauseEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_PlayEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Play, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwReserved1), PARAM(psh, dwReserved2), PARAM(psh, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: Must be after CDirectSoundBuffer_PlayEx for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Set3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pc3DBufferParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetBufferData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pvBufferData), PARAM(psh, dwBufferBytes))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeAngles, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwInsideConeAngle), PARAM(psh, dwOutsideConeAngle), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeOutsideVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, lConeOutsideVolume), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetCurrentPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwNewPosition))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, flDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, flDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetEG, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pwfxFormat))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFrequency, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwFrequency))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetI3DL2Source, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pds3db), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetLFO, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetLoopRegion, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwLoopStart), PARAM(psh, dwLoopLength))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMaxDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, flMaxDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMinDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, flMinDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBins, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, mixBins))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBinVolumes, CALL(std), STACK(12), PARAMS(PARAM(psh, this), PARAM(psh, dwMixBinMask), PARAM(psh, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBinVolumes, CALL(std), STACK(8), PARAMS(PARAM(psh, this), PARAM(psh, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwMode), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetNotificationPositions, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwNotifyCount), PARAM(psh, paNotifies))),
                    SYM_SIG(3911, 4039, 4242)), // Uncommenting these fixes dashboard 4920 (from 4627 comment)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetOutputBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pOutputBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPitch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, lPitch))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPlayRegion, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwPlayStart), PARAM(psh, dwPlayLength))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetRolloffCurve, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pflPoints), PARAM(psh, dwPointCount), PARAM(psh, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, fRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_StopEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Stop, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: Must be after CDirectSoundBuffer_StopEx for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Use3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pUnknown2))),
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

#if 0
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Constructor, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pdssd))),
                      SYM_SIG(3911)), // NOTE: Does not need to be register in db. Using manual work instead, like D3D8 did.
#endif
#if 0 // These signatures are no longer in use, yet preserved as documented signatures for future research usage. \
    //   Instead of these signatures below, using CDirectSoundStream_Constructor signature plus manual work allow us to reduce the scan process.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: The function and CAc97MediaObject::AddRef are the same asm code.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Discontinuity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Flush, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                               SYM_SIG(3911, 4039, 4134, 5028)), // Final generic OOVPA: 5028; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetInfo, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pInfo))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdwStatus))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Process, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pInputBuffer), PARAM(psh, pOutputBuffer))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
#endif
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_FlushEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetVoiceProperties, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Pause, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwPause))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_PauseEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Set3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pc3DBufferParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeAngles, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwInsideConeAngle), PARAM(psh, dwOutsideConeAngle), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeOutsideVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lConeOutsideVolume), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetEG, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pwfxFormat))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFrequency, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwFrequency))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetI3DL2Source, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pds3db), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetLFO, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMaxDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fMaxDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMinDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fMinDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBins, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBinVolumes_12, CALL(std), STACK(/*embed*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMixBinMask), PARAM(psh, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in XDK 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBinVolumes_8, CALL(std), STACK(/*embed*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // Then it has changed in XDK 4039 and newer.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMode), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetOutputBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pOutputBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetPitch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lPitch))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetRolloffCurve, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pflPoints), PARAM(psh, dwPointCount), PARAM(psh, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Use3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CommitDeferredSettings, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this))),
                    SYM_SIG(3911, 4039, 4134, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CommitEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CreateSoundBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pdsbd), PARAM(psh, ppBuffer), PARAM(psh, pUnused4))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CreateSoundStream, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pdssd), PARAM(psh, ppStream), PARAM(psh, pUnused4))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_DownloadEffectsImage, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pvImageBuffer), PARAM(psh, dwImageSize), PARAM(psh, pImageLoc), PARAM(psh, ppImageDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_DoWork, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_EnableHeadphones, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, fEnabled))),
                    SYM_SIG(3911, 4039, 4134, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetCaps, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pDSCaps))),
                    SYM_SIG(3911, 4039, 4134, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwEffectIndex), PARAM(psh, dwOffset), PARAM(psh, pvData), PARAM(psh, dwDataSize))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetOutputLevels, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pOutputLevels), PARAM(psh, bResetPeakValues))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetSpeakerConfig, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pdwSpeakerConfig))),
                    SYM_SIG(3911, 4242, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetTime, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, prtCurrent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_MapBufferData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pvBufferData), PARAM(psh, dwBufferBytes), PARAM(psh, ppUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pDS3DListenerParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, fDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, fDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwEffectIndex), PARAM(psh, dwOffset), PARAM(psh, pvData), PARAM(psh, dwDataSize), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetI3DL2Listener, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pds3dl), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetMixBinHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, dwMixBinMask), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, xFront), PARAM(psh, yFront), PARAM(psh, zFront), PARAM(psh, xTop), PARAM(psh, yTop), PARAM(psh, zTop), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, fRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SynchPlayback, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this))),
                    SYM_SIG(4831, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4831)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_UnmapBufferData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, this), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_Calculate3D, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pUnknown1), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetMixBinVolumes, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, pUnknown3))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetPanData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, flUnknown1), PARAM(psh, flUnknown2), PARAM(psh, unknown3), PARAM(psh, pflUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pUnknown1), PARAM(psh, pUnknown2), PARAM(psh, pUnknown3), PARAM(psh, pUnknown4), PARAM(psh, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetCurrentPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdwCurrentPlayCursor), PARAM(psh, pdwCurrentWriteCursor))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdwStatus))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetVoiceProperties, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Lock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwOffset), PARAM(psh, dwBytes), PARAM(psh, ppvAudioPtr1), PARAM(psh, pdwAudioBytes1), PARAM(psh, ppvAudioPtr2), PARAM(psh, pdwAudioBytes2), PARAM(psh, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Pause, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_PauseEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Play, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwReserved1), PARAM(psh, dwReserved2), PARAM(psh, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_PlayEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Restore, CALL(std), STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Set3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5455)), // undocument // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pc3DBufferParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetBufferData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pvBufferData), PARAM(psh, dwBufferBytes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeAngles, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwInsideConeAngle), PARAM(psh, dwOutsideConeAngle), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeOutsideVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lConeOutsideVolume), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetCurrentPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwNewPosition))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetEG, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pwfxFormat))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFrequency, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetI3DL2Source, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pds3db), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetLFO, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetLoopRegion, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwLoopStart), PARAM(psh, dwLoopLength))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMaxDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flMaxDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMinDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flMinDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBins, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, mixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBinVolumes, CALL(std), STACK(12), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMixBinMask), PARAM(psh, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBinVolumes, CALL(std), STACK(8), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // Then it has changed in 4039 and higher.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMode), PARAM(psh, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetNotificationPositions, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwNotifyCount), PARAM(psh, paNotifies))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetOutputBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pOutputBuffer))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPitch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPlayRegion, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwPlayStart), PARAM(psh, dwPlayLength))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetRolloffCurve, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pflPoints), PARAM(psh, dwPointCount), PARAM(psh, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lVolume))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Stop, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_StopEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Unlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, ppvAudioPtr1), PARAM(psh, pdwAudioBytes1), PARAM(psh, ppvAudioPtr2), PARAM(psh, pdwAudioBytes2))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Use3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // undocument // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_GetVoiceProperties, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_FlushEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Pause, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwPause))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_PauseEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh2, rtTimeStamp), PARAM(psh, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Set3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pc3DBufferParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeAngles, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwInsideConeAngle), PARAM(psh, dwOutsideConeAngle), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeOutsideVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lConeOutsideVolume), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, flDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetEG, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetLFO, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pwfxFormat))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFrequency, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetI3DL2Source, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pds3db), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMaxDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fMaxDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMinDistance, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fMinDistance), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBins, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBinVolumes, CALL(std), STACK(12), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMixBinMask), PARAM(psh, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBinVolumes, CALL(std), STACK(8), PARAMS(PARAM(psh, pThis), PARAM(psh, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // Then it has changed in 4039 and higher.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMode), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetOutputBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pOutputBuffer))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetPitch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetRolloffCurve, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pflPoints), PARAM(psh, dwPointCount), PARAM(psh, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, lVolume))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Use3DVoiceData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // jmp only // Final generic OOVPA: 5558 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(IDirectSound_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CommitDeferredSettings, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CommitEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSound_Compact, CALL(std), STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CreateSoundBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdsbd), PARAM(psh, ppBuffer), PARAM(psh, pUnused4))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CreateSoundStream, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdssd), PARAM(psh, ppStream), PARAM(psh, pUnused4))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_DownloadEffectsImage, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pvImageBuffer), PARAM(psh, dwImageSize), PARAM(psh, pImageLoc), PARAM(psh, ppImageDesc))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_EnableHeadphones, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fEnabled))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetCaps, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pDSCaps))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwEffectIndex), PARAM(psh, dwOffset), PARAM(psh, pvData), PARAM(psh, dwDataSize))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetOutputLevels, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pOutputLevels), PARAM(psh, bResetPeakValues))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetSpeakerConfig, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pdwSpeakerConfig))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetTime, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, prtCurrent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_MapBufferData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pvBufferData), PARAM(psh, dwBufferBytes), PARAM(psh, ppUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetAllParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pDS3DListenerParameters), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetCooperativeLevel, CALL(std), STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetDistanceFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fDistanceFactor), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetDopplerFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fDopplerFactor), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwEffectIndex), PARAM(psh, dwOffset), PARAM(psh, pvData), PARAM(psh, dwDataSize), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetI3DL2Listener, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pds3dl), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetMixBinHeadroom, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, dwMixBinMask), PARAM(psh, dwHeadroom))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetOrientation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, xFront), PARAM(psh, yFront), PARAM(psh, zFront), PARAM(psh, xTop), PARAM(psh, yTop), PARAM(psh, zTop), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetPosition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetRolloffFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, fRolloffFactor), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetVelocity, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, x), PARAM(psh, y), PARAM(psh, z), PARAM(psh, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SynchPlayback, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4831)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_UnmapBufferData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(CSensaura3d_GetFullHRTFFilterPair, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3), PARAM(psh, pUnknown4), PARAM(psh, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911, 3936)), // Final generic OOVPA: 3936; Removed: 4134+ // NOTE: 4039 revert back to 3911
    REGISTER_OOVPAS(SYM_FUN(CSensaura3d_GetLiteHRTFFilterPair, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3), PARAM(psh, pUnknown4), PARAM(psh, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4134+
    REGISTER_OOVPAS(SYM_FUN(CFullHRTFSource_GetCenterVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3), PARAM(psh, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CLightHRTFSource_GetCenterVolume, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3), PARAM(psh, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4039, /*4134,*/ 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetFullHRTF5Channel, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4039, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetLightHRTF5Channel, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4039, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetFullHRTF4Channel, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetLightHRTF4Channel, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CFullHrtfSource_GetHrtfFilterPair, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CLightHrtfSource_GetHrtfFilterPair, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CHrtfSource_SetAlgorithm_FullHrtf, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CHrtfSource_SetAlgorithm_LightHrtf, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)

    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreate, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pguidDeviceId), PARAM(psh, ppDirectSound), PARAM(psh, pUnused3))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreateBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pdsbd), PARAM(psh, ppBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreateStream, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pdssd), PARAM(psh, ppStream))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundDoWork, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundGetSampleTime, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundOverrideSpeakerConfig, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwSpeakerConfig))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseFullHRTF, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134, 4242 /*, 5344=revert to 4134*/)), // Final generic OOVPA: 5344 (revert to 4134); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseLightHRTF, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, /*4134?,*/ 4242, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseFullHRTF4Channel, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseLightHRTF4Channel, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(IsValidFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pwfx))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 4361+ // NOTE: 4361+ is replace into a class function

    REGISTER_OOVPAS(SYM_FUN(XAudioDownloadEffectsImage, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pszImageName), PARAM(psh, pImageLoc), PARAM(psh, dwFlags), PARAM(psh, ppImageDesc))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(XAudioSetEffectData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwEffectIndex), PARAM(psh, pDesc), PARAM(psh, pRawDesc))),
                    SYM_SIG(5028, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in ??5028 or 5120??)
    REGISTER_OOVPAS(SYM_FUN(XAudioCreatePcmFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, nChannels), PARAM(psh, nSamplesPerSec), PARAM(psh, wBitsPerSample), PARAM(psh, pwfx))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: later revision changed to a jmp, and convert into class function
    REGISTER_OOVPAS(SYM_FUN(XAudioCreateAdpcmFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, nChannels), PARAM(psh, nSamplesPerSec), PARAM(psh, pwfx))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0 // NOTE: later revision changed to a jmp, and convert into class function

    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObject, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pszFileName), PARAM(psh, dwDesiredAccess), PARAM(psh, dwShareMode), PARAM(psh, dwCreationDisposition), PARAM(psh, dwFlagsAndAttributes), PARAM(psh, ppMediaObject))),
                    SYM_SIG(3911, 4242, 4361)), // TODO: Need investigation on 3936-4039
    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObjectAsync, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hFile), PARAM(psh, dwMaxPackets), PARAM(psh, ppMediaObject))),
                    SYM_SIG(4432)), // TODO: Need investigation (confirmed does not exist in 4242)
    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObjectEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hFile), PARAM(psh, ppMediaObject))),
                    SYM_SIG(4242, 4361)), // TODO: Need investigation on 3936-4039

    REGISTER_OOVPAS(SYM_FUN(XWaveFileCreateMediaObject, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pszFileName), PARAM(psh, ppwfxFormat), PARAM(psh, ppMediaObject))),
                    SYM_SIG(3911, 4242, 4361)), // TODO: Need investigation on 3936-4039
    REGISTER_OOVPAS(SYM_FUN(XWaveFileCreateMediaObjectEx, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pszFileName), PARAM(psh, hFile), PARAM(psh, ppMediaObject))),
                    SYM_SIG(4242, 4361)), // TODO: Need investigation on 3936?-4039
};

// ******************************************************************
// * DSound_OOVPA
// ******************************************************************
OOVPATableList DSound_OOVPA = { XBSDB_ARRAY_SIZE(DSound_OOVPA_Table), DSound_OOVPA_Table };

#endif
