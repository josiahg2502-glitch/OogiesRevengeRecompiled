// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * _tls_array
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(_tls_array,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * _tls_index
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(_tls_index,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceType_Gamepad
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceType_Gamepad,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceType_IRDongle
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceType_IRDongle,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceType_Keyboard
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceType_Keyboard,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceType_Mouse
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceType_Mouse,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_DeviceType_MU
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_DeviceType_MU,
                         3911)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_XapiAltLett_MU
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_XapiAltLett_MU,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_XapiCurrentTopLevelFilter
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_XapiCurrentTopLevelFilter,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * g_XapiMountedMUs
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(g_XapiMountedMUs,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * XapiCurrentFiber OFFSET
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(XapiCurrentFiber_OFFSET,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * XapiLastErrorCode OFFSET
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(XapiLastErrorCode_OFFSET,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * XapiThreadFiberData OFFSET
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(XapiThreadFiberData_OFFSET,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * XapiThreadNotifyRoutineList
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(XapiThreadNotifyRoutineList,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * XGetSectionSize
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(XGetSectionSize,
                         0)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * GetExitCodeThread
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(GetExitCodeThread,
                         3911)
OOVPA_SIG_MATCH(

    // GetExitCodeThread+0x00 : push ebp
    OV_MATCH(0x00, 0x55),

    // GetExitCodeThread+0x03 : lea eax, [ebp+0x08]
    OV_MATCH(0x03, 0x8D, 0x45, 0x08),

    // GetExitCodeThread+0x1A : mov ecx, dword ptr [ebp+0x08]
    OV_MATCH(0x1A, 0x8B, 0x4D, 0x08),

    // Unique offset for asm code.
    // GetExitCodeThread+0x2B : mov eax, 0x0103
    OV_MATCH(0x2B, 0xB8, 0x03, 0x01),

    // GetExitCodeThread+0x49 : retn 0x08
    OV_MATCH(0x49, 0xC2, 0x08),
    //
);

// ******************************************************************
// * XInitDevices
// ******************************************************************
// * NOTE: We are actually intercepting USBD_Init, because
// *       XInitDevices Simply redirects to that function
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInitDevices,
                         3911)
OOVPA_SIG_MATCH(

    // XInitDevices+0x03 : push 0xB4
    OV_MATCH(0x03, 0x68, 0xB4),

    // XInitDevices+0x10 : jmp +0x13
    OV_MATCH(0x10, 0x74, 0x13),

    // XInitDevices+0x5B : movzx eax, byte ptr [esi+0xA1]
    OV_MATCH(0x5B, 0x0F, 0xB6, 0x86, 0xA1),

    // XInitDevices+0x8B : retn 8
    OV_MATCH(0x8B, 0xC2, 0x08),
    //
);

// ******************************************************************
// * CreateMutexA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(CreateMutexA,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call XapiFormatObjectAttributes
    XREF_ENTRY(0x18, XREF_XapiFormatObjectAttributes),

    // sub esp, 0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // push 0x000000B7
    OV_MATCH(0x39, 0x68, 0xB7, 0x00),

    // mov eax, [ebp+0x10]
    OV_MATCH(0x47, 0x8B, 0x45, 0x10),
    //
);

// ******************************************************************
// * CreateThread
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(CreateThread,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // push XapiThreadStartup
    XREF_ENTRY(0x13, XREF_XapiThreadStartup),

    // push ebp; mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov eax,[0x00010130]
    OV_MATCH(0x0A, 0xA1, 0x30, 0x01, 0x01, 0x00),

    // push XapiThreadStartup
    OV_MATCH(0x12, 0x68),

    // mov ecx,0xFFFFFF01
    OV_MATCH(0x1C, 0x81, 0xE1, 0x01, 0xFF, 0xFF),
    //
);

// ******************************************************************
// * SetThreadPriority
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(SetThreadPriority,
                         3911)
OOVPA_SIG_MATCH(
    // push ebp
    OV_MATCH(0x00, 0x55),

    // push 0x10
    OV_MATCH(0x22, 0x6A, 0x10),

    // cmp eax, 0xF1
    OV_MATCH(0x26, 0x83, 0xF8, 0xF1),

    // push 0xF0
    OV_MATCH(0x2B, 0x6A, 0xF0),

    // ret 0x0008
    OV_MATCH(0x4F, 0xC2, 0x08),
    //
);

// ******************************************************************
// * OutputDebugStringA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(OutputDebugStringA,
                         3911)
OOVPA_SIG_MATCH(

    // push ebp
    OV_MATCH(0x00, 0x55),

    // mov dl,[eax]
    OV_MATCH(0x0E, 0x8A, 0x10),

    // test dl,dl
    OV_MATCH(0x11, 0x84, 0xD2),

    // Unique asm code for first Interrupt 0x2D.
    // Interrupt 0x2D, Interrupt 3
    OV_MATCH(0x2B, 0xCD, 0x2D, 0xCC),

    // leave; ret 0x0004
    OV_MATCH(0x2F, 0xC2, 0x04),
    //
);

// ******************************************************************
// * OutputDebugStringW
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(OutputDebugStringW,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call [OutputDebugStringA]
    XREF_ENTRY(0x35, XREF_OutputDebugStringA),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // push 0x01
    OV_MATCH(0x14, 0x6A, 0x01),

    // push [ebp-0x04]
    OV_MATCH(0x31, 0xFF, 0x75, 0xFC),

    // leave; ret 0x0004
    OV_MATCH(0x49, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XapiInitProcess
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiInitProcess,
                         3911)
OOVPA_SIG_MATCH(

    // XapiInitProcess+0x03 : sub esp, 30h
    { 0x05, 0x30 },

    // XapiInitProcess+0x0F : push 0x0C
    { 0x0F, 0x6A },
    { 0x10, 0x0C },

    // XapiInitProcess+0x17 : repe stosd
    { 0x17, 0xF3 },
    { 0x18, 0xAB },

    // XapiInitProcess+0x42 : jnz +0x0A
    { 0x42, 0x75 },
    { 0x43, 0x0A },
    //
);

// ******************************************************************
// * XapiBootToDash
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiBootToDash,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call XLaunchNewImageA
    XREF_ENTRY(0x53, XREF_XLaunchNewImageA),

    // sub esp, 0x0C00
    OV_MATCH(0x03, 0x81, 0xEC),
    OV_MATCH(0x06, 0x0C),

    // mov eax, ds:0x10118
    OV_MATCH(0x09, 0xA1, 0x18, 0x01, 0x01),

    // repe stosd
    OV_MATCH(0x25, 0xF3, 0xAB),

    // retn 0x0C
    OV_MATCH(0x59, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * XRegisterThreadNotifyRoutine
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XRegisterThreadNotifyRoutine,
                         3911)
OOVPA_SIG_MATCH(

    // XRegisterThreadNotifyRoutine+0x0D : cmp [esp+0x0C], 0
    { 0x0D, 0x83 },
    { 0x0E, 0x7C },
    { 0x0F, 0x24 },
    { 0x10, 0x0C },

    // XRegisterThreadNotifyRoutine+0x12 : jz +0x1C
    { 0x12, 0x74 },
    { 0x13, 0x1C },

    // XRegisterThreadNotifyRoutine+0x24 : mov [eax+4], ecx
    { 0x24, 0x89 },
    { 0x25, 0x48 },
    { 0x26, 0x04 },

    // XRegisterThreadNotifyRoutine+0x46 : retn 0x08
    { 0x46, 0xC2 },
    { 0x47, 0x08 },
    //
);

// ******************************************************************
// * GetTimeZoneInformation
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(GetTimeZoneInformation,
                         3911)
OOVPA_SIG_MATCH(

    { 0x05, 0x28 },
    { 0x2E, 0x28 },
    { 0x4F, 0x59 },
    { 0x56, 0xAB },
    { 0x8C, 0xC0 },
    { 0xB9, 0x80 },
    { 0xF7, 0x99 },
    //
);

// ******************************************************************
// * XCalculateSignatureBegin
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XCalculateSignatureBegin,
                         3911)
OOVPA_SIG_MATCH(

    // XCalculateSignatureBegin+0x01 : push 0x7C; push 0
    OV_MATCH(0x01, 0x6A, 0x7C, 0x6A, 0x00),

    // XCalculateSignatureBegin+0x10 : push 0x08
    OV_MATCH(0x10, 0x6A, 0x08),

    // XCalculateSignatureBegin+0x2E : push 0x10
    OV_MATCH(0x2E, 0x6A, 0x10),

    // XCalculateSignatureBegin+0x3B : retn 0x04
    OV_MATCH(0x3B, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XGetDevices
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGetDevices,
                         3911)
OOVPA_SIG_MATCH(

    // XGetDevices+0x07 : mov edx, [esp+arg_0]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },

    // XGetDevices+0x0D : and [edx+4], 0
    { 0x0D, 0x83 },
    { 0x0E, 0x62 },
    { 0x0F, 0x04 },
    { 0x10, 0x00 },

    // XGetDevices+0x11 : mov cl, al
    { 0x11, 0x8A },
    { 0x12, 0xC8 },

    // XGetDevices+0x16 : call KfLowerIrql
    { 0x16, 0xFF },
    { 0x17, 0x15 },

    // XGetDevices+0x1F : retn 4
    { 0x1F, 0xC2 },
    { 0x20, 0x04 },
    //
);

// ******************************************************************
// * XGetDeviceChanges
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGetDeviceChanges,
                         3911)
OOVPA_SIG_MATCH(

    // XGetDeviceChanges+0x00 : push ebp
    OV_MATCH(0x00, 0x55),

    // XGetDeviceChanges+0x07 : xor eax, eax
    OV_MATCH(0x07, 0x33, 0xC0),

    // XGetDeviceChanges+0x33 : not edx
    OV_MATCH(0x33, 0xF7, 0xD2),

    // XGetDeviceChanges+0x42 : or edx, edi
    OV_MATCH(0x42, 0x0B, 0xD7),

    // XGetDeviceChanges+0x51 : mov cl, al
    OV_MATCH(0x51, 0x8A, 0xC8),
    //
);

// ******************************************************************
// * XInputOpen
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XInputOpen,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // cmp dword [ebp + 0x08],g_DeviceType_Gamepad
    XREF_ENTRY(0x0B, XREF_g_DeviceType_Gamepad), // derived

    // cmp dword [ebp + 0x08],g_DeviceType_Keyboard
    XREF_ENTRY(0x18, XREF_g_DeviceType_Keyboard), // derived

    // cmp dword [ebp + 0x08],g_DeviceType_IRDongle
    XREF_ENTRY(0x25, XREF_g_DeviceType_IRDongle), // derived

    // jmp +0x0B
    OV_MATCH(0x20, 0xEB, 0x0B),

    // jnz +0x3D
    OV_MATCH(0x29, 0x75, 0x3D),

    // add edx,0x10
    OV_MATCH(0x4A, 0x83, 0xC2, 0x10),

    // jmp +0x09
    OV_MATCH(0x66, 0xEB, 0x09),

    // push 0x57
    OV_MATCH(0x68, 0x6A, 0x57),
    //
);

// ******************************************************************
// * XID_fCloseDevice
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XID_fCloseDevice,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call [KeRaiseIrqlToDpcLevel]
    XREF_ENTRY(0x0C, XREF_KT_FUNC_KeRaiseIrqlToDpcLevel),

    // push ebp; mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // call [KeRaiseIrqlToDpcLevel]
    OV_MATCH(0x0A, 0xFF, 0x15),

    // lea eax,[ebp-0x0C]
    OV_MATCH(0x3E, 0x8D, 0x45, 0xF4),
    // [ebp+...],eax
    OV_MATCH(0x41, 0x89, 0x45),
    //
);

// ******************************************************************
// * XInputClose
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XInputClose,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // XInputClose+0x05 : call [fCloseDevice]
    XREF_ENTRY(0x05, XREF_XID_fCloseDevice),

    // XInputClose+0x00 : mov ecx, [esp+0x04]
    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // XInputClose+0x04 : call [fCloseDevice]
    { 0x04, 0xE8 },

    // XInputClose+0x09 : retn 0x04
    { 0x09, 0xC2 },
    { 0x0A, 0x04 },
    //
);

