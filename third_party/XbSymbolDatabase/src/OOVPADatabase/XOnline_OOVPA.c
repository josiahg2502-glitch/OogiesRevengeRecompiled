// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library version
//   [LibV] Title Name                        | Verify  |   Comments
//-------------------------------------------------------------------
// * [4721] NFL 2K3                           |  100%   | Contain full library.
// * [4721] NFL Fever 2003                    |  100%   | Contain full library.
// * [4831] MechAssault                       |  100%   | Contain full library.
// * [4831] NBA 2K3                           |  100%   | Contain full library.
// * [4831] Whacked Demo                      |  100%   | Contain full library.
// * [4928] Ghost Recon                       |  100%   | Contain full library.
// * [4928] Unreal Championship               |  100%   | Contain full library.
// * [5028] Capcom vs. SNK 2 EO               |  100%   | Contain full library.
// * [5120] Muzzle Flash                      |  100%   | have 11/14 library.
// * [5233] Midtown Madness 3                 |  100%   | Contain full library.
// * [5233] MotoGP 2                          |  100%   | have 11/14 library.
// * [5344] Burnout 2                         |  100%   | have 11/14 library.
// * [5344] Wolfenstein                       |  100%   | May contain full library.
// * [5455] Ghost Recon Island Thunder        |  100%   | Contain full library.
// * [5558] ESPN NBA Basketball               |  100%   | Contain full library.
// * [5558] Links 2004                        |  100%   | Contain full library.
// * [5558] XIII                              |  100%   | Contain full library.
// * [5659] Crimson Skies                     |  100%   | Contain full library.
// * [5659] Plus Plum 2                       |  100%   | Contain full library.
// * [5659] Unreal II: The Awakening          |  100%   | Contain full library.
// * [5788] All-Star Baseball '05             |  100%   | Contain full library.
// * [5788] Splinter Cell: Pandora Tomorrow   |  100%   | Contain full library.
// * [5849] Brothers In Arms: Earned In Blood |  100%   | Contain full library.
// * [5849] Brothers In Arms: Road to Hill 30 |  100%   | Contain full library.
// * [5849] Call of Duty Finest Hour          |  100%   | Contain full library.
// * [5849] Chessmaster                       |  100%   | Contain full library.
// * [5849] Kingdom Under Fire: The Crusaders |  100%   | Contain full library.
// * [5849] MechAssault 2: Lone Wolf          |  100%   | Contain full library.
// * [5849] Splinter Cell: Chaos Theory       |  100%   | Contain full library.
// * [5849] Stacked                           |  100%   | Contain full library.
// * [5849] World Series of Poker             |  100%   | Contain full library.

// TODO: Known XOnlines OOVPA issue list
// * Following OOVPA revision are not verified
//   * listen (5120, 5233)
//   * recv (5120, 5233)
//   * send (5120, 5233)

#include "OOVPA_databases.h"

#include "XOnline/4361.inl"
#include "XOnline/4627.inl"
#include "XOnline/4721.inl"
#include "XOnline/5028.inl"
#include "XOnline/5233.inl"
#include "XOnline/5455.inl"
#include "XOnline/5558.inl"
#include "XOnline/5788.inl"
#include "XOnline/5849.inl"

