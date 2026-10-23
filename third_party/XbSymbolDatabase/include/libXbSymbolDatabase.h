// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2002 Aaron Robinson <caustik@caustik.com>
// SPDX-FileCopyrightText: 2016-2017 PatrickvL
// SPDX-FileCopyrightText: 2017-2018 Luke Usher
// SPDX-FileCopyrightText: 2018-2019 RadWolfie

#pragma once

#include <stdlib.h> // for size_t
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************************************
// * Library strings
// ******************************************************************
// clang-format off
#define LIB_UNKNOWN  "UNKNOWN"
// clang-format on
// Group of sections since most libraries are compiled inside the
// section(s) below.
#define SEC_TEXT     ".text"
#define SEC_FLASHROM "FLASHROM"
// DSOUND has a vtable store in .rdata section.
// clang-format off
#define SEC_RDATA    ".rdata"
// clang-format on
// Individual library (yet do include group sections above)
#define LIB_D3D8     "D3D8"
#define SEC_D3D      "D3D"
#define LIB_D3D8LTCG "D3D8LTCG"
#define LIB_D3DX8    "D3DX8"
#define SEC_D3DX     "D3DX"
#define LIB_DSOUND   "DSOUND"
#define SEC_DSOUND   LIB_DSOUND
#define LIB_JVS      "JVS"
#define LIB_XACTENG  "XACTENG"
#define SEC_XACTENG  LIB_XACTENG
#define LIB_XAPILIB  "XAPILIB"
#define SEC_XID      ".XID"
#define SEC_XPP      "XPP"
#define SEC_XPPDAT   ".XPP&Dat"
#define LIB_XGRAPHC  "XGRAPHC"
#define SEC_XGRPH    "XGRPH"
#define LIB_XNET     "XNET"
#define SEC_XNET     LIB_XNET
#define LIB_XNETN    "XNETN"
#define LIB_XNETS    "XNETS"
#define LIB_XONLINE  "XONLINE"
#define SEC_XONLINE  LIB_XONLINE
#define LIB_XONLINEN "XONLINEN"
#define LIB_XONLINES "XONLINES"
#define LIB_XONLINLS "XONLINLS"

#define XBSDBLIB_D3D8     (1 << 0)
#define XBSDBLIB_D3D8LTCG (1 << 1)
#define XBSDBLIB_D3DX8    (1 << 2)
#define XBSDBLIB_DSOUND   (1 << 3)
#define XBSDBLIB_JVS      (1 << 4)
#define XBSDBLIB_XACTENG  (1 << 5)
#define XBSDBLIB_XAPILIB  (1 << 6)
#define XBSDBLIB_XGRAPHC  (1 << 7)
#define XBSDBLIB_XNET     (1 << 8)
#define XBSDBLIB_XNETN    (1 << 9)
#define XBSDBLIB_XNETS    (1 << 10)
#define XBSDBLIB_XONLINE  (1 << 11)
#define XBSDBLIB_XONLINEN (1 << 12)
#define XBSDBLIB_XONLINES (1 << 13)
#define XBSDBLIB_XONLINLS (1 << 14)

// clang-format off
// TODO: Need to find a way keep below intact.
#define XBSDBLIB_ALL ( XBSDBLIB_D3D8 | XBSDBLIB_D3D8LTCG | XBSDBLIB_D3DX8 | XBSDBLIB_DSOUND \
                     | XBSDBLIB_JVS | XBSDBLIB_XACTENG | XBSDBLIB_XAPILIB | XBSDBLIB_XGRAPHC \
                     | XBSDBLIB_XNET | XBSDBLIB_XNETN | XBSDBLIB_XNETS | XBSDBLIB_XONLINE \
                     | XBSDBLIB_XONLINEN | XBSDBLIB_XONLINES | XBSDBLIB_XONLINLS)
// clang-format on

typedef enum _xb_output_message {
    XB_OUTPUT_MESSAGE_DEBUG = 0,
    XB_OUTPUT_MESSAGE_INFO,
    XB_OUTPUT_MESSAGE_WARN,
    XB_OUTPUT_MESSAGE_ERROR,
    // Only for internal usage.
    XB_OUTPUT_MESSAGE_MAX
} xb_output_message;

typedef enum _xb_xbe_type {
    XB_XBE_TYPE_RETAIL = 0,
    XB_XBE_TYPE_DEBUG,
    XB_XBE_TYPE_CHIHIRO,
    // Only for internal usage.
    XB_XBE_TYPE_MAX
} xb_xbe_type;

