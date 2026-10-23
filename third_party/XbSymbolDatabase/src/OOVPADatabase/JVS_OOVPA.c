// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library
//   [LibV] Title Name                       |  Verify   |  Comments
//-------------------------------------------------------------------
// * [4831] House of The Dead 3              |   100%    | Contain full library.
// * [4831] Crazy Taxi 3                     |   100%    | Contain full library.
// * [5028] SegaBoot v2.00.0                 |   100%    | Contain full library.
// * [5028] SegaBoot v2.13.0                 |   100%    | Contain full library.
// * [5028] Virtua Cop 3                     |   100%    | Contain full library.
// * [5455] Ollie King                       |   100%    | Contain full library.
// * [5558] Outrun 2                         |   100%    | Contain full library.
// * [5659] Outrun 2 SP                      |   100%    | Contain full library.
// * [5788] Ghost Squad                      |   100%    | Contain full library.
// * [5849] Sega Golf 2006                   |   100%    | Contain full library.

// NOTES:
//  * JVSSendCommand1/2/3 sometime changes even when the library version
//    is the same except the functions are quite different in layout, etc
//    and some offsets are different within them too.

#include "OOVPA_databases.h"

#include "JVS/4831.inl"

// ******************************************************************
// * JVSLIB_OOVPA_Table
// ******************************************************************
static OOVPATable JVSLIB_OOVPA_Table[] = {

    // Variables
    REGISTER_OOVPAS_M(SYM_VAR(JVS_g_pPINSA),
                      SYM_SIG(4831)),
    REGISTER_OOVPAS_M(SYM_VAR(JVS_g_pPINSB),
                      SYM_SIG(4831)),
    // Chihiro/JVS (XRef strings)
    REGISTER_OOVPAS(SYM_VAR(JVS_SendCommand_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsBACKUP_Read_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsBACKUP_Write_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsEEPROM_Read_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsEEPROM_Write_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsFirmwareDownload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsFirmwareUpload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsNodeReceivePacket_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsNodeSendPacket_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsRTC_Read_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsRTC_Write_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScFirmwareDownload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScFirmwareUpload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScReceiveMidi_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScReceiveRs323c_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScSendMidi_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScSendRs323c_String),
                    SYM_SIG(4831)),

    // Chihiro/JVS (Functions)
    REGISTER_OOVPAS(SYM_FUN(JVS_SendCommand, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, Command), PARAM(psh, unknown3), PARAM(psh, Length), PARAM(psh, unknown5), PARAM(psh, unknown6), PARAM(psh, unknown7), PARAM(psh, unknown8))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JVS_SendCommand, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, Command), PARAM(psh, unknown3), PARAM(psh, Length), PARAM(psh, unknown5), PARAM(psh, unknown6), PARAM(psh, unknown7), PARAM(psh, unknown8))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JVS_SendCommand, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, Command), PARAM(psh, unknown3), PARAM(psh, Length), PARAM(psh, unknown5), PARAM(psh, unknown6), PARAM(psh, unknown7), PARAM(psh, unknown8))),
                    SYM_SIG(4831, 4832)),
    REGISTER_OOVPAS(SYM_FUN(JvsBACKUP_Read, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsBACKUP_Read, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsBACKUP_Read, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsBACKUP_Write, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsBACKUP_Write, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsEEPROM_Read, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Read, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Read, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsEEPROM_Write, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Write, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Write, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsFirmwareDownload, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareDownload, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareDownload, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareDownload, SUFFIX(4), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsFirmwareUpload, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareUpload, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareUpload, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareUpload, SUFFIX(4), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsNodeReceivePacket, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsNodeReceivePacket, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsNodeSendPacket, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsNodeSendPacket, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsRTC_Read, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, time), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsRTC_Read, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, time), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsRTC_Read, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, time), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsRTC_Write, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, time), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsRTC_Write, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, time), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScFirmwareDownload, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareDownload, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareDownload, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareDownload, SUFFIX(4), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScFirmwareUpload, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareUpload, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareUpload, SUFFIX(3), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Offset), PARAM(psh, Length), PARAM(psh, Buffer), PARAM(psh, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScReceiveMidi, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScReceiveMidi, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScReceiveRs323c, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScReceiveRs323c, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScSendMidi, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScSendMidi, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, unknown1), PARAM(psh, unknown2), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScSendRs323c, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScSendRs323c, SUFFIX(2), CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Buffer), PARAM(psh, Length), PARAM(psh, unknown3))),
                    SYM_SIG(4831)),
};

// ******************************************************************
// * JVSLIB_OOVPA
// ******************************************************************
OOVPATableList JVSLIB_OOVPA = { XBSDB_ARRAY_SIZE(JVSLIB_OOVPA_Table), JVSLIB_OOVPA_Table };
