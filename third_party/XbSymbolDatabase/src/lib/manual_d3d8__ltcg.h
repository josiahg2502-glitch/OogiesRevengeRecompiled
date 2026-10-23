// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

#pragma once

// Notes :
// * Most renderstates were introduced in the (lowest known) XDK version : 3424
// * Some titles use XDK version 3911
// * The lowest XDK version that has been verified is : 3944
// * All renderstates marked 3424 are also verified to be present in 3944
// * Twenty-three additional renderstates were introduced after 3944 and up to 4627;
// *   D3DRS_DEPTHCLIPCONTROL, D3DRS_STIPPLEENABLE, D3DRS_SIMPLE_UNUSED8..D3DRS_SIMPLE_UNUSED1,
// *   D3DRS_SWAPFILTER, D3DRS_PRESENTATIONINTERVAL, D3DRS_DEFERRED_UNUSED8..D3DRS_DEFERRED_UNUSED1,
// *   D3DRS_MULTISAMPLEMODE, D3DRS_MULTISAMPLERENDERTARGETMODE, and D3DRS_SAMPLEALPHA
// * One renderstate, D3DRS_MULTISAMPLETYPE, was removed (after 3944, before 4039, perhaps even 4034)
// * Around when D3DRS_MULTISAMPLETYPE was removed, D3DRS_MULTISAMPLEMODE was introduced (after 3944, before or at 4039, perhaps even 4034)
// * We MUST list exact versions for all above mentioned renderstates, since their inserts impacts mapping!
// * Renderstates verified to be introduced at 4039 or earlier, may have been introduced at 4034 or earlier
// * Renderstates were finalized in 4627 (so no change after that version)
// * XDK versions that have been verified : 3944, 4039, 4134, 4242, 4361, 4432, 4531, 4627, 4721, 4831, 4928, 5028, 5120, 5233, 5344, 5455, 5558, 5659, 5788, 5849, 5933
// * Renderstates with uncertain validity are marked "Verified absent in #XDK#" and/or "present in #XDK#". Some have "Might be introduced "... "in between" or "around #XDK#"
// * Renderstates after D3DRS_MULTISAMPLEMASK have no host DX9 D3DRS mapping, thus no impact
typedef struct _RenderStateRevision {
    uint16_t version;
    uint16_t removed;
    unsigned xref;
    const char* name;
} RenderStateRevision;

#define XREF_NAME(x) XREF_##x, #x