// ******************************************************************
// * XInputGetCapabilities
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetCapabilities,
                         3911)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x55),

    OV_MATCH(0x0F, 0x15),

    OV_MATCH(0x1E, 0x0F, 0x84),

    // mov edi,edx; rep stos [edi]
    OV_MATCH(0x36, 0x8B, 0xFA, 0xF3, 0xAB),

    // stos [edi]; mov al,[esi+0x0B]
    OV_MATCH(0x3A, 0xAA, 0x8A, 0x46, 0x0B),

    OV_MATCH(0x3E, 0x88),
    //
);

// ******************************************************************
// * XInputGetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetState,
                         3911)
OOVPA_SIG_MATCH(

    // XInputGetState+0x0E : cmp byte ptr [edx+0x0A3], 1
    { 0x0E, 0x80 },
    { 0x0F, 0xBA },
    { 0x10, 0xA3 },
    { 0x14, 0x01 },

    // XInputGetState+0x17 : push 0x57
    { 0x17, 0x6A },
    { 0x18, 0x57 },

    // XInputGetState+0x1A : jmp +0x46
    { 0x1A, 0xEB },
    { 0x1B, 0x46 },

    // XInputGetState+0x28 : mov ebx, 0x048F
    { 0x28, 0xBB },
    { 0x29, 0x8F },
    { 0x2A, 0x04 },

    // XInputGetState+0x6E : retn 8
    { 0x6E, 0xC2 },
    { 0x6F, 0x08 },
    //
);

