// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap,
                         4531)
OOVPA_SIG_MATCH(

    // D3DDevice_Swap+0x10 : mov ebx, 5
    { 0x10, 0xBB },
    { 0x11, 0x05 },

    // D3DDevice_Swap+0x1D : test bl, 3
    { 0x1D, 0xF6 },
    { 0x1E, 0xC3 },
    { 0x1F, 0x03 },

    // D3DDevice_Swap+0x46 : inc dword ptr [esi+0x2AD8]
    { 0x46, 0xFF },
    { 0x47, 0x86 },
    { 0x48, 0xD8 },
    { 0x49, 0x2A },

    // D3DDevice_Swap+0xAE : retn 4
    { 0xB9, 0xC2 },
    { 0xBA, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_UpdateOverlay
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_UpdateOverlay,
                         4531) // Up to 5120
OOVPA_SIG_MATCH(

    { 0x03, 0xA1 },
    { 0x1A, 0x04 },
    { 0x1F, 0x7C },

    { 0x6F, 0x8B },
    { 0x70, 0x4F },
    { 0x71, 0x04 },
    { 0x72, 0x8B },
    { 0x73, 0xD0 },
    { 0x74, 0x8B },
    { 0x75, 0x44 },
    { 0x76, 0x24 },
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff,
                         4531)
OOVPA_SIG_MATCH(
    // push ecx
    OV_MATCH(0x00, 0x51),

    // test byte ptr [ecx + 0x8], 0x04
    // jz eip + 8
    OV_MATCH(0x05, 0xF6, 0x41, 0x08, 0x04, 0x74, 0x08),

    // or [eax + 0x08], 0x2000
    OV_MATCH(0x7D, 0x81, 0x48, 0x08, 0x00, 0x20, 0x00, 0x00), // unique

    // ret
    OV_MATCH(0x85, 0xC3),
    //
);

// ******************************************************************
// * D3DPalette_Lock
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DPalette_Lock,
                         4531)
OOVPA_SIG_MATCH(

    { 0x00, 0xF6 },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x0C },
    { 0x04, 0xA0 },
    { 0x05, 0x56 },
    { 0x06, 0x8B },
    { 0x07, 0x74 },
    { 0x08, 0x24 },
    { 0x09, 0x08 },
    { 0x0A, 0x75 },
    { 0x0B, 0x06 },
    { 0x0C, 0x56 },
    { 0x0D, 0xE8 },

    { 0x12, 0x8B },
    { 0x21, 0xC2 },
    { 0x22, 0x0C },
    //
);

// ******************************************************************
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush_4,
                      4531,
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

    // ret 0x0004
    OV_MATCH(0x1D, 0xC2, 0x04),
    //
);
