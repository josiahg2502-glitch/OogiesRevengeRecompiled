// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * JVS_g_pPINSA
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(JVS_g_pPINSA,
                         4831)
OOVPA_SIG_MATCH_DUMMY();

// ******************************************************************
// * JVS_g_pPINSB
// ******************************************************************
// dummy signature
OOVPA_SIG_HEADER_NO_XREF(JVS_g_pPINSB,
                         4831)
OOVPA_SIG_MATCH_DUMMY();

OOVPA_SIG_HEADER_NO_XREF(JVS_SendCommand_String,
                         4831)
OOVPA_SIG_MATCH(
    // JVS_STATUS_ERROR_DEVICE_NOT_CONNECTED2 from JVS_SendCommand
    OV_MATCH(0x00, 'J', 'V', 'S'),
    OV_MATCH(0x04, 'S'),
    OV_MATCH(0x0B, 'E'),
    OV_MATCH(0x11, 'D'),
    OV_MATCH(0x18, 'N'),
    OV_MATCH(0x1C, 'C'),
    OV_MATCH(0x25, '2'),
    OV_MATCH(0x27, 'f'),
    OV_MATCH(0x2C, 'J'),
    OV_MATCH(0x30, 'S'),
    OV_MATCH(0x34, 'C'),
    //
);


OOVPA_SIG_HEADER_NO_XREF(JvsBACKUP_Read_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error <JvsBACKUP_Read>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'B'),
    OV_MATCH(0x18, 'R'),
    OV_MATCH(0x1B, 'd'),
    OV_MATCH(0x1C, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsBACKUP_Write_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error <JvsBACKUP_Write>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'B'),
    OV_MATCH(0x18, 'W'),
    OV_MATCH(0x1C, 'e'),
    OV_MATCH(0x1D, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsEEPROM_Read_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error <JvsEEPROM_Read>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'E'),
    OV_MATCH(0x18, 'R'),
    OV_MATCH(0x1B, 'd'),
    OV_MATCH(0x1C, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsEEPROM_Write_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error <JvsEEPROM_Write>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'E'),
    OV_MATCH(0x18, 'W'),
    OV_MATCH(0x1C, 'e'),
    OV_MATCH(0x1D, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsFirmwareDownload_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error1 <JvsFirmwareDownload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0C, '1'),
    OV_MATCH(0x0E, '<', 'J'),
    OV_MATCH(0x12, 'F'),
    OV_MATCH(0x1A, 'D'),
    OV_MATCH(0x21, 'd'),
    OV_MATCH(0x22, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsNodeReceivePacket_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status waiting <JvsNodeReceivePacket>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'N'),
    OV_MATCH(0x17, 'R'),
    OV_MATCH(0x1E, 'P'),
    OV_MATCH(0x24, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsRTC_Read_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status wait <JvsRTC_Read>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0C, '<', 'J'),
    OV_MATCH(0x10, 'R'),
    OV_MATCH(0x14, 'R'),
    OV_MATCH(0x18, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsRTC_Write_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status wait <JvsRTC_Write>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0C, '<', 'J'),
    OV_MATCH(0x10, 'R'),
    OV_MATCH(0x14, 'W'),
    OV_MATCH(0x19, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsNodeSendPacket_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status waiting <JvsNodeSendPacket>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'N'),
    OV_MATCH(0x17, 'S'),
    OV_MATCH(0x1B, 'P'),
    OV_MATCH(0x21, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsFirmwareUpload_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error1 <JvsFirmwareUpload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0C, '1'),
    OV_MATCH(0x0E, '<', 'J'),
    OV_MATCH(0x12, 'F'),
    OV_MATCH(0x1A, 'U'),
    OV_MATCH(0x1F, 'd'),
    OV_MATCH(0x20, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsScFirmwareDownload_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error1 <JvsScFirmwareDownload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0C, '1'),
    OV_MATCH(0x0E, '<', 'J'),
    OV_MATCH(0x12, 'S'),
    OV_MATCH(0x14, 'F'),
    OV_MATCH(0x1C, 'D'),
    OV_MATCH(0x23, 'd'),
    OV_MATCH(0x24, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsScFirmwareUpload_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status waiting <JvsScFirmwareUpload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x15, 'F'),
    OV_MATCH(0x1D, 'U'),
    OV_MATCH(0x22, 'd'),
    OV_MATCH(0x23, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsScReceiveMidi_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status waiting <JvsScReceiveMidi>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x15, 'R'),
    OV_MATCH(0x1C, 'M'),
    OV_MATCH(0x20, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsScReceiveRs323c_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error <JvsScReceiveRs323c>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'S'),
    OV_MATCH(0x13, 'R'),
    OV_MATCH(0x1A, 'R'),
    OV_MATCH(0x20, '>'),
    //
);

