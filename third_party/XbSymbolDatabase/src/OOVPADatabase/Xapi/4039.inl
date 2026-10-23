// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XCalculateSignatureBegin
// ******************************************************************
// TODO: Need to find out if XCalculateSignatureBegin had been changed
//       in 3950 and lower.
// Generic OOVPA as of 4034? and newer.
OOVPA_SIG_HEADER_NO_XREF(XCalculateSignatureBegin,
                         4034)
OOVPA_SIG_MATCH(

    // mov eax,ds:[0x00010118]
    OV_MATCH(0x00, 0xA1, 0x18, 0x01, 0x01, 0x00),

    // push [eax+0x08]
    OV_MATCH(0x05, 0xFF, 0x70, 0x08),

    // push [esp+0x08]
    OV_MATCH(0x08, 0xFF, 0x74, 0x24, 0x08),

    // call XCalculateSignatureBeginEx
    OV_MATCH(0x0C, 0xE8),

    // ret 0x0004
    OV_MATCH(0x11, 0xC2, 0x04, 0x00),
    //
);
