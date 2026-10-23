// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XInputSetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputSetState,
                         4831)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x8D },
    { 0x05, 0x81 },
    { 0x06, 0xA3 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },

    { 0x21, 0x8B },
    { 0x22, 0x40 },

    { 0x30, 0xC2 },
    { 0x31, 0x08 },
    //
);

// ******************************************************************
// * XID_fCloseDevice
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XID_fCloseDevice,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call [KeRaiseIrqlToDpcLevel]
    OV_MATCH(0x0C, XREF_KT_FUNC_KeRaiseIrqlToDpcLevel),

    // push ebp; mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // call [KeRaiseIrqlToDpcLevel]
    OV_MATCH(0x0A, 0xFF, 0x15),

    // Possible replacement for accuracy
    // or [esi+0xA2],1
    OV_MATCH(0x2A, 0x80, 0x8E, 0xA2),
    OV_MATCH(0x2F, 0x00, 0x01),
    // lea eax,[ebp-0x0C]
    OV_MATCH(0x31, 0x8D, 0x45, 0xF4),
    // [ebp-0x08],eax
    OV_MATCH(0x34, 0x89, 0x45, 0xF8),
    //
);

// ******************************************************************
// * XInputGetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetState,
                         4831)
OOVPA_SIG_MATCH(

    { 0x0E, 0x8B },
    { 0x0F, 0x8A },
    { 0x10, 0xA3 },

    { 0x1A, 0x6A },
    { 0x1B, 0x57 },

    { 0x1D, 0xEB },
    { 0x1E, 0x3E },

    { 0x3A, 0x8B },
    { 0x3B, 0x8A },
    { 0x3C, 0xA3 },

    { 0x69, 0xC2 },
    { 0x6A, 0x08 },
    //
);

// ******************************************************************
// * XInputGetCapabilities
// ******************************************************************
// Generic OOVPA as of 4831 and newer.
OOVPA_SIG_HEADER_NO_XREF(XInputGetCapabilities,
                         4831)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x55),

    OV_MATCH(0x1F, 0x0F),

    // mov edi,edx; rep stos [edi]
    OV_MATCH(0x37, 0x8B, 0xFA, 0xF3, 0xAB),

    // stos [edi]; mov al,[esi+0x0B]
    OV_MATCH(0x3B, 0xAA, 0x8A, 0x46, 0x0B),

    OV_MATCH(0x3F, 0x88),

    OV_MATCH(0x59, 0x0F, 0xB6),
    //
);

// ******************************************************************
// * XGetDeviceEnumerationStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGetDeviceEnumerationStatus,
                         4831)
OOVPA_SIG_MATCH(

    { 0x04, 0x15 },
    { 0x0A, 0x35 },
    { 0x10, 0x09 },

    { 0x17, 0x00 },
    { 0x18, 0x74 },
    { 0x19, 0x03 },
    { 0x1A, 0x33 },
    { 0x1B, 0xF6 },
    { 0x1C, 0x46 },
    { 0x1D, 0x8A },
    { 0x1E, 0xC8 },
    { 0x1F, 0xFF },

    { 0x25, 0x8B },
    { 0x28, 0xC3 },
    //
);

// ******************************************************************
// * XapiInitProcess
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiInitProcess,
                         4831)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x13, 0x6A },
    { 0x14, 0x0C },
    { 0x15, 0x59 },
    { 0x16, 0x33 },
    { 0x17, 0xC0 },
    { 0x18, 0x8D },
    { 0x19, 0x7D },
    { 0x1A, 0xCC },

    { 0x1D, 0x8D },
    { 0x1E, 0x45 },
    //
);

// ******************************************************************
// * XInputGetDeviceDescription
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetDeviceDescription,
                         4831)
OOVPA_SIG_MATCH(

    { 0x04, 0xEC },
    { 0x0B, 0x15 },

    { 0x13, 0x45 },
    { 0x14, 0x08 },
    { 0x15, 0x8B },
    { 0x16, 0x30 },
    { 0x17, 0x3B },
    { 0x18, 0xF3 },
    { 0x19, 0x88 },
    { 0x1A, 0x4D },
    { 0x1B, 0xFF },
    { 0x1C, 0x0F },
    { 0x1D, 0x84 },

    { 0x30, 0x45 },
    //{ 0x31, 0xF8 }, // 4831 0xF4 vs 5344 0xF8
    //
);

// ******************************************************************
// * XInputSetLightgunCalibration
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XInputSetLightgunCalibration,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call [KeRaiseIrqlToDpcLevel]
    XREF_ENTRY(0x1C, XREF_KT_FUNC_KeRaiseIrqlToDpcLevel),

    // push ebp
    // mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // rep stosd
    // stosw
    OV_MATCH(0x16, 0xF3, 0xAB, 0x66, 0xAB),

    // cmp edx, ebx
    // setnz cl
    OV_MATCH(0x27, 0x3B, 0xD3, 0x0F, 0x95, 0xC1),
    //
);

// ******************************************************************
// * UnhandledExceptionFilter
// ******************************************************************
// Generic OOVPA as of 4831 and newer.
// NOTE: 3911 signature is exactly the same at start of offset 0x1F
OOVPA_SIG_HEADER_XREF(UnhandledExceptionFilter,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov eax,[g_XapiCurrentTopLevelFilter]
    XREF_ENTRY(0x20, XREF_g_XapiCurrentTopLevelFilter), // derived

    // mov eax,fs:[0x20]
    OV_MATCH(0x00, 0x64, 0xA1, 0x20, 0x00),

    // mov eax,[eax+0x250]
    OV_MATCH(0x06, 0x8B, 0x80, 0x50, 0x02, 0x00),

    // mov eax,[g_XapiCurrentTopLevelFilter]
    OV_MATCH(0x1F, 0xA1),

    // push param_1
    OV_MATCH(0x28, 0xFF, 0x74, 0x24, 0x04),

    // call eax
    OV_MATCH(0x2C, 0xFF, 0xD0),

    // cmp eax,-1
    OV_MATCH(0x2E, 0x83, 0xF8, 0xFF),

    // or eax,eax
    OV_MATCH(0x33, 0x0B, 0xC0),

    // xor eax,eax
    OV_MATCH(0x37, 0x33, 0xC0),

    // ret 0x0004
    OV_MATCH(0x39, 0xC2, 0x04),
    //
);

// ******************************************************************
// * mainXapiStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(mainXapiStartup,
                      4831,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call XapiInitProcess
    //XREF_ENTRY(0x01, XREF_XapiInitProcess),

    // call _rtinit
    XREF_ENTRY(0x4D, XREF__rtinit),

    // call _cinit
    XREF_ENTRY(0x52, XREF__cinit),

    // call XapiApplyKernelPatches
    OV_MATCH(0x00, 0xE8),
    // call XapiInitProcess
    OV_MATCH(0x05, 0xE8),
    // mov eax, fs:[0x20]
    OV_MATCH(0x0A, 0x64, 0xA1, 0x20, 0x00),


    // call _rtinit
    OV_MATCH(0x4C, 0xE8),
    // call _cinit
    OV_MATCH(0x51, 0xE8),
    //
);
