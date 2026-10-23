// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2002 Aaron Robinson <caustik@caustik.com>
// SPDX-FileCopyrightText: 2017 PatrickvL
// SPDX-FileCopyrightText: 2017 RadWolfie

#pragma once

#include "libXbSymbolDatabase.h"

// http://stackoverflow.com/questions/5134523/msvc-doesnt-expand-va-args-correctly
// MSVC_EXPAND works around a Visual C++ problem, expanding __VA_ARGS__ incorrectly:
#define MSVC_EXPAND(x) x

// Wrap C++ style macro function so that clang-format follows our code style.
// NOTE: Not relative to MSVC_EXPAND macro's bugfix.
#define MACRO_FUNC(x) x

#define STRINGIZEX(x) #x
#define STRINGIZE(x)  STRINGIZEX(x)

// Concatenate two strings into one string for preprocessor to process.
#define CONCAT(a, b) a##b

// parentheses
#define VA_ARGS_EXPAND(...)        __VA_ARGS__
#define UNPARENTHESES_INVOKE(args) VA_ARGS_EXPAND(args)
#define UNPARENTHESES(args)        UNPARENTHESES_INVOKE(VA_ARGS_EXPAND args)

// get the number of elements of an array
#define COUNT_ARRAYSIZE(type_, array_) (sizeof((type_[])UNPARENTHESES(array_)) / sizeof(type_))

// Increment counter used by the PARAMS macro.
#define INC_1  2
#define INC_2  3
#define INC_3  4
#define INC_4  5
#define INC_5  6
#define INC_6  7
#define INC_7  8
#define INC_8  9
#define INC_9  10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC_16 17
#define INC_17 18
#define INC_18 19

#pragma pack(1)

// ******************************************************************
// * Optimized (Offset, Value)-Pair Array
// ******************************************************************
typedef struct _OOVPA {

    unsigned char Padding[1];

    // This OOVPA field, XRefCount, contains the number of
    // {Offset, XREF_*-enum}-pairs that come before all other
    // {Offset, Value}-pairs.
    // (The {Offset, XREF_*-enum}-pairs are INCLUDED in OOVPA.Count)
    // (Also, see comments at XRefZero and XRefOne.)
    unsigned char XRefCount;

    unsigned char DetectSelect;

    // This OOVPA field, Count, indicates the number of
    // {Offset, Value}-pairs present in the Lovp array,
    // available after casting this OOVPA to LOOVPA.
    // (This Count INCLUDES optional leading {Offset, XREF_*-enum}-
    // pairs - see comment at XRefCount.)
    unsigned char Count;

    // Define LOVP here to reduce type definition complexity.
    // (Otherwise, if defined in the template classes, that would mean
    // that for each template instance, the type is redefined. Let's
    // avoid that.)
} OOVPA;

// {Offset, Value}-pair(s)
typedef struct _LOVP {
    // Both the Offset and Value are 16-bit to allow for XRefs with a
    // large offset. Value can be safely cast to 8-bit for OOVPA, but must
    // remain 16-bit for XRef entries.
    unsigned short offset;
    union {
        // Generic structure TODO: Remove me after replace array to macro for OOVPA database
        unsigned short value;

        struct {
            unsigned char unused;
            unsigned char value;
        } byte;

        struct {
            unsigned short index;
        } xref;
    };
} LOVP;

// Set variable's padding to 0.
#define VARPADSET 0

/*
// XRefZero constant, when set in the OOVPA.XRefCount field,
// indicates there are no {offset, XREF_*-enum} present in the OOVPA.

// XRefOne constant, when set in the OOVPA.XRefCount field,
// indicates the OOVPA contains one (1) {offset, XREF_* enum} pair.

// Sometimes, there can be more than one {Offset, XREF_*-enum}
// pair at the start of the OOVPA's.
*/
#define XRefZero  0
#define XRefOne   1
#define XRefTwo   2
#define XRefThree 3
#define XRefFour  4

// TODO: Rename to OV_XREF.
// Macro used for storing an XRef {Offset, XREF}-Pair.
// clang-format off
#define XREF_ENTRY( Offset, XRef) \
    { Offset, .xref.index = XRef }