// ******************************************************************
// * XInputSetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputSetState,
                         3911)
OOVPA_SIG_MATCH(

    // XInputSetState+0x04 : lea eax, [ecx+0x0A3]
    { 0x04, 0x8D },
    { 0x05, 0x81 },
    { 0x06, 0xA3 },

    // XInputSetState+0x0F : push 0x57
    { 0x0F, 0x6A },
    { 0x10, 0x57 },

    // XInputSetState+0x12 : jmp +0x21
    { 0x12, 0xEB },
    { 0x13, 0x21 },

    // XInputSetState+0x2D : mov [edx+0x41], al
    { 0x2D, 0x88 },
    { 0x2E, 0x42 },
    { 0x2F, 0x41 },

    // XInputSetState+0x35 : retn 0x08
    { 0x35, 0xC2 },
    { 0x36, 0x08 },
    //
);

// ******************************************************************
// * SetThreadPriorityBoost
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(SetThreadPriorityBoost,
                         3911) // generic version
OOVPA_SIG_MATCH(

    // SetThreadPriorityBoost+0x0D : push [ebp+0x08]
    { 0x0D, 0xFF },
    { 0x0E, 0x75 },
    { 0x0F, 0x08 },

    // SetThreadPriorityBoost+0x18 : jl +0x20
    { 0x18, 0x7C },
    { 0x19, 0x20 },

    // SetThreadPriorityBoost+0x1F : setnz al
    { 0x1F, 0x0F },
    { 0x20, 0x95 },
    { 0x21, 0xC0 },

    // SetThreadPriorityBoost+0x2C : mov ecx, [ebp+0x08]
    { 0x2C, 0x8B },
    { 0x2D, 0x4D },
    //
);

// ******************************************************************
// * GetThreadPriority
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(GetThreadPriority,
                         3911)
OOVPA_SIG_MATCH(

    // GetThreadPriority+0x0D : push [ebp+0x08]
    { 0x0D, 0xFF },
    { 0x0E, 0x75 },
    { 0x0F, 0x08 },

    // GetThreadPriority+0x18 : jl +0x2B
    { 0x18, 0x7C },
    { 0x19, 0x2B },

    // GetThreadPriority+0x2F : cmp esi, 0xF0
    { 0x2F, 0x83 },
    { 0x30, 0xFE },
    { 0x31, 0xF0 },

    // GetThreadPriority+0x37 : mov ecx, [ebp+0x08]
    { 0x37, 0x8B },
    { 0x38, 0x4D },
    //
);

// ******************************************************************
// * CreateFiber
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CreateFiber,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x56 },
    { 0x05, 0x57 },
    { 0x06, 0x33 },
    { 0x07, 0xFF },
    { 0x08, 0x3B },
    { 0x09, 0xC7 },
    { 0x0A, 0x75 },
    { 0x0B, 0x05 },
    { 0x0C, 0xA1 },
    { 0x0D, 0x30 },
    { 0x0E, 0x01 },
    { 0x0F, 0x01 },
    { 0x10, 0x00 },
    { 0x11, 0xB9 },
    { 0x12, 0x00 },
    { 0x13, 0x30 },
    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0x3B },
    { 0x17, 0xC1 },
    { 0x18, 0x73 },
    { 0x19, 0x02 },
    { 0x1A, 0x8B },
    { 0x1B, 0xC1 },
    { 0x1C, 0x8D },
    { 0x1D, 0xB0 },
    { 0x1E, 0xFF },
    { 0x1F, 0x0F },
    //
);

// ******************************************************************
// * DeleteFiber
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DeleteFiber,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0xFF },
    { 0x05, 0x70 },
    { 0x06, 0x08 },
    { 0x07, 0xFF },
    { 0x08, 0x70 },
    { 0x09, 0x04 },
    { 0x0A, 0xFF },
    { 0x0B, 0x15 },

    { 0x10, 0xC2 },
    { 0x11, 0x04 },
    { 0x12, 0x00 },
    //
);

// ******************************************************************
// * SwitchToFiber
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(SwitchToFiber,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x06, 0x64 },
    { 0x07, 0x8B },
    { 0x08, 0x0D },
    { 0x09, 0x04 },
    { 0x0A, 0x00 },
    { 0x0B, 0x00 },
    { 0x0C, 0x00 },
    { 0x0D, 0x8B },
    { 0x0E, 0x44 },
    { 0x0F, 0x24 },
    { 0x10, 0x04 },
    { 0x11, 0x55 },
    { 0x12, 0x56 },
    { 0x13, 0x57 },
    { 0x14, 0x53 },
    { 0x15, 0x64 },
    { 0x16, 0xFF },
    { 0x17, 0x35 },
    { 0x18, 0x00 },
    { 0x19, 0x00 },
    { 0x1A, 0x00 },
    { 0x1B, 0x00 },
    { 0x1C, 0x8B },
    { 0x1D, 0x14 },
    { 0x1E, 0x91 },
    { 0x1F, 0x8B },
    //
);

// ******************************************************************
// * ConvertThreadToFiber
// ******************************************************************
OOVPA_SIG_HEADER_XREF(ConvertThreadToFiber,
                      3911,
                      XRefFour)
OOVPA_SIG_MATCH(

    // mov eax,[_tls_index]
    XREF_ENTRY(0x01, XREF__tls_index), // derived

    // mov ecx,fs:[_tls_array]
    XREF_ENTRY(0x08, XREF__tls_array), // derived

    // lea ecx,[edx+XapiThreadFiberData_OFFSET]
    XREF_ENTRY(0x15, XREF_XapiThreadFiberData_OFFSET), // derived

    // mov [edx+XapiCurrentFiber_OFFSET],ecx
    XREF_ENTRY(0x2D, XREF_XapiCurrentFiber_OFFSET), // derived

    // mov eax,[_tls_index]
    OV_MATCH(0x00, 0xA1),

    // mov ecx,fs:[_tls_array]
    OV_MATCH(0x05, 0x64, 0x8B, 0x0D),

    // and [ecx+0x08],0x00
    OV_MATCH(0x24, 0x83, 0x61, 0x08, 0x00),

    // mov [ecx+0x04],eax
    OV_MATCH(0x28, 0x89, 0x41, 0x04),

    // ret 0x0004
    OV_MATCH(0x33, 0xC2, 0x04),
    //
);

// ******************************************************************
// * SignalObjectAndWait
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(SignalObjectAndWait,
                         3911) // generic version
