// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

#pragma once

// ******************************************************************
// * internal functions designed for XbSymbolDatabase purpose
// ******************************************************************

static SymbolDatabaseList* XbSDBi_FindLibraryDB(uint32_t library_flag, unsigned* db_i)
{
    unsigned db = *db_i;
    for (; db < SymbolDBListCount; db++) {
        // Check if library flag match then return symbol database.
        if ((library_flag & SymbolDBList[db].LibSec.library) > 0) {
            *db_i = db;
            return &SymbolDBList[db];
        }
    }
    *db_i = db;
    return NULL;
}

// NOTE: PatrickvL state the arguments are named differently and the function does something that has another meaning,
//       the implementation could be changed if the need ever arises.
static inline void XbSDBi_GetXRefEntry(OOVPA* oovpa, int index, uint32_t* xref_out, uint16_t* offset_out)
{
    *xref_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].xref.index;
    *offset_out = ((LOOVPA*)oovpa)->Lovp[index].offset;
}

static inline void XbSDBi_GetOovpaEntry(OOVPA* oovpa, int index, uint32_t* offset_out, uint8_t* value_out)
{
    *offset_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].offset;
    *value_out = (uint8_t)((LOOVPA*)oovpa)->Lovp[index].value;
}

static inline bool XbSDBi_MatchXRefAddr(memptr_t cur, uintptr_t xb_start_virt_addr, xbaddr XRefAddr)
{
    xbaddr ActualAddr = *(xbaddr*)(cur);
    // check if PC-relative or direct reference matches XRef
    if ((ActualAddr + (xbaddr)((uintptr_t)cur - xb_start_virt_addr) + 4 != XRefAddr) && (ActualAddr != XRefAddr))
        return false;

    return true;
}

static bool XbSDBi_CompareOOVPAToAddress(XbSDBiContext* pContext, OOVPA* Oovpa, memptr_t cur, uintptr_t xb_start_virt_addr)
{
    uint32_t v = 0; // verification counter

    // Check all XRefs, stop if any does not match
    for (; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint16_t Offset;

        // get currently registered (un)known address
        XbSDBi_GetXRefEntry(Oovpa, v, &XRef, &Offset);
        xbaddr XRefAddr = pContext->xref_database[XRef];
        // Undetermined XRef cannot be checked yet
        // (XbSymbolLocateFunction already checked this, but this check
        // is cheap enough to keep, and keep this function generic).
        if (XRefAddr == XREF_ADDR_UNDETERMINED)
            return false;

        // Don't verify an xref that has to be (but isn't yet) derived
        if (XRefAddr == XREF_ADDR_DERIVE)
            continue;

        // check if PC-relative or direct reference matches XRef
        if (!XbSDBi_MatchXRefAddr(cur + Offset, xb_start_virt_addr, XRefAddr))
            return false;
    }

    // Check all (Offset,Value)-pairs, stop if any does not match
    for (; v < Oovpa->Count; v++) {
        uint32_t Offset;
        uint8_t ExpectedValue;

        // get offset + value pair
        XbSDBi_GetOovpaEntry(Oovpa, v, &Offset, &ExpectedValue);
        uint8_t ActualValue = *(uint8_t*)(cur + Offset);
        if (ActualValue != ExpectedValue)
            return false;
    }

    // all offsets matched
    return true;
}

// Return if the given (XRef'erenced) is not set yet.
static inline bool XbSDBi_IsXRefUnset(uint16_t XRef)
{
    return (XRef == (uint16_t)XREF_ADDR_UNDETERMINED) || (XRef == XREF_ADDR_DERIVE);
}

// Return if the given (XRef'erenced) address is not set yet.
static inline bool XbSDBi_IsXRefAddrUnset(xbaddr XRefAddr)
{
    return (XRefAddr == XREF_ADDR_UNDETERMINED) || (XRefAddr == XREF_ADDR_DERIVE);
}

// Return if the given (XRef'erenced) address is valid.
static bool XbSDBi_IsXRefAddrValid(xbaddr XRefAddr)
{
    return (XRefAddr + 1) > (XREF_ADDR_DERIVE + 1); // Implies also not equal to XREF_ADDR_UNDETERMINED (-1) nor XREF_ADDR_NOT_FOUND (0)
}

