// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         4242)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x0440]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x40 },
    { 0x08, 0x04 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x05 : mov [eax+0x0440], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0x40 },
    { 0x0F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex,
                      4242,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    // D3DDevice_SetTextureState_TexCoordIndex+0x0D : shl eax, 0x07
    { 0x0D, 0xC1 },
    { 0x0E, 0xE0 },
    { 0x0F, 0x07 },

    // D3DDevice_SetTextureState_TexCoordIndex+0x24 : cmp eax, ecx
    { 0x24, 0x3B },
    { 0x25, 0xC1 },

    // D3DDevice_SetTextureState_TexCoordIndex+0x6B : mov esi, 0x2400
    { 0x6B, 0xBE },
    { 0x6D, 0x24 },

    // D3DDevice_SetTextureState_TexCoordIndex+0xB3 : shl edx, 0x04
    { 0xB3, 0xC1 },
    { 0xB4, 0xE2 },
    { 0xB5, 0x04 },
    //
);

// ******************************************************************
// * CMiniport_IsFlipPending
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMiniport_IsFlipPending,
                         4242)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x81 },
    { 0x02, 0xF4 },
    { 0x03, 0x01 },
    { 0x04, 0x00 },
    { 0x05, 0x00 },
    { 0x06, 0x83 },
    { 0x07, 0xE0 },
    { 0x08, 0x01 },
    { 0x09, 0x8B },
    { 0x0A, 0x84 },
    { 0x0B, 0xC1 },
    { 0x0C, 0xB4 },
    { 0x0D, 0x01 },
    { 0x0E, 0x00 },
    { 0x0F, 0x00 },
    { 0x10, 0xC3 },
    //
);