OOVPA_SIG_MATCH(

    { 0x07, 0x75 },
    { 0x12, 0x8B },
    { 0x19, 0x01 },
    { 0x26, 0x85 },
    { 0x2B, 0x7D },
    { 0x34, 0x00 },
    { 0x3F, 0x83 },
    { 0x46, 0x00 },
    //
);

// ******************************************************************
// * QueueUserAPC
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(QueueUserAPC,
                         3911) // generic version
OOVPA_SIG_MATCH(

    { 0x03, 0x74 },
    { 0x08, 0x24 },
    { 0x0F, 0xFF },
    { 0x12, 0x18 },
    { 0x19, 0x33 },
    { 0x1C, 0xC0 },
    { 0x21, 0xC1 },
    //
);

// ******************************************************************
// * QueryPerformanceCounter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(QueryPerformanceCounter,
                         3911) // generic version
OOVPA_SIG_MATCH(
    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x0F },
    { 0x05, 0x31 },
    { 0x06, 0x89 },
    { 0x07, 0x01 },
    { 0x08, 0x89 },
    { 0x09, 0x51 },
    { 0x0A, 0x04 },
    { 0x0B, 0x33 },
    { 0x0C, 0xC0 },
    { 0x0D, 0x40 },
    { 0x0E, 0xC2 },
    { 0x0F, 0x04 },
    { 0x10, 0x00 },
    //
);

// ******************************************************************
// * lstrcmpiW
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(lstrcmpiW,
                         3911)
OOVPA_SIG_MATCH(

    { 0x07, 0x56 },
    { 0x0F, 0x01 },
    { 0x10, 0xE8 },
    { 0x19, 0x39 },
    { 0x22, 0x0E },
    { 0x2D, 0x59 },
    { 0x34, 0xEB },
    { 0x3D, 0x03 },
    //
);

// ******************************************************************
// * XMountAlternateTitleA
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XMountAlternateTitleA,
                         3911)
OOVPA_SIG_MATCH(

    { 0x04, 0xEC },

    { 0x0F, 0x18 },
    { 0x10, 0x01 },
    { 0x11, 0x01 },
    { 0x12, 0x00 },
    { 0x13, 0x53 },
    { 0x14, 0x8A },

    { 0x30, 0x39 },
    { 0x31, 0x55 },
    { 0x32, 0x0C },
    { 0x33, 0x74 },
    { 0x34, 0x09 },

    { 0x3D, 0xEC },
    //
);

// ******************************************************************
// * XUnmountAlternateTitleA
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XUnmountAlternateTitleA,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call [IoDeleteSymbolicLink]
    XREF_ENTRY(0x3D, XREF_KT_FUNC_IoDeleteSymbolicLink),

    // mov byte [g_XapiAltLett_MU],0x00
    XREF_ENTRY(0x4D, XREF_g_XapiAltLett_MU), // derived

    { 0x0A, 0x65 },
    { 0x16, 0xFF },
    { 0x23, 0x83 },
    { 0x2E, 0x45 },

    // call [IoDeleteSymbolicLink]
    OV_MATCH(0x3B, 0xFF, 0x15),

    { 0x46, 0x0B },
    { 0x52, 0x50 },

    // leave
    // ret 0x04
    OV_MATCH(0x59, 0xC9, 0xC2, 0x04)
    //
);

// ******************************************************************
// * XMountMUA
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XMountMUA,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x2E, XREF_g_XapiMountedMUs), // derived
    XREF_ENTRY(0xCE, XREF_XapiMapLetterToDirectory),

    { 0x1E, 0x0C },
    { 0x3E, 0x66 },
    { 0x61, 0x85 },
    { 0x7E, 0x8D },
    { 0xA2, 0x0F },
    { 0xBE, 0x50 },
    { 0xDE, 0x74 },
    //
);

// ******************************************************************
// * CloseHandle
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CloseHandle,
                         3911)
OOVPA_SIG_MATCH(

    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x0A, 0x85 },
    { 0x0B, 0xC0 },
    { 0x0E, 0x33 },
    { 0x12, 0x08 },
    { 0x19, 0x33 },
    { 0x1A, 0xC0 },
    //
);

// ******************************************************************
// * ExitThread
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(ExitThread,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call XapiCallThreadNotifyRoutines
    XREF_ENTRY(0x03, XREF_XapiCallThreadNotifyRoutines),

    // call [PsTerminateSystemThread]
    XREF_ENTRY(0x0D, XREF_KT_FUNC_PsTerminateSystemThread),

    // push 0x00
    OV_MATCH(0x00, 0x6A, 0x00),

    // call XapiCallThreadNotifyRoutines
    OV_MATCH(0x02, 0xE8),

    // push [esp+0x04]
    OV_MATCH(0x07, 0xFF, 0x74, 0x24, 0x04),

    // call [PsTerminateSystemThread]
    OV_MATCH(0x0B, 0xFF, 0x15),

    // Interrupt 3
    OV_MATCH(0x11, 0xCC),
    //
);

// ******************************************************************
// * XLaunchNewImageA
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XLaunchNewImageA,
                         3911)
OOVPA_SIG_MATCH(

    { 0x1E, 0x80 },
    { 0x3E, 0xC0 },
    { 0x5E, 0xFF },
    { 0x7E, 0xFC },
    { 0x9E, 0x08 },
    { 0xBE, 0x50 },
    { 0xDE, 0x05 },
    { 0xFE, 0x85 },
    //
);

// ******************************************************************
// * XGetLaunchInfo
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGetLaunchInfo,
                         3911)
OOVPA_SIG_MATCH(

    { 0x0B, 0x8B },
    { 0x18, 0x15 },
    { 0x25, 0x8B },
    { 0x32, 0x30 },
    { 0x3F, 0x00 },
    { 0x4C, 0x83 },
    { 0x59, 0x5E },
    //
);

// ******************************************************************
// * XGetSectionHandleA
//   558BEC83EC10538B1D........5657FF75088D45F050FFD38B351C0101008B3D
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGetSectionHandleA,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x10 },
    { 0x06, 0x53 },
    { 0x07, 0x8B },
    { 0x08, 0x1D },

    { 0x0D, 0x56 },
    { 0x0E, 0x57 },
    { 0x0F, 0xFF },
    //
);

// ******************************************************************
// * XLoadSectionByHandle
//  568B74240856FF15........85C07D0A50E8........33C0EB038B46045EC204
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XLoadSectionByHandle,
                         3911)