OOVPA_SIG_HEADER_NO_XREF(JvsScSendMidi_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status waiting <JvsScSendMidi>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x15, 'S'),
    OV_MATCH(0x19, 'M'),
    OV_MATCH(0x1D, '>'),
    //
);


OOVPA_SIG_HEADER_NO_XREF(JvsScSendRs323c_String,
                         4831)
OOVPA_SIG_MATCH(
    // Status error <JvsScSendRs323c>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'S'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x17, 'R'),
    OV_MATCH(0x1D, '>'),
    //
);

// ******************************************************************
// * JVS_SendCommand
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JVS_SendCommand,
                      4831,
                      XRefThree)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x250, XREF_JVS_SendCommand_String),
    XREF_ENTRY(0x2A0, XREF_JVS_g_pPINSA), // Derived
    XREF_ENTRY(0x2A8, XREF_JVS_g_pPINSB), // Derived

    // sub esp,0x?
    OV_MATCH(0x00, 0x81, 0xEC),

    // mov e??, [e?? + param_4]
    OV_MATCH(0x0A, 0xB4, 0x00),

    // test ebp,ebp
    OV_MATCH(0x0E, 0x85, 0xED),
    // push esi
    // push edi
    OV_MATCH(0x10, 0x56, 0x57),

    // mov esi,[e?? + 0x?]
    OV_MATCH(0x31, 0x8B, 0xB4),

    // jz +?
    OV_MATCH(0x90, 0x0F),

    // test al,0x??
    OV_MATCH(0x96, 0xA8),

    // and eax,0x3
    OV_MATCH(0x2A4, 0x83, 0xE0, 0x03),
    //
);

// ******************************************************************
// * JVS_SendCommand2
// * Variation of JVS_SendCommand
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JVS_SendCommand2,
                      4831,
                      XRefThree)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x2C0, XREF_JVS_SendCommand_String),
    XREF_ENTRY(0x312, XREF_JVS_g_pPINSA), // Derived
    XREF_ENTRY(0x31B, XREF_JVS_g_pPINSB), // Derived

    // sub esp,0x58
    // push ebx
    OV_MATCH(0x00, 0x83, 0xEC, 0x58, 0x53),

    // mov [esp + 0x70],al
    OV_MATCH(0x86, 0x88, 0x44, 0x24, 0x70),

    // and edx,0x3
    OV_MATCH(0x316, 0x83, 0xE2, 0x03),
    //
);

// ******************************************************************
// * JVS_SendCommand3
// * Variation of JVS_SendCommand
// ******************************************************************
// TODO: Set this signature as revision 1
OOVPA_SIG_HEADER_XREF(JVS_SendCommand3,
                      4831,
                      XRefThree)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x28B, XREF_JVS_SendCommand_String),
    XREF_ENTRY(0x302, XREF_JVS_g_pPINSA), // Derived
    XREF_ENTRY(0x30B, XREF_JVS_g_pPINSB), // Derived

    // sub esp,0x58
    // push ebx
    OV_MATCH(0x00, 0x83, 0xEC, 0x58, 0x53),

    // mov [esp + 0x70],al
    OV_MATCH(0x86, 0x88, 0x44, 0x24, 0x70),

    // and edx,0x3
    OV_MATCH(0x306, 0x83, 0xE2, 0x03),
    //
);

