// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * Direct3D_CreateDevice
// ******************************************************************
//85C9750AC705 ...C21000
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice_16__LTCG_eax4_ebx6,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    { 0x06, 0x85 },
    { 0x07, 0xC9 },
    { 0x08, 0x75 },
    { 0x09, 0x0A },
    { 0x0A, 0xC7 },
    { 0x0B, 0x05 },

    { 0x28, 0x56 },
    { 0x29, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
//C7000803040075
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      1045,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_CullMode],e??
    XREF_ENTRY(0x2D, XREF_D3DRS_CullMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // unique
    // mov [eax],0x40308
    OV_MATCH(0x1B, 0xC7, 0x00, 0x08, 0x03, 0x04, 0x00),
    // jnz +0x??
    OV_MATCH(0x21, 0x75),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_VertexBlend
// ******************************************************************
//C70028030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_VertexBlend,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x24, 0xC7 },
    { 0x25, 0x00 },
    { 0x26, 0x28 },
    { 0x27, 0x03 },
    { 0x28, 0x04 },
    { 0x29, 0x00 },
    { 0x2A, 0x89 },
    { 0x2B, 0x48 },
    { 0x2C, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BumpEnv
// ******************************************************************
//000085C08BDF75 ...C20800
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BumpEnv_8__LTCG_eax1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0x85 },
    { 0x17, 0xC0 },
    { 0x18, 0x8B },
    { 0x19, 0xDF },
    { 0x1A, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
//C9C7000C03040089480483
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x2F, 0xC9 },
    { 0x30, 0xC7 },
    { 0x31, 0x00 },
    { 0x32, 0x0C },
    { 0x33, 0x03 },
    { 0x34, 0x04 },
    { 0x35, 0x00 },
    { 0x36, 0x89 },
    { 0x37, 0x48 },
    { 0x38, 0x04 },
    { 0x39, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TextureFactor
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TextureFactor,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x08, 0x86 },
    //{ 0x09, 0x84 },
    //{ 0x0A, 0x07 },
    { 0x0B, 0x00 },
    { 0x0C, 0x00 },
    { 0x0D, 0x85 },
    { 0x0E, 0xC0 },
    { 0x0F, 0x75 },

    { 0x11, 0x8B },
    { 0x12, 0x06 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//538BD9C1E107 ...C3
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_0__LTCG_edi1_eax2,
                      2039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x08, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x53 },
    { 0x01, 0x8B },
    { 0x02, 0xD9 },
    { 0x03, 0xC1 },
    { 0x04, 0xE1 },
    { 0x05, 0x07 },

    { 0x13, 0x25 },
    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0xFF },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//C1..0681..241B040089 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor_0__LTCG_eax1_ebx2,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x1C, 0xC1 },
    { 0x1D, 0xE1 },
    { 0x1E, 0x06 },
    { 0x1F, 0x81 },
    { 0x20, 0xC1 },
    { 0x21, 0x24 },
    { 0x22, 0x1B },
    { 0x23, 0x04 },
    { 0x24, 0x00 },
    { 0x25, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_0__LTCG_eax1_ebx2,
                         3911)
OOVPA_SIG_MATCH(

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov edi, param_1
    // mov eax, [e??]
    OV_MATCH(0x0B, 0x8B, 0xF8, 0x8B),
    // cmp eax, ecx
    // jne +0x07
    OV_MATCH(0x0F, 0x3B, 0xC1, 0x72, 0x07),

    // lea e??, [e?? * 0x04 + 0x40AE0] // 0x40AE0 is a reliable hardcoded value across all builds.
    OV_MATCH(0x1A, 0x8D),
    OV_MATCH(0x1D, 0xE0, 0x0A, 0x04, 0x00),

    // This is required OV pair to tell the difference from the (symbol)_4__LTCG_eax1 signature.
    // ret
    OV_MATCH(0x36, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZBias
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZBias,
                         1024)
OOVPA_SIG_MATCH(
    // push ecx
    // push ebx // non-LTCG does not have this instruction
    // push esi
    OV_MATCH(0x00, 0x51, 0x53, 0x56),

    // setnz al
    OV_MATCH(0x0C, 0x0F, 0x95, 0xC0),

    // fild [esp + param_1]
    OV_MATCH(0x15, 0xDB, 0x44, 0x24, 0x14),

    // jge +0x06
    OV_MATCH(0x1B, 0x7D, 0x06),
    // fadd [0x????????]
    OV_MATCH(0x1D, 0xD8, 0x05),
    // NOTE: fchs instruction is moved to different offset
    // Source: (4928) The Fellowship of the Ring
);

// ******************************************************************
// * D3DDevice_SetRenderState_LineWidth
// ******************************************************************
//44240C57D88E
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_LineWidth,
                         1024)
