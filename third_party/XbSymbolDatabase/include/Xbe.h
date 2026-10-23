// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2002 Aaron Robinson <caustik@caustik.com>
// SPDX-FileCopyrightText: 2018 RadWolfie

#pragma once

#include <stdint.h>

#pragma pack(1)

typedef uint32_t p_xbe_string;

// Xbe section header
typedef struct _xbe_s_flags {
    uint32_t bWritable : 1;     // writable flag
    uint32_t bPreload : 1;      // preload flag
    uint32_t bExecutable : 1;   // executable flag
    uint32_t bInsertedFile : 1; // inserted file flag
    uint32_t bHeadPageRO : 1;   // head page read only flag
    uint32_t bTailPageRO : 1;   // tail page read only flag
    uint32_t Unused_a1 : 1;     // unused (or unknown)
    uint32_t Unused_a2 : 1;     // unused (or unknown)
    uint32_t Unused_b1 : 8;     // unused (or unknown)
    uint32_t Unused_b2 : 8;     // unused (or unknown)
    uint32_t Unused_b3 : 8;     // unused (or unknown)
} xbe_s_flags;

#define XBE_SECTION_HEADER_FLAGS_WRITABLE     (1 << 0)
#define XBE_SECTION_HEADER_FLAGS_PRELOAD      (1 << 1)
#define XBE_SECTION_HEADER_FLAGS_EXECUTABLE   (1 << 2)
#define XBE_SECTION_HEADER_FLAGS_INSERTEDFILE (1 << 3)
#define XBE_SECTION_HEADER_FLAGS_HEADPAGERO   (1 << 4)
#define XBE_SECTION_HEADER_FLAGS_TAILPAGERO   (1 << 5)

typedef struct _xbe_section_header {

    union {
        xbe_s_flags dwFlags;
        uint32_t dwFlags_value;
    };

    uint32_t dwVirtualAddr;             // virtual address
    uint32_t dwVirtualSize;             // virtual size
    uint32_t dwRawAddr;                 // file offset to raw data
    uint32_t dwSizeofRaw;               // size of raw data
    const p_xbe_string SectionNameAddr; // section name addr
    uint32_t dwSectionRefCount;         // section reference count
    uint32_t dwHeadSharedRefCountAddr;  // head shared page reference count address
    uint32_t dwTailSharedRefCountAddr;  // tail shared page reference count address
    uint8_t bzSectionDigest[20];        // section digest
} xbe_section_header;
typedef uint32_t p_xbe_section_header;

typedef struct _xbe_certificate {
    uint32_t dwSize;                              // 0x0000 - size of certificate
    uint32_t dwTimeDate;                          // 0x0004 - timedate stamp
    uint32_t dwTitleId;                           // 0x0008 - title id
    uint16_t wszTitleName[40];                    // 0x000C - title name (unicode)
    uint32_t dwAlternateTitleId[0x10];            // 0x005C - alternate title ids
    uint32_t dwAllowedMedia;                      // 0x009C - allowed media types
    uint32_t dwGameRegion;                        // 0x00A0 - game region
    uint32_t dwGameRatings;                       // 0x00A4 - game ratings
    uint32_t dwDiskNumber;                        // 0x00A8 - disk number
    uint32_t dwVersion;                           // 0x00AC - version
    uint8_t bzLanKey[16];                         // 0x00B0 - lan key
    uint8_t bzSignatureKey[16];                   // 0x00C0 - signature key
    uint8_t bzTitleAlternateSignatureKey[16][16]; // 0x00D0 - alternate signature keys // NOTE: NOT ALL XBEs have these fields!
    uint32_t dwOriginalCertificateSize;           // 0x01D0 - Original Certificate Size?
    uint32_t dwOnlineService;                     // 0x01D4 - Online Service ID
    uint32_t dwSecurityFlags;                     // 0x01D8 - Extra Security Flags
    uint8_t bzCodeEncKey[16];                     // 0x01DC - Code Encryption Key?
} xbe_certificate;
typedef uint32_t p_xbe_certificate;

