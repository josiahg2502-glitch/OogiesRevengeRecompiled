// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CXo::XOnlineMatchSessionUpdate
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineMatchSessionUpdate,
                         5233)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    // push esi
    // mov esi, ecx
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x56, 0x8B, 0xF1),
    // test esi, esi
    // jnz eip + $07h
    OV_MATCH(0x06, 0x85, 0xF6, 0x75),

    // push 0
    // push dword ptr [ebp + param_2]
    // mov ecx, esi
    OV_MATCH(0x11, 0x6A, 0x00, 0xFF, 0x75, 0x0C, 0x8B, 0xCE),
    // push dword ptr [ebp + param_1]
    OV_MATCH(0x18, 0xFF, 0x75, 0x08),
    //
);