static xbaddr XbSDBi_OOVPARevision_ConvertXRefRelativeAddrtToVirtAddr(XbSDBiContext* pContext,
                                                                      const OOVPATable* pSymbol,
                                                                      const OOVPARevision* pRevision,
                                                                      const char* xref_str,
                                                                      XRefDatabase xref_target)
{
    if (pRevision->Oovpa->XRefCount == 0) {
        // Should not be triggered when there is no xref listed.
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "%s (%hu) signature cannot have zero XRefCount when calling %s!", pSymbol->szSymbolName, pRevision->Version, __func__);
        return 0;
    }

    xbaddr virt_start_addr = pContext->xref_database[pSymbol->xref];

    LOVP* lovp = ((LOOVPA*)pRevision->Oovpa)->Lovp;
    int offset = -1;
    for (unsigned i = 0; i < pRevision->Oovpa->XRefCount; i++) {
        if (lovp->xref.index == xref_target) {
            offset = lovp->offset;
            break;
        }
    }

    if (offset == -1) {
        // If no match is found, then contributor need to verify both OOVPA revision and xref index are correct.
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "%s (%hu) signature does not have %s's xref entry!", pSymbol->szSymbolName, pRevision->Version, xref_str);
        return 0;
    }

    virt_start_addr += offset + pContext->xref_database[xref_target] + 4 /*32 bit size of address space range */;

    return virt_start_addr;
}

// Obligatory function for setting an address in the XRefDataBase
// (only initialization may write to XRefDataBase outside of this function).
static inline void XbSDBi_SetXRefDatabase(XbSDBiContext* pContext, eLibraryType iLibraryType, uint32_t XRef, xbaddr XRefAddr)
{
    // Count when changing from an initial value to a valid value
    if (XbSDBi_IsXRefAddrUnset(pContext->xref_database[XRef])) {
        pContext->library_contexts[iLibraryType].xref_registered++;
    }
    pContext->xref_database[XRef] = XRefAddr; // Besides initialization, this is the only code that writes values to XRefDataBase
}