OOVPA_SIG_MATCH(


    // XREF_ENTRY( 0x5B, XREF_D3DRS_LineWidth ),

    { 0x02, 0x5C },

    { 0x11, 0x44 },
    { 0x12, 0x24 },
    { 0x13, 0x0C },
    { 0x14, 0x57 },
    { 0x15, 0xD8 },
    { 0x16, 0x8E },
    //
);

//******************************************************************
//* D3DDevice_SetRenderState_BackFillMode
//******************************************************************
// Found in 4039 title "NBA 2K2"
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_BackFillMode,
                      1024,
                      XRefThree)
OOVPA_SIG_MATCH(

    // mov ecx,ptr [D3DRS_FillMode]
    XREF_ENTRY(0x06, XREF_D3DRS_FillMode),
    // mov [D3DRS_BackFillMode],eax
    XREF_ENTRY(0x0B, XREF_D3DRS_BackFillMode),
    // jmp D3DDevice_SetRenderState_FillMode
    XREF_ENTRY(0x14, XREF_D3DDevice_SetRenderState_FillMode),

    // mov eax,ptr [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov ecx,ptr [D3DRS_FillMode]
    OV_MATCH(0x04, 0x8B, 0x0D),

    // mov [D3DRS_BackFillMode],eax
    OV_MATCH(0x0A, 0xA3),
    // mov ptr [esp + param_1],ecx
    OV_MATCH(0x0F, 0x89, 0x4C, 0x24, 0x04),
    // jmp D3DDevice_SetRenderState_FillMode
    OV_MATCH(0x13, 0xE9)
    //
);

