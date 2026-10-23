// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetMaterial,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0x70 },
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
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0xB4 },
    { 0x0F, 0x0B },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x10 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackMaterial,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0xB4 },
    { 0x0E, 0x0B },
    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 4039, 11)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget,
           4039,
           1 + 11,
           XRefOne)
{

    XREF_ENTRY(0x18, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0xXX
        OV_MATCH(0x00, 0x83, 0xEC),
            //OV_MATCH(0x02, 0x30),

            // Require in order to separate from CommonSetRenderTarget function.
            // D3DDevice_SetRenderTarget+0x02 : push esi
            OV_MATCH(0x04, 0x56),

            // D3DDevice_SetRenderTarget+0x73 : shr ecx,0x14
            OV_MATCH(0x79, 0xC1, 0xE9, 0x14),

            // D3DDevice_SetRenderTarget+0x7C : and ecx, 0x0F
            OV_MATCH(0x7C, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0x84 : shl eax,cl
            OV_MATCH(0x84, 0xD3, 0xE0),
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_Begin
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Begin,
                         4039)
OOVPA_SIG_MATCH(

    { 0x07, 0xE8 },

    { 0x18, 0x8B },
    { 0x19, 0x4C },
    { 0x1A, 0x24 },
    { 0x1B, 0x08 },
    { 0x1C, 0xC7 },
    { 0x1D, 0x00 },
    { 0x1E, 0xFC },
    { 0x1F, 0x17 },
    { 0x20, 0x04 },
    { 0x21, 0x00 },

    { 0x32, 0xC2 },
    { 0x33, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetSwapCallback
// ******************************************************************
// Generic OOVPA as of 4039 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetSwapCallback,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // D3DDevice_SetSwapCallback+0x04 : mov ecx,[D3D_g_pDevice]
    XREF_ENTRY(0x06, XREF_D3D_g_pDevice),

    // D3DDevice_SetSwapCallback+0x0A : mov [ecx+OFFSET_D3DDevice__m_SwapCallback],eax
    XREF_ENTRY(0x0C, XREF_D3DDevice__m_SwapCallback_OFFSET),

    // D3DDevice_SetSwapCallback+0x00 : mov eax,[esp+0x04]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // D3DDevice_SetSwapCallback+0x0A : mov [ecx+OFFSET_D3DDevice__m_SwapCallback],eax
    OV_MATCH(0x0A, 0x89, 0x81),

    // D3DDevice_SetSwapCallback+0x10 : retn 0x04
    OV_MATCH(0x10, 0xC2, 0x04, 0x00),

    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2f
// ******************************************************************
// TODO: May need lower to 4034, not 100% sure... Check with other
//       signatures has similar instruction at offset 0x17
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexData2f,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // lea edx,[ecx * 8 + 0x81880]
    OV_MATCH(0x17, 0x8D, 0x14, 0xCD, 0x80, 0x18, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x2E, 0x83, 0xC0, 0x0C),

    // retn 0x0C
    OV_MATCH(0x34, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2s
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData2s,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x02, 0x35 },

    { 0x17, 0x8D },
    { 0x18, 0x14 },
    { 0x19, 0x8D },
    { 0x1A, 0x00 },
    { 0x1B, 0x19 },
    { 0x1C, 0x04 },
    { 0x1D, 0x00 },
    { 0x1E, 0x0F },
    { 0x1F, 0xBF },
    { 0x25, 0x0F },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4f
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4f,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x18, 0xF9 },
    { 0x19, 0xFF },
    { 0x1A, 0x75 },
    { 0x1B, 0x07 },
    { 0x1C, 0xB9 },
    { 0x1D, 0x18 },
    { 0x1E, 0x15 },
    { 0x1F, 0x00 },
    { 0x56, 0xC2 },
    /*
        { 0x0A, 0x46 },
        { 0x16, 0x08 },
        { 0x22, 0x09 },
        { 0x2E, 0x24 },
        { 0x3A, 0x24 },
        { 0x46, 0x8B },
        { 0x52, 0x14 },*/
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4s
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4s,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x08, 0x06 },

    { 0x15, 0x24 },
    { 0x16, 0x08 },
    { 0x17, 0x8D },
    { 0x18, 0x14 },
    { 0x19, 0xCD },
    { 0x1A, 0x80 },
    { 0x1B, 0x19 },
    { 0x1F, 0xBF },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4ub
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4ub,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x08, 0x06 },
    { 0x13, 0x8B },
    { 0x1C, 0x04 },
    { 0x26, 0x0F },
    { 0x30, 0x24 },
    { 0x3A, 0x24 },
    { 0x44, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexDataColor
// ******************************************************************
// TODO: Need to test and verify for 4034 titles.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexDataColor,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // call D3DDevice_MakeSpace
    XREF_ENTRY(0x10, XREF_D3DDevice_MakeSpace),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov ecx,[esp + 0x0C]
    OV_MATCH(0x14, 0x8B, 0x4C, 0x24, 0x0C),
    // lea edx[ecx * 4 + 0x00041940] // 0x00041940 is hardcode value
    OV_MATCH(0x18, 0x8D, 0x14, 0x8D, 0x40, 0x19, 0x04, 0x00),

    // and ecx,0xFF00FF00
    OV_MATCH(0x37, 0x81, 0xE1, 0x00, 0xFF, 0x00, 0xFF),
    //
);

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_End,
                         4039) // Up to 5233
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x07, 0x8B },
    { 0x0E, 0xE8 },
    { 0x16, 0x17 },
    { 0x1E, 0x00 },

    { 0x22, 0x08 },
    { 0x23, 0x89 },
    { 0x24, 0x06 },
    { 0x25, 0x8B },
    { 0x26, 0x46 },
    { 0x27, 0x08 },
    { 0x28, 0xF6 },
    { 0x29, 0xC4 },

    { 0x2E, 0x01 },
    { 0x36, 0x08 },
    { 0x3C, 0xC3 },
    //
);

