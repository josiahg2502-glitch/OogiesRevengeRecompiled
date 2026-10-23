// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

#pragma once

static bool manual_scan_section_dsound(XbSDBiContext* pContext,
                                       const XbSDBiLibrarySession* pLibrarySession,
                                       SymbolDatabaseList* pLibraryDB,
                                       const XbSDBSection* pSection)
{
    // Generic usage
    xbaddr xblower = pSection->xb_virt_addr;
    xbaddr xbupper = pSection->xb_virt_addr + pSection->buffer_size;
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;
    xbaddr xSymbolAddr = 0;
    memptr_t pSymbolAddr = 0;

    /*
    bool testRun = 1;
    while (testRun) {
    }//*/

    // Scan for DirectSoundStream's constructor function.
    if (pContext->xref_database[XREF_CDirectSoundStream_Constructor] == XREF_ADDR_UNDETERMINED) {
        xSymbolAddr = (xbaddr)(uintptr_t)XbSDBi_SymbolDatabaseList_ScanByReference(pContext,
                                                                                   pLibrarySession,
                                                                                   pLibraryDB,
                                                                                   pSection,
                                                                                   XREF_CDirectSoundStream_Constructor,
                                                                                   DB_ST_MANUAL,
                                                                                   FIRSTPASS_YES,
                                                                                   REGISTER_YES,
                                                                                   NULL,
                                                                                   NULL);

        // If not found, skip the rest of the scan.
        if (xSymbolAddr == 0) {
            return false;
        }

        // TODO: If possible, integrate into the OOVPA structure.
        XbSDBi_RegisterXRef(pContext, pLibrarySession, XREF_DSS_VOICE_VTABLE, 3911,
                            NULL, *(xbaddr*)(virt_start_relative + xSymbolAddr + 0x14), symbol_variable, call_none, 0, NULL, false);
        XbSDBi_RegisterXRef(pContext, pLibrarySession, XREF_DSS_STREAM_VTABLE, 3911,
                            NULL, *(xbaddr*)(virt_start_relative + xSymbolAddr + 0x1B), symbol_variable, call_none, 0, NULL, false);
    }

    // Verify both variables are already set from the scan function above.
    if (pContext->xref_database[XREF_DSS_STREAM_VTABLE] == XREF_ADDR_DERIVE ||
        pContext->xref_database[XREF_DSS_VOICE_VTABLE] == XREF_ADDR_DERIVE) {

        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Something went wrong with finding DSS' vtables...");
        return false;
    }

    // Finally, manually add CDirectSoundStream's AddRef and Release functions.
    if (pContext->xref_database[XREF_CDirectSoundStream_AddRef] == XREF_ADDR_UNDETERMINED) {
        xbaddr vtable = pContext->xref_database[XREF_DSS_STREAM_VTABLE];

        if (xblower <= vtable && vtable < xbupper) {
            pSymbolAddr = (memptr_t)virt_start_relative + vtable;
            OOVPATable* pSymbolEntry = NULL;
            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_AddRef);
            XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 3911, *(uint32_t*)(pSymbolAddr + 0 * 4));

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_Release);
            XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 3911, *(uint32_t*)(pSymbolAddr + 1 * 4));

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_GetInfo);
            XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 3911, *(uint32_t*)(pSymbolAddr + 2 * 4));

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_GetStatus);
            // TODO: May need further investigation with Cxbx-Reloaded's source code for possible reasoning why this method is used.
            SYMBOL_COUNTER_VALUE; // Force increase by one symbol counter since we do not have both revisions difference in the OOVPA database.
            if (pLibrarySession->pLibrary->build_version < 4134) {
                XbSDBi_RegisterSymbolHelper(pContext, pLibrarySession, pSymbolEntry, "CDirectSoundStream_GetStatus__r1", 3911, *(uint32_t*)(pSymbolAddr + 3 * 4));
            }
            else {
                XbSDBi_RegisterSymbolHelper(pContext, pLibrarySession, pSymbolEntry, "CDirectSoundStream_GetStatus__r2", 4134, *(uint32_t*)(pSymbolAddr + 3 * 4));
            }

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_Process);
            XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 3911, *(uint32_t*)(pSymbolAddr + 4 * 4));

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_Discontinuity);
            XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 3911, *(uint32_t*)(pSymbolAddr + 5 * 4));

            XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbolEntry, CDirectSoundStream_Flush);
            XbSDBi_RegisterSymbol(pContext, pLibrarySession, pSymbolEntry, 3911, *(uint32_t*)(pSymbolAddr + 6 * 4));

            // NOTE: it is possible to manual add GetInfo, GetStatus, Process, Discontinuity,
            // and Flush functions.
        }
        else {
            return false;
        }
    }

    return true;
}
