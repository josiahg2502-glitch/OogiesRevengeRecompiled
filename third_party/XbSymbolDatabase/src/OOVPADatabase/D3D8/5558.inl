// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetMaterial,
                         5558)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0xF0 },
    { 0x0F, 0x0E },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x90 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetMaterial,
                         5558)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },

    { 0x0D, 0xF0 },
    { 0x0E, 0x0E },

    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3D::SetFence
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         5558)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x09, 0x3B },
    { 0x0A, 0x46 },
    { 0x0B, 0x04 },
    { 0x0F, 0xE8 },
    { 0x14, 0x8B },
    { 0x15, 0x7E },
    { 0x16, 0x2C },

    { 0x39, 0x0C },
    //
);

// ******************************************************************
// * D3D::BlockOnTime
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime,
                         5558)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x08, 0x46 },
    { 0x1F, 0x83 },

    { 0x52, 0x8B },
    { 0x53, 0x4D },
    { 0x54, 0x04 },
    { 0x55, 0x3B },
    { 0x56, 0xCA },
    { 0x57, 0x77 },
    { 0x58, 0x03 },
    { 0x59, 0x03 },
    { 0x5A, 0x4E },
    /*
        { 0x09, 0x30 },
        { 0x27, 0x07 },
        { 0x7E, 0x25 },
        { 0x9F, 0x20 },
        { 0xD3, 0x56 },
        { 0xE9, 0x57 },*/
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         5558)
OOVPA_SIG_MATCH(

    { 0x1D, 0x44 },
    { 0x3C, 0x8B },
    { 0x5D, 0xD9 },
    { 0x7D, 0xD8 },
    { 0x99, 0x0E },
    { 0xB8, 0xE8 },
    { 0xD7, 0x24 },
    { 0xF6, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         5558)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x0934]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x34 },
    { 0x08, 0x09 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x0C : mov [eax+0x0934], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0x34 },
    { 0x0F, 0x09 },
    //
);

// ******************************************************************
// * D3DDevice_SetGammaRamp
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetGammaRamp,
                         5558)
OOVPA_SIG_MATCH(

    { 0x0F, 0x68 },
    { 0x20, 0x34 },
    { 0x31, 0xB4 },
    { 0x42, 0x08 },
    { 0x53, 0xF3 },
    { 0x64, 0xCA },
    { 0x75, 0x07 },
    //
);

// ******************************************************************
// * D3DDevice_SetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetBackMaterial,
                         5558)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0x34 },
    { 0x0F, 0x0F },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x90 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackMaterial,
                         5558)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },

    { 0x0D, 0x34 },
    { 0x0E, 0x0F },

    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3D::MakeRequestedSpace
// ******************************************************************
// Generic OOVPA as of 5558 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3D_MakeRequestedSpace_8,
                         5558)
OOVPA_SIG_MATCH(

    // D3D::MakeRequestedSpace+0x00 : push ecx; push esi
    OV_MATCH(0x00, 0x51, 0x56),

    // D3D::MakeRequestedSpace+0x08 : test [esi+0x08],0x04
    OV_MATCH(0x08, 0xF6, 0x46, 0x08, 0x04),

    // D3D::MakeRequestedSpace+0x20 : sub ecx,edi; add edx,ecx
    OV_MATCH(0x20, 0x2B, 0xCF, 0x03, 0xD1),

    // D3D::MakeRequestedSpace+0x32 : ret 0x08
    OV_MATCH(0x32, 0xC2, 0x08),

    //
);

// ******************************************************************
// * D3DDevice_GetViewportOffsetAndScale
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetViewportOffsetAndScale,
                         5558)
OOVPA_SIG_MATCH(

    { 0x1E, 0xD8 },
    { 0x40, 0xD8 },
    { 0x5E, 0xC9 },
    { 0x8C, 0x0E },
    { 0x9D, 0x0E },
    { 0xBE, 0xD8 },
    { 0xDD, 0x14 },
    { 0xFE, 0xC1 },
    //
);

// ******************************************************************
// * D3DDevice_GetProjectionViewportMatrix
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetProjectionViewportMatrix,
                         5558)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },
    { 0x07, 0x57 },
    { 0x0F, 0x09 },
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
// * D3DDevice_RunPushBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         5558)
OOVPA_SIG_MATCH(

    { 0x0E, 0xED },
    { 0x42, 0x18 },
    { 0x62, 0x04 },
    { 0x8D, 0x1C },
    { 0xAF, 0x0F },
    { 0xF6, 0x41 },
    //
);

// ******************************************************************
// * D3DDevice_GetShaderConstantMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetShaderConstantMode,
                         5558)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x18 },
    { 0x08, 0x19 },
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
// * D3DDevice_GetPixelShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetPixelShader,
                         5558)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x80 },
    { 0x08, 0x07 },
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
// * D3DDevice_GetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShader,
                         5558)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x94 },
    { 0x08, 0x07 },
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
OOVPA_NO_XREF(D3DDevice_GetTexture2, 5558, 23) // Up to 5659
    {
#else
OOVPA_XREF(D3DDevice_GetTexture2, 5558, 1 + 23, // Up to 5659
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
            { 0x0E, 0x78 }, // GetTexture2 780F vs GetPalette2 880F
            { 0x0F, 0x0F },

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
// * Rollback support signature(s)
// ******************************************************************
#define Direct3D_CreateDevice_5558                      Direct3D_CreateDevice_3911
#define D3DDevice_GetTransform_5558                     D3DDevice_GetTransform_4039
#define D3DDevice_SetVertexShaderConstantNotInline_5558 D3DDevice_SetVertexShaderConstantNotInline_4627