// locate the given symbol, searching within lower and upper bounds
static void* XbSDBi_LocateSymbol(XbSDBiContext* pContext,
                                 eLibraryType iLibraryType,
                                 const char* szSymbolName,
                                 uint16_t version,
                                 OOVPA* Oovpa,
                                 const XbSDBSection* pSection,
                                 bool xref_first_pass)
{
    memptr_t buffer_upper = (memptr_t)pSection->buffer_lower + pSection->buffer_size;
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;

    // skip out if this is an unnecessary search
    if (!xref_first_pass && Oovpa->XRefCount == XRefZero)
        return 0;

    uint32_t derive_indices = 0;
    void* symbol_address = NULL;

    // Check all XRefs are known (if not, don't do a useless scan) :
    for (unsigned int v = 0; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint16_t Offset;

        // get currently registered (un)known address
        XbSDBi_GetXRefEntry(Oovpa, v, &XRef, &Offset);
        xbaddr XRefAddr = pContext->xref_database[XRef];
        // Undetermined XRef cannot be checked yet
        if (XRefAddr == XREF_ADDR_UNDETERMINED)
            // Skip this scan over the address range
            return 0;

        // Don't verify an xref that has to be (but isn't yet) derived
        if (XRefAddr == XREF_ADDR_DERIVE) {
            // Mark (up to index 32) which xref needs to be derived
            derive_indices |= (1 << v);
            continue;
        }
    }

    // correct upper bound with highest Oovpa offset
    uint32_t count = Oovpa->Count;
    {
        uint32_t Offset;
        uint8_t Value; // ignored

        XbSDBi_GetOovpaEntry(Oovpa, count - 1, &Offset, &Value);
        buffer_upper -= Offset;
    }

    //
    unsigned int detect_selection = Oovpa->DetectSelect;
    unsigned int counter = 0;

    // search all of the buffer memory range
    for (memptr_t cur = pSection->buffer_lower; cur < buffer_upper; cur++) {
        if (XbSDBi_CompareOOVPAToAddress(pContext, Oovpa, cur, virt_start_relative)) {

            // Increase the counter whenever detected address is found.
            counter++;

            while (derive_indices > 0) {
                uint32_t XRef;
                uint16_t Offset;
                uint32_t derive_index;

                // Extract an index from the indices mask
                derive_index = BitScanReverse(derive_indices);
                derive_indices ^= (1 << derive_index);

                // get currently registered (un)known address
                XbSDBi_GetXRefEntry(Oovpa, derive_index, &XRef, &Offset);

                // Calculate the address where the XRef resides and read the address it points to
                uint32_t XRefAddr = *(uint32_t*)(cur + Offset);

                // NOTE: Commented out code belows are no longer valid since we are using lower and upper passdown only.

                /* For now assume it's a direct reference;
                // TODO : Check if it's PC-relative reference?
                if (XRefAddr + cur + Offset + 4 < XBE_MAX_VA)
                XRefAddr = XRefAddr + cur + Offset + 4;
                */

                // Does the address seem valid?
                /*if (XRefAddr < XBE_MAX_VA) {
                    // save and count the derived address
                    SetXRefDataBase(pContext, XRef, XRefAddr);
                }*/

                // Check if selection is default (zero) then perform the standard procedure.
                if (detect_selection == 0) {
                    if (!pContext->scan_first_detect || (pContext->scan_first_detect && symbol_address == NULL)) {
                        XbSDBi_SetXRefDatabase(pContext, iLibraryType, XRef, XRefAddr);
                    }
                }
                // Otherwise, perform a detected selection procedure.
                else {
                    // If counter match the target selection, then save the ref address.
                    if (detect_selection == counter) {
                        XbSDBi_SetXRefDatabase(pContext, iLibraryType, XRef, XRefAddr);
                    }
                }
            }

            // Check if selection is default (zero) then perform the standard procedure.
            if (detect_selection == 0) {

                if (symbol_address != NULL) {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                          "Duplicate symbol detection found for %s (%hu), 0x%08x vs 0x%08x",
                                          szSymbolName, version, symbol_address, cur - virt_start_relative);
                }

                if (!pContext->scan_first_detect || (pContext->scan_first_detect && symbol_address == NULL)) {
                    symbol_address = cur - virt_start_relative;
                }

                if (pContext->one_time_scan) {
                    break;
                }
            }
            // Otherwise, perform a detected selection procedure.
            else {
                // If counter match the detected selection, then perform a force break here
                // with address set.
                if (detect_selection == counter) {
                    symbol_address = cur - virt_start_relative;

                    if (pContext->one_time_scan) {
                        break;
                    }
                }
                // Otherwise, let's log debug info about what is skipped address detection.
                else {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG,
                                          "Skipped symbol detection found for %s (%hu), 0x%08x",
                                          szSymbolName, version, cur - virt_start_relative);
                }
            }
        }
    }

    return symbol_address;
}

// Old Method - However, the library's scan method doesn't have self-register support implemented yet.
// NOTE: Do not use direct call to this function. Use XbSDBi_RegisterValidXRefAddr_M macro instead.
static void XbSDBi_RegisterValidXRefAddr(XbSDBiContext* pContext,
                                         const char* library_name,
                                         uint32_t library_flag,
                                         uint32_t XRefIndex,
                                         uint16_t version,
                                         const char* symbol_name,
                                         XbSDBSymbolType symbol_type,
                                         XbSDBCallType call_type,
                                         unsigned param_count,
                                         const XbSDBSymbolParam* param_list)
{
    xbaddr xSymbolAddr = pContext->xref_database[XRefIndex];

    if (XbSDBi_IsXRefAddrValid(xSymbolAddr)) {
        pContext->register_func(library_name, library_flag, XRefIndex, symbol_name, xSymbolAddr, version, symbol_type, call_type, param_count, param_list);
    }
}

// Always use this to be aware of manual register xrefs such as variables.
#define XbSDBi_RegisterValidXRefAddr_M(...) \
    SYMBOL_COUNTER_VALUE;                   \
    XbSDBi_RegisterValidXRefAddr(__VA_ARGS__);