OOVPA_SIG_MATCH(

    // XLoadSectionByHandle+0x01 : mov esi, [esp+4+arg_0]
    { 0x01, 0x8B },
    { 0x02, 0x74 },
    { 0x03, 0x24 },
    { 0x04, 0x08 },

    // XLoadSectionByHandle+0x0C : test eax, eax
    { 0x0C, 0x85 },
    { 0x0D, 0xC0 },

    // XLoadSectionByHandle+0x1A : mov eax, [esi+4]
    { 0x1A, 0x8B },
    { 0x1B, 0x46 },
    { 0x1C, 0x04 },

    // XLoadSectionByHandle+0x1E : retn 4
    { 0x1E, 0xC2 },
    { 0x1F, 0x04 },
    //
);

// ******************************************************************
// * XFreeSectionByHandle
// FF742404FF15........85C07D0A50E8........33C0EB0333C040C20400....
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XFreeSectionByHandle,
                         3911)
OOVPA_SIG_MATCH(

    // XFreeSectionByHandle+0x00 : push esp
    { 0x00, 0xFF },
    { 0x01, 0x74 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // XFreeSectionByHandle+0x0A : test eax, eax
    { 0x0A, 0x85 },
    { 0x0B, 0xC0 },

    // XFreeSectionByHandle+0x18 : xor eax, eax
    { 0x18, 0x33 },
    { 0x19, 0xC0 },

    // XFreeSectionByHandle+0x1A : inc eax
    { 0x1A, 0x40 },

    // XFreeSectionByHandle+0x1B : retn 4
    { 0x1B, 0xC2 },
    { 0x1C, 0x04 },
    //
);

// ******************************************************************
// * XAutoPowerDownResetTimer
// ******************************************************************
// Assembly line at 0x00 and 0x09 are unique. It will prevent any false detection it might find in the future.
OOVPA_SIG_HEADER_NO_XREF(XAutoPowerDownResetTimer,
                         3911)
OOVPA_SIG_MATCH(

    //XAutoPowerDownResetTimer+0x00 : push 0FFFFFFCDh
    { 0x00, 0x6A },
    { 0x01, 0xCD },

    //XAutoPowerDownResetTimer+0x02 : pop ecx
    { 0x02, 0x59 },

    //XAutoPowerDownResetTimer+0x08 : push ecx
    { 0x08, 0x51 },

    //XAutoPowerDownResetTimer+0x09 : mov eax, 0B5659000h
    { 0x09, 0xB8 },
    { 0x0A, 0x00 },
    { 0x0B, 0x90 },
    { 0x0C, 0x65 },
    { 0x0D, 0xB5 },

    //XAutoPowerDownResetTimer+0x0E : push eax
    { 0x0E, 0x50 },

    { 0x14, 0xFF },

    //XAutoPowerDownResetTimer+0x1A : ret
    { 0x1A, 0xC3 },
    //
);

// ******************************************************************
// * XMountMURootA
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XMountMURootA,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x2D, XREF_g_XapiMountedMUs), // derived

    { 0x1E, 0x0C },
    { 0x3E, 0x00 },
    { 0x61, 0x8B },
    { 0x7E, 0x00 },
    { 0x9E, 0x00 },
    { 0xBE, 0xFF },
    { 0xDE, 0xFF },
    //
);

// ******************************************************************
// * XMountUtilityDrive
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XMountUtilityDrive,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x18, XREF_XapiSelectCachePartition),

    // push ebp
    // mov ebp, esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),
    // sub esp, 0x114
    OV_MATCH(0x03, 0x81, 0xEC, 0x14, 0x01),
    // push ebx
    // push esi
    // push edi
    OV_MATCH(0x09, 0x53, 0x56, 0x57),

    // push eax
    // push dword ptr [ebp+0x08]
    // call XapiSelectCachePartition
    OV_MATCH(0x13, 0x50, 0xFF, 0x75, 0x08, 0xE8),
    //
);

// ******************************************************************
// * ReadFileEx@20
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(ReadFileEx,
                         3911)
OOVPA_SIG_MATCH(

    { 0x09, 0x48 },
    { 0x14, 0x8D },
    { 0x1F, 0xFF },
    { 0x2A, 0xFF },
    { 0x2F, 0x00 },
    { 0x35, 0x00 },
    { 0x40, 0x50 },
    { 0x4B, 0xC0 },
    //
);

// ******************************************************************
// * WriteFileEx
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(WriteFileEx,
                         3911)
OOVPA_SIG_MATCH(

    { 0x09, 0x48 },
    { 0x14, 0x8D },
    { 0x1F, 0xFF },
    { 0x2A, 0xFF },
    { 0x2F, 0xFC },
    { 0x35, 0x00 },
    { 0x40, 0x50 },
    { 0x4B, 0xC0 },
    //
);

// ******************************************************************
// * XInputPoll
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputPoll,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x56 },
    { 0x02, 0x33 },
    { 0x03, 0xF6 },
    { 0x04, 0xFF },
    { 0x05, 0x15 },

    { 0x18, 0x04 },
    { 0x19, 0x02 },
    { 0x1A, 0x75 },
    { 0x1B, 0x29 },
    { 0x1C, 0xF6 },
    { 0x1D, 0x80 },
    { 0x1E, 0xA2 },
    { 0x1F, 0x00 },
    //
);

// ******************************************************************
// * timeSetEvent
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(timeSetEvent,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x14 },
    { 0x06, 0x53 },
    { 0x07, 0x68 },

    { 0x1B, 0xCB },
    { 0x1C, 0x75 },

    { 0x2A, 0x45 },
    { 0x55, 0x53 },
    //
);

// ******************************************************************
// * timeKillEvent
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(timeKillEvent,
                         3911)
OOVPA_SIG_MATCH(

    { 0x02, 0xBF },
    { 0x13, 0x0D },

    { 0x18, 0x0F },
    { 0x19, 0xB7 },
    { 0x1A, 0xC2 },
    { 0x1B, 0x48 },
    { 0x1C, 0x85 },
    { 0x1D, 0xC9 },
    { 0x1E, 0x74 },
    { 0x1F, 0x3E },

    { 0x4A, 0x6A },
    { 0x55, 0x15 },
    //
);

// ******************************************************************
// * GetOverlappedResult
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(GetOverlappedResult,
                         3911)
OOVPA_SIG_MATCH(

    { 0x0B, 0x75 },
    { 0x18, 0xC0 },
    { 0x27, 0xEB },
    { 0x32, 0x00 },
    { 0x3F, 0xEB },
    { 0x4C, 0x89 },
    { 0x59, 0x56 },
    //
);

// ******************************************************************
// * RaiseException
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(RaiseException,
                         3911)
OOVPA_SIG_MATCH(

    { 0x09, 0x83 },
    { 0x14, 0x8B },
    { 0x1F, 0xC7 },
    { 0x2A, 0x10 },
    { 0x35, 0x89 },
    { 0x40, 0x5F },
    { 0x4B, 0xFF },
    //
);

// ******************************************************************
// * SwitchToThread
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(SwitchToThread,
                         3911)
