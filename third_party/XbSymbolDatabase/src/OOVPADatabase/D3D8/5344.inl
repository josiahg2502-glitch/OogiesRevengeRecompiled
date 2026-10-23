// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SetLight
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetLight,
                         5344)
OOVPA_SIG_MATCH(

    // D3DDevice_SetLight+0x1f : add REG, 0x10
    { 0x1F, 0x83 },
    { 0x21, 0x10 },

    // D3DDevice_SetLight+0x22 : and REG, 0xfffffff0
    { 0x22, 0x83 },
    { 0x24, 0xf0 },

    // D3DDevice_SetLight+0x2c : push 0x24800000
    { 0x2C, 0x68 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0x80 },
    { 0x30, 0x24 },

    // D3DDevice_SetLight+0x65 : jz +8
    { 0x65, 0x74 },
    { 0x66, 0x08 },

    // D3DDevice_SetLight+0xe3 : jz +8
    { 0xE3, 0x74 },
    { 0xE4, 0x08 },

    // D3DDevice_SetLight+0xfe : shr ???, 2
    { 0xFE, 0xC1 },
    { 0x100, 0x02 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TwoSidedLighting
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_TwoSidedLighting],eax
    XREF_ENTRY(0x42, XREF_D3DRS_TwoSidedLighting),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B),

    // mov e??,[esp + param_1]
    OV_MATCH(0x14, 0x8B),

    // mov [D3DRS_TwoSidedLighting],e??
    OV_MATCH(0x40, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_LightEnable,
                      5344,
                      XRefTwo) // PatrickvL : Also for 5558, 5659, 5788, 5849, 5933
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_D3D_g_pDevice), // Derived
    XREF_ENTRY(0x67, XREF_D3DDevice_SetLight),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x68 },
    { 0x03, 0x53 },

    { 0x04, 0x8B },
    { 0x05, 0x5C },
    { 0x06, 0x24 },
    { 0x07, 0x70 },
    { 0x08, 0x56 },

    { 0x09, 0x8B },
    { 0x0A, 0x35 },

    { 0x0F, 0x3B },
    { 0x10, 0x9E },

    //{ 0x11, 0x90 }, // A4 // A8
    //{ 0x12, 0x03 }, // 07
    { 0x13, 0x00 },

    { 0x14, 0x00 },
    { 0x15, 0x57 },
    { 0x16, 0x73 },
    { 0x17, 0x13 },
    { 0x18, 0x8B },

    { 0x19, 0x8E },
    //{ 0x1A, 0x8C }, // A0 // A4
    //{ 0x1B, 0x03 }, // 07
    { 0x1C, 0x00 },
    { 0x1D, 0x00 },
    { 0x1E, 0x8D },
    { 0x1F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetLightEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetLightEnable,
                      5344,
                      XRefOne) // PatrickvL : Also for 5558, 5659, 5788, 5849, 5933
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3D_g_pDevice), // Derived

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x8B },
    { 0x05, 0x0D },

    { 0x0A, 0x8B },
    { 0x0B, 0x91 },
    //{ 0x0C, 0x8C }, 5344 0x8C03 vs 5558 0xA007
    //{ 0x0D, 0x03 },
    { 0x0E, 0x00 },
    { 0x0F, 0x00 },
    { 0x10, 0x8D },
    { 0x11, 0x04 },
    { 0x12, 0xC0 },
    { 0x13, 0xC1 },
    { 0x14, 0xE0 },
    { 0x15, 0x04 },
    { 0x16, 0x56 },
    { 0x17, 0x8B },
    { 0x18, 0xB4 },
    { 0x19, 0x02 },
    { 0x1A, 0x8C },
    { 0x1B, 0x00 },
    { 0x1C, 0x00 },
    { 0x1D, 0x00 },
    { 0x1E, 0x8B },
    { 0x1F, 0x54 },
    /*
        { 0x3E, 0xC7 },
        { 0x5E, 0xC7 },
        { 0x7E, 0x00 },
        { 0x9E, 0x85 },
        { 0xBE, 0x01 },
        { 0xDE, 0x00 },
        { 0xFE, 0x83 },
*/
    //
);

// ******************************************************************
// * D3DDevice_SetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetMaterial,
                         5344)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0xE0 },
    { 0x0F, 0x0A },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x90 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         5344)
OOVPA_SIG_MATCH(

    { 0x1E, 0x87 },
    { 0x3E, 0xC0 },
    { 0x5E, 0x49 },
    { 0x7E, 0xD6 },
    { 0x9E, 0xE2 },
    { 0xBE, 0xC1 },
    { 0xDE, 0xC9 },
    { 0xFE, 0x14 },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         5344)