// New Method
static void XbSDBi_RegisterSelfValidXRefAddr(XbSDBiContext* pContext,
                                             const XbSDBiLibrarySession* pLibrarySession,
                                             const OOVPATable* pSymbol,
                                             uint16_t version)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    xbaddr xSymbolAddr = pContext->xref_database[pSymbol->xref];

    if (XbSDBi_IsXRefAddrValid(xSymbolAddr)) {
        pContext->register_func(pLibrary->name, pLibrary->flag, pSymbol->xref, pSymbol->szSymbolName, xSymbolAddr, version, pSymbol->symbol_type, pSymbol->call_type, pSymbol->param_count, pSymbol->param_list);
    }
}

// Old Method
static void XbSDBi_RegisterXRef(XbSDBiContext* pContext,
                                const XbSDBiLibrarySession* pLibrarySession,
                                uint32_t XRefIndex,
                                uint16_t version,
                                const char* symbol_name,
                                uint32_t symbol_addr,
                                XbSDBSymbolType symbol_type,
                                XbSDBCallType call_type,
                                unsigned param_count,
                                const XbSDBSymbolParam* param_list,
                                bool do_register)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    xbaddr xRefAddr = pContext->xref_database[XRefIndex];

    if (XbSDBi_IsXRefAddrValid(xRefAddr)) {

        if (pContext->xref_database[XRefIndex] != symbol_addr) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                  "Duplicate XREF address found for %s (%hu), %08X vs %08X!",
                                  symbol_name, version, xRefAddr, symbol_addr);
        }

        if (pContext->scan_first_detect) {
            return;
        }
    }

    XbSDBi_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XRefIndex, symbol_addr);
    if (do_register && pContext->register_func != NULL) {
        pContext->register_func(pLibrary->name, pLibrary->flag, XRefIndex, symbol_name, symbol_addr, version, symbol_type, call_type, param_count, param_list);
    }
}

// New method
static void XbSDBi_RegisterXRefHelper(XbSDBiContext* pContext,
                                      const XbSDBiLibrarySession* pLibrarySection,
                                      const OOVPATable* pSymbol,
                                      uint16_t version,
                                      uint32_t symbol_addr,
                                      bool do_register)
{
    XbSDBi_RegisterXRef(pContext, pLibrarySection, pSymbol->xref, version, pSymbol->szSymbolName, symbol_addr, pSymbol->symbol_type, pSymbol->call_type, pSymbol->param_count, pSymbol->param_list, do_register);
}

// (Old / Manual) method
static void XbSDBi_RegisterSymbolManual(XbSDBiContext* pContext,
                                        const XbSDBiLibrarySession* pLibrarySession,
                                        const XRefDatabase xref_index,
                                        uint16_t version,
                                        const char* symbol_name,
                                        uint32_t symbol_addr,
                                        const XbSDBSymbolType symbol_type,
                                        const XbSDBCallType call_type,
                                        const unsigned param_count,
                                        const XbSDBSymbolParam* param_list)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // If XRef is not found, save it then register once.
    if (XbSDBi_IsXRefAddrUnset(pContext->xref_database[xref_index])) {
        XbSDBi_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, xref_index, symbol_addr);
        if (pContext->register_func != NULL) {
            pContext->register_func(pLibrary->name, pLibrary->flag, xref_index, symbol_name, symbol_addr, version, symbol_type, call_type, param_count, param_list);
        }
    }
}

// Use _M suffix only, if OOVPA signature is not in database.
#define XbSDBi_RegisterSymbol_M(...) \
    SYMBOL_COUNTER_VALUE;            \
    XbSDBi_RegisterSymbolManual(__VA_ARGS__);

// New method
static void XbSDBi_RegisterSymbol(XbSDBiContext* pContext,
                                  const XbSDBiLibrarySession* pLibrarySession,
                                  const OOVPATable* pSymbol,
                                  uint16_t version,
                                  uint32_t symbol_addr)
{
    // forward to XbSDBi_RegisterSymbolManual to avoid need to copy paste between two identical functions.
    XbSDBi_RegisterSymbolManual(pContext, pLibrarySession, pSymbol->xref, version, pSymbol->szSymbolName, symbol_addr, pSymbol->symbol_type, pSymbol->call_type, pSymbol->param_count, pSymbol->param_list);
}