// ******************************************************************
// * XONLINE_OOVPA_Table
// ******************************************************************
static OOVPATable XONLINE_OOVPA_Table[] = {

    // XOnline section
    REGISTER_OOVPAS(SYM_FUN(CXo_XOnlineLogon, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, pUsers), PARAM(psh, pdwServiceIDs), PARAM(psh, dwServices), PARAM(psh, hEvent), PARAM(psh, pHandle))),
                    SYM_SIG(4361, 4627, 4721, 5455, 5558, 5849)),
    REGISTER_OOVPAS(SYM_FUN(XOnlineLogon, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pUsers), PARAM(psh, pdwServiceIDs), PARAM(psh, dwServices), PARAM(psh, hEvent), PARAM(psh, pHandle))),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(CXo_XOnlineMatchSearch, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwProcedureIndex), PARAM(psh, dwNumResults), PARAM(psh, dwNumAttributes), PARAM(psh, pAttributes), PARAM(psh, dwResultsLen), PARAM(psh, hWorkEvent), PARAM(psh, phTask))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(XOnlineMatchSearch, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwProcedureIndex), PARAM(psh, dwNumResults), PARAM(psh, dwNumAttributes), PARAM(psh, pAttributes), PARAM(psh, dwResultsLen), PARAM(psh, hWorkEvent), PARAM(psh, phTask))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(CXo_XOnlineMatchSearchResultsLen, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwNumResults), PARAM(psh, dwNumSessionAttributes), PARAM(psh, pSessionAttributeSpec))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(XOnlineMatchSearchResultsLen, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwNumResults), PARAM(psh, dwNumSessionAttributes), PARAM(psh, pSessionAttributeSpec))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(CXo_XOnlineMatchSearchGetResults, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, hTask), PARAM(psh, prgpSearchResults), PARAM(psh, pdwReturnedResults))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(XOnlineMatchSearchGetResults, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hTask), PARAM(psh, prgpSearchResults), PARAM(psh, pdwReturnedResults))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(CXo_XOnlineMatchSessionUpdate, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, SessionID), PARAM(psh, dwPublicCurrent), PARAM(psh, dwPublicAvailable), PARAM(psh, dwPrivateCurrent), PARAM(psh, dwPrivateAvailable), PARAM(psh, dwNumAttributes), PARAM(psh, pAttributes), PARAM(psh, hWorkEvent), PARAM(psh, phTask))),
                    SYM_SIG(4721, 5233)),
    REGISTER_OOVPAS(SYM_FUN(XOnlineMatchSessionUpdate, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, SessionID), PARAM(psh, dwPublicCurrent), PARAM(psh, dwPublicAvailable), PARAM(psh, dwPrivateCurrent), PARAM(psh, dwPrivateAvailable), PARAM(psh, dwNumAttributes), PARAM(psh, pAttributes), PARAM(psh, hWorkEvent), PARAM(psh, phTask))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(CXo_XOnlineMatchSessionCreate, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, dwPublicCurrent), PARAM(psh, dwPublicAvailable), PARAM(psh, dwPrivateCurrent), PARAM(psh, dwPrivateAvailable), PARAM(psh, dwNumAttributes), PARAM(psh, pAttributes), PARAM(psh, hWorkEvent), PARAM(psh, phTask))),
                    SYM_SIG(4721, 5849)),
    REGISTER_OOVPAS(SYM_FUN(XOnlineMatchSessionCreate, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwPublicCurrent), PARAM(psh, dwPublicAvailable), PARAM(psh, dwPrivateCurrent), PARAM(psh, dwPrivateAvailable), PARAM(psh, dwNumAttributes), PARAM(psh, pAttributes), PARAM(psh, hWorkEvent), PARAM(psh, phTask))),
                    SYM_SIG(4721)),
    REGISTER_OOVPAS(SYM_FUN(XoUpdateLaunchNewImageInternal, CALL(std), STACK(12), PARAMS(PARAM(psh, lpTitlePath), PARAM(psh, pLaunchData), PARAM(psh, unkFlags))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(XoUpdateLaunchNewImageInternal, CALL(std), STACK(16), PARAMS(PARAM(psh, lpTitlePath), PARAM(psh, pLaunchData), PARAM(psh, unkFlags), PARAM(psh, pUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5028, 5788)),
};

// ******************************************************************
// * XONLINE_OOVPA
// ******************************************************************
OOVPATableList XONLINE_OOVPA = { XBSDB_ARRAY_SIZE(XONLINE_OOVPA_Table), XONLINE_OOVPA_Table };