// Xbe library versions
typedef struct _xbe_lv_flags {
    uint16_t QFEVersion : 13; // QFE Version
    uint16_t Approved : 2;    // Approved? (0:no, 1:possibly, 2:yes)
    uint16_t bDebugBuild : 1; // Is this a debug build?
} xbe_lv_flags;
typedef struct _xbe_library_version {
    char szName[8];         // library name
    uint16_t wMajorVersion; // major version
    uint16_t wMinorVersion; // minor version
    uint16_t wBuildVersion; // build version

    union {
        xbe_lv_flags wFlags;
        uint16_t wFlags_value;
    };
} xbe_library_version;
typedef uint32_t p_xbe_library_version;

// Xbe header
typedef struct _xbe_h_InitFlags {
    uint32_t bMountUtilityDrive : 1;  // mount utility drive flag
    uint32_t bFormatUtilityDrive : 1; // format utility drive flag
    uint32_t bLimit64MB : 1;          // limit development kit run time memory to 64mb flag
    uint32_t bDontSetupHarddisk : 1;  // don't setup hard disk flag
    uint32_t Unused : 4;              // unused (or unknown)
    uint32_t Unused_b1 : 8;           // unused (or unknown)
    uint32_t Unused_b2 : 8;           // unused (or unknown)
    uint32_t Unused_b3 : 8;           // unused (or unknown)
} xbe_h_InitFlags;

typedef struct _xbe_header {
    uint32_t dwMagic;                           // 0x0000 - magic number [should be "XBEH"]
    uint8_t pbDigitalSignature[256];            // 0x0004 - digital signature
    uint32_t dwBaseAddr;                        // 0x0104 - base address
    uint32_t dwSizeofHeaders;                   // 0x0108 - size of headers
    uint32_t dwSizeofImage;                     // 0x010C - size of image
    uint32_t dwSizeofImageHeader;               // 0x0110 - size of image header
    uint32_t dwTimeDate;                        // 0x0114 - timedate stamp
    p_xbe_certificate pCertificateAddr;         // 0x0118 - certificate address
    uint32_t dwSections;                        // 0x011C - number of sections
    p_xbe_section_header pSectionHeadersAddr;   // 0x0120 - section headers address
    union {                                     // 0x0124 - initialization flags
        xbe_h_InitFlags dwInitFlags;            //
        uint32_t dwInitFlags_value;             //
    };                                          //
    uint32_t dwEntryAddr;                       // 0x0128 - entry point address
    uint32_t dwTLSAddr;                         // 0x012C - thread local storage directory address
    uint32_t dwPeStackCommit;                   // 0x0130 - size of stack commit
    uint32_t dwPeHeapReserve;                   // 0x0134 - size of heap reserve
    uint32_t dwPeHeapCommit;                    // 0x0138 - size of heap commit
    uint32_t dwPeBaseAddr;                      // 0x013C - original base address
    uint32_t dwPeSizeofImage;                   // 0x0140 - size of original image
    uint32_t dwPeChecksum;                      // 0x0144 - original checksum
    uint32_t dwPeTimeDate;                      // 0x0148 - original timedate stamp
    uint32_t dwDebugPathnameAddr;               // 0x014C - debug pathname address
    uint32_t dwDebugFilenameAddr;               // 0x0150 - debug filename address
    uint32_t dwDebugUnicodeFilenameAddr;        // 0x0154 - debug unicode filename address
    uint32_t dwKernelImageThunkAddr;            // 0x0158 - kernel image thunk address
    uint32_t dwNonKernelImportDirAddr;          // 0x015C - non kernel import directory address
    uint32_t dwLibraryVersions;                 // 0x0160 - number of library versions
    p_xbe_library_version pLibraryVersionsAddr; // 0x0164 - library versions address
    uint32_t dwKernelLibraryVersionAddr;        // 0x0168 - kernel library version address
    uint32_t dwXAPILibraryVersionAddr;          // 0x016C - xapi library version address
    uint32_t dwLogoBitmapAddr;                  // 0x0170 - logo bitmap address
    uint32_t dwSizeofLogoBitmap;                // 0x0174 - logo bitmap size
} xbe_header;
#pragma pack()
