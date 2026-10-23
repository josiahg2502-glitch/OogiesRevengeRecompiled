// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library version
//   [LibV] Title Name                        | Verify  |  Comments
//-------------------------------------------------------------------
// * [3911] Halo                              |  100%   | Contain full library.
// * [4039] Tony Hawk's Pro Skater 3          |  100%   | have 10/11 library.
// * [4361] MotoGP                            |  100%   | Contain full library.
// * [4721] TimeSplitters 2                   |  100%   | have 8/11 library.
// * [5344] Stake                             |  100%   | have 10/11 XNETN library.

// TODO: Known XNET OOVPA issue list
// * XnInit 3911 is for only XNETS library. XNET library is different one.
// * Verification needed: Function Name ( Revision )
//   * connect (4721)
//   * listen (4039, 4721)
//   * send (4721)
//   * XNetGetEthernetLinkStatus (5344)

#include "OOVPA_databases.h"

#include "XNet/3911.inl"
#include "XNet/4361.inl"
#include "XNet/4627.inl"
#include "XNet/5120.inl"
#include "XNet/5455.inl"

// ******************************************************************
// * XNET_OOVPA_Table
// ******************************************************************
static OOVPATable XNET_OOVPA_Table[] = {

    REGISTER_OOVPAS(SYM_FUN(XnInit, CALL(std), STACK(8), PARAMS(PARAM(psh, pxnsp), PARAM(psh, bWSA))),
                    SYM_SIG(3911)), // 3911 is only XNETS library, XNET library is different OOVPA.
    REGISTER_OOVPAS(SYM_FUN(XnInit, CALL(std), STACK(24), PARAMS(PARAM(psh, pUnknown1), PARAM(psh, unknown2), PARAM(psh, pxnsp), PARAM(psh, bWSA), PARAM(psh, wVersionRequested), PARAM(psh, lpWSAData))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(WSAStartup, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, wVersionRequested), PARAM(psh, lpWSAData))),
                    SYM_SIG(3911, 4361)),
    REGISTER_OOVPAS(SYM_FUN(XNetStartup, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pxnsp))),
                    SYM_SIG(3911, 4361)),
    REGISTER_OOVPAS(SYM_FUN(XNetGetEthernetLinkStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4627)), // NOTE: Found in .text section, confirmed it is correct.

    // TODO: Fix below signatures to contain class (aka CXnSock_ prefix) then add actual non-class functions.
    REGISTER_OOVPAS(SYM_FUN(bind, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, s), PARAM(psh, name), PARAM(psh, namelen))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(connect, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, s), PARAM(psh, name), PARAM(psh, namelen))),
                    SYM_SIG(3911, 5120)),
    REGISTER_OOVPAS(SYM_FUN(ioctlsocket, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, s), PARAM(psh, cmd), PARAM(psh, argp))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(listen, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, s), PARAM(psh, backlog))),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(recv, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, s), PARAM(psh, buf), PARAM(psh, len), PARAM(psh, flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(send, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, s), PARAM(psh, buf), PARAM(psh, len), PARAM(psh, flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(socket, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, af), PARAM(psh, type), PARAM(psh, protocol))),
                    SYM_SIG(3911, 4627, 5455)),
};

// ******************************************************************
// * XNET_OOVPA
// ******************************************************************
OOVPATableList XNET_OOVPA = { XBSDB_ARRAY_SIZE(XNET_OOVPA_Table), XNET_OOVPA_Table };
