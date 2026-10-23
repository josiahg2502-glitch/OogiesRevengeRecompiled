// SPDX-License-Identifier: ODbL-1.0

#include "unittest.hpp"

static const library_list database_opt = {
    REGISTER_SYMBOL_INLINE(JvsRTC_Write_String, VER_RANGE(4831)),
    REGISTER_SYMBOLS(JvsRTC_Write,
                     REGISTER_SYMBOL(JvsRTC_Write, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsRTC_Write2, VER_RANGE(4831))),
};

static const library_list database_min = {
    REGISTER_SYMBOL_INLINE(JVS_SendCommand_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsBACKUP_Read_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsBACKUP_Write_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsEEPROM_Read_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsEEPROM_Write_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsFirmwareDownload_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsFirmwareUpload_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsNodeReceivePacket_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsNodeSendPacket_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsRTC_Read_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsScFirmwareDownload_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsScFirmwareUpload_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsScReceiveMidi_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsScReceiveRs323c_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsScSendMidi_String, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JvsScSendRs323c_String, VER_RANGE(4831)),
};

static const library_list database_full = {
    // vars
    REGISTER_SYMBOL_INLINE(JVS_g_pPINSA, VER_RANGE(4831)),
    REGISTER_SYMBOL_INLINE(JVS_g_pPINSB, VER_RANGE(4831)),

    // functions
    REGISTER_SYMBOLS(JVS_SendCommand,
                     REGISTER_SYMBOL(JVS_SendCommand, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JVS_SendCommand2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JVS_SendCommand3, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsBACKUP_Read,
                     REGISTER_SYMBOL(JvsBACKUP_Read, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsBACKUP_Read2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsBACKUP_Read3, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsBACKUP_Write,
                     REGISTER_SYMBOL(JvsBACKUP_Write, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsBACKUP_Write2, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsEEPROM_Read,
                     REGISTER_SYMBOL(JvsEEPROM_Read, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsEEPROM_Read2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsEEPROM_Read3, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsEEPROM_Write,
                     REGISTER_SYMBOL(JvsEEPROM_Write, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsEEPROM_Write2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsEEPROM_Write3, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsFirmwareDownload,
                     REGISTER_SYMBOL(JvsFirmwareDownload, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsFirmwareDownload2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsFirmwareDownload3, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsFirmwareDownload4, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsFirmwareUpload,
                     REGISTER_SYMBOL(JvsFirmwareUpload, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsFirmwareUpload2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsFirmwareUpload3, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsFirmwareUpload4, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsNodeReceivePacket,
                     REGISTER_SYMBOL(JvsNodeReceivePacket, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsNodeReceivePacket2, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsNodeSendPacket,
                     REGISTER_SYMBOL(JvsNodeSendPacket, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsNodeSendPacket2, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsRTC_Read,
                     REGISTER_SYMBOL(JvsRTC_Read, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsRTC_Read2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsRTC_Read3, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsScFirmwareDownload,
                     REGISTER_SYMBOL(JvsScFirmwareDownload, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScFirmwareDownload2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScFirmwareDownload3, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScFirmwareDownload4, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsScFirmwareUpload,
                     REGISTER_SYMBOL(JvsScFirmwareUpload, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScFirmwareUpload2, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScFirmwareUpload3, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsScReceiveMidi,
                     REGISTER_SYMBOL(JvsScReceiveMidi, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScReceiveMidi2, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsScReceiveRs323c,
                     REGISTER_SYMBOL(JvsScReceiveRs323c, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScReceiveRs323c2, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsScSendMidi,
                     REGISTER_SYMBOL(JvsScSendMidi, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScSendMidi2, VER_RANGE(4831))),
    REGISTER_SYMBOLS(JvsScSendRs323c,
                     REGISTER_SYMBOL(JvsScSendRs323c, VER_RANGE(4831)),
                     REGISTER_SYMBOL(JvsScSendRs323c2, VER_RANGE(4831))),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/jvs.def>
#undef XREF_SYMBOL
    LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(JVS_SendCommand_String)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

static const subcategory_db jvs_db = {
    .name = "general",
    .optional = &database_opt,
    .min = &database_min,
    .full = &database_full,
};

void getLibraryJVS(library_db& lib_db)
{
    lib_db.subcategories = { &jvs_db };
    lib_db.xref_offset = XREF_OFFSET;
    lib_db.xref_total = LOCAL_COUNT;
    lib_db.xref_exclude = 0;
}