OOVPA_SIG_MATCH(

    { 0x1D, 0x44 },
    { 0x3C, 0x8B },
    { 0x5D, 0xD9 },
    { 0x7D, 0xD8 },
    { 0x99, 0x0A },
    { 0xB8, 0xE8 },
    { 0xD7, 0x24 },
    { 0xF6, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
// Generic as of OOVPA 5344/5455 and newer.
// The only difference between 5344/5455 is the offset shift for
// D3DDevice__m_RenderTarget's asm code.
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 5344, 13)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget,
           5344,
           1 + 13,
           XRefOne)
{

    // D3DDevice_SetRenderTarget+0x16 : mov eax,[edi+0x________]
    XREF_ENTRY(0x18, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived // NOTE 5455+ is at offset 0x19
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0x0C
        OV_MATCH(0x00, 0x83, 0xEC, 0x0C),

            // D3DDevice_SetRenderTarget+0x16 : mov eax,[edi+0x________]
            OV_MATCH(0x16, 0x8B, 0x87), // Offset 5344 0x16 vs 5455+ 0x17

            // D3DDevice_SetRenderTarget+0xF1 : shr ecx,0x14
            OV_MATCH(0xF1, 0xC1, 0xE9, 0x14),

            // D3DDevice_SetRenderTarget+0xF4 : and ecx, 0x0F
            OV_MATCH(0xF4, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0xFC : shl eax,cl
            OV_MATCH(0xFC, 0xD3, 0xE0),
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_CreateVertexBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateVertexBuffer2,
                         5344)
OOVPA_SIG_MATCH(

    { 0x08, 0xE8 },
    { 0x0E, 0xF0 },
    { 0x10, 0xF6 },
    { 0x14, 0x44 },
    { 0x18, 0x04 },
    { 0x1C, 0x6A },
    { 0x2C, 0x85 },
    { 0x30, 0x68 },
    { 0x34, 0x24 },
    //
);

// ******************************************************************
// * D3DDevice_CreatePalette2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreatePalette2,
                         5344)
OOVPA_SIG_MATCH(

    { 0x08, 0xE8 },
    { 0x10, 0xFF },
    { 0x11, 0x75 },
    { 0x12, 0x04 },
    { 0x13, 0x5F },
    { 0x14, 0xC2 },
    { 0x38, 0x85 },
    { 0x3C, 0x68 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVerticesUP,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x0B, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x15, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov edi,[D3D_g_pDevice]
    OV_MATCH(0x09, 0x8B, 0x3D),

    // mov ecx,edi
    OV_MATCH(0x0F, 0x8B, 0xCF),
    // mov [ebp - 0x14],e??
    OV_MATCH(0x11, 0x89),
    OV_MATCH(0x13, 0xEC), // D3DDevice_DrawVerticesUP 0xEC vs D3DDevice_DrawIndexedVerticesUP 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x14, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVerticesUP,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x15, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x08, 0x8B, 0x35),

    // mov ecx,esi
    OV_MATCH(0x0F, 0x8B, 0xCE),

    // mov [ebp - 0x8],e??
    OV_MATCH(0x11, 0x89),
    OV_MATCH(0x13, 0xF8), // D3DDevice_DrawIndexedVerticesUP 0xF8 vs D3DDevice_DrawVerticesUP 0xEC
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x14, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
//Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_End,
                         5344)
OOVPA_SIG_MATCH(

    { 0x08, 0x06 },
    { 0x0A, 0x46 },
    { 0x0E, 0xE8 },
    { 0x15, 0xFC },
    { 0x17, 0x04 },

    { 0x34, 0x4E },
    { 0x35, 0x08 },
    { 0x36, 0x5E },
    { 0x37, 0x74 },
    { 0x38, 0x07 },
    { 0x39, 0x6A },
    { 0x3A, 0x01 },
    { 0x3B, 0xE8 },

    { 0x40, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_CreatePixelShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreatePixelShader,
                         5344)
OOVPA_SIG_MATCH(

    // D3DDevice_CreatePixelShader+0x05 : push 0xFC
    { 0x05, 0x68 },
    { 0x06, 0xFC },

    // D3DDevice_CreatePixelShader+0x10 : mov eax, 0x8007000E
    { 0x13, 0xB8 },
    { 0x14, 0x0E },
    { 0x15, 0x00 },
    { 0x16, 0x07 },
    { 0x17, 0x80 },

    // D3DDevice_CreatePixelShader+0x31 : mov ecx, 0x3C
    { 0x34, 0xB9 },
    { 0x35, 0x3C },

    // D3DDevice_CreatePixelShader+0x42 : retn 0x08
    { 0x45, 0xC2 },
    { 0x46, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_DeleteVertexShader
// ******************************************************************
//Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeleteVertexShader,
                         5344)
OOVPA_SIG_MATCH(

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),
    // mov ecx,[eax + -0x1]
    OV_MATCH(0x04, 0x8B, 0x48, 0xFF),

    // mov [eax],ecx
    OV_MATCH(0x09, 0x89, 0x08),
    // JNZ +0xB
    OV_MATCH(0x0B, 0x75, 0x0B),

    // retn 4
    OV_MATCH(0x18, 0xC2, 0x04)
    //
);

// ******************************************************************
// * D3DDevice_DeletePixelShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeletePixelShader,
                         5344)
OOVPA_SIG_MATCH(

    { 0x02, 0x24 },
    { 0x06, 0x75 },
    { 0x0A, 0x04 },
    { 0x0E, 0x0B },
    { 0x12, 0x80 },
    { 0x1A, 0xC2 },
    { 0x1B, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetMaterial,
                         5344)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0xE0 },
    { 0x0E, 0x0A },
    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackMaterial,
                         5344)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0x24 },
    { 0x0E, 0x0B },
    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetBackMaterial,
                         5344)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0x24 },
    { 0x0F, 0x0B },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x90 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetProjectionViewportMatrix
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetProjectionViewportMatrix,
                         5344) // Up to 5455
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x07, 0x57 },

    { 0x0E, 0x60 }, // 4361 0x7004
    { 0x0F, 0x05 },
    { 0x10, 0x00 },
    { 0x11, 0x00 },
    { 0x12, 0xB9 },
    { 0x13, 0x10 },
    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0x00 },
    { 0x17, 0xF3 },
    { 0x18, 0xA5 },
    { 0x19, 0x5F },
    { 0x1A, 0x5E },
    { 0x1B, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_CreateIndexBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateIndexBuffer2,
                         5344)
