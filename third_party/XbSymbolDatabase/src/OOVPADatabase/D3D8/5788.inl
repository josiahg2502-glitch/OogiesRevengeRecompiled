// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3D::RecordStateBlock
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_RecordStateBlock,
                         5788)
OOVPA_SIG_MATCH(

    // D3D_RecordStateBlock+0x0F : mov eax, [edi+0x07A4]
    { 0x0F, 0x8B },
    { 0x10, 0x87 },
    { 0x11, 0xA4 },
    { 0x12, 0x07 },

    // D3D_RecordStateBlock+0x95 : add ebx, ecx
    { 0x95, 0x03 },
    { 0x96, 0xD9 },

    // D3D_RecordStateBlock+0xD5 : mov dword ptr [esi+0x0C], 1
    { 0xD5, 0xC7 },
    { 0xD6, 0x46 },
    { 0xD7, 0x0C },
    { 0xD8, 0x01 },
    //
);

// ******************************************************************
// * D3DDevice_SetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetMaterial,
                         5788)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0x00 },
    { 0x0F, 0x0F },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x90 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetMaterial,
                         5788)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },

    { 0x0D, 0x00 },
    { 0x0E, 0x0F },

    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         5788)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x0938]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x38 },
    { 0x08, 0x09 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x0C : mov [eax+0x0938], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0x38 },
    { 0x0F, 0x09 },
    //
);

// ******************************************************************
// * D3DDevice_SetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetBackMaterial,
                         5788)
OOVPA_SIG_MATCH(

    { 0x04, 0x08 },

    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0x44 },
    { 0x0F, 0x0F },
    { 0x10, 0x00 },

    { 0x16, 0x00 },
    { 0x1F, 0x81 },
    { 0x22, 0x90 },
    { 0x2C, 0x5E },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackMaterial,
                         5788)
OOVPA_SIG_MATCH(

    { 0x05, 0x56 },
    { 0x06, 0x57 },
    { 0x0A, 0x0C },

    { 0x0D, 0x44 },
    { 0x0E, 0x0F },

    { 0x12, 0x11 },
    { 0x16, 0xF3 },
    { 0x1A, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_GetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShader,
                         5788)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x98 },
    { 0x08, 0x07 },
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
                         5788)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x84 },
    { 0x08, 0x07 },
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
// * D3DDevice_GetShaderConstantMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetShaderConstantMode,
                         5788)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x28 },
    { 0x08, 0x19 },
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
// * D3DDevice_GetTexture, named with 2 suffix to match EMUPATCH(D3DDevice_GetTexture2)
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_GetTexture2, 5788, 23) // Up to 5849
    {
#else
OOVPA_XREF(D3DDevice_GetTexture2, 5788, 1 + 23, // Up to 5849
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
            { 0x0E, 0x88 }, // GetTexture2 880F vs GetPalette2 980F
            { 0x0F, 0x0F },

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
