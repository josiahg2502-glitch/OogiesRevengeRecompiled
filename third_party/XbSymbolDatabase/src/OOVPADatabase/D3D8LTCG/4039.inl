// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_DrawIndexedVertices
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVertices,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x17, XREF_D3D_CDevice_SetStateVB),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x08
    OV_MATCH(0x03, 0x83, 0xEC, 0x08),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x08, 0x8B),

    // mov [ebp - 8],esi
    OV_MATCH(0x13, 0x89, 0x75, 0xF8),
    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x16, 0xE8),
    // Do not use any offsets after 0x1A
);

// ******************************************************************
// * D3DDevice_DrawIndexedVertices
// ******************************************************************
// TODO: Migrate this change into 1036 (above) signature once range
//       offset is supported.
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVertices,
                      1037,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x18, XREF_D3D_CDevice_SetStateVB),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x08
    OV_MATCH(0x03, 0x83, 0xEC, 0x08),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x08, 0x8B),

    // mov [ebp - 8],esi
    OV_MATCH(0x14, 0x89, 0x75, 0xF8),
    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x17, 0xE8),
    // Do not use any offsets after 0x1B
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_0__LTCG_edx1,
                         4039)
OOVPA_SIG_MATCH(
    // mov eax, [edx + 0x08]
    OV_MATCH(0x00, 0x8B, 0x42, 0x08),

    // "test ?h, 0x20" and "test ?l, 0x4" instructions tend to swap or at different offsets.
    // To reduce signatures, we check for "or eax, 0x2000" unique instruction and its return.

    // pop edi
    // or eax, 0x2000
    // pop ebp
    OV_MATCH(0x82, 0x5F, 0x0D, 0x00, 0x20, 0x00, 0x00, 0x5D), // unique

    // ret
    OV_MATCH(0x8D, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//EB06894424088BF8
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x23, 0xEB },
    { 0x24, 0x06 },
    { 0x25, 0x89 },
    { 0x26, 0x44 },
    { 0x27, 0x24 },
    { 0x28, 0x08 },
    { 0x29, 0x8B },
    { 0x2A, 0xF8 },
    //
);

// ******************************************************************
// * D3DDevice_SetLight
// ******************************************************************
//83E0F0894424108D04C0
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetLight,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0xF0 },
    { 0x29, 0x89 },
    { 0x2A, 0x44 },
    { 0x2B, 0x24 },
    { 0x2C, 0x10 },
    { 0x2D, 0x8D },
    { 0x2E, 0x04 },
    { 0x2F, 0xC0 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//51538B5C240C8BC6 ...C20400
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_4__LTCG_esi1,
                      2040,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x14, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x51 },
    { 0x01, 0x53 },
    { 0x02, 0x8B },
    { 0x03, 0x5C },
    { 0x04, 0x24 },
    { 0x05, 0x0C },
    { 0x06, 0x8B },
    { 0x07, 0xC6 },

    { 0x12, 0x89 },
    { 0x18, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//8BCEC1E10681C1241B04 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor_4__LTCG_eax1,
                         2048)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x23, 0x8B },
    { 0x24, 0xCE },
    { 0x25, 0xC1 },
    { 0x26, 0xE1 },
    { 0x27, 0x06 },
    { 0x28, 0x81 },
    { 0x29, 0xC1 },
    { 0x2A, 0x24 },

    { 0x44, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
//C7000803040075
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      1049,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_CullMode],e??
    XREF_ENTRY(0x31, XREF_D3DRS_CullMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // unique
    // mov [eax],0x40308
    OV_MATCH(0x1F, 0xC7, 0x00, 0x08, 0x03, 0x04, 0x00),
    // jnz +0x??
    OV_MATCH(0x25, 0x75),
    //
);


// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
//A4030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x1F, 0xA4 },
    { 0x20, 0x03 },
    { 0x21, 0x04 },
    { 0x22, 0x00 },
    { 0x23, 0x89 },
    { 0x24, 0x48 },
    { 0x25, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
//C7000C0304008950
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x37, 0xC7 },
    { 0x38, 0x00 },
    { 0x39, 0x0C },
    { 0x3A, 0x03 },
    { 0x3B, 0x04 },
    { 0x3C, 0x00 },
    { 0x3D, 0x89 },
    { 0x3E, 0x50 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilEnable,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_StencilEnable],e??
    XREF_ENTRY(0x82, XREF_D3DRS_StencilEnable),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov [e?? + 0x8],0x4032C
    OV_MATCH(0x71, 0xC7),
    OV_MATCH(0x73, 0x08, 0x2C, 0x03, 0x04, 0x00),

    // mov [D3DRS_StencilEnable],e??
    OV_MATCH(0x80, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FillMode,
                      1036,
                      XRefThree)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1B, XREF_D3DRS_TwoSidedLighting),
    XREF_ENTRY(0x21, XREF_D3DRS_BackFillMode),
    XREF_ENTRY(0x42, XREF_D3DRS_FillMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    OV_MATCH(0x19, 0x8B),

    // mov edx,ptr [D3DRS_BackFillMode]
    OV_MATCH(0x1F, 0x8B),

    // mov ptr [eax],0x008038C
    OV_MATCH(0x2F, 0xC7, 0x00, 0x8C, 0x03, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x3B, 0x83, 0xC0, 0x0C),

    // mov ptr [D3DRS_FillMode],ecx
    OV_MATCH(0x40, 0x89),

    // retn 0x04
    OV_MATCH(0x47, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
//54240E8BF981
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x20, 0x54 },
    { 0x21, 0x24 },
    { 0x22, 0x0E },
    { 0x23, 0x8B },
    { 0x24, 0xF9 },
    { 0x25, 0x81 },
    //
);


// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
//6C1E04008D91
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },

    { 0x1F, 0x6C },
    { 0x20, 0x1E },
    { 0x21, 0x04 },
    { 0x22, 0x00 },
    { 0x23, 0x8D },
    { 0x24, 0x91 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
//0020030800894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         1036)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x1A, 0x4C },

    { 0x1E, 0x00 },
    { 0x1F, 0x20 },
    { 0x20, 0x03 },
    { 0x21, 0x08 },
    { 0x22, 0x00 },
    { 0x23, 0x89 },
    { 0x24, 0x48 },
    { 0x25, 0x04 },
    //
);

// ******************************************************************
// * D3DTexture_GetLevelDesc
// ******************************************************************
// * NOTE: We are actually intercepting Get2DSurfaceDesc, because
// *       GetLevelDesc Simply redirects to that function
// ******************************************************************
//7909C74608010000 ...C3
OOVPA_SIG_HEADER_NO_XREF(Get2DSurfaceDesc_0__LTCG_edi1_ebx2_esi3,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x0F },
    { 0x01, 0xB6 },

    { 0x2A, 0x79 },
    { 0x2B, 0x09 },
    { 0x2C, 0xC7 },
    { 0x2D, 0x46 },
    { 0x2E, 0x08 },
    { 0x2F, 0x01 },
    { 0x30, 0x00 },
    { 0x31, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_4__LTCG_eax1,
                         4039)
OOVPA_SIG_MATCH(
    // push ebx
    OV_MATCH(0x00, 0x53),

    // mov esi, param_1
    // mov eax, [e??]
    OV_MATCH(0x10, 0x8B, 0xF0, 0x8B),
    // cmp eax, ecx
    // jne +0x0B
    OV_MATCH(0x14, 0x3B, 0xC1, 0x72, 0x0B),

    // lea e??, [e?? * 0x04 + 0x40AE0] // 0x40AE0 is a reliable hardcoded value across all builds.
    OV_MATCH(0x23, 0x8D),
    OV_MATCH(0x26, 0xE0, 0x0A, 0x04, 0x00),

    // This is required OV pair to tell the difference from the (symbol)_4__LTCG_eax1_ebx2 signature.
    // retn 0x04
    OV_MATCH(0x40, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
//F6C30155568B35
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x12, XREF_D3DDevice__m_VertexShader_OFFSET), // Derived (unverified, yet should be align base on existing 4 bytes in signatures)

    { 0x00, 0x53 },
    { 0x01, 0x8B },
    { 0x02, 0x5C },
    { 0x03, 0x24 },
    { 0x04, 0x08 },
    { 0x05, 0xF6 },
    { 0x06, 0xC3 },
    { 0x07, 0x01 },
    { 0x08, 0x55 },
    { 0x09, 0x56 },
    { 0x0A, 0x8B },
    { 0x0B, 0x35 },
    //
);

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
//7505BB050000008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap,
                         1036)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x0E, 0x75 },
    { 0x0F, 0x05 },
    { 0x10, 0xBB },
    { 0x11, 0x05 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_IsFencePending
// ******************************************************************
//D12B4424043B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_IsFencePending,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0x8B },

    { 0x10, 0xD1 },
    { 0x11, 0x2B },
    { 0x12, 0x44 },
    { 0x13, 0x24 },
    { 0x14, 0x04 },
    { 0x15, 0x3B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_VertexBlend
// ******************************************************************
//81CA000200003BC1
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_VertexBlend,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x12, 0x81 },
    { 0x13, 0xCA },
    { 0x14, 0x00 },
    { 0x15, 0x02 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x3B },
    { 0x19, 0xC1 },
    //
);