OOVPA_SIG_MATCH(

    { 0x05, 0x00 },
    { 0x0C, 0x50 },
    { 0x13, 0xC0 },
    { 0x1A, 0xC9 },
    { 0x21, 0x04 },
    { 0x28, 0xC7 },
    { 0x2F, 0x48 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x09, XREF_D3D_CDevice_SetStateVB),

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x06, 0x6A },
    { 0x07, 0x00 },

    { 0x11, 0x40 },

    { 0x12, 0x89 },
    { 0x13, 0x44 },
    { 0x14, 0x24 },
    { 0x15, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         5344)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x0520]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x20 },
    { 0x08, 0x05 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x0C : mov [eax+0x0520], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0x20 },
    { 0x0F, 0x05 },
    //
);

// ******************************************************************
// * D3DDevice_GetShaderConstantMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetShaderConstantMode,
                         5344)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x08 },
    { 0x08, 0x15 },
    { 0x09, 0x00 },
    { 0x0A, 0x00 },
    { 0x0B, 0x8B },
    { 0x0C, 0x54 },
    { 0x0D, 0x24 },
    { 0x0E, 0x04 },
    { 0x0F, 0x89 },
    { 0x10, 0x0A },
    { 0x11, 0xC2 },
    { 0x12, 0x04 },
    { 0x13, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_GetTexture, named with 2 suffix to match EMUPATCH(D3DDevice_GetTexture2)
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_GetTexture2, 5344, 23)
    {
#else
OOVPA_XREF(D3DDevice_GetTexture2, 5344, 1 + 23, // Up to 5455
           XRefOne)
{

    XREF_ENTRY(0x0E, XREF_OFFSET_D3DDevice__m_Textures), // Derived
#endif
        { 0x00, 0x8B },
            { 0x01, 0x44 },
            { 0x02, 0x24 },
            { 0x03, 0x04 },
            { 0x04, 0x8B },
            { 0x05, 0x0D },

            { 0x0A, 0x56 },
            { 0x0B, 0x8D },
            { 0x0C, 0xB4 },
            { 0x0D, 0x81 },
            { 0x0E, 0x68 }, // GetTexture2 680B vs GetPalette2 780B
            { 0x0F, 0x0B },

            { 0x10, 0x00 },
            { 0x11, 0x00 },
            { 0x12, 0x8B },
            { 0x13, 0x06 },
            { 0x14, 0x85 },
            { 0x15, 0xC0 },
            { 0x16, 0x74 },

            { 0x18, 0x50 },
            { 0x19, 0xE8 },

            { 0x1E, 0x8B },
            { 0x1F, 0x06 },
        //{ 0x21, 0xC2 },
    }
OOVPA_END;

// ******************************************************************
// * D3D_CommonSetMultiSampleModeAndScale
// ******************************************************************
// Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_XREF(D3D_CommonSetMultiSampleModeAndScale,
                      5344,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3DRS_MultiSampleMode]
    XREF_ENTRY(0x2D, XREF_D3DRS_MultiSampleMode),

    // sub esp,0x10
    OV_MATCH(0x00, 0x83, 0xEC, 0x10),

    // mov esi,ecx
    OV_MATCH(0x06, 0x8B, 0xF1),

    // shr ecx,0x14
    OV_MATCH(0x49, 0xC1, 0xE9, 0x14),
    // and ecx,0xF
    OV_MATCH(0x4C, 0x83, 0xE1, 0x0F),
    // mov eax,0x1
    OV_MATCH(0x4F, 0xB8, 0x01, 0x00),
    //
);

// ******************************************************************
// * Rollback support signature(s)
// ******************************************************************
#define D3DDevice_GetTransform_5344 D3DDevice_GetTransform_3925