OOVPA_SIG_MATCH(

    // call [NtYieldExecution]
    OV_MATCH(0x00, 0xFF, 0x15),

    // xor ecx,ecx
    OV_MATCH(0x06, 0x33, 0xC9),

    // cmp eax,0x40000024
    OV_MATCH(0x08, 0x3D, 0x24, 0x00, 0x00, 0x40),

    // setne cl
    OV_MATCH(0x0D, 0x0F, 0x95, 0xC1),

    // ret
    OV_MATCH(0x12, 0xC3),
    //
);

// ******************************************************************
// * XapiThreadStartup
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiThreadStartup,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call XapiCallThreadNotifyRoutines
    XREF_ENTRY(0x68, XREF_XapiCallThreadNotifyRoutines),

    // call UnhandledExceptionFilter
    XREF_ENTRY(0x82, XREF_UnhandledExceptionFilter),

    // push 0x18
    OV_MATCH(0x00, 0x6A, 0x18),

    // push ...
    OV_MATCH(0x02, 0x68),

    // shr ecx, 0x02
    OV_MATCH(0x3C, 0xC1, 0xE9, 0x02),

    // and ecx, 0x03
    OV_MATCH(0x43, 0x83, 0xE1, 0x03),

    // ret
    OV_MATCH(0x86, 0xC3),

    // Interrupt 3
    OV_MATCH(0x97, 0xCC),
    //
);

// ******************************************************************
// * MoveFileA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(MoveFileA,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call XapiSetLastNTError
    XREF_ENTRY(0x8A, XREF_XapiSetLastNTError),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // push 0xFD
    OV_MATCH(0x17, 0x6A, 0xFD),

    // push 0x0A
    OV_MATCH(0x5F, 0x6A, 0x0A),

    // push 0x10
    OV_MATCH(0x61, 0x6A, 0x10),

    // ret 0x0008
    OV_MATCH(0x93, 0xC2, 0x08),
    //
);

// ******************************************************************
// * XapiFiberStartup
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(XapiFiberStartup,
                         3911)
OOVPA_SIG_MATCH(

    { 0x00, 0x6A },
    { 0x01, 0x08 },

    { 0x25, 0xFF },
    { 0x26, 0x30 },
    { 0x27, 0xFF },
    { 0x28, 0x55 },
    { 0x29, 0x08 },
    { 0x2A, 0xEB },
    { 0x2B, 0x0C },
    { 0x2C, 0xFF },
    { 0x2D, 0x75 },
    { 0x2E, 0xEC },
    { 0x2F, 0xE8 },

    { 0x44, 0xCC },
    //
);

// ******************************************************************
// * XUnmountMU
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XUnmountMU,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_g_XapiMountedMUs), // derived
    XREF_ENTRY(0x38, XREF_XUnmountAlternateTitleA),

    // push EBP
    // mov EBP, ESP
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // push 0x20
    // push 0x01
    // xor edi, edi
    OV_MATCH(0x5D, 0x6A, 0x20, 0x6A, 0x01, 0x33, 0xFF),

    //
);

// ******************************************************************
// * MU_Init
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(MU_Init,
                         3911)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    // sub esp, 0x10
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10),

    // push eax
    // push 0x00
    // push 0x3A
    // lea eax, [ebp-0x10]
    OV_MATCH(0x95, 0x50, 0x6A, 0x00, 0x6A, 0x3A, 0x8D, 0x45, 0xF0),

    //
);

// ******************************************************************
// * XapiMapLetterToDirectory
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiMapLetterToDirectory,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call XGetSectionSize
    XREF_ENTRY(0x243, XREF_XGetSectionSize), // derived

    // push ebp
    // mov ebp, esp
    // sub esp, 0x284
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x84, 0x02, 0x00),

    // push 0x03
    // push 0x03
    // mov edi, 0x80
    OV_MATCH(0x14, 0x6A, 0x03, 0x6A, 0x03, 0xBF, 0x80, 0x00 /*, 0x00, 0x00*/),

    // call XGetSectionSize
    OV_MATCH(0x242, 0xE8),

    //
);

// ******************************************************************
// * IUsbInit::GetMaxDeviceTypeCount
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(IUsbInit_GetMaxDeviceTypeCount,
                         3911)
OOVPA_SIG_MATCH(

    // mov edx, [ecx + 0x9C]
    OV_MATCH(0x00, 0x8B, 0x91, 0x9C, 0x00, 0x00 /*, 0x00*/),

    // mov ecx, [ecx + 0x98]
    OV_MATCH(0x0C, 0x8B, 0x89, 0x98, 0x00, 0x00 /*, 0x00*/),

    // ret 0x4
    OV_MATCH(0x2E, 0xC2, 0x04 /*, 0x00*/)

    //
);

// ******************************************************************
// * _cinit
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(_cinit,
                         3911)
OOVPA_SIG_MATCH(

    // mov eax,[...]
    OV_MATCH(0x00, 0xA1),

    // mov eax,...
    OV_MATCH(0x0D, 0xB8),
    // mov edi,...
    OV_MATCH(0x12, 0xBF),

    // cmp eax,0xFF
    OV_MATCH(0x23, 0x83, 0xF8, 0xFF),

    // cmp eax,0xFF
    OV_MATCH(0x47, 0x83, 0xF8, 0xFF),

    // call eax
    OV_MATCH(0x4C, 0xFF, 0xD0),

    // ret
    OV_MATCH(0x57, 0xC3),
    //
);

// ******************************************************************
// * _rtinit
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(_rtinit,
                         3911)
OOVPA_SIG_MATCH(

    // push esi; push edi
    OV_MATCH(0x00, 0x56, 0x57),

    // mov eax,...
    OV_MATCH(0x02, 0xB8),
    // mov edi,...
    OV_MATCH(0x07, 0xBF),

    // cmp eax,0xFF
    OV_MATCH(0x18, 0x83, 0xF8, 0xFF),

    // call eax
    OV_MATCH(0x1D, 0xFF, 0xD0),

    // ret
    OV_MATCH(0x28, 0xC3),
    //
);

// ******************************************************************
// * GetLastError
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(GetLastError,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // mov eax,[_tls_index]
    XREF_ENTRY(0x13, XREF__tls_index), // derived

    // mov ecx,fs:[_tls_array]
    XREF_ENTRY(0x1A, XREF__tls_array), // derived

    // mov eax,[eax+XapiLastErrorCode_OFFSET]
    XREF_ENTRY(0x23, XREF_XapiLastErrorCode_OFFSET), // derived

    // movzx eax,fs:[0x00000024]
    OV_MATCH(0x00, 0x64, 0x0F, 0xB6),

    // cmp al,0x02
    OV_MATCH(0x08, 0x3C, 0x02),

    // mov eax,[eax+XapiLastErrorCode_OFFSET]
    OV_MATCH(0x21, 0x8B, 0x80),

    // ret
    OV_MATCH(0x27, 0xC3),
    //
);

