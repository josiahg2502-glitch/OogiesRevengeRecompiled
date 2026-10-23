// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//51538B5C240C8BC6C1E0 ...C20400
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_4__LTCG_esi1,
                      2045,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x14, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x51 },
    { 0x01, 0x53 },
    { 0x02, 0x8B },
    { 0x03, 0x1D },

    { 0x0D, 0x8B },
    { 0x0E, 0xC7 },
    { 0x0F, 0xC1 },
    { 0x10, 0xE0 },
    { 0x11, 0x07 },
    { 0x12, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//8BCEC1E10681C1241B04 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor_4__LTCG_eax1,
                         2060)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x26, 0x8B },
    { 0x27, 0xCE },
    { 0x28, 0xC1 },
    { 0x29, 0xE1 },
    { 0x2A, 0x06 },
    { 0x2B, 0x81 },
    { 0x2C, 0xC1 },
    { 0x2D, 0x24 },

    { 0x47, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
// Generic OOVPA as of 4531 and newer
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_4__LTCG_eax1,
                         4531)
OOVPA_SIG_MATCH(
    // push ebx
    OV_MATCH(0x00, 0x53),

    // mov esi, param_1
    // mov eax, [e??]
    OV_MATCH(0x10, 0x8B, 0xF0, 0x8B),
    // cmp eax, ecx
    // jne +0x0E
    OV_MATCH(0x14, 0x3B, 0xC1, 0x72, 0x0E),

    // lea e??, [e?? * 0x04 + 0x40AE0] // 0x40AE0 is a reliable hardcoded value across all builds.
    OV_MATCH(0x26, 0x8D),
    OV_MATCH(0x29, 0xE0, 0x0A, 0x04, 0x00),

    // This is required OV pair to tell the difference from the (symbol)_4__LTCG_eax1_ebx2 signature.
    // retn 0x04
    OV_MATCH(0x43, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
//7505BB050000008B ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap_0__LTCG_eax1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x0C, 0x75 },
    { 0x0D, 0x05 },
    { 0x0E, 0xBB },
    { 0x0F, 0x05 },
    { 0x10, 0x00 },
    { 0x11, 0x00 },
    { 0x12, 0x00 },
    { 0x13, 0x8B },
    //
);

//******************************************************************
//* D3DDevice_SelectVertexShader
//******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_4__LTCG_eax1,
                         4531)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x4C, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),

    // mov [eax + 0x4],0x6
    OV_MATCH(0x55, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x5A, 0x00, 0x00),

    // add eax,0xC
    OV_MATCH(0x5F, 0x83, 0xC0, 0x0C),

    // ret
    OV_MATCH(0x95, 0xC2, 0x04),
    //
);

// ******************************************************************
// * CMiniport_InitHardware
// ******************************************************************
//558BEC83EC1053578BF85768
OOVPA_SIG_HEADER_NO_XREF(CMiniport_InitHardware_4,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x10 },
    { 0x06, 0x53 },
    { 0x07, 0x57 },
    { 0x08, 0x8B },
    { 0x09, 0xF8 },
    { 0x0A, 0x57 },
    { 0x0B, 0x68 },
    //
);

// ******************************************************************
// * D3DDevice_SetFlickerFilter
// ******************************************************************
//6A00566A0B50FF15 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetFlickerFilter_0__LTCG_esi1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x1D, 0x6A },
    { 0x1E, 0x00 },
    { 0x1F, 0x56 },
    { 0x20, 0x6A },
    { 0x21, 0x0B },
    { 0x22, 0x50 },
    { 0x23, 0xFF },
    { 0x24, 0x15 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader_0__LTCG_eax1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x6D, 0xC7 },
    { 0x6E, 0x40 },
    { 0x6F, 0x04 },
    { 0x70, 0x00 },
    { 0x71, 0x00 },
    { 0x72, 0x21 },
    { 0x73, 0x00 },
    { 0x74, 0x83 },
    { 0x75, 0xC0 },
    { 0x76, 0x08 },

    { 0x7B, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
//008107000008008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginPushBuffer_0__LTCG_edi1,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x43, 0x00 },
    { 0x44, 0x81 },
    { 0x45, 0x07 },
    { 0x46, 0x00 },
    { 0x47, 0x00 },
    { 0x48, 0x08 },
    { 0x49, 0x00 },
    { 0x4A, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
//00576A00568BF8E8 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer_4__LTCG_eax2,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x0A, 0x00 },
    { 0x0B, 0x57 },
    { 0x0C, 0x6A },
    { 0x0D, 0x00 },
    { 0x0E, 0x56 },
    { 0x0F, 0x8B },
    { 0x10, 0xF8 },
    { 0x11, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureStageStateNotInline
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_esi3,
                      4531,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    XREF_ENTRY(0x23, XREF_D3D_g_DeferredTextureState),

    // cmp edx(param_2),0x??
    OV_MATCH(0x00, 0x83, 0xFA),

    // shl eax(param_1),0x05
    OV_MATCH(0x15, 0xC1, 0xE0, 0x05),

    // mov D3D_g_DeferredTextureState[e?? * 4],e??
    OV_MATCH(0x22, 0x89),

    // ret
    OV_MATCH(0x2A, 0xC3),
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
// stdcall (LTCG)
// NOTE: Detected with 4627 build, except moved to 4531 since it is
//       almost identical to non-ltcg 4531 signature.
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_4,
                         4531)
OOVPA_SIG_MATCH(
    // mov eax, [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // test byte ptr [eax + 0x08], 0x04
    OV_MATCH(0x04, 0xF6, 0x40, 0x08, 0x04),

    // jz eip + 0x08
    OV_MATCH(0x09, 0x74, 0x08),

    // or ecx, 0x2000
    OV_MATCH(0xB8, 0x81, 0xC9, 0x00, 0x20, 0x00, 0x00), // unique

    // ret 0x04
    OV_MATCH(0xC3, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
// Generic OOVPA as of 4531 and newer?
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_4__LTCG_ebx1,
                         4531)
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

    // Possible start at offset 0x140 - 0x176 to use one signature rather than multiple
    // mov edi, eax
    OV_MATCH(0x142, 0x8B, 0xF8), // random selection to avoid an error when the OOVPA is expanded.

    // add eax, 0x18
    // dec ecx
    OV_MATCH(0x158, 0x83, 0xC0, 0x18, 0x49),

    // lea eax, [ebx + 0x????]
    OV_MATCH(0x171, 0x8D, 0x83),
    //
);
