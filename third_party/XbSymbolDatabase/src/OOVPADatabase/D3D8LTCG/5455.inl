// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0__LTCG_eax1_ebx2,
                         2060)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x5C, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),

    // mov [eax + 0x4],0x6
    OV_MATCH(0x65, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x6A, 0x00, 0x00),

    // add eax,0xC
    OV_MATCH(0x6F, 0x83, 0xC0, 0x0C),

    // pop esi
    // ret
    OV_MATCH(0x9E, 0x5E, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0__LTCG_eax1_ebx2,
                         2061)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x6E, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),

    // mov [eax + 0x4],0x6
    OV_MATCH(0x77, 0xC7, 0x40, 0x04, 0x06, 0x00),
    //OV_MATCH(0x7C, 0x00, 0x00),

    // add eax,0xC
    OV_MATCH(0x81, 0x83, 0xC0, 0x0C),

    // pop esi
    // ret
    OV_MATCH(0xB0, 0x5E, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
// NOTE: Detected in b5659 title
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0__LTCG_eax1_ebx2,
                         2062)
OOVPA_SIG_MATCH(

    // test param_1,param_1
    OV_MATCH(0x00, 0x85, 0xC0),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B),

    // mov [eax],0x00081E94
    OV_MATCH(0x6F, 0xC7, 0x00, 0x94, 0x1E, 0x08, 0x00),

    // mov [eax + 0x4],0x6
    OV_MATCH(0x78, 0xC7, 0x40, 0x04, 0x06, 0x00),
    // OV_MATCH(0x7D, 0x00, 0x00),

    // add eax,0xC
    OV_MATCH(0x82, 0x83, 0xC0, 0x0C),

    // pop esi
    // ret
    OV_MATCH(0xB2, 0x5E, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SetScreenSpaceOffset
// ******************************************************************
// Generic OOVPA as of 5455 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetScreenSpaceOffset,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x0D, XREF_D3D_g_pDevice),

    // fld [esp + param_1]
    OV_MATCH(0x00, 0xD9, 0x44, 0x24, 0x04),

    // fadd [0x????????]
    OV_MATCH(0x05, 0xD8, 0x05),
    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x0B, 0x8B),

    // fld [esp + param_2]
    OV_MATCH(0x17, 0xD9, 0x44, 0x24, 0x0C),
    //
);

// ******************************************************************
// * D3D::SetTileNoWait
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3D_SetTileNoWait_0__LTCG_eax1_ecx2,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x08, XREF_D3D_g_pDevice),

    // sub esp,0x18
    OV_MATCH(0x00, 0x83, 0xEC, 0x18),

    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x06, 0x8B, 0x1D),

    // esi,[param_2]
    OV_MATCH(0x16, 0x8B, 0x31),
    // test esi,esi
    OV_MATCH(0x18, 0x85, 0xF6),

    // js +0x04
    // xor ecx,ecx
    // xor edi,edi
    OV_MATCH(0x30, 0x78, 0x04, 0x33, 0xC9, 0x33, 0xFF),

    // and e??,0x0FFFFFFF
    OV_MATCH(0x6B, 0x81),
    //OV_MATCH(0x6C, 0xE2), // Sometimes changed over builds.
    OV_MATCH(0x6D, 0xFF, 0xFF, 0xFF, 0x0F) // 0x0F vs 0x03 from D3DDevice_SetTile
    //
);

// ******************************************************************
// * D3D::SetTileNoWait
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3D_SetTileNoWait_0__LTCG_eax1_ecx2,
                      5659,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x08, XREF_D3D_g_pDevice),

    // sub esp,0x1C
    OV_MATCH(0x00, 0x83, 0xEC, 0x1C),

    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x06, 0x8B, 0x1D),

    // esi,[param_2]
    OV_MATCH(0x1A, 0x8B, 0x31),
    // test esi,esi
    OV_MATCH(0x1C, 0x85, 0xF6),

    // js +0x04
    // xor ecx,ecx
    // xor edi,edi
    OV_MATCH(0x34, 0x78, 0x04, 0x33, 0xC9, 0x33, 0xFF),

    // and e??,0x0FFFFFFF
    OV_MATCH(0x68, 0x81),
    // OV_MATCH(0x69, 0xE2), // Sometimes changed over builds.
    OV_MATCH(0x6A, 0xFF, 0xFF, 0xFF, 0x0F) // 0x0F vs 0x03 from D3DDevice_SetTile
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//8B4C240483EC0C85C9568B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x83 },
    { 0x05, 0xEC },
    { 0x06, 0x0C },
    { 0x07, 0x85 },
    { 0x08, 0xC9 },
    { 0x09, 0x56 },
    { 0x0A, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_UpdateOverlay
// ******************************************************************
//7707B800001000EB
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_UpdateOverlay,
                         1024)
