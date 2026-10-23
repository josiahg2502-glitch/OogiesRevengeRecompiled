// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3D_GetAdapterDisplayMode
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3D_GetAdapterDisplayMode,
                         4627)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x0A, 0x08 },
    { 0x0B, 0x76 },
    { 0x0C, 0x88 },
    { 0x0D, 0xC2 },
    { 0x0E, 0x08 },
    { 0x0F, 0x00 },
    { 0x10, 0x56 },
    { 0x11, 0x8B },
    { 0x12, 0x35 },

    { 0x30, 0xC2 },
    { 0x31, 0x08 },
    //
);

// ******************************************************************
// * D3D_KickOffAndWaitForIdle
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_KickOffAndWaitForIdle,
                         4627)
OOVPA_SIG_MATCH(

    // D3D_KickOffAndWaitForIdle+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3D_KickOffAndWaitForIdle+0x05 : mov ecx, [eax+0x30]
    { 0x05, 0x8B },
    { 0x06, 0x48 },
    { 0x07, 0x30 },

    // D3D_KickOffAndWaitForIdle+0x08 : push 2
    { 0x08, 0x6A },
    { 0x09, 0x02 },

    // D3D_KickOffAndWaitForIdle+0x0A : push ecx
    { 0x0A, 0x51 },

    // D3D_KickOffAndWaitForIdle+0x0B : call [addr]
    { 0x0B, 0xE8 },

    // D3D_KickOffAndWaitForIdle+0x10 : retn
    { 0x10, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush_4,
                      4627,
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

    // mov ecx,[esp + param_1]
    OV_MATCH(0x15, 0x8B, 0x4C, 0x24, 0x08),
    //
);

// ******************************************************************
// * D3D_CommonSetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3D_CommonSetRenderTarget, 4627, 12)
    {
#else
OOVPA_XREF(D3D_CommonSetRenderTarget,
           4627,
           1 + 12,
           XRefOne)
{

    XREF_ENTRY(0x18, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3D_CommonSetRenderTarget+0x00 : sub esp, 0x20
        { 0x00, 0x83 },
            { 0x01, 0xEC },
            { 0x02, 0x20 },

            // D3D_CommonSetRenderTarget+0x86 : jmp +0x06
            { 0x86, 0xEB },
            { 0x87, 0x06 },

            // D3D_CommonSetRenderTarget+0x88 : and eax, 0x0FFF
            { 0x88, 0x25 },
            { 0x89, 0xFF },
            { 0x8A, 0x0F },
            { 0x8B, 0x00 },

            // D3D_CommonSetRenderTarget+0xC6 : and ecx, 0x0F
            { 0xC6, 0x83 },
            { 0xC7, 0xE1 },
            { 0xC8, 0x0F },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderTarget,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_SetRenderTarget+0x10 : call [D3D_CommonSetRenderTarget]
    XREF_ENTRY(0x10, XREF_D3D_CommonSetRenderTarget),

    // D3DDevice_SetRenderTarget+0x00 : mov eax, [esp+0x08]
    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x08 },

    // D3DDevice_SetRenderTarget+0x04 : mov ecx, [esp+0x04]
    { 0x04, 0x8B },
    { 0x05, 0x4C },
    { 0x06, 0x24 },
    { 0x07, 0x04 },

    // D3DDevice_SetRenderTarget+0x0D : push eax; push ecx
    { 0x0D, 0x50 },
    { 0x0E, 0x51 },

    // D3DDevice_SetRenderTarget+0x14 : retn 0x08
    { 0x14, 0xC2 },
    { 0x15, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x0500]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x00 },
    { 0x08, 0x05 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x0C : mov [eax+0x0500], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0x00 },
    { 0x0F, 0x05 },
    //
);

// ******************************************************************
// * D3DDevice_SetGammaRamp
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetGammaRamp,
                         4627) // Up to 5849
OOVPA_SIG_MATCH(

    { 0x25, 0x57 },
    { 0x26, 0x83 },
    { 0x27, 0xE0 },
    { 0x28, 0x01 },

    { 0x39, 0xF3 },
    { 0x3A, 0xA7 },

    { 0x5A, 0x89 },
    { 0x5B, 0x82 },
    { 0x5C, 0xE4 },

    { 0x70, 0x00 },
    { 0x71, 0xC7 },
    { 0x72, 0x84 },
    { 0x73, 0x82 },
    { 0x74, 0xDC },
    { 0x75, 0x07 },
    { 0x76, 0x00 },
    { 0x77, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         4627)
OOVPA_SIG_MATCH(
    // sub esp, 0x___ (always 0x194)
    OV_MATCH(0x00, 0x81, 0xEC),

    // mov eax, [esp + param_1]
    OV_MATCH(0x06, 0x8B, 0x84, 0x24),

    // movzx ebp, [eax + 0x0D]
    OV_MATCH(0x0F, 0x0F, 0xB6, 0x68, 0x0D),
    // mov bl, [ebp + 0x____]
    OV_MATCH(0x13, 0x8A, 0x9D),

    // Few instructions later will always have
    // shr e__, 0x3
    // and e__, 0x7
    // except above instructions could not be added into the signature
    // because of the offset changing over time.
    //
);

// ******************************************************************
// * D3DDevice_GetBackBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetBackBuffer,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3DDevice_GetBackBuffer2),

    { 0x03, 0x04 },
    { 0x05, 0xE8 },

    { 0x0A, 0x8B },
    { 0x0B, 0x4C },
    { 0x0C, 0x24 },
    { 0x0D, 0x0C },
    { 0x0E, 0x89 },
    { 0x0F, 0x01 },
    { 0x10, 0xC2 },
    { 0x11, 0x0C },
    //
);