// ******************************************************************
// * D3DResource_IsBusy
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DResource_IsBusy,
                         4039)
OOVPA_SIG_MATCH(

    // D3DResource_IsBusy+0x24 : test eax, 0x780000
    { 0x24, 0xA9 },
    { 0x25, 0x00 },
    { 0x26, 0x00 },
    { 0x27, 0x78 },

    // D3DResource_IsBusy+0x35 : jnz +0x41
    { 0x35, 0x75 },
    { 0x36, 0x41 },

    // D3DResource_IsBusy+0x4E : mov eax, [ecx+0x14]
    { 0x4E, 0x8B },
    { 0x4F, 0x41 },
    { 0x50, 0x14 },

    // D3DResource_IsBusy+0x76 : jnb +0x09
    { 0x76, 0x73 },
    { 0x77, 0x09 },
    //
);

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
// Reused in 5455 as well.
OOVPA_SIG_HEADER_XREF(D3DDevice_PersistDisplay,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_PersistDisplay+0x04 : mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x06, XREF_D3D_g_pDevice),

    // D3DDevice_PersistDisplay+0x00 : sub esp,0x__
    OV_MATCH(0x01, 0xEC),

    // D3DDevice_PersistDisplay+0x0A : call [AvGetSavedDataAddress]
    OV_MATCH(0x0A, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x19 : call [MmFreeContiguousMemory] // NOTE: doesn't exist in 5455
    //OV_MATCH(0x19, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x1F : push 0x00
    OV_MATCH(0x1F, 0x6A, 0x00),

    // D3DDevice_PersistDisplay+0x21 : call [AvSetSavedDataAddress]
    OV_MATCH(0x21, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x3A : ret
    OV_MATCH(0x3A, 0xC3),

    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVerticesUP,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov edi,[D3D_g_pDevice]
    XREF_ENTRY(0x09, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateUP
    XREF_ENTRY(0x13, XREF_D3D_CDevice_SetStateUP),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // mov edi,[D3D_g_pDevice]
    OV_MATCH(0x07, 0x8B, 0x3D),

    // mov ecx,edi
    OV_MATCH(0x0D, 0x8B, 0xCF),

    // mov [ebp - 0x14],e??
    OV_MATCH(0x0F, 0x89),
    OV_MATCH(0x11, 0xEC), // D3DDevice_DrawVerticesUP 4039 0xEC vs D3DDevice_DrawIndexedVerticesUP 5028 0xF8
    // call D3D::CDevice::SetStateUP
    OV_MATCH(0x12, 0xE8),
    //
);

// ******************************************************************
// * D3DDevice_GetDisplayMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetDisplayMode,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x0B, 0x00 },
    { 0x0C, 0x00 },
    { 0x0D, 0x8B },
    { 0x0E, 0x41 },
    { 0x0F, 0x10 },
    { 0x10, 0x85 },
    { 0x11, 0xC0 },
    { 0x12, 0x57 },
    { 0x13, 0x75 },
    { 0x14, 0x12 },
    { 0x15, 0x8B },
    { 0x16, 0x49 },
    { 0x17, 0x0C },
    { 0x18, 0xC1 },
    { 0x19, 0xE9 },
    { 0x1A, 0x14 },
    { 0x1B, 0x83 },
    { 0x1C, 0xE1 },
    { 0x1D, 0x0F },
    { 0x1E, 0xB8 },
    { 0x1F, 0x01 },

    { 0x4C, 0xD3 },
    { 0x4D, 0xE0 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginPushBuffer,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x57 },
    { 0x1C, 0xBE },

    { 0x50, 0xFC },
    { 0x51, 0xFD },
    { 0x52, 0xFF },
    { 0x53, 0xFF },
    { 0x54, 0x8B },
    { 0x55, 0x46 },
    { 0x56, 0x08 },
    { 0x57, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         4039)
OOVPA_SIG_MATCH(

    { 0x1E, 0x07 },
    { 0x3E, 0x00 },
    { 0x5E, 0x46 },
    { 0x7E, 0x24 },
    { 0x9E, 0x18 },
    { 0xBE, 0x74 },
    { 0xE2, 0x8B },
    { 0xFE, 0x24 },
    //
);

// ******************************************************************
// * D3DDevice_GetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShader,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xFC }, // D3DDevice_GetVertexShader 0xFC vs D3DDevice_GetPixelShader 0xE8
    { 0x08, 0x04 },
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
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xE8 }, // D3DDevice_GetVertexShader 0xFC vs D3DDevice_GetPixelShader 0xE8
    { 0x08, 0x04 },
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
// * D3DDevice_GetVertexShaderConstant
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShaderConstant,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x0C, 0x24 },

    { 0x15, 0x57 },
    { 0x16, 0x8B },
    { 0x17, 0x7C },
    { 0x18, 0x24 },
    { 0x19, 0x10 },
    { 0x1A, 0x8D },
    { 0x1B, 0xB4 },
    { 0x1C, 0x10 },

    { 0x28, 0x8B },
    { 0x2F, 0x5F },
    //
);

