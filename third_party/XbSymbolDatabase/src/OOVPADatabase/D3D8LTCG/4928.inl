// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_CreateTexture2
// ******************************************************************
//F744241C0000010074
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture2,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x57 },

    { 0x42, 0xF7 },
    { 0x43, 0x44 },
    { 0x44, 0x24 },
    { 0x45, 0x1C },
    { 0x46, 0x00 },
    { 0x47, 0x00 },
    { 0x48, 0x01 },
    { 0x49, 0x00 },
    { 0x4A, 0x74 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
//008107000008008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginPushBuffer_0__LTCG_edi1,
                         2060)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x46, 0x00 },
    { 0x47, 0x81 },
    { 0x48, 0x07 },
    { 0x49, 0x00 },
    { 0x4A, 0x00 },
    { 0x4B, 0x08 },
    { 0x4C, 0x00 },
    { 0x4D, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_GetDepthStencilSurface2
// ******************************************************************
//000085C9750333C0C38B01A9
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetDepthStencilSurface2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x09, 0x00 },
    { 0x0A, 0x00 },
    { 0x0B, 0x85 },
    { 0x0C, 0xC9 },
    { 0x0D, 0x75 },
    { 0x0E, 0x03 },
    { 0x0F, 0x33 },
    { 0x10, 0xC0 },
    { 0x11, 0xC3 },
    { 0x12, 0x8B },
    { 0x13, 0x01 },
    { 0x14, 0xA9 },
    //
);

// ******************************************************************
// * D3DDevice_GetRenderTarget2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetRenderTarget2,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(
    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // TODO: Uncomment when WIP_LessVertexPatching is defined
    // XREF_ENTRY(0x07, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived

    // call D3DResource_AddRef
    XREF_ENTRY(0x2D, XREF_D3DResource_AddRef),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // mov eci,[eax + OFFSET_D3DDevice__m_RenderTarget]
    OV_MATCH(0x05, 0x8B, 0x88),

    // jz +0x24
    OV_MATCH(0x0D, 0x74, 0x24),

    // call D3DResource_AddRef
    OV_MATCH(0x2C, 0xE8),

    // ret
    OV_MATCH(0x35, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
//85C0740F50FF15
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_PersistDisplay,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x55 },

    { 0x0E, 0x85 },
    { 0x0F, 0xC0 },
    { 0x10, 0x74 },
    { 0x11, 0x0F },
    { 0x12, 0x50 },
    { 0x13, 0xFF },
    { 0x14, 0x15 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShaderConstant
// ******************************************************************
//450C8B451085
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShaderConstant,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x07, 0x15 },

    { 0x19, 0x45 },
    { 0x1A, 0x0C },
    { 0x1B, 0x8B },
    { 0x1C, 0x45 },
    { 0x1D, 0x10 },
    { 0x1E, 0x85 },
    //
);

// ******************************************************************
// * D3DDevice_UpdateOverlay
// ******************************************************************
//7707B800001000EB
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_UpdateOverlay,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0xA1 },

    { 0xFD, 0x77 },
    { 0xFE, 0x07 },
    { 0xFF, 0xB8 },
    { 0x100, 0x00 },
    { 0x101, 0x00 },
    { 0x102, 0x10 },
    { 0x103, 0x00 },
    { 0x104, 0xEB },
    //
);

// ******************************************************************
// * D3DTexture_GetSurfaceLevel2
// ******************************************************************
//7C24148D442418508D
OOVPA_SIG_HEADER_NO_XREF(D3DTexture_GetSurfaceLevel2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },

    { 0x05, 0x7C },
    { 0x06, 0x24 },
    { 0x07, 0x14 },
    { 0x08, 0x8D },
    { 0x09, 0x44 },
    { 0x0A, 0x24 },
    { 0x0B, 0x18 },
    { 0x0C, 0x50 },
    { 0x0D, 0x8D },

    { 0x45, 0xC2 },
    { 0x46, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShaderDirect
// ******************************************************************
//B940000000BF ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShaderDirect_0__LTCG_eax1_ebx2,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x10, 0x01 },
    { 0x11, 0xB9 },
    { 0x12, 0x40 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0xBF },

    { 0x25, 0xC3 },
    //
);