// ******************************************************************
// * D3DDevice_GetBackBuffer2
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_GetBackBuffer2,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x09, XREF_D3D_g_pDevice),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // jnz +0x19 // difference between LTCG is jump's value
    OV_MATCH(0x0D, 0x75, 0x19),

    // mov eax,1
    OV_MATCH(0x0F, 0xB8, 0x01, 0x00 /*, 0x00, 0x00*/),
    // push esi
    OV_MATCH(0x14, 0x56), // push esi vs jmp LTCG 4626
    // mov esi,[ecx + eax * 4 + 0xXXXX]
    OV_MATCH(0x15, 0x8B, 0xB4, 0x81), // difference between LTCG is offset location

    // retn 0x04 // sometimes at different location for LTCG
    OV_MATCH(0x40, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_GetRenderTarget
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_GetRenderTarget,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call D3DDevice_GetRenderTarget2
    XREF_ENTRY(0x01, XREF_D3DDevice_GetRenderTarget2),

    // call D3DDevice_GetRenderTarget2
    OV_MATCH(0x00, 0xE8),

    // mov ecx, [esp + 0x04]
    OV_MATCH(0x05, 0x8B, 0x4C, 0x24, 0x04),

    // mov [ecx], eax
    OV_MATCH(0x09, 0x89, 0x01),

    // xor eax, eax
    OV_MATCH(0x0B, 0x33, 0xC0),

    // ret 0x0004
    OV_MATCH(0x0D, 0xC2, 0x04, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_GetRenderTarget2
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_GetRenderTarget2,
                      4627,
                      XRefTwo)
OOVPA_SIG_MATCH(
    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // TODO: Uncomment when WIP_LessVertexPatching is defined
    //XREF_ENTRY(0x08, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived

    // call D3DResource_AddRef
    XREF_ENTRY(0x12, XREF_D3DResource_AddRef),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // push esi
    OV_MATCH(0x05, 0x56),

    // mov esi,[eax + OFFSET_D3DDevice__m_RenderTarget]
    OV_MATCH(0x06, 0x8B, 0xB0),

    // jz +0x06
    OV_MATCH(0x0E, 0x74, 0x06),

    // call D3DResource_AddRef
    OV_MATCH(0x11, 0xE8),

    // ret
    OV_MATCH(0x19, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_GetDepthStencilSurface
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetDepthStencilSurface,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x01, XREF_D3DDevice_GetDepthStencilSurface2),

    { 0x00, 0xE8 },

    { 0x06, 0x4C },
    { 0x15, 0x66 },
    { 0x16, 0x08 },
    { 0x17, 0x76 },
    { 0x18, 0x88 },
    { 0x19, 0x8B },
    { 0x1A, 0xC2 },
    { 0x1B, 0xC2 },
    { 0x1C, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetDepthStencilSurface2
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_GetDepthStencilSurface2, 4627, 20)
    {
#else
OOVPA_XREF(D3DDevice_GetDepthStencilSurface2,
           4627,
           1 + 20,
           XRefOne)
{

    XREF_ENTRY(0x08, XREF_OFFSET_D3DDevice__m_DepthStencil), // Derived
#endif
        { 0x00, 0xA1 },

            { 0x05, 0x56 },
            { 0x06, 0x8B },
            { 0x07, 0xB0 },
            //{ 0x08, 0xB8 },
            //{ 0x09, 0x21 },
            { 0x0A, 0x00 },
            { 0x0B, 0x00 },
            { 0x0C, 0x85 },
            { 0x0D, 0xF6 },
            { 0x0E, 0x75 },
            { 0x0F, 0x04 },
            { 0x10, 0x33 },
            { 0x11, 0xC0 },
            { 0x12, 0x5E },
            { 0x13, 0xC3 },
            { 0x14, 0x56 },
            { 0x15, 0xE8 },

            { 0x1A, 0x8B },
            { 0x1B, 0xC6 },
            { 0x1C, 0x5E },
            { 0x1D, 0xC3 },
    }
OOVPA_END;

// ******************************************************************
// * D3D::SetTileNoWait
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetTileNoWait,
                         4627)
OOVPA_SIG_MATCH(

    // mov edx, [D3D__pDevice]
    OV_MATCH(0x00, 0x8B, 0x15),

    // sub esp, 0x18
    OV_MATCH(0x06, 0x83, 0xEC, 0x18),

    // mov ecx,6
    OV_MATCH(0x1A, 0xB9, 0x06, 0x00 /*, 0x00, 0x00*/),

    // mov ecx,6
    OV_MATCH(0x44, 0xB9, 0x06, 0x00 /*, 0x00, 0x00*/),

    // and e??,0x0FFFFFFF
    OV_MATCH(0x68, 0x81),
    // OV_MATCH(0x69, 0xE1), // Sometimes changed over builds.
    OV_MATCH(0x6A, 0xFF, 0xFF, 0xFF, 0x0F) // 0x0F vs 0x03 from D3DDevice_SetTile
    //
);

// ******************************************************************
// * D3DDevice_SetTile
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTile,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3D_SetTileNoWait),

    { 0x00, 0xE8 },
    { 0x05, 0xE9 },
    //
);