// clang-format on

// Macro for storing a normal (non-XRef) {Offset, Value}-Pair
// Offsets can go up to 16 bits, values are always one byte (8 bits)
// clang-format off
#define OV_BYTE(Offset, Value) \
    { Offset, .value = Value }
// clang-format on
// TODO: Remove above line, then uncomment the line below for easy swap after OOVPA database has been fixed.
//  { Offset, { .unused = 0, .value = Value } }

// Macro for determine how the OOVPA scan will process for detection.
#define DetectDefault 0
#define DetectFirst   1
#define DetectSecond  2
#define DetectThird   3
#define DetectFourth  4

// ******************************************************************
// * Large Optimized (Offset,Value)-Pair Array
// ******************************************************************
#pragma warning(push)
#pragma warning(disable : 4200)
typedef struct _LOOVPA {
    OOVPA Header;

    // Large (Offset,Value)-Pair(s)
    LOVP Lovp[];
} LOOVPA;
#pragma warning(pop)

// clang-format off
#define OOVPA_SIG_MATCH(...) COUNT_ARRAYSIZE(LOVP, ({ __VA_ARGS__ })), { __VA_ARGS__ } }
#define OOVPA_SIG_MATCH_DUMMY() 0, { { 0, 0 } } }
// clang-format on

#define OOVPA_SIG_HEADER_XREF_EXTEND(Name, Version, XRefCount, DetectSelect) \
    static LOOVPA Name##_##Version = { VARPADSET, XRefCount, DetectSelect,

#define OOVPA_XREF_EXTEND(Name, Version, Count, XRefCount, DetectSelect) \
    static LOOVPA Name##_##Version = { VARPADSET, XRefCount, DetectSelect, Count,

#define OOVPA_SIG_HEADER_XREF_DETECT OOVPA_SIG_HEADER_XREF_EXTEND

#define OOVPA_XREF_DETECT OOVPA_XREF_EXTEND

#define OOVPA_SIG_HEADER_NO_XREF_DETECT(Name, Version, DetectSelect) \
    OOVPA_SIG_HEADER_XREF_EXTEND(Name, Version, XRefZero, DetectSelect)

#define OOVPA_NO_XREF_DETECT(Name, Version, Count, DetectSelect) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefZero, DetectSelect)

#define OOVPA_SIG_HEADER_XREF(Name, Version, XRefCount) \
    OOVPA_SIG_HEADER_XREF_EXTEND(Name, Version, XRefCount, DetectDefault)

#define OOVPA_XREF(Name, Version, Count, XRefCount) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefCount, DetectDefault)

#define OOVPA_SIG_HEADER_NO_XREF(Name, Version) \
    OOVPA_SIG_HEADER_XREF_EXTEND(Name, Version, XRefZero, DetectDefault)

#define OOVPA_NO_XREF(Name, Version, Count) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefZero, DetectDefault)

#define OOVPA_END }

#pragma pack() // restore packing so that AppleClang can build
typedef struct _OOVPARevision {
    OOVPA* Oovpa;
    unsigned short Version; // : 13; // 2^13 = 8192, enough to store lowest and highest possible Library Version number in
} OOVPARevision;
#pragma pack(1)

typedef enum _eDBScanType {
    DB_ST_NONE = 0,
    DB_ST_MANUAL = (1 << 0),
    DB_ST_AUTO = (1 << 1),

    DB_ST_ALL = DB_ST_MANUAL | DB_ST_AUTO
} eDBScanType;

// ******************************************************************
// * OOVPATable
// ******************************************************************
#pragma pack() // restore packing so that AppleClang can build
typedef struct _OOVPATable {
    const uint16_t xref;
    const unsigned scan_type;
    const XbSDBSymbolType symbol_type;
    const char* szSymbolName;
    const XbSDBCallType call_type;
    const unsigned param_count;
    const XbSDBSymbolParam* param_list;
    const unsigned count;
    OOVPARevision* const revisions;
} OOVPATable;

typedef struct _OOVPATableList {
    unsigned int Count;
    OOVPATable* Table;
} OOVPATableList;
#pragma pack(1)