//******************************************************************
//* D3DDevice_SetRenderState_TwoSidedLighting
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3DRS_FillMode]
    XREF_ENTRY(0x18, XREF_D3DRS_FillMode),

    // mov [D3DRS_TwoSidedLighting],e??
    XREF_ENTRY(0x1D, XREF_D3DRS_TwoSidedLighting),

    // mov e??,[0x????????]
    OV_MATCH(0x00, 0x8B),

    // mov e??,[esp + param_1]
    OV_MATCH(0x06, 0x8B),

    // mov e??,[D3DRS_FillMode]
    OV_MATCH(0x16, 0x8B),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_LogicOp,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_LogicOp],e??
    XREF_ENTRY(0x31, XREF_D3DRS_LogicOp),

    // push esi
    OV_MATCH(0x00, 0x56),

    // jnz +0x??
    OV_MATCH(0x1F, 0x75),
    // unique
    // mov [eax],0x417bc
    OV_MATCH(0x21, 0xC7, 0x00, 0xBC, 0x17, 0x04, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleMode,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_D3DRS_MultiSampleMode),

    { 0x00, 0x8B },
    { 0x15, 0x3B },
    //{ 0x16, 0x90 },
    //{ 0x17, 0x14 },
    //{ 0x18, 0x1A },
    { 0x19, 0x00 },
    { 0x1A, 0x00 },
    { 0x1B, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilFail,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_StencilFail],e??
    XREF_ENTRY(0x6B, XREF_D3DRS_StencilFail),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov [e?? + 0x8],0x40370
    OV_MATCH(0x5A, 0xC7),
    OV_MATCH(0x5C, 0x08, 0x70, 0x03, 0x04, 0x00),

    // mov [D3DRS_StencilFail],e??
    OV_MATCH(0x69, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FrontFace,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_FrontFace],e??
    XREF_ENTRY(0x2D, XREF_D3DRS_FrontFace),

    // push esi
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x56, 0x8B, 0x35),

    // add eax,0x08
    OV_MATCH(0x26, 0x83, 0xC0, 0x08),

    // mov [D3DRS_FrontFace],e??
    OV_MATCH(0x2B, 0x89),
    //
);

// ******************************************************************
// * D3D::CreateTexture
// ******************************************************************
// NOTE: Custom stdcall with params 1 - 7 pushed onto stack but has
//       param 8 as DL and param 9 as EDI registers.
// NOTE2: Can confirm NASCAR Heat 2002 (3925) does not use D3D_CreateTexture.
OOVPA_SIG_HEADER_NO_XREF(D3D_CreateTexture_28__LTCG_dl8_edi9,
                         4039)
OOVPA_SIG_MATCH(

    // push ebx
    // push esi
    // lea e??,[esp + 0x20]
    OV_MATCH(0x00, 0x53, 0x56, 0x8D),

    // unique instruction
    // and [esp + 0x24],0xFFFFFFF7
    OV_MATCH(0x41, 0x83, 0x64, 0x24, 0x24, 0xF7),
    // push 0x14
    OV_MATCH(0x46, 0x6A, 0x14),
    // push 0x40
    OV_MATCH(0x48, 0x6A, 0x40),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//0F85..0100008B0D
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderTarget,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4F, XREF_D3DRS_MultiSampleMode),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x3C },

    { 0x47, 0x0F },
    { 0x48, 0x85 },
    //{ 0x49, 0x65 },
    { 0x4A, 0x01 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },
    { 0x4D, 0x8B },
    { 0x4E, 0x0D },

    { 0x53, 0x8B },
    //
);

//******************************************************************
//* D3DSurface_GetDesc
//******************************************************************
//578B7C241033DBE8
OOVPA_SIG_HEADER_NO_XREF(D3DSurface_GetDesc,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x06, 0x57 },
    { 0x07, 0x8B },
    { 0x08, 0x7C },
    { 0x09, 0x24 },
    { 0x0A, 0x10 },
    { 0x0B, 0x33 },
    { 0x0C, 0xDB },
    { 0x0D, 0xE8 },
    //
);

//******************************************************************
//* Lock2DSurface
//******************************************************************
//2418F6C320558B ...C21000
OOVPA_SIG_HEADER_NO_XREF(Lock2DSurface_16__LTCG_esi4_eax5,
                         2048)
OOVPA_SIG_MATCH(

    { 0x01, 0x53 },
    { 0x04, 0x24 },
    { 0x05, 0x18 },
    { 0x06, 0xF6 },
    { 0x07, 0xC3 },
    { 0x08, 0x20 },
    { 0x09, 0x55 },
    { 0x0A, 0x8B },
    //
);