// ******************************************************************
// * D3DDevice_CreateIndexBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateIndexBuffer2,
                         4627)
OOVPA_SIG_MATCH(

    { 0x05, 0xC0 },
    { 0x0F, 0x85 },
    { 0x13, 0xC2 },
    { 0x1A, 0x89 },
    { 0x21, 0x08 },
    { 0x28, 0x00 },
    { 0x2F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_CreateIndexBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateIndexBuffer,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3DDevice_CreateIndexBuffer2),

    { 0x00, 0x8B },

    { 0x0A, 0x8B },
    { 0x0B, 0x4C },
    { 0x0C, 0x24 },
    { 0x0D, 0x14 },
    { 0x0E, 0x33 },
    { 0x0F, 0xD2 },
    { 0x10, 0x85 },
    { 0x11, 0xC0 },

    { 0x1F, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShaderConstant,
                      4627,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstant+0x08: jmp D3DDevice_SetVertexShaderConstant1
    XREF_ENTRY(0x09, XREF_D3DDevice_SetVertexShaderConstant1),

    // D3DDevice_SetVertexShaderConstant+0x12: jmp D3DDevice_SetVertexShaderConstant4
    XREF_ENTRY(0x13, XREF_D3DDevice_SetVertexShaderConstant4),

    { 0x00, 0x83 },
    { 0x01, 0xC1 },
    { 0x02, 0x60 },
    { 0x03, 0x83 },
    { 0x04, 0xF8 },
    { 0x05, 0x01 },
    { 0x06, 0x75 },
    { 0x07, 0x05 },
    { 0x08, 0xE9 },

    { 0x17, 0xC1 },
    { 0x18, 0xE0 },
    { 0x19, 0x02 },

    { 0x20, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant1
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant1,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstant1+0x06 : add eax, 0x1C
    { 0x06, 0x83 },
    { 0x07, 0xC0 },
    { 0x08, 0x1C },

    // D3DDevice_SetVertexShaderConstant1+0x0F : jnb +0x43
    { 0x0F, 0x73 },
    { 0x10, 0x43 },

    // D3DDevice_SetVertexShaderConstant1+0x27 : shl ecx, 0x04
    { 0x27, 0xC1 },
    { 0x28, 0xE1 },
    { 0x29, 0x04 },

    // D3DDevice_SetVertexShaderConstant1+0x53 : retn
    { 0x53, 0xC3 },

    // D3DDevice_SetVertexShaderConstant1+0x5D : jmp +0xA2
    { 0x5D, 0xEB },
    { 0x5E, 0xA2 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant4
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant4,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstant4+0x05 : add eax, 0x4C
    { 0x05, 0x83 },
    { 0x06, 0xC0 },
    { 0x07, 0x4C },

    // D3DDevice_SetVertexShaderConstant4+0x34 : movq mm7, qword ptr [edx+0x38]
    { 0x34, 0x0F },
    { 0x35, 0x6F },
    { 0x36, 0x7A },
    { 0x37, 0x38 },

    // D3DDevice_SetVertexShaderConstant4+0x42 : shl ecx, 0x04
    { 0x42, 0xC1 },
    { 0x43, 0xE1 },
    { 0x44, 0x04 },

    // D3DDevice_SetVertexShaderConstant4+0x91 : emms
    { 0x91, 0x0F },
    { 0x92, 0x77 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstantNotInline
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstantNotInline,
                         4627) // (NOT 5344!)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstantNotInline+0x02 : test byte ptr ds:[abs], 0x10
    { 0x02, 0xF6 },
    { 0x07, 0x00 },
    { 0x08, 0x10 },

    // D3DDevice_SetVertexShaderConstantNotInline+0x0E : jnz +0x15
    { 0x0E, 0x75 },
    { 0x0F, 0x15 },

    // D3DDevice_SetVertexShaderConstantNotInline+0x42 : push esi; push edi; mov edi, eax
    { 0x10, 0x56 },
    { 0x11, 0x57 },
    { 0x12, 0x8B },
    { 0x13, 0xF8 },

    // D3DDevice_SetVertexShaderConstantNotInline+0x21 : rep movsd
    { 0x21, 0xF3 },
    { 0x22, 0xA5 },

    // D3DDevice_SetVertexShaderConstantNotInline+0x28 : call [abs]
    { 0x28, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstantNotInlineFast
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstantNotInlineFast,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstantNotInlineFast+0x00 : push esi
    { 0x00, 0x56 },

    // D3DDevice_SetVertexShaderConstantNotInlineFast+0x26 : cmp eax, 0x10
    { 0x26, 0x83 },
    { 0x27, 0xF8 },
    { 0x28, 0x10 },

    // D3DDevice_SetVertexShaderConstantNotInlineFast+0x29 : jnb +0x1F
    { 0x29, 0x73 },
    { 0x2A, 0x1F },

    // D3DDevice_SetVertexShaderConstantNotInlineFast+0x33 : or eax, 0x0B80
    { 0x33, 0x0D },
    { 0x34, 0x80 },
    { 0x35, 0x0B },
    { 0x36, 0x00 },

    // D3DDevice_SetVertexShaderConstantNotInlineFast+0x3B : rep movsd
    { 0x3B, 0xF3 },
    { 0x3C, 0xA5 },

    // D3DDevice_SetVertexShaderConstantNotInlineFast+0x43 : emms
    { 0x43, 0x0F },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant1Fast
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant1Fast,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstant1Fast+0x05 : add eax, 0x1C
    { 0x05, 0x83 },
    { 0x06, 0xC0 },
    { 0x07, 0x1C },

    // D3DDevice_SetVertexShaderConstant1Fast+0x0E : jnb +0x2E
    { 0x0E, 0x73 },
    { 0x0F, 0x2E },

    // D3DDevice_SetVertexShaderConstant1Fast+0x28 : mov [eax-0x10], ecx
    { 0x28, 0x89 },
    { 0x29, 0x48 },
    { 0x2A, 0xF0 },

    // D3DDevice_SetVertexShaderConstant1Fast+0x3D : retn
    { 0x3D, 0xC3 },

    // D3DDevice_SetVertexShaderConstant1Fast+0x47 : jmp +0xB7
    { 0x47, 0xEB },
    { 0x48, 0xB7 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetPixelShader, 4627, 16)
    {
#else
OOVPA_XREF(D3DDevice_SetPixelShader,
           4627,
           1 + 16,
           XRefOne)
{

    XREF_ENTRY(0x0A, XREF_OFFSET_D3DDevice__m_PixelShader), // Derived
#endif
        { 0x03, 0x1D },

            { 0x0C, 0x00 },
            { 0x0D, 0x00 },
            { 0x0E, 0x89 },
            { 0x0F, 0x44 },
            { 0x10, 0x24 },
            { 0x11, 0x04 },
            { 0x12, 0x8B },
            { 0x13, 0x44 },
            { 0x14, 0x24 },
            { 0x15, 0x0C },
            { 0x16, 0x85 },
            { 0x17, 0xC0 },
            { 0x18, 0x89 },

            { 0x69, 0xC7 },
            { 0x76, 0x83 },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_CreateTexture2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture2,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_CreateTexture2+0x02 : lea eax, [esp+0x20]
    { 0x02, 0x8D },
    { 0x05, 0x20 },

    // D3DDevice_CreateTexture2+0x0E : setz dl
    { 0x0E, 0x0F },
    { 0x0F, 0x94 },
    { 0x10, 0xC2 },

    // D3DDevice_CreateTexture2+0x11 : cmp eax, 5
    { 0x11, 0x83 },
    { 0x12, 0xF8 },
    { 0x13, 0x05 },

    // D3DDevice_CreateTexture2+0x53 : call [abs]
    { 0x53, 0xE8 },

    // D3DDevice_CreateTexture2+0x78 : jnz +0x0D
    { 0x78, 0x75 },
    { 0x79, 0x0D },

    // D3DDevice_CreateTexture2+0xAE : retn 0x1C
    { 0xAE, 0xC2 },
    { 0xAF, 0x1C },
    //
);

// ******************************************************************
// * D3DDevice_CreateTexture
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture,
                         4627)
OOVPA_SIG_MATCH(

    { 0x03, 0x14 },

    { 0x13, 0x51 },
    { 0x14, 0x8B },
    { 0x15, 0x4C },
    { 0x16, 0x24 },
    { 0x17, 0x10 },
    { 0x18, 0x52 },
    { 0x19, 0x6A },
    { 0x1A, 0x01 },

    { 0x23, 0x54 },
    { 0x38, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_RunPushBuffer+0x3C : mov edx, [esi+30h]
    { 0x3C, 0x8B },
    { 0x3D, 0x56 },
    { 0x3E, 0x30 },

    // D3DDevice_RunPushBuffer+0xCA : mov edi, ebp
    { 0xCA, 0x8B },
    { 0xCB, 0xFD },

    // D3DDevice_RunPushBuffer+0xDC : jmp +0x12
    { 0xDC, 0xEB },
    { 0xDD, 0x12 },

    // D3DDevice_RunPushBuffer+0xED : lea edi, [eax+4]
    { 0xED, 0x8D },
    { 0xEE, 0x78 },
    { 0xEF, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap,
                         4627)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x2A, 0xBB },
    { 0x2B, 0x05 },
    { 0x37, 0xF6 },
    { 0x38, 0xC3 },
    { 0x39, 0x03 },

    { 0x73, 0xEB },
    { 0x74, 0x36 },
    { 0x75, 0x8B },
    { 0x76, 0xFB },
    { 0x77, 0x83 },
    { 0x78, 0xE7 },
    { 0x79, 0x04 },
    { 0x7A, 0x74 },
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateVertexBuffer,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3DDevice_CreateVertexBuffer2),

    { 0x00, 0x8B },

    { 0x0A, 0x8B },
    { 0x0B, 0x4C },
    { 0x0C, 0x24 },
    { 0x0D, 0x14 },
    { 0x0E, 0x33 },
    { 0x0F, 0xD2 },
    { 0x10, 0x85 },
    { 0x11, 0xC0 },
    { 0x12, 0x0F },

    { 0x1E, 0x8B },
    { 0x1F, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateVertexBuffer2,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_CreateVertexBuffer2+0x03 : push 0x40
    { 0x03, 0x6A },
    { 0x04, 0x40 },

    // D3DDevice_CreateVertexBuffer2+0x10 : mov eax, [esp+8]
    { 0x10, 0x8B },
    { 0x11, 0x44 },
    { 0x12, 0x24 },
    { 0x13, 0x08 },

    // D3DDevice_CreateVertexBuffer2+0x41 : mov dword ptr [esi], 0x01000001
    { 0x41, 0xC7 },
    { 0x42, 0x06 },
    { 0x43, 0x01 },
    { 0x44, 0x00 },
    { 0x46, 0x01 },

    // D3DDevice_CreateVertexBuffer2+0x4A : retn 0x04
    { 0x4A, 0xC2 },
    { 0x4B, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    // D3DDevice_SetTextureState_TexCoordIndex+0x14 : shl eax, 0x07
    { 0x14, 0xC1 },
    { 0x15, 0xE0 },
    { 0x16, 0x07 },

    // D3DDevice_SetTextureState_TexCoordIndex+0x26 : cmp eax, ecx
    { 0x26, 0x3B },
    { 0x27, 0xC1 },

    // D3DDevice_SetTextureState_TexCoordIndex+0x71 : mov ebp, 0x2400
    { 0x71, 0xBD },
    { 0x73, 0x24 },

    // D3DDevice_SetTextureState_TexCoordIndex+0xAA : shl ebx, 0x04
    { 0xAA, 0xC1 },
    { 0xAB, 0xE3 },
    { 0xAC, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleAntiAlias
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleAntiAlias,
                      4627,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // mov [D3DRS_MultiSampleAntiAlias],eax
    XREF_ENTRY(0x0F, XREF_D3DRS_MultiSampleAntiAlias),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x05, 0x8B, 0x35),

    // mov [D3DRS_MultiSampleAntiAlias],eax
    OV_MATCH(0x0E, 0xA3), // 3911 0x0D vs 0x0E
    //
);

// ******************************************************************
// * D3DDevice_SetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetMaterial,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_SetMaterial+0x0C : add edi, 0x0AB0
    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0xB0 },
    { 0x0F, 0x0A },

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
// * D3DVertexBuffer_Lock2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DVertexBuffer_Lock2,
                         4627)
OOVPA_SIG_MATCH(

    // D3DVertexBuffer_Lock2B+0x00 : push ebx
    { 0x00, 0x53 },

    // D3DVertexBuffer_Lock2+0x01 : mov bl, [esp+0x0C]
    { 0x01, 0x8A },
    { 0x02, 0x5C },
    { 0x03, 0x24 },
    { 0x04, 0x0C },

    // D3DVertexBuffer_Lock2B+0x09 : jnz +0x24
    { 0x09, 0x75 },
    { 0x0A, 0x24 },

    // D3DVertexBuffer_Lock2+0x3E : mov eax, [esi+4]
    { 0x3E, 0x8B },
    { 0x3F, 0x46 },
    { 0x40, 0x04 },

    // D3DVertexBuffer_Lock2+0x48 : retn 0x08
    { 0x48, 0xC2 },
    { 0x49, 0x08 },
    //
);

// ******************************************************************
// * D3DVertexBuffer_Lock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DVertexBuffer_Lock,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_D3DVertexBuffer_Lock2),

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x14 },
    { 0x04, 0x8B },
    { 0x05, 0x4C },
    { 0x06, 0x24 },
    { 0x07, 0x04 },
    { 0x08, 0x50 },
    { 0x09, 0x51 },
    { 0x0A, 0xE8 },

    { 0x0F, 0x8B },
    { 0x10, 0x4C },
    { 0x11, 0x24 },
    { 0x12, 0x08 },
    { 0x13, 0x8B },
    { 0x14, 0x54 },
    { 0x15, 0x24 },
    { 0x16, 0x10 },
    { 0x17, 0x03 },
    { 0x18, 0xC1 },
    { 0x19, 0x89 },
    { 0x1A, 0x02 },
    { 0x1B, 0xC2 },
    { 0x1C, 0x14 },
    //
);

// ******************************************************************
// * D3DTexture_GetSurfaceLevel2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DTexture_GetSurfaceLevel2,
                         4627)
OOVPA_SIG_MATCH(

    // D3DTexture_GetSurfaceLevel2+0x00 : sub esp, 0x0C
    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x0C },

    // D3DTexture_GetSurfaceLevel2+0x04 : mov esi, [esp+0x14]
    { 0x04, 0x8B },
    { 0x07, 0x14 },

    // D3DTexture_GetSurfaceLevel2+0x08 : lea eax, [esp+0x14]
    { 0x08, 0x8D },
    { 0x0B, 0x14 },

    // D3DTexture_GetSurfaceLevel2+0x17 : mov edx, [esp+0x24]
    { 0x17, 0x8B },
    { 0x1A, 0x24 },

    // D3DTexture_GetSurfaceLevel2+0x1B : lea eax, [esp+0x18]
    { 0x1B, 0x8D },
    { 0x1E, 0x18 },

    // D3DTexture_GetSurfaceLevel2+0x3E : call [abs]
    { 0x3E, 0xE8 },
    //
);

