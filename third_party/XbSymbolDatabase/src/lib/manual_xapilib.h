// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

#pragma once

static bool internal_xapi_find_XGetSectionSize(XbSDBiContext* pContext,
                                               const XbSDBiLibrarySession* pLibrarySession,
                                               SymbolDatabaseList* pLibraryDB,
                                               const XbSDBSection* pSection,
                                               uintptr_t virt_start_relative)
{
    xbaddr xSymbolAddr = 0;
    OOVPARevision* pSymbolRevision = NULL;
    OOVPATable* pSymbolEntry = NULL;

    // Find XapiMapLetterToDirectory function
    if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_XapiMapLetterToDirectory])) {
        const char* xref_str = "XGetSectionSize";

        xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                   pLibrarySession,
                                                                                   pLibraryDB,
                                                                                   pSection,
                                                                                   XREF_XapiMapLetterToDirectory,
                                                                                   DB_ST_MANUAL,
                                                                                   FIRSTPASS_YES,
                                                                                   REGISTER_YES,
                                                                                   &pSymbolEntry,
                                                                                   &pSymbolRevision);

        if (xSymbolAddr) {

            // Register XGetSectionSize function.
            if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_XGetSectionSize])) {
                // If relative address is not recorded, then signature needs a fix.
                output_message_format(&pContext->output,
                                      XB_OUTPUT_MESSAGE_ERROR,
                                      "Please verify %s (%hu) signature do contain %s's xref entry.",
                                      pSymbolEntry->szSymbolName, pSymbolRevision->Version, xref_str);
                return false;
            }
            // Manually translate to virtual address from relative address.
            xSymbolAddr = XbSDBi_OOVPARevision_ConvertXRefRelativeAddrtToVirtAddr(pContext, pSymbolEntry, pSymbolRevision, xref_str, XREF_XGetSectionSize);
            if (!xSymbolAddr) {
                // Error message is handled by above function. No extra message necessary here.
                return false;
            }
            // Update to use virtual address instead of relative address.
            pContext->xref_database[XREF_XGetSectionSize] = xSymbolAddr;

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, XGetSectionSize);
            XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, pSymbolRevision->Version);
        }
    }

    return true;
}

static bool internal_xapi_find_DeviceType_MU(XbSDBiContext* pContext,
                                             const XbSDBiLibrarySession* pLibrarySession,
                                             SymbolDatabaseList* pLibraryDB,
                                             const XbSDBSection* pSection,
                                             uintptr_t virt_start_relative)
{
    xbaddr xSymbolAddr = 0;
    memptr_t buffer_upper = (memptr_t)pSection->buffer_lower + pSection->buffer_size;

    // Find MU_Init function
    if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_MU_Init])) {

        xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                   pLibrarySession,
                                                                                   pLibraryDB,
                                                                                   pSection,
                                                                                   XREF_MU_Init,
                                                                                   DB_ST_MANUAL,
                                                                                   FIRSTPASS_YES,
                                                                                   REGISTER_YES,
                                                                                   NULL,
                                                                                   NULL);
    }

    if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_MU_Init])) {
        // If not found, skip the rest of the scan.
        return false;
    }


    // Scan for IUsbInit::GetMaxDeviceTypeCount function.
    if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_IUsbInit_GetMaxDeviceTypeCount])) {
        xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                   pLibrarySession,
                                                                                   pLibraryDB,
                                                                                   pSection,
                                                                                   XREF_IUsbInit_GetMaxDeviceTypeCount,
                                                                                   DB_ST_MANUAL,
                                                                                   FIRSTPASS_YES,
                                                                                   REGISTER_YES,
                                                                                   NULL,
                                                                                   NULL);

        // If not found, skip the rest of the scan.
        if (xSymbolAddr == 0) {
            return false;
        }
    }

    xSymbolAddr = 0;
    // TODO: Move below into separate function.
    // search all of the buffer memory range
    for (memptr_t cur = (memptr_t)virt_start_relative + pContext->xref_database[XREF_MU_Init]; cur < buffer_upper; cur++) {
        // We are looking for "leave; ret 0x04;" for end of function then stop searching.
        if (cur[0] == 0xC9 && cur[1] == 0xC2 && cur[2] == 0x04) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Could not find g_DeviceType_MU from MU_Init!");
            return false;
        }

        // Look for possible push and call next to each other.
        if (cur[0] == 0x68 && cur[5] == 0xE8) {

            // check if call is linked to IUsbInit_GetMaxDeviceTypeCount function.
            xbaddr ActualAddr = *(xbaddr*)(cur + 6);
            if (XbSDBi_MatchXRefAddr(cur + 6, virt_start_relative, pContext->xref_database[XREF_IUsbInit_GetMaxDeviceTypeCount])) {
                // this is where g_DeviceType_MU hardcode address reside in.
                xSymbolAddr = *(xbaddr*)(cur + 1);
                break;
            }
        }
    }

    // register if g_DeviceType_MU is not valid.
    if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_g_DeviceType_MU])) {

        // Register g_DeviceType_MU
        OOVPATable* pSymbolEntry = NULL;
        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceType_MU);
        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, pSymbolEntry->revisions[0].Version, xSymbolAddr);
    }

    return true;
}

