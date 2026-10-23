// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2018 Luke Usher <luke.usher@outlook.com>
// SPDX-FileCopyrightText: 2018 ergo720

#pragma once

#include <cuchar> // for std::c16rtomb
#include <climits> // for MB_LEN_MAX

// made by Luke Usher and ergo720
static std::string FormatTitleId(uint32_t title_id)
{
    std::stringstream ss;

    // If the Title ID prefix is a printable character, parse it
    // This shows the correct game serial number for retail titles!
    // EG: MS-001 for 1st tile published by MS, EA-002 for 2nd title by EA, etc
    // Some special Xbes (Dashboard, XDK Samples) use non-alphanumeric serials
    // We fall back to Hex for those
    // ergo720: we cannot use isalnum() here because it will treat chars in the
    // range -1 - 255 as valid ascii chars which can lead to unicode characters
    // being printed in the title (e.g.: dashboard uses 0xFE and 0xFF)
    uint8_t pTitleId1 = (title_id >> 24) & 0xFF;
    uint8_t pTitleId2 = (title_id >> 16) & 0xFF;

    if ((pTitleId1 < 65 || pTitleId1 > 90) ||
        (pTitleId2 < 65 || pTitleId2 > 90)) {
        // Prefix was non-printable, so we need to print a hex reprentation of
        // the entire title_id
        ss << std::setfill('0') << std::setw(8) << std::hex << std::uppercase
           << title_id;
        return ss.str();
    }

    ss << pTitleId1 << pTitleId2;
    ss << "-";
    ss << std::setfill('0') << std::setw(3) << std::dec
       << (title_id & 0x0000FFFF);

    return ss.str();
}

// made by ergo720
static void PurgeBadChar(std::string& s,
                         const std::string& illegalChars = "\\/:?\"<>|")
{
    for (auto it = s.begin(); it < s.end(); ++it) {
        bool found = illegalChars.find(*it) != std::string::npos;
        if (found) {
            *it = '_';
        }
    }
}

static const std::string getXbeHeaderHash(const void* pXbeHeader)
{
    uint64_t uiHash = XXH3_64bits(pXbeHeader, sizeof(xbe_header));
    std::stringstream toHexStr;
    toHexStr << std::hex << uiHash;
    return toHexStr.str();
}

// made by RadWolfie
static const std::string getXbeTitle(const xbe_header* pXbeHeader)
{
    size_t xb_start_addr =
        reinterpret_cast<size_t>(pXbeHeader) - pXbeHeader->dwBaseAddr;
    xbe_certificate* pCertificate = nullptr;

    if (pXbeHeader->pCertificateAddr) {
        pCertificate = reinterpret_cast<xbe_certificate*>(
            xb_start_addr + pXbeHeader->pCertificateAddr);
    }

    size_t titleMaxLength = sizeof(pCertificate->wszTitleName) / sizeof(uint16_t);
    if (pCertificate) {
        std::mbstate_t state{};
        char output[MB_LEN_MAX]{};
        std::string tTitleName;
        for (size_t i = 0; i < titleMaxLength; i++) {
            // check for null terminator, if one existed then exit loop
            if (pCertificate->wszTitleName[i] == 0) {
                break;
            }
            size_t length = std::c16rtomb(output, pCertificate->wszTitleName[i], &state);
            // if unable to convert utf16 to utf8, then exit loop
            if (length == 0 || length > MB_LEN_MAX) {
                break;
            }
            else {
                // append utf8 character to string
                for (size_t ii = 0; ii < length; ii++) {
                    tTitleName += output[ii];
                }
            }
        }
        // return title name if it is not empty
        if (!tTitleName.empty()) {
            return tTitleName;
        }
    }
    // otherwise, return as unknown string
    return "Unknown";
}

static constexpr uint32_t FourCC(char const c[5])
{
    return (c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3];
}

// made by RadWolfie
static const std::string FormatGameRegion(uint32_t game_region)
{
    constexpr uint32_t GAME_REGION_CODE_MASK = 0x7;
    constexpr uint32_t GAME_REGION_MANUFACTURING = 0x80000000;
    constexpr uint32_t GAME_REGION_VALID_MASK = GAME_REGION_CODE_MASK | GAME_REGION_MANUFACTURING;
    if (game_region & ~GAME_REGION_VALID_MASK) {
        return "REGION ERROR";
    }
    const struct RegionList {
        std::string Code;
        std::string Name;
    } Regions[] = {
        { "?", "Unknown" },
        { "A", "NTSC" },
        { "J", "JAPAN" },
        { "K", "NTSC+JAPAN" },
        { "E", "PAL" },
        { "L", "PAL+NTSC" },
        { "?", "PAL+JAPAN" },
        { "W", "Region Free" }
    };
    const RegionList& region_struct = Regions[game_region & GAME_REGION_CODE_MASK];
    std::string output = region_struct.Code + " (" + region_struct.Name + ")";
    if (game_region & GAME_REGION_MANUFACTURING) {
        output += " (DEBUG)";
    }
    return output;
}

// made by Luke Usher
static const std::string FormatVersion(uint32_t version)
{
    return std::to_string(version & 0xFF) + "." + std::to_string((version & 0xFFFFFF00) >> 8);
}