// ******************************************************************
// * D3DDevice_IsFencePending
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_IsFencePending,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x01, XREF_D3D_g_pDevice), // Derived

    { 0x07, 0x34 },
    { 0x0A, 0x30 },
    { 0x10, 0xD1 },
    { 0x17, 0x1B },
    { 0x1C, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         4039)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x05B4]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xB4 },
    { 0x08, 0x05 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x05 : mov [eax+0x05B4], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0xB4 },
    { 0x0F, 0x05 },
    //
);

// ******************************************************************
// * D3DDevice_SetModelView
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetModelView,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x15, 0x25 },
    { 0x2F, 0x81 },
    { 0x43, 0x43 },
    { 0x5A, 0x04 },
    { 0x72, 0x8D },
    { 0x88, 0x00 },
    { 0x9F, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_GetModelView
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetModelView,
                         4039)
OOVPA_SIG_MATCH(

    { 0x05, 0x57 },
    { 0x0A, 0x85 },
    { 0x10, 0xB0 },
    { 0x16, 0x10 },
    { 0x1C, 0x5E },
    { 0x22, 0xC1 },
    { 0x28, 0xE0 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderInput
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderInput,
                         4039)
OOVPA_SIG_MATCH(

    { 0x03, 0x04 },
    { 0x04, 0x83 },
    { 0x05, 0xEC },
    { 0x06, 0x40 },
    { 0x07, 0x85 },
    { 0x08, 0xC0 },
    { 0x09, 0x53 },
    { 0x0A, 0x8B },
    { 0x0B, 0x1D },

    { 0x19, 0x25 },
    { 0x1A, 0xFF },
    { 0x1B, 0xFF },
    { 0x1C, 0xFF },
    { 0x1D, 0xBF },
    { 0x1E, 0x83 },
    { 0x1F, 0xC8 },
    //
);

// ******************************************************************
// * D3DDevice_RunVertexStateShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunVertexStateShader,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x09, 0x3B },
    { 0x14, 0x4C },
    { 0x1F, 0xC0 },
    { 0x2A, 0x40 },
    { 0x35, 0xF4 },
    { 0x40, 0xC7 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush_8,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x0C, XREF_D3D_CDevice_SetStateVB),

    // push esi
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x56, 0x8B, 0x35),

    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x0B, 0xE8),
    // mov eax,[esp + param_1]
    OV_MATCH(0x10, 0x8B, 0x44, 0x24, 0x08),
    // inc eax
    OV_MATCH(0x14, 0x40),

    // call XMETAL_StartPushCount
    OV_MATCH(0x17, 0xE8),

    // mov ecx,[esp + param_2]
    OV_MATCH(0x1C, 0x8B, 0x4C, 0x24, 0x0C),

    // pop esi
    // ret 0x0008
    OV_MATCH(0x23, 0xC2, 0x08),

    //
);

