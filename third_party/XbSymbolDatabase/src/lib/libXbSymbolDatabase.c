// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2002 Aaron Robinson <caustik@caustik.com>
// SPDX-FileCopyrightText: 2016 Luke Usher
// SPDX-FileCopyrightText: 2016 PatrickvL
// SPDX-FileCopyrightText: 2017 RadWolfie
// SPDX-FileCopyrightText: 2017 jarupxx
// SPDX-FileCopyrightText: 2018 x1nixmzeng

#define _XBOXKRNL_DEFEXTRN_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h> // for static_assert

#ifdef _MSC_VER
#include <intrin.h>
static inline uint32_t BitScanReverse(uint32_t value)
{
    unsigned long index;
    if (!_BitScanReverse(&index, value)) {
        return 32;
    }
    return index;
}
#elif __GNUC__
static inline uint32_t BitScanReverse(uint32_t value)
{
    if (value == 0) {
        return 32;
    }
    return 31 - __builtin_clz(value);
}
#else
#error Unsupported platform
#endif

// ******************************************************************
// * Xbox Symbol Database
// ******************************************************************

#include "libXbSymbolDatabase.h"
#include "Xbe.h"

// __COUNTER__ is currently suppported for msvc, gcc, and clang
#define SYMBOL_COUNTER_VALUE __COUNTER__

// ******************************************************************
// * Xbox Symbol OOVPA Database
// ******************************************************************

#include "OOVPA_databases.h"

#define PAIRSCANSEC_MAX 4

typedef uint8_t* memptr_t;

typedef struct _OutputHandler {
    xb_output_message verbose_level;
    xb_output_message_t func;
} OutputHandler;

// Library Type is a requirement to prevent another thread
// doing the same scan process.
typedef enum _eLibraryType {
    LT_UNKNOWN = -1,
    LT_KERNEL = 0,
    LT_D3D,
    LT_AUDIO,
    LT_JVS,
    LT_XAPI,
    LT_GRAPHIC,
    LT_NETWORK,
    LT_MAX,
    LT_COUNT = LT_MAX
} eLibraryType;

typedef enum _eScanStage {
    SS_NONE = 0,
    SS_1_MANUAL,
    SS_2_SCAN_LIBS,
} eScanStage;

typedef enum _eRegisterSymbol {
    REGISTER_NO = 0,
    REGISTER_YES,
} eRegisterSymbol;

typedef enum _eFirstPass {
    FIRSTPASS_NO = 0,
    FIRSTPASS_YES,
} eFirstPass;

typedef struct _XbSDBiLibraryContext {
    uint32_t xref_registered;
    bool is_active;
} XbSDBiLibraryContext;

typedef struct _XbSDBiLibrarySession {
    const XbSDBLibrary* pLibrary;
    eLibraryType iLibraryType;
} XbSDBiLibrarySession;

typedef struct _XbSDBiContext {
    bool strict_build_version_limit;
    bool one_time_scan;
    bool scan_first_detect;
    uint32_t library_filter;
    xbaddr xref_database[XREF_COUNT];
    OutputHandler output;
    xb_symbol_register_t register_func;
    XbSDBLibraryHeader library_input;
    XbSDBSectionHeader section_input;
    eScanStage scan_stage;
    XbSDBiLibraryContext library_contexts[LT_COUNT];
} XbSDBiContext;

typedef const struct _PairScanLibSec {
    uint32_t library;
    const char* section[PAIRSCANSEC_MAX];
} PairScanLibSec;

typedef const struct _SymbolDatabaseList {
    PairScanLibSec LibSec;

    OOVPATableList* Symbols;
} SymbolDatabaseList;

typedef bool (*custom_scan_func_t)(XbSDBiContext* pContext,
                                   const XbSDBiLibrarySession* pLibrarySession,
                                   SymbolDatabaseList* pLibraryDB,
                                   const XbSDBSection* pSection);

SymbolDatabaseList SymbolDBList[] = {
    // Support inline functions in .text section
    { XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG, { SEC_TEXT, SEC_D3D, SEC_FLASHROM }, &D3D8_OOVPA },

    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    { XBSDBLIB_D3D8LTCG, { SEC_TEXT, SEC_D3D }, &D3D8LTCG_OOVPA },

    // NOTE: Likely is a D3D Helper library.
    // Jarupxx mention this is not a requirement?
    //{ LIB_D3DX8, { SEC_D3DX }, &_OOVPA },

    // Only used for manual scan purpose as a workaround since both FLASHROM
    // and text section will lead to false detection for non-manual signatures, see comment below.
    { XBSDBLIB_DSOUND, { SEC_DSOUND, SEC_RDATA, SEC_FLASHROM, SEC_TEXT }, &DSound_OOVPA_manual },

    // NOTE: By adding FLASHROM to scan section may will lead false detection.
    // Since some symbols has very short asm codes.
    { XBSDBLIB_DSOUND, { SEC_DSOUND, SEC_RDATA, SEC_FLASHROM }, &DSound_OOVPA },

    // DSOUNDH is just meant to define hot fix, there is no separate section
    //{ XBSDBLIB_DSOUNDH, { SEC_DSOUND }, &DSound_OOVPA },

    // Only used in Chihiro applications
    { XBSDBLIB_JVS, { SEC_TEXT, SEC_XPP, SEC_FLASHROM }, &JVSLIB_OOVPA },

    //
    { XBSDBLIB_XACTENG, { SEC_XACTENG, SEC_FLASHROM }, &XACTENG_OOVPA },

    // test case: Power Drome (Unluckily, it use LTCG version of the library.)
    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    //{ XBSDBLIB_XACTENLT, { SEC_XACTENG }, &XACTENGLT_OOVPA },

    //
    { XBSDBLIB_XAPILIB, { SEC_TEXT, SEC_XPP, SEC_FLASHROM }, &XAPILIB_OOVPA },

    // Support inline functions in .text section
    { XBSDBLIB_XGRAPHC, { SEC_TEXT, SEC_XGRPH, SEC_FLASHROM }, &XGRAPHC_OOVPA },

    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    //{ XBSDBLIB_XGRAPHCL, { SEC_XGRPH }, &XGRAPHCL_OOVPA },

    // Added SEC_TEXT and SEC_XNET just in case.
    // TODO: Do we need to keep SEC_XNET in here?
    // TODO: Need to find out which function is only part of XOnlines.
    // Fun fact, XONLINES are split into 2 header sections.
    { XBSDBLIB_XONLINE | XBSDBLIB_XONLINEN | XBSDBLIB_XONLINES | XBSDBLIB_XONLINLS, { SEC_TEXT, SEC_XONLINE, SEC_XNET, SEC_FLASHROM }, &XONLINE_OOVPA },

    // Added SEC_TEXT just in case.
    // TODO: Need to find out which function is only part of XNets.
    // XNETS only has XNET, might be true.
    // XNETN's test case: Stake
    { XBSDBLIB_XNET | XBSDBLIB_XNETS | XBSDBLIB_XNETN | XBSDBLIB_XONLINE | XBSDBLIB_XONLINEN | XBSDBLIB_XONLINES | XBSDBLIB_XONLINLS, { SEC_TEXT, SEC_XNET, SEC_FLASHROM }, &XNET_OOVPA },
};

