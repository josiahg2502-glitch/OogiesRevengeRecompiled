// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * g_DeviceType_SBC
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceType_SBC,
                         4242)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceTypeInfoTableBegin
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceTypeInfoTableBegin,
                         4242)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceTypeInfoTableEnd
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceTypeInfoTableEnd,
                         4242)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * XInputOpen
// ******************************************************************
// Generic OOVPA as of 4242 and newer.
OOVPA_SIG_HEADER_XREF(XInputOpen,
                      4242,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call GetTypeInformation
    XREF_ENTRY(0x0C, XREF_GetTypeInformation),

    // call SetLastError
    XREF_ENTRY(0x17, XREF_SetLastError),

    // push 0x57
    OV_MATCH(0x14, 0x6A, 0x57),

    // jmp +0x33
    OV_MATCH(0x1D, 0xEB, 0x33),

    // add edx, 0x10
    OV_MATCH(0x33, 0x83, 0xC2, 0x10),

    // jmp +0x06
    OV_MATCH(0x47, 0x75, 0x06),

    // leave
    OV_MATCH(0x52, 0xC9),

    // retn 0x10
    OV_MATCH(0x53, 0xC2, 0x10),
    //
);

// ******************************************************************
// * XInputGetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetState,
                         4242)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x56 },

    { 0x0A, 0x8B },
    { 0x0B, 0x54 },
    { 0x0C, 0x24 },
    { 0x0D, 0x0C },
    { 0x0E, 0x8B },
    { 0x0F, 0x8A },
    { 0x10, 0xA3 },
    { 0x11, 0x00 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },

    { 0x5B, 0xF3 },
    //
);

// ******************************************************************
// * XInputSetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputSetState,
                         4242)
OOVPA_SIG_MATCH(

    // XInputSetState+0x04 : lea eax, [ecx+0x0A3]
    { 0x04, 0x8D },
    { 0x05, 0x81 },
    { 0x06, 0xA3 },

    // XInputSetState+0x15 : push 0x57
    { 0x15, 0x6A },
    { 0x16, 0x57 },

    // XInputSetState+0x18 : jmp +0x19
    { 0x18, 0xEB },
    { 0x19, 0x19 },

    // XInputSetState+0x2B : mov [edx+0x41], al
    { 0x2B, 0x88 },
    { 0x2C, 0x42 },
    { 0x2D, 0x41 },

    // XInputSetState+0x33 : retn 0x08
    { 0x33, 0xC2 },
    { 0x34, 0x08 },
    //
);

// ******************************************************************
// * XMountMUA
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XMountMUA,
                      4242,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3A, XREF_g_XapiMountedMUs), // derived
    XREF_ENTRY(0xE7, XREF_XapiMapLetterToDirectory),

    { 0x22, 0x8A },
    { 0x3E, 0x89 },
    { 0x5E, 0x5C },
    { 0x7E, 0xF4 },
    { 0x9E, 0x50 },
    { 0xBE, 0xF8 },
    { 0xDE, 0x8D },
    { 0xFE, 0x09 },
    //
);

// ******************************************************************
// * XFormatUtilityDrive
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XFormatUtilityDrive,
                         4242)
OOVPA_SIG_MATCH(

    { 0x02, 0xEC },
    { 0x10, 0x50 },
    { 0x1E, 0xEC },

    { 0x40, 0xF8 },
    { 0x41, 0x8D },
    { 0x42, 0x45 },
    { 0x43, 0xE4 },
    { 0x44, 0x50 },
    { 0x45, 0x8D },
    { 0x46, 0x45 },
    { 0x47, 0xF4 },

    { 0x6D, 0x33 },
    //
);

// ******************************************************************
// * XMountMURootA
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XMountMURootA,
                      4242,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3A, XREF_g_XapiMountedMUs), // derived

    { 0x16, 0xBF },
    { 0x22, 0x8A },
    { 0x39, 0x05 },

    { 0x50, 0x55 },
    { 0x51, 0x58 },
    { 0x52, 0xE9 },
    { 0x53, 0x0E },
    { 0x54, 0x01 },
    { 0x55, 0x00 },
    { 0x56, 0x00 },
    { 0x57, 0x66 },

    { 0x72, 0xE8 },
    //
);

// ******************************************************************
// * XapiInitProcess
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiInitProcess,
                         4242)
OOVPA_SIG_MATCH(

    // XapiInitProcess+0x03 : sub esp, 30h
    { 0x05, 0x30 },

    // XapiInitProcess+0x0F : push 0x0C
    { 0x0F, 0x6A },
    { 0x10, 0x0C },

    // XapiInitProcess+0x17 : repe stosd
    { 0x17, 0xF3 },
    { 0x18, 0xAB },

    // XapiInitProcess+0x42 : jnz +0x0B
    { 0x42, 0x75 },
    { 0x43, 0x0B },
    //
);