//******************************************************************
//* Lock3DSurface
//******************************************************************
//83EC08538A5C241CF6C32055 ...C21000
OOVPA_SIG_HEADER_NO_XREF(Lock3DSurface_16__LTCG_eax4,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x53 },
    { 0x04, 0x8A },
    { 0x05, 0x5C },
    { 0x06, 0x24 },
    { 0x07, 0x1C },
    { 0x08, 0xF6 },
    { 0x09, 0xC3 },
    { 0x0A, 0x20 },
    { 0x0B, 0x55 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader_0__LTCG_eax1,
                         2072)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x6B, 0xC7 },
    { 0x6C, 0x40 },
    { 0x6D, 0x04 },
    { 0x6E, 0x00 },
    { 0x6F, 0x00 },
    { 0x70, 0x21 },
    { 0x71, 0x00 },
    { 0x72, 0x83 },
    { 0x73, 0xC0 },
    { 0x74, 0x08 },

    { 0x79, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_DeletePixelShader
// ******************************************************************
//FF08750D8B480485C9740650E8 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeletePixelShader_0__LTCG_eax1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0xFF },
    { 0x01, 0x08 },
    { 0x02, 0x75 },
    { 0x03, 0x0D },
    { 0x04, 0x8B },
    { 0x05, 0x48 },
    { 0x06, 0x04 },
    { 0x07, 0x85 },
    { 0x08, 0xC9 },
    { 0x09, 0x74 },
    { 0x0A, 0x06 },
    { 0x0B, 0x50 },
    { 0x0C, 0xE8 },

    { 0x10, 0xFF },
    { 0x11, 0xC3 },
    //
);

// ******************************************************************
// * D3DResource_GetType
// ******************************************************************
//3D00000300772274 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DResource_GetType_0__LTCG_ecx1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x01 },

    { 0x07, 0x3D },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x03 },
    { 0x0B, 0x00 },
    { 0x0C, 0x77 },
    { 0x0D, 0x22 },
    { 0x0E, 0x74 },

    { 0x0F, 0x1A },
    //
);

// ******************************************************************
// * D3D_BlockOnResource
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource_0__LTCG_ecx1,
                         4039)
OOVPA_SIG_MATCH(
    // mov esi, [D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov edx, param_1
    OV_MATCH(0x0B, 0x8B, 0x11),

    // test edx, 0x780000
    OV_MATCH(0x22, 0xF7, 0xC2, 0x00, 0x00, 0x78, 0x00),
    // jnz +0x??
    OV_MATCH(0x28, 0x75),
    //
);

// ******************************************************************
// * D3D_BlockOnResource
// ******************************************************************
// TODO: Lowest build detected is 4627, find if any other titles are
//       detected by this signature or missing detection.
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource_0__LTCG_eax1,
                         4039)
OOVPA_SIG_MATCH(
    // mov esi, [D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov edx, param_1
    OV_MATCH(0x0B, 0x8B, 0x10),

    // test edx, 0x780000
    OV_MATCH(0x24, 0xF7, 0xC2, 0x00, 0x00, 0x78, 0x00),
    // jnz +0x??
    OV_MATCH(0x2A, 0x75),
    //
);

// ******************************************************************
// * D3DDevice_Begin
// ******************************************************************
//814E08000800005EC204
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Begin,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x30, 0x81 },
    { 0x31, 0x4E },
    { 0x32, 0x08 },
    { 0x33, 0x00 },
    { 0x34, 0x08 },
    { 0x35, 0x00 },
    { 0x36, 0x00 },
    { 0x37, 0x5E },
    { 0x38, 0xC2 },
    { 0x39, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackBuffer
// ******************************************************************
//7507B801000000EB07F7 ...C20800
OOVPA_SIG_HEADER_XREF(D3DDevice_GetBackBuffer_8__LTCG_eax1,
                      2048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e?x, [D3D_g_pDevice]
    XREF_ENTRY(0x05, XREF_D3D_g_pDevice),

    // call D3DResource::AddRef
    XREF_ENTRY(0x45, XREF_D3DResource_AddRef),

    // cmp eax,0x??
    OV_MATCH(0x00, 0x83, 0xF8),

    // jnz +0x07
    OV_MATCH(0x09, 0x75, 0x07),
    // mov eax,0x1
    OV_MATCH(0x0B, 0xB8, 0x01, 0x00, 0x00, 0x00),
    // jmp +0x07
    OV_MATCH(0x10, 0xEB, 0x07),
    // neg e?x
    OV_MATCH(0x12, 0xF7),

    // retn 0x08
    OV_MATCH(0x4C, 0xC2, 0x08),
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2s
// ******************************************************************
//8D....00190400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData2s,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x1D, 0x8D },
    //{ 0x21, 0x14 },
    //{ 0x22, 0x8D },
    { 0x20, 0x00 },
    { 0x21, 0x19 },
    { 0x22, 0x04 },
    { 0x23, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2f
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexData2f,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // lea e??,[e?? * 8 + 0x00081880]
    OV_MATCH(0x1D, 0x8D),
    OV_MATCH(0x20, 0x80, 0x18, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x34, 0x83, 0xC0, 0x0C),

    // retn 0x0C
    OV_MATCH(0x3A, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4f
// ******************************************************************
//B918150000EB09 ...C21000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4f_16__LTCG_edi1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x1E, 0xB9 },
    { 0x1F, 0x18 },
    { 0x20, 0x15 },
    { 0x21, 0x00 },
    { 0x22, 0x00 },
    { 0x23, 0xEB },
    { 0x24, 0x09 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4s
// ******************************************************************
//801908000FBF
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4s,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x20, 0x80 },
    { 0x21, 0x19 },
    { 0x22, 0x08 },
    { 0x23, 0x00 },
    { 0x24, 0x0F },
    { 0x25, 0xBF },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4ub
// ******************************************************************
//8D....4019040033
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4ub,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x1D, 0x8D },

    { 0x20, 0x40 },
    { 0x21, 0x19 },
    { 0x22, 0x04 },
    { 0x23, 0x00 },
    { 0x24, 0x33 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexDataColor
// ******************************************************************
// TODO: Need verify with 4034 titles.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexDataColor,
                      4038, // Due to non-LTCG signature conflict, lowered down by one offset.
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x08, XREF_D3D_g_pDevice),

    // push esi
    // mov esi,[esp + param_2]
    OV_MATCH(0x00, 0x56, 0x8B, 0x74, 0x24, 0x0C),
    // push edi
    // mov edi,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x57, 0x8B, 0x3D),

    // mov eax,[edi]
    // cmp eax[edi + 0x04]
    OV_MATCH(0x0C, 0x8B, 0x07, 0x3B, 0x47, 0x04),
    // jc +0x??
    OV_MATCH(0x11, 0x72),

    // mov eax,0x????????
    OV_MATCH(0x13, 0xA1)
    // Offset 0x18 and later has changed
);

// ******************************************************************
// * D3D::SetFence
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x24, 0xC9 },
    { 0x25, 0x89 },
    { 0x26, 0x48 },
    { 0x27, 0x0C },
    { 0x28, 0x89 },
    { 0x29, 0x48 },
    { 0x2A, 0x14 },
    { 0x2B, 0xC7 },
    //
);

