// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3D_SetFence
// ******************************************************************
//460457720EA1
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x0D, 0x8B },

    { 0x10, 0x46 },
    { 0x11, 0x04 },
    { 0x12, 0x57 },
    { 0x13, 0x72 },
    { 0x14, 0x0E },
    { 0x15, 0xA1 },
    //
);

// ******************************************************************
// * Direct3D_CreateDevice
// ******************************************************************
//00000800A1
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x06, 0xC0 },

    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0x08 },
    { 0x12, 0x00 },
    { 0x13, 0xA1 },
    //
);

// ******************************************************************
// * D3DDevice_SetStreamSource
// ******************************************************************
//7406810300000800
OOVPA_SIG_HEADER_XREF(D3DDevice_SetStreamSource,
                      1044,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x22, XREF_D3D_g_Stream_i_pVertexBuffer), // Derived
    XREF_ENTRY(0x52, XREF_D3D_g_Stream), // Derived

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x0E, 0x74 },
    { 0x0F, 0x06 },
    { 0x10, 0x81 },
    { 0x11, 0x03 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x08 },
    { 0x15, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//8BC3C1E007578B3D
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex,
                      1944,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x53 },
    { 0x02, 0x5C },

    { 0x0B, 0x8B },
    { 0x0C, 0xC3 },
    { 0x0D, 0xC1 },
    { 0x0E, 0xE0 },
    { 0x0F, 0x07 },
    { 0x10, 0x57 },
    { 0x11, 0x8B },
    { 0x12, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
//C7000803040075
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      1052,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_CullMode],e??
    XREF_ENTRY(0x34, XREF_D3DRS_CullMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // unique
    // mov [eax],0x40308
    OV_MATCH(0x22, 0xC7, 0x00, 0x08, 0x03, 0x04, 0x00),
    // jnz +0x??
    OV_MATCH(0x28, 0x75),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
//A4030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x22, 0xA4 },
    { 0x23, 0x03 },
    { 0x24, 0x04 },
    { 0x25, 0x00 },
    { 0x26, 0x89 },
    { 0x27, 0x48 },
    { 0x28, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
//C9C7000C0304008948048B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x36, 0xC9 },
    { 0x37, 0xC7 },
    { 0x38, 0x00 },
    { 0x39, 0x0C },
    { 0x3A, 0x03 },
    { 0x3B, 0x04 },
    { 0x3C, 0x00 },
    { 0x3D, 0x89 },
    { 0x3E, 0x48 },
    { 0x3F, 0x04 },
    { 0x40, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilEnable,
                      1048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_StencilEnable],e??
    XREF_ENTRY(0x85, XREF_D3DRS_StencilEnable),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov [e?? + 0x8],0x4032C
    OV_MATCH(0x74, 0xC7),
    OV_MATCH(0x76, 0x08, 0x2C, 0x03, 0x04, 0x00),

    // mov [D3DRS_StencilEnable],e??
    OV_MATCH(0x83, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FillMode,
                      1048,
                      XRefThree)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1E, XREF_D3DRS_TwoSidedLighting),
    XREF_ENTRY(0x24, XREF_D3DRS_BackFillMode),
    XREF_ENTRY(0x45, XREF_D3DRS_FillMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    OV_MATCH(0x1C, 0x8B),

    // mov edx,ptr [D3DRS_BackFillMode]
    OV_MATCH(0x22, 0x8B),

    // mov ptr [eax],0x008038C
    OV_MATCH(0x32, 0xC7, 0x00, 0x8C, 0x03, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x3E, 0x83, 0xC0, 0x0C),

    // mov ptr [D3DRS_FillMode],ecx
    OV_MATCH(0x43, 0x89),

    // retn 0x04
    OV_MATCH(0x4A, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
//54240E8BF981
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x23, 0x54 },
    { 0x24, 0x24 },
    { 0x25, 0x0E },
    { 0x26, 0x8B },
    { 0x27, 0xF9 },
    { 0x28, 0x81 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
//6C1E04008D91
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },

    { 0x22, 0x6C },
    { 0x23, 0x1E },
    { 0x24, 0x04 },
    { 0x25, 0x00 },
    { 0x26, 0x8D },
    { 0x27, 0x91 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
//0020030800894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x1D, 0x4C },

    { 0x21, 0x00 },
    { 0x22, 0x20 },
    { 0x23, 0x03 },
    { 0x24, 0x08 },
    { 0x25, 0x00 },
    { 0x26, 0x89 },
    { 0x27, 0x48 },
    { 0x28, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor,
                         4432)
OOVPA_SIG_MATCH(
    // push esi
    OV_MATCH(0x00, 0x56),

    // mov eax, [e??]
    OV_MATCH(0x07, 0x8B),
    // cmp eax, [esi + 0x04]
    // jne +0x0E
    OV_MATCH(0x09, 0x3B, 0x46, 0x04, 0x72, 0x0E),

    // mov e??, [esp + param_1]
    OV_MATCH(0x1C, 0x8B),
    OV_MATCH(0x1E, 0x24, 0x08),
    // lea e??, [e?? * 0x04 + 0x40AE0] // 0x40AE0 is a reliable hardcoded value across all builds.
    OV_MATCH(0x20, 0x8D),
    OV_MATCH(0x23, 0xE0, 0x0A, 0x04, 0x00),

    // mov e??, [esp + param_2]
    OV_MATCH(0x29, 0x8B),
    OV_MATCH(0x2B, 0x24, 0x0C),

    // This is an optional OV pair to tell the difference from the (symbol)_(LTCG variant) signature.
    // retn 0x08
    OV_MATCH(0x3F, 0xC2, 0x08),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_VertexBlend
// ******************************************************************
//81CA00020000568B35
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_VertexBlend,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x06, 0x81 },
    { 0x07, 0xCA },
    { 0x08, 0x00 },
    { 0x09, 0x02 },
    { 0x0A, 0x00 },
    { 0x0B, 0x00 },
    { 0x0C, 0x56 },
    { 0x0D, 0x8B },
    { 0x0E, 0x35 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_LogicOp,
                      1048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_LogicOp],e??
    XREF_ENTRY(0x34, XREF_D3DRS_LogicOp),

    // push esi
    OV_MATCH(0x00, 0x56),

    // jnz +0x??
    OV_MATCH(0x22, 0x75),
    // unique
    // mov [eax],0x417bc
    OV_MATCH(0x24, 0xC7, 0x00, 0xBC, 0x17, 0x04, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilFail,
                      1048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_StencilFail],e??
    XREF_ENTRY(0x6E, XREF_D3DRS_StencilFail),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov [e?? + 0x8],0x40370
    OV_MATCH(0x5D, 0xC7),
    OV_MATCH(0x5F, 0x08, 0x70, 0x03, 0x04, 0x00),

    // mov [D3DRS_StencilFail],e??
    OV_MATCH(0x6C, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FrontFace,
                      1048,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_FrontFace],e??
    XREF_ENTRY(0x35, XREF_D3DRS_FrontFace),

    // push esi
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x56, 0x8B, 0x35),

    // add eax,0x08
    OV_MATCH(0x29, 0x83, 0xC0, 0x08),

    // mov [D3DRS_FrontFace],e??
    OV_MATCH(0x33, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_CreateTexture
// ******************************************************************
//206A00508B44241451
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x10, 0x20 },
    { 0x11, 0x6A },
    { 0x12, 0x00 },
    { 0x13, 0x50 },
    { 0x14, 0x8B },
    { 0x15, 0x44 },
    { 0x16, 0x24 },
    { 0x17, 0x14 },
    { 0x18, 0x51 },

    { 0x29, 0x5F },
    { 0x2A, 0xC2 },
    { 0x2B, 0x1C },
    //
);

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
//816608FFE7FFFF5EC3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_End,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x3D, 0x81 },
    { 0x3E, 0x66 },
    { 0x3F, 0x08 },
    { 0x40, 0xFF },
    { 0x41, 0xE7 },
    { 0x42, 0xFF },
    { 0x43, 0xFF },
    { 0x44, 0x5E },
    { 0x45, 0xC3 },
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
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x0F },
    { 0x01, 0xB6 },

    { 0x29, 0x79 },
    { 0x2A, 0x09 },
    { 0x2B, 0xC7 },
    { 0x2C, 0x46 },
    { 0x2D, 0x08 },
    { 0x2E, 0x01 },
    { 0x2F, 0x00 },
    { 0x30, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetShaderConstantMode
// ******************************************************************
//8B442404A810538B1D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetShaderConstantMode,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0xA8 },
    { 0x05, 0x10 },
    { 0x06, 0x53 },
    { 0x07, 0x8B },
    { 0x08, 0x1D },

    { 0x1F, 0xFF },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
//F6C30155568B35
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_D3DDevice__m_VertexShader_OFFSET), // Derived (OK, yet unverified)

    { 0x00, 0x51 },
    { 0x01, 0x53 },
    { 0x02, 0x8B },
    { 0x03, 0x5C },
    { 0x04, 0x24 },
    { 0x05, 0x0C },
    { 0x06, 0xF6 },
    { 0x07, 0xC3 },
    { 0x08, 0x01 },
    { 0x09, 0x55 },
    { 0x0A, 0x56 },
    { 0x0B, 0x8B },
    { 0x0C, 0x35 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant
// ******************************************************************
//83C160C1E202A810
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x14, 0x83 },
    { 0x15, 0xC1 },
    { 0x16, 0x60 },
    { 0x17, 0xC1 },
    { 0x18, 0xE2 },
    { 0x19, 0x02 },
    { 0x1A, 0xA8 },
    { 0x1B, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVertices
// ******************************************************************
// TODO: May could lower this down to 3911 since it is more or less
//       identical to non-LTCG sig (3911).
//       Or better yet, migrate into non-LTCG sig (3911)
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVertices,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x0D, XREF_D3D_CDevice_SetStateVB),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53, 0x8B, 0x1D),

    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x0C, 0xE8),
    // mov edi,[esp + param_3]
    OV_MATCH(0x11, 0x8B, 0x7C, 0x24, 0x18),
    //
);

