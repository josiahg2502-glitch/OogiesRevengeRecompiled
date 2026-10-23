// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_CreateTexture2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture2,
                         4831)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x57 },

    { 0x10, 0x0F },
    { 0x11, 0x94 },
    { 0x12, 0xC2 },
    { 0x13, 0x8D },
    { 0x14, 0x4C },
    { 0x15, 0x24 },
    { 0x16, 0x28 },
    { 0x17, 0x51 },

    { 0x51, 0x24 },
    { 0x52, 0xF7 },
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetTexture, 4831, 15)
    {
#else
OOVPA_XREF(D3DDevice_SetTexture,
           4831,
           1 + 15,
           XRefOne)
    {

        XREF_ENTRY(0x13, XREF_OFFSET_D3DDevice__m_Textures), // Derived
#endif
#if 0 // PatrickvL preparations // 1+31,
        { 0x00, 0x83 },
        { 0x01, 0xEC },
        { 0x02, 0x08 },
        { 0x03, 0x53 },
        { 0x04, 0x56 },
        { 0x05, 0x8B },
        { 0x06, 0x74 },
        { 0x07, 0x24 },
        { 0x08, 0x14 },
        { 0x09, 0x57 },
        { 0x0A, 0x8B },
        { 0x0B, 0x3D }, // TODO : See if this should be value 0x56?

        { 0x10, 0x8B },
        { 0x11, 0x84 },
        { 0x12, 0xB7 },
        //{ 0x13, 0x38 }, // disabled. part of an offset
        //{ 0x14, 0x0B },
        { 0x15, 0x00 },
        { 0x16, 0x00 },
        { 0x17, 0x85 },
        { 0x18, 0xC0 },
        { 0x19, 0x89 },
        { 0x1A, 0x7C },
        { 0x1B, 0x24 },
        { 0x1C, 0x0C },
        { 0x1D, 0x89 },
        { 0x1E, 0x44 },
        { 0x1F, 0x24 },
#else
            { 0x0B, 0x56 },

            { 0x21, 0x74 },
            { 0x22, 0x20 },

            { 0x33, 0xF7 },
            { 0x34, 0xC1 },
            { 0x36, 0xFF },

            { 0x39, 0x89 },
            { 0x3A, 0x10 },

            { 0x50, 0x75 },
            { 0x51, 0x47 },
#endif
        { 0x52, 0x8B },
            { 0x53, 0x45 },
            { 0x54, 0x00 },
            { 0x55, 0x3B },
            { 0x56, 0x45 },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
// Up to 5849, excluding 5455
OOVPA_SIG_HEADER_XREF(D3DDevice_PersistDisplay,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_PersistDisplay+0x04 : mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x06, XREF_D3D_g_pDevice),

    // D3DDevice_PersistDisplay+0x00 : sub esp,0x__
    OV_MATCH(0x01, 0xEC),

    // D3DDevice_PersistDisplay+0x0A : call [AvGetSavedDataAddress]
    OV_MATCH(0x0A, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x15 : call [MmFreeContiguousMemory]
    OV_MATCH(0x15, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x1D : call [AvSetSavedDataAddress]
    OV_MATCH(0x1D, 0xFF, 0x15),

    // D3DDevice_PersistDisplay+0x36 : ret
    OV_MATCH(0x36, 0xC3),

    //
);

// ******************************************************************
// * D3DDevice_SetPixelShaderConstant
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShaderConstant,
                         4831)
OOVPA_SIG_MATCH(

    // D3DDevice_SetPixelShaderConstant+0x1E : test eax, eax
    { 0x1E, 0x85 },
    { 0x1F, 0xC0 },

    // D3DDevice_SetPixelShaderConstant+0x32 : mov [ebp+0x10], eax
    { 0x32, 0x89 },
    { 0x33, 0x45 },
    { 0x34, 0x10 },

    // D3DDevice_SetPixelShaderConstant+0x84 : or eax, ebx
    { 0x84, 0x0B },
    { 0x85, 0xC3 },

    // D3DDevice_SetPixelShaderConstant+0xBD : mov dword ptr [eax], 0x406A0
    { 0xBD, 0xC7 },
    { 0xBE, 0x00 },
    { 0xBF, 0x60 },
    { 0xC0, 0x0A },
    { 0xC1, 0x04 },
    { 0xC2, 0x00 },
    //
);