// ******************************************************************
// * D3DDevice_MultiplyTransform
// ******************************************************************
//558BEC83E4F081EC8800000056578BF0 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_MultiplyTransform_0__LTCG_ebx1_eax2,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xE4 },
    { 0x05, 0xF0 },
    { 0x06, 0x81 },
    { 0x07, 0xEC },
    { 0x08, 0x88 },
    { 0x09, 0x00 },
    { 0x0A, 0x00 },
    { 0x0B, 0x00 },
    { 0x0C, 0x56 },
    { 0x0D, 0x57 },
    { 0x0E, 0x8B },
    { 0x0F, 0xF0 },
    { 0x10, 0xB9 },
    { 0x11, 0x10 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x8D },
    { 0x16, 0x7C },
    //
);

// ******************************************************************
// * D3DDevice_SetIndices
// ******************************************************************
//74108103000008008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetIndices,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

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
// * D3DDevice_SetStreamSource
// ******************************************************************
//7406810300000800 ...C20800
OOVPA_SIG_HEADER_XREF(D3DDevice_SetStreamSource_8__LTCG_eax1,
                      2040,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x23, XREF_D3D_g_Stream_i_pVertexBuffer), // Derived
    XREF_ENTRY(0x53, XREF_D3D_g_Stream), // Derived

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x13, 0x74 },
    { 0x14, 0x06 },
    { 0x15, 0x81 },
    { 0x16, 0x03 },
    { 0x17, 0x00 },
    { 0x18, 0x00 },
    { 0x19, 0x08 },
    { 0x1A, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderInput
// ******************************************************************
//8B44240483EC4085C0538B1D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderInput,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x83 },
    { 0x05, 0xEC },
    { 0x06, 0x40 },
    { 0x07, 0x85 },
    { 0x08, 0xC0 },
    { 0x09, 0x53 },
    { 0x0A, 0x8B },
    { 0x0B, 0x1D },

    { 0x1A, 0x25 },
    { 0x1B, 0xFF },
    { 0x1C, 0xFF },
    { 0x1D, 0xFF },
    { 0x1E, 0xBF },
    { 0x1F, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
//F64401680175 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LightEnable_4__LTCG_eax1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x21, 0xF6 },
    { 0x22, 0x44 },
    { 0x23, 0x01 },
    { 0x24, 0x68 },
    { 0x25, 0x01 },
    { 0x26, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//C700B402040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x72, 0xC7 },
    { 0x73, 0x00 },
    { 0x74, 0xB4 },
    { 0x75, 0x02 },
    { 0x76, 0x04 },
    { 0x77, 0x00 },
    //
);

//******************************************************************
//* D3DDevice_DrawVerticesUP
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVerticesUP,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x09, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x11, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x07, 0x8B, 0x35),

    // mov [ebp - 0x14],e??
    OV_MATCH(0x0D, 0x89),
    OV_MATCH(0x0F, 0xEC), // D3DDevice_DrawVerticesUP 0xEC vs D3DDevice_DrawIndexedVerticesUP 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x10, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVerticesUP,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x09, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x11, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x07, 0x8B, 0x35),

    // mov [ebp - 0x14],e??
    OV_MATCH(0x0D, 0x89),
    OV_MATCH(0x0F, 0xF8), // D3DDevice_DrawVerticesUP 0xEC vs D3DDevice_DrawIndexedVerticesUP 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x10, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_LoadVertexShader
// ******************************************************************
//C7009C1E0400894804 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_4__LTCG_eax1,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x50, 0xC7 },
    { 0x51, 0x00 },
    { 0x52, 0x9C },
    { 0x53, 0x1E },
    { 0x54, 0x04 },
    { 0x55, 0x00 },
    { 0x56, 0x89 },
    { 0x57, 0x48 },
    { 0x58, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_LoadVertexShaderProgram
// ******************************************************************
//18C7009C1E0400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShaderProgram,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x54 },

    { 0x62, 0x18 },
    { 0x63, 0xC7 },
    { 0x64, 0x00 },
    { 0x65, 0x9C },
    { 0x66, 0x1E },
    { 0x67, 0x04 },
    { 0x68, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVertices
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVertices_8__LTCG_eax3,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebp,[D3D_g_pDevice]
    XREF_ENTRY(0x08, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x14, XREF_D3D_CDevice_SetStateVB),

    // push ebx
    // mov ebx,[esp + param_2]
    OV_MATCH(0x00, 0x53, 0x8B, 0x5C, 0x24, 0x0C),
    // push ebp
    // mov ebp,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x55, 0x8B, 0x2D),

    // push 0x0
    // push ebp
    OV_MATCH(0x0E, 0x6A, 0x00, 0x55),
    // mov edi,param_3
    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x11, 0x8B, 0xF8, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderStateInline__GenericFragment
// ******************************************************************
// Generic OOVPA as of 4039? and newer.
// NOTE: This signature will find any generic match with D3D_g_RenderState
//       Currently, this is the best method if
//       D3DDevice_SetRenderStateNotInline detection is absent.
//       This OOVPA itself is not a symbol.
// NOTE: Unknown if any titles build before 4039 with sig been detected.
//       Due to lack of titles compiled as LTCG in 4039 and earlier builds.
//       All titles from 4039 and later always detect 4039 sig.
OOVPA_SIG_HEADER_XREF_DETECT(D3DDevice_SetRenderStateInline__GenericFragment,
                             4039,
                             XRefTwo,
                             DetectFirst)
OOVPA_SIG_MATCH(
    // call D3DDevice_SetRenderState_Simple
    XREF_ENTRY(0x0F, XREF_D3DDevice_SetRenderState_Simple),
    XREF_ENTRY(0x16, XREF_D3D_g_RenderState),

    // cmp esi,0x?? // Up until < 4242 is 0x52; 4432 & 4531 = 0x53; 4627+ = 0x5C
    OV_MATCH(0x00, 0x83, 0xFE),
    // jge +0x??
    OV_MATCH(0x03, 0x7D),

    // mov ecx,ptr [esi * 4 + ????]
    OV_MATCH(0x05, 0x8B, 0x0C, 0xB5),

    // mov edx,edi
    OV_MATCH(0x0C, 0x8B, 0xD7),
    // call D3DDevice_SetRenderState_Simple
    OV_MATCH(0x0E, 0xE8),

    // mov ptr [esi * 4 + D3D_g_RenderState],edi
    OV_MATCH(0x13, 0x89, 0x3C, 0xB5),
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateVB
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateVB_8,
                         4039)
OOVPA_SIG_MATCH(

    // sub esp,0x08
    OV_MATCH(0x00, 0x83, 0xEC, 0x08),

    // mov e??,[0x????????]
    OV_MATCH(0x4, 0x8B),
    // mov e??,e??
    OV_MATCH(0xA, 0x8B),

    // unique
    // and eax,0xFFFFFFAF
    OV_MATCH(0xC, 0x83, 0xE0, 0xAF),
    // test ebx,0x3FFFFF8F
    OV_MATCH(0x0F, 0xF7, 0xC3, 0x8F, 0xFF, 0xFF, 0x3F),
    //
);

// ******************************************************************
// * D3DDevice_BeginVisibilityTest
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginVisibilityTest,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x56, 0x8B, 0x35),

    // mov [eax],0x000817C8
    OV_MATCH(0x19, 0xC7, 0x00, 0xC8, 0x17, 0x08, 0x00),
    // mov ecx,1
    OV_MATCH(0x1F, 0xB9, 0x01, 0x00),

    // add eax,0x0C
    OV_MATCH(0x2A, 0x83, 0xC0, 0x0C),

    // ret
    OV_MATCH(0x30, 0xC3),
    //
);

//******************************************************************
//* D3DDevice_SetTile
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTile_0__LTCG_ebx1_eax2,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov edx,[D3D_g_pDevice]
    XREF_ENTRY(0x06, XREF_D3D_g_pDevice),

    // sub esp,0x18
    OV_MATCH(0x00, 0x83, 0xEC, 0x18),

    // mov ebp,[D3D_g_pDevice]
    OV_MATCH(0x04, 0x8B, 0x2D),

    // mov esi,eax(param_2)
    OV_MATCH(0x0B, 0x8B, 0xF0),

    // mov [esp + 0x20],edx
    OV_MATCH(0x2C, 0x89, 0x54, 0x24, 0x20),
    // mov [esp + 0x1C],edx
    OV_MATCH(0x30, 0x89, 0x54, 0x24, 0x1C),
    //
);

