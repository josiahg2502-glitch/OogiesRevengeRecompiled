// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XInitDevices
// ******************************************************************
// * NOTE: We are actually intercepting USBD_Init, because
// *       XInitDevices Simply redirects to that function
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInitDevices,
                         5120)
OOVPA_SIG_MATCH(

    { 0x0E, 0x75 },
    { 0x20, 0xBE },
    { 0x2E, 0xC0 },
    { 0x3E, 0xEC },
    { 0x50, 0x0F },
    { 0x5F, 0xE8 },
    { 0x70, 0x5F },
    //
);

// ******************************************************************
// * MU_Init
// ******************************************************************
// Generic OOVPA as of 5120 and newer.
OOVPA_SIG_HEADER_NO_XREF(MU_Init,
                         5120)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    // sub esp, 0x0C
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C),

    // push eax
    // push 0x00
    // push 0x3A
    // lea eax, [ebp-0x0C]
    OV_MATCH(0x8E, 0x50, 0x6A, 0x00, 0x6A, 0x3A, 0x8D, 0x45, 0xF4), // Was 5233 offset 0x8A

    //
);