// http://en.cppreference.com/w/cpp/iterator/size
// clang-format off
//#include <iterator>
//#define XBSDB_ARRAY_SIZE(x) std::size(x)
// clang-format on
#define XBSDB_ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// clang-format off
#define OOVPA_TABLE_ENTRY_FULL(Oovpa, Version) \
    { &Oovpa##_##Version.Header, Version }
// clang-format on

// Register each version into one symbol table database.
#define REGISTER_OOVPA(Symbol, Version) \
    OOVPA_TABLE_ENTRY_FULL(Symbol, Version)

// Based on https://codecraft.co/2014/11/25/variadic-macros-tricks/
// and https://groups.google.com/d/msg/comp.std.c/d-6Mj5Lko_s/jqonQLK20HcJ
#define REGISTER_OOVPA_0(...)
#define REGISTER_OOVPA_1(Symbol, Version)       REGISTER_OOVPA(Symbol, Version)
#define REGISTER_OOVPA_2(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_1(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_3(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_2(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_4(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_3(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_5(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_4(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_6(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_5(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_7(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_6(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_8(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_7(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_9(Symbol, Version, ...)  REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_8(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_10(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_9(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_11(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_10(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_12(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_11(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_13(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_12(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_14(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_13(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_15(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_14(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_16(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_15(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_17(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_16(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_18(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_17(Symbol, __VA_ARGS__))
#define REGISTER_OOVPA_19(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_18(Symbol, __VA_ARGS__))

#define OV_BYTES_0(...)
#define OV_BYTES_1(Offset, Value)      OV_BYTE(Offset, Value)
#define OV_BYTES_2(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_1(Offset + 1, __VA_ARGS__))
#define OV_BYTES_3(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_2(Offset + 1, __VA_ARGS__))
#define OV_BYTES_4(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_3(Offset + 1, __VA_ARGS__))
#define OV_BYTES_5(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_4(Offset + 1, __VA_ARGS__))
#define OV_BYTES_6(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_5(Offset + 1, __VA_ARGS__))
#define OV_BYTES_7(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_6(Offset + 1, __VA_ARGS__))
#define OV_BYTES_8(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_7(Offset + 1, __VA_ARGS__))

#define CALL_unk   call_unknown
#define CALL_cde   call_cdecl
#define CALL_std   call_stdcall
#define CALL_thi   call_thiscall
#define CALL_fas   call_fastcall
#define CALL(Name) CALL_##Name

// For generate symbol's suffix name, mainly for registers, and extended API usage.
#define PARAM(Param, Name)            Param, Name
#define PARAM1(Param)                 Param, ""
#define PARAM_TOKEN_unk(Index, Name)  _unk##Index
#define PARAM_TOKEN_void(Index, Name) // No argument, do not append to symbol reference.
#define PARAM_TOKEN_psh2(Index, Name) // (Custom) argument is stored in call stack with two pushes, do not append to symbol reference.
#define PARAM_TOKEN_psh(Index, Name)  // Argument is stored in call stack with one push, do not append to symbol reference.
#define PARAM_TOKEN_eax(Index, Name)  _eax##Index
#define PARAM_TOKEN__ax(Index, Name)  _ax##Index
#define PARAM_TOKEN__ah(Index, Name)  _ah##Index
#define PARAM_TOKEN__al(Index, Name)  _al##Index
#define PARAM_TOKEN_ebx(Index, Name)  _ebx##Index
#define PARAM_TOKEN__bx(Index, Name)  _bx##Index
#define PARAM_TOKEN__bh(Index, Name)  _bh##Index
#define PARAM_TOKEN__bl(Index, Name)  _bl##Index
#define PARAM_TOKEN_ecx(Index, Name)  _ecx##Index
#define PARAM_TOKEN__cx(Index, Name)  _cx##Index
#define PARAM_TOKEN__ch(Index, Name)  _ch##Index
#define PARAM_TOKEN__cl(Index, Name)  _cl##Index
#define PARAM_TOKEN_edx(Index, Name)  _edx##Index
#define PARAM_TOKEN__dx(Index, Name)  _dx##Index
#define PARAM_TOKEN__dh(Index, Name)  _dh##Index
#define PARAM_TOKEN__dl(Index, Name)  _dl##Index
#define PARAM_TOKEN_ebp(Index, Name)  _ebp##Index
#define PARAM_TOKEN_edi(Index, Name)  _edi##Index
#define PARAM_TOKEN_esi(Index, Name)  _esi##Index

#define PARAMS_TOKEN_EXPAND(param_a, param_b) CONCAT(param_a, param_b)
#define PARAMS_TOKEN_0(...)
#define PARAMS_TOKEN_X(Index, Param, Name)       PARAM_TOKEN_##Param(Index, Name)
#define PARAMS_TOKEN_1(Index, Param, Name)       PARAMS_TOKEN_X(Index, Param, Name)
#define PARAMS_TOKEN_2(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_1(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_3(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_2(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_4(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_3(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_5(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_4(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_6(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_5(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_7(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_6(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_8(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_7(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_9(Index, Param, Name, ...)  PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_8(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_10(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_9(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_11(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_10(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_12(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_11(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_13(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_12(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_14(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_13(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_15(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_14(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_16(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_15(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_17(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_16(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_18(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_17(CONCAT(INC_, Index), __VA_ARGS__))
#define PARAMS_TOKEN_19(Index, Param, Name, ...) PARAMS_TOKEN_EXPAND(PARAMS_TOKEN_X(Index, Param, Name), PARAMS_TOKEN_18(CONCAT(INC_, Index), __VA_ARGS__))

#define PARAMS_LIST_EXPAND(param_a, param_b) CONCAT(param_a, param_b)
#define PARAMS_LIST_0(...)                   { param_unk, "" },
#define PARAMS_LIST_1(Param, Name)           { param_##Param, #Name },
#define PARAMS_LIST_2(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_1(__VA_ARGS__)
#define PARAMS_LIST_3(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_2(__VA_ARGS__)
#define PARAMS_LIST_4(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_3(__VA_ARGS__)
#define PARAMS_LIST_5(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_4(__VA_ARGS__)
#define PARAMS_LIST_6(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_5(__VA_ARGS__)
#define PARAMS_LIST_7(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_6(__VA_ARGS__)
#define PARAMS_LIST_8(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_7(__VA_ARGS__)
#define PARAMS_LIST_9(Param, Name, ...)      { param_##Param, #Name }, PARAMS_LIST_8(__VA_ARGS__)
#define PARAMS_LIST_10(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_9(__VA_ARGS__)
#define PARAMS_LIST_11(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_10(__VA_ARGS__)
#define PARAMS_LIST_12(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_11(__VA_ARGS__)
#define PARAMS_LIST_13(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_12(__VA_ARGS__)
#define PARAMS_LIST_14(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_13(__VA_ARGS__)
#define PARAMS_LIST_15(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_14(__VA_ARGS__)
#define PARAMS_LIST_16(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_15(__VA_ARGS__)
#define PARAMS_LIST_17(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_16(__VA_ARGS__)
#define PARAMS_LIST_18(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_17(__VA_ARGS__)
#define PARAMS_LIST_19(Param, Name, ...)     { param_##Param, #Name }, PARAMS_LIST_18(__VA_ARGS__)

// Accept any number of args >= N, but expand to just the Nth one. In this case,
// we have settled on 20 as N. We could pick a different number by adjusting
// the count of throwaway args before N. Note that this macro is preceded by
// an underscore--it's an implementation detail, not something we expect people
// to call directly.
#define _GET_NTH_ARG_MAX_19(                          \
    _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, \
    _9, _8, _7, _6, _5, _4, _3, _2, _1, _0,           \
    N, ...) N