// ******************************************************************
// * JVS_SendCommand3
// * Variation of JVS_SendCommand
// ******************************************************************
// TODO: Set this signature as revision 2
OOVPA_SIG_HEADER_XREF(JVS_SendCommand3,
                      4832,
                      XRefThree)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x28B, XREF_JVS_SendCommand_String),
    XREF_ENTRY(0x307, XREF_JVS_g_pPINSA), // Derived
    XREF_ENTRY(0x313, XREF_JVS_g_pPINSB), // Derived

    // sub esp,0x58
    // push ebx
    OV_MATCH(0x00, 0x83, 0xEC, 0x58, 0x53),

    // mov [esp + 0x70],al
    OV_MATCH(0x86, 0x88, 0x44, 0x24, 0x70),

    // and edx,0x3
    OV_MATCH(0x30B, 0x83, 0xE2, 0x03),
    //
);

// ******************************************************************
// * JvsBACKUP_Read
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsBACKUP_Read,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x6E, XREF_JvsBACKUP_Read_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x11, 0x8D, 0x54, 0x24),

    OV_MATCH(0x17, 0x18),

    OV_MATCH(0x43, 0xBE, 0x00),

    OV_MATCH(0x4C, 0x05, 0x00),
    //
);

// ******************************************************************
// * JvsBACKUP_Read2
// * Seems to be specfic to Crazy Taxi: Same function as above
// * Very different code structure, needs different signature
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsBACKUP_Read2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x6F, XREF_JvsBACKUP_Read_String),

    OV_MATCH(0x00, 0x53),

    OV_MATCH(0x10, 0x6A),

    OV_MATCH(0x12, 0x0F, 0x83),

    OV_MATCH(0x18, 0x8B),

    OV_MATCH(0x43, 0x55, 0x52),

    OV_MATCH(0x4C, 0x8D, 0x87),
    //
);

// ******************************************************************
// * JvsBACKUP_Read3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsBACKUP_Read3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x5E, XREF_JvsBACKUP_Read_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x43, 0xBE, 0x00),

    OV_MATCH(0x4C, 0x05, 0x00),
    //
);

// ******************************************************************
// * JvsBACKUP_Write
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsBACKUP_Write,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x6E, XREF_JvsBACKUP_Write_String),

    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    OV_MATCH(0x0A, 0x55, 0x56),

    OV_MATCH(0x0E, 0x00, 0x6A),

    OV_MATCH(0x11, 0x8D, 0x54),

    OV_MATCH(0x17, 0x1F),

    OV_MATCH(0x31, 0x51, 0x6A),

    OV_MATCH(0x90, 0x0C, 0x2E),
    //
);

// ******************************************************************
// * JvsBACKUP_Write2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsBACKUP_Write2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x5E, XREF_JvsBACKUP_Write_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x43, 0xBE, 0x00),

    OV_MATCH(0x4C, 0x05, 0x00),
    //
);


// ******************************************************************
// * JvsEEPROM_Read
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsEEPROM_Read,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x188, XREF_JvsEEPROM_Read_String),

    OV_MATCH(0x00, 0x51),

    OV_MATCH(0x13, 0x40),

    OV_MATCH(0x21, 0x74, 0x24, 0x18),

    OV_MATCH(0x43, 0x6A, 0x17),

    OV_MATCH(0x4C, 0x6A, 0x40),
    //
);

// ******************************************************************
// * JvsEEPROM_Read2
// * Almost identical to JvsEEPROM_Read, but some bytes are shifted
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsEEPROM_Read2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1B0, XREF_JvsEEPROM_Read_String),

    OV_MATCH(0x00, 0x51),

    OV_MATCH(0x12, 0x40),

    OV_MATCH(0x21, 0x74, 0x24, 0x18),

    OV_MATCH(0x43, 0x6A, 0x17),

    OV_MATCH(0x4C, 0x6A, 0x40),
    //
);

