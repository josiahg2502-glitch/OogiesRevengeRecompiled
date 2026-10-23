// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

#pragma once

static inline void manual_register_jvs(XbSDBiContext* pContext)
{
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_JVS, XBSDBLIB_JVS, XREF_JVS_g_pPINSA, 4831, "JVS_g_pPINSA", symbol_variable, call_none, 0, NULL);
    XbSDBi_RegisterValidXRefAddr(pContext, LIB_JVS, XBSDBLIB_JVS, XREF_JVS_g_pPINSB, 4831, "JVS_g_pPINSB", symbol_variable, call_none, 0, NULL);
}
