// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * Direct3D_CreateDevice
// ******************************************************************
//85C9750AC705 ...C21000
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice_16__LTCG_eax4_ecx6,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x0A, 0x85 },
    { 0x0B, 0xC9 },
    { 0x0C, 0x75 },
    { 0x0D, 0x0A },
    { 0x0E, 0xC7 },
    { 0x0F, 0x05 },

    { 0x3A, 0x18 },
    //
);

// ******************************************************************
// * D3DTexture_GetLevelDesc
// ******************************************************************
// * NOTE: We are actually intercepting Get2DSurfaceDesc, because
// *       GetLevelDesc Simply redirects to that function
// ******************************************************************
//7909C74608010000 ...C20400
OOVPA_SIG_HEADER_NO_XREF(Get2DSurfaceDesc_4__LTCG_edi1_esi3,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x0F },
    { 0x01, 0xB6 },

    { 0x2F, 0x79 },
    { 0x30, 0x09 },
    { 0x31, 0xC7 },
    { 0x32, 0x46 },
    { 0x33, 0x08 },
    { 0x34, 0x01 },
    { 0x35, 0x00 },
    { 0x36, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZBias
// ******************************************************************
// List of titles found:
// - (4627) Aggressive Inline
// - (5028) BMX XXX
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZBias,
                         1060)
OOVPA_SIG_MATCH(
    // push ecx
    // push ebx // non-LTCG titles does not have this instruction
    // push ebp // most LTCG titles does not have this instruction
    // push esi
    OV_MATCH(0x00, 0x51, 0x53, 0x55, 0x56),

    // setnz al
    OV_MATCH(0x0D, 0x0F, 0x95, 0xC0),

    // fild [esp + param_1]
    OV_MATCH(0x16, 0xDB, 0x44, 0x24, 0x18),

    // jge +0x06
    OV_MATCH(0x1C, 0x7D, 0x06),
    // fadd [0x????????]
    OV_MATCH(0x1E, 0xD8, 0x05),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleAntiAlias
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleAntiAlias,
                      1060,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // mov [D3DRS_MultiSampleAntiAlias],eax
    XREF_ENTRY(0x0D, XREF_D3DRS_MultiSampleAntiAlias),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B, 0x35),

    // mov [D3DRS_MultiSampleAntiAlias],eax
    OV_MATCH(0x0C, 0xA3), // 4627 (non-LTCG) 0x0E vs 0x0C
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleMask
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleMask,
                      1060,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // mov [D3DRS_MultiSampleMask],eax
    XREF_ENTRY(0x0C, XREF_D3DRS_MultiSampleMask),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov edi,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B, 0x3D),

    // mov [D3DRS_MultiSampleMask],eax
    OV_MATCH(0x0B, 0xA3), // 4627 (non-LTCG) 0x0A vs 0x0B
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_SampleAlpha
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_SampleAlpha,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // mov [D3DRS_SampleAlpha],eax
    XREF_ENTRY(0x0C, XREF_D3DRS_SampleAlpha),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B),

    // mov [D3DRS_SampleAlpha],eax
    OV_MATCH(0x0B, 0xA3),
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//088BD1C1E20681C2241B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x1F, 0x08 },
    { 0x20, 0x8B },
    { 0x21, 0xD1 },
    { 0x22, 0xC1 },
    { 0x23, 0xE2 },
    { 0x24, 0x06 },
    { 0x25, 0x81 },
    { 0x26, 0xC2 },
    { 0x27, 0x24 },
    { 0x28, 0x1B },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BumpEnv
// ******************************************************************
//8d5e01f6c303
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BumpEnv,
                         1024)
OOVPA_SIG_MATCH(

    { 0x02, 0x56 },

    { 0x1A, 0x8D },
    { 0x1B, 0x5E },
    { 0x1C, 0x01 },
    { 0x1D, 0xF6 },
    { 0x1E, 0xC3 },
    { 0x1F, 0x03 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//c1e0078998
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex,
                      1958,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x53 },
    { 0x08, 0x35 },

    { 0x14, 0xC1 },
    { 0x15, 0xE0 },
    { 0x16, 0x07 },
    { 0x17, 0x89 },
    { 0x18, 0x98 },

    { 0x1D, 0x8B },
    { 0x1E, 0x06 },
    { 0x1F, 0x8B },
    //
);