// ******************************************************************
// * SymbolDBListCount
// ******************************************************************
const unsigned int SymbolDBListCount = XBSDB_ARRAY_SIZE(SymbolDBList);

const char SectionList[][8] = {
    SEC_TEXT,
    SEC_FLASHROM,
    SEC_RDATA,
    SEC_D3D,
    SEC_D3DX,
    SEC_DSOUND,
    SEC_XACTENG,
    SEC_XID,
    SEC_XPP,
    SEC_XPPDAT,
    SEC_XGRPH,
    SEC_XONLINE,
    SEC_XNET
};

const unsigned int SectionListTotal = XBSDB_ARRAY_SIZE(SectionList);

#if _DEBUG
xb_output_message g_output_verbose_level = XB_OUTPUT_MESSAGE_DEBUG;
#else
xb_output_message g_output_verbose_level = XB_OUTPUT_MESSAGE_INFO;
#endif

// Intended for send the message as-is without formating.
// (To avoid corrupted string when perform a bad coding.
//  Plus certain message need special character without format.)
void output_message(OutputHandler* pOutput, xb_output_message mLevel, const char* message)
{
    // Check if output function is set.
    // Plus if pass minimum verbose level to output.
    if (pOutput->func != NULL && mLevel >= pOutput->verbose_level) {
        pOutput->func(mLevel, message);
    }
}

// Intended to format the message with given extra parameters.
void output_message_format(OutputHandler* pOutput, xb_output_message mLevel, const char* format, ...)
{
    char bufferTemp[2048];

    // Check if output function is set.
    // Plus if pass minimum verbose level to output.
    if (pOutput->func != NULL && mLevel >= pOutput->verbose_level) {
        va_list args;
        va_start(args, format);
        (void)vsprintf(bufferTemp, format, args);
        va_end(args);

        pOutput->func(mLevel, bufferTemp);
    }
}

// ported from Dxbx's XbeExplorer
static xb_xbe_type GetXbeType(const xbe_header* pXbeHeader)
{
    // Detect if the XBE is for Chihiro (Untested!) :
    // This is based on https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L29
    if ((pXbeHeader->dwEntryAddr & 0xf0000000) == 0x40000000) {
        return XB_XBE_TYPE_CHIHIRO;
    }

    // Check for Debug XBE, using high bit of the kernel thunk address :
    // (DO NOT test like https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L33 !)
    if ((pXbeHeader->dwKernelImageThunkAddr & 0x80000000) > 0) {
        return XB_XBE_TYPE_DEBUG;
    }

    // Otherwise, the XBE is a Retail build :
    return XB_XBE_TYPE_RETAIL;
}

static bool XbSDBiContext_AllowSetParameter(XbSDBiContext* pContext)
{
    bool bRet = (pContext->scan_stage == SS_NONE);

    if (!bRet) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Cannot set parameter value after first and during scan call.");
    }

    return bRet;
}

static bool XbSDBiContext_AllowScanLibrary(XbSDBiContext* pContext)
{
    bool bRet = (pContext->scan_stage == SS_2_SCAN_LIBS);

    if (!bRet) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "XbSDBContext_ScanManual must be call first before scan for library's symbols.");
    }

    return bRet;
}

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

#include "internal_functions.h"


// ******************************************************************
// * global API functions
// ******************************************************************

xb_output_message_t g_output_func = NULL;
void XbSDB_SetOutputMessage(xb_output_message_t message_func)
{
    g_output_func = message_func;
}

bool XbSDB_SetOutputVerbosity(xb_output_message verbose_level)
{
    if (verbose_level < XB_OUTPUT_MESSAGE_MAX) {
        g_output_verbose_level = verbose_level;
        return true;
    }
    // Return false only when requested level is invalid.
    return false;
}

const char* XbSDB_LibraryToString(uint32_t library_flag)
{
    switch (library_flag) {
        case XBSDBLIB_D3D8: {
            return LIB_D3D8;
        }
        case XBSDBLIB_D3D8LTCG: {
            return LIB_D3D8LTCG;
        }
        case XBSDBLIB_D3DX8: {
            return LIB_D3DX8;
        }
        case XBSDBLIB_DSOUND: {
            return LIB_DSOUND;
        }
        case XBSDBLIB_JVS: {
            return LIB_JVS;
        }
        case XBSDBLIB_XACTENG: {
            return LIB_XACTENG;
        }
        case XBSDBLIB_XAPILIB: {
            return LIB_XAPILIB;
        }
        case XBSDBLIB_XGRAPHC: {
            return LIB_XGRAPHC;
        }
        case XBSDBLIB_XNET: {
            return LIB_XNET;
        }
        case XBSDBLIB_XNETN: {
            return LIB_XNETN;
        }
        case XBSDBLIB_XNETS: {
            return LIB_XNETS;
        }
        case XBSDBLIB_XONLINE: {
            return LIB_XONLINE;
        }
        case XBSDBLIB_XONLINEN: {
            return LIB_XONLINEN;
        }
        case XBSDBLIB_XONLINES: {
            return LIB_XONLINES;
        }
        case XBSDBLIB_XONLINLS: {
            return LIB_XONLINLS;
        }
        default: {
            return LIB_UNKNOWN;
        }
    }
}