// ******************************************************************
// * D3DDevice_Clear
// ******************************************************************
//FFFDFFFF8944
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Clear,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x40, 0xFF },
    { 0x41, 0xFD },
    { 0x42, 0xFF },
    { 0x43, 0xFF },
    { 0x44, 0x89 },
    { 0x45, 0x44 },
    //
);

// ******************************************************************
// * D3DDevice_GetDepthStencilSurface
// ******************************************************************
//B866087688..C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetDepthStencilSurface,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x40, 0xB8 },
    { 0x41, 0x66 },
    { 0x42, 0x08 },
    { 0x43, 0x76 },
    { 0x44, 0x88 },

    { 0x46, 0xC2 },
    { 0x47, 0x04 },
    { 0x48, 0x00 },
    //
);

//******************************************************************
//* D3DDevice_SetTile
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTile_0__LTCG_ecx1_eax2,
                      4432,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov edx,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // sub esp,0x18
    OV_MATCH(0x00, 0x83, 0xEC, 0x18),

    // mov ebp,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B, 0x2D),

    // mov esi,eax(param_2)
    OV_MATCH(0x0C, 0x8B, 0xF0),

    // mov ebx,ecx(param_1)
    OV_MATCH(0x13, 0x8B, 0xD9),

    // mov [esp + 0x24],edx
    OV_MATCH(0x2F, 0x89, 0x54, 0x24, 0x24),
    // mov [esp + 0x20],edx
    OV_MATCH(0x33, 0x89, 0x54, 0x24, 0x20),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//5533ED3BD5565775
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTarget,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x54 },

    { 0x0E, 0x55 },
    { 0x0F, 0x33 },
    { 0x10, 0xED },
    { 0x11, 0x3B },
    { 0x12, 0xD5 },
    { 0x13, 0x56 },
    { 0x14, 0x57 },
    { 0x15, 0x75 },
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShader
//******************************************************************
//C7009C1E040089 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_0__LTCG_ecx1_eax2,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },

    { 0x59, 0xC7 },
    { 0x5A, 0x00 },
    { 0x5B, 0x9C },
    { 0x5C, 0x1E },
    { 0x5D, 0x04 },
    { 0x5E, 0x00 },
    { 0x5F, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2f
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexData2f,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // lea e??,[e?? * 8 + 0x00081880]
    OV_MATCH(0x20, 0x8D),
    OV_MATCH(0x23, 0x80, 0x18, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x37, 0x83, 0xC0, 0x0C),

    // retn 0x0C
    OV_MATCH(0x3D, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4f
// ******************************************************************
//B918150000EB09
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4f,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x25, 0xB9 },
    { 0x26, 0x18 },
    { 0x27, 0x15 },
    { 0x28, 0x00 },
    { 0x29, 0x00 },
    { 0x2A, 0xEB },
    { 0x2B, 0x09 },
    //
);