// ******************************************************************
// * D3D_CommonSetRenderTarget
// ******************************************************************
//83FD0C742683FD0D7E
OOVPA_SIG_HEADER_NO_XREF(D3D_CommonSetRenderTarget,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x40, 0x83 },
    { 0x41, 0xFD },
    { 0x42, 0x0C },
    { 0x43, 0x74 },
    { 0x44, 0x26 },
    { 0x45, 0x83 },
    { 0x46, 0xFD },
    { 0x47, 0x0D },
    { 0x48, 0x7E },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//C700B402040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x88, 0xC7 },
    { 0x89, 0x00 },
    { 0x8A, 0xB4 },
    { 0x8B, 0x02 },
    { 0x8C, 0x04 },
    { 0x8D, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
//81C10000F8FF89
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTexture,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x28, 0x81 },
    { 0x29, 0xC1 },
    { 0x2A, 0x00 },
    { 0x2B, 0x00 },
    { 0x2C, 0xF8 },
    { 0x2D, 0xFF },
    { 0x2E, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
// Test case:
// DDS9 (4928)
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         4627)
OOVPA_SIG_MATCH(
    // sub esp, 0x___ (always 0x194)
    OV_MATCH(0x00, 0x81, 0xEC),

    // mov esi, [esp + param_1]
    OV_MATCH(0x09, 0x8B, 0xB4, 0x24),
    // movzx edx, [esi + 0x0D]
    OV_MATCH(0x10, 0x0F, 0xB6, 0x56, 0x0D),
    // mov bl, [edx + 0x____]
    OV_MATCH(0x14, 0x8A, 0x9A),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
// TODO: May could be lower down to 3911 as the 4627+ is very
//       similar to 3911+ assembly instructions structure.
// Test case:
// Rally Fusion : Race Of Champions (4928)
// Enter The Matrix (5344)
// The Italian Job (5344)
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         4628)
OOVPA_SIG_MATCH(
    // mov edx, [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x54, 0x24, 0x04),
    // mov ecx, [edx + 0x10]
    OV_MATCH(0x04, 0x8B, 0x4A, 0x10),
    // sub esp, 0x___ (always 0x194 or 0x34 for 5120 and later)
    // offset 0x07 will have 0x81 for 4627 until 5120 and later has 0x83.
    OV_MATCH(0x08, 0xEC),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);

//******************************************************************
//* D3DDevice_BeginVisibilityTest
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginVisibilityTest,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x56, 0x8B, 0x35),

    // mov [eax],0x000817C8
    OV_MATCH(0x1C, 0xC7, 0x00, 0xC8, 0x17, 0x08, 0x00),
    // mov ecx,1
    OV_MATCH(0x22, 0xB9, 0x01, 0x00),

    // add eax,0x0C
    OV_MATCH(0x2D, 0x83, 0xC0, 0x0C),

    // ret
    OV_MATCH(0x33, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_CreateTexture2
// ******************************************************************
//F744241C0000010074
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x57 },

    { 0x3D, 0xF7 },
    { 0x3E, 0x44 },
    { 0x3F, 0x24 },
    { 0x40, 0x1C },
    { 0x41, 0x00 },
    { 0x42, 0x00 },
    { 0x43, 0x01 },
    { 0x44, 0x00 },
    { 0x45, 0x74 },
    //
);

// ******************************************************************
// * D3DDevice_DeleteStateBlock
// ******************************************************************
//535556578B7C241433ED33DB
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeleteStateBlock,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },
    { 0x02, 0x56 },
    { 0x03, 0x57 },
    { 0x04, 0x8B },
    { 0x05, 0x7C },
    { 0x06, 0x24 },
    { 0x07, 0x14 },
    { 0x08, 0x33 },
    { 0x09, 0xED },
    { 0x0A, 0x33 },
    { 0x0B, 0xDB },
    //
);