static const char* const param_type_str[] = {
#define PARAM_TYPE__0(type)  #type,
#define PARAM_TYPE_64(type)  #type,
#define PARAM_TYPE_32(type)  #type,
#define PARAM_TYPE_16_(type) #type,
#define PARAM_TYPE__8_(type) #type,
#include <libParamTypes.h>
#undef PARAM_TYPE__0
#undef PARAM_TYPE_64
#undef PARAM_TYPE_32
#undef PARAM_TYPE_16_
#undef PARAM_TYPE__8_
};

const char* XbSDB_ParamToString(uint32_t param_type)
{
    if (param_type >= param_max) {
        return param_type_str[param_unk];
    }

    return param_type_str[param_type];
}

static const char* const call_type_str[] = {
#define CALL_(type) #type,
#include <libCallTypes.h>
#undef CALL_
};

const char* XbSDB_CallingConventionToString(uint32_t call_type)
{
    if (call_type >= call_max) {
        return call_type_str[call_unknown];
    }

    return call_type_str[call_type];
}

const char* xref_str[] = {
#define XREF_SYMBOL(e) #e,
#include "xref/d3d8.def"
#include "xref/d3d8ltcg.def"
#include "xref/dsound.def"
#include "xref/jvs.def"
#include "xref/xacteng.def"
#include "xref/xapilib.def"
#include "xref/xgraphic.def"
#include "xref/xnet.def"
#include "xref/xonline.def"
#undef XREF_SYMBOL
};

const char* XbSDB_SymbolReferenceToString(uint32_t xref_index)
{
    if (xref_index <= XREF_KT_COUNT || XREF_COUNT <= xref_index) {
        return NULL;
    }
    return xref_str[XREF_API_TO_PUBLIC_INDEX(xref_index)];
}

// NOTE: Library string must return only one specific flag, cannot make a mix combo flags.
//       Otherwise, internal scan and XbSDB_LibraryToString will not function correctly.
uint32_t XbSDB_LibraryToFlag(const char* library_name)
{
    if (strncmp(library_name, LIB_D3D8, 8) == 0) {
        return XBSDBLIB_D3D8;
    }
    if (strncmp(library_name, LIB_D3D8LTCG, 8) == 0) {
        return XBSDBLIB_D3D8LTCG;
    }
    if (strncmp(library_name, LIB_D3DX8, 8) == 0) {
        return XBSDBLIB_D3DX8;
    }
    if (strncmp(library_name, LIB_DSOUND, 8) == 0) {
        return XBSDBLIB_DSOUND;
    }
    if (strncmp(library_name, LIB_JVS, 8) == 0) {
        return XBSDBLIB_JVS;
    }
    if (strncmp(library_name, LIB_XACTENG, 8) == 0) {
        return XBSDBLIB_XACTENG;
    }
    if (strncmp(library_name, LIB_XAPILIB, 8) == 0) {
        return XBSDBLIB_XAPILIB;
    }
    if (strncmp(library_name, LIB_XGRAPHC, 8) == 0) {
        return XBSDBLIB_XGRAPHC;
    }
    if (strncmp(library_name, LIB_XNET, 8) == 0) {
        return XBSDBLIB_XNET;
    }
    if (strncmp(library_name, LIB_XNETN, 8) == 0) {
        return XBSDBLIB_XNETN;
    }
    if (strncmp(library_name, LIB_XNETS, 8) == 0) {
        return XBSDBLIB_XNETS;
    }
    if (strncmp(library_name, LIB_XONLINE, 8) == 0) {
        return XBSDBLIB_XONLINE;
    }
    if (strncmp(library_name, LIB_XONLINEN, 8) == 0) {
        return XBSDBLIB_XONLINEN;
    }
    if (strncmp(library_name, LIB_XONLINES, 8) == 0) {
        return XBSDBLIB_XONLINES;
    }
    if (strncmp(library_name, LIB_XONLINLS, 8) == 0) {
        return XBSDBLIB_XONLINLS;
    }
    return 0;
}

uint32_t XbSDB_GetLibraryDependencies(uint32_t library_flag, XbSDBLibraryHeader library_filters)
{
    uint32_t flag_dependencies;
    switch (library_flag) {
        default:
            return 0;
        case XBSDBLIB_D3DX8:
            flag_dependencies = XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG;
            break;
        case XBSDBLIB_XACTENG:
            return XBSDBLIB_DSOUND;
#if 0 // Disabled since internal scan will scan XNET(N|S) library anyway.
        case XBSDBLIB_XONLINE:
        case XBSDBLIB_XONLINEN:
        case XBSDBLIB_XONLINES:
        case XBSDBLIB_XONLINLS:
            flag_dependencies = XBSDBLIB_XNET | XBSDBLIB_XNETN | XBSDBLIB_XNETS;
            break;
#endif
    }

    // TODO: Should we go with this method or convert into a function for separate dependency process?
    uint32_t ret_dependencies = 0;
    for (unsigned i = 0; i < library_filters.count; i++) {
        if (library_filters.filters[i].flag & flag_dependencies) {
            ret_dependencies |= library_filters.filters[i].flag;
        }
    }
    // If library filters were given, then return any dependencies that were found.
    if (library_filters.count) {
        return ret_dependencies;
    }
    // If not, then return whole dependency filters.
    return flag_dependencies;
}

uint32_t XbSDBContext_GetLibraryDependencies(XbSDBContextHandle pHandle, uint32_t library_flag)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;
    // Forward call to XbSDB_GetLibraryDependencies.
    return XbSDB_GetLibraryDependencies(library_flag, pContext->library_input);
}