OOVPA_SIG_MATCH(

    { 0x02, 0x08 },

    { 0xCB, 0x77 },
    { 0xCC, 0x07 },
    { 0xCD, 0xB8 },
    { 0xCE, 0x00 },
    { 0xCF, 0x00 },
    { 0xD0, 0x10 },
    { 0xD1, 0x00 },
    { 0xD2, 0xEB },
    //
);

// ******************************************************************
// * D3D_BlockOnResource
// ******************************************************************
// Test case:
// - Freaky Flyers
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource_0__LTCG_eax1,
                         5455)
OOVPA_SIG_MATCH(
    // mov esi, [D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov edx, param_1
    OV_MATCH(0x0F, 0x8B, 0x10),

    // test edx, 0x780000
    OV_MATCH(0x28, 0xF7, 0xC2, 0x00, 0x00, 0x78, 0x00),
    // jnz +0x??
    OV_MATCH(0x2E, 0x75),
    //
);

// ******************************************************************
// * D3D_KickOffAndWaitForIdle
// ******************************************************************
//8B4C24088B442404E8
OOVPA_SIG_HEADER_NO_XREF(D3D_KickOffAndWaitForIdle2,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x13, 0x8B },
    { 0x14, 0x4C },
    { 0x15, 0x24 },
    { 0x16, 0x08 },
    { 0x17, 0x8B },
    { 0x18, 0x44 },
    { 0x19, 0x24 },
    { 0x1A, 0x04 },
    { 0x1B, 0xE8 },

    { 0x20, 0xC2 },
    { 0x21, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//A900007800751925000007003D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTarget,
                         1084)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x25, 0xA9 },
    { 0x26, 0x00 },
    { 0x27, 0x00 },
    { 0x28, 0x78 },
    { 0x29, 0x00 },
    { 0x2A, 0x75 },
    { 0x2B, 0x19 },
    { 0x2C, 0x25 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0x07 },
    { 0x30, 0x00 },
    { 0x31, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
//F64401680175
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LightEnable,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x24, 0xF6 },
    { 0x25, 0x44 },
    { 0x26, 0x01 },
    { 0x27, 0x68 },
    { 0x28, 0x01 },
    { 0x29, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      5455,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    XREF_ENTRY(0xFB, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // lea edi,[param_1 + 0x21]
    OV_MATCH(0x09, 0x8D, 0x78, 0x21),
    // shl edi,0x6
    OV_MATCH(0x0C, 0xC1, 0xE7, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x11, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xFA, 0xE8),

    // ret
    OV_MATCH(0x109, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
// Lowest build detected was 5558, since function is almost identical to
// standard 5028's function changed.
// TODO: Find out if we need to lower CDevice_KickOff down to 5028.
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff,
                         1048)
OOVPA_SIG_MATCH(
    // mov eax, [ecx + 0x08]
    // test al, 0x04
    OV_MATCH(0x00, 0x8B, 0x41, 0x08, 0xA8, 0x04),

    // jz eip + 0x08
    OV_MATCH(0x06, 0x74, 0x08),

    // Below OV pairs help reduce multiple signatures into one because
    // xref of D3D_g_pDevice's offset and ret instruction are changed in
    // various titles, even in the same build version.

    // or [ecx + 0x08], 0x2000
    OV_MATCH(0x8F, 0x81, 0x49, 0x08, 0x00, 0x20, 0x00, 0x00), // unique
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_0__LTCG_eax1,
                         5455)
OOVPA_SIG_MATCH(
    // mov ecx, [eax + 0x08]
    // test cl, 0x04
    OV_MATCH(0x00, 0x8B, 0x48, 0x08, 0xF6, 0xC1, 0x04),

    // jz eip + 0x08
    OV_MATCH(0x07, 0x74, 0x08),

    // or [eax + 0x08], 0x2000
    OV_MATCH(0x8F, 0x81, 0x48, 0x08, 0x00, 0x20, 0x00, 0x00), // unique

    // ret
    OV_MATCH(0x98, 0xC3),
    //
);

// ******************************************************************
// * D3D::CDevice::InitializeFrameBuffers
// ******************************************************************
// Generic OOVPA as of 5455 and newer?
// NOTE: Lowest detected was 5455, unknown if it's present in earlier
//       builds and if it's detected there too.
OOVPA_SIG_HEADER_NO_XREF(CDevice_InitializeFrameBuffers_4__LTCG_edi1,
                         5455)
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
    // mov ebx, eax
    OV_MATCH(0x144, 0x8B, 0xD8), // random selection to avoid an error when the OOVPA is expanded.

    // add eax, 0x18
    // dec esi
    OV_MATCH(0x172, 0x83, 0xC0, 0x18, 0x4E),

    // lea instruction can be at different offsets and can use different registers, so don't rely on this.
    // i.e. lea eax, [edi + 0x????] vs lea ecx, [edi + 0x????]
);