static bool internal_xapi_find_device_types(XbSDBiContext* pContext,
                                            const XbSDBiLibrarySession* pLibrarySession,
                                            SymbolDatabaseList* pLibraryDB,
                                            const XbSDBSection* pSection,
                                            uintptr_t virt_start_relative)
{
    xbaddr xSymbolAddr = 0;

    // Find GetTypeInformation function
    if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_GetTypeInformation])) {
        xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                   pLibrarySession,
                                                                                   pLibraryDB,
                                                                                   pSection,
                                                                                   XREF_GetTypeInformation,
                                                                                   DB_ST_MANUAL,
                                                                                   FIRSTPASS_YES,
                                                                                   REGISTER_YES,
                                                                                   NULL,
                                                                                   NULL);

        // If GetTypeInformation is not found, then try find GetTypeInformation2
        if (!xSymbolAddr) {
            xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                       pLibrarySession,
                                                                                       pLibraryDB,
                                                                                       pSection,
                                                                                       XREF_GetTypeInformation2,
                                                                                       DB_ST_MANUAL,
                                                                                       FIRSTPASS_YES,
                                                                                       REGISTER_YES,
                                                                                       NULL,
                                                                                       NULL);
        }

        // If either GetTypeInformation overload is found, start look up in DeviceTypeInfo table's entries.
        if (xSymbolAddr) {

            // TODO: Make below as self-register
            OOVPATable* pSymbolEntry = NULL;
            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceTypeInfoTableBegin);
            XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 4242);
            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceTypeInfoTableEnd);
            XbSDBi_RegisterSelfValidXRefAddr(pContext, pLibrarySession, pSymbolEntry, 4242);

            uint32_t* table_i = (uint32_t*)XbSDBi_section_VirtToHostAddress(pContext, pContext->xref_database[XREF_g_DeviceTypeInfoTableBegin]);
            uint32_t* table_end = (uint32_t*)XbSDBi_section_VirtToHostAddress(pContext, pContext->xref_database[XREF_g_DeviceTypeInfoTableEnd]);
            size_t type_description_table_count = ((memptr_t)table_end - (memptr_t)table_i) / sizeof(uint32_t);

            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "DeviceTypeInfoTable Entries: %u", type_description_table_count);

            // Partial extracted for ucType and XppType fields needed to get specific device type named.
            typedef struct _XID_TYPE_INFORMATION {
                uint8_t ucType;
                uint8_t bRemainingHandles;
                uint8_t ucUnknown[2]; // probably for xbox::dword_xt align
                xbaddr XppType;       // pointer to DeviceType structure.
            } XID_TYPE_INFORMATION, *PXID_TYPE_INFORMATION;

            // Iterate through the table until we find known device types.
            int i = 0;
            for (; table_i < table_end; table_i++, i++) {
                PXID_TYPE_INFORMATION DeviceTypeInfo = (PXID_TYPE_INFORMATION)XbSDBi_section_VirtToHostAddress(pContext, *table_i);
                if (!DeviceTypeInfo) {
                    // if address is nullptr, then skip it.
                    continue;
                }
                switch (DeviceTypeInfo->ucType) {
                    case 1: // Gamepad (Generic)
                        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceType_Gamepad);
                        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 0, DeviceTypeInfo->XppType);
                        break;
                    case 2: // Keyboard
                        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceType_Keyboard);
                        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 0, DeviceTypeInfo->XppType);
                        break;
                    case 3: // IR Dongle
                        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceType_IRDongle);
                        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 0, DeviceTypeInfo->XppType);
                        break;
                    case 4: // Mouse
                        // NOTE: Possibly introduced when Phantasy Star Online (b4831) added keyboard support.
                        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceType_Mouse);
                        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 0, DeviceTypeInfo->XppType);
                        break;
                    case 128: // Steel Battalion
                        XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, g_DeviceType_SBC);
                        XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 4242, DeviceTypeInfo->XppType);
                        break;
                    default: // Unknown
                        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Unknown device type, DeviceTypeInfoTable[%hhu]:  ucType = %hhu, XppType = %08X", i, DeviceTypeInfo->ucType, DeviceTypeInfo->XppType);
                        break;
                }
            }
        }
        else {
            // Find XInputOpen function
            if (!XbSDBi_IsXRefAddrValid(pContext->xref_database[XREF_XInputOpen])) {
                xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                           pLibrarySession,
                                                                                           pLibraryDB,
                                                                                           pSection,
                                                                                           XREF_XInputOpen,
                                                                                           DB_ST_MANUAL,
                                                                                           FIRSTPASS_YES,
                                                                                           REGISTER_YES,
                                                                                           NULL,
                                                                                           NULL);
                // No further manual action require.
            }
        }
    }

    if (!xSymbolAddr) {
        return false;
    }

    return true;
};