// For OV_MATCH macro
// Even though x86 instructions can be anywhere from 1 to 15 bytes long,
// we don't need to fill in whole instruction.
#define _GET_NTH_ARG_MAX_8(             \
    _8, _7, _6, _5, _4, _3, _2, _1, _0, \
    N, ...) N
// For STACK macro
// We want to accept empty argument to exclude _# suffix from symbol name.
#define _GET_NTH_ARG_MAX_1(_1, _0, N, ...) N

// Works, even with empty argument.
#define COUNT_VARARGS_MAX_19(...) _GET_NTH_ARG_MAX_19("ignored", ##__VA_ARGS__, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define SUFFIX(x) x

#define STACK_0(...)
#define STACK_1(Size) _##Size

#define STACK(...)                                          \
    MACRO_FUNC(_GET_NTH_ARG_MAX_1("ignored", ##__VA_ARGS__, \
                                  STACK_1, STACK_0)(__VA_ARGS__))

#define PARAMS(...)                                                                                                                  \
    MACRO_FUNC(_GET_NTH_ARG_MAX_19("ignored", ##__VA_ARGS__,                                                                         \
                                   PARAMS_TOKEN_19, PARAMS_TOKEN_18, PARAMS_TOKEN_17, PARAMS_TOKEN_16, PARAMS_TOKEN_15,              \
                                   PARAMS_TOKEN_14, PARAMS_TOKEN_13, PARAMS_TOKEN_12, PARAMS_TOKEN_11, PARAMS_TOKEN_10,              \
                                   PARAMS_TOKEN_9, PARAMS_TOKEN_8, PARAMS_TOKEN_7, PARAMS_TOKEN_6, PARAMS_TOKEN_5,                   \
                                   PARAMS_TOKEN_4, PARAMS_TOKEN_3, PARAMS_TOKEN_2, PARAMS_TOKEN_1, PARAMS_TOKEN_0)(1, __VA_ARGS__)), \
        ({ MACRO_FUNC(_GET_NTH_ARG_MAX_19("ignored", ##__VA_ARGS__,                                                                  \
                                          PARAMS_LIST_19, PARAMS_LIST_18, PARAMS_LIST_17, PARAMS_LIST_16, PARAMS_LIST_15,            \
                                          PARAMS_LIST_14, PARAMS_LIST_13, PARAMS_LIST_12, PARAMS_LIST_11, PARAMS_LIST_10,            \
                                          PARAMS_LIST_9, PARAMS_LIST_8, PARAMS_LIST_7, PARAMS_LIST_6, PARAMS_LIST_5,                 \
                                          PARAMS_LIST_4, PARAMS_LIST_3, PARAMS_LIST_2, PARAMS_LIST_1, PARAMS_LIST_0)(__VA_ARGS__)) })

