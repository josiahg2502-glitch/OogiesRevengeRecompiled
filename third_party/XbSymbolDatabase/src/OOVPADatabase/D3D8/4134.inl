// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_GetBackBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackBuffer,
                         4134)
OOVPA_SIG_MATCH(

    // D3DDevice_GetBackBuffer+0x04 : cmp eax, 0xFFFFFFFF
    { 0x04, 0x83 },
    { 0x05, 0xF8 },
    { 0x06, 0xFF },

    // D3DDevice_GetBackBuffer+0x0D : jnz +0x07
    { 0x0D, 0x75 },
    { 0x0E, 0x07 },

    // D3DDevice_GetBackBuffer+0x18 : sbb eax, eax
    { 0x18, 0x1B },
    { 0x19, 0xC0 },

    // D3DDevice_GetBackBuffer+0x1D : mov eax, [ecx+eax*4+0x207C]
    { 0x1D, 0x8B },
    { 0x1E, 0x84 },
    { 0x1F, 0x81 },
    { 0x20, 0x7C },
    { 0x21, 0x20 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         4134)
OOVPA_SIG_MATCH(

    // D3DDevice_SetRenderState_ZEnable+0x0C : jb +0x05
    { 0x0C, 0x72 },
    { 0x0D, 0x05 },

    // D3DDevice_SetRenderState_ZEnable+0x1B : mov edx, [esi+0x2074h]
    { 0x1B, 0x8B },
    { 0x1C, 0x96 },
    { 0x1D, 0x74 },
    { 0x1E, 0x20 },

    // D3DDevice_SetRenderState_ZEnable+0x31 : mov dword ptr [eax], 0x4030C
    { 0x31, 0xC7 },
    { 0x32, 0x00 },
    { 0x33, 0x0C },
    { 0x34, 0x03 },
    { 0x35, 0x04 },

    // D3DDevice_SetRenderState_ZEnable+0x98 : retn 0x04
    { 0x98, 0xC2 },
    { 0x99, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_D3DDevice__m_VertexShader_OFFSET), // Derived

    // D3DDevice_SetVertexShader+0x06 : test bl, 1
    { 0x06, 0xF6 },
    { 0x07, 0xC3 },
    { 0x08, 0x01 },

    // D3DDevice_SetVertexShader+0x11 : mov eax, [esi+0x0380]
    { 0x11, 0x8B },
    { 0x12, 0x86 },
    { 0x13, 0x80 },
    { 0x14, 0x03 },

    // D3DDevice_SetVertexShader+0x90 : retn 0x04
    { 0x90, 0xC2 },
    { 0x91, 0x04 },

    // D3DDevice_SetVertexShader+0xB0 : mov dword ptr [eax], 0x4194C
    { 0xB0, 0xC7 },
    { 0xB1, 0x00 },
    { 0xB2, 0x4C },
    { 0xB3, 0x19 },
    { 0xB4, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetMaterial,
                         4134)
OOVPA_SIG_MATCH(

    // D3DDevice_SetMaterial+0x0C : add edi, 0x0940
    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0xF0 },
    { 0x0F, 0x09 },

    // D3DDevice_SetMaterial+0x12 : mov ecx, 0x11
    { 0x12, 0xB9 },
    { 0x13, 0x11 },

    // D3DDevice_SetMaterial+0x1F : or ecx, 0x1000
    { 0x1F, 0x81 },
    { 0x20, 0xC9 },
    { 0x21, 0x00 },
    { 0x22, 0x10 },

    // D3DDevice_SetMaterial+0x2D : retn 0x04
    { 0x2D, 0xC2 },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetMaterial,
                         4134)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0xF0 },
    { 0x0E, 0x09 },
    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0xB9 },
    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetBackMaterial,
                         4134)
