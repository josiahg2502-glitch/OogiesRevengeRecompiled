// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
//7505BB050000008B ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap_0__LTCG_eax1,
                         2036)
OOVPA_SIG_MATCH(

    { 0x01, 0x56 },

    { 0x26, 0x75 },
    { 0x27, 0x05 },
    { 0x28, 0xBB },
    { 0x29, 0x05 },
    { 0x2A, 0x00 },
    { 0x2B, 0x00 },
    { 0x2C, 0x00 },
    { 0x2D, 0x8B },
    //
);

// ******************************************************************
// * D3D::SetTileNoWait
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3D_SetTileNoWait_0__LTCG_ecx1_eax2,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // sub esp,0x18
    OV_MATCH(0x00, 0x83, 0xEC, 0x18),

    // mov esi,eax(param_2)
    OV_MATCH(0x05, 0x8B, 0xF0),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x09, 0xA1),

    // mov ebx,ecx(param_1)
    OV_MATCH(0x0F, 0x8B, 0xD9),

    // mov [esp + 0x20],0
    OV_MATCH(0x2D, 0xC7, 0x44, 0x24, 0x20, 0x00, 0x00, 0x00, 0x00),
    // mov [esp + 0x1C],0
    OV_MATCH(0x35, 0xC7, 0x44, 0x24, 0x1C),
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
//81C10000F8FF89 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTexture_4__LTCG_eax1,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x2B, 0x81 },
    { 0x2C, 0xC1 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0xF8 },
    { 0x30, 0xFF },
    { 0x31, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVertices
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVertices_4__LTCG_ecx2_eax3,
                      2024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebp,[D3D_g_pDevice]
    XREF_ENTRY(0x04, XREF_D3D_g_pDevice),

    // call D3D::CDevice::SetStateVB
    XREF_ENTRY(0x12, XREF_D3D_CDevice_SetStateVB),

    // push ebx
    // push ebp
    // mov ebp,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53, 0x55, 0x8B, 0x2D),

    // push 0x0
    // push ebp
    OV_MATCH(0x0A, 0x6A, 0x00, 0x55),
    // mov edi,param_3
    // mov ebx,param_2
    OV_MATCH(0x0D, 0x8B, 0xF8, 0x8B, 0xD9),
    // call D3D::CDevice::SetStateVB
    OV_MATCH(0x11, 0xE8),
    //
);
