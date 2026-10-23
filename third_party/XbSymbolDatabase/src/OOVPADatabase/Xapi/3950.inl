// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XapiInitProcess
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiInitProcess,
                         3950)
OOVPA_SIG_MATCH(

    // XapiInitProcess+0x03 : sub esp, 30h
    { 0x05, 0x30 },

    // XapiInitProcess+0x0F : push 0x0C
    { 0x10, 0x6A },
    { 0x11, 0x0C },

    // XapiInitProcess+0x17 : repe stosd
    { 0x18, 0xF3 },
    { 0x19, 0xAB },

    // XapiInitProcess+0x42 : jnz +0x0A
    { 0x43, 0x75 },
    { 0x44, 0x0A },
    //
);