// ******************************************************************
// * D3DTexture_GetSurfaceLevel
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DTexture_GetSurfaceLevel,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_D3DTexture_GetSurfaceLevel2),

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x08 },

    { 0x0A, 0xE8 },

    { 0x0F, 0x8B },
    { 0x10, 0x54 },
    { 0x11, 0x24 },
    { 0x12, 0x0C },
    { 0x13, 0x33 },
    { 0x14, 0xC9 },
    { 0x15, 0x85 },
    //
);

// ******************************************************************
// * D3DDevice_GetShaderConstantMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetShaderConstantMode,
                         4627)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xD8 },
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
// * D3DDevice_LoadVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader,
                         4627)
OOVPA_SIG_MATCH(

    { 0x09, 0x08 },
    { 0x14, 0x75 },
    { 0x21, 0x8B },
    { 0x2A, 0xE8 },
    { 0x35, 0x9C },
    { 0x40, 0x14 },
    { 0x4B, 0x8D },
    //
);

// ******************************************************************
// * D3DDevice_GetStreamSource2 (Maybe same in older versions)
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetStreamSource2,
                         4627)
OOVPA_SIG_MATCH(

    { 0x06, 0x34 },
    { 0x12, 0x85 },
    { 0x16, 0x57 },
    { 0x22, 0x8B },
    { 0x26, 0x89 },
    { 0x2E, 0x00 },
    { 0x36, 0x89 },
    //
);