static const RenderStateRevision DxbxRenderStateInfo[] = {
    // Ord | Version (add/remove) | Name
    /*   0 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs0) */ },
    /*   1 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs1) */ },
    /*   2 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs2) */ },
    /*   3 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs3) */ },
    /*   4 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs4) */ },
    /*   5 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs5) */ },
    /*   6 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs6) */ },
    /*   7 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaInputs7) */ },
    /*   8 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSFinalCombinerInputsABCD) */ },
    /*   9 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSFinalCombinerInputsEFG) */ },
    /*  10 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_0) */ },
    /*  11 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_1) */ },
    /*  12 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_2) */ },
    /*  13 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_3) */ },
    /*  14 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_4) */ },
    /*  15 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_5) */ },
    /*  16 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_6) */ },
    /*  17 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant0_7) */ },
    /*  18 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_0) */ },
    /*  19 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_1) */ },
    /*  20 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_2) */ },
    /*  21 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_3) */ },
    /*  22 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_4) */ },
    /*  23 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_5) */ },
    /*  24 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_6) */ },
    /*  25 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSConstant1_7) */ },
    /*  26 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs0) */ },
    /*  27 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs1) */ },
    /*  28 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs2) */ },
    /*  29 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs3) */ },
    /*  30 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs4) */ },
    /*  31 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs5) */ },
    /*  32 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs6) */ },
    /*  33 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSAlphaOutputs7) */ },
    /*  34 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs0) */ },
    /*  35 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs1) */ },
    /*  36 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs2) */ },
    /*  37 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs3) */ },
    /*  38 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs4) */ },
    /*  39 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs5) */ },
    /*  40 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs6) */ },
    /*  41 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBInputs7) */ },
    /*  42 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSCompareMode) */ },
    /*  43 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSFinalCombinerConstant0) */ },
    /*  44 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSFinalCombinerConstant1) */ },
    /*  45 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs0) */ },
    /*  46 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs1) */ },
    /*  47 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs2) */ },
    /*  48 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs3) */ },
    /*  49 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs4) */ },
    /*  50 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs5) */ },
    /*  51 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs6) */ },
    /*  52 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSRGBOutputs7) */ },
    /*  53 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSCombinerCount) */ },
    /*  54 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSTextureModes_Reserved) */ },          // Dxbx note : This takes the slot of X_D3DPIXELSHADERDEF.PSTextureModes, set by D3DDevice_SetRenderState_LogicOp?
    /*  55 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSDotMapping) */ },                     //
    /*  56 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PSInputTexture) */ },                   //
    /* End of "pixel-shader" render states, continuing with "simple" render states: */ //
    /*  57 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ZFunc) */ },                            //
    /*  58 */ { 3424, 0000 /*, XREF_NAME(D3DRS_AlphaFunc) */ },                        //
    /*  59 */ { 3424, 0000 /*, XREF_NAME(D3DRS_AlphaBlendEnable) */ },                 //
    /*  60 */ { 3424, 0000 /*, XREF_NAME(D3DRS_AlphaTestEnable) */ },                  //
    /*  61 */ { 3424, 0000 /*, XREF_NAME(D3DRS_AlphaRef) */ },                         //
    /*  62 */ { 3424, 0000 /*, XREF_NAME(D3DRS_SrcBlend) */ },                         //
    /*  63 */ { 3424, 0000 /*, XREF_NAME(D3DRS_DestBlend) */ },                        //
    /*  64 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ZWriteEnable) */ },                     //
    /*  65 */ { 3424, 0000 /*, XREF_NAME(D3DRS_DitherEnable) */ },                     //
    /*  66 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ShadeMode) */ },                        //
    /*  67 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ColorWriteEnable) */ },                 // *_ALPHA, etc. per-channel write enable
    /*  68 */ { 3424, 0000 /*, XREF_NAME(D3DRS_StencilZFail) */ },                     //
    /*  69 */ { 3424, 0000 /*, XREF_NAME(D3DRS_StencilPass) */ },                      //
    /*  70 */ { 3424, 0000 /*, XREF_NAME(D3DRS_StencilFunc) */ },                      //
    /*  71 */ { 3424, 0000 /*, XREF_NAME(D3DRS_StencilRef) */ },                       //
    /*  72 */ { 3424, 0000 /*, XREF_NAME(D3DRS_StencilMask) */ },                      //
    /*  73 */ { 3424, 0000 /*, XREF_NAME(D3DRS_StencilWriteMask) */ },                 //
    /*  74 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BlendOp) */ },                          //
    /*  75 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BlendColor) */ },                       //
    /* D3D9 D3DRS_BLENDFACTOR : D3DColor used for a constant blend factor during */    //
    /* alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */            //
    /*  76 */ { 3424, 0000 /*, XREF_NAME(D3DRS_SwathWidth) */ },                       //
    /*  77 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PolygonOffsetZSlopeScale) */ },         //
    /*  78 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PolygonOffsetZOffset) */ },             //
    /*  79 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointOffsetEnable) */ },                //
    /*  80 */ { 3424, 0000 /*, XREF_NAME(D3DRS_WireFrameOffsetEnable) */ },            //
    /*  81 */ { 3424, 0000 /*, XREF_NAME(D3DRS_SolidOffsetEnable) */ },                //
    /*  82 */ { 4432, 0000 /*, XREF_NAME(D3DRS_DepthClipControl) */ },                 // Verified absent in 4361, present in 4432  TODO: Might be introduced around 4400?
    /*  83 */ { 4627, 0000 /*, XREF_NAME(D3DRS_StippleEnable) */ },                    // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  84 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused8) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  85 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused7) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  86 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused6) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  87 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused5) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  88 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused4) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  89 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused3) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  90 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused2) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /*  91 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Simple_Unused1) */ },                   // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* End of "simple" render states, continuing with "deferred" render states: */     //
    /* Verified as XDK 3911 Deferred RenderStates(3424 yet to do) */                   //
    /*  92 */ { 3424, 0000, XREF_NAME(D3DRS_FogEnable) },                              // TRUE to enable fog blending
    /*  93 */ { 3424, 0000 /*, XREF_NAME(D3DRS_FogTableMode) */ },                     // D3DFOGMODE
    /*  94 */ { 3424, 0000 /*, XREF_NAME(D3DRS_FogStart) */ },                         // float fog start (for both vertex and pixel fog)
    /*  95 */ { 3424, 0000 /*, XREF_NAME(D3DRS_FogEnd) */ },                           // float fog end
    /*  96 */ { 3424, 0000 /*, XREF_NAME(D3DRS_FogDensity) */ },                       // float fog density // + NV2A_FOG_EQUATION_LINEAR + NV2A_FOG_EQUATION_QUADRATIC
    /*  97 */ { 3424, 0000 /*, XREF_NAME(D3DRS_RangeFogEnable) */ },                   // TRUE to enable range-based fog
    /*  98 */ { 3424, 0000 /*, XREF_NAME(D3DRS_Wrap0) */ },                            // D3DWRAP* flags (D3DWRAP_U, D3DWRAPCOORD_0, etc.) for 1st texture coord.
    /*  99 */ { 3424, 0000 /*, XREF_NAME(D3DRS_Wrap1) */ },                            // D3DWRAP* flags (D3DWRAP_U, D3DWRAPCOORD_0, etc.) for 2nd texture coord.
    /* 100 */ { 3424, 0000 /*, XREF_NAME(D3DRS_Wrap2) */ },                            // D3DWRAP* flags (D3DWRAP_U, D3DWRAPCOORD_0, etc.) for 3rd texture coord.
    /* 101 */ { 3424, 0000 /*, XREF_NAME(D3DRS_Wrap3) */ },                            // D3DWRAP* flags (D3DWRAP_U, D3DWRAPCOORD_0, etc.) for 4th texture coord.
    /* 102 */ { 3424, 0000 /*, XREF_NAME(D3DRS_Lighting) */ },                         // TRUE to enable lighting // TODO: Needs push-buffer data conversion
    /* 103 */ { 3424, 0000 /*, XREF_NAME(D3DRS_SpecularEnable) */ },                   // TRUE to enable specular
    /* 104 */ { 3424, 0000 /*, XREF_NAME(D3DRS_LocalViewer) */ },                      // TRUE to enable camera-relative specular highlights
    /* 105 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ColorVertex) */ },                      // TRUE to enable per-vertex color
    /* 106 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BackSpecularMaterialSource) */ },       // D3DMATERIALCOLORSOURCE (Xbox extension) nsp.
    /* 107 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BackDiffuseMaterialSource) */ },        // D3DMATERIALCOLORSOURCE (Xbox extension) nsp.
    /* 108 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BackAmbientMaterialSource) */ },        // D3DMATERIALCOLORSOURCE (Xbox extension) nsp.
    /* 109 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BackEmissiveMaterialSource) */ },       // D3DMATERIALCOLORSOURCE (Xbox extension) nsp.
    /* 110 */ { 3424, 0000 /*, XREF_NAME(D3DRS_SpecularMaterialSource) */ },           // D3DMATERIALCOLORSOURCE
    /* 111 */ { 3424, 0000 /*, XREF_NAME(D3DRS_DiffuseMaterialSource) */ },            // D3DMATERIALCOLORSOURCE
    /* 112 */ { 3424, 0000 /*, XREF_NAME(D3DRS_AmbientMaterialSource) */ },            // D3DMATERIALCOLORSOURCE
    /* 113 */ { 3424, 0000 /*, XREF_NAME(D3DRS_EmissiveMaterialSource) */ },           // D3DMATERIALCOLORSOURCE
    /* 114 */ { 3424, 0000 /*, XREF_NAME(D3DRS_BackAmbient) */ },                      // D3DCOLOR (Xbox extension) // ..NV2A_MATERIAL_FACTOR_Back_B nsp. Was NV2A_LIGHT_MODEL_Back_AMBIENT_R
    /* 115 */ { 3424, 0000 /*, XREF_NAME(D3DRS_Ambient) */ },                          // D3DCOLOR // ..NV2A_LIGHT_MODEL_FRONT_Ambient_B + NV2A_MATERIAL_FACTOR_FRONT_R..NV2A_MATERIAL_FACTOR_FRONT_A  Was NV2A_LIGHT_MODEL_FRONT_AMBIENT_R
    /* 116 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointSize) */ },                        // float point size
    /* 117 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointSize_Min) */ },                    // float point size min threshold
    /* 118 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointSpriteEnable) */ },                // TRUE to enable point sprites
    /* 119 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointScaleEnable) */ },                 // TRUE to enable point size scaling
    /* 120 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointScale_A) */ },                     // float point attenuation A value
    /* 121 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointScale_B) */ },                     // float point attenuation B value
    /* 122 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointScale_C) */ },                     // float point attenuation C value
    /* 123 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PointSize_Max) */ },                    // float point size max threshold
    /* 124 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PatchEdgeStyle) */ },                   // D3DPATCHEDGESTYLE
    /* 125 */ { 3424, 0000 /*, XREF_NAME(D3DRS_PatchSegments) */ },                    // DWORD number of segments per edge when drawing patches, nsp (D3DRS_PATCHSEGMENTS exists in Direct3D 8, but not in 9)
    /* TODO -oDxbx : Is X_D3DRS_SWAPFILTER really a xtD3DMULTISAMPLE_TYPE? */          //
    /* 126 */ { 4034, 0000 /*, XREF_NAME(D3DRS_SwapFilter) */ },                       // nsp. Verified absent in 3944, present in 4034.  4034 state based on test-case : The Simpsons Road Rage
    /* 127 */ { 4627, 0000 /*, XREF_NAME(D3DRS_PresentationInterval) */ },             // nsp. Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 128 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused8) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 129 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused7) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 130 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused6) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 131 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused5) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 132 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused4) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 133 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused3) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 134 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused2) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 135 */ { 4627, 0000 /*, XREF_NAME(D3DRS_Deferred_Unused1) */ },                 // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* End of "deferred" render states, continuing with "complex" render states: */    //
    /* 136 */ { 3424, 0000, XREF_NAME(D3DRS_PSTextureModes) },                         // This is where pPSDef->PSTextureModes is stored (outside the pPSDEF - see DxbxUpdateActivePixelShader)
    /* 137 */ { 3424, 0000 /*, XREF_NAME(D3DRS_VertexBlend) */ },                      //
    /* 138 */ { 3424, 0000 /*, XREF_NAME(D3DRS_FogColor) */ },                         // SwapRgb
    /* 139 */ { 3424, 0000, XREF_NAME(D3DRS_FillMode) },                               //
    /* 140 */ { 3424, 0000, XREF_NAME(D3DRS_BackFillMode) },                           // nsp.
    /* 141 */ { 3424, 0000, XREF_NAME(D3DRS_TwoSidedLighting) },                       // nsp.  // FIXME map from NV2A_LIGHT_MODEL
    /* 142 */ { 3424, 0000 /*, XREF_NAME(D3DRS_NormalizeNormals) */ },                 //
    /* 143 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ZEnable) */ },                          // D3DZBUFFERTYPE?
    /* 144 */ { 3424, 0000, XREF_NAME(D3DRS_StencilEnable) },                          //
    /* 145 */ { 3424, 0000, XREF_NAME(D3DRS_StencilFail) },                            //
    /* 146 */ { 3424, 0000, XREF_NAME(D3DRS_FrontFace) },                              // nsp.
    /* 147 */ { 3424, 0000, XREF_NAME(D3DRS_CullMode) },                               //
    /* 148 */ { 3424, 0000 /*, XREF_NAME(D3DRS_TextureFactor) */ },                    //
    /* 149 */ { 3424, 0000, XREF_NAME(D3DRS_ZBias) },                                  // Was D3DRS_ZBIAS
    /* 150 */ { 3424, 0000, XREF_NAME(D3DRS_LogicOp) },                                // nsp.
    /* 151 */ { 3424, 0000 /*, XREF_NAME(D3DRS_EdgeAntiAlias) */ },                    // Was D3DRS_EDGEANTIALIAS. Dxbx note : No Xbox ext. (according to Direct3D8) !
    /* 152 */ { 3424, 0000, XREF_NAME(D3DRS_MultiSampleAntiAlias) },                   //
    /* 153 */ { 3424, 0000, XREF_NAME(D3DRS_MultiSampleMask) },                        //
    /* 154 */ { 3424, 4034, XREF_NAME(D3DRS_MultiSampleType) },                        // Verified present in 3944, removed in 4034. 4034 state based on test-case : The Simpsons Road Rage
    /* 155 */ { 4034, 0000, XREF_NAME(D3DRS_MultiSampleMode) },                        // D3DMULTISAMPLEMODE for the backbuffer. Verified absent in 3944, present in 4034.  4034 state based on test-case : The Simpsons Road Rage
    /* 156 */ { 4034, 0000, XREF_NAME(D3DRS_MultiSampleRenderTargetMode) },            // Verified absent in 3944, present in 4034. Presence in 4034 is based on test-case : The Simpsons Road Rage
    /* 157 */ { 3424, 0000 /*, XREF_NAME(D3DRS_ShadowFunc) */ },                       //
    /* 158 */ { 3424, 0000 /*, XREF_NAME(D3DRS_LineWidth) */ },                        //
    /* 159 */ { 4627, 0000, XREF_NAME(D3DRS_SampleAlpha) },                            // Verified absent in 4531, present in 4627  TODO: might be introduced in between?
    /* 160 */ { 3424, 0000, XREF_NAME(D3DRS_Dxt1NoiseEnable) },                        //
    /* 161 */ { 3911, 0000, XREF_NAME(D3DRS_YuvEnable) },                              // Verified present in 3944
    /* 162 */ { 3911, 0000, XREF_NAME(D3DRS_OcclusionCullEnable) },                    // Verified present in 3944
    /* 163 */ { 3911, 0000, XREF_NAME(D3DRS_StencilCullEnable) },                      // Verified present in 3944
    /* 164 */ { 3911, 0000, XREF_NAME(D3DRS_RopZCmpAlwaysRead) },                      // Verified present in 3944
    /* 165 */ { 3911, 0000, XREF_NAME(D3DRS_RopZRead) },                               // Verified present in 3944
    /* 166 */ { 3911, 0000, XREF_NAME(D3DRS_DoNotCullUncompressed) },                  // Verified present in 3944
};
static_assert(XBSDB_ARRAY_SIZE(DxbxRenderStateInfo) == 167, "DxbxRenderStateInfo is not at correct array size!");