//******************************************************************
//* D3DDevice_SetRenderState_BackFillMode
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_BackFillMode,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov [D3DRS_BackFillMode],eax
    XREF_ENTRY(0x0C, XREF_D3DRS_BackFillMode),
    // mov edi,ptr [D3DRS_FillMode]
    XREF_ENTRY(0x18, XREF_D3DRS_FillMode),

    // mov eax,ptr [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov [D3DRS_BackFillMode],eax
    OV_MATCH(0x0B, 0xA3),

    // mov eax,ptr [esi]
    OV_MATCH(0x10, 0x8B, 0x06),
    // cmp eax,ptr [esi + 0x4]
    OV_MATCH(0x12, 0x3B, 0x46, 0x04),
    // push edi
    OV_MATCH(0x15, 0x57),
    // mov edi,ptr [D3DRS_FillMode]
    OV_MATCH(0x16, 0x8B, 0x3D),
    // Generic support over multiple revisions end at offset 0x1C
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
//0020030800894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x12, 0x4C },

    { 0x1A, 0x00 },
    { 0x1B, 0x20 },
    { 0x1C, 0x03 },
    { 0x1D, 0x08 },
    { 0x1E, 0x00 },
    { 0x1F, 0x89 },
    { 0x20, 0x48 },
    { 0x21, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FillMode,
                      1024,
                      XRefThree)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x17, XREF_D3DRS_TwoSidedLighting),
    XREF_ENTRY(0x1D, XREF_D3DRS_BackFillMode),
    XREF_ENTRY(0x3E, XREF_D3DRS_FillMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    OV_MATCH(0x15, 0x8B),

    // mov edx,ptr [D3DRS_BackFillMode]
    OV_MATCH(0x1B, 0x8B),

    // mov ptr [eax],0x008038C
    OV_MATCH(0x2B, 0xC7, 0x00, 0x8C, 0x03, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x37, 0x83, 0xC0, 0x0C),

    // mov ptr [D3DRS_FillMode],ecx
    OV_MATCH(0x3C, 0x89),

    // retn 0x04
    OV_MATCH(0x43, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
//54240E8BF981
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x1C, 0x54 },
    { 0x1D, 0x24 },
    { 0x1E, 0x0E },
    { 0x1F, 0x8B },
    { 0x20, 0xF9 },
    { 0x21, 0x81 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleAntiAlias
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleAntiAlias,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // mov [D3DRS_MultiSampleAntiAlias],eax
    XREF_ENTRY(0x0C, XREF_D3DRS_MultiSampleAntiAlias),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B, 0x35),

    // mov [D3DRS_MultiSampleAntiAlias],eax
    OV_MATCH(0x0B, 0xA3), // 3911 (non-LTCG) 0x0D vs 0x0B
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleMask
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleMask,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // mov [D3DRS_MultiSampleMask],eax
    XREF_ENTRY(0x0C, XREF_D3DRS_MultiSampleMask),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B, 0x35),

    // mov [D3DRS_MultiSampleMask],eax
    OV_MATCH(0x0B, 0xA3), // 3911 (non-LTCG) 0x0D vs 0x0B
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_LogicOp,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_LogicOp],e??
    XREF_ENTRY(0x2D, XREF_D3DRS_LogicOp),

    // push esi
    OV_MATCH(0x00, 0x56),

    // jnz +0x??
    OV_MATCH(0x1B, 0x75),
    // unique
    // mov [eax],0x417bc
    OV_MATCH(0x1D, 0xC7, 0x00, 0xBC, 0x17, 0x04, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
//A4030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x1B, 0xA4 },
    { 0x1C, 0x03 },
    { 0x1D, 0x04 },
    { 0x1E, 0x00 },
    { 0x1F, 0x89 },
    { 0x20, 0x48 },
    { 0x21, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilFail,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_StencilFail],e??
    XREF_ENTRY(0x67, XREF_D3DRS_StencilFail),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov [e?? + 0x8],0x40370
    OV_MATCH(0x56, 0xC7),
    OV_MATCH(0x58, 0x08, 0x70, 0x03, 0x04, 0x00),

    // mov [D3DRS_StencilFail],e??
    OV_MATCH(0x65, 0x89),
    //
);

//******************************************************************
//* D3DDevice_SetRenderState_TwoSidedLighting
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // mov [D3DRS_TwoSidedLighting],eax
    XREF_ENTRY(0x15, XREF_D3DRS_TwoSidedLighting),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // mov e??,[esp + param_1]
    OV_MATCH(0x09, 0x8B),

    // mov [D3DRS_TwoSidedLighting],eax
    OV_MATCH(0x14, 0xA3),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FrontFace,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_FrontFace],e??
    XREF_ENTRY(0x2E, XREF_D3DRS_FrontFace),

    // push esi
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x56, 0x8B, 0x35),

    // add eax,0x08
    OV_MATCH(0x22, 0x83, 0xC0, 0x08),

    // mov [D3DRS_FrontFace],e??
    OV_MATCH(0x2C, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
//6C1E04008D91
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },

    { 0x1B, 0x6C },
    { 0x1C, 0x1E },
    { 0x1D, 0x04 },
    { 0x1E, 0x00 },
    { 0x1F, 0x8D },
    { 0x20, 0x91 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilEnable,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // mov [D3DRS_StencilEnable],e??
    XREF_ENTRY(0x7E, XREF_D3DRS_StencilEnable),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov [e?? + 0x8],0x4032C
    OV_MATCH(0x6D, 0xC7),
    OV_MATCH(0x6F, 0x08, 0x2C, 0x03, 0x04, 0x00),

    // mov [D3DRS_StencilEnable],e??
    OV_MATCH(0x7C, 0x89),
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexShader
// ******************************************************************
//241833f685ed
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateVertexShader,
                         1024)
OOVPA_SIG_MATCH(

    { 0x04, 0x6C },
    { 0x0C, 0x0F },
    { 0x1A, 0x24 },
    { 0x1B, 0x18 },
    { 0x1C, 0x33 },
    { 0x1D, 0xF6 },
    { 0x1E, 0x85 },
    { 0x1F, 0xED },
    //
);