// ******************************************************************
// * CMiniport_IsFlipPending
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMiniport_IsFlipPending,
                         4627) // Was D3DDevice_Reset
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x81 },
    { 0x02, 0xBC },
    { 0x03, 0x01 },
    { 0x04, 0x00 },
    { 0x05, 0x00 },
    { 0x06, 0x83 },
    { 0x07, 0xE0 },
    { 0x08, 0x01 },
    { 0x09, 0x83 },
    { 0x0A, 0xC0 },
    { 0x0B, 0x1F },
    { 0x0C, 0x8D },
    { 0x0D, 0x04 },
    { 0x0E, 0x40 },
    { 0x0F, 0x8B },
    { 0x10, 0x04 },
    { 0x11, 0x81 },
    //
);

// ******************************************************************
// * D3DDevice_GetProjectionViewportMatrix
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetProjectionViewportMatrix,
                         4627) // Up to 5233
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x07, 0x57 },

    { 0x0E, 0x30 }, // 4361 0x7004
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
// * D3DDevice_SetRenderState_MultiSampleMask
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleMask,
                      4627,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov [D3DRS_MultiSampleMask],eax
    XREF_ENTRY(0x0B, XREF_D3DRS_MultiSampleMask),

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x15, XREF_D3D_g_pDevice),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov [D3DRS_MultiSampleMask],eax
    OV_MATCH(0x0A, 0xA3),

    // esi,[D3D_g_pDevice]
    OV_MATCH(0x13, 0x8B, 0x35),
    //
);