static bool manual_scan_section_xapilib(XbSDBiContext* pContext,
                                        const XbSDBiLibrarySession* pLibrarySession,
                                        SymbolDatabaseList* pLibraryDB,
                                        const XbSDBSection* pSection)
{
    // Generic usage
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;

    bool foundXGetSectionSize = internal_xapi_find_XGetSectionSize(pContext, pLibrarySession, pLibraryDB, pSection, virt_start_relative);

    bool foundMURefs = internal_xapi_find_DeviceType_MU(pContext, pLibrarySession, pLibraryDB, pSection, virt_start_relative);

    bool foundDeviceTypes = internal_xapi_find_device_types(pContext, pLibrarySession, pLibraryDB, pSection, virt_start_relative);

    return foundXGetSectionSize && foundMURefs && foundDeviceTypes;
}

static inline void manual_register_xapilib(XbSDBiContext* pContext)
{
    // TODO: Make everything below have ability to perform self-register. (but we need difference between virtual and relative address.... can it be built-in support?)
    //       Actually, let's make a separate pull request for this...
    // NOTE: These device types can be self-register according to XInputOpen signature. But newer implementation require manual search.
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceType_Gamepad, 0, "g_DeviceType_Gamepad", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceType_IRDongle, 0, "g_DeviceType_IRDongle", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceType_Keyboard, 0, "g_DeviceType_Keyboard", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceType_Mouse, 0, "g_DeviceType_Mouse", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceType_SBC, 4242, "g_DeviceType_SBC", symbol_variable, call_none, 0, NULL);
    //XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceTypeInfoTableBegin, 4242, "g_DeviceTypeInfoTableBegin", symbol_variable, call_none, 0, NULL);
    //XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_DeviceTypeInfoTableEnd, 4242, "g_DeviceTypeInfoTableEnd", symbol_variable, call_none, 0, NULL);
    // TODO: The above could actually do self-register but... do we need to?
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_XapiAltLett_MU, 0, "g_XapiAltLett_MU", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_XapiMountedMUs, 0, "g_XapiMountedMUs", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_g_XapiCurrentTopLevelFilter, 0, "g_XapiCurrentTopLevelFilter", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF__tls_array, 0, "_tls_array", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF__tls_index, 0, "_tls_index", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_XapiCurrentFiber_OFFSET, 0, "XapiCurrentFiber_OFFSET", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_XapiLastErrorCode_OFFSET, 0, "XapiLastErrorCode_OFFSET", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_XapiThreadFiberData_OFFSET, 0, "XapiThreadFiberData_OFFSET", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_XAPILIB, XBSDBLIB_XAPILIB, XREF_XapiThreadNotifyRoutineList, 0, "XapiThreadNotifyRoutineList", symbol_variable, call_none, 0, NULL);
}
