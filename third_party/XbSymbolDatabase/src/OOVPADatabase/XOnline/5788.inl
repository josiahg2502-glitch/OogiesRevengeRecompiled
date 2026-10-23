// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XoUpdateLaunchNewImageInternal
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XoUpdateLaunchNewImageInternal_16,
                         5788)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov esi, [ebp + param_1]
    OV_MATCH(0x0B, 0x8B, 0x75, 0x08),

    // mov ebx, [ebp + param_2]
    // cmp ebx, ecx
    OV_MATCH(0x19, 0x8B, 0x5D, 0x0C, 0x3B, 0xD9),

    // mov eax, [ebx]
    // cmp eax, 0x05
    OV_MATCH(0x27, 0x8B, 0x03, 0x83, 0xF8, 0x05),
    //
);