// TODO: Expose to third-party?
static bool XbSDBi_HasDSoundSection(const void* xb_header_addr)
{
    const xbe_header* pXbeHeader = xb_header_addr;
    memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    xbe_section_header* pSectionHeaders = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    const char* SectionName;
    bool has_dsound = false;

    // Verify if title do contain DirectSound library section.
    for (unsigned int v = 0; v < pXbeHeader->dwSections; v++) {
        SectionName = (const char*)(xb_start_addr + pSectionHeaders[v].SectionNameAddr);

        if (strncmp(SectionName, LIB_DSOUND, 8) == 0) {
            has_dsound = true;
            break;
        }
    }

    return has_dsound;
}

uint32_t XbSDB_GenerateLibraryFilter(const void* xb_header_addr, XbSDBLibraryHeader* library_header)
{
    uint32_t library_flag;
    const xbe_header* pXbeHeader = xb_header_addr;
    const memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    const xbe_library_version* xb_library_versions = (xbe_library_version*)(xb_start_addr + pXbeHeader->pLibraryVersionsAddr);
    unsigned int library_total = pXbeHeader->dwLibraryVersions;
    unsigned int count = 0;
    uint16_t build_version = 0;
    bool has_dsound_library = false;
    bool has_d3d8__ltcg_library = false;
    xb_xbe_type XbeType = GetXbeType(xb_header_addr);
    OutputHandler output = {
        .func = g_output_func,
        .verbose_level = g_output_verbose_level
    };

    // Only process XDK applications.
    if (pXbeHeader->pLibraryVersionsAddr != 0) {

        for (unsigned library_index = 0; library_index < library_total; library_index++) {

            library_flag = XbSDB_LibraryToFlag(xb_library_versions[library_index].szName);

            // Keep the highest build version for manual checklist.
            if (build_version < xb_library_versions[library_index].wBuildVersion) {
                build_version = xb_library_versions[library_index].wBuildVersion;
            }

            // If library is unknown to the database, skip it.
            if (library_flag == 0) {
                continue;
            }

            // If found DSOUND library, then skip the manual check.
            if (library_flag == XBSDBLIB_DSOUND) {
                if (!has_dsound_library) {
                    has_dsound_library = true;
                }
            }

            // If D3D8 and D3D8LTCG library details may had bundled by accident, then do manual fix below.
            // See details from https://github.com/Cxbx-Reloaded/XbSymbolDatabase/issues/178
            if (library_flag & (XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG)) {
                if (has_d3d8__ltcg_library) {
                    if (library_header != NULL) {
                        if (library_flag == XBSDBLIB_D3D8LTCG) {
                            // Force set to D3D8LTCG if D3D8 flag was found first.
                            XbSDBi_LibraryFilterUpdateFlagIfExist(library_header->filters,
                                                                  count,
                                                                  XBSDBLIB_D3D8,
                                                                  XBSDBLIB_D3D8LTCG);
                        }
                        // Update duplicated library detail
                        XbSDBi_LibraryFilterUpdateVersionIfGreater(library_header->filters,
                                                                   count,
                                                                   XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG,
                                                                   xb_library_versions[library_index].wBuildVersion,
                                                                   xb_library_versions[library_index].wFlags.QFEVersion);
                    }

                    // Skip duplicate library finding.
                    continue;
                }
                else if (!has_d3d8__ltcg_library) {
                    has_d3d8__ltcg_library = true;
                }
            }

            // Append the information to the array.
            if (library_header != NULL) {

                library_header->filters[count].flag = library_flag;
                library_header->filters[count].build_version = xb_library_versions[library_index].wBuildVersion;
                library_header->filters[count].qfe_version = xb_library_versions[library_index].wFlags.QFEVersion;
                memcpy(library_header->filters[count].name, XbSDB_LibraryToString(library_flag), 8);

                if ((library_flag & (XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG)) > 0) {

                    // Functions in this library were updated by June 2003 XDK (5558) with Integrated Hotfixes,
                    // However August 2003 XDK (5659) still uses the old function.
                    // Please use updated 5788 instead.
                    if (xb_library_versions[library_index].wBuildVersion >= 5558 &&
                        xb_library_versions[library_index].wBuildVersion <= 5659 &&
                        xb_library_versions[library_index].wFlags.QFEVersion > 1) {

                        output_message_format(&output, XB_OUTPUT_MESSAGE_WARN,
                                              "D3D8 version 1.0.%d.%d Title Detected: This game uses an alias version 1.0.5788",
                                              xb_library_versions[library_index].wBuildVersion,
                                              xb_library_versions[library_index].wFlags.QFEVersion);

                        library_header->filters[count].build_version = 5788;
                    }
                }
            }
            count++;
        }

        // Manual check if DSOUND section do exist.
        if (!has_dsound_library) {
            if (XbSDBi_HasDSoundSection(xb_header_addr)) {
                if (library_header != NULL) {
                    library_header->filters[count].flag = XBSDBLIB_DSOUND;
                    library_header->filters[count].build_version = build_version;
                    library_header->filters[count].qfe_version = 0;
                    (void)strncpy(library_header->filters[count].name, LIB_DSOUND, 8);
                }
                count++;
            }
        }

        // Manual check if Xbe type is debug or Chihiro
        if (XbeType != XB_XBE_TYPE_RETAIL) {
            if (library_header != NULL) {
                library_header->filters[count].flag = XBSDBLIB_JVS;
                library_header->filters[count].build_version = build_version;
                library_header->filters[count].qfe_version = 0;
                (void)strncpy(library_header->filters[count].name, LIB_JVS, 8);
            }
            count++;
        }
    }

    return count;
}