// ******************************************************************
// * JvsEEPROM_Read3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsEEPROM_Read3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x199, XREF_JvsEEPROM_Read_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x14, 0x40),

    OV_MATCH(0x46, 0x6A),

    OV_MATCH(0x48, 0x6A),

    OV_MATCH(0x4A, 0x8D),
    //
);


// ******************************************************************
// * JvsEEPROM_Write
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsEEPROM_Write,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x18E, XREF_JvsEEPROM_Write_String),

    OV_MATCH(0x13, 0x08),

    OV_MATCH(0x3E, 0x8D, 0x44, 0x24),

    OV_MATCH(0x42, 0x50, 0x6A),

    OV_MATCH(0x6B, 0xE1, 0xFF),

    OV_MATCH(0x70, 0x81, 0xFA),
    //
);

// ******************************************************************
// * JvsEEPROM_Write2
// * Almost identical to JvsEEPROM_Write2, but some bytes are shifted
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsEEPROM_Write2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1B6, XREF_JvsEEPROM_Write_String),
    OV_MATCH(0x12, 0x08),

    OV_MATCH(0x3E, 0x8D, 0x44, 0x24),

    OV_MATCH(0x42, 0x50, 0x6A),

    OV_MATCH(0x6B, 0xE1, 0xFF),

    OV_MATCH(0x70, 0x81, 0xFA),
    //
);

// ******************************************************************
// * JvsEEPROM_Write3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsEEPROM_Write3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x199, XREF_JvsEEPROM_Write_String),

    OV_MATCH(0x00, 0x83, 0xEC),

    OV_MATCH(0x34, 0x8B),
    //
);

// ******************************************************************
// * JvsFirmwareDownload
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareDownload,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1D4, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
    //
);

// ******************************************************************
// * JvsFirmwareDownload2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareDownload2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x203, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
    //
);

// ******************************************************************
// * JvsFirmwareDownload3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareDownload3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1E3, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
    //
);


// ******************************************************************
// * JvsFirmwareDownload4
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareDownload4,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1CF, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
    //
);

// ******************************************************************
// * JvsFirmwareUpload
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareUpload,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1B7, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x12, 0x83, 0xF9, 0x20),

    OV_MATCH(0x40, 0x8D, 0x44, 0x24, 0x4C),
    //
);

// ******************************************************************
// * JvsFirmwareUpload2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareUpload2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1DE, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x12, 0x83, 0xF9, 0x20),

    OV_MATCH(0x40, 0x8D, 0x44, 0x24, 0x4C),
    //
);


// ******************************************************************
// * JvsFirmwareUpload3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareUpload3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1DA, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
    //
);


// ******************************************************************
// * JvsFirmwareUpload4
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsFirmwareUpload4,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1BF, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
    //
);

// ******************************************************************
// * JvsNodeReceivePacket
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsNodeReceivePacket,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x6D, XREF_JvsNodeReceivePacket_String),

    OV_MATCH(0x28, 0x6A, 0x19),

    OV_MATCH(0x2B, 0x6A, 0x03),

    OV_MATCH(0x54, 0xF6),

    OV_MATCH(0x55, 0xC3, 0x01),

    OV_MATCH(0xC9, 0xC2),
    //
);

// ******************************************************************
// * JvsNodeReceivePacket2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsNodeReceivePacket2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x55, XREF_JvsNodeReceivePacket_String),

    OV_MATCH(0x00, 0x53, 0x55, 0x56, 0x57),
    //
);

// ******************************************************************
// * JvsNodeSendPacket
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsNodeSendPacket,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x6D, XREF_JvsNodeSendPacket_String),

    OV_MATCH(0x23, 0x6A, 0x20),

    OV_MATCH(0x26, 0x6A, 0x0B),

    OV_MATCH(0x54, 0xF6, 0xC3, 0x01),

    OV_MATCH(0xC9, 0xC2),
    //
);

// ******************************************************************
// * JvsNodeSendPacket2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsNodeSendPacket2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x55, XREF_JvsNodeSendPacket_String),

    OV_MATCH(0x00, 0x53, 0x55, 0x56, 0x57),
    //
);