// ******************************************************************
// * D3DDevice_SetShaderConstantMode
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetShaderConstantMode_0__LTCG_eax1,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x05, XREF_D3D_g_pDevice),

    // test al,0x10
    OV_MATCH(0x00, 0xA8, 0x10),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B, 0x1D),

    // or ecx,0x200
    OV_MATCH(0x0E, 0x81, 0xC9, 0x00, 0x02, 0x00, 0x00),

    // mov ???,???
    OV_MATCH(0x2E, 0x8B), // Unique OV to determine if function is LTCG.
    // Offset 0x2F and later had change over time.
);

// ******************************************************************
// * D3DDevice_Clear
// ******************************************************************
//FFFDFFFF8944
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Clear,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x42, 0xFF },
    { 0x43, 0xFD },
    { 0x44, 0xFF },
    { 0x45, 0xFF },
    { 0x46, 0x89 },
    { 0x47, 0x44 },
    //
);

// ******************************************************************
// * D3DResource_Release
// ******************************************************************
//578B7C24088B078BC881E1FFFF0000
OOVPA_SIG_HEADER_NO_XREF(D3DResource_Release,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x57 },
    { 0x01, 0x8B },
    { 0x02, 0x7C },
    { 0x03, 0x24 },
    { 0x04, 0x08 },
    { 0x05, 0x8B },
    { 0x06, 0x07 },
    { 0x07, 0x8B },
    { 0x08, 0xC8 },
    { 0x09, 0x81 },
    { 0x0A, 0xE1 },
    { 0x0B, 0xFF },
    { 0x0C, 0xFF },
    { 0x0D, 0x00 },
    { 0x0E, 0x00 },
    //
);

//******************************************************************
//* D3DDevice_SetTile
//******************************************************************
// NOTE: Only very few titles with 4627 or later build triggered
//       this detection which is the same as
//       D3D_SetTileNoWait_0__LTCG_eax1_ecx2 (2024) signature
//       with early ret shifted by one offset.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTile_0__LTCG_eax1_ecx2,
                      3911,
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

    // NOTE: Required separate difference to avoid detect 4627+
    //       build titles.
    // add esp,0x18
    // ret
    OV_MATCH(0x80, 0x83, 0xC4, 0x18, 0xC3), // offset 0x80 vs 2024 0x80
    //
);

