// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_DeleteVertexShader
// ******************************************************************
//Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeleteVertexShader_0__LTCG_eax1,
                         5344)
OOVPA_SIG_MATCH(

    // mov ecx,[eax + -0x1]
    OV_MATCH(0x00, 0x8B, 0x48, 0xFF),
    // dec eax
    // dec ecx
    OV_MATCH(0x03, 0x48, 0x49),
    // mov [eax],ecx
    OV_MATCH(0x05, 0x89, 0x08),
    // JNZ +0xB
    OV_MATCH(0x07, 0x75, 0x0B),

    // call XMemFree
    OV_MATCH(0x0F, 0xE8),

    OV_MATCH(0x14, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShaderDirect
// ******************************************************************
//B940000000BF
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShaderDirect,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x13, 0x00 },
    { 0x14, 0xB9 },
    { 0x15, 0x40 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x00 },
    { 0x19, 0xBF },

    { 0x2B, 0xC2 },
    { 0x2C, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVerticesUP,
                      1048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x13, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x08, 0x8B, 0x35),

    // mov [ebp - 0x14],e??
    OV_MATCH(0x0F, 0x89),
    OV_MATCH(0x11, 0xF8), // D3DDevice_DrawVerticesUP 0xEC vs D3DDevice_DrawIndexedVerticesUP 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x12, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVerticesUP,
                      1048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x13, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x08, 0x8B, 0x35),

    // mov [ebp - 0x14],e??
    OV_MATCH(0x0F, 0x89),
    OV_MATCH(0x11, 0xEC), // D3DDevice_DrawVerticesUP 0xEC vs D3DDevice_DrawIndexedVerticesUP 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x12, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_End,
                         1048)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x13, 0x50 },
    { 0x1C, 0xC7 },
    { 0x22, 0xC7 },
    { 0x2B, 0x08 },
    { 0x34, 0xE1 },
    { 0x49, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetLight
// ******************************************************************
//83E0F0894424108D04C0
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetLight,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x22, 0x83 },
    { 0x23, 0xE0 },
    { 0x24, 0xF0 },
    { 0x25, 0x89 },
    { 0x26, 0x44 },
    { 0x27, 0x24 },
    { 0x28, 0x10 },
    { 0x29, 0x8D },
    { 0x2A, 0x04 },
    { 0x2B, 0xC0 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TwoSidedLighting
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                      1060,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // jz +0x0A
    OV_MATCH(0x31, 0x74, 0x0A),
    // or [0x????????],0x900000
    OV_MATCH(0x33, 0x81),
    OV_MATCH(0x38, 0x00, 0x00, 0x90, 0x00, 0x00), // unique
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TwoSidedLighting
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                      1061,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // jz +0x0A
    OV_MATCH(0x32, 0x74, 0x0A),
    // or [0x????????],0x900000
    OV_MATCH(0x34, 0x81),
    OV_MATCH(0x39, 0x00, 0x00, 0x90, 0x00, 0x00), // unique
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//A900007800751925000007003D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTarget,
                         1072)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x26, 0xA9 },
    { 0x27, 0x00 },
    { 0x28, 0x00 },
    { 0x29, 0x78 },
    { 0x2A, 0x00 },
    { 0x2B, 0x75 },
    { 0x2C, 0x19 },
    { 0x2D, 0x25 },
    { 0x2E, 0x00 },
    { 0x2F, 0x00 },
    { 0x30, 0x07 },
    { 0x31, 0x00 },
    { 0x32, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//55894424088B430489
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0xEC },

    { 0x16, 0x55 },
    { 0x17, 0x89 },
    { 0x18, 0x44 },
    { 0x19, 0x24 },
    { 0x1A, 0x08 },
    { 0x1B, 0x8B },
    { 0x1C, 0x43 },
    { 0x1D, 0x04 },
    { 0x1E, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    XREF_ENTRY(0xF1, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // lea edi,[param_1 + 0x21]
    OV_MATCH(0x09, 0x8D, 0x78, 0x21),
    // shl edi,0x6
    OV_MATCH(0x0C, 0xC1, 0xE7, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x11, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xF0, 0xE8),

    // ret
    OV_MATCH(0xFF, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
//F64401680175 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LightEnable_4__LTCG_eax1,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x22, 0xF6 },
    { 0x23, 0x44 },
    { 0x24, 0x01 },
    { 0x25, 0x68 },
    { 0x26, 0x01 },
    { 0x27, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//005D6A006A006A00E8
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x13C, 0x00 },
    { 0x13D, 0x5D },
    { 0x13E, 0x6A },
    { 0x13F, 0x00 },
    { 0x140, 0x6A },
    { 0x141, 0x00 },
    { 0x142, 0x6A },
    { 0x143, 0x00 },
    { 0x144, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset_0__LTCG_ebx1,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x37, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // jnz +0x??
    OV_MATCH(0x33, 0x75),

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x36, 0xE8),
    // push param_1
    OV_MATCH(0x3B, 0x53),
    //
);

// ******************************************************************
// * D3D_CommonSetMultiSampleModeAndScale
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3D_CommonSetMultiSampleModeAndScale_4__LTCG_eax1,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3DRS_MultiSampleMode]
    XREF_ENTRY(0x29, XREF_D3DRS_MultiSampleMode),

    // sub esp,0x0C
    OV_MATCH(0x00, 0x83, 0xEC, 0x0C),

    // mov esi,eax
    OV_MATCH(0x06, 0x8B, 0xF0),

    // shr ecx,0x14
    OV_MATCH(0x45, 0xC1, 0xE9, 0x14),
    // and ecx,0xF
    OV_MATCH(0x48, 0x83, 0xE1, 0x0F),
    // mov eax,0x1
    OV_MATCH(0x4B, 0xB8, 0x01, 0x00),
    //
);