uint32_t XbSDB_GenerateSectionFilter(const void* xb_header_addr, XbSDBSectionHeader* section_header, bool is_raw)
{
    const xbe_header* pXbeHeader = xb_header_addr;
    const memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    const xbe_section_header* xb_section_headers = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    const xbe_section_header* sh_index;
    XbSDBSection* sv_index;
    unsigned int section_total = pXbeHeader->dwSections;
    unsigned int count = 0;
    const char* SectionName;
    uint32_t kernel_thunk_addr;

    if (pXbeHeader->pSectionHeadersAddr != 0) {

        kernel_thunk_addr = XbSDB_GetKernelThunkAddress(xb_header_addr);

        for (unsigned section_index = 0; section_index < section_total; section_index++) {

            SectionName = (const char*)(xb_start_addr + xb_section_headers[section_index].SectionNameAddr);
            sh_index = &xb_section_headers[section_index];

            // Verify if section is preload. If not, then skip it.
            // Intend for optimization usage and avoid false positive detection.
            if ((sh_index->dwFlags_value & XBE_SECTION_HEADER_FLAGS_PRELOAD) == 0) {
                continue;
            }

            bool is_detected = false;

            for (unsigned int SectionList_index = 0; SectionList_index < SectionListTotal; SectionList_index++) {

                // Once match is found, increase the count plus append to section vars.
                if (strncmp(SectionName, SectionList[SectionList_index], 8) == 0) {
                    is_detected = true;
                    break;
                }
            }

            // If section is not on the filter list, check if there is kernel thunk table within section to enforce include it.
            if (is_detected == false) {
                if (kernel_thunk_addr >= sh_index->dwVirtualAddr && kernel_thunk_addr < (sh_index->dwVirtualAddr + sh_index->dwSizeofRaw)) {
                    // Once found within range, then enforce add section to the filter.
                    is_detected = true;
                }
            }

            // If detected, then register into filter list.
            if (is_detected == true) {
                if (section_header != NULL) {
                    sv_index = &section_header->filters[count];

                    memcpy(sv_index->name, SectionName, 8);
                    sv_index->xb_virt_addr = sh_index->dwVirtualAddr;
                    sv_index->buffer_size = sh_index->dwSizeofRaw;

                    if (is_raw) {
                        sv_index->buffer_lower = (memptr_t)xb_header_addr + sh_index->dwRawAddr;
                    }
                    else {
                        sv_index->buffer_lower = xb_start_addr + sh_index->dwVirtualAddr;
                    }
                }

                count++;
            }
        }
    }

    return count;
}

xbaddr XbSDB_GetKernelThunkAddress(const void* xb_header_addr)
{
    xb_xbe_type xbe_type = GetXbeType(xb_header_addr);

    uint32_t kernel_thunk_addr = *(uint32_t*)((uint8_t*)xb_header_addr + 0x0158);
    kernel_thunk_addr ^= XB_XOR_KT[xbe_type];

    return kernel_thunk_addr;
}

#include "internal_db_version.h"
unsigned int XbSDB_LibraryVersion()
{
    // Calculate this just once
    static unsigned int CalculatedHash = 0;
    if (CalculatedHash == 0) {
        CalculatedHash = HashSymbolDataArray(SymbolDBList, SymbolDBListCount);
    }
    return CalculatedHash;
}

#include "internal_tests.h"
unsigned int XbSDB_TestOOVPAs()
{
    XbSDBiVerifyContext context = { 0 };
    context.output.func = g_output_func;
    context.output.verbose_level = g_output_verbose_level;
    return XbSDBiVerifyContext_VerifyDatabaseList(&context);
}

// ******************************************************************
// * XbSDBContextHandle manager functions
// ******************************************************************

bool XbSDB_CreateContext(XbSDBContextHandle* ppHandle,
                         xb_symbol_register_t register_func,
                         XbSDBLibraryHeader library_input,
                         XbSDBSectionHeader section_input,
                         xbaddr kernel_thunk)
{
    if (register_func == NULL) {
        goto EmptyCleanup;
    }

    // Verify if Microsoft XDK library do exist
    if (library_input.count == 0 || library_input.filters == NULL) {
        goto EmptyCleanup;
    }

    // Verify if we have sections exist to process.
    if (section_input.count == 0 || section_input.filters == NULL) {
        goto EmptyCleanup;
    }

    *ppHandle = calloc(1, sizeof(XbSDBiContext));

    if (*ppHandle == NULL) {
        goto EmptyCleanup;
    }

    XbSDBiContext* pContext = (XbSDBiContext*)*ppHandle;

    pContext->scan_stage = SS_NONE;

    pContext->register_func = register_func;

    // Initialize default values to context handler.
    pContext->strict_build_version_limit = true;
    pContext->one_time_scan = true;
    pContext->scan_first_detect = false;
    pContext->output.verbose_level = g_output_verbose_level;
    pContext->output.func = g_output_func;
    pContext->library_filter = 0;

    // Copy pointers and values to context handler.
    pContext->library_input.count = library_input.count;
    pContext->library_input.filters = malloc(sizeof(XbSDBLibrary) * library_input.count);
    if (pContext->library_input.filters == NULL) {
        goto ContextCleanup;
    }

    pContext->section_input.count = section_input.count;
    pContext->section_input.filters = malloc(sizeof(XbSDBSection) * section_input.count);
    if (pContext->section_input.filters == NULL) {
        goto LibraryCleanup;
    }

    memcpy(pContext->library_input.filters, library_input.filters, sizeof(XbSDBLibrary) * library_input.count);
    memcpy(pContext->section_input.filters, section_input.filters, sizeof(XbSDBSection) * section_input.count);

    // Mark all Xrefs initially as undetermined
    memset((void*)pContext->xref_database, XREF_ADDR_UNDETERMINED, sizeof(pContext->xref_database));

    // Find specific section contains the kernel thunk.
    bool kt_found = false;
    for (unsigned int i = 0; i < pContext->section_input.count; i++) {
        XbSDBSection* section = pContext->section_input.filters + i;
        uintptr_t virt_start_relative = (uintptr_t)section->buffer_lower - section->xb_virt_addr;

        // Once found, start register the kernel xreferences.
        if (kernel_thunk >= section->xb_virt_addr && kernel_thunk < (section->xb_virt_addr + section->buffer_size)) {
            uint32_t* kt = (uint32_t*)(virt_start_relative + kernel_thunk);
            xbaddr kt_addr = kernel_thunk;
            kt_found = true;
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG,
                                  "Kernel thunk is found in %.8s section",
                                  section->name);

            while (*kt > 0) {
                unsigned int index = *kt & 0x7FFFFFFF;
                // Check if the index is within range, then add to the xreference database.
                if (index > 0 && index < XREF_KT_COUNT) {
                    XbSDBi_SetXRefDatabase(pContext, LT_KERNEL, index, kt_addr);
                }
                else {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                          "Unable to register kernel thunk: index=%u; vaddr=0x%08x",
                                          index, kt_addr);
                }
                kt++;
                kt_addr += 4;
            }
            break;
        }
    }

    if (!kt_found) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                       "Kernel thunk is not found from sections input, certain symbol's OOVPAs may not be detected.");
    }

    // clang-format off
    // Request a few fundamental XRefs to be derived instead of checked
    // D3D
    pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] = XREF_ADDR_DERIVE;                     //In use
    pContext->xref_database[XREF_D3D_g_Stream] = XREF_ADDR_DERIVE;                             //In use
    pContext->xref_database[XREF_D3D_g_Stream_i_pVertexBuffer] = XREF_ADDR_DERIVE;             //In use
    pContext->xref_database[XREF_D3DDevice__m_PixelShader_OFFSET] = XREF_ADDR_DERIVE;          //
    pContext->xref_database[XREF_D3DDevice__m_Textures_OFFSET] = XREF_ADDR_DERIVE;             //
    pContext->xref_database[XREF_D3DDevice__m_Palettes_OFFSET] = XREF_ADDR_DERIVE;             //
    pContext->xref_database[XREF_D3DDevice__m_RenderTarget_OFFSET] = XREF_ADDR_DERIVE;         //
    pContext->xref_database[XREF_D3DDevice__m_DepthStencil_OFFSET] = XREF_ADDR_DERIVE;         //
    pContext->xref_database[XREF_D3DDevice__m_VerticalBlankEvent_OFFSET] = XREF_ADDR_DERIVE;   //In use