// ******************************************************************
// * D3DDevice_GetTexture, named with 2 suffix to match EMUPATCH(D3DDevice_GetTexture2)
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_GetTexture2, 4627, 23)
    {
#else
OOVPA_XREF(D3DDevice_GetTexture2, 4627, 1 + 23, // Up to 5233. Also for 5344, 5558, 5659, 5788, 5849, 5933
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
            { 0x0E, 0x38 }, // GetTexture2 380B vs GetPalette2 480B
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
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVerticesUP,
                         4627)
OOVPA_SIG_MATCH(

    // D3DDevice_DrawIndexedVerticesUP+0x4A : or edx, 0x800
    { 0x4A, 0x81 },
    { 0x4B, 0xCA },
    { 0x4C, 0x00 },
    { 0x4D, 0x08 },

    // D3DDevice_DrawIndexedVerticesUP+0x5C : lea edx, [edi+0x784]
    { 0x5C, 0x8D },
    { 0x5D, 0x97 },
    { 0x5E, 0x84 },
    { 0x5F, 0x07 },

    // D3DDevice_DrawIndexedVerticesUP+0x6A : mov eax, 0x10
    { 0x6A, 0xB8 },
    { 0x6B, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_SetStipple
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetStipple,
                         4627)
OOVPA_SIG_MATCH(

    { 0x08, 0x03 },
    { 0x15, 0xF6 },
    { 0x1C, 0x10 },
    { 0x26, 0x20 },
    { 0x30, 0x80 },
    { 0x3A, 0x00 },
    { 0x44, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_PersistDisplay,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_PersistDisplay+0x02 : mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x04, XREF_D3D_g_pDevice),

    // D3DDevice_PersistDisplay+0x00 : push ecx
    OV_MATCH(0x00, 0x51),

    // D3DDevice_PersistDisplay+0x08 : call [AvGetSavedDataAddress]
    OV_MATCH(0x08, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x13 : call [MmFreeContiguousMemory]
    OV_MATCH(0x13, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x1B : call [AvSetSavedDataAddress]
    OV_MATCH(0x1B, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x32 : ret
    OV_MATCH(0x32, 0xC3),

    //
);

// ******************************************************************
// * D3DDevice_ApplyStateBlock
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_ApplyStateBlock,
                         4627)
OOVPA_SIG_MATCH(

    { 0x1E, 0xC6 },
    { 0x40, 0x83 },
    { 0x5E, 0x04 },
    { 0x7E, 0x50 },
    { 0xA0, 0x83 },
    { 0xBE, 0x51 },
    { 0xDE, 0xE9 },
    { 0xFE, 0x33 },
    //
);

// ******************************************************************
// * D3D::BlockOnTime
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime,
                         4627)
OOVPA_SIG_MATCH(

    { 0x09, 0x34 },
    { 0x27, 0x07 },
    { 0x55, 0x7E },
    { 0x7B, 0x58 },
    { 0xE3, 0x80 },
    { 0xF5, 0x30 },
    //
);

// ******************************************************************
// * D3DDevice_CreateImageSurface
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateImageSurface,
                         4627)
OOVPA_SIG_MATCH(

    { 0x04, 0x8B },
    { 0x0A, 0x24 },
    { 0x0E, 0x00 },
    { 0x10, 0x52 },
    { 0x16, 0x8B },
    { 0x1C, 0x85 },
    { 0x22, 0x01 },
    { 0x28, 0x07 },
    { 0x2E, 0x00 },
    //
);

// ******************************************************************
// * D3DCubeTexture_GetCubeMapSurface
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DCubeTexture_GetCubeMapSurface,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call D3DCubeTexture_GetCubeMapSurface2
    XREF_ENTRY(0x10, XREF_D3DCubeTexture_GetCubeMapSurface2),

    // mov e??,[esp + 0x??]
    OV_MATCH(0x00, 0x8B),
    // mov e??,[esp + 0x??]
    OV_MATCH(0x04, 0x8B),
    // mov e??,[esp + 0x??]
    OV_MATCH(0x08, 0x8B),

    // call D3DCubeTexture_GetCubeMapSurface2
    OV_MATCH(0x0F, 0xE8),

    // mov e??,[esp + 0x??]
    OV_MATCH(0x14, 0x8B),

    // setne ??
    OV_MATCH(0x1C, 0x0F, 0x95),

    // retn 0x10
    OV_MATCH(0x2A, 0xC2, 0x10),
    //
);

// ******************************************************************
// * D3DCubeTexture_GetCubeMapSurface2
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3DCubeTexture_GetCubeMapSurface2,
                         4627)
