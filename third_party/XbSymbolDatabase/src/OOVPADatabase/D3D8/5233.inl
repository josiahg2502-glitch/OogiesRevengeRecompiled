// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_UpdateOverlay
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_UpdateOverlay,
                         5233) // Up to 5849
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x13, 0x89 },
    { 0x14, 0x88 },
    { 0x74, 0x4F },

    { 0x80, 0xE1 },
    { 0x81, 0xFE },
    { 0x82, 0x0F },
    { 0x83, 0xAF },
    { 0x84, 0xCA },
    { 0x85, 0x25 },
    { 0x86, 0xFF },
    { 0x87, 0xFF },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTargetFast
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTargetFast, 5233, 27)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTargetFast,
           5233,
           1 + 27,
           XRefOne)
{

    XREF_ENTRY(0x15, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3DDevice_SetRenderTargetFast+0x00 : push ebp
        { 0x00, 0x55 },

            // D3DDevice_SetRenderTargetFast+0x01 : mov ebp, [esp+8]
            { 0x01, 0x8B },
            { 0x02, 0x6C },
            { 0x03, 0x24 },
            { 0x04, 0x08 },

            // D3DDevice_SetRenderTargetFast+0x05 : push esi
            { 0x05, 0x56 },

            // D3DDevice_SetRenderTargetFast+0x06 : push edi
            { 0x06, 0x57 },

            // D3DDevice_SetRenderTargetFast+0x07 : mov edi, [ds:{addr}]
            { 0x07, 0x8B },
            { 0x08, 0x3D },

            // D3DDevice_SetRenderTargetFast+0x0D : push ebp
            { 0x0D, 0x55 },

            // D3DDevice_SetRenderTargetFast+0x0E : call {addr}
            { 0x0E, 0xE8 },

            // D3DDevice_SetRenderTargetFast+0x13 : mov eax, [edi+{offset}]
            { 0x13, 0x8B },
            { 0x14, 0x87 },

            // D3DDevice_SetRenderTargetFast+0x19 : mov ecx, [eax+0x14]
            { 0x19, 0x8B },
            { 0x1A, 0x48 },
            { 0x1B, 0x14 },

            // D3DDevice_SetRenderTargetFast+0x1C : test ecx, ecx
            { 0x1C, 0x85 },
            { 0x1D, 0xC9 },

            // D3DDevice_SetRenderTargetFast+0x1E : jz + 0x02
            { 0x1E, 0x74 },
            { 0x1F, 0x02 },

            { 0x3C, 0x89 },
            { 0x5F, 0x8B },
            { 0x7A, 0x04 },
            { 0x99, 0x04 },
            { 0xB8, 0x02 },
            { 0xD7, 0x0C },
            { 0xF6, 0xC5 },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetVisibilityTestResult
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVisibilityTestResult,
                         5233)
OOVPA_SIG_MATCH(

    { 0x0E, 0x08 },
    { 0x10, 0xFF },
    { 0x2A, 0x16 },
    { 0x3C, 0x76 },
    { 0x3F, 0x0C },
    { 0x51, 0x0A },
    { 0x5F, 0x0C },
    //
);