#if 0                                                                                          //
    pContext->xref_database[XREF_D3DDevice__m_SwapCallback_OFFSET] = XREF_ADDR_UNDETERMINED;   //In use // Manual check only.
    pContext->xref_database[XREF_D3DDevice__m_VBlankCallback_OFFSET] = XREF_ADDR_UNDETERMINED; //In use // Manual check only.
#endif                                                                                         //
    pContext->xref_database[XREF_D3DDevice__m_VertexShader_OFFSET] = XREF_ADDR_DERIVE;         //In use
    // JVS                                                                                     //
    pContext->xref_database[XREF_JVS_g_pPINSA] = XREF_ADDR_DERIVE;                             //In use
    pContext->xref_database[XREF_JVS_g_pPINSB] = XREF_ADDR_DERIVE;                             //In use
    // XAPILIB                                                                                 //
    pContext->xref_database[XREF_g_XapiCurrentTopLevelFilter] = XREF_ADDR_DERIVE;              //In use
    pContext->xref_database[XREF_g_DeviceType_Gamepad] = XREF_ADDR_DERIVE;                     //In use
    pContext->xref_database[XREF_g_DeviceType_Keyboard] = XREF_ADDR_DERIVE;                    //In use
    pContext->xref_database[XREF_g_DeviceType_IRDongle] = XREF_ADDR_DERIVE;                    //In use
    pContext->xref_database[XREF_g_DeviceTypeInfoTableBegin] = XREF_ADDR_DERIVE;               //In use
    pContext->xref_database[XREF_g_DeviceTypeInfoTableEnd] = XREF_ADDR_DERIVE;                 //In use
    pContext->xref_database[XREF_g_XapiAltLett_MU] = XREF_ADDR_DERIVE;                         //In use
    pContext->xref_database[XREF_g_XapiMountedMUs] = XREF_ADDR_DERIVE;                         //In use
    pContext->xref_database[XREF_XapiCurrentFiber_OFFSET] = XREF_ADDR_DERIVE;                  //In use
    pContext->xref_database[XREF_XapiLastErrorCode_OFFSET] = XREF_ADDR_DERIVE;                 //In use
    pContext->xref_database[XREF_XapiThreadFiberData_OFFSET] = XREF_ADDR_DERIVE;               //In use
    pContext->xref_database[XREF__tls_array] = XREF_ADDR_DERIVE;                               //In use
    pContext->xref_database[XREF__tls_index] = XREF_ADDR_DERIVE;                               //In use
    pContext->xref_database[XREF_XapiThreadNotifyRoutineList] = XREF_ADDR_DERIVE;              //In use
    pContext->xref_database[XREF_XGetSectionSize] = XREF_ADDR_DERIVE;                          //In use
    // clang-format on

    // Mark all library contexts as zero-initialized for scan activity.
    memset(pContext->library_contexts, 0, sizeof(pContext->library_contexts));

    return true;

    // Failure cleanup crew handle
    //FullCleanup:

    //SectionCleanup:
    //free(pContext->section_input.filters);

LibraryCleanup:
    free(pContext->library_input.filters);

ContextCleanup:
    free(*ppHandle);

EmptyCleanup:
    *ppHandle = NULL;
    return false;
}

void XbSDBContext_Release(XbSDBContextHandle pHandle)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    for (unsigned int i = 0; i < LT_COUNT; i++) {
        if (pContext->library_contexts[i].is_active) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type is currently active: %u", i);
        }
    }

    free(pHandle);
}


// ******************************************************************
// * Context API functions
// ******************************************************************

void XbSDBContext_SetBypassBuildVersionLimit(XbSDBContextHandle pHandle, bool bypass_limit)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (XbSDBiContext_AllowSetParameter(pContext)) {
        pContext->strict_build_version_limit = !bypass_limit;
    }
}