// ******************************************************************
// * D3DCubeTexture_GetCubeMapSurface
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DCubeTexture_GetCubeMapSurface,
                         1024)
OOVPA_SIG_MATCH(

    // sub esp,8
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
    OV_MATCH(0x44, 0xE8),

    // add esp,8
    OV_MATCH(0x4A, 0x83, 0xC4, 0x08),
    // retn 0x10
    OV_MATCH(0x4D, 0xC2, 0x10),
    //
);

// ******************************************************************
// * D3DResource_GetType
// ******************************************************************
//7728741E85C0
OOVPA_SIG_HEADER_NO_XREF(D3DResource_GetType,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x4C },

    { 0x10, 0x77 },
    { 0x11, 0x28 },
    { 0x12, 0x74 },
    { 0x13, 0x1E },
    { 0x14, 0x85 },
    { 0x15, 0xC0 },
    //
);

// ******************************************************************
// * D3DDevice_Begin
// ******************************************************************
//814E08000800005EC204
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Begin,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x33, 0x81 },
    { 0x34, 0x4E },
    { 0x35, 0x08 },
    { 0x36, 0x00 },
    { 0x37, 0x08 },
    { 0x38, 0x00 },
    { 0x39, 0x00 },
    { 0x3A, 0x5E },
    { 0x3B, 0xC2 },
    { 0x3C, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShaderConstant
// ******************************************************************
//44242085C08974240C894C24
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShaderConstant,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x14, 0x44 },
    { 0x15, 0x24 },
    { 0x16, 0x20 },
    { 0x17, 0x85 },
    { 0x18, 0xC0 },
    { 0x19, 0x89 },
    { 0x1A, 0x74 },
    { 0x1B, 0x24 },
    { 0x1C, 0x0C },
    { 0x1D, 0x89 },
    { 0x1E, 0x4C },
    { 0x1F, 0x24 },
    //
);