static const size_t DxbxRenderStateInfoSize = XBSDB_ARRAY_SIZE(DxbxRenderStateInfo);

static bool IsRenderStateAvailableInCurrentXboxD3D8Lib(RenderStateRevision aRenderStateInfo,
                                                       uint16_t library_version)
{
    bool bIsRenderStateAvailable = (aRenderStateInfo.version <= library_version);
    if (aRenderStateInfo.removed > 0) { // Applies to xbox::X_D3DRS_MULTISAMPLETYPE
        // Note : X_D3DRS_MULTISAMPLETYPE seems the only render state that got
        // removed (from 4039 onwards), so we check that limitation here as well
        bIsRenderStateAvailable &= (library_version < aRenderStateInfo.removed);
    }
    return bIsRenderStateAvailable;
}

static int GetRenderStateOffsetByXRef(uint16_t xref,
                                      uint16_t library_version)
{
    int offset = 0;
    for (size_t i = 0; i < DxbxRenderStateInfoSize; i++) {
        if (DxbxRenderStateInfo[i].xref == xref) {
            return offset;
        }
        if (IsRenderStateAvailableInCurrentXboxD3D8Lib(DxbxRenderStateInfo[i], library_version)) {
            offset++;
        }
    }
    return -1;
}

static void manual_scan_section_dx8_VerifyRenderStateOffsets(XbSDBiContext* pContext,
                                                             const XbSDBiLibrarySession* pLibrarySession)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // Perform basic check up on:
    // * Deferred offset
    // * Complex offset
    // Verify D3D_g_RenderState is set.
    xbaddr g_RenderState = pContext->xref_database[XREF_D3D_g_RenderState];
    if (XbSDBi_IsXRefAddrUnset(g_RenderState)) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "D3D_g_RenderState is not set!");
        return;
    }

    // Verify D3D_g_DeferredRenderState is set.
    xbaddr g_DeferredRenderState = pContext->xref_database[XREF_D3D_g_DeferredRenderState];
    if (XbSDBi_IsXRefAddrUnset(g_DeferredRenderState)) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "D3D_g_DeferredRenderState is not set!");
        return;
    }
    // Verify deferred offset is correct
    int RenderStateOffset = GetRenderStateOffsetByXRef(XREF_D3DRS_FogEnable, pLibrary->build_version);
    if (RenderStateOffset == -1) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Could not find D3DRS_FogEnable offset from DxbxRenderStateInfo list!");
        return;
    }
    if (RenderStateOffset * sizeof(xbaddr) != g_DeferredRenderState - g_RenderState) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "DxbxRenderStateInfo list's entry base on g_DeferredRenderState is inaccurate!");
    }

    // Verify D3D_g_ComplexRenderState is set.
    xbaddr g_ComplexRenderState = pContext->xref_database[XREF_D3D_g_ComplexRenderState];
    if (XbSDBi_IsXRefAddrUnset(g_ComplexRenderState)) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "D3D_g_ComplexRenderState is not set!");
        return;
    }
    // Verify complex offset is correct
    RenderStateOffset = GetRenderStateOffsetByXRef(XREF_D3DRS_PSTextureModes, pLibrary->build_version);
    if (RenderStateOffset == -1) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Could not find D3DRS_PSTextureModes offset from DxbxRenderStateInfo list!");
        return;
    }
    if (RenderStateOffset * sizeof(xbaddr) != g_ComplexRenderState - g_RenderState) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "DxbxRenderStateInfo list's entry base on g_ComplexRenderState is inaccurate!");
    }

    // Now we want to inspect each entries to be sure they are properly offset from DxbxRenderStateInfo list inspection.
    // If an offset is inaccurate, we want to know ASAP!
    unsigned RenderState_iLib = 0;
    char buffer_str[512];
    for (size_t i = 0; i < DxbxRenderStateInfoSize; i++) {
        if (IsRenderStateAvailableInCurrentXboxD3D8Lib(DxbxRenderStateInfo[i], pLibrary->build_version)) {
            if (DxbxRenderStateInfo[i].xref) {
                xbaddr RenderState_iAddr = pContext->xref_database[DxbxRenderStateInfo[i].xref];
                if (XbSDBi_IsXRefAddrUnset(RenderState_iAddr)) {
                    if (RenderState_iAddr != XREF_ADDR_DERIVE) {
                        snprintf(buffer_str, XBSDB_ARRAY_SIZE(buffer_str), "XbSymbolDatabase's %s symbol is not set!", DxbxRenderStateInfo[i].name);
                        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, buffer_str);
                    }
                    else {
                        snprintf(buffer_str, XBSDB_ARRAY_SIZE(buffer_str), "XbSymbolDatabase's %s symbol is currently set to derive.", DxbxRenderStateInfo[i].name);
                        output_message(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, buffer_str);
                    }
                }
                else if (RenderState_iLib * sizeof(xbaddr) != RenderState_iAddr - g_RenderState) {
                    snprintf(buffer_str, XBSDB_ARRAY_SIZE(buffer_str), "DxbxRenderStateInfo list's entry base on %s is inaccurate!", DxbxRenderStateInfo[i].name);
                    output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, buffer_str);
                }
            }
            RenderState_iLib++;
        }
    }

    output_message(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Verify RenderState offsets is complete.");
}