void XbSDBContext_SetContinuousSigScan(XbSDBContextHandle pHandle, bool enable)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (XbSDBiContext_AllowSetParameter(pContext)) {
        pContext->one_time_scan = !enable;
    }
}

void XbSDBContext_SetFirstDetectAddressOnly(XbSDBContextHandle pHandle, bool enable)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (XbSDBiContext_AllowSetParameter(pContext)) {
        pContext->scan_first_detect = enable;
    }
}

bool XbSDBContext_RegisterLibrary(XbSDBContextHandle pHandle, uint32_t library_filter)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (!XbSDBiContext_AllowSetParameter(pContext)) {
        return false;
    }

    // Check to make sure all flags are acceptable before set.
    if ((library_filter & ~XBSDBLIB_ALL) > 0) {
        return false;
    }

    pContext->library_filter = library_filter;
    return true;
}

#include "manual_custom.h"
void XbSDBContext_ScanManual(XbSDBContextHandle pHandle)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (pContext->scan_stage >= SS_1_MANUAL) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Manual rescan request is skip.");
        return;
    }
    pContext->scan_stage = SS_1_MANUAL;

    for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {

        const XbSDBLibrary* pLibrary = pContext->library_input.filters + lv;
        eLibraryType i_LibraryType = XbSDBi_GetLibraryType(pLibrary->flag);

        if (i_LibraryType <= LT_UNKNOWN || LT_MAX <= i_LibraryType) {
            continue;
        }

        XbSDBiLibrarySession libSession = {
            .pLibrary = pLibrary,
            .iLibraryType = i_LibraryType
        };

        if ((pLibrary->flag & (XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG)) > 0) {
            // TODO: Do we need to check twice?
            // Perform check twice, since sections can be in different order.
            for (unsigned int loop = 0; loop < 2; loop++) {
                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                // By doing this method will reduce false detection dramatically. If it had happened before.
                if (!manual_scan_library_custom(pContext, manual_scan_section_dx8, &libSession)) {
                    continue;
                }
                break;
            }
        }
        else if ((pLibrary->flag & XBSDBLIB_DSOUND) > 0) {
            // Perform check twice, since sections can be in different order.
            for (unsigned int loop = 0; loop < 2; loop++) {
                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                // By doing this method will reduce false detection dramatically. If it had happened before.
                if (!manual_scan_library_custom(pContext, manual_scan_section_dsound, &libSession)) {
                    continue;
                }
                break;
            }
        }
        else if ((pLibrary->flag & XBSDBLIB_XAPILIB) > 0) {
            manual_scan_library_custom(pContext, manual_scan_section_xapilib, &libSession);
        }
    }

    pContext->scan_stage = SS_2_SCAN_LIBS;
}

unsigned int XbSDBContext_ScanLibrary(XbSDBContextHandle pHandle,
                                      const XbSDBLibrary* pLibrary,
                                      bool xref_first_pass)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;
    eLibraryType iLibraryType = XbSDBi_GetLibraryType(pLibrary->flag);

    if (iLibraryType <= LT_UNKNOWN || LT_MAX <= iLibraryType) {
        return 0;
    }

    XbSDBiLibrarySession librarySession = {
        .pLibrary = pLibrary,
        .iLibraryType = iLibraryType
    };

    unsigned int xref_count = pContext->library_contexts[iLibraryType].xref_registered;

    if (!XbSDBiContext_AllowScanLibrary(pContext)) {
        return 0;
    }

    // If library type is active, do nothing.
    if (!XbSDBi_SetLibraryTypeStart(pContext, iLibraryType)) {
        return 0;
    }

    SymbolDatabaseList* pSymbolDB;
    unsigned db_i = 0;
    while ((pSymbolDB = XbSDBi_FindLibraryDB(pLibrary->flag, &db_i))) {
        db_i++;
        for (unsigned int s = 0; s < pContext->section_input.count; s++) {

            // Initialize a matching specific section is currently pair with library in order to scan specific section only.
            // By doing this method will reduce false detection dramatically. If it had happened before.
            for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                if (pSymbolDB->LibSec.section[d3] != NULL &&
                    strncmp(pContext->section_input.filters[s].name, pSymbolDB->LibSec.section[d3], 8) == 0) {

                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section",
                                          pLibrary->name, pSymbolDB->LibSec.section[d3]);

                    XbSDBi_OOVPATableList_scan(pContext,
                                               &librarySession,
                                               pSymbolDB->Symbols,
                                               pContext->section_input.filters + s,
                                               xref_first_pass);
                    break;
                }
            }

            // NOTE: Do not use break since database entry can have multiple same library entries even doesn't have 2+ bit flags.
            // Affected case: DSound's manual scan required more sections.
#if 0
            // Use the break if there are 2+ bit flags set such as include LTCG flag in std flag's oovpa database like D3D8.
            if ((SymbolDBList[d2].LibSec.library & ~pLibrary->flag) == 0) {
                break;
            }
#endif
        }
    }

    xref_count = pContext->library_contexts[iLibraryType].xref_registered - xref_count;

    XbSDBi_SetLibraryTypeEnd(pContext, iLibraryType);

    return xref_count;
}