// ******************************************************************
// * D3DDevice_EndVisibilityTest
// ******************************************************************
//B80E0007805E
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_EndVisibilityTest,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x10, 0xB8 },
    { 0x11, 0x0E },
    { 0x12, 0x00 },
    { 0x13, 0x07 },
    { 0x14, 0x80 },
    { 0x15, 0x5E },

    { 0x16, 0xC2 },
    { 0x17, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_EndVisibilityTest
// ******************************************************************
//B80E0007805E ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_EndVisibilityTest_0__LTCG_eax1,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0xE8 },

    { 0x0C, 0xB8 },
    { 0x0D, 0x0E },
    { 0x0E, 0x00 },
    { 0x0F, 0x07 },
    { 0x10, 0x80 },
    { 0x11, 0x5E },

    { 0x12, 0xC3 },
    { 0x13, 0x57 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetBackBuffer2,
                      4626, // Due to non-LTCG signature conflict, lowered down by one number.
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e?x,[D3D_g_pDevice]
    XREF_ENTRY(0x09, XREF_D3D_g_pDevice),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // jnz +0x07
    OV_MATCH(0x0D, 0x75, 0x07),
    // mov eax, 0x1
    OV_MATCH(0x0F, 0xB8, 0x01, 0x00 /*, 0x00, 0x00*/),
    // jmp +0x07
    OV_MATCH(0x14, 0xEB, 0x07), // jmp vs push esi non-LTCG 4627
    // neg eax
    OV_MATCH(0x16, 0xF7, 0xD8),
    // sbb eax,eax
    OV_MATCH(0x18, 0x1B, 0xC0),
    // and eax,0x2
    OV_MATCH(0x1A, 0x83, 0xE0, 0x02),

    // Offset 0x1D and later has shifted by one.
);

// ******************************************************************
// * D3DDevice_GetBackBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetBackBuffer2_0__LTCG_eax1,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e?x,[D3D_g_pDevice]
    XREF_ENTRY(0x05, XREF_D3D_g_pDevice),

    // cmp eax,-0x1
    OV_MATCH(0x00, 0x83, 0xF8, 0xFF),

    // jnz +0x07
    OV_MATCH(0x09, 0x75, 0x07),
    // mov eax,0x1
    OV_MATCH(0x0B, 0xB8, 0x01, 0x00, 0x00, 0x00),
    // jmp +0x07
    OV_MATCH(0x10, 0xEB, 0x07),
    // neg e?x
    OV_MATCH(0x12, 0xF7),

    // ret
    OV_MATCH(0x48, 0xC3), // 0x48 vs 5233 0x46 offset
    //
);

// ******************************************************************
// * D3DDevice_GetDepthStencilSurface2
// ******************************************************************
//85F6750433C05EC3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetDepthStencilSurface2,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x0B, 0x00 },
    { 0x0C, 0x85 },
    { 0x0D, 0xF6 },
    { 0x0E, 0x75 },
    { 0x0F, 0x04 },
    { 0x10, 0x33 },
    { 0x11, 0xC0 },
    { 0x12, 0x5E },
    { 0x13, 0xC3 },
    //
);

//******************************************************************
//* D3DDevice_GetDisplayMode
//******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetDisplayMode,
                         1024)
OOVPA_SIG_MATCH(
    //8B90181A0000
    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x90 },
    //{ 0x07, 0x18 },
    //{ 0x08, 0x1A },
    { 0x09, 0x00 },
    { 0x0A, 0x00 },
    { 0x0D, 0x10 },
    { 0x0E, 0x85 },
    { 0x12, 0x8B },
    { 0x13, 0x4A },
    //
);

// ******************************************************************
// * D3DDevice_GetTransform
// ******************************************************************
//56C1E106578B7C24108DB4
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetTransform,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    { 0x09, 0x56 },
    { 0x0A, 0xC1 },
    { 0x0B, 0xE1 },
    { 0x0C, 0x06 },
    { 0x0D, 0x57 },
    { 0x0E, 0x8B },
    { 0x0F, 0x7C },
    { 0x10, 0x24 },
    { 0x11, 0x10 },
    { 0x12, 0x8D },
    { 0x13, 0xB4 },
    //
);

