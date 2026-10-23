// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library
//   [LibV] Title Name                       |  Verify   |  Comments
//-------------------------------------------------------------------
// * [3911] Cel Damage                       |   100%    | Contain full library.
// * [4034] Dark Summit                      |   100%    | have 3/10 library.
// * [4039] New Legends                      |   100%    | have 6/10 library.
// * [4134] Double-S.T.E.A.L                 |   100%    | have 9/10 library.
// * [4242] Legends of Wrestling             |   100%    | have 4/10 library.
// * [4361] Umezawa Yukari no Igo Seminar    |   100%    | have 6/11 library.
// * [4432] Sega Soccer Slam                 |   100%    | have 9/11 library.
// * [4531] NHL HITZ 2003                    |   100%    | have 9/11 library.
// * [4627] Rayman Arena                     |   100%    | have 6/11 library.
// * [4721] Terminator - Dawn of Fate        |   100%    | have 10/11 library.
// * [4831] Whacked                          |   100%    | have 9/11 library.
// * [4928] Drihoo                           |   100%    | have 8/11 library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | have 5/11 library.
// * [5120] N.U.D.E.@                        |   100%    | have 8/11 library.
// * [5233] Rayman 3                         |   100%    | have 8/11 library.
// * [5344] Starsky & Hutch                  |   100%    | have 8/11 library.
// * [5455] Dinosaur Hunting                 |   100%    | have 10/11 library.
// * [5558] XIII                             |   100%    | have 9/11 library.
// * [5659] LMA Manager 2004                 |   100%    | have 9/11 library.
// * [5788] All-Star Baseball 2005           |   100%    | have 9/11 library.
// * [5849] Nickelodeon Tak 2                |   100%    | have 9/11 library.

// TODO: Known Xgraphics OOVPA issue list
// * 3911 XGCompressRect is XREF in v1 database, any reason for this?
// * Verification needed: Function Name ( Revision )
//   * XFONT_OpenBitmapFontFromMemory (4432, 4531, 4831, 5120)
//   * XGCompressRect (4034, 4242, 4721, 5028, 5120)
//   * XGIsSwizzledFormat (4034)
//   * XGSetIndexBufferHeader (4034)
//   * XGSetTextureHeader (4034)
//   * XGSetVertexBufferHeader (4034)
//   * XGSwizzleBox (4242)
//   * XGUnswizzleBox (4034, 4134, 4242)
//   * XGWriteSurfaceOrTextureToXPR (4034, 4242, 5028)
// NOTE: Known Xgraphics OOVPA not included in initial revision.
//   * XFONT_OpenBitmapFontFromMemory (4361)

#include "OOVPA_databases.h"

#include "XGraphic/3911.inl"
#include "XGraphic/4134.inl"
#include "XGraphic/4361.inl"

// ******************************************************************
// * XGRAPHC_OOVPA_Table
// ******************************************************************
static OOVPATable XGRAPHC_OOVPA_Table[] = {

    REGISTER_OOVPAS(SYM_FUN(XFONT_OpenBitmapFontFromMemory, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pFontData), PARAM(psh, uFontDataSize), PARAM(psh, ppFont))),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(XGCompressRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pDestBuf), PARAM(psh, DestFormat), PARAM(psh, DestPitch), PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, pSrcData), PARAM(psh, SrcFormat), PARAM(psh, SrcPitch), PARAM(psh, fAlphaRef), PARAM(psh, Flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGIsSwizzledFormat, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Format))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGSetIndexBufferHeader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Length), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, Pool), PARAM(psh, pBuffer), PARAM(psh, Data))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(XGSetSurfaceHeader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Format), PARAM(psh, pSurface), PARAM(psh, Data), PARAM(psh, Pitch))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XGSetTextureHeader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Levels), PARAM(psh, Usage), PARAM(psh, Format), PARAM(psh, Pool), PARAM(psh, pTexture), PARAM(psh, Data), PARAM(psh, Pitch))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGSetVertexBufferHeader, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Length), PARAM(psh, Usage), PARAM(psh, FVF), PARAM(psh, Pool), PARAM(psh, pBuffer), PARAM(psh, Data))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(XGSwizzleBox, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSource), PARAM(psh, RowPitch), PARAM(psh, SlicePitch), PARAM(psh, pBox), PARAM(psh, pDest), PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Depth), PARAM(psh, pPoint), PARAM(psh, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGSwizzleRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSource), PARAM(psh, Pitch), PARAM(psh, pRect), PARAM(psh, pDest), PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, pPoint), PARAM(psh, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGUnswizzleBox, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSource), PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, Depth), PARAM(psh, pBox), PARAM(psh, pDest), PARAM(psh, RowPitch), PARAM(psh, SlicePitch), PARAM(psh, pPoint), PARAM(psh, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGUnswizzleRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pSource), PARAM(psh, Width), PARAM(psh, Height), PARAM(psh, pRect), PARAM(psh, pDest), PARAM(psh, Pitch), PARAM(psh, pPoint), PARAM(psh, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGWriteSurfaceOrTextureToXPR, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pResource), PARAM(psh, cPath), PARAM(psh, bWriteSurfaceAsTexture))),
                    SYM_SIG(3911)),
};

// ******************************************************************
// * XGRAPHC_OOVPA
// ******************************************************************
OOVPATableList XGRAPHC_OOVPA = { XBSDB_ARRAY_SIZE(XGRAPHC_OOVPA_Table), XGRAPHC_OOVPA_Table };
