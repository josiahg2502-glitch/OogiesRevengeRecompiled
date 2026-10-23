// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilEnable,
                      5849,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // [D3DRS_StencilEnable],e??
    XREF_ENTRY(0x0E, XREF_D3DRS_StencilEnable),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov e??,[esp + param_1]
    OV_MATCH(0x08, 0x8B),
    OV_MATCH(0x0A, 0x24, 0x0C),

    // [D3DRS_StencilEnable],e??
    OV_MATCH(0x0C, 0x89),
    // Do NOT use any offsets after 0x1D
);

// ******************************************************************
// * D3D::SetFence
// * SOURCE: Spiderman 2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         5849)
OOVPA_SIG_MATCH(

    { 0x0E, 0x05 },
    { 0x17, 0xC7 },
    { 0x3E, 0x40 },
    { 0x5E, 0x00 },
    { 0x87, 0x4E },
    { 0x98, 0x83 },
    { 0xA8, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilFail,
                      5849,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // [D3DRS_StencilFail],e??
    XREF_ENTRY(0x0E, XREF_D3DRS_StencilFail),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov e??,[esp + param_1]
    OV_MATCH(0x08, 0x8B),
    OV_MATCH(0x0A, 0x24, 0x0C),

    // [D3DRS_StencilFail],e??
    OV_MATCH(0x0C, 0x89),
    // Do NOT use any offsets after 0x1D
);
