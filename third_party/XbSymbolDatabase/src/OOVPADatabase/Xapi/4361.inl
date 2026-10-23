// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * CreateThread
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CreateThread,
                         4361)
OOVPA_SIG_MATCH(

    // CreateThread+0x0A : mov eax, ds:10130h
    { 0x0A, 0xA1 },
    { 0x0B, 0x30 },
    { 0x0C, 0x01 },

    // CreateThread+0x1C : and ecx, 0xFFFFFF01
    { 0x1C, 0x81 },
    { 0x1D, 0xE1 },
    { 0x1E, 0x01 },

    // CreateThread+0x6B : retn 0x18
    { 0x6B, 0xC2 },
    { 0x6C, 0x18 },
    //
);

// ******************************************************************
// * CloseHandle
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CloseHandle,
                         4361)
OOVPA_SIG_MATCH(

    // CloseHandle+0x00 : push [esp+4]
    { 0x00, 0xFF },
    { 0x01, 0x74 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // CloseHandle+0x04 : call ds:[addr]
    { 0x04, 0xFF },
    { 0x05, 0x15 },

    // CloseHandle+0x11 : jmp +0x08
    { 0x11, 0xEB },
    { 0x12, 0x08 },

    // CloseHandle+0x1B : retn 4
    { 0x1B, 0xC2 },
    { 0x1C, 0x04 },
    //
);

// ******************************************************************
// * XapiSetupPerTitleDriveLetters
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiSetupPerTitleDriveLetters,
                         4361)
OOVPA_SIG_MATCH(

    // XapiSetupPerTitleDriveLetters+0x09 : lea eax, [ebp-0x0C]
    { 0x09, 0x8D },
    { 0x0A, 0x45 },
    { 0x0B, 0xF4 },

    // XapiSetupPerTitleDriveLetters+0x17 : edd esp, 0x0C
    { 0x17, 0x83 },
    { 0x18, 0xC4 },
    { 0x19, 0x0C },

    // XapiSetupPerTitleDriveLetters+0x35 : jl 0x1A
    { 0x35, 0x7C },
    { 0x36, 0x1A },

    // XapiSetupPerTitleDriveLetters+0x52 : retn 0x08
    { 0x52, 0xC2 },
    { 0x53, 0x08 },
    //
);

// ******************************************************************
// * mainCRTStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(mainCRTStartup,
                      4361,
                      XRefThree)
OOVPA_SIG_MATCH(

    // push mainXapiStartup
    XREF_ENTRY(0x4C, XREF_mainXapiStartup),

    // call CreateThread
    XREF_ENTRY(0x55, XREF_CreateThread),

    // call XapiBootToDash
    XREF_ENTRY(0x65, XREF_XapiBootToDash),

    // mov ecx, [...]
    OV_MATCH(0x00, 0x8B, 0x0D),
    // sub eax, [...]
    OV_MATCH(0x06, 0xA1),

    // mov eax, [...]
    OV_MATCH(0x18, 0xA1),
    // sub eax, [...]
    OV_MATCH(0x1D, 0x2B, 0x05),

    // and eax, -16
    OV_MATCH(0x2F, 0x83, 0xE0, 0xF0),
    // push -4
    OV_MATCH(0x32, 0x6A, 0xFC),

    // push mainXapiStartup
    OV_MATCH(0x4B, 0x68),

    // call CreateThread
    OV_MATCH(0x54, 0xE8),

    // call XapiBootToDash
    OV_MATCH(0x64, 0xE8),
    //
);