// ******************************************************************
// * D3DDevice_EndPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_EndPush,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3D_g_pDevice), // Derived

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x8B },
    { 0x05, 0x0D },
    { 0x0A, 0x89 },
    { 0x0B, 0x01 },
    { 0x0C, 0xC2 },
    { 0x0D, 0x04 },
    { 0x0E, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_PrimeVertexCache
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_PrimeVertexCache,
                         4039)
OOVPA_SIG_MATCH(

    { 0x02, 0x2D },

    { 0x07, 0x8B },
    { 0x08, 0x45 },
    { 0x09, 0x1C },
    { 0x0A, 0x56 },
    { 0x0B, 0x50 },
    { 0x0C, 0x8B },
    { 0x0D, 0xCD },

    { 0x19, 0x00 },
    { 0x1A, 0x8B },
    { 0x1B, 0x4D },
    { 0x1C, 0x04 },
    { 0x1D, 0xD1 },
    { 0x1E, 0xEE },
    { 0x1F, 0x3B },
    //
);

// ******************************************************************
// * D3DDevice_SetBackBufferScale
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetBackBufferScale,
                         4039)
OOVPA_SIG_MATCH(

    { 0x09, 0x86 },

    { 0x10, 0xC1 },
    { 0x11, 0xE9 },
    { 0x12, 0x04 },
    { 0x13, 0x83 },
    { 0x14, 0xE1 },
    { 0x15, 0x0F },
    { 0x16, 0x85 },
    { 0x17, 0xC9 },

    { 0x28, 0xD8 },
    { 0x29, 0x4C },
    { 0x2A, 0x24 },
    { 0x2B, 0x0C },
    { 0x2C, 0x83 },
    { 0x2D, 0xE0 },
    { 0x2E, 0x0F },
    //
);

// ******************************************************************
// * D3DDevice_FlushVertexCache
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_FlushVertexCache,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x08, 0x06 },
    { 0x0D, 0x05 },
    { 0x13, 0xC7 },
    { 0x15, 0x10 },
    { 0x17, 0x04 },
    { 0x1C, 0x00 },
    { 0x21, 0xC0 },
    { 0x26, 0xC3 },
    //
);
