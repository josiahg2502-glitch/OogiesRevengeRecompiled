// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleType
// ******************************************************************
// Generic OOVPA as of 3925 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleType,
                      3925,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov [D3DRS_MultiSampleType],e??
    XREF_ENTRY(0x0B, XREF_D3DRS_MultiSampleType),

    // call D3DDevice_SetRenderTarget
    XREF_ENTRY(0x1E, XREF_D3DDevice_SetRenderTarget),

    // mov ecx,[esp + param_1]
    OV_MATCH(0x05, 0x8B, 0x4C, 0x24, 0x04),

    // call D3DDevice_SetRenderTarget
    OV_MATCH(0x1D, 0xE8),

    // retn 0x04
    OV_MATCH(0x22, 0xC2, 0x04),
    //
);
