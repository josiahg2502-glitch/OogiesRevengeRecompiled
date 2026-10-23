// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 3947, 11)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget,
           3947,
           1 + 11,
           XRefOne)
{

    XREF_ENTRY(0x1D, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0xXX
        OV_MATCH(0x00, 0x83, 0xEC),
            //OV_MATCH(0x02, 0x30), // 3947 0x2C vs 3948 0x30

            // D3DDevice_SetRenderTarget+0x54 : mov eax, 0x00000001
            OV_MATCH(0x54, 0xB8, 0x01, 0x00),

            // D3DDevice_SetRenderTarget+0x59 : and ecx, 0x0F
            OV_MATCH(0x59, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0x60 : shr eax,0x0C
            OV_MATCH(0x60, 0xC1, 0xE8, 0x0C),
    }
OOVPA_END;
