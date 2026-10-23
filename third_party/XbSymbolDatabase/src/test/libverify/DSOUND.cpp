// SPDX-License-Identifier: ODbL-1.0

#include <map>
#include <string>

#include "unittest.hpp"

static const library_list database_min = {
    REGISTER_SYMBOL_INLINE(CMcpxAPU_ServiceDeferredCommandsLow, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CDirectSound_DoWork, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(DirectSoundCreate, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DirectSoundDoWork, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DirectSoundGetSampleTime, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DirectSoundOverrideSpeakerConfig, VER_RANGE(4039)),
};

static const library_list database_full = {
    //REGISTER_SYMBOL_INLINE(DSS_VOICE_VTABLE, VER_RANGE(3911)), // Not output
    //REGISTER_SYMBOL_INLINE(DSS_STREAM_VTABLE, VER_RANGE(3911)), // Not output

    REGISTER_SYMBOL_INLINE(XAudioCalculatePitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DirectSoundEnterCriticalSection, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(DSound_CRefCount_AddRef, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DSound_CRefCount_Release, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DSound_CMemoryManager_PoolAlloc, VER_RANGE(4134)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Commit3dSettings, VER_RANGE(3911, 4039)),
    // CMcpxAPU_ServiceDeferredCommandsLow moved in db_min
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Set3dDistanceFactor, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Set3dDopplerFactor, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Set3dParameters, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Set3dPosition, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Set3dRolloffFactor, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_Set3dVelocity, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_SetI3DL2Listener, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOLS(CMcpxAPU_SetMixBinHeadroom,
                     REGISTER_SYMBOL(CMcpxAPU_SetMixBinHeadroom_8, VER_RANGE(3911, 4039)),
                     REGISTER_SYMBOL(CMcpxAPU_SetMixBinHeadroom_4, VER_RANGE(4039))),
    REGISTER_SYMBOL_INLINE(CMcpxAPU_SynchPlayback, VER_RANGE(4831)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_GetVoiceProperties, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dConeOrientation, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dConeOutsideVolume, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dMaxDistance, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dMinDistance, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dMode, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dPosition, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dVelocity, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetEG, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetFilter, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetI3DL2Source, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetLFO, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetMixBins, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetPitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_SetVolume, VER_RANGE(3911)),
    REGISTER_SYMBOLS(CMcpxVoiceClient_Commit3dSettings,
                     REGISTER_SYMBOL(CMcpxVoiceClient_Commit3dSettings_4, VER_RANGE(3911, 4039)),
                     REGISTER_SYMBOL(CMcpxVoiceClient_Commit3dSettings_0, VER_RANGE(4039))),
    REGISTER_SYMBOL_INLINE(CMcpxVoiceClient_Set3dParameters, VER_RANGE(3911, 4039)),
    // ========================================================
    //REGISTER_SYMBOL_INLINE(CDirectSoundVoiceSettings_SetMixBins, VER_RANGE(4039)), // Unused, should be useable
    REGISTER_SYMBOL_INLINE(CDirectSoundVoiceSettings_SetMixBinVolumes, VER_RANGE(4039)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_CommitDeferredSettings, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_GetVoiceProperties, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_Set3DVoiceData, VER_RANGE(5455)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetAllParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetConeAngles, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetConeOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetConeOutsideVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetDistanceFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetDopplerFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetEG, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetFilter, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetFormat, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetI3DL2Source, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetLFO, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetMaxDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetMinDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetMixBins, VER_RANGE(3911)),
    REGISTER_SYMBOLS(CDirectSoundVoice_SetMixBinVolumes,
                     REGISTER_SYMBOL(CDirectSoundVoice_SetMixBinVolumes_12, VER_RANGE(3911, 4039)),
                     REGISTER_SYMBOL(CDirectSoundVoice_SetMixBinVolumes_8, VER_RANGE(4039))),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetOutputBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetPitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetFrequency, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetRolloffCurve, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetRolloffFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_SetVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundVoice_Use3DVoiceData, VER_RANGE(5558)),

    // ========================================================

    REGISTER_SYMBOL_INLINE(CDirectSound_CommitDeferredSettings, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_CommitEffectData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_CreateSoundBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_CreateSoundStream, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_DownloadEffectsImage, VER_RANGE(3911)),
    // CDirectSound_DoWork moved in db_min
    REGISTER_SYMBOL_INLINE(CDirectSound_EnableHeadphones, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_GetCaps, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_GetEffectData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_GetOutputLevels, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(CDirectSound_GetSpeakerConfig, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_GetTime, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_MapBufferData, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetAllParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetDistanceFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetDopplerFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetEffectData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetI3DL2Listener, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetMixBinHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetRolloffFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSound_SynchPlayback, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(CDirectSound_UnmapBufferData, VER_RANGE(5344)),

    // ========================================================

    REGISTER_SYMBOL_INLINE(IDirectSound_AddRef, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_CommitDeferredSettings, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_CommitEffectData, VER_RANGE(3911)),
    //REGISTER_SYMBOL_INLINE(IDirectSound_Compact, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_CreateSoundBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_CreateSoundStream, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_DownloadEffectsImage, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_EnableHeadphones, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_GetCaps, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_GetEffectData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_GetOutputLevels, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(IDirectSound_GetSpeakerConfig, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_GetTime, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_MapBufferData, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(IDirectSound_Release, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetAllParameters, VER_RANGE(3911)),
    //REGISTER_SYMBOL_INLINE(IDirectSound_SetCooperativeLevel, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetDistanceFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetDopplerFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetEffectData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetI3DL2Listener, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetMixBinHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetRolloffFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSound_SynchPlayback, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(IDirectSound_UnmapBufferData, VER_RANGE(5344)),

    // DirectSound functions are moved to db_min variable.

    REGISTER_SYMBOL_INLINE(IsValidFormat, VER_RANGE(3911, 4361)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(XAudioDownloadEffectsImage, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(XAudioSetEffectData, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(XAudioCreatePcmFormat, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(XAudioCreateAdpcmFormat, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(XFileCreateMediaObject, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(XFileCreateMediaObjectAsync, VER_RANGE(4432)),
    REGISTER_SYMBOL_INLINE(XFileCreateMediaObjectEx, VER_RANGE(4242)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(XWaveFileCreateMediaObject, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(XWaveFileCreateMediaObjectEx, VER_RANGE(4242)),
};

static const library_list dshrtf_full = {
    REGISTER_SYMBOL_INLINE(CSensaura3d_GetFullHRTFFilterPair, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CSensaura3d_GetLiteHRTFFilterPair, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CFullHRTFSource_GetCenterVolume, VER_RANGE(4039, 4242, 5344)),
    REGISTER_SYMBOL_INLINE(CLightHRTFSource_GetCenterVolume, VER_RANGE(4039, 4242, 5344)),
    REGISTER_SYMBOL_INLINE(CHRTFSource_SetFullHRTF5Channel, VER_RANGE(4039, 4242, 5344)),
    REGISTER_SYMBOL_INLINE(CHRTFSource_SetLightHRTF5Channel, VER_RANGE(4039, 4242, 5344)),
    REGISTER_SYMBOL_INLINE(CHRTFSource_SetFullHRTF4Channel, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(CHRTFSource_SetLightHRTF4Channel, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(CFullHrtfSource_GetHrtfFilterPair, VER_RANGE(4242, 5344)),
    REGISTER_SYMBOL_INLINE(CLightHrtfSource_GetHrtfFilterPair, VER_RANGE(4242, 5344)),
    REGISTER_SYMBOL_INLINE(CHrtfSource_SetAlgorithm_FullHrtf, VER_RANGE(4242, 5344)),
    REGISTER_SYMBOL_INLINE(CHrtfSource_SetAlgorithm_LightHrtf, VER_RANGE(4242, 5344)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(DirectSoundUseFullHRTF, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DirectSoundUseLightHRTF, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(DirectSoundUseFullHRTF4Channel, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(DirectSoundUseLightHRTF4Channel, VER_RANGE(5344)),
};

static const library_list ds3dcalculator_full = {
    REGISTER_SYMBOL_INLINE(CDirectSound3DCalculator_Calculate3D, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(CDirectSound3DCalculator_GetMixBinVolumes, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(CDirectSound3DCalculator_GetPanData, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(CDirectSound3DCalculator_GetVoiceData, VER_RANGE(5344)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(IDirectSound3DCalculator_Calculate3D, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(IDirectSound3DCalculator_GetMixBinVolumes, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(IDirectSound3DCalculator_GetPanData, VER_RANGE(5344)),
    REGISTER_SYMBOL_INLINE(IDirectSound3DCalculator_GetVoiceData, VER_RANGE(5344)),
};

static const library_list dsbuffer_full = {
    REGISTER_SYMBOL_INLINE(DirectSoundCreateBuffer, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CDirectSoundBufferSettings_SetBufferData, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_GetCurrentPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_GetStatus, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_Pause, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_Pause_Ex, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_Play, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_Play_Ex, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_SetBufferData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_SetCurrentPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_Stop, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxBuffer_Stop_Ex, VER_RANGE(4134)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_GetCurrentPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_GetStatus, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_GetVoiceProperties, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_Lock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_Pause, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_PauseEx, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_PlayEx, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_Play, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_Set3DVoiceData, VER_RANGE(5455)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetAllParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetBufferData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetConeAngles, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetConeOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetConeOutsideVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetCurrentPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetDistanceFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetDopplerFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetEG, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetFilter, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetFormat, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetFrequency, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetI3DL2Source, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetLFO, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetLoopRegion, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetMaxDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetMinDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetMixBins, VER_RANGE(3911)),
    REGISTER_SYMBOLS(CDirectSoundBuffer_SetMixBinVolumes,
                     REGISTER_SYMBOL(CDirectSoundBuffer_SetMixBinVolumes_12, VER_RANGE(3911, 4039)),
                     REGISTER_SYMBOL(CDirectSoundBuffer_SetMixBinVolumes_8, VER_RANGE(4039))),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetNotificationPositions, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetOutputBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetPitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetPlayRegion, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetRolloffCurve, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetRolloffFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_SetVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_StopEx, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_Stop, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundBuffer_Use3DVoiceData, VER_RANGE(5558)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_AddRef, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_GetCurrentPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_GetStatus, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_GetVoiceProperties, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Lock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Pause, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_PauseEx, VER_RANGE(4721)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Play, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_PlayEx, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Release, VER_RANGE(3911)),
    //REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Restore, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Set3DVoiceData, VER_RANGE(5455)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetAllParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetBufferData, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetConeAngles, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetConeOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetConeOutsideVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetCurrentPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetDistanceFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetDopplerFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetEG, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetFilter, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetFormat, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetFrequency, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetI3DL2Source, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetLFO, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetLoopRegion, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetMaxDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetMinDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetMixBins, VER_RANGE(3911)),
    REGISTER_SYMBOLS(IDirectSoundBuffer_SetMixBinVolumes,
                     REGISTER_SYMBOL(IDirectSoundBuffer_SetMixBinVolumes_12, VER_RANGE(3911, 4039)),
                     REGISTER_SYMBOL(IDirectSoundBuffer_SetMixBinVolumes_8, VER_RANGE(4039))),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetNotificationPositions, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetOutputBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetPitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetPlayRegion, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetRolloffCurve, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetRolloffFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_SetVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Stop, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_StopEx, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Unlock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundBuffer_Use3DVoiceData, VER_RANGE(5558)),
};

static const library_list dsstream_full = {
    REGISTER_SYMBOL_INLINE(DirectSoundCreateStream, VER_RANGE(3911)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CMcpxStream_Stop, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CMcpxStream_Stop_Ex, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CMcpxStream_Flush, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxStream_Discontinuity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxStream_GetStatus, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CMcpxStream_Pause, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CMcpxStream_Pause_Ex, VER_RANGE(4361)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Constructor, VER_RANGE(3911)),
    // These symbols are manual registered with special scan using above symbol.
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_AddRef, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Discontinuity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Flush, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_GetInfo, VER_RANGE(3911)),
    REGISTER_SYMBOLS(CDirectSoundStream_GetStatus,
                     REGISTER_SYMBOL(CDirectSoundStream_GetStatus__r1, VER_RANGE(3911, 4134)),
                     REGISTER_SYMBOL(CDirectSoundStream_GetStatus__r2, VER_RANGE(4134))),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Process, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Release, VER_RANGE(3911)),
    // -------------------------------
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_FlushEx, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_GetVoiceProperties, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Pause, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_PauseEx, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Set3DVoiceData, VER_RANGE(5455)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetAllParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetConeAngles, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetConeOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetConeOutsideVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetDistanceFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetDopplerFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetEG, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetFilter, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetFormat, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetFrequency, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetI3DL2Source, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetLFO, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetMaxDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetMinDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetMixBins, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetMixBinVolumes_12, VER_RANGE(3911, 4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetMixBinVolumes_8, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetOutputBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetPitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetRolloffCurve, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetRolloffFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_SetVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(CDirectSoundStream_Use3DVoiceData, VER_RANGE(5558)),
    // ========================================================
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_GetVoiceProperties, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_FlushEx, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_Pause, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_PauseEx, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_Set3DVoiceData, VER_RANGE(5455)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetAllParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetConeAngles, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetConeOrientation, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetConeOutsideVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetDistanceFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetDopplerFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetEG, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetLFO, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetFilter, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetFormat, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetFrequency, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetHeadroom, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetI3DL2Source, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetMaxDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetMinDistance, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetMixBins, VER_RANGE(3911)),
    REGISTER_SYMBOLS(IDirectSoundStream_SetMixBinVolumes,
                     REGISTER_SYMBOL(IDirectSoundStream_SetMixBinVolumes_12, VER_RANGE(3911, 4039)),
                     REGISTER_SYMBOL(IDirectSoundStream_SetMixBinVolumes_8, VER_RANGE(4039))),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetOutputBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetPitch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetPosition, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetRolloffCurve, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetRolloffFactor, VER_RANGE(4134)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetVelocity, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_SetVolume, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(IDirectSoundStream_Use3DVoiceData, VER_RANGE(5558)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/dsound.def>
#undef XREF_SYMBOL
    LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(DSS_VOICE_VTABLE)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

static const subcategory_db dsound_db = {
    .name = "general",
    .optional = nullptr,
    .min = &database_min,
    .full = &database_full,
};

static const subcategory_db dshrtf_db = {
    .name = "HRTF",
    .optional = nullptr,
    .min = nullptr,
    .full = &dshrtf_full,
};

static const subcategory_db ds3dcalculator_db = {
    .name = "3D Calculator",
    .optional = nullptr,
    .min = nullptr,
    .full = &ds3dcalculator_full,
};

static const subcategory_db dsbuffer_db = {
    .name = "Buffer",
    .optional = nullptr,
    .min = nullptr,
    .full = &dsbuffer_full,
};

static const subcategory_db dsstream_db = {
    .name = "Stream",
    .optional = nullptr,
    .min = nullptr,
    .full = &dsstream_full,
};

void getLibraryDSOUND(library_db& lib_db)
{
    lib_db.subcategories = { &dsound_db, &dshrtf_db, &ds3dcalculator_db, &dsbuffer_db, &dsstream_db };
    lib_db.xref_offset = XREF_OFFSET;
    lib_db.xref_total = LOCAL_COUNT;
    lib_db.xref_exclude = 2; // 2 symbols are not output internally
}
