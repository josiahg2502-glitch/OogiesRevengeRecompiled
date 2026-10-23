// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3D_GetAdapterDisplayMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_GetAdapterDisplayMode,
                         4361)
OOVPA_SIG_MATCH(

    // D3D_GetAdapterDisplayMode+0x08 : mov eax, 0x8876086C
    { 0x08, 0xB8 },
    { 0x09, 0x6C },
    { 0x0A, 0x08 },
    { 0x0B, 0x76 },
    { 0x0C, 0x88 },

    // D3D_GetAdapterDisplayMode+0x18 : jnz +0x17
    { 0x18, 0x75 },
    { 0x19, 0x17 },

    // D3D_GetAdapterDisplayMode+0x31 : mov ecx, [edx+0x2080]
    { 0x31, 0x8B },
    { 0x32, 0x8A },
    { 0x33, 0x80 },
    { 0x34, 0x20 },

    // D3D_GetAdapterDisplayMode+0xBD : retn 0x08
    { 0xBD, 0xC2 },
    { 0xBE, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetTexture, 4361, 28)
    {
#else
OOVPA_XREF(D3DDevice_SetTexture,
           4361,
           1 + 26,
           XRefOne)
{

    XREF_ENTRY(0x13, XREF_OFFSET_D3DDevice__m_Textures), // Derived
#endif
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
            { 0x0B, 0x3D },

            { 0x10, 0x8B },
            { 0x11, 0x84 },
            { 0x12, 0xB7 },
#ifndef WIP_LessVertexPatching
            { 0x13, 0x78 }, // disabled. part of an offset
            { 0x14, 0x0A },
#endif
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
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SelectVertexShaderDirect
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShaderDirect,
                         4361)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x05, 0x85 },
    { 0x0C, 0x00 },

    { 0x14, 0xF3 },
    { 0x15, 0xA5 },
    { 0x16, 0x5F },
    { 0x17, 0x5E },
    { 0x18, 0xB9 },

    { 0x1D, 0x83 },
    { 0x1E, 0xC9 },
    { 0x1F, 0x01 },

    { 0x29, 0x5E },
    { 0x32, 0xE9 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderInputDirect
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderInputDirect,
                         4361)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x05, 0x85 },
    { 0x0C, 0x00 },

    { 0x14, 0xF3 },
    { 0x15, 0xA5 },
    { 0x16, 0x5F },
    { 0x17, 0x5E },
    { 0x18, 0xBA },

    { 0x1D, 0x83 },
    { 0x1E, 0xCA },
    { 0x1F, 0x01 },

    { 0x29, 0x5E },
    { 0x32, 0xE9 },
    //
);
