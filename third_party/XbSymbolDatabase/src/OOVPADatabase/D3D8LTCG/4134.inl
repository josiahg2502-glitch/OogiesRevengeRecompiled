// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * D3DDevice::MakeSpace
// ******************************************************************
// Almost identical to generic 4134 signature.
// Earliest found is in titles with 5659 build.
OOVPA_SIG_HEADER_XREF(D3DDevice_MakeSpace,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call D3D::MakeRequestedSpace
    XREF_ENTRY(0x0B, XREF_D3D_MakeRequestedSpace),

    // mov eax, [addr]
    OV_MATCH(0x00, 0xA1),

    // push ecx
    OV_MATCH(0x09, 0x51),
    // call D3D::MakeRequestedSpace
    OV_MATCH(0x0A, 0xE8),
    // ret
    OV_MATCH(0x0F, 0xC3), // required to separate this detection from inlined function
    //
);