static bool manual_scan_section_dx8_register_D3DRS_vars(XbSDBiContext* pContext,
                                                        const XbSDBiLibrarySession* pLibrarySession,
                                                        SymbolDatabaseList* pLibraryDB,
                                                        const XbSDBSection* pSection)
{
    // Instead of individual register call, let's go through the list to automatically register valid xrefs.
    const uint16_t lib_version = pLibrarySession->pLibrary->build_version;
    unsigned RenderState_iLib = 0;
    char buffer_str[512];
    for (size_t i = 0; i < DxbxRenderStateInfoSize; i++) {
        const RenderStateRevision render_state_i = DxbxRenderStateInfo[i];
        if (IsRenderStateAvailableInCurrentXboxD3D8Lib(render_state_i, lib_version)) {
            if (DxbxRenderStateInfo[i].xref) {
                xbaddr RenderState_iAddr = pContext->xref_database[DxbxRenderStateInfo[i].xref];
                // Check if D3DRS_ prefix variables are set.
                if (XbSDBi_IsXRefAddrUnset(RenderState_iAddr)) {
                    if (RenderState_iAddr != XREF_ADDR_DERIVE) {
                        // If it is not derive address, then let's calculate base on DxbxRenderStateInfo table for accuracy.
                        XbSDBi_SetXRefDatabase(pContext,
                                               pLibrarySession->iLibraryType,
                                               DxbxRenderStateInfo[i].xref,
                                               pContext->xref_database[XREF_D3D_g_RenderState] + RenderState_iLib * sizeof(xbaddr));
                        snprintf(buffer_str, XBSDB_ARRAY_SIZE(buffer_str), "%s symbol address is manually set to D3D_g_RenderState + %zd * %u.", DxbxRenderStateInfo[i].name, sizeof(xbaddr), RenderState_iLib);
                        output_message(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, buffer_str);
                    }
                }
                XbSDBi_RegisterValidXRefAddr(pContext, LIB_D3D8, XBSDBLIB_D3D8, render_state_i.xref, render_state_i.version, render_state_i.name, symbol_variable, call_none, 0, NULL);
            }
            RenderState_iLib++;
        }
    }

    // Manual register RenderState sections.
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_D3D8, XBSDBLIB_D3D8, XREF_D3D_g_RenderState, 0, "D3D_g_RenderState", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_D3D8, XBSDBLIB_D3D8, XREF_D3D_g_ComplexRenderState, 0, "D3D_g_ComplexRenderState", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_D3D8, XBSDBLIB_D3D8, XREF_D3D_g_DeferredRenderState, 0, "D3D_g_DeferredRenderState", symbol_variable, call_none, 0, NULL);

    return true;
}