// ******************************************************************
// * D3DDevice_IsBusy
// ******************************************************************
//8B88BC2300008B90
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_IsBusy,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xBC },
    { 0x08, 0x23 },
    { 0x09, 0x00 },
    { 0x0A, 0x00 },
    { 0x0B, 0x8B },
    { 0x0C, 0x90 },
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
//F64401680175
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LightEnable,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x23, 0xF6 },
    { 0x24, 0x44 },
    { 0x25, 0x01 },
    { 0x26, 0x68 },
    { 0x27, 0x01 },
    { 0x28, 0x75 },
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShaderProgram
//******************************************************************
//8B542404530FB75A0255
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShaderProgram,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x54 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x53 },
    { 0x05, 0x0F },
    { 0x06, 0xB7 },
    { 0x07, 0x5A },
    { 0x08, 0x02 },
    { 0x09, 0x55 },
    //
);

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
//85C0740F50FF15
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_PersistDisplay,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x0D, 0x85 },
    { 0x0E, 0xC0 },
    { 0x0F, 0x74 },
    { 0x10, 0x0F },
    { 0x11, 0x50 },
    { 0x12, 0xFF },
    { 0x13, 0x15 },
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x37, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // mov ebx, [esp + param_1]
    OV_MATCH(0x01, 0x8B, 0x5C, 0x24, 0x08),

    // jnz +0x??
    OV_MATCH(0x33, 0x75),

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x36, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_RunVertexStateShader
// ******************************************************************
//C740EC801E1000D9 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunVertexStateShader_4__LTCG_esi2,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x57 },

    { 0x2E, 0xC7 },
    { 0x2F, 0x40 },
    { 0x30, 0xEC },
    { 0x31, 0x80 },
    { 0x32, 0x1E },
    { 0x33, 0x10 },
    { 0x34, 0x00 },
    { 0x35, 0xD9 },
    //
);

// ******************************************************************
// * D3DDevice_SetGammaRamp
// ******************************************************************
//C78498DC07000001000000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetGammaRamp,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x6E, 0xC7 },
    { 0x6F, 0x84 },
    { 0x70, 0x98 },
    { 0x71, 0xDC },
    { 0x72, 0x07 },
    { 0x73, 0x00 },
    { 0x74, 0x00 },
    { 0x75, 0x01 },
    { 0x76, 0x00 },
    { 0x77, 0x00 },
    { 0x78, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x53 },

    { 0x76, 0xC7 },
    { 0x77, 0x40 },
    { 0x78, 0x04 },
    { 0x79, 0x00 },
    { 0x7A, 0x00 },
    { 0x7B, 0x21 },
    { 0x7C, 0x00 },
    { 0x7D, 0x83 },
    { 0x7E, 0xC0 },
    { 0x7F, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader_0__LTCG_eax1,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x85 },

    { 0x72, 0xC7 },
    { 0x73, 0x40 },
    { 0x74, 0x04 },
    { 0x75, 0x00 },
    { 0x76, 0x00 },
    { 0x77, 0x21 },
    { 0x78, 0x00 },
    { 0x79, 0x83 },
    { 0x7A, 0xC0 },
    { 0x7B, 0x08 },

    { 0x80, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2s
// ******************************************************************
//8D....00190400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData2s,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x20, 0x8D },
    //{ 0x21, 0x14 },
    //{ 0x22, 0x8D },
    { 0x23, 0x00 },
    { 0x24, 0x19 },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4f
// ******************************************************************
//B918150000EB09 ...C21000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4f_16__LTCG_edi1,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x21, 0xB9 },
    { 0x22, 0x18 },
    { 0x23, 0x15 },
    { 0x24, 0x00 },
    { 0x25, 0x00 },
    { 0x26, 0xEB },
    { 0x27, 0x09 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4s
// ******************************************************************
//801908000FBF
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4s,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x23, 0x80 },
    { 0x24, 0x19 },
    { 0x25, 0x08 },
    { 0x26, 0x00 },
    { 0x27, 0x0F },
    { 0x28, 0xBF },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4ub
// ******************************************************************
//8D....4019040033
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4ub,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x20, 0x8D },

    { 0x23, 0x40 },
    { 0x24, 0x19 },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x33 },
    //
);

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
//7505BB050000008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x28, 0x75 },
    { 0x29, 0x05 },
    { 0x2A, 0xBB },
    { 0x2B, 0x05 },
    { 0x2C, 0x00 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0x8B },
    //
);

//******************************************************************
//* D3DPalette_Lock2
//******************************************************************
//F6442408A0568B74
OOVPA_SIG_HEADER_NO_XREF(D3DPalette_Lock2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xF6 },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x08 },
    { 0x04, 0xA0 },
    { 0x05, 0x56 },
    { 0x06, 0x8B },
    { 0x07, 0x74 },
    //
);