OOVPA_SIG_MATCH(

    // sub esp,0x8
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
    OV_MATCH(0x41, 0xE8),

    // add esp,8
    OV_MATCH(0x47, 0x83, 0xC4, 0x08),
    // retn 0x0C
    OV_MATCH(0x4A, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * D3DDevice_CreatePalette2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreatePalette2,
                         4627)
OOVPA_SIG_MATCH(

    { 0x0A, 0x8B },
    { 0x16, 0x74 },
    { 0x22, 0x04 },
    { 0x2E, 0x50 },
    { 0x3A, 0xE8 },
    { 0x46, 0xC1 },
    { 0x52, 0xFF },
    { 0x5E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_CreatePalette
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_CreatePalette,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3DDevice_CreatePalette2),

    { 0x00, 0x8B },
    { 0x0A, 0x8B },

    { 0x13, 0x95 },
    { 0x14, 0xC2 },
    { 0x15, 0x89 },
    { 0x16, 0x01 },
    { 0x17, 0x4A },
    { 0x18, 0x81 },
    { 0x19, 0xE2 },
    { 0x1A, 0x0E },
    //
);

// ******************************************************************
// * D3DPalette_Lock2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DPalette_Lock2,
                         4627)
OOVPA_SIG_MATCH(

    { 0x02, 0x24 },
    { 0x06, 0x8B },
    { 0x0A, 0x75 },
    { 0x12, 0x8B },
    { 0x13, 0x46 },
    { 0x16, 0x00 },
    { 0x1A, 0x5E },
    //
);