// ******************************************************************
// * D3DDevice_Present
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Present,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x56 },
    { 0x04, 0x8B },
    { 0x05, 0x35 },

    { 0x0B, 0x6A },
    { 0x0C, 0x02 },
    { 0x0D, 0xE8 },
    { 0x12, 0x8B },
    { 0x13, 0x86 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x8B },
    { 0x19, 0x8E },
    { 0x1C, 0x00 },
    { 0x1D, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVerticesUP,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x0B, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x14, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov edi,[D3D_g_pDevice]
    OV_MATCH(0x09, 0x8B, 0x3D),

    // mov [ebp - 0x8],e??
    OV_MATCH(0x10, 0x89),
    OV_MATCH(0x12, 0xF8), // D3DDevice_DrawIndexedVerticesUP 0xF8 vs D3DDevice_DrawVerticesUP 0xFC
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x13, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVertices
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVertices,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x09, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x19, XREF_D3D_CDevice_SetStateVB),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x08
    OV_MATCH(0x03, 0x83, 0xEC, 0x08),

    // push esi
    OV_MATCH(0x06, 0x56),
    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x07, 0x8B),
    // mov e??,[e?? + 0x????????]
    OV_MATCH(0x0D, 0x8B),

    // mov [ebp - 8],esi
    OV_MATCH(0x15, 0x89, 0x75, 0xF8),
    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x18, 0xE8),
    // Do not use any offsets after 0x1C
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
//F6C30155568B35 ...C3
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader_0__LTCG_ebx1,
                      2024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0D, XREF_D3DDevice__m_VertexShader_OFFSET), // Derived (confirmed)

    { 0x00, 0xF6 },
    { 0x01, 0xC3 },
    { 0x02, 0x01 },
    { 0x03, 0x55 },
    { 0x04, 0x56 },
    { 0x05, 0x8B },
    { 0x06, 0x35 },

    { 0x15, 0x74 },
    { 0x16, 0x05 },
    { 0x17, 0x8D },
    { 0x18, 0x7B },
    { 0x19, 0xFF },
    { 0x1A, 0xEB },
    { 0x1B, 0x0E },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//75448B..000B00008B..080B00008B..040B0000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x13, 0x75 },
    { 0x14, 0x44 },
    { 0x15, 0x8B },
    { 0x17, 0x00 },
    { 0x18, 0x0B },
    { 0x19, 0x00 },
    { 0x1A, 0x00 },
    { 0x1B, 0x8B },
    { 0x1D, 0x08 },
    { 0x1E, 0x0B },
    { 0x1F, 0x00 },
    { 0x20, 0x00 },
    { 0x21, 0x8B },
    { 0x23, 0x04 },
    { 0x24, 0x0B },
    { 0x25, 0x00 },
    { 0x26, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    // TODO: Need to fix 3925 to able detect function below
    XREF_ENTRY(0xEB, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // lea edi, [param_1 + 0x22]
    OV_MATCH(0x09, 0x8D, 0x78, 0x22), // 3911 0x22 vs 5344 0x21 value
    // shl edi,0x6
    OV_MATCH(0x0C, 0xC1, 0xE7, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x11, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xEA, 0xE8),

    // ret
    OV_MATCH(0xF9, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant
// ******************************************************************
//83C160C1E202A810 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant_8__LTCG_edx3,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x13, 0x83 },
    { 0x14, 0xC1 },
    { 0x15, 0x60 },
    { 0x16, 0xC1 },
    { 0x17, 0xE2 },
    { 0x18, 0x02 },
    { 0x19, 0xA8 },
    { 0x1A, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVerticesUP_12__LTCG_ebx3,
                      2024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x13, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov edi,[D3D_g_pDevice]
    OV_MATCH(0x08, 0x8B, 0x3D),

    // mov [ebp - 0x4],e??
    OV_MATCH(0x0F, 0x89),
    OV_MATCH(0x11, 0xFC), // D3DDevice_DrawVerticesUP 0xFC vs D3DDevice_DrawIndexedVerticesUP 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x12, 0xE8),

    // mov e??,[ebp + param_1]
    OV_MATCH(0x25, 0x8B),
    OV_MATCH(0x27, 0x08),
    // mov e??,[ebp + param_4]
    OV_MATCH(0x28, 0x8B),
    OV_MATCH(0x2A, 0x10),
    // difference from non-LTCG, there is identical mov instruction from two above but is absent.
    // mov [e?? + 0x??,e??
    OV_MATCH(0x2B, 0x89),
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShader
//******************************************************************
//C7009C1E04008B ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_0__LTCG_ecx1_eax2,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x3F, 0xC7 },
    { 0x40, 0x00 },
    { 0x41, 0x9C },
    { 0x42, 0x1E },
    { 0x43, 0x04 },
    { 0x44, 0x00 },
    { 0x45, 0x8B },
    //
);

//******************************************************************
//* D3DDevice_SelectVertexShader
//******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_4__LTCG_eax1,
                         3911)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x40, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),
    // mov [eax + 0x4],0x6
    OV_MATCH(0x46, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x4B, 0x00, 0x00),
    // add eax,0xC
    OV_MATCH(0x4D, 0x83, 0xC0, 0x0C),

    // ret 0x4
    OV_MATCH(0x7B, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_DeleteVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeleteVertexShader_0__LTCG_eax1,
                         3911)
OOVPA_SIG_MATCH(

    // mov ecx,[eax + -0x1]
    OV_MATCH(0x00, 0x8B, 0x48, 0xFF),
    // dec eax
    // dec ecx
    OV_MATCH(0x03, 0x48, 0x49),
    // mov [eax],ecx
    OV_MATCH(0x05, 0x89, 0x08),
    // jnz
    OV_MATCH(0x07, 0x75, 0x06),

    // call LocalFree
    OV_MATCH(0x0A, 0xE8),

    OV_MATCH(0x0F, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 1024, 11)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget,
           1024,
           1 + 11,
           XRefOne)
{

    XREF_ENTRY(0x17, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0x20
        OV_MATCH(0x00, 0x83, 0xEC),

            // D3DDevice_SetRenderTarget+0x4A : mov eax, 0x00000001
            OV_MATCH(0x4A, 0xB8, 0x01, 0x00),

            // D3DDevice_SetRenderTarget+0x4F : and ecx, 0x0F
            OV_MATCH(0x4F, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0x56 : shr eax,0x0C
            OV_MATCH(0x56, 0xC1, 0xE8, 0x0C),
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//EB06894424088BF8
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x25, 0xEB },
    { 0x26, 0x06 },
    { 0x27, 0x89 },
    { 0x28, 0x44 },
    { 0x29, 0x24 },
    { 0x2A, 0x08 },
    { 0x2B, 0x8B },
    { 0x2C, 0xF8 },
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
//81C10000F8FF89 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTexture_4__LTCG_eax2,
                         2024)
OOVPA_SIG_MATCH(

    // sub esp, ...
    OV_MATCH(0x00, 0x83, 0xEC),

    // mov esi, eax
    OV_MATCH(0x1A, 0x8B, 0xF0),

    // add ecx, 0FFF80000h; mov ...
    OV_MATCH(0x27, 0x81, 0xC1, 0x00, 0x00, 0xF8, 0xFF, 0x89),
    //
);

// ******************************************************************
// * D3D_BlockOnResource
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource_0__LTCG_eax1,
                         3911)
OOVPA_SIG_MATCH(
    // mov edx, [D3D_g_pDevice]
    OV_MATCH(0x00, 0x8B, 0x15),

    // mov esi, param_1
    OV_MATCH(0x09, 0x8B, 0xF0),

    // test ecx, 0x780000
    OV_MATCH(0x28, 0xF7, 0xC1, 0x00, 0x00, 0x78, 0x00),
    // jnz +0x0C
    // test e??, e??
    OV_MATCH(0x2E, 0x75, 0x0C, 0x085),
    //
);

// ******************************************************************
// * D3DDevice_SetStreamSource
// ******************************************************************
//7406810300000800
OOVPA_SIG_HEADER_XREF(D3DDevice_SetStreamSource_8__LTCG_edx1,
                      2039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x47, XREF_D3D_g_Stream_i_pVertexBuffer), // Derived
    XREF_ENTRY(0x77, XREF_D3D_g_Stream), // Derived

    { 0x00, 0x53 },
    { 0x01, 0x8B },
    { 0x02, 0x1D },

    { 0x38, 0x81 },
    { 0x39, 0x45 },
    { 0x3A, 0x00 },
    { 0x3B, 0x00 },
    { 0x3C, 0x00 },
    { 0x3D, 0x08 },
    { 0x3E, 0x00 },
    { 0x3F, 0x8D },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader_0__LTCG_eax1,
                         2060)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x5C, 0xC7 },
    { 0x5D, 0x40 },
    { 0x5E, 0x04 },
    { 0x5F, 0x00 },
    { 0x60, 0x00 },
    { 0x61, 0x21 },
    { 0x62, 0x00 },
    { 0x63, 0x83 },
    { 0x64, 0xC0 },
    { 0x65, 0x08 },

    { 0x6A, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_BlockUntilVerticalBlank
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
// NOTE: Later XDK version start to use std signature.
// NOTE: NASCAR Heat 2002 reveal this function is inlined, need some sort of indicator which is inline or not.
OOVPA_SIG_HEADER_XREF(D3DDevice_BlockUntilVerticalBlank,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // D3DDevice_BlockUntilVerticalBlank+0x00 : mov eax, [D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // D3DDevice_BlockUntilVerticalBlank+0x17 : add eax, OFFSET_D3DDevice__m_VerticalBlankEvent
    XREF_ENTRY(0x18, XREF_D3DDevice__m_VerticalBlankEvent_OFFSET),

    // D3DDevice_BlockUntilVerticalBlank+0x00 : mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // D3DDevice_BlockUntilVerticalBlank+0x05 : push 0; push 0; push 1
    OV_MATCH(0x05, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x01),

    // D3DDevice_BlockUntilVerticalBlank+0x0B : mov dword ptr [eax+OFFSET_D3DDEVICE_M_???],
    OV_MATCH(0x0B, 0xC7, 0x80),

    // D3DDevice_BlockUntilVerticalBlank+0x15 : push 6
    OV_MATCH(0x15, 0x6A, 0x06),

    // D3DDevice_BlockUntilVerticalBlank+0x17 : add eax, OFFSET_D3DDevice__m_VerticalBlankEvent
    OV_MATCH(0x17, 0x05),

    // D3DDevice_BlockUntilVerticalBlank+0x1D : call [KeWaitForSingleObject]
    OV_MATCH(0x1D, 0xFF, 0x15),

    // D3DDevice_BlockUntilVerticalBlank+0x23 : mov eax,[addr]
    OV_MATCH(0x23, 0xA1), // NOTE: std has a ret here and isn't a extended function.

    //
);

// ******************************************************************
// * D3D_DestroyResource
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(D3D_DestroyResource_0__LTCG_edi1,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3D_DestroyResource+0x19 : D3D_BlockOnResource
    XREF_ENTRY(0x1A, XREF_D3D_BlockOnResource),

    // D3D_DestroyResource+0x00 : mov eax, [edi]
    OV_MATCH(0x00, 0x8B, 0x07), // LTCG offset 0x00 vs STD offset 0x06

    // D3D_DestroyResource+0x05 : and esi, $70000
    OV_MATCH(0x05, 0x81, 0xE6, 0x00, 0x00, 0x07, 0x00),

    // D3D_DestroyResource+0x0B : cmp esi, $50000
    OV_MATCH(0x0B, 0x81, 0xFE, 0x00, 0x00, 0x05, 0x00),

    // D3D_DestroyResource+0x17 : mov e__,e__
    OV_MATCH(0x17, 0x8B), // LTCG mov e__,e__ vs STD push edi

    // relative to 0x00; LTCG offset 0x24 vs STD offset 0x22
    // D3D_DestroyResource+0x24 : cmp esi, $50000
    OV_MATCH(0x24, 0x81, 0xFE, 0x00, 0x00, 0x05, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderStateInline__GenericFragment
// ******************************************************************
// NOTE: This signature will find any generic match with D3D_g_RenderState
//       Currently, this is the best method if
//       D3DDevice_SetRenderStateNotInline detection is absent.
//       This OOVPA itself is not a symbol.
OOVPA_SIG_HEADER_XREF_DETECT(D3DDevice_SetRenderStateInline__GenericFragment,
                             3911,
                             XRefTwo,
                             DetectFirst)
OOVPA_SIG_MATCH(
    // call D3DDevice_SetRenderState_Simple
    XREF_ENTRY(0x15, XREF_D3DDevice_SetRenderState_Simple),
    XREF_ENTRY(0x1C, XREF_D3D_g_RenderState),

    // cmp esi,0x?? // Up until < 4039 is 0x52
    OV_MATCH(0x00, 0x83, 0xFE),

    // mov edi,ptr [ebx + ????]
    OV_MATCH(0x03, 0x8B, 0xBB),

    // jge +0x??
    OV_MATCH(0x09, 0x7D),

    // mov ecx,ptr [esi * 4 + ????]
    OV_MATCH(0x0B, 0x8B, 0x0C, 0xB5),

    // mov edx,edi
    OV_MATCH(0x12, 0x8B, 0xD7),
    // call D3DDevice_SetRenderState_Simple
    OV_MATCH(0x14, 0xE8),

    // mov ptr [esi * 4 + D3D_g_RenderState],edi
    OV_MATCH(0x19, 0x89, 0x3C, 0xB5),
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateVB
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateVB_8,
                         3911)
OOVPA_SIG_MATCH(
    // push ebp
    OV_MATCH(0x00, 0x55),

    // call ????
    OV_MATCH(0x06, 0xE8),

    // test eax,0x40000000
    OV_MATCH(0x12, 0xA9, 0x00, 0x00, 0x00, 0x40),

    // and eax,0xBFFFFF7F
    OV_MATCH(0x2D, 0x25, 0x7F, 0xFF, 0xFF, 0xBF),
    // or eax,0x300
    OV_MATCH(0x32, 0x0D, 0x00, 0x03, 0x00 /*, 0x00*/),
    //
);

// ******************************************************************
// * D3DDevice_SetTextureStageStateNotInline
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_ecx1_edx2_eax3,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    XREF_ENTRY(0x32, XREF_D3D_g_DeferredTextureState),

    // mov e??,eax(param_3)
    // mov e??,[0x????????]
    OV_MATCH(0x02, 0xD8, 0xA1),

    // cmp edx(param_2),0x??
    OV_MATCH(0x09, 0x83, 0xFA),

    // shl ecx(param_1),0x05
    OV_MATCH(0x23, 0xC1, 0xE1, 0x05),

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    OV_MATCH(0x2F, 0x89),

    // retn 0x04
    OV_MATCH(0x41, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateUP
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateUP_4,
                         3911)
OOVPA_SIG_MATCH(

    // sub esp,0x??
    OV_MATCH(0x00, 0x83, 0xEC),

    // call ????
    OV_MATCH(0x08, 0xE8),

    // and eax,0xFFFFFEFF
    OV_MATCH(0x19, 0x25, 0xFF, 0xFE, 0xFF, 0xFF),

    // or eax,0x80
    OV_MATCH(0x1F, 0x0D, 0x80, 0x00, 0x00),
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_0__LTCG_edx1,
                         3911)
OOVPA_SIG_MATCH(
    // mov eax, [addr]
    OV_MATCH(0x00, 0xA1),
    // test eax, eax
    // jnz eip + 0x2B
    OV_MATCH(0x05, 0x85, 0xC0, 0x75, 0x2B),
    // test byte ptr [edx + 0Ch], 4
    OV_MATCH(0x09, 0xF6, 0x42, 0x0C, 0x04),
    // push esi
    // jz eip + 0x08
    OV_MATCH(0x0D, 0x56, 0x74, 0x08),

    // ret
    OV_MATCH(0x33, 0xC3),
    //
);

// ******************************************************************
// * D3D::CDevice::FreeFrameBuffers
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDevice_FreeFrameBuffers_0__LTCG_ebx1,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(
    // call [AvGetSavedDataAddress]
    XREF_ENTRY(0x02, XREF_KT_FUNC_AvGetSavedDataAddress),
    // call [AvSendTVEncoderOption]
    XREF_ENTRY(0x18, XREF_KT_FUNC_AvSendTVEncoderOption),

    // call [AvGetSavedDataAddress]
    OV_MATCH(0x00, 0xFF, 0x15),

    // call [AvSendTVEncoderOption]
    OV_MATCH(0x16, 0xFF, 0x15),

    // mov esi, [ebx + 0x????]
    OV_MATCH(0x64, 0x8B, 0xB3),

    // call ????
    OV_MATCH(0x6A, 0xE8),
    // mov [ebx + 0x????], e??
    OV_MATCH(0x6F, 0x89),

    // cmp [ebx + 0x????], e??
    OV_MATCH(0x75, 0x39),
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_8,
                         3911)
OOVPA_SIG_MATCH(
    // sub esp, 0x??
    OV_MATCH(0x00, 0x83, 0xEC),

    // jc +4
    // mov [esp + 0x??], eax
    OV_MATCH(0x19, 0x72, 0x04, 0x89, 0x44, 0x24),

    // mov eax, [edi + 0x08]
    // call ????
    OV_MATCH(0x1F, 0x8B, 0x47, 0x08, 0xE8),

    // mov e??, [e?? + 0x24]
    OV_MATCH(0x29, 0x8B),
    OV_MATCH(0x2B, 0x24),

    // NOTE: Do not include ADD, DEC, and LEA instructions OVs. Because they
    //       are at different offsets and sometimes don't have a complete set
    //       of instructions. Plus it is unnecessary.
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset_0__LTCG_edi1,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x2C, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // jnz +0x??
    OV_MATCH(0x29, 0x75),

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x2B, 0xE8),
    // push param_1
    OV_MATCH(0x30, 0x57),
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
// Test case:
// Bruce Lee: QOD (4432)
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         3911)
OOVPA_SIG_MATCH(
    // sub esp, 0x___ (always 0x1A0)
    OV_MATCH(0x00, 0x81, 0xEC),

    // mov ebp, [esp + param_1]
    OV_MATCH(0x08, 0x8B, 0xAC, 0x24),

    // movzx esi, [ebp + 0x0D]
    OV_MATCH(0x13, 0x0F, 0xB6, 0x75, 0x0D),
    // mov bl, [esi + 0x____]
    OV_MATCH(0x17, 0x8A, 0x9E),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);
