// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * Direct3D_CreateDevice
// ******************************************************************
//85C9750AC705 ...C21000
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice_16__LTCG_eax4_ecx6,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    { 0x0D, 0x85 },
    { 0x0E, 0xC9 },
    { 0x0F, 0x75 },
    { 0x10, 0x0A },
    { 0x11, 0xC7 },
    { 0x12, 0x05 },

    { 0x1B, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
// ...C20400
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_4__LTCG_esi1,
                      2058,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x14, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x01, 0x53 },
    { 0x02, 0x8B },

    { 0x08, 0x55 },
    { 0x09, 0x8B },

    { 0x0C, 0x10 },
    { 0x0D, 0x8B },
    { 0x0E, 0xC6 },
    { 0x0F, 0xC1 },
    { 0x10, 0xE0 },
    { 0x11, 0x07 },
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShader
//******************************************************************
//C7009C1E040089 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_4__LTCG_eax1,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },

    { 0x5E, 0xC7 },
    { 0x5F, 0x00 },
    { 0x60, 0x9C },
    { 0x61, 0x1E },
    { 0x62, 0x04 },
    { 0x63, 0x00 },
    { 0x64, 0x89 },
    //
);

// ******************************************************************
// * D3D_CommonSetRenderTarget
// ******************************************************************
//8B490CC1E91483E10FB801
OOVPA_SIG_HEADER_NO_XREF(D3D_CommonSetRenderTarget,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x57, 0x8B },
    { 0x58, 0x49 },
    { 0x59, 0x0C },
    { 0x5A, 0xC1 },
    { 0x5B, 0xE9 },
    { 0x5C, 0x14 },
    { 0x5D, 0x83 },
    { 0x5E, 0xE1 },
    { 0x5F, 0x0F },
    { 0x60, 0xB8 },
    { 0x61, 0x01 },
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
// Generic OOVPA as of 5028 and newer.
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_0__LTCG_edx1,
                         5028)
OOVPA_SIG_MATCH(
    // mov eax, [edx + 0x08]
    // test al, 0x04
    OV_MATCH(0x00, 0x8B, 0x42, 0x08, 0xA8, 0x04),

    // jz eip + 0x08
    OV_MATCH(0x06, 0x74, 0x08),

    // [edx + 0x08], 0x2000
    OV_MATCH(0x5F, 0x81, 0x4A, 0x08, 0x00, 0x20, 0x00, 0x00), // unique
    // pop esi
    // ret
    OV_MATCH(0x66, 0x5E, 0xC3),
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
// stdcall (LTCG)
// NOTE: Detected with 5120 build, except moved to 5028 since it is
//       almost identical to non-ltcg 5028 signature.
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_4,
                         5028)
OOVPA_SIG_MATCH(
    // mov eax, [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // test cl, 0x04
    // jz eip + 0x08
    OV_MATCH(0x07, 0xF6, 0xC1, 0x04, 0x74, 0x08),

    // or [eax + 0x08], 0x2000
    OV_MATCH(0xA5, 0x81, 0x48, 0x08, 0x00, 0x20, 0x00, 0x00), // unique

    // ret 0x04
    OV_MATCH(0xAD, 0xC2, 0x04),
    //
);