#define SYMBOL_EXPAND(symbol_name, stack_size, suffix, params, ...)      (symbol_name, symbol_name##stack_size##suffix, __VA_ARGS__)
#define SYMBOL_EXPAND_LTCG(symbol_name, stack_size, suffix, params, ...) (symbol_name, symbol_name##stack_size##suffix##params, __VA_ARGS__)
#define SYM_INT(symbol_name)                                             SYMBOL_EXPAND(symbol_name, /*NONE*/, /*NONE*/, /*NONE*/, ({ param_unk, "" }), symbol_internal, call_none)
#define SYM_VAR(symbol_name)                                             SYMBOL_EXPAND(symbol_name, /*NONE*/, /*NONE*/, /*NONE*/, ({ param_unk, "" }), symbol_variable, call_none)
#define SYM_FUN(symbol_name, call_type, stack_size, params)              SYMBOL_EXPAND(symbol_name, stack_size, /*NONE*/, params, symbol_function, call_type)
#define SYM_FUN_ALT(symbol_name, suffix, call_type, stack_size, params)  SYMBOL_EXPAND(symbol_name, stack_size, suffix, params, symbol_function, call_type)
#define SYM_FUN_LTCG(symbol_name, call_type, stack_size, params)         SYMBOL_EXPAND_LTCG(symbol_name, stack_size, __LTCG, params, symbol_function, call_type)
#define SYM_SIG                                                          VA_ARGS_EXPAND