// No dependency requirement
static bool manual_scan_section_dx8_register_D3DRS(XbSDBiContext* pContext,
                                                   const XbSDBiLibrarySession* pLibrarySession,
                                                   SymbolDatabaseList* pLibraryDB,
                                                   const XbSDBSection* pSection)
{
    // First, we need to find D3DDevice_SetRenderState_Simple symbol.
    xbaddr D3DDevice_SetRenderState_Simple = pContext->xref_database[XREF_D3DDevice_SetRenderState_Simple];
    if (XbSDBi_IsXRefAddrUnset(D3DDevice_SetRenderState_Simple)) {
        xbaddr xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                          pLibrarySession,
                                                                                          pLibraryDB,
                                                                                          pSection,
                                                                                          XREF_D3DDevice_SetRenderState_Simple,
                                                                                          DB_ST_MANUAL,
                                                                                          FIRSTPASS_YES,
                                                                                          REGISTER_YES,
                                                                                          NULL,
                                                                                          NULL);
        // If not found, skip the rest of the scan.
        if (xSymbolAddr == 0) {
            return false;
        }
    }

    memptr_t pD3D_g_DeferredRenderStateOffset = 0;

    // Then look up for D3D_g_RenderState
    xbaddr D3D_g_RenderState = pContext->xref_database[XREF_D3D_g_RenderState];
    if (XbSDBi_IsXRefAddrUnset(D3D_g_RenderState)) {
        // Below xref is used to obtain from D3DDevice_SetRenderState(Not)Inline signatures.
        pContext->xref_database[XREF_D3D_g_RenderState] = XREF_ADDR_DERIVE;
        xbaddr xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                          pLibrarySession,
                                                                                          pLibraryDB,
                                                                                          pSection,
                                                                                          XREF_D3DDevice_SetRenderStateNotInline,
                                                                                          DB_ST_MANUAL,
                                                                                          FIRSTPASS_YES,
                                                                                          REGISTER_YES,
                                                                                          NULL,
                                                                                          NULL);
        if (xSymbolAddr == 0) {
            // If not found, then check if library is not LTCG.
            if (pLibrarySession->pLibrary->flag == XBSDBLIB_D3D8) {
                pContext->xref_database[XREF_D3D_g_RenderState] = XREF_ADDR_UNDETERMINED;
                return false;
            }
            // Otherwise, let's look up for D3DDevice_SetRenderStateInline__GenericFragment which is NOT a symbol.
            xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                       pLibrarySession,
                                                                                       pLibraryDB,
                                                                                       pSection,
                                                                                       XREF_D3DDevice_SetRenderStateInline__GenericFragment,
                                                                                       DB_ST_MANUAL,
                                                                                       FIRSTPASS_YES,
                                                                                       REGISTER_NO,
                                                                                       NULL,
                                                                                       NULL);

            // If not found, skip the rest of the scan.
            if (xSymbolAddr == 0) {
                pContext->xref_database[XREF_D3D_g_RenderState] = XREF_ADDR_UNDETERMINED;
                return false;
            }
            // pointer to cmp opcode's value from D3DDevice_SetRenderStateInline__GenericFragment sig.
            pD3D_g_DeferredRenderStateOffset = XbSDBi_section_VirtToHostAddress(pContext, xSymbolAddr + 0x02);

            // If it is found, don't register it.
        }
        else {
            // pointer to cmp opcode's value from D3DDevice_SetRenderStateNotInline sig.
            pD3D_g_DeferredRenderStateOffset = XbSDBi_section_VirtToHostAddress(pContext, xSymbolAddr + 0x07);

            // Self register only D3DDevice_SetRenderStateNotInline symbol function.
            // NOTE: D3DDevice_SetRenderStateInline__GenericFragment is NOT a symbol but a generic method to find D3D_g_RenderState.
        }
        // D3D_g_RenderState variable is already set internal, will be register later.


        // And set D3D_g_DeferredRenderState, including D3DRS_FogEnable, variables base on signature cmp opcode's value as offset.
        // This is 100% accurate method than manual offset usage.
        if (pD3D_g_DeferredRenderStateOffset) {
            uint8_t D3D_g_DeferredRenderStateOffset = *(uint8_t*)pD3D_g_DeferredRenderStateOffset;
            XbSDBi_SetXRefDatabase(pContext,
                                   pLibrarySession->iLibraryType,
                                   XREF_D3D_g_DeferredRenderState,
                                   pContext->xref_database[XREF_D3D_g_RenderState] + D3D_g_DeferredRenderStateOffset * 4);

            XbSDBi_SetXRefDatabase(pContext,
                                   pLibrarySession->iLibraryType,
                                   XREF_D3DRS_FogEnable,
                                   pContext->xref_database[XREF_D3D_g_DeferredRenderState]);
        }
    }
    return true;
}