// ******************************************************************
// * SetLastError
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(SetLastError,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // mov ecx,fs:[_tls_array]
    XREF_ENTRY(0x15, XREF__tls_array), // derived

    // mov eax,[_tls_index]
    XREF_ENTRY(0x1A, XREF__tls_index), // derived

    // mov [eax+XapiLastErrorCode_OFFSET],ecx
    XREF_ENTRY(0x27, XREF_XapiLastErrorCode_OFFSET), // derived

    // movzx eax,fs:[0x00000024]
    OV_MATCH(0x00, 0x64, 0x0F, 0xB6),

    // cmp al,0x02
    OV_MATCH(0x08, 0x3C, 0x02),

    // mov [eax+XapiLastErrorCode_OFFSET],ecx
    OV_MATCH(0x25, 0x89, 0x88),

    // ret
    OV_MATCH(0x2B, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XapiSetLastNTError
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiSetLastNTError,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call SetLastError
    XREF_ENTRY(0x0E, XREF_SetLastError),

    // push [esp+0x04]
    OV_MATCH(0x00, 0xFF, 0x74, 0x24, 0x04),

    // mov edx,eax
    OV_MATCH(0x0A, 0x8B, 0xD0),

    // mov eax,edx
    OV_MATCH(0x12, 0x8B, 0xC2),

    // ret
    OV_MATCH(0x14, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XapiFormatObjectAttributes
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiFormatObjectAttributes,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call [RtlInitAnsiString]
    XREF_ENTRY(0x0C, XREF_KT_FUNC_RtlInitAnsiString),

    // push esi
    OV_MATCH(0x00, 0x56),

    // push esi
    OV_MATCH(0x09, 0x56),

    // call [RtlInitAnsiString]
    OV_MATCH(0x0A, 0xFF, 0x15),

    // mov [eax],0xFFFFFFFC
    OV_MATCH(0x17, 0xC7, 0x00, 0xFC, 0xFF, 0xFF),

    // ret 0x000C
    OV_MATCH(0x25, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * XapiCallThreadNotifyRoutines
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiCallThreadNotifyRoutines,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov edi,XapiThreadNotifyRoutineList
    XREF_ENTRY(0x16, XREF_XapiThreadNotifyRoutineList), // derived

    // push ebx; push esi; push edi
    OV_MATCH(0x00, 0x53, 0x56, 0x57),

    // mov ebx,XapiProcessLock
    OV_MATCH(0x03, 0xBB),

    // call [eax+0x08]
    OV_MATCH(0x024, 0xFF, 0x50, 0x08),

    // pop edi; pop esi; pop ebx
    OV_MATCH(0x32, 0x5F, 0x5E, 0x5B),

    // ret 0x0004
    OV_MATCH(0x35, 0xC2, 0x04),
    //
);

// ******************************************************************
// * UnhandledExceptionFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(UnhandledExceptionFilter,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov eax,[g_XapiCurrentTopLevelFilter]
    XREF_ENTRY(0x01, XREF_g_XapiCurrentTopLevelFilter), // derived

    // mov eax,[g_XapiCurrentTopLevelFilter]
    OV_MATCH(0x00, 0xA1),

    // push param_1
    OV_MATCH(0x09, 0xFF, 0x74, 0x24, 0x04),

    // call eax
    OV_MATCH(0x0D, 0xFF, 0xD0),

    // cmp eax,-1
    OV_MATCH(0x0F, 0x83, 0xF8, 0xFF),

    // or eax,eax
    OV_MATCH(0x14, 0x0B, 0xC0),

    // xor eax,eax
    OV_MATCH(0x18, 0x33, 0xC0),

    // ret 0x0004
    OV_MATCH(0x1A, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XapiSelectCachePartition
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XapiSelectCachePartition,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call [NtOpenFile]
    XREF_ENTRY(0x3F, XREF_KT_FUNC_NtOpenFile),

    // call [NtReadFile]
    XREF_ENTRY(0x74, XREF_KT_FUNC_NtReadFile),

    // push ebp
    // mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // push 0x10
    OV_MATCH(0x12, 0x6A, 0x10),

    // push 0x03
    OV_MATCH(0x17, 0x6A, 0x03),
    // lea eax, [ebp-0x20]
    OV_MATCH(0x19, 0x8D, 0x45, 0xE0),

    // lea eax, [ebp-0x2C]
    OV_MATCH(0x1D, 0x8D, 0x45, 0xD4),

    // call [NtOpenFile]
    OV_MATCH(0x3D, 0xFF, 0x15),

    // call [NtReadFile]
    OV_MATCH(0x72, 0xFF, 0x15),
    //
);

// ******************************************************************
// * mainXapiStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(mainXapiStartup,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call XapiInitProcess
    //XREF_ENTRY(0x01, XREF_XapiInitProcess),


    // call _rtinit
    XREF_ENTRY(0x48, XREF__rtinit),

    // call _cinit
    XREF_ENTRY(0x4D, XREF__cinit),

    // call XapiInitProcess
    OV_MATCH(0x00, 0xE8),
    // mov eax, fs:[0x20]
    OV_MATCH(0x05, 0x64, 0xA1, 0x20, 0x00),

    // call _rtinit
    OV_MATCH(0x47, 0xE8),
    // call _cinit
    OV_MATCH(0x4C, 0xE8),
    //
);

// ******************************************************************
// * mainCRTStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(mainCRTStartup,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // push mainXapiStartup
    XREF_ENTRY(0x34, XREF_mainXapiStartup),

    //  call CreateThread
    XREF_ENTRY(0x3D, XREF_CreateThread),

    //  call XapiBootToDash
    XREF_ENTRY(0x4D, XREF_XapiBootToDash),

    // mov eax, [...]
    OV_MATCH(0x00, 0xA1),
    // sub eax, [...]
    OV_MATCH(0x05, 0x2B, 0x05),

    // and eax, -16
    OV_MATCH(0x17, 0x83, 0xE0, 0xF0),
    // push -4
    OV_MATCH(0x1A, 0x6A, 0xFC),

    // push mainXapiStartup
    OV_MATCH(0x33, 0x68),

    // call CreateThread
    OV_MATCH(0x3C, 0xE8),

    // call XapiBootToDash
    OV_MATCH(0x4C, 0xE8),
    //
);

// ******************************************************************
// * XMUNameFromDriveLetter
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XMUNameFromDriveLetter,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // test [g_XapiMountedMUs], edx
    XREF_ENTRY(0x14, XREF_g_XapiMountedMUs),

    // call NtOpenFile
    XREF_ENTRY(0x6C, XREF_KT_FUNC_NtOpenFile),

    // call NtFsControlFile
    XREF_ENTRY(0xA0, XREF_KT_FUNC_NtFsControlFile),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp, 0x74
    OV_MATCH(0x03, 0x83, 0xEC, 0x74),

    // push 0x80100000 // GENERIC_READ | SYNCHRONIZE
    OV_MATCH(0x59, 0x68, 0x00, 0x00, 0x10, 0x80),

    // call NtOpenFile
    OV_MATCH(0x6A, 0xFF, 0x15),

    // call NtFsControlFile
    OV_MATCH(0x9E, 0xFF, 0x15),
    //
);