// ******************************************************************
// * XUnmountMU
// ******************************************************************
// Generic OOVPA as of 4242 and newer.
OOVPA_SIG_HEADER_XREF(XUnmountMU,
                      4242,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x2C, XREF_g_XapiMountedMUs), // derived
    XREF_ENTRY(0x50, XREF_XUnmountAlternateTitleA), // Was 3911 offset 0x38

    // push EBP
    // mov EBP, ESP
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // push 0x20
    // push 0x01
    // xor edi, edi
    OV_MATCH(0x74, 0x6A, 0x20, 0x6A, 0x01, 0x33, 0xFF), // Was 3911 offset 0x5D

    //
);

// ******************************************************************
// * MU_Init
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(MU_Init,
                         4242)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    // sub esp, 0x0C // Was 3911 opcode ..., 0x10
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C),

    // push eax
    // push 0x00
    // push 0x3A
    // lea eax, [ebp-0x0C] // Was 3911 opcode ...-0x10]
    OV_MATCH(0x8A, 0x50, 0x6A, 0x00, 0x6A, 0x3A, 0x8D, 0x45, 0xF4), // Was 3911 offset 0x95

    //
);

// ******************************************************************
// * XReadMUMetaData
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XReadMUMetaData,
                      4242,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x31, XREF_g_XapiMountedMUs),

    // push ebp
    // mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov WORD PTR [ebp-0x0E],0x3E
    OV_MATCH(0x51, 0x66, 0xC7, 0x45, 0xF2, 0x3E, 0x00),
    //
);

// ******************************************************************
// * GetTypeInformation
// ******************************************************************
// Generic OOVPA as of 4242 and newer.
OOVPA_SIG_HEADER_XREF(GetTypeInformation,
                      4242,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov eax,g_DeviceTypeInfoTableBegin
    XREF_ENTRY(0x01, XREF_g_DeviceTypeInfoTableBegin), // derived

    // mov esi,g_DeviceTypeInfoTableEnd
    XREF_ENTRY(0x09, XREF_g_DeviceTypeInfoTableEnd), // derived

    // mov eax,g_DeviceTypeInfoTableBegin
    OV_MATCH(0x00, 0xB8),
    // push esi
    // mov edx,eax
    // mov esi,g_DeviceTypeInfoTableEnd
    OV_MATCH(0x05, 0x56, 0x8B, 0xD0, 0xBE),
    // cmp edx,esi
    OV_MATCH(0x0D, 0x3B, 0xD6),
    // jnc +0x12
    OV_MATCH(0x0F, 0x73, 0x12),
    // mov edx,dword [eax]
    OV_MATCH(0x11, 0x8B, 0x10),
    // test edx,edx
    OV_MATCH(0x13, 0x85, 0xD2),

    // cmp dword [edx + 0x04],ecx
    OV_MATCH(0x17, 0x39, 0x4A, 0x04),
    // JZ +0x0B
    OV_MATCH(0x1A, 0x74, 0x0B),
    // add eax,0x04
    OV_MATCH(0x1C, 0x83, 0xC0, 0x04),

    // ret
    OV_MATCH(0x26, 0xC3),

    // ret
    OV_MATCH(0x2A, 0xC3),
    //
);

// ******************************************************************
// * GetTypeInformation2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(GetTypeInformation2,
                      4242,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov eax,g_DeviceTypeInfoTableBegin
    XREF_ENTRY(0x06, XREF_g_DeviceTypeInfoTableBegin), // derived

    // mov esi,g_DeviceTypeInfoTableEnd
    XREF_ENTRY(0x0E, XREF_g_DeviceTypeInfoTableEnd), // derived

    // mov eax,g_DeviceTypeInfoTableBegin
    OV_MATCH(0x05, 0xB8),
    // push edi
    // mov edi,eax
    // mov esi,g_DeviceTypeInfoTableEnd
    OV_MATCH(0x0A, 0x57, 0x8B, 0xF8, 0xBE),

    // cmp edi,esi
    OV_MATCH(0x14, 0x3B, 0xFE),
    // jnc +0x13
    OV_MATCH(0x16, 0x73, 0x13),

    // mov edi,dword [eax]
    OV_MATCH(0x18, 0x8B, 0x38),
    // test edi,edi
    OV_MATCH(0x1A, 0x85, 0xFF),

    // cmp dword [edi],cl
    OV_MATCH(0x1E, 0x38, 0x0F),
    // JZ +0x0F
    OV_MATCH(0x20, 0x74, 0x0F),

    // add eax,0x04
    OV_MATCH(0x24, 0x83, 0xC0, 0x04),

    // ret
    OV_MATCH(0x30, 0xC3),

    // jmp -0x0A
    OV_MATCH(0x35, 0xEB, 0xF6),
    //
);
