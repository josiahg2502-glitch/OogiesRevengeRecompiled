// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library version
//   [LibV] Title Name                       |  Verify   |   Comments
//-----------------------------------------------------------------------
// * [3925] Azurik                           |   100%    | Missing D3D_SetPushBufferSize due locate in BINK section, have 182/196 library.
// * [3948] Shikigami no Shiro               |   100%    | have 178/196 library.
// * [4034] Dark Summit                      |   100%    | have 113/195 library.
// * [4039] New Legends                      |   100%    | have 117/195 library.
// * [4134] Double-S.T.E.A.L                 |   100%    | have 195/202 library.
// * [4242] NFL Blitz 2002                   |   100%    | have 180/202 library.
// * [4361] Hunter The Reckoning             |   100%    | have 117/204 library.
// * [4432] RedCard 2003                     |   100%    | have 184/206 library.
// * [4531] NHL HITZ 2003                    |   100%    | have 196/206 library.
// * [4627] MLB SlugFest 2003                |   100%    | have 216/227 library.
// * [4721] Terminator - Dawn of Fate        |   100%    | have 202/227 library.
// * [4831] Frogger Beyond                   |   100%    | have 200/227 library.
// * [4928] Drihoo                           |   100%    | have 201/228 library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | have 201/229 library.
// * [5120] N.U.D.E.@                        |   100%    | have 211/229 library.
// * [5233] Evil Dead                        |   100%    | have 208/230 library.
// * [5344] Gladius DEMO                     |   100%    | have 202/229 library.
// * [5455] Dinosaur Hunting                 |   100%    | have 207/229 library.
// * [5558] NHL HITZ Pro 2004                |   100%    | have 218/230 library.
// * [5558] XIII                             |   100%    | With Intergrated Hotfixes. have 209/230 library.
// * [5659] NFL Blitz Pro                    |   100%    | have 208/230 library.
// * [5659] Midway Arcade Treasures Paperboy |   100%    | With Intergrated Hotfixes. have 212/230 library.
// * [5788] Digimon Battle Chronicle         |   100%    | have 210/230 library.
// * [5849] Nickelodeon Tak 2                |   100%    | have 210/229 library.