static OOVPATable* XbSDBi_OOVPATable_FindBySymbolName(SymbolDatabaseList* LibraryDB, const char* szSymbolName, unsigned scan_type)
{
    OOVPATableList* Symbols = LibraryDB->Symbols;
    for (unsigned i = 0; i < Symbols->Count; i++) {

        // Intended for optimization purpose without need to search every single symbol's string.
        if ((scan_type & LibraryDB->Symbols->Table[i].scan_type) == 0) {
            continue;
        }

        if (strcmp(szSymbolName, Symbols->Table[i].szSymbolName) == 0) {
            return &Symbols->Table[i];
        }
    }
    return NULL;
}

static OOVPATable* XbSDBi_OOVPATable_FindByReference(SymbolDatabaseList* LibraryDB, uint16_t xref_index, unsigned scan_type)
{
    OOVPATableList* Symbols = LibraryDB->Symbols;
    for (unsigned i = 0; i < Symbols->Count; i++) {

        // Intended for optimization purpose without need to search every single symbol's string.
        if ((scan_type & Symbols->Table[i].scan_type) == 0) {
            continue;
        }

        if (Symbols->Table[i].xref == xref_index) {
            return &Symbols->Table[i];
        }
    }
    return NULL;
}

#define XbSDBi_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, xref)                                            \
    pSymbol = XbSDBi_OOVPATable_FindByReference(pLibraryDB, XREF_##xref, DB_ST_MANUAL);                              \
    if (!pSymbol) {                                                                                                  \
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Unable to find " #xref " entry in database..."); \
        return false;                                                                                                \
    }

#define XbSDBi_RegisterSymbolHelper(pContext, pLibrarySession, pSymbol, szSymbolName, version, symbol_addr) \
    XbSDBi_RegisterSymbolManual(pContext, pLibrarySession, pSymbol->xref, version, szSymbolName, symbol_addr, pSymbol->symbol_type, pSymbol->call_type, pSymbol->param_count, pSymbol->param_list)

static void XbSDBi_OOVPATable_scan(XbSDBiContext* pContext,
                                   const XbSDBiLibrarySession* pLibrarySession,
                                   const XbSDBSection* pSection,
                                   const bool xref_first_pass,
                                   const OOVPATable* pSymbol,
                                   OOVPARevision** pRevisionReturn,
                                   void** pAddressReturn)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    OOVPARevision* pLastKnownRevision = NULL;
    void* pLastKnownSymbolAddr = 0;

    for (unsigned i = 0; i < pSymbol->count; i++) {
        OOVPARevision* pRevision = &pSymbol->revisions[i];

        // Skip higher build version
        if (pContext->strict_build_version_limit && pLibrary->build_version < pRevision->Version)
            continue;

        // Search for each symbol's location using the OOVPA
        void* symbol_addr = XbSDBi_LocateSymbol(pContext, iLibraryType, pSymbol->szSymbolName, pRevision->Version, pRevision->Oovpa, pSection, xref_first_pass);
        if (symbol_addr == 0) {
            continue;
        }

        if (symbol_addr == pLastKnownSymbolAddr && pLastKnownRevision == pRevision - 1) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                  "Duplicate OOVPA signature found for %s, %hu vs %hu!",
                                  pSymbol->szSymbolName, pLastKnownRevision->Version, pRevision->Version);
        }

        if (pLibrary->build_version < pRevision->Version) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                  "OOVPA signature is too high for [%hu] %s!",
                                  pRevision->Version, pSymbol->szSymbolName);
        }

        pLastKnownSymbolAddr = symbol_addr;
        pLastKnownRevision = pRevision;
    }

    *pAddressReturn = pLastKnownSymbolAddr;
    *pRevisionReturn = pLastKnownRevision;
}