// ******************************************************************
// * D3DTexture_LockRect
// ******************************************************************
//8B4424148B4C24088B542404568B
OOVPA_SIG_HEADER_NO_XREF(D3DTexture_LockRect,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x14 },
    { 0x04, 0x8B },
    { 0x05, 0x4C },
    { 0x06, 0x24 },
    { 0x07, 0x08 },
    { 0x08, 0x8B },
    { 0x09, 0x54 },
    { 0x0A, 0x24 },
    { 0x0B, 0x04 },
    { 0x0C, 0x56 },
    { 0x0D, 0x8B },
    //
);

// Verteks 11/03/2009
// blueshogun96 7/17/2010
// ******************************************************************
// * D3DVertexBuffer_Lock2
// ******************************************************************
//0CF6C3105675
OOVPA_SIG_HEADER_NO_XREF(D3DVertexBuffer_Lock2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8A },
    { 0x04, 0x0C },
    { 0x05, 0xF6 },
    { 0x06, 0xC3 },
    { 0x07, 0x10 },
    { 0x08, 0x56 },
    { 0x09, 0x75 },
    { 0x11, 0x8B },
    //
);

// ******************************************************************
// * D3D_BlockOnTime
// ******************************************************************
//6A006A006A016A0656
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime,
                         1036)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    //{ 0x02, 0x5C }, (This value has changed, commented out to expand support for later revisions.)

    { 0x110, 0x6A },
    { 0x111, 0x00 },
    { 0x112, 0x6A },
    { 0x113, 0x00 },
    { 0x114, 0x6A },
    { 0x115, 0x01 },
    { 0x116, 0x6A },
    { 0x117, 0x06 },
    { 0x118, 0x56 },
    //
);

// ******************************************************************
// * D3D_CommonSetRenderTarget
// ******************************************************************
//00750C8B87B42100
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3D_CommonSetRenderTarget, 1024, 10)
    {
#else
OOVPA_XREF(D3D_CommonSetRenderTarget,
           1024,
           1 + 10,
           XRefOne)
{

    XREF_ENTRY(0x18, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif

        { 0x00, 0x83 },
            { 0x01, 0xEC },

            { 0x13, 0x00 },
            { 0x14, 0x75 },
            { 0x15, 0x0C },
            { 0x16, 0x8B },
            { 0x17, 0x87 },
            { 0x18, 0xB4 },
            { 0x19, 0x21 },
            { 0x1A, 0x00 },
    }
OOVPA_END;

// ******************************************************************
// * D3D_KickOffAndWaitForIdle
// ******************************************************************
//8B4C24088B442404E8
OOVPA_SIG_HEADER_NO_XREF(D3D_KickOffAndWaitForIdle2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x10, 0x8B },
    { 0x11, 0x4C },
    { 0x12, 0x24 },
    { 0x13, 0x08 },
    { 0x14, 0x8B },
    { 0x15, 0x44 },
    { 0x16, 0x24 },
    { 0x17, 0x04 },
    { 0x18, 0xE8 },

    { 0x1D, 0xC2 },
    { 0x1E, 0x08 },
    //
);

//******************************************************************
//* D3DDevice_UpdateOverlay
//******************************************************************
//7707B800001000EB
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_UpdateOverlay,
                         1036)
OOVPA_SIG_MATCH(

    { 0x02, 0x08 },

    { 0xCA, 0x77 },
    { 0xCB, 0x07 },
    { 0xCC, 0xB8 },
    { 0xCD, 0x00 },
    { 0xCE, 0x00 },
    { 0xCF, 0x10 },
    { 0xD0, 0x00 },
    { 0xD1, 0xEB },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderStateNotInline
// ******************************************************************
//C381FE880000007D1D8B0D ...C3
// NOTE: Compiler with LTCG flag perform task differently and will
//       produce redundant functions. BUT we need better correction OR
//       maybe removal due to compiler made its own decision how to do
//       things.
// NOTE2: Due to complication problem to tell which one is or not relative
//       to D3DDevice_SetRenderStateNotInline function. There are some that
//       are inline, some do use returns, and some only does jumps.
//       Please cross reference with D3DDevice_SetRenderStateInline__GenericFragment
//       signatures for possible replacement.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderStateNotInline_0__LTCG_esi1_edi2,
                      2048,
                      XRefTwo)