// TODO: Known D3D8 OOVPA issue list
//   * CMiniport_IsFlipPending is XREF in v1 database, any reason for this?
// * Verification needed: Function Name ( Revision )
//   * D3D_AllocContiguousMemory (4034, 4242)
//   * D3D_ClearStateBlockFlags (4034, 4039, 4721, 5028, 5120)
//   * D3D_GetAdapterIdentifier (4034)
//   * D3D_RecordStateBlock (4034, 4039, 4721, 5028, 5120)
//   * D3D_SetPushBufferSize (4034)
//   * D3DBaseTexture_GetLevelCount (4034)
//   * D3DCubeTexture_GetCubeMapSurface (5233)
//   * D3DDevice_AddRef (4034)
//   * D3DDevice_ApplyStateBlock (4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_Begin (4034)
//   * D3DDevice_BeginPushBuffer (3950, 4034, 4242, 4831, 5028)
//   * D3DDevice_BeginStateBlock (3950, 4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_BlockOnFence (4034)
//   * D3DDevice_CaptureStateBlock (4034, 4039, 4432, 4721, 4831, 5028, 5120)
//   * D3DDevice_CreateCubeTexture (4721, 5028, 5233)
//   * D3DDevice_CreateImageSurface (4721, 5028, 5120)
//   * D3DDevice_CreateIndexBuffer (4721, 4928)
//   * D3DDevice_CreatePalette (4721, 4831, 4928, 5120, 5233, 5455)
//   * D3DDevice_CreateStateBlock (4034, 4039, 4242, 4432, 4721, 4928, 5028, 5120)
//   * D3DDevice_CreateVolumeTexture (5028, 5120, 5233, 5455)
//   * D3DDevice_DeletePatch (3950, 4134, 4242, 4432, 4721, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_DeleteStateBlock (3950, 4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_DeleteVertexShader (4034)
//   * D3DDevice_DrawIndexedVerticesUP (4034)
//   * D3DDevice_DrawRectPatch (3950, 4242, 4432, 4721, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_DrawTriPatch (3950, 4034, 4039, 4242, 4432, 4721, 4831, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_DrawVerticesUP (4034)
//   * D3DDevice_EnableOverlay (3950, 4034, 4039)
//   * D3DDevice_End (4034)
//   * D3DDevice_EndPushBuffer (3950, 4034, 4242, 4831, 5028)
//   * D3DDevice_EndStateBlock (3950, 4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_FlushVertexCache (4034)
//   * D3DDevice_GetBackBuffer (4721, 4831, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_GetBackMaterial (4034)
//   * D3DDevice_GetDepthStencilSurface (4034)
//   * D3DDevice_GetDisplayFieldStatus (4034)
//   * D3DDevice_GetDisplayMode (4034)
//   * D3DDevice_GetLightEnable (4034)
//   * D3DDevice_GetMaterial (4034)
//   * D3DDevice_GetModelView (4034)
//   * D3DDevice_GetOverlayUpdateStatus (3950, 4034, 4039, 4134, 4242, 4432, 4531)
//   * D3DDevice_GetPixelShader (4034)
//   * D3DDevice_GetProjectionViewportMatrix (4034, 4039)
//   * D3DDevice_GetPushBufferOffset (3950, 4034, 4242, 4831, 5028)
//   * D3DDevice_GetRenderTarget (4034, 5028)
//   * D3DDevice_GetScissors (4034)
//   * D3DDevice_GetShaderConstantMode (4034, 4039)
//   * D3DDevice_GetTexture2 (4034, 4039)
//   * D3DDevice_GetTile (4034)
//   * D3DDevice_GetVertexShader (4034)
//   * D3DDevice_GetVertexShaderConstant (4034)
//   * D3DDevice_GetVertexShaderDeclaration (4034)
//   * D3DDevice_GetVertexShaderFunction (4034)
//   * D3DDevice_GetVertexShaderInput (4034)
//   * D3DDevice_GetVertexShaderSize (4034)
//   * D3DDevice_GetVertexShaderType (4034)
//   * D3DDevice_InsertCallback (4034, 4039)
//   * D3DDevice_InsertFence (4034)
//   * D3DDevice_IsFencePending (4034)
//   * D3D_CDevice_KickOff (5455,5849)
//   * D3DDevice_KickPushBuffer (4034)
//   * D3DDevice_LoadVertexShaderProgram (4034)
//   * D3DDevice_PersistDisplay (4034)
//   * D3DDevice_PrimeVertexCache (4034)
//   * D3DDevice_RunPushBuffer (4034, 4831, 5028)
//   * D3DDevice_RunVertexStateShader (4034)
//   * D3DDevice_SetBackMaterial (4034)
//   * D3DDevice_SetModelView (4034)
//   * D3DDevice_SetPixelShaderConstant (4034)
//   * D3DDevice_SetPixelShaderProgram (4034)
//   * D3DDevice_SetVertexData2f (4034)
//   * D3DDevice_SetVertexData2s (4034)
//   * D3DDevice_SetVertexData4f (4034)
//   * D3DDevice_SetVertexData4s (4034)
//   * D3DDevice_SetVertexData4ub (4034)
//   * D3DDevice_SetVertexDataColor (4034)
//   * D3DDevice_SetVertexShaderInput (4034)
//   * D3DDevice_SetVerticalBlankCallback (4034)
//   * D3DDevice_SwitchTexture (4034)
//   * D3DDevice_UpdateOverlay (3950, 4034, 4039)
//   * D3DPalette_Lock (4721, 4831, 4928, 5120)
//   * D3DResource_BlockUntilNotBusy (4034)
//   * D3DResource_IsBusy (4034)
//   * D3DResource_Register (4034)
//   * D3DVertexBuffer_GetDesc (4034)
//   * D3DVertexBuffer_Lock (4721, 4831, 4928, 5120, 5233, 5455)
//   * Direct3D_CheckDeviceMultiSampleType (4034)
//   * CMiniport_IsFlipPending (4034, 4039, 4134, 4928, 5028, 5120, 5233, 5455)
//   * D3D_EnumAdapterModes (4034)
//   * D3D_GetAdapterDisplayMode (4034)
//   * D3D_GetAdapterModeCount (4034)
//   * IDirect3DVertexBuffer8_Lock (4721, 5028, 5120, 5233)
// * List of functions might be D3D8LTCG library: (Verifying with Sega GT 2002 title)
//   * D3D_CreateDeviceX (4627)
//   * D3D_KickOffAndWaitForIdle2 (4627)
//   * D3D_CommonSetRenderTargetB (4627)