// ******************************************************************
// * JvsRTC_Read
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsRTC_Read,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x81, XREF_JvsRTC_Read_String),

    OV_MATCH(0x05, 0x00, 0x53),

    OV_MATCH(0x10, 0x1C, 0x8B, 0x6C, 0x24),

    OV_MATCH(0x2B, 0x55, 0xE8),
    //
);

// ******************************************************************
// * JvsRTC_Read2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsRTC_Read2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x96, XREF_JvsRTC_Read_String),

    OV_MATCH(0x05, 0x00, 0x53),

    OV_MATCH(0x10, 0x1C, 0x8B, 0x6C, 0x24),

    OV_MATCH(0x2B, 0x55, 0xE8),
    //
);

// ******************************************************************
// * JvsRTC_Read3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsRTC_Read3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x68, XREF_JvsRTC_Read_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x10, 0x8B),

    OV_MATCH(0x14, 0x56, 0x57),
    //
);

// ******************************************************************
// * JvsScFirmwareDownload
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareDownload,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1D4, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
    //
);

// ******************************************************************
// * JvsRTC_Write
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsRTC_Write,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x96, XREF_JvsRTC_Write_String),

    OV_MATCH(0x05, 0x00, 0x53),

    OV_MATCH(0x10, 0x1C, 0x8B, 0x6C, 0x24),

    OV_MATCH(0x2B, 0x55, 0xE8),
    //
);

// ******************************************************************
// * JvsRTC_Write2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsRTC_Write2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x68, XREF_JvsRTC_Write_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x10, 0x8B),

    OV_MATCH(0x14, 0x56, 0x57),
    //
);

// ******************************************************************
// * JvsScFirmwareDownload2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareDownload2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x203, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
    //
);

// ******************************************************************
// * JvsScFirmwareDownload3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareDownload3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1E3, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
    //
);

// ******************************************************************
// * JvsScFirmwareDownload4
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareDownload4,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x1CF, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
    //
);

// ******************************************************************
// * JvsScFirmwareUpload
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareUpload,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0xA9, XREF_JvsScFirmwareUpload_String),

    OV_MATCH(0x00, 0x51, 0x8B),
    OV_MATCH(0x05, 0x53, 0x8B),
    //
);

// ******************************************************************
// * JvsScFirmwareUpload2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareUpload2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0xBE, XREF_JvsScFirmwareUpload_String),

    OV_MATCH(0x00, 0x51, 0x8B),

    OV_MATCH(0x05, 0x53, 0x8B),
    //
);

// ******************************************************************
// * JvsScFirmwareUpload3
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScFirmwareUpload3,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x9E, XREF_JvsScFirmwareUpload_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x03, 0x8B),

    OV_MATCH(0x07, 0x53, 0x55),
    //
);

// ******************************************************************
// * JvsScReceiveMidi
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScReceiveMidi,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x7D, XREF_JvsScReceiveMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
    //
);

// ******************************************************************
// * JvsScReceiveMidi2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScReceiveMidi2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x65, XREF_JvsScReceiveMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
    //
);

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScReceiveRs323c,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x63, XREF_JvsScReceiveRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x56),
    //
);

// ******************************************************************
// * JvsScReceiveRs323c2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScReceiveRs323c2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x4F, XREF_JvsScReceiveRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x56),
    //
);

// ******************************************************************
// * JvsScSendMidi
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScSendMidi,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x7D, XREF_JvsScSendMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
    //
);

// ******************************************************************
// * JvsScSendMidi2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScSendMidi2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x5D, XREF_JvsScSendMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
    //
);

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScSendRs323c,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x5E, XREF_JvsScSendRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0xC7),
    //
);

// ******************************************************************
// * JvsScReceiveRs323c2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(JvsScSendRs323c2,
                      4831,
                      XRefOne)
OOVPA_SIG_MATCH(
    XREF_ENTRY(0x4D, XREF_JvsScSendRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x56),
    //
);