#define REGISTER_OOVPAS_TYPE(xref, symbol_name, param_list, symbol_type, call_type, scan_type, ...)                                                         \
    XREF_##xref,                                                                                                                                            \
        scan_type,                                                                                                                                          \
        symbol_type,                                                                                                                                        \
        #symbol_name,                                                                                                                                       \
        call_type,                                                                                                                                          \
        COUNT_ARRAYSIZE(const XbSDBSymbolParam, param_list),                                                                                                \
        (const XbSDBSymbolParam[])UNPARENTHESES(param_list),                                                                                                \
        COUNT_ARRAYSIZE(unsigned short, ({ __VA_ARGS__ })),                                                                                                 \
        (OOVPARevision[])                                                                                                                                   \
    {                                                                                                                                                       \
        MACRO_FUNC(_GET_NTH_ARG_MAX_19("ignored", ##__VA_ARGS__,                                                                                            \
                                       REGISTER_OOVPA_19, REGISTER_OOVPA_18, REGISTER_OOVPA_17, REGISTER_OOVPA_16, REGISTER_OOVPA_15,                       \
                                       REGISTER_OOVPA_14, REGISTER_OOVPA_13, REGISTER_OOVPA_12, REGISTER_OOVPA_11, REGISTER_OOVPA_10,                       \
                                       REGISTER_OOVPA_9, REGISTER_OOVPA_8, REGISTER_OOVPA_7, REGISTER_OOVPA_6, REGISTER_OOVPA_5,                            \
                                       REGISTER_OOVPA_4, REGISTER_OOVPA_3, REGISTER_OOVPA_2, REGISTER_OOVPA_1, REGISTER_OOVPA_0)(symbol_name, __VA_ARGS__)) \
    }

#define REGISTER_OOVPAS_TYPE_PREFIX(xref_prefix, xref, ...) REGISTER_OOVPAS_TYPE(xref_prefix##_##xref, __VA_ARGS__)

// Use REGISTER_OOVPAS for automate scan only process
#define REGISTER_OOVPAS_EXPAND(...)                      REGISTER_OOVPAS_TYPE(__VA_ARGS__)
#define REGISTER_OOVPAS_EXPAND_PREFIX(...)               REGISTER_OOVPAS_TYPE_PREFIX(__VA_ARGS__)
#define REGISTER_OOVPAS(Symbol_Info, ...)                REGISTER_OOVPAS_EXPAND(UNPARENTHESES(Symbol_Info), DB_ST_AUTO, __VA_ARGS__)
#define REGISTER_OOVPAS_PREFIX(Prefix, Symbol_Info, ...) REGISTER_OOVPAS_EXPAND_PREFIX(Prefix, UNPARENTHESES(Symbol_Info), DB_ST_AUTO, __VA_ARGS__)
// Use REGISTER_OOVPAS_M for manual scan only process
#define REGISTER_OOVPAS_M(Symbol_Info, ...)                REGISTER_OOVPAS_EXPAND(UNPARENTHESES(Symbol_Info), DB_ST_MANUAL, __VA_ARGS__)
#define REGISTER_OOVPAS_M_PREFIX(Prefix, Symbol_Info, ...) REGISTER_OOVPAS_EXPAND_PREFIX(Prefix, UNPARENTHESES(Symbol_Info), DB_ST_MANUAL, __VA_ARGS__)
// Use REGISTER_OOVPAS_C for combine manual and automate scan process
#define REGISTER_OOVPAS_C(Symbol_Info, ...)                REGISTER_OOVPAS_EXPAND(UNPARENTHESES(Symbol_Info), DB_ST_ALL, __VA_ARGS__)
#define REGISTER_OOVPAS_C_PREFIX(Prefix, Symbol_Info, ...) REGISTER_OOVPAS_EXPAND_PREFIX(Prefix, UNPARENTHESES(Symbol_Info), DB_ST_ALL, __VA_ARGS__)

#define OV_MATCH(Offset, ...)                                                                 \
    MACRO_FUNC(_GET_NTH_ARG_MAX_8("ignored", ##__VA_ARGS__,                                   \
                                  OV_BYTES_8, OV_BYTES_7, OV_BYTES_6, OV_BYTES_5, OV_BYTES_4, \
                                  OV_BYTES_3, OV_BYTES_2, OV_BYTES_1, OV_BYTES_0)(Offset, __VA_ARGS__))

#pragma pack()