static const uint32_t XB_XOR_KT[] = {
    0x5B6D40B6, // Kernel Thunk (Retail)
    0xEFB1F152, // Kernel Thunk (Debug)
    0x2290059D  // Kernel Thunk (Chihiro)
};

static const char* xbe_type_str[XB_XBE_TYPE_MAX] = {
    "RETAIL",
    "DEBUG",
    "CHIHIRO"
};

typedef enum _XbSDBSymbolType {
    symbol_internal = 0, // Only for internal usage.
    symbol_variable,
    symbol_function
} XbSDBSymbolType;

typedef enum _XbSDBCallType {
#define CALL_(type) call_##type,
#include <libCallTypes.h>
#undef CALL_
    call_max
} XbSDBCallType;

typedef enum _XbSDBParamType {
#define PARAM_TYPE__0(type)  param_##type,
#define PARAM_TYPE_64(type)  param_##type,
#define PARAM_TYPE_32(type)  param_##type,
#define PARAM_TYPE_16_(type) param__##type,
#define PARAM_TYPE__8_(type) param__##type,
#include <libParamTypes.h>
#undef PARAM_TYPE__0
#undef PARAM_TYPE_64
#undef PARAM_TYPE_32
#undef PARAM_TYPE_16_
#undef PARAM_TYPE__8_
    param_max
} XbSDBParamType;

typedef struct _XbSDBSymbolParam {
    XbSDBParamType type;
    const char* const name;
} XbSDBSymbolParam;

#ifndef xbaddr
typedef uint32_t xbaddr;
#endif

typedef struct _XbSDBLibrary {
    uint16_t build_version;
    uint16_t qfe_version;
    uint32_t flag;
    char name[8];
} XbSDBLibrary;

typedef struct _XbSDBLibraryHeader {
    unsigned int count;
    XbSDBLibrary* filters;
} XbSDBLibraryHeader;

typedef struct _XbSDBSection {
    // These three variables must be fixed info.
    char name[8];
    uint32_t xb_virt_addr;
    uint32_t buffer_size;
    void* buffer_lower;
} XbSDBSection;

typedef struct _XbSDBSectionHeader {
    unsigned int count;
    XbSDBSection* filters;
} XbSDBSectionHeader;

typedef void* XbSDBContextHandle;

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

/// <summary>
/// Return value is only useful to prevent re-cache the file every time. It does not taken existing functions into account.
/// </summary>
/// <returns>Return a version of current library database.</returns>
unsigned int XbSDB_LibraryVersion();

/// <summary>
/// Total symbols return give ability to support for progress bar from third-party software. Not all symbols will be detected in every titles.
/// </summary>
/// <param name="library_filter">See defined prefix of XBSDBLIB_ above to choose one or more library you wish to obtain total symbols.</param>
/// <returns>Return total symbols in current database system.</returns>
unsigned XbSDB_GetTotalSymbols(uint32_t library_filter);

/// <summary>
/// Register one or more library to be scan instead of whole database for optimize performance.
/// </summary>
/// <param name="library_filter">See defined prefix of XBSDBLIB_ above to choose one or more library you wish to scan.</param>
/// <returns>Return true if success, or else will return false for invalid parameter.</returns>
bool XbSDBContext_RegisterLibrary(XbSDBContextHandle pHandle, uint32_t library_filter);

/// <summary>
/// Callback function type for output message to software when have information to be output.
/// </summary>
/// <param name="message_flag">Output enum level flag.</param>
/// <param name="message_str">Output log message.</param>
typedef void (*xb_output_message_t)(xb_output_message message_flag, const char* message_str);

/// <summary>
/// Register output message callback function to receive output message.
/// </summary>
/// <param name="message_func">Set output message to a callback function.</param>
void XbSDB_SetOutputMessage(xb_output_message_t message_func);

/// <summary>
/// To register any detected symbol name with address and build version back to third-party program.
/// NOTE: Be aware that the library name will vary since some libraries are detected in other sections as well.
/// </summary>
/// <param name="library_str">Name of the library in string.</param>
/// <param name="library_flag">Name of the library in flag.</param>
/// <param name="xref_index">Output unique xreference of symbol name.</param>
/// <param name="symbol_str">Name of the library in symbol string.</param>
/// <param name="address">Return xbox's virtual address.</param>
/// <param name="build_version">Found with specific build version.</param>
/// <param name="symbol_type">Type of symbol. If symbol type is a function, then the following arguments starting with a param_ prefix will be set.</param>
/// <param name="param_count">Total count of parameters.</param>
/// <param name="param_list">List of parameters.</param>
typedef void (*xb_symbol_register_t)(const char* library_str, uint32_t library_flag, uint32_t xref_index, const char* symbol_str, xbaddr address, uint32_t build_version, uint32_t symbol_type, uint32_t call_type, uint32_t param_count, const XbSDBSymbolParam* param_list);