// ******************************************************************
// * D3DDevice_SetTextureStageStateNotInline
// ******************************************************************
OOVPA_SIG_HEADER_XREF_DETECT(D3DDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_ecx3,
                             4039,
                             XRefOne,
                             DetectFirst)
OOVPA_SIG_MATCH(

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    XREF_ENTRY(0x23, XREF_D3D_g_DeferredTextureState),

    // cmp edx(param_2),0x??
    OV_MATCH(0x00, 0x83, 0xFA),

    // shl eax(param_1),0x05
    OV_MATCH(0x18, 0xC1, 0xE0, 0x05),

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    OV_MATCH(0x20, 0x89),

    // ret
    OV_MATCH(0x2E, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SetTextureStageStateNotInline
// ******************************************************************
// NOTE: Signature is exactly the same as above but is failed to find
//       in different xbe's section.
OOVPA_SIG_HEADER_XREF_DETECT(D3DDevice_SetTextureStageStateNotInline2_0__LTCG_eax1_edx2_ecx3,
                             4039,
                             XRefOne,
                             DetectSecond)
OOVPA_SIG_MATCH(

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    XREF_ENTRY(0x23, XREF_D3D_g_DeferredTextureState),

    // cmp edx(param_2),0x??
    OV_MATCH(0x00, 0x83, 0xFA),

    // shl eax(param_1),0x05
    OV_MATCH(0x18, 0xC1, 0xE0, 0x05),

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    OV_MATCH(0x20, 0x89),

    // ret
    OV_MATCH(0x2E, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice::SetTextureStageStateNotInline
// ******************************************************************
// NOTE: has return 0 (xor eax)
OOVPA_SIG_HEADER_XREF(D3D_CDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_ecx3,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    XREF_ENTRY(0x22, XREF_D3D_g_DeferredTextureState),

    // cmp edx(param_2),0x??
    OV_MATCH(0x00, 0x83, 0xFA),

    // shl eax(param_1),0x05
    OV_MATCH(0x18, 0xC1, 0xE0, 0x05),

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    OV_MATCH(0x1F, 0x89),

    // ret
    OV_MATCH(0x30, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_CreateTexture
// ******************************************************************
// NOTE: param 6 is unused.
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateTexture_8__LTCG_edx3_ecx4_eax5_edi7,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call D3D::CreateTexture
    XREF_ENTRY(0x14, XREF_D3D_CreateTexture),

    // push 0x0
    // push param_5
    OV_MATCH(0x00, 0x6A, 0x00, 0x50),

    // push param_4
    OV_MATCH(0x07, 0x51),
    // push param_2
    // OV_MATCH(0x08, 0x51),

    // push param_3
    // push 0x1
    OV_MATCH(0x0C, 0x52, 0x6A, 0x01),

    // xor dl,dl
    // call D3D::CreateTexture
    OV_MATCH(0x11, 0x32, 0xD2, 0xE8),
    // ret 0xC
    OV_MATCH(0x18, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * D3DDevice_CreateVolumeTexture
// ******************************************************************
// NOTE: param 7 is unused.
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateVolumeTexture_12__LTCG_edx4_ecx5_eax6_edi8,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call D3D::CreateTexture
    XREF_ENTRY(0x17, XREF_D3D_CreateTexture),

    // push 0x0
    // push param_6
    OV_MATCH(0x00, 0x6A, 0x00, 0x50),

    // push param_5
    OV_MATCH(0x07, 0x51),

    // push param_4
    OV_MATCH(0x0C, 0x52),

    // mov edx,0x01
    // call D3D::CreateTexture
    OV_MATCH(0x14, 0xB2, 0x01, 0xE8),
    // ret 0x8
    OV_MATCH(0x1B, 0xC2, 0x10),
    //
);

// ******************************************************************
// * D3DDevice_CreateCubeTexture
// ******************************************************************
// NOTE: param 5 is unused.
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateCubeTexture_4__LTCG_eax1_edx3_ecx4_edi6,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call D3D::CreateTexture
    XREF_ENTRY(0x10, XREF_D3D_CreateTexture),

    // push 0x1
    // push param_4
    OV_MATCH(0x00, 0x6A, 0x01, 0x51),

    // push param_3
    OV_MATCH(0x07, 0x52),
    // push param_2
    //OV_MATCH(0x08, 0x51),

    // push 0x1
    // push param_1
    // push param_1
    OV_MATCH(0x09, 0x6A, 0x01, 0x50, 0x50),
    // xor dl,dl
    // call D3D::CreateTexture
    OV_MATCH(0x0D, 0x32, 0xD2, 0xE8),
    // ret 0x8
    OV_MATCH(0x14, 0xC2, 0x08),
    //
);

//******************************************************************
//* D3DDevice_SelectVertexShader
//******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_4__LTCG_eax1,
                         4039)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x4C, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),
    // mov [eax + 0x4],0x6
    OV_MATCH(0x52, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x4B, 0x00, 0x00),

    // lea ecx,[eax + 0xC]
    OV_MATCH(0x5C, 0x8D, 0x48, 0x0C),

    // ret 0x4
    OV_MATCH(0x92, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateUP
// ******************************************************************
// revision 0
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateUP_0__LTCG_esi1,
                         4039)
OOVPA_SIG_MATCH(

    // mov eax,[0x????????]
    OV_MATCH(0x00, 0xA1),
    // sub esp,0x14
    OV_MATCH(0x5, 0x83, 0xEC, 0x14),
    // test eax,0x3FFFFF8F
    OV_MATCH(0x08, 0xA9, 0x8F, 0xFF, 0xFF, 0x3F),

    // call ????????
    OV_MATCH(0x0F, 0xE8),

    // jz 0x???????? // required to separate difference with LTCG version
    OV_MATCH(0x1B, 0x0F, 0x84),
    // mov ecx,[esi + 0x4]
    OV_MATCH(0x21, 0x8B, 0x4E, 0x04),
    // and eax,0xFFFFFFDF
    // or eax,0x50
    OV_MATCH(0x24, 0x83, 0xE0, 0xDF, 0x83, 0xC8, 0x50),
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateUP
// ******************************************************************
// revision 1
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateUP_0__LTCG_esi1,
                         4040)
OOVPA_SIG_MATCH(

    // mov eax,[0x????????]
    OV_MATCH(0x00, 0xA1),
    // sub esp,0x14
    OV_MATCH(0x5, 0x83, 0xEC, 0x14),
    // test eax,0x3FFFFF8F
    OV_MATCH(0x08, 0xA9, 0x8F, 0xFF, 0xFF, 0x3F),

    // jz 0x???????? // required to separate difference with LTCG version
    OV_MATCH(0x1B, 0x0F, 0x84),
    // and eax,0xFFFFFFDF
    // or eax,0x50
    OV_MATCH(0x21, 0x83, 0xE0, 0xDF, 0x83, 0xC8, 0x50),

    // mov ecx,[esi + 0x4]
    OV_MATCH(0x32, 0x8B, 0x4E, 0x04),
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
// Generic OOVPA as of 4039 and newer
// NOTE: Only found in NBA 2K2 title (4039) so far.
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_4__LTCG_esi1,
                         4039)
OOVPA_SIG_MATCH(
    // sub esp, 0x??
    OV_MATCH(0x00, 0x83, 0xEC),

    // jc +4
    // mov [esp + 0x??], eax
    OV_MATCH(0x18, 0x72, 0x04, 0x89, 0x44, 0x24),

    // mov e??, [e?? + 0x08]
    // call ????
    OV_MATCH(0x1E, 0x8B),
    OV_MATCH(0x20, 0x08, 0xE8),

    // mov e??, [e?? + 0x24]
    OV_MATCH(0x2A, 0x8B),
    OV_MATCH(0x2C, 0x24),

    // [esi + 0x????], eax
    OV_MATCH(0x4E, 0x89, 0x86),

    // Unknown what offset range may be reliable, unlike other LTCG variants.
    // For now, we'll rely on the instruction at offset 0x4E until another update is needed.
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset_0__LTCG_edi1,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x35, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // TODO: Add range 0 to 1 offset at 0x32 (in summary, offset 0x32 - 0x33)
    // jnz +0x??
    OV_MATCH(0x32, 0x75), // Offset 4039 0x32 vs 4041-ish 0x33

    // TODO: Add range 0 to 1 offset at 0x34 (in summary, offset 0x34 - 0x36, including above range)
    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x34, 0xE8), // Offset 4039 0x34 vs 4040-ish 0x35 vs 4041-ish 0x36 (the same for below)
    // push param_1
    OV_MATCH(0x39, 0x57),
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
// NOTE: Lowest detected was 4627 except very similar to 4039 signature.
// TODO: Migrate this signature into 4039 with offset shift range by one.
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset_0__LTCG_edi1,
                      4040,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x36, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // jnz +0x??
    OV_MATCH(0x32, 0x75),

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x35, 0xE8),
    // push param_1
    OV_MATCH(0x3A, 0x57),
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
// NOTE: Earliest found is 4928 build.
// TODO: Migrate this signature into 4040-ish with offset shift range by one.
//       See TODOs in 4039 signature for range difference.
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset_0__LTCG_edi1,
                      4041,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x37, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // jnz +0x??
    OV_MATCH(0x33, 0x75), // Offset 4041-ish 0x33 vs 4039 0x32 (the same for below)

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x36, 0xE8),

    // push param_1
    OV_MATCH(0x3B, 0x57),
    //
);