// No dependency requirement
static bool manual_scan_section_dx8_register_D3DCRS(XbSDBiContext* pContext,
                                                    const XbSDBiLibrarySession* pLibrarySession,
                                                    SymbolDatabaseList* pLibraryDB,
                                                    const XbSDBSection* pSection)
{
    // First, we need to find D3DRS_FillMode symbol.
    xbaddr D3DRS_FillMode = pContext->xref_database[XREF_D3DRS_FillMode];
    if (XbSDBi_IsXRefAddrUnset(D3DRS_FillMode)) {
        // These xrefs are used to obtain from D3DDevice_SetRenderState_FillMode signature.
        pContext->xref_database[XREF_D3DRS_FillMode] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_BackFillMode] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_TwoSidedLighting] = XREF_ADDR_DERIVE;
        xbaddr xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                          pLibrarySession,
                                                                                          pLibraryDB,
                                                                                          pSection,
                                                                                          XREF_D3DDevice_SetRenderState_FillMode,
                                                                                          DB_ST_MANUAL,
                                                                                          FIRSTPASS_NO,
                                                                                          REGISTER_YES,
                                                                                          NULL,
                                                                                          NULL);
        // If not found, skip the rest of the scan.
        if (xSymbolAddr == 0) {
            pContext->xref_database[XREF_D3DRS_FillMode] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_BackFillMode] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_TwoSidedLighting] = XREF_ADDR_UNDETERMINED;
            return false;
        }
    }

    // Derived D3DRS_FillMode, D3DRS_BackFillMode, and D3DRS_TwoSidedLighting variables are already set.

    // Set D3D_g_ComplexRenderState variable
    // Had been reverse engineered and verified across compiled XDK builds from retail titles.
    pContext->xref_database[XREF_D3D_g_ComplexRenderState] = pContext->xref_database[XREF_D3DRS_FillMode] - 3 /*index*/ * sizeof(xbaddr);

    // Set D3DRS_PSTextureModes variable which reside in same address as D3D_g_ComplexRenderState is at.
    pContext->xref_database[XREF_D3DRS_PSTextureModes] = pContext->xref_database[XREF_D3D_g_ComplexRenderState];

    return true;
}

// No dependency requirement
static bool manual_scan_section_dx8_register_D3DRS_end_of_list(XbSDBiContext* pContext,
                                                               const XbSDBiLibrarySession* pLibrarySession,
                                                               SymbolDatabaseList* pLibraryDB,
                                                               const XbSDBSection* pSection)
{
    // First, we need to find D3DRS_DoNotCullUncompressed symbol.
    xbaddr D3DRS_DoNotCullUncompressed = pContext->xref_database[XREF_D3DRS_DoNotCullUncompressed];
    if (XbSDBi_IsXRefAddrUnset(D3DRS_DoNotCullUncompressed)) {
        // These xrefs are used to obtain from D3D_CommonSetDebugRegisters signature.
        pContext->xref_database[XREF_D3D_g_pDevice] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_RopZCmpAlwaysRead] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_RopZRead] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_DoNotCullUncompressed] = XREF_ADDR_DERIVE;
        xbaddr xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                          pLibrarySession,
                                                                                          pLibraryDB,
                                                                                          pSection,
                                                                                          XREF_D3D_CommonSetDebugRegisters,
                                                                                          DB_ST_MANUAL,
                                                                                          FIRSTPASS_NO,
                                                                                          REGISTER_YES,
                                                                                          NULL,
                                                                                          NULL);
        // If not found, skip the rest of the scan.
        if (xSymbolAddr == 0) {
            pContext->xref_database[XREF_D3D_g_pDevice] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_RopZCmpAlwaysRead] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_RopZRead] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_DoNotCullUncompressed] = XREF_ADDR_UNDETERMINED;
            return false;
        }

        OOVPATable* pSymbolEntry = NULL;
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3D_g_pDevice);
        XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 0);