// ******************************************************************
// * XMUWriteNameToDriveLetter
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(XMUWriteNameToDriveLetter,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // test [g_XapiMountedMUs], edx
    XREF_ENTRY(0x14, XREF_g_XapiMountedMUs),

    // call NtOpenFile
    XREF_ENTRY(0x6C, XREF_KT_FUNC_NtOpenFile),

    // call NtFsControlFile
    XREF_ENTRY(0xAE, XREF_KT_FUNC_NtFsControlFile),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp, 0x74
    OV_MATCH(0x03, 0x83, 0xEC, 0x74),

    // push 0x40100000 // GENERIC_WRITE | SYNCHRONIZE
    OV_MATCH(0x59, 0x68, 0x00, 0x00, 0x10, 0x40),

    // call NtOpenFile
    OV_MATCH(0x6A, 0xFF, 0x15),

    // call NtFsControlFile
    OV_MATCH(0xAC, 0xFF, 0x15),
    //
);

// ******************************************************************
// * XMUPortFromDriveLetterA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(XMUPortFromDriveLetterA,
                         3911)
OOVPA_SIG_MATCH(

    // mov al, byte [esp + 4]
    OV_MATCH(0x00, 0x8A, 0x44, 0x24, 0x04),
    // cmp al, 0x46
    OV_MATCH(0x04, 0x3C, 0x46),

    // cdq
    OV_MATCH(0x12, 0x99),

    // sar eax, 1
    OV_MATCH(0x15, 0xD1, 0xF8),

    // ret
    OV_MATCH(0x1C, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XMUSlotFromDriveLetterA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_NO_XREF(XMUSlotFromDriveLetterA,
                         3911)
OOVPA_SIG_MATCH(

    // mov al, byte [esp + 4]
    OV_MATCH(0x00, 0x8A, 0x44, 0x24, 0x04),
    // cmp al, 0x46
    OV_MATCH(0x04, 0x3C, 0x46),

    // cdq
    OV_MATCH(0x12, 0x99),

    // idiv eax, ecx
    OV_MATCH(0x16, 0xF7, 0xF9),

    // ret
    OV_MATCH(0x1F, 0xC2, 0x04),
    //
);

// ******************************************************************
// * CreateEventA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(CreateEventA,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call [NtCreateEvent]
    XREF_ENTRY(0x33, XREF_KT_FUNC_NtCreateEvent),

    // call XapiSetLastNTError
    XREF_ENTRY(0x57, XREF_XapiSetLastNTError),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp, 0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // call [NtCreateEvent]
    OV_MATCH(0x31, 0xFF, 0x15),

    // push 0xB7
    OV_MATCH(0x42, 0x68, 0xB7, 0x00, 0x00),

    // call XapiSetLastNTError
    OV_MATCH(0x56, 0xE8),

    // ret
    OV_MATCH(0x5E, 0xC2, 0x10),
    //
);

// ******************************************************************
// * SetEvent
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(SetEvent,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call [NtSetEvent]
    XREF_ENTRY(0x08, XREF_KT_FUNC_NtSetEvent),

    // call XapiSetLastNTError
    XREF_ENTRY(0x17, XREF_XapiSetLastNTError),

    // push 0
    OV_MATCH(0x00, 0x6A, 0x00),
    // push [ESP + param_1]
    OV_MATCH(0x02, 0xFF, 0x74, 0x24, 0x08),
    // call [NtSetEvent]
    OV_MATCH(0x06, 0xFF, 0x15),

    // call XapiSetLastNTError
    OV_MATCH(0x16, 0xE8),

    // ret
    OV_MATCH(0x1D, 0xC2, 0x04),
    //
);

// ******************************************************************
// * ResetEvent
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(ResetEvent,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call [NtClearEvent]
    XREF_ENTRY(0x06, XREF_KT_FUNC_NtClearEvent),

    // call XapiSetLastNTError
    XREF_ENTRY(0x15, XREF_XapiSetLastNTError),

    // push [ESP + param_1]
    OV_MATCH(0x00, 0xFF, 0x74, 0x24, 0x04),
    // call [NtClearEvent]
    OV_MATCH(0x04, 0xFF, 0x15),

    // call XapiSetLastNTError
    OV_MATCH(0x14, 0xE8),

    // ret
    OV_MATCH(0x1B, 0xC2, 0x04),
    //
);

// ******************************************************************
// * PulseEvent
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(PulseEvent,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // call [NtPulseEvent]
    XREF_ENTRY(0x08, XREF_KT_FUNC_NtPulseEvent),

    // call XapiSetLastNTError
    XREF_ENTRY(0x17, XREF_XapiSetLastNTError),

    // push 0
    OV_MATCH(0x00, 0x6A, 0x00),
    // push [ESP + param_1]
    OV_MATCH(0x02, 0xFF, 0x74, 0x24, 0x08),
    // call [NtPulseEvent]
    OV_MATCH(0x06, 0xFF, 0x15),

    // call XapiSetLastNTError
    OV_MATCH(0x16, 0xE8),

    // ret
    OV_MATCH(0x1D, 0xC2, 0x04),
    //
);

// ******************************************************************
// * OpenEventA
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(OpenEventA,
                      3911,
                      XRefThree)
OOVPA_SIG_MATCH(

    // push [ExEventObjectType]
    XREF_ENTRY(0x32, XREF_KT_VAR__ExEventObjectType),

    // call [ObOpenObjectByName]
    XREF_ENTRY(0x43, XREF_KT_FUNC_ObOpenObjectByName),

    // call XapiSetLastNTError
    XREF_ENTRY(0x4D, XREF_XapiSetLastNTError),

    // push ebp
    OV_MATCH(0x00, 0x55),

    // sub esp, 0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // push 0xC000000D
    OV_MATCH(0x0C, 0x68, 0x0D, 0x00, 0x00, 0xC0),

    // push [ExEventObjectType]
    OV_MATCH(0x30, 0xFF, 0x35),

    // call [ObOpenObjectByName]
    OV_MATCH(0x41, 0xFF, 0x15),

    // call XapiSetLastNTError
    OV_MATCH(0x4C, 0xE8),

    // ret
    OV_MATCH(0x59, 0xC2, 0x0C),
    //
);