static void* XbSDBi_SymbolDatabaseList_ScanByReference(XbSDBiContext* pContext,
                                                       const XbSDBiLibrarySession* pLibrarySession,
                                                       SymbolDatabaseList* LibraryDB,
                                                       const XbSDBSection* pSection,
                                                       const uint16_t xref_index,
                                                       const unsigned scan_type,
                                                       const eFirstPass xref_first_pass,
                                                       const eRegisterSymbol register_symbol,
                                                       OOVPATable** pSymbolReturn,
                                                       OOVPARevision** pRevisionReturn)
{
    OOVPARevision* pRevision = NULL;
    void* pSymbolAddr = NULL;
    OOVPATableList* Symbols = LibraryDB->Symbols;
    for (unsigned i = 0; i < Symbols->Count; i++) {

        // Intended for optimization purpose without need to search every single symbol reference index.
        if ((scan_type & Symbols->Table[i].scan_type) == 0) {
            continue;
        }

        if (Symbols->Table[i].xref == xref_index) {
            // If reference is found, then perform the scan process.
            XbSDBi_OOVPATable_scan(pContext,
                                   pLibrarySession,
                                   pSection,
                                   xref_first_pass,
                                   Symbols->Table + i,
                                   &pRevision,
                                   &pSymbolAddr);

            // if symbol is found, then make the break to return the symbol entry.
            if (pSymbolAddr) {
                if (pSymbolReturn) {
                    *pSymbolReturn = Symbols->Table + i;
                }
                if (pRevisionReturn) {
                    *pRevisionReturn = pRevision;
                }
                if (register_symbol) {
                    XbSDBi_RegisterSymbol(pContext, pLibrarySession, Symbols->Table + i, pRevision->Version, (xbaddr)(uintptr_t)pSymbolAddr);
                }
                break;
            }
        }
    }
    return pSymbolAddr;
}

static void XbSDBi_OOVPA_register(XbSDBiContext* pContext,
                                  const OOVPATable* Symbol,
                                  const OOVPARevision* OovpaRevision,
                                  const XbSDBiLibrarySession* pLibrarySession,
                                  xbaddr address)
{
    if (OovpaRevision != NULL) {
        XbSDBi_RegisterSymbol(pContext, pLibrarySession, Symbol, OovpaRevision->Version, address);
    }
}

static void XbSDBi_OOVPATableList_scan(XbSDBiContext* pContext,
                                       const XbSDBiLibrarySession* pLibrarySession,
                                       OOVPATableList* Symbols,
                                       const XbSDBSection* pSection,
                                       const bool xref_first_pass)
{
    // traverse the full OOVPA table
    OOVPATable* pSymbolEnd = &Symbols->Table[Symbols->Count];
    OOVPATable* pSymbol = Symbols->Table;

    for (; pSymbol < pSymbolEnd; pSymbol++) {

        // We only want to do normal scan process.
        // If there's a symbol require manual scan, skip it.
        // Since manual scan is performed separately.
        if ((pSymbol->scan_type & DB_ST_AUTO) == 0) {
            continue;
        }

        OOVPARevision* pLastKnownRevision = NULL;
        void* lastKnownSymbolAddr = 0;

        XbSDBi_OOVPATable_scan(pContext,
                               pLibrarySession,
                               pSection,
                               xref_first_pass,
                               pSymbol,
                               &pLastKnownRevision,
                               &lastKnownSymbolAddr);

        if (pLastKnownRevision != NULL) {
            XbSDBi_OOVPA_register(pContext, pSymbol, pLastKnownRevision, pLibrarySession, (xbaddr)(uintptr_t)lastKnownSymbolAddr);
        }
    }
}

static eLibraryType XbSDBi_GetLibraryType(uint32_t library)
{
    switch (library) {
        default:
            return LT_UNKNOWN;
        case XBSDBLIB_D3D8:
        case XBSDBLIB_D3D8LTCG:
        case XBSDBLIB_D3DX8:
            return LT_D3D;
        case XBSDBLIB_DSOUND:
        case XBSDBLIB_XACTENG:
            return LT_AUDIO;
        case XBSDBLIB_JVS:
            return LT_JVS;
        case XBSDBLIB_XAPILIB:
            return LT_XAPI;
        case XBSDBLIB_XGRAPHC:
            return LT_GRAPHIC;
        case XBSDBLIB_XONLINE:
        case XBSDBLIB_XONLINEN:
        case XBSDBLIB_XONLINES:
        case XBSDBLIB_XONLINLS:
        case XBSDBLIB_XNET:
        case XBSDBLIB_XNETS:
        case XBSDBLIB_XNETN:
            return LT_NETWORK;
    }
}