#if 0 // TODO: Fix this after #208 pull request is merged.
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3DRS_RopZCmpAlwaysRead);
        XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 0);
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3DRS_RopZRead);
        XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 0);
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3DRS_DoNotCullUncompressed);
        XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 0);
#endif
    }
    return true;
}

// No dependency requirement
static bool manual_scan_section_dx8_register_D3DRS_Stencils_and_Occlusion(XbSDBiContext* pContext,
                                                                          const XbSDBiLibrarySession* pLibrarySession,
                                                                          SymbolDatabaseList* pLibraryDB,
                                                                          const XbSDBSection* pSection)
{
    // First, we need to find D3DRS_StencilEnable symbol.
    xbaddr D3DRS_StencilEnable = pContext->xref_database[XREF_D3DRS_StencilEnable];
    if (XbSDBi_IsXRefAddrUnset(D3DRS_StencilEnable)) {
        // These xrefs are used to obtain from D3DRS_Stencils_and_Occlusion__GenericFragment signature.
        pContext->xref_database[XREF_D3DRS_StencilEnable] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_StencilFail] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_OcclusionCullEnable] = XREF_ADDR_DERIVE;
        pContext->xref_database[XREF_D3DRS_StencilCullEnable] = XREF_ADDR_DERIVE;
        xbaddr xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                          pLibrarySession,
                                                                                          pLibraryDB,
                                                                                          pSection,
                                                                                          XREF_D3DRS_Stencils_and_Occlusion__GenericFragment,
                                                                                          DB_ST_MANUAL,
                                                                                          FIRSTPASS_NO,
                                                                                          REGISTER_NO,
                                                                                          NULL,
                                                                                          NULL);
        // If not found, skip the rest of the scan.
        if (xSymbolAddr == 0) {
            pContext->xref_database[XREF_D3DRS_StencilEnable] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_StencilFail] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_OcclusionCullEnable] = XREF_ADDR_UNDETERMINED;
            pContext->xref_database[XREF_D3DRS_StencilCullEnable] = XREF_ADDR_UNDETERMINED;
            return false;
        }

        // If found, then above xrefs will be set internally.
    }
    return true;
}

static void manual_scan_section_dx8_register_D3DTSS(XbSDBiContext* pContext,
                                                    const XbSDBiLibrarySession* pLibrarySession)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    xbaddr DerivedAddr_D3DTSS_TEXCOORDINDEX = pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX];
    int Decrement = 0x70; // TODO : Rename into something understandable

    //XbSDBi_SetXRefDatabase(pContext, iLibraryType, XREF_D3DTSS_BUMPENV, DerivedAddr_D3DTSS_TEXCOORDINDEX - 28 * 4);
    //XbSDBi_SetXRefDatabase(pContext, iLibraryType, XREF_D3DTSS_TEXCOORDINDEX, DerivedAddr_D3DTSS_TEXCOORDINDEX); // Already been set.
    //XbSDBi_SetXRefDatabase(pContext, iLibraryType, XREF_D3DTSS_BORDERCOLOR, DerivedAddr_D3DTSS_TEXCOORDINDEX + 1 * 4);
    //XbSDBi_SetXRefDatabase(pContext, iLibraryType, XREF_D3DTSS_COLORKEYCOLOR, DerivedAddr_D3DTSS_TEXCOORDINDEX + 2 * 4);

    uint32_t EmuD3DDeferredTextureState = DerivedAddr_D3DTSS_TEXCOORDINDEX - Decrement;

    XbSDBi_RegisterXRef(pContext, pLibrarySession, XREF_D3D_g_DeferredTextureState, 0, "D3D_g_DeferredTextureState", EmuD3DDeferredTextureState, symbol_variable, call_none, 0, NULL, true);
}

// Has dependency on D3D_g_pDevice xref.
static bool manual_scan_section_dx8_register_callbacks(XbSDBiContext* pContext,
                                                       const XbSDBiLibrarySession* pLibrarySession,
                                                       SymbolDatabaseList* pLibraryDB,
                                                       const XbSDBSection* pSection)
{
    // Generic usage
    memptr_t pFunc = 0;
    xbaddr xSymbolAddr = 0;
    // Manual check require for able to self-register these symbols:
    // * D3DDevice_SetSwapCallback
    // * D3DDevice_SetVerticalBlankCallback

    // First, check if D3D_g_pDevice is found.
    if (pContext->xref_database[XREF_D3D_g_pDevice] != XREF_ADDR_DERIVE &&
        // Then, check at least one of symbol's member variable is not found.
        pContext->xref_database[XREF_D3DDevice__m_SwapCallback_OFFSET] == XREF_ADDR_UNDETERMINED) {

        // Scan if event handle variable is not yet derived.
        if (pContext->xref_database[XREF_D3DDevice__m_VerticalBlankEvent_OFFSET] == XREF_ADDR_DERIVE) {
            xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                       pLibrarySession,
                                                                                       pLibraryDB,
                                                                                       pSection,
                                                                                       XREF_D3DDevice__m_VerticalBlankEvent__GenericFragment,
                                                                                       DB_ST_MANUAL,
                                                                                       FIRSTPASS_YES,
                                                                                       REGISTER_NO,
                                                                                       NULL,
                                                                                       NULL);
        }

        // We are not registering D3DDevice__m_VerticalBlankEvent__GenericFragment itself, as it is NOT a symbol.


        // If not found, skip manual register.
        if (pContext->xref_database[XREF_D3DDevice__m_VerticalBlankEvent_OFFSET] == XREF_ADDR_DERIVE) {
            return false;
        }

        // Finally, manual register the symbol variables.
        OOVPATable* pSymbolEntry = NULL;
        xSymbolAddr = pContext->xref_database[XREF_D3DDevice__m_VerticalBlankEvent_OFFSET];
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3DDevice__m_VerticalBlankEvent_OFFSET);
        XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 0);
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3DDevice__m_SwapCallback_OFFSET);
        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 0, xSymbolAddr - 8);
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, D3DDevice__m_VBlankCallback_OFFSET);
        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 0, xSymbolAddr - 4);
    }
    // If D3D_g_pDevice is not found, the scan is not complete
    // and will continue scan to next given section.
    else {
        return false;
    }

    return true;
}