/// <summary>
/// DEPRECATED: To scan symbols in memory of raw xbe or host's virtual xbox environment.
/// </summary>
/// <param name="xb_header_addr">Starting point of xbox header address.</param>
/// <param name="register_func">Callback register function to be call for any detected symbols.</param>
/// <param name="is_raw">True: Full scan of raw xbe; False: Scan only loaded sections.</param>
/// <returns>Only return false if something is not valid.</returns>
bool XbSDB_Scan(const void* xb_header_addr, xb_symbol_register_t register_func, bool is_raw);

/// <summary>
/// To convert library flag into string format.
/// </summary>
/// <param name="library_flag">Input specific library flag.</param>
/// <returns>Return "UNKNOWN" string if does not exist in the database. Otherwise will return library name string.</returns>
const char* XbSDB_LibraryToString(uint32_t library_flag);

/// <summary>
/// To convert parameter type into string format.
/// </summary>
/// <param name="param_type">Input provided param_type from symbol register callback.</param>
/// <returns>Return "unk" string if does not exist in the database. Otherwise it will return the string representation of the parameter type.</returns>
const char* XbSDB_ParamToString(uint32_t param_type);

/// <summary>
/// To convert calling convention type into string format.
/// </summary>
/// <param name="call_type">Input provided call_type from symbol register callback.</param>
/// <returns>Return "unknown" string if does not exist in the database. Otherwise it will return the string representation of the calling convention type.</returns>
const char* XbSDB_CallingConventionToString(uint32_t call_type);

/// <summary>
/// To convert a symbol reference index into string format.
/// </summary>
/// <param name="xref_index">Input provided xref_index from symbol register callback.</param>
/// <returns>Returns a demangled symbol name string.</returns>
const char* XbSDB_SymbolReferenceToString(uint32_t xref_index);

/// <summary>
/// To convert library name string into flag format.
/// </summary>
/// <param name="library_name">Input library name string.</param>
/// <returns>Return 0 if does not exist in the database. Otherwise will return flag value.</returns>
uint32_t XbSDB_LibraryToFlag(const char* library_name);

/// <summary>
/// (Debug feature) By calling it will perform a self test for duplicate OOVPAs. (May will change at any time.)
/// </summary>
/// <returns>Return total count of errors.</returns>
unsigned int XbSDB_TestOOVPAs();

/// <summary>
/// (Debug feature) Set to true will perform full range of OOVPAs registered in current database.
/// Or stop at xbe's build version detected.
/// </summary>
/// <param name="bypass_limit">Input boolean to either bypass or enable the build version limit.</param>
void XbSDBContext_SetBypassBuildVersionLimit(XbSDBContextHandle pHandle, bool bypass_limit);

/// <summary>
/// To set verbose level can be output message.
/// By default, release build is set to info+ level and debug build is set to debug+ level.
/// </summary>
/// <param name="verbose_level">See xb_output_message enum for list of options.</param>
/// <returns>True: Successful set. False: Invalid input value.</returns>
bool XbSDB_SetOutputVerbosity(xb_output_message verbose_level);

/// <summary>
/// (Debug feature) Set to true will continue the same signature scan after first detected.
/// </summary>
/// <param name="enable">Input boolean to either continue with the signature scan after first symbol found or not.</param>
void XbSDBContext_SetContinuousSigScan(XbSDBContextHandle pHandle, bool enable);

/// <summary>
/// (Debug feature) Set to true will register first detected address only.
/// This function can be used if XbSDBContext_SetContinuousSigScan is set to true.
/// </summary>
/// <param name="enable">Input boolean to use first symbol address only or not.</param>
void XbSDBContext_SetFirstDetectAddressOnly(XbSDBContextHandle pHandle, bool enable);

/// <summary>
/// Get library flag's dependencies.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
/// <param name="library_flag">Input specific library flag.</param>
/// <param name="library_filters">Input generated library filters.</param>
/// <returns>Return either none, one, or more library flag dependencies.</returns>
uint32_t XbSDB_GetLibraryDependencies(uint32_t library_flag, XbSDBLibraryHeader library_filters);