void XbSDBContext_ScanAllLibraryFilter(XbSDBContextHandle pHandle)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (!XbSDBiContext_AllowScanLibrary(pContext)) {
        return;
    }

    // Library input should not be above 4 * 8 (32) total.
    if (pContext->library_input.count > sizeof(uint32_t) * 8) {
        return;
    }

    uint32_t library_scan = 0;
    uint32_t library_completion = 0;
    bool not_first_pass[sizeof(uint32_t) * 8] = { false }; // Set to invert true for search speed optimization
    uint32_t library_dependency[sizeof(uint32_t) * 8] = { 0 };
    // Get Library's dependency flag(s)
    for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {
        const XbSDBLibrary* library = pContext->library_input.filters + lv;
        if (XbSDBi_LibraryFilterPermitScan(pContext, library->flag)) {
            library_dependency[lv] = XbSDBContext_GetLibraryDependencies(pHandle, library->flag);
            library_scan |= library->flag;
        }
    }

    // TODO: Update this loop for dependency check up.
    // Repeat process until all libraries has been scanned.
    do {
        for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {
            const XbSDBLibrary* library = pContext->library_input.filters + lv;

            // Keep scanning active library until it is done or skipped.
            do {
                // Temporary placeholder until v2.0 API's section scan function is ready or may be permanent in here.
                // Skip specific library if third-party set to specific library.
                if (!XbSDBi_LibraryFilterPermitScan(pContext, library->flag)) {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Skipping %.8s (%hu) scan.", library->name, library->build_version);
                }
                else {
                    // Check if we already completed library scan first.
                    if (XbSDB_CheckDependencyCompletion(library_completion, library->flag)) {
                        // Skip if already been scanned.
                        break;
                    }

                    // Check if any dependency is set and if they are completed
                    if (library_dependency[lv] && !XbSDB_CheckDependencyCompletion(library_completion, library_dependency[lv])) {
                        // Skip if any dependency library isn't done yet.
                        break;
                    }
                    // Start library scan against symbol database we want to search for address of symbols and xreferences.
                    unsigned counter = XbSDBContext_ScanLibrary(pHandle, library, !not_first_pass[lv]);

                    // If no additional symbols found, then set as scan completed.
                    if (counter == 0) {
                        XbSDB_SetLibraryCompletion(library_completion, library->flag);
                    }
                    // Once first pass is done, multiple passes may will occur for any xref dependency symbols haven't been found.
                    if (!not_first_pass[lv]) {
                        not_first_pass[lv] = true;
                    }
                }
            } while (true);
        }

    } while (!XbSDB_CheckDependencyCompletion(library_completion, library_scan));
}

// Does individual registration of derived XRef's that are useful but not yet registered.
// Called after entire scan.
void XbSDBContext_RegisterXRefs(XbSDBContextHandle pHandle)
{
    XbSDBiContext* pContext = (XbSDBiContext*)pHandle;

    if (pContext->register_func == NULL) {
        return;
    }

    // Any symbols that are not registered, check into below function's library calls.
    // Then add missing symbol(s) to appropriate library's function.
    manual_register_symbols(pContext);
}


// ******************************************************************
// * global API functions (required to be at end of the file)
// ******************************************************************

// Aka the basic example to handle the scan process.
bool XbSDB_Scan(const void* xb_header_addr,
                xb_symbol_register_t register_func,
                bool is_raw)
{
    bool bCheckJVS = false;

    XbSDBContextHandle pHandle;
    XbSDBiContext* iContext;
    XbSDBLibraryHeader library_input = { 0 };
    XbSDBSectionHeader section_input = { 0 };

    // Step 1, let's get the total sum of array to allocate library input.
    library_input.count = XbSDB_GenerateLibraryFilter(xb_header_addr, NULL);
    // If total sum is zero, then the input is invalid.
    if (library_input.count == 0) {
        return false;
    }
    // Then allocate the necessary memory requirement to obtain the information.
    library_input.filters = malloc(sizeof(XbSDBLibrary) * library_input.count);
    // Verify if memory has been allocated.
    if (library_input.filters == NULL) {
        return false;
    }
    // Finally, obtain the information for internal scan process.
    (void)XbSDB_GenerateLibraryFilter(xb_header_addr, &library_input);

    // Step 2, let's get the total sum of array to allocate section input.
    section_input.count = XbSDB_GenerateSectionFilter(xb_header_addr, NULL, is_raw);
    // If total sum is zero, then the input is invalid.
    if (section_input.count == 0) {
        goto LibraryCleanup;
    }
    // Then allocate the necessary memory requirement to obtain the information.
    section_input.filters = malloc(sizeof(XbSDBSection) * section_input.count);
    // Verify if memory has been allocated.
    if (section_input.filters == NULL) {
        goto LibraryCleanup;
    }
    // Finally, obtain the information for internal scan process.
    (void)XbSDB_GenerateSectionFilter(xb_header_addr, &section_input, is_raw);

    xb_xbe_type xbe_type = GetXbeType(xb_header_addr);

    uint32_t kernel_thunk_addr = XbSDB_GetKernelThunkAddress(xb_header_addr);

    // Step 3, initialize context handle to pre-allocate the requirement.
    // However, calling global functions are recommended first for any customization.
    if (!XbSDB_CreateContext(&pHandle, register_func, library_input, section_input, kernel_thunk_addr)) {
        goto FullCleanup;
    }
    // After initialize, we do not need to keep the allocated filter arrays in memory.
    free(section_input.filters);
    free(library_input.filters);

    iContext = (XbSDBiContext*)pHandle;

    output_message_format(&iContext->output, XB_OUTPUT_MESSAGE_DEBUG, "xbe type is %s", xbe_type_str[xbe_type]);

    // Step 4, perform manual scan requirement to collect the necessary requirement
    // before perform general scan.
    XbSDBContext_ScanManual(pHandle);

    // Step 5, do a full scan process.
    XbSDBContext_ScanAllLibraryFilter(pHandle);

    // Step 6, register any xrefs (which doesn't have its own OOVPA)
    XbSDBContext_RegisterXRefs(pHandle);

    // Finally, after all the scan process is done, release the context handler.
    XbSDBContext_Release(pHandle);

    return true;

// Failure cleanup crew handle
FullCleanup:

#if 0
SectionCleanup:
#endif
    free(section_input.filters);

LibraryCleanup:
    free(library_input.filters);

    return false;
}

// Require to be at end of various functions may use manual register calls in order to count properly.
unsigned XbSDB_GetTotalSymbols(uint32_t library_filter)
{
    unsigned db_i = 0, total = SYMBOL_COUNTER_VALUE;
    SymbolDatabaseList* pLibraryDB;
    while ((pLibraryDB = XbSDBi_FindLibraryDB(library_filter, &db_i))) {
        db_i++;
        total += pLibraryDB->Symbols->Count;
    }
    return total;
}