OOVPA_SIG_MATCH(

    // D3DDevice_SetBackMaterial+0x0C : add edi, 0x0A34
    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0x34 },
    { 0x0F, 0x0A },

    // D3DDevice_SetBackMaterial+0x12 : mov ecx, 0x11
    { 0x12, 0xB9 },
    { 0x13, 0x11 },

    // D3DDevice_SetBackMaterial+0x1F : or ecx, 0x1000
    { 0x1F, 0x81 },
    { 0x20, 0xC9 },
    { 0x21, 0x00 },
    { 0x22, 0x10 },

    // D3DDevice_SetBackMaterial+0x2D : retn 0x04
    { 0x2D, 0xC2 },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackMaterial,
                         4134)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },

    { 0x0D, 0x34 },
    { 0x0E, 0x0A },
    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0xB9 },
    { 0x12, 0x11 },

    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3D::SetFence
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         4134)
OOVPA_SIG_MATCH(

    { 0x0D, 0x72 },
    { 0x0E, 0x0E },
    { 0x31, 0xBA },
    { 0x32, 0x90 },
    { 0x33, 0x1D },
    { 0x34, 0x04 },
    { 0x35, 0x00 },
    { 0x45, 0x83 },
    { 0x46, 0xE1 },
    { 0x47, 0x3F },
    { 0xAA, 0xC2 },
    { 0xAB, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetFlickerFilter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetFlickerFilter,
                         4134)
OOVPA_SIG_MATCH(

    { 0x01, 0x0D },

    { 0x0D, 0x56 },
    { 0x0E, 0x8B },
    { 0x0F, 0x74 },
    { 0x10, 0x24 },
    { 0x11, 0x08 },
    { 0x12, 0x74 },
    { 0x13, 0x08 },
    { 0x14, 0x39 },
    { 0x15, 0x35 },

    { 0x22, 0x6A },
    { 0x23, 0x00 },
    { 0x24, 0x56 },
    { 0x25, 0x6A },
    { 0x26, 0x0B },
    { 0x27, 0x50 },

    { 0x3F, 0xC2 },
    { 0x40, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetSoftDisplayFilter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetSoftDisplayFilter,
                         4134)
OOVPA_SIG_MATCH(

    { 0x01, 0x0D },

    { 0x23, 0x74 },
    { 0x24, 0x28 },
    { 0x25, 0x8B },
    { 0x26, 0x90 },

    { 0x2B, 0x6A },
    { 0x2C, 0x00 },
    { 0x2D, 0x56 },
    { 0x2E, 0x6A },
    { 0x2F, 0x0E },
    { 0x30, 0x52 },

    { 0x4E, 0xC2 },
    { 0x4F, 0x04 },

    /*
        // D3DDevice_SetSoftDisplayFilter+0x25 : mov edx, [eax+0x2268]
        { 0x25, 0x8B },
        { 0x26, 0x90 },
        { 0x27, 0x68 },
        { 0x28, 0x22 },*/

    //
);

// ******************************************************************
// * D3DDevice_EnableOverlay
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_EnableOverlay,
                         4134)
OOVPA_SIG_MATCH(

    // D3DDevice_EnableOverlay+0x0B : mov ecx, [eax+0x8700]
    { 0x0B, 0x8B },
    { 0x0C, 0x88 },
    { 0x0E, 0x87 },

    // D3DDevice_EnableOverlay+0x15 : jz +0x0A
    { 0x15, 0x74 },
    { 0x16, 0x0A },

    // D3DDevice_EnableOverlay+0x5A : mov [eax+0x8918], ecx
    { 0x5A, 0x89 },
    { 0x5B, 0x88 },
    { 0x5C, 0x18 },
    { 0x5D, 0x89 },

    // D3DDevice_EnableOverlay+0x60 : retn 0x04
    { 0x60, 0xC2 },
    { 0x61, 0x04 },
    //
);

// ******************************************************************
// * D3D::MakeRequestedSpace
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_MakeRequestedSpace_8,
                         4134)
OOVPA_SIG_MATCH(

    // D3D::MakeRequestedSpace+0x00 : sub esp,0x__
    OV_MATCH(0x00, 0x83, 0xEC),

    // D3D::MakeRequestedSpace+0x0A : test [esi+0x08],0x04
    OV_MATCH(0x0A, 0xF6, 0x46, 0x08, 0x04),

    // D3D::MakeRequestedSpace+0x22 : sub ecx,edi; add edx,ecx
    OV_MATCH(0x22, 0x2B, 0xCF, 0x03, 0xD1),

    // D3D::MakeRequestedSpace+0x33 : add esp,0x__
    OV_MATCH(0x33, 0x83, 0xC4),

    // D3D::MakeRequestedSpace+0x36 : ret 0x0008
    OV_MATCH(0x36, 0xC2, 0x08),

    //
);