/// <summary>
/// Step 1: Generate library array for LibraryHeader input.
/// First call with <paramref name="library_out"/> as null pointer will return total count. Then second call will insert information to <paramref name="library_out"/>.filters field.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <param name="library_out">Input null pointer will provide the count to allocate memory for library_out.filters field. Otherwise, information will be input to library_out.filters field.</param>
/// <returns>Return total library found can be use in scan process.</returns>
unsigned int XbSDB_GenerateLibraryFilter(const void* xb_header_addr, XbSDBLibraryHeader* library_out);

/// <summary>
/// Step 2: Generate section array for SectionHeader input.
/// First call with <paramref name="section_out"/> as null pointer will return total count. Then second call will insert information to <paramref name="section_out"/>.filters field.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <param name="section_out">Input null pointer will provide the count to allocate memory, then allocate memory to section_out.filters field.</param>
/// <param name="is_raw">True: Convert array to use raw xbe's relative address; False: Convert array to use xbox virtual memory relative address.</param>
/// <returns>Return total sections found can be use in scan process.</returns>
unsigned int XbSDB_GenerateSectionFilter(const void* xb_header_addr, XbSDBSectionHeader* section_out, bool is_raw);

/// <summary>
/// Step 3: Get Xbox kernel thunk address.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <returns>Return kernel thunk address. NOTE: This function may not return valid address.</returns>
xbaddr XbSDB_GetKernelThunkAddress(const void* xb_header_addr);

/// <summary>
/// Step 4: Create XbSDBContextHandle context for the scan process.
/// </summary>
/// <param name="ppHandle">Output XbSDBContextHandle handler.</param>
/// <param name="register_func">Register callback function for any detected symbols during scan process.</param>
/// <param name="library_input">See XbSDB_GenerateLibraryFilter for details.</param>
/// <param name="section_input">See XbSDB_GenerateSectionFilter for details.</param>
/// <param name="kernel_thunk">Input decoded virtual kernel thunk.</param>
/// <returns>Return true if context handle's creation is a success.</returns>
bool XbSDB_CreateContext(XbSDBContextHandle* ppHandle, xb_symbol_register_t register_func, XbSDBLibraryHeader library_input, XbSDBSectionHeader section_input, xbaddr kernel_thunk);

/// <summary>
/// Step 5: Perform a manual scan to set references, XRefDatabase, manually by requirement.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
void XbSDBContext_ScanManual(XbSDBContextHandle pHandle);

/// <summary>
/// Step 6: Get library flag's dependencies.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
/// <param name="library_flag">Input specific library flag.</param>
/// <param name="library_filters">Input generated library filters.</param>
/// <returns>Return either none, one, or more library flag dependencies.</returns>
uint32_t XbSDBContext_GetLibraryDependencies(XbSDBContextHandle pHandle, uint32_t library_flag);

#define XbSDB_CheckDependencyCompletion(completion_flag, dependencies) ((completion_flag & dependencies) == dependencies)

/// <summary>
/// Step 7a: (multi-thread safe, optional) Process individual library input by third-party.
/// NOTE: If planned to use multi-thread purpose, please use thread-safe method for library dependency checkup.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
/// <param name="pLibrary">Input pointer of a library to start a scan process.</param>
/// <param name="xref_first_pass">True: Optimized first search scan process; False: 2nd call and later will continue to return non-zero; see return for detail.</param>
/// <returns>Return total xref count found. Unless it return zero, then there's nothing left to find.</returns>
unsigned int XbSDBContext_ScanLibrary(XbSDBContextHandle pHandle, const XbSDBLibrary* pLibrary, bool xref_first_pass);

#define XbSDB_SetLibraryCompletion(completion_flag, library_flag) (completion_flag |= library_flag)

/// <summary>
/// Step 7b: (single-thread usage) Process all of filter libraries internally.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
void XbSDBContext_ScanAllLibraryFilter(XbSDBContextHandle pHandle);

/// <summary>
/// Step 8: Register any references, XRefDatabase, may not had been output during the scan process.
/// NOTE: Currently a stub at the moment.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
void XbSDBContext_RegisterXRefs(XbSDBContextHandle pHandle);

/// <summary>
/// Final Step: Release context.
/// </summary>
/// <param name="pHandle">Input XbSDBContextHandle handler.</param>
void XbSDBContext_Release(XbSDBContextHandle pHandle);

#ifdef __cplusplus
}
#endif