// ******************************************************************
// * D3DPalette_Lock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DPalette_Lock,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_D3DPalette_Lock2),

    { 0x01, 0x44 },
    { 0x08, 0x50 },
    { 0x0A, 0xE8 },
    { 0x0F, 0x8B },
    { 0x10, 0x54 },
    { 0x13, 0x89 },
    { 0x14, 0x02 },
    //
);

// ******************************************************************
// * D3DDevice_GetPushBufferOffset
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetPushBufferOffset,
                         4627)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },
    { 0x08, 0x86 },
    { 0x18, 0x00 },
    { 0x19, 0x2B },
    { 0x1A, 0xC1 },
    { 0x1B, 0x99 },
    { 0x1C, 0x83 },
    { 0x1D, 0xE2 },
    { 0x1E, 0x07 },
    { 0x1F, 0x03 },
    //
);

// ******************************************************************
// * D3DDevice_SetModelView
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetModelView,
                         4627)
OOVPA_SIG_MATCH(

    { 0x15, 0xFF },
    { 0x2D, 0x81 },
    { 0x43, 0x3B },
    { 0x5A, 0xC1 },
    { 0x71, 0x53 },
    { 0x8A, 0x8B },
    { 0x9F, 0x30 },
    //
);

// ******************************************************************
// * D3D::LazySetPointParams
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_LazySetPointParams,
                         4627)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x14 },
    { 0x4E, 0xE0 },
    { 0x73, 0xF6 },
    { 0x74, 0xC4 },
    { 0x75, 0x41 },
    //
);

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetMaterial,
                         4627)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0xB0 },
    { 0x0E, 0x0A },
    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetBackMaterial,
                         4627)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },
    { 0x0C, 0x81 },
    { 0x0E, 0xF4 },
    { 0x0F, 0x0A },
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
                         4627)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },
    { 0x0D, 0xF4 },
    { 0x0E, 0x0A },
    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_SampleAlpha
// ******************************************************************
// Generic OOVPA as of 4627 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_SampleAlpha,
                      4627,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x11, XREF_D3D_g_pDevice),

    // mov [D3DRS_SampleAlpha],eax
    XREF_ENTRY(0x18, XREF_D3DRS_SampleAlpha),

    // mov eax,[esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x0F, 0x8B),

    // mov [D3DRS_SampleAlpha],eax
    OV_MATCH(0x17, 0xA3),
    //
);

// ******************************************************************
// * D3DDevice_CreateVolumeTexture
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateVolumeTexture,
                         4627)
OOVPA_SIG_MATCH(

    { 0x03, 0x18 },
    { 0x0B, 0x10 },
    { 0x0C, 0x6A },
    { 0x0D, 0x04 },
    { 0x0E, 0x50 },
    { 0x0F, 0x8B },
    { 0x10, 0x44 },
    { 0x11, 0x24 },
    { 0x12, 0x14 },
    { 0x13, 0x51 },
    { 0x14, 0x8B },
    { 0x15, 0x4C },

    { 0x28, 0x20 },
    { 0x3B, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_CreateCubeTexture
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateCubeTexture,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_CreateCubeTexture0x19: call D3DDevice_CreateTexture2
    XREF_ENTRY(0x20, XREF_D3DDevice_CreateTexture2),

    { 0x03, 0x10 },
    { 0x10, 0x44 },
    { 0x11, 0x24 },
    { 0x12, 0x0C },
    { 0x13, 0x51 },
    { 0x14, 0x52 },
    { 0x15, 0x6A },
    { 0x16, 0x01 },
    { 0x17, 0x50 },
    { 0x18, 0x50 },

    { 0x1F, 0x4C },
    //
);

// ******************************************************************
// * IDirect3DVertexBuffer8_Lock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirect3DVertexBuffer8_Lock,
                      4627,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x03, XREF_D3DVertexBuffer_Lock2),

    { 0x00, 0x50 },
    { 0x01, 0x51 },
    { 0x02, 0xE8 },

    { 0x07, 0x8B },
    { 0x08, 0x4C },
    { 0x09, 0x24 },
    { 0x0A, 0x04 },
    { 0x0B, 0x8B },
    { 0x0C, 0x54 },
    { 0x0D, 0x24 },
    //
);

// ******************************************************************
// * Rollback support signature(s)
// ******************************************************************
#define D3DResource_Release_4627 D3DResource_Release_3911