// ******************************************************************
// * D3DDevice_InsertCallback
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_InsertCallback,
                         4134)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x07, 0x8B },
    { 0x0E, 0xA1 },

    { 0x1F, 0x0C },
    { 0x20, 0x8B },
    { 0x21, 0x54 },
    { 0x22, 0x24 },
    { 0x23, 0x10 },
    { 0x24, 0xC7 },
    { 0x25, 0x00 },
    { 0x26, 0x8C },
    { 0x27, 0x1D },
    { 0x28, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_GetShaderConstantMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetShaderConstantMode,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x18 },
    { 0x08, 0x20 },
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
// * D3DDevice_GetProjectionViewportMatrix
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetProjectionViewportMatrix,
                         4134) // Up to 4531
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x07, 0x57 },

    { 0x0E, 0x70 }, // 4361 0x7004
    { 0x0F, 0x04 },
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
// * D3DDevice_CaptureStateBlock
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CaptureStateBlock,
                         4134)
OOVPA_SIG_MATCH(

    { 0x14, 0x3D },
    { 0x36, 0x8B },

    { 0x50, 0x83 },
    { 0x51, 0xC3 },
    { 0x52, 0x08 },
    { 0x53, 0xFF },
    { 0x54, 0x45 },
    { 0x55, 0xF8 },
    { 0x56, 0x8B },
    { 0x57, 0x45 },
    { 0x58, 0xF8 },

    { 0x6A, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_BeginStateBlock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginStateBlock,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_BeginStateBlock+0x0F : call [ClearStateBlockFlags]
    XREF_ENTRY(0x0A, XREF_D3D_ClearStateBlockFlags),

    // D3DDevice_BeginStateBlock+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_BeginStateBlock+0x05 : mov [eax+8], 0x20
    { 0x05, 0x83 },
    { 0x06, 0x48 },
    { 0x07, 0x08 },
    { 0x08, 0x20 },
    //
);

// ******************************************************************
// * D3DDevice_EndStateBlock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_EndStateBlock,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_EndStateBlock+0x0F : call [ClearStateBlockFlags]
    XREF_ENTRY(0x0A, XREF_D3D_RecordStateBlock),

    // D3DDevice_EndStateBlock+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_EndStateBlock+0x05 : and [eax+8], 0xFFFFFFDF
    { 0x05, 0x83 },
    { 0x06, 0x60 },
    { 0x07, 0x08 },
    { 0x08, 0xDF },
    //
);

// ******************************************************************
// * D3DDevice_GetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShader,
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x84 },
    { 0x08, 0x03 },
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
                         4134)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x70 },
    { 0x08, 0x03 },
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
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         4134)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x043C]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x3C },
    { 0x08, 0x04 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x0C : mov [eax+0x043C], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0x3C },
    { 0x0F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_MakeSpace
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_MakeSpace,
                      4134,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call D3D::MakeRequestedSpace
    XREF_ENTRY(0x0A, XREF_D3D_MakeRequestedSpace),

    // mov eax, [addr]
    OV_MATCH(0x00, 0xA1),
    // push eax
    OV_MATCH(0x05, 0x50),

    // call D3D::MakeRequestedSpace
    OV_MATCH(0x09, 0xE8),
    // ret
    OV_MATCH(0x0E, 0xC3), // required to separate this detection from inlined function
    //
);

// ******************************************************************
// * D3DDevice_GetTexture, named with 2 suffix to match EMUPATCH(D3DDevice_GetTexture2)
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_GetTexture2, 4134, 23) // Up to 4531
    {
#else
OOVPA_XREF(D3DDevice_GetTexture2, 4134, 1 + 23, // Up to 4531
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
            { 0x0E, 0x78 }, // GetTexture 780A vs GetPalette 880A
            { 0x0F, 0x0A },
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
            { 0x1F, 0x16 },
    }
OOVPA_END;

// ******************************************************************
// * Rollback support signature(s)
// ******************************************************************
#define D3DDevice_EndVisibilityTest_4134 D3DDevice_EndVisibilityTest_3925