#include "OOVPA_databases.h"

#include "D3D8/3911.inl"
#include "D3D8/3925.inl"
#include "D3D8/3947.inl"
#include "D3D8/4034.inl"
#include "D3D8/4039.inl"
#include "D3D8/4134.inl"
#include "D3D8/4242.inl"
#include "D3D8/4361.inl"
#include "D3D8/4432.inl"
#include "D3D8/4531.inl"
#include "D3D8/4627.inl"
#include "D3D8/4831.inl"
#include "D3D8/4928.inl"
#include "D3D8/5028.inl"
#include "D3D8/5120.inl"
#include "D3D8/5233.inl"
#include "D3D8/5344.inl"
#include "D3D8/5455.inl"
#include "D3D8/5558.inl"
#include "D3D8/5788.inl"
#include "D3D8/5849.inl"

#define REGISTER_OOVPAS_D3D(Symbol, ...)  REGISTER_OOVPAS_PREFIX(D3D, Symbol, __VA_ARGS__)
#define REGISTER_OOVPAS_D3D8(Symbol, ...) REGISTER_OOVPAS_PREFIX(D3D8, Symbol, __VA_ARGS__)

// ******************************************************************
// * D3D8_OOVPA_Table
// ******************************************************************
static OOVPATable D3D8_OOVPA_Table[] = {
    // Custom manual search by reverse engineering team (which will not be public to the user)
    REGISTER_OOVPAS_M(SYM_INT(D3DDevice__m_VerticalBlankEvent__GenericFragment),
                      SYM_SIG(3911)), // This OOVPA signature is not a symbol. Read its note for more details.
    REGISTER_OOVPAS_M(SYM_INT(D3DRS_Stencils_and_Occlusion__GenericFragment),
                      SYM_SIG(3911)), // This OOVPA signature is not a symbol. Read its note for more details.

    // Variables
    REGISTER_OOVPAS_M(SYM_VAR(D3D_g_pDevice),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_PixelShader_OFFSET),
                      SYM_SIG(0)),
#if 0 // Unused
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_Textures_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_Palettes_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_RenderTarget_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_DepthStencil_OFFSET),
                      SYM_SIG(0)),