// ******************************************************************
// * D3DDevice_GetViewportOffsetAndScale_0
// ******************************************************************
//000085F6577D06D805 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetViewportOffsetAndScale_0__LTCG_edx1_ecx2,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0xDB },

    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x85 },
    { 0x16, 0xF6 },
    { 0x17, 0x57 },
    { 0x18, 0x7D },
    { 0x19, 0x06 },
    { 0x1A, 0xD8 },
    { 0x1B, 0x05 },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//C700B402040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1072)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x74, 0xC7 },
    { 0x75, 0x00 },
    { 0x76, 0xB4 },
    { 0x77, 0x02 },
    { 0x78, 0x04 },
    { 0x79, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0__LTCG_eax1_ebx2,
                         2024)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x3D, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),

    // mov [eax + 0x4],0x6
    OV_MATCH(0x46, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x4B, 0x00, 0x00),

    // add eax,0xC
    OV_MATCH(0x50, 0x83, 0xC0, 0x0C),

    // pop esi
    // ret
    OV_MATCH(0x84, 0x5E, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
//008107000008008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginPushBuffer,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x48, 0x00 },
    { 0x49, 0x81 },
    { 0x4A, 0x07 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },
    { 0x4D, 0x08 },
    { 0x4E, 0x00 },
    { 0x4F, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_EndPushBuffer
// ******************************************************************
// TODO: Maybe move this signature to 3911? Last found was 4432.
OOVPA_SIG_HEADER_XREF(D3DDevice_EndPushBuffer,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x04, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x0D, XREF_D3D_CDevice_SetStateVB),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x02, 0x8B),

    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x0C, 0xE8),

    // and edx,0xFFFFFF7B
    OV_MATCH(0x4C, 0x81, 0xE2, 0x7B, 0xFF, 0xFF, 0xFF),

    // test eax,0x78FFFF
    OV_MATCH(0x62, 0xA9, 0xFF, 0xFF, 0x78, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
//81E1FFFFFF0F4189 ...C20800
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x90, 0x81 },
    { 0x91, 0xE1 },
    { 0x92, 0xFF },
    { 0x93, 0xFF },
    { 0x94, 0xFF },
    { 0x95, 0x0F },
    { 0x96, 0x41 },
    { 0x97, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
//85C0740F50FF15
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_PersistDisplay,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x53 },

    { 0x2F, 0xB8 },
    { 0x30, 0x05 },
    { 0x31, 0x40 },
    { 0x32, 0x00 },
    { 0x33, 0x80 },
    { 0x34, 0x5B },
    { 0x35, 0x59 },
    { 0x36, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetGammaRamp
// ******************************************************************
//C78498DC07000001000000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetGammaRamp,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x2E, 0x8B },
    { 0x2F, 0xFB },
    { 0x30, 0xF3 },
    { 0x31, 0xA5 },
    { 0x32, 0xF6 },
    { 0x33, 0x44 },
    { 0x34, 0x24 },
    { 0x35, 0x10 },
    { 0x36, 0x02 },
    { 0x37, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureStageStateNotInline
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_ecx1_eax2_edx3,
                      4432,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    XREF_ENTRY(0x25, XREF_D3D_g_DeferredTextureState),

    // cmp eax(param_2),0x??
    OV_MATCH(0x00, 0x83, 0xF8),

    // shl ecx(param_1),0x05
    OV_MATCH(0x16, 0xC1, 0xE1, 0x05),

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    OV_MATCH(0x22, 0x89),

    // ret
    OV_MATCH(0x2A, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_CreateCubeTexture
// ******************************************************************
// TODO: Might be possible to move it early as 4039 since this function
//       is compatible with D3D::CreateTexture's 4039 LTCG signature.
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateCubeTexture,
                      4432,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call D3D::CreateTexture
    XREF_ENTRY(0x21, XREF_D3D_CreateTexture),

    // mov eax,[esp + param_4]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x10),

    // push 0x1
    // push param_4
    OV_MATCH(0x11, 0x6A, 0x01, 0x50),

    // push param_3
    OV_MATCH(0x18, 0x51),
    // push param_2
    // OV_MATCH(0x19, 0x52),

    // push 0x1
    // push param_1
    // push param_1
    OV_MATCH(0x1A, 0x6A, 0x01, 0x50, 0x50),
    // xor dl,dl
    // call D3D::CreateTexture
    OV_MATCH(0x1E, 0x32, 0xD2, 0xE8),
    // ret 0x18
    OV_MATCH(0x26, 0xC2, 0x18),
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
// stdcall (LTCG)
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_4,
                         4432)
OOVPA_SIG_MATCH(
    // mov eax, [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // test ch, 0x20
    OV_MATCH(0x07, 0xF6, 0xC5, 0x20),

    // or ecx, 0x2000
    OV_MATCH(0xB6, 0x81, 0xC9, 0x00, 0x20, 0x00, 0x00), // unique

    // ret 0x04
    OV_MATCH(0xC1, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3D::CDevice::FreeFrameBuffers
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDevice_FreeFrameBuffers_4,
                      4432,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call [AvGetSavedDataAddress]
    XREF_ENTRY(0x08, XREF_KT_FUNC_AvGetSavedDataAddress),
    // NOTE: AvSendTVEncoderOption call occurs at different offsets in various titles.

    // This is a requirement to separate detection vs CDevice_FreeFrameBuffers_0__LTCG_ebx1 (4034)
    // mov e??, [esp + param_1]
    OV_MATCH(0x01, 0x8B),
    OV_MATCH(0x03, 0x24, 0x08),

    // call [AvGetSavedDataAddress]
    OV_MATCH(0x06, 0xFF, 0x15), // Offset 4432 0x06 vs 4433-ish 0x07 (the same for below)

    // jz +0x20
    // mov ecx, [eax + 0x14]
    OV_MATCH(0x2E, 0x74, 0x20, 0x8B, 0x48, 0x14),

    // call ????
    OV_MATCH(0x6F, 0xE8), // Offset 4432 0x69 vs 4433-ish 0x68 (the same for below)
    // mov [ebp + 0x????], e??
    OV_MATCH(0x74, 0x89),

    // cmp [ebp + 0x????], e??
    OV_MATCH(0x7A, 0x39),
    //
);

// ******************************************************************
// * D3D::CDevice::FreeFrameBuffers
// ******************************************************************
// TODO: Migrate this signature into 4432 with offset shift range by one.
// Found in "Call of Cthulhu: Dark Corners of the Earth" title (5849)
// Yet all other 5849 title builds do match CDevice_FreeFrameBuffers_4 4432's signature.
OOVPA_SIG_HEADER_XREF(CDevice_FreeFrameBuffers_4,
                      4433,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call [AvGetSavedDataAddress]
    XREF_ENTRY(0x09, XREF_KT_FUNC_AvGetSavedDataAddress),
    // NOTE: AvSendTVEncoderOption call occurs at different offsets in various titles.

    // mov e??, [esp + param_1]
    OV_MATCH(0x01, 0x8B),
    OV_MATCH(0x03, 0x24, 0x08),

    // call [AvGetSavedDataAddress]
    OV_MATCH(0x07, 0xFF, 0x15), // Offset 4433-ish 0x07 vs 4432 0x06

    // jz +0x20
    // mov ecx, [eax + 0x14]
    OV_MATCH(0x2D, 0x74, 0x20, 0x8B, 0x48, 0x14),

    // call ????
    OV_MATCH(0x6E, 0xE8), // Offset 4433-ish 0x68 vs 4432 0x69 (the same for below)
    // mov [ebp + 0x????], e??
    OV_MATCH(0x73, 0x89),

    // cmp [ebp + 0x????], e??
    OV_MATCH(0x79, 0x39),
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_4__LTCG_ebx1,
                         4432)
OOVPA_SIG_MATCH(
    // mov edx, [esp + param_2]
    OV_MATCH(0x00, 0x8B, 0x54, 0x24, 0x04),

    // mov e??, [e?? + 0x08]
    OV_MATCH(0x17, 0x8B),
    OV_MATCH(0x19, 0x08),

    // mov e??, [e?? + 0x24]
    OV_MATCH(0x27, 0x8B),
    OV_MATCH(0x29, 0x24),

    // Possible start at offset 0x141 - 0x17B to use one signature rather than multiple
    // add eax, 0x18
    // dec ecx
    OV_MATCH(0x161, 0x83, 0xC0, 0x18, 0x49), // offset 4432 0x161 vs 4433 0x160

    // lea eax, [ebx + 0x????]
    OV_MATCH(0x176, 0x8D, 0x83), // offset 4432 0x176 vs 4433 0x175
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
// TODO: Migrate this signature into 4432 with offset shift range by one.
// Only detected in Sega GT 2002 (4627)
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_4__LTCG_ebx1,
                         4433)
OOVPA_SIG_MATCH(
    // mov edx, [esp + param_2]
    OV_MATCH(0x00, 0x8B, 0x54, 0x24, 0x04),

    // mov e??, [e?? + 0x08]
    OV_MATCH(0x17, 0x8B),
    OV_MATCH(0x19, 0x08),

    // mov e??, [e?? + 0x24]
    OV_MATCH(0x27, 0x8B),
    OV_MATCH(0x29, 0x24),

    // Possible start at offset 0x140 - 0x17A to use one signature rather than multiple
    // add eax, 0x18
    // dec ecx
    OV_MATCH(0x160, 0x83, 0xC0, 0x18, 0x49), // offset 4433 0x160 vs 4432 0x161

    // lea eax, [ebx + 0x????]
    OV_MATCH(0x175, 0x8D, 0x83), // offset 4433 0x175 vs 4432 0x176
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset,
                      4432,
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
    // mov edi, [esp + param_1]
    OV_MATCH(0x3A, 0x8B),
    OV_MATCH(0x3C, 0x24, 0x14),
    //
);