OOVPA_SIG_MATCH(
    // call D3DDevice_SetRenderState_Simple
    XREF_ENTRY(0x0F, XREF_D3DDevice_SetRenderState_Simple),
    // mov D3D_g_RenderState[param_1]
    XREF_ENTRY(0x16, XREF_D3D_g_RenderState),

    // cmp esi,0x??
    OV_MATCH(0x00, 0x83, 0xFE),

    { 0x1A, 0xC3 },
    { 0x1B, 0x81 },
    { 0x1C, 0xFE },
    { 0x1D, 0x88 },
    { 0x1E, 0x00 },
    { 0x1F, 0x00 },
    { 0x20, 0x00 },
    { 0x21, 0x7D },
    { 0x22, 0x1D },
    { 0x23, 0x8B },
    { 0x24, 0x0D },
    //
);

// ******************************************************************
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush_4,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x0B, XREF_D3D_CDevice_SetStateVB),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B),

    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x0A, 0xE8),

    // mov eax,[esi]
    OV_MATCH(0x0F, 0x8B, 0x06),
    // mov esi,[esi + 0x4]
    OV_MATCH(0x11, 0x8B, 0x76, 0x04),
    // mov ecx,[esp + 0x8]
    OV_MATCH(0x14, 0x8B, 0x4C, 0x24, 0x08),
    // add esi,0x200
    OV_MATCH(0x18, 0x81, 0xC6, 0x00, 0x02, 0x00, 0x00),

    // lea ????
    OV_MATCH(0x1E, 0x8D),
    //
);