static bool manual_scan_section_dx8(XbSDBiContext* pContext,
                                    const XbSDBiLibrarySession* pLibrarySession,
                                    SymbolDatabaseList* pLibraryDB,
                                    const XbSDBSection* pSection)
{
    // Generic usage
    memptr_t pSymbolAddr = 0;
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // We need to mask boolean from each function's scan process if any return false.
    // Needed for no dependency, scanning multiple sections, and library's databases.
    bool bComplete = true;

    // Get end of D3D_g_RenderState list by D3DRS_DoNotCullUncompressed variable
    bComplete &= manual_scan_section_dx8_register_D3DRS_end_of_list(pContext, pLibrarySession, pLibraryDB, pSection);

    // Get D3D_g_RenderState and D3D_g_DeferredRenderState variables
    bComplete &= manual_scan_section_dx8_register_D3DRS(pContext, pLibrarySession, pLibraryDB, pSection);

    // Get D3D_g_ComplexRenderState, D3DRS_FillMode, and D3DRS_PSTextureModes variables
    bComplete &= manual_scan_section_dx8_register_D3DCRS(pContext, pLibrarySession, pLibraryDB, pSection);

    // Get D3DRS_OcclusionCullEnable, D3DRS_StencilCullEnable, D3DRS_StencilEnable, and D3DRS_StencilFail variables
    bComplete &= manual_scan_section_dx8_register_D3DRS_Stencils_and_Occlusion(pContext, pLibrarySession, pLibraryDB, pSection);

    // Check if any results as incomplete scan.
    if (!bComplete) {
        return bComplete;
    }

    bComplete = manual_scan_section_dx8_register_D3DRS_vars(pContext, pLibrarySession, pLibraryDB, pSection);

    if (bComplete) {
        manual_scan_section_dx8_VerifyRenderStateOffsets(pContext, pLibrarySession);
    }
    if (!bComplete) {
        return bComplete;
    }

    if (pLibrary->build_version < 3911) {
        // Not supported, currently ignored.
        return true;
    }

    // then locate D3DDeferredTextureState
    OOVPATable* pSymbolEntry = NULL;
    OOVPARevision* pSymbolEntryRevision = NULL;
    pSymbolAddr = XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                            pLibrarySession,
                                                            pLibraryDB,
                                                            pSection,
                                                            XREF_D3DDevice_SetTextureState_TexCoordIndex, DB_ST_MANUAL,
                                                            FIRSTPASS_YES,
                                                            REGISTER_YES,
                                                            &pSymbolEntry,
                                                            &pSymbolEntryRevision);

    if (pSymbolAddr != 0) {
        // Self register D3DDevice_SetTextureState_TexCoordIndex

        manual_scan_section_dx8_register_D3DTSS(pContext, pLibrarySession);
    }

    pSymbolEntry = NULL;
    pSymbolEntryRevision = NULL;
    pSymbolAddr = XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                            pLibrarySession,
                                                            pLibraryDB,
                                                            pSection,
                                                            XREF_D3DDevice_SetStreamSource,
                                                            DB_ST_MANUAL,
                                                            FIRSTPASS_YES,
                                                            REGISTER_YES,
                                                            &pSymbolEntry,
                                                            &pSymbolEntryRevision);

    if (pSymbolAddr != 0) {
        // Self register D3DDevice_SetStreamSource

        xbaddr D3D_g_Stream = pContext->xref_database[XREF_D3D_g_Stream];
        xbaddr D3D_g_Stream_i_pVertexBuffer = pContext->xref_database[XREF_D3D_g_Stream_i_pVertexBuffer];

        // Verify both variables are offset correctly.
        if (D3D_g_Stream_i_pVertexBuffer - D3D_g_Stream != 8) {
            // If not correct, then do the correction in case of third-party rely on this.
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "D3D_g_Stream_i_pVertexBuffer (0x%08X) - D3D_g_Stream (0x%08X) != 0x8", D3D_g_Stream_i_pVertexBuffer, D3D_g_Stream);
            pContext->xref_database[XREF_D3D_g_Stream] = D3D_g_Stream_i_pVertexBuffer - 8;
        }

        // TODO: Use XbSDBi_FindByReferenceHelper to get OOVPA revision. Or better yet, do self register.
        XbSDBi_RegisterValidXRefAddr(pContext, pLibrary->name, pLibrary->flag, XREF_D3D_g_Stream, 0, "D3D_g_Stream", symbol_variable, call_none, 0, NULL);
    }

    bComplete = manual_scan_section_dx8_register_callbacks(pContext, pLibrarySession, pLibraryDB, pSection);

    return bComplete;
}

static inline void manual_register_d3d8__ltcg(XbSDBiContext* pContext)
{
    // TODO: Require to be here until self register functionality is implement.
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_D3D8, XBSDBLIB_D3D8, XREF_D3DDevice__m_VertexShader_OFFSET, 0, "D3DDevice__m_VertexShader_OFFSET", symbol_variable, call_none, 0, NULL);
    // NOTE: D3DDevice__m_PixelShader_OFFSET is not accessible to the user.
}