#endif
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_VerticalBlankEvent_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_SwapCallback_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_VBlankCallback_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(D3DDevice__m_VertexShader_OFFSET),
                      SYM_SIG(0)),

    REGISTER_OOVPAS(SYM_FUN(D3D_UpdateProjectionViewportTransform, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3900, 3901)), // Final generic OOVPA: 4034; Removed: 0 // NOTE: 3901 is 4034 signature, except LTCG title been detected in 3925.

    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_InitializeFrameBuffers, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pPresentationParams))),
                        SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_FreeFrameBuffers, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(3911, 4034, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_SetStateUP, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_SetStateVB, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, unknown2))), // TODO: Update unknown parameter name(s) if able.
                        SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0

    REGISTER_OOVPAS(SYM_FUN(D3D_CreateTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Depth), PARAM(psh, Levels), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, isCube), PARAM(psh, isVolume), PARAM(psh, ppTexture))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_MakeSpace, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(3911)), // NOTE: has multiple rets.
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_CreateCtxDmaObject, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3), PARAM(psh, unknown4), PARAM(psh, unknown5))), // TODO: Update unknown parameter name(s) if able.
                        SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_InitHardware, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(3911, 4034, 5455)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_IsFlipPending, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(3911, 4242, 4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(D3DBaseTexture_GetLevelCount, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_GetCubeMapSurface2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, FaceType), PARAM(psh, Level))),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_GetCubeMapSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, FaceType), PARAM(psh, Level), PARAM(psh, ppCubeMapSurface))),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_LockRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, FaceType), PARAM(psh, Level), PARAM(psh, pLockedBox), PARAM(psh, pRect), PARAM(psh, Flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134, 4242, 4627, 5028, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_ApplyStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Token))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Begin, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PrimitiveType))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPush, CALL(std), STACK(8), PARAMS(PARAM(psh, Count), PARAM(psh, ppPush))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPush, CALL(std), STACK(4), PARAMS(PARAM(psh, Count))),
                    SYM_SIG(4531, 4627, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPushBuffer))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginStateBig, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginVisibilityTest, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BlockOnFence, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Fence))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BlockUntilVerticalBlank, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CaptureStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Token))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Clear, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Count), PARAM(psh, pRects), PARAM(psh, Flags), PARAM(psh, Color), PARAM(psh, Z), PARAM(psh, Stencil))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CopyRects, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSourceSurface), PARAM(psh, pSourceRectsArray), PARAM(psh, cRects), PARAM(psh, pDestinationSurface), PARAM(psh, pDestPointsArray))),
                    SYM_SIG(3911, 4627, 5120)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateCubeTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, EdgeLength), PARAM(psh, Levels), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, Pool), PARAM(psh, ppCubeTexture))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateImageSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Format), PARAM(psh, ppBackBuffer))),
                    SYM_SIG(3911, 4034, 4627)), // TODO 4721,4928 (from 4627's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateIndexBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Length), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, Pool), PARAM(psh, ppIndexBuffer))),
                    SYM_SIG(3911, 4627)), // TODO: This needs to be verified on 4361
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateIndexBuffer2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Length))),
                    SYM_SIG(4627, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePalette, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Size), PARAM(psh, ppPalette))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePalette2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Size))),
                    SYM_SIG(4627, 5344, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePixelShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPSDef), PARAM(psh, pHandle))),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Type), PARAM(psh, pToken))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateTexture2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Depth), PARAM(psh, Levels), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, D3DResource))),
                    SYM_SIG(4627, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Levels), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, Pool), PARAM(psh, ppTexture))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Length), PARAM(psh, Usage), PARAM(psh, FVF), PARAM(psh, Pool), PARAM(psh, ppVertexBuffer))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexBuffer2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Length))),
                    SYM_SIG(4627, 5344, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pDeclaration), PARAM(psh, pFunction), PARAM(psh, pHandle), PARAM(psh, Usage))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVolumeTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Depth), PARAM(psh, Levels), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, Pool), PARAM(psh, ppVolumeTexture))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeletePatch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeletePixelShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle))),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeleteStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Token))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeleteVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle))),
                    SYM_SIG(3911, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawIndexedVertices, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PrimitiveType), PARAM(psh, VertexCount), PARAM(psh, pIndexData))),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawIndexedVerticesUP, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PrimitiveType), PARAM(psh, VertexCount), PARAM(psh, pIndexData), PARAM(psh, pVertexStreamZeroData), PARAM(psh, VertexStreamZeroStride))),
                    SYM_SIG(3911, 5028, 5344)), // Final generic OOVPA: 5344; Removed: 0 // TODO: Need verify title with 4034 version.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawRectPatch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, pNumSegs), PARAM(psh, pRectPatchInfo))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawTriPatch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, pNumSegs), PARAM(psh, pTriPatchInfo))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawVertices, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PrimitiveType), PARAM(psh, StartVertex), PARAM(psh, VertexCount))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawVerticesUP, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PrimitiveType), PARAM(psh, VertexCount), PARAM(psh, pVertexStreamZeroData), PARAM(psh, VertexStreamZeroStride))),
                    SYM_SIG(3911, 4039, 5344)), // Final generic OOVPA: 5344; Removed: 0 // TODO: Need verify title with 4034 version.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EnableOverlay, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Enable))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_End, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndPush, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPush))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pToken))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndVisibilityTest, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_FlushVertexCache, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, BackBuffer), PARAM(psh, Type), PARAM(psh, ppBackBuffer))),
                    SYM_SIG(3911, 4034, 4134, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackBuffer2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, BackBuffer))),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackMaterial, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pMaterial))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetCreationParameters, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pParameters))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDepthStencilSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, ppZStencilSurface))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDepthStencilSurface2, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDeviceCaps, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pCaps))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDisplayFieldStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pFieldStatus))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDisplayMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pModes))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetGammaRamp, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pRamp))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetLight, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pLight))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetLightEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pEnable))),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetMaterial, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pMaterial))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetModelView, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pModelView))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetOverlayUpdateStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetPersistedSurface2, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4928)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetPixelShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Name), PARAM(psh, pHandle))),
                    SYM_SIG(3911, 4039, 4134, 5028, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetProjectionViewportMatrix, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pProjectionViewport))),
                    SYM_SIG(3911, 4134, 4627, 5344, 5558)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetPushBufferOffset, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pOffset))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetRenderTarget2, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetRenderTarget, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, ppRenderTarget))),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetScissors, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pCount), PARAM(psh, pExclusive), PARAM(psh, pRects))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetShaderConstantMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pMode))),
                    SYM_SIG(3911, 4134, 4627, 5028, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetStreamSource2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, StreamNumber), PARAM(psh, pStride))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTexture2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage))),
                    SYM_SIG(3911, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTile, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pTile))),
                    SYM_SIG(3911, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTransform, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, State), PARAM(psh, pMatrix))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pHandle))),
                    SYM_SIG(3911, 4039, 4134, 5028, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderConstant, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, pConstantData), PARAM(psh, ConstantCount))),
                    SYM_SIG(3911, 4039, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderDeclaration, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, pData), PARAM(psh, pSizeOfData))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderFunction, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, pData), PARAM(psh, pSizeOfData))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderInput, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pHandle), PARAM(psh, pStreamCount), PARAM(psh, pStreamInputs))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderSize, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, pSize))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderType, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, pType))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetViewport, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pViewport))),
                    SYM_SIG(3911, 5455)), // Was 4627 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetViewportOffsetAndScale, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pOffset), PARAM(psh, pScale))),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVisibilityTestResult, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pResult), PARAM(psh, pTimeStamp))),
                    SYM_SIG(3911, 5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_InsertCallback, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Type), PARAM(psh, pCallback), PARAM(psh, Context))),
                    SYM_SIG(3911, 4134, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_InsertFence, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_IsBusy, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_IsFencePending, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Fence))),
                    SYM_SIG(3911, 4039, 5028)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_KickOff, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(3911, 4034, 4531, 5028, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_KickPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LightEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, bEnable))),
                    SYM_SIG(3911, 5344)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LoadVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, Address))),
                    SYM_SIG(3911, 4034, 4627, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LoadVertexShaderProgram, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pFunction), PARAM(psh, Address))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_MakeSpace, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4034, 4134)), // NOTE: LTCG has duplicate functions, need to find out how to resolve this issue with cross referencing.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_PersistDisplay, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4627, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Present, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSourceRect), PARAM(psh, pDestRect), PARAM(psh, pUnused3), PARAM(psh, pUnused4))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_PrimeVertexCache, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, VertexCount), PARAM(psh, pIndexData))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Reset, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPresentationParameters))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_RunPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPushBuffer), PARAM(psh, pFixup))),
                    SYM_SIG(3911, 4039, 4627, 5120, 5558)), // for 5455 (from 5558's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_RunVertexStateShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Address), PARAM(psh, pData))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SelectVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, Address))),
                    SYM_SIG(3911, 4034, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SelectVertexShaderDirect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pVAF), PARAM(psh, Address))),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetBackBufferScale, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, x), PARAM(psh, y))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetBackMaterial, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pMaterial))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetDepthClipPlanes, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Near), PARAM(psh, Far), PARAM(psh, Flags))),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetFlickerFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Filter))),
                    SYM_SIG(3911, 4034, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetGammaRamp, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwFlags), PARAM(psh, pRamp))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetIndices, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pIndexData), PARAM(psh, BaseVertexIndex))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetLight, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pLight))),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetMaterial, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pMaterial))),
                    SYM_SIG(3911, 4034, 4134, 4627, 5344, 5558, 5788)), // Was 4627 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetModelView, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pModelView), PARAM(psh, pInverseModelView), PARAM(psh, pComposite))),
                    SYM_SIG(3911, 4039, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPalette, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, pPalette))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle))),
                    SYM_SIG(3911, 4034, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShaderConstant, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, pConstantData), PARAM(psh, ConstantCount))),
                    SYM_SIG(3911, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShaderProgram, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPSDef))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderState_Simple, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Method), PARAM(edx, Value))),
                      SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderStateNotInline, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, State), PARAM(psh, Value))),
                      SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: Must be after D3DDevice_SetRenderState_Simple.
    // NOTE: Some or most of render state signatures below must be after D3DDevice_SetRenderStateNotInline.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, State), PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, State), PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: There is a verified duplicate function.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_BackFillMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_C(SYM_FUN(D3DDevice_SetRenderState_CullMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                      SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_Deferred, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, State), PARAM(edx, Value))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_DoNotCullUncompressed, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_Dxt1NoiseEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_EdgeAntiAlias, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderState_FillMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                      SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_FogColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_FrontFace, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_LineWidth, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_LogicOp, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleAntiAlias, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleMask, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleRenderTargetMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleType, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 3925)), // Final generic OOVPA: 3925 Removed: 4034
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_NormalizeNormals, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_OcclusionCullEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 1024)), // Final generic OOVPA: 3911 (LTCG) / 4034 (non-LTCG); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_PSTextureModes, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_RopZCmpAlwaysRead, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_RopZRead, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_SampleAlpha, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ShadowFunc, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilCullEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 1024)), // Final generic OOVPA: 3911 (LTCG) / 4034 (non-LTCG); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034, 5849)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilFail, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034, 5849)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_TextureFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_TwoSidedLighting, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_VertexBlend, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_YuvEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 1024)), // Final generic OOVPA: 3911 (LTCG) / 4034 (non-LTCG); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ZBias, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ZEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Value))),
                    SYM_SIG(3911, 4034, 4134, 4432)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderTarget, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pRenderTarget), PARAM(psh, pNewZStencil))),
                    SYM_SIG(3911, 3947, 4034, 4039, 4627, 5344, 5455)), // Final generic OOVPA: 5344/5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderTargetFast, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pRenderTarget), PARAM(psh, pNewZStencil), PARAM(psh, Flags))),
                    SYM_SIG(5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetScissors, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Count), PARAM(psh, Exclusive), PARAM(psh, pRects))),
                    SYM_SIG(3911, 5344, 5558)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetScreenSpaceOffset, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, x), PARAM(psh, y))),
                    SYM_SIG(4034, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetShaderConstantMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Mode))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetSoftDisplayFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Enable))),
                    SYM_SIG(3911, 4034, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetStipple, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPattern))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetStreamSource, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, StreamNumber), PARAM(psh, pStreamData), PARAM(psh, Stride))),
                      SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetSwapCallback, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pCallback))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, pTexture))),
                    SYM_SIG(3911, 4034, 4361, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureStageStateNotInline, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, Type), PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_BorderColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_BumpEnv, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, Type), PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_ColorKeyColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, Value))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_Deferred, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Stage), PARAM(edx, Type), PARAM(psh, Value))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetTextureState_TexCoordIndex, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Stage), PARAM(psh, Value))),
                      SYM_SIG(3911, 4034, 4242, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTile, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pTile))),
                    SYM_SIG(3911, 4034, 4627)), // Then it has changed calls ?SetTileNoWait@D3D@@YGXKPBU_D3DTILE@@@Z in XDK 4627 and higher.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTransform, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, State), PARAM(psh, pMatrix))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_MultiplyTransform, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, State), PARAM(psh, pMatrix))),
                    SYM_SIG(3911, 4034)), // TODO: Verify 4034 is correct
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData2f, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, a), PARAM(psh, b))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData2s, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, a), PARAM(psh, b))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4f, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, a), PARAM(psh, b), PARAM(psh, c), PARAM(psh, d))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4s, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, a), PARAM(psh, b), PARAM(psh, c), PARAM(psh, d))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4ub, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, a), PARAM(psh, b), PARAM(psh, c), PARAM(psh, d))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexDataColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, Color))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle))),
                    SYM_SIG(3911, 4034, 4134, 5028, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Register), PARAM(psh, pConstantData), PARAM(psh, ConstantCount))),
                    SYM_SIG(3911, 4034, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant1, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Register), PARAM(edx, pConstantData))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant1Fast, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Register), PARAM(edx, pConstantData))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant4, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Register), PARAM(edx, pConstantData))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstantNotInline, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Register), PARAM(edx, pConstantData), PARAM(psh, ConstantCount))),
                    SYM_SIG(4627, 5028, 5558)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstantNotInlineFast, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Register), PARAM(edx, pConstantData), PARAM(psh, ConstantCount))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderInput, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Handle), PARAM(psh, StreamCount), PARAM(psh, pStreamInputs))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderInputDirect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pVAF), PARAM(psh, StreamCount), PARAM(psh, pStreamInputs))),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVerticalBlankCallback, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pCallback))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetViewport, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pViewport))),
                    SYM_SIG(3911, 4034, 5344, 5455)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Suspend, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Swap, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Flags))),
                    SYM_SIG(4034, 4531, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SwitchTexture, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, Method), PARAM(edx, Data), PARAM(psh, Format))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_UpdateOverlay, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSurface), PARAM(psh, SrcRect), PARAM(psh, DstRect), PARAM(psh, EnableColorKey), PARAM(psh, ColorKey))),
                    SYM_SIG(3911, 4531, 5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DPalette_Lock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, ppColors), PARAM(psh, Flags))),
                    SYM_SIG(3911, 4531, 4627)), // Called D3DPalette_Lock2 (from 4627's comment) NOTE: Use D3DPalette_Lock2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DPalette_Lock2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, Flags))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_AddRef, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_BlockUntilNotBusy, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_GetType, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911, 4034)), // Probably not even necessary... (from 3925's comment) // I forget why I had this in here... (from 5028's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DResource_IsBusy, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_Register, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pBase))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DSurface_GetDesc, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pDesc))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DSurface_LockRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pLockedRect), PARAM(psh, pRect), PARAM(psh, Flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_GetSurfaceLevel, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, Level), PARAM(psh, ppSurfaceLevel))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_GetSurfaceLevel2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, Level))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_LockRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, Level), PARAM(psh, pLockedRect), PARAM(psh, pRect), PARAM(psh, Flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_GetDesc, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, pDesc))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_Lock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pVertexBuffer), PARAM(psh, OffsetToLock), PARAM(psh, SizeToLock), PARAM(psh, ppbData), PARAM(psh, Flags))),
                    SYM_SIG(3911, 4034, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_Lock2, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pVertexBuffer), PARAM(psh, Flags))),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DVolumeTexture_LockBox, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis), PARAM(psh, Level), PARAM(psh, pLockedVolume), PARAM(psh, pBox), PARAM(psh, Flags))),
                    SYM_SIG(3911)), // Just calls Lock3DSurface (from 4134, 4432's comment)
    REGISTER_OOVPAS(SYM_FUN(D3D_AllocContiguousMemory, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwSize), PARAM(psh, dwAllocAttributes))),
                    SYM_SIG(3911, 5455)), // Final generic OOVPA: 5455; Removed: 0 // Just calls MmAllocateContiguousMemory.
    REGISTER_OOVPAS(SYM_FUN(D3D_BlockOnResource, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pResource))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3D_BlockOnTime, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2))), // TODO: Update unknown parameter name(s) if able. Both parameters do change over time. Likely may need a separate group...
                    SYM_SIG(3911, 4034, 4627, 5028, 5558)), // NOTE: unknown2 parameter can be different value from same caller function over time.
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_GetDisplayCapabilities, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                        SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_CheckDeviceFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, DeviceType), PARAM(psh, AdapterFormat), PARAM(psh, Usage), PARAM(psh, RType), PARAM(psh, CheckFormat))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_ClearStateBlockFlags, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(D3D_CommonSetDebugRegisters, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                      SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3D_CommonSetRenderTarget, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pRenderTarget), PARAM(psh, pNewZStencil), PARAM(psh, pUnknown3))),
                    SYM_SIG(4627, 5028)), // Final generic OOVPA: 4627; Removed: 5344
    REGISTER_OOVPAS(SYM_FUN(D3D_CommonSetMultiSampleModeAndScale, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(edx, pViewport))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3D_CreateStandAloneSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3), PARAM(psh, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4034)),
    REGISTER_OOVPAS(SYM_FUN(D3D_DestroyResource, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pResource))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_EnumAdapterModes, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, Mode), PARAM(psh, pMode))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetAdapterDisplayMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, pMode))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetAdapterIdentifier, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, Flags), PARAM(psh, pIdentifier))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetAdapterModeCount, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, Format))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetDeviceCaps, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, DeviceType), PARAM(psh, pCaps))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_KickOffAndWaitForIdle, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4034, 4627, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3D_LazySetPointParams, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Device))),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3D_RecordStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pToken))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetFence, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Flags))),
                    SYM_SIG(3911, 4034, 4134, 5028, 5558)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetPushBufferSize, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, PushBufferSize), PARAM(psh, KickOffSize))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetTileNoWait, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Index), PARAM(psh, pTile))),
                    SYM_SIG(4627, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(Direct3D_CheckDeviceMultiSampleType, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, DeviceType), PARAM(psh, SurfaceFormat), PARAM(psh, Windowed), PARAM(psh, MultiSampleType))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(Direct3D_CreateDevice, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Adapter), PARAM(psh, DeviceType), PARAM(psh, hFocusWindow), PARAM(psh, BehaviorFlags), PARAM(psh, pPresentationParameters), PARAM(psh, ppReturnedDeviceInterface))),
                    SYM_SIG(3911, 5028)),
    REGISTER_OOVPAS_D3D8(SYM_FUN(Get2DSurfaceDesc, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPixelContainer), PARAM(psh, dwLevel), PARAM(psh, pDesc))),
                         SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_D3D8(SYM_FUN(Lock2DSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPixelContainer), PARAM(psh, FaceType), PARAM(psh, Level), PARAM(psh, pLockedRect), PARAM(psh, pRect), PARAM(psh, Flags))),
                         SYM_SIG(3911)),
    REGISTER_OOVPAS_D3D8(SYM_FUN(Lock3DSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pPixelContainer), PARAM(psh, Level), PARAM(psh, pLockedVolume), PARAM(psh, pBox), PARAM(psh, Flags))),
                         SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_MakeRequestedSpace, CALL(std), STACK(4), PARAMS(PARAM(psh, RequestedSpace))),
                    SYM_SIG(4034)), // Final generic OOVPA: 4034??; Removed: 4134 // NOTE: has multiple rets.
    REGISTER_OOVPAS(SYM_FUN(D3D_MakeRequestedSpace, CALL(std), STACK(8), PARAMS(PARAM(psh, MinimumSpace), PARAM(psh, RequestedSpace))),
                    SYM_SIG(4134, 5558)), // Final generic OOVPA: 5558; Removed: 0 // NOTE: has multiple rets.
    REGISTER_OOVPAS(SYM_FUN(XMETAL_StartPush, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pDevice))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4034??
    REGISTER_OOVPAS(SYM_FUN(IDirect3DVertexBuffer8_Lock, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pVertexBuffer), PARAM(psh, OffsetToLock), PARAM(psh, SizeToLock), PARAM(psh, ppbData), PARAM(psh, Flags))),
                    SYM_SIG(4627)),
};

// ******************************************************************
// * D3D8_OOVPA
// ******************************************************************
OOVPATableList D3D8_OOVPA = { XBSDB_ARRAY_SIZE(D3D8_OOVPA_Table), D3D8_OOVPA_Table };