// ******************************************************************
// * D3DDevice_SetIndices
// ******************************************************************
//74108103000008008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetIndices,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x14, 0x74 },
    { 0x15, 0x10 },
    { 0x16, 0x81 },
    { 0x17, 0x03 },
    { 0x18, 0x00 },
    { 0x19, 0x00 },
    { 0x1A, 0x08 },
    { 0x1B, 0x00 },
    { 0x1C, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetIndices_4
// ******************************************************************
//74108103000008008B ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetIndices_4__LTCG_ebx1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xDB },
    { 0x06, 0x08 },

    { 0x0F, 0x74 },
    { 0x10, 0x10 },
    { 0x11, 0x81 },
    { 0x12, 0x03 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x08 },
    { 0x16, 0x00 },
    { 0x17, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_GetRenderTarget2
// ******************************************************************
//8B88041A000085
OOVPA_SIG_HEADER_XREF(D3DDevice_GetRenderTarget2,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(
    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // TODO: Uncomment when WIP_LessVertexPatching is defined
    // XREF_ENTRY(0x08, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived

    // call D3DResource_AddRef
    XREF_ENTRY(0x2E, XREF_D3DResource_AddRef),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // mov esi,[eax + OFFSET_D3DDevice__m_RenderTarget]
    OV_MATCH(0x06, 0x8B, 0xB0),

    // jz +0x24
    OV_MATCH(0x0E, 0x74, 0x24),

    // call D3DResource_AddRef
    OV_MATCH(0x2D, 0xE8),

    // ret
    OV_MATCH(0x37, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_4__LTCG_eax1,
                         4627)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x42, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),

    // mov [eax + 0x4],0x6
    OV_MATCH(0x4B, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x50, 0x00, 0x00),

    // add eax,0xC
    OV_MATCH(0x55, 0x83, 0xC0, 0x0C),

    // ret
    OV_MATCH(0x8B, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
//04C700941E080083
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x40, 0x04 },
    { 0x41, 0xC7 },
    { 0x42, 0x00 },
    { 0x43, 0x94 },
    { 0x44, 0x1E },
    { 0x45, 0x08 },
    { 0x46, 0x00 },
    { 0x47, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_SetSoftDisplayFilter
// ******************************************************************
//6A00566A0E52FF15 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetSoftDisplayFilter_0__LTCG_unk1,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x16, 0x6A },
    { 0x17, 0x00 },
    { 0x18, 0x56 },
    { 0x19, 0x6A },
    { 0x1A, 0x0E },
    { 0x1B, 0x52 },
    { 0x1C, 0xFF },
    { 0x1D, 0x15 },
    //
);

// ******************************************************************
// * D3DCubeTexture_GetCubeMapSurface2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DCubeTexture_GetCubeMapSurface2,
                         1024)
OOVPA_SIG_MATCH(

    // sub esp,0x8
    OV_MATCH(0x00, 0x83, 0xEC, 0x08),

    // mov e??,[esp + 0x10]
    OV_MATCH(0x04, 0x8B),
    OV_MATCH(0x06, 0x24, 0x10),

    // mov e??,[esp + 0x24]
    OV_MATCH(0x17, 0x8B),
    OV_MATCH(0x19, 0x24, 0x24),
    // lea eax,[esp + 0x14]
    OV_MATCH(0x1B, 0x8D),
    OV_MATCH(0x1D, 0x24, 0x14),
    // push eax
    OV_MATCH(0x1F, 0x50),
    // mov e??,[esp + 0x24]
    OV_MATCH(0x20, 0x8B),
    OV_MATCH(0x22, 0x24, 0x24),

    // call ????
    OV_MATCH(0x3F, 0xE8),

    // add esp,8
    OV_MATCH(0x45, 0x83, 0xC4, 0x08),
    // retn 0x0C
    OV_MATCH(0x48, 0xC2, 0x0C),
    //
);

//******************************************************************
//* D3D::SetTileNoWait
//******************************************************************
// Revision 0
// NOTE: Only very few titles triggered this detection which is the
//       same as D3DDevice_SetTile_0__LTCG_eax1_ecx2 (3911) signature
//       with early ret shifted by one offset.
OOVPA_SIG_HEADER_XREF(D3D_SetTileNoWait_0__LTCG_eax1_ecx2,
                      2024,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov edx,[D3D_g_pDevice]
    XREF_ENTRY(0x02, XREF_D3D_g_pDevice),

    // mov edx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x8B, 0x15),
    // sub esp,0x18
    OV_MATCH(0x06, 0x83, 0xEC, 0x18),

    // mov esi,ecx(param_2)
    OV_MATCH(0x0A, 0x8B, 0xF1),

    // mov [esp + 0x20],0
    OV_MATCH(0x2C, 0xC7, 0x44, 0x24, 0x20, 0x00, 0x00, 0x00, 0x00),
    // mov [esp + 0x1C],0
    OV_MATCH(0x34, 0xC7, 0x44, 0x24, 0x1C),

    // NOTE: Required separate difference to avoid detect <4627
    //       build titles.
    // add esp,0x18
    // ret
    OV_MATCH(0x81, 0x83, 0xC4, 0x18, 0xC3), // offset 0x81 vs 3911 0x80
    //
);

//******************************************************************
//* D3D::SetTileNoWait
//******************************************************************
// Revision 1
OOVPA_SIG_HEADER_XREF(D3D_SetTileNoWait_0__LTCG_eax1_ecx2,
                      2048,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov edx,[D3D_g_pDevice]
    XREF_ENTRY(0x02, XREF_D3D_g_pDevice),

    // mov edx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x8B, 0x15),

    // sub esp,0x18
    OV_MATCH(0x06, 0x83, 0xEC, 0x18),

    // mov esi,ecx(param_2)
    OV_MATCH(0x0B, 0x8B, 0xF1), // offset 0x0B vs 3911/2024 0x0A

    // mov [esp + 0x20],0
    OV_MATCH(0x2C, 0xC7, 0x44, 0x24, 0x20, 0x00, 0x00, 0x00, 0x00),
    // mov [esp + 0x1C],0
    OV_MATCH(0x34, 0xC7, 0x44, 0x24, 0x1C),
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
// Generic OOVPA as of 4627 and newer?
// NOTE: Lowest detected was 4627, unknown if it's present in earlier
//       builds and if it's detected there too.
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_8,
                         4627)
OOVPA_SIG_MATCH(
    // sub esp, 0x??
    OV_MATCH(0x00, 0x83, 0xEC),

    // jc +4
    // mov [esp + 0x??], eax
    OV_MATCH(0x1D, 0x72, 0x04, 0x89, 0x44, 0x24),

    // mov eax, [e?? + 0x08]
    // call ????
    OV_MATCH(0x23, 0x8B),
    OV_MATCH(0x25, 0x08, 0xE8),

    // mov e??, [e?? + 0x24]
    OV_MATCH(0x2F, 0x8B),
    OV_MATCH(0x31, 0x24),

    // NOTE: Do not include ADD, DEC, and LEA instructions OVs. Because they
    //       are at different offsets and sometimes don't have a complete set
    //       of instructions. Plus it is unnecessary.
    //
);