static bool XbSDBi_SetLibraryTypeStart(XbSDBiContext* pContext, eLibraryType library_type)
{
    if (!XbSDBiContext_AllowScanLibrary(pContext)) {
        return false;
    }

    // Don't accept request if library type is unknown.
    if (library_type <= LT_UNKNOWN || LT_MAX <= library_type) {
        return false;
    }

    bool ret = false;

    // Accept request if library type is inactive.
    if (!pContext->library_contexts[library_type].is_active) {
        // Then accept the scan request.
        pContext->library_contexts[library_type].is_active = true;
        ret = true;
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type active: %u", library_type);
    }

    return ret;
}

static void XbSDBi_SetLibraryTypeEnd(XbSDBiContext* pContext, eLibraryType library_type)
{
    // If library is active, deny the scan request.
    if (!pContext->library_contexts[library_type].is_active) {
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Attempted to set already inactive library type %u.", library_type);
    }

    pContext->library_contexts[library_type].is_active = false;
    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type inactive: %u", library_type);
}

static memptr_t XbSDBi_section_VirtToHostAddress(XbSDBiContext* pContext, xbaddr virt_addr)
{
    memptr_t host_addr = NULL;
    XbSDBSection* section_filter = pContext->section_input.filters;
    for (unsigned i = 0; i < pContext->section_input.count; i++, section_filter++) {
        // Check if virt_addr match within specific section range, then convert to host address.
        if (section_filter->xb_virt_addr <= virt_addr && virt_addr <= section_filter->xb_virt_addr + section_filter->buffer_size) {
            host_addr = (memptr_t)section_filter->buffer_lower - section_filter->xb_virt_addr + virt_addr;
            break;
        }
    }
    return host_addr;
}

static xbaddr XbSDBi_section_HostToVirtAddress(XbSDBiContext* pContext, memptr_t host_addr)
{
    xbaddr virt_addr = 0;
    XbSDBSection* section_filter = pContext->section_input.filters;
    for (unsigned i = 0; i < pContext->section_input.count; i++, section_filter++) {
        // Check if host_addr match within specific section range, then convert to virtual address.
        if ((memptr_t)section_filter->buffer_lower <= host_addr && host_addr <= (memptr_t)section_filter->buffer_lower + section_filter->buffer_size) {
            virt_addr = (xbaddr)(host_addr - (memptr_t)section_filter->buffer_lower + section_filter->xb_virt_addr);
            break;
        }
    }
    return virt_addr;
}

static bool XbSDBi_LibraryFilterPermitScan(XbSDBiContext* pContext, uint32_t library_flag)
{
    if (pContext->library_filter == 0 || (pContext->library_filter & library_flag) > 0) {
        return true;
    }
    return false;
}

// Check & update if build version is higher than existing library flag.
static void XbSDBi_LibraryFilterUpdateVersionIfGreater(XbSDBLibrary* filters,
                                                       unsigned int count,
                                                       uint32_t library_flags,
                                                       uint16_t wBuildVersion,
                                                       uint16_t QFEVersion)
{
    for (unsigned filter_i = 0; filter_i < count; filter_i++) {
        if (filters[filter_i].flag & library_flags) {
            if (filters[filter_i].build_version < wBuildVersion) {
                filters[filter_i].build_version = wBuildVersion;
                filters[filter_i].qfe_version = QFEVersion;
            }
            else if (filters[filter_i].qfe_version < QFEVersion) {
                filters[filter_i].qfe_version = QFEVersion;
            }
        }
    }
}

// Check & update existing library flag to new library flag.
static void XbSDBi_LibraryFilterUpdateFlagIfExist(XbSDBLibrary* filters,
                                                  unsigned int count,
                                                  uint32_t library_flag_find,
                                                  uint32_t library_flag_set)
{
    for (unsigned filter_i = 0; filter_i < count; filter_i++) {
        if ((filters[filter_i].flag & library_flag_find) == library_flag_find) {
            filters[filter_i].flag = library_flag_set;
            memcpy(filters[filter_i].name, XbSDB_LibraryToString(library_flag_set), 8);
        }
    }
}
