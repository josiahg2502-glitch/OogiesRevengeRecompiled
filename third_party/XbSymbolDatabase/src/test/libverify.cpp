// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2019 RadWolfie

// Perform detected symbol inspection for any symbols may had been missed or
// not.

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <SimpleIni.h>

#include "libverify.hpp"
#include "libverify/unittest.hpp"

static const std::string pass_str = "PASS";
static const std::string partial_str = "PARTIAL";
static const std::string none_str = "NONE";
static const std::string fail_str = "FAIL";

extern CSimpleIni gen_result;

bool verify_version_range(const std::string& symbol_str,
                          const version_ranges& version_range)
{
    bool ret = true;
    if (version_range.intro_start == VER_NONE &&
        version_range.intro_end == VER_NONE) {
        ret = false;
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, symbol_str + " cannot have VER_NONE in intro range. start= " + std::to_string(version_range.intro_start) + "; end= " + std::to_string(version_range.intro_end));
    }
    else if (version_range.intro_start >= version_range.intro_end) {
        ret = false;
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, symbol_str + " has invalid intro range. start= " + std::to_string(version_range.intro_start) + "; end= " + std::to_string(version_range.intro_end));
    }

    if ((version_range.revive_start == VER_NONE &&
         version_range.revive_end != VER_NONE) ||
        (version_range.revive_start != VER_NONE &&
         version_range.revive_end == VER_NONE) ||
        (version_range.revive_start != VER_NONE &&
         version_range.revive_start >= version_range.revive_end)) {
        ret = false;
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, symbol_str + " has invalid revive range. start= " + std::to_string(version_range.revive_start) + "; end= " + std::to_string(version_range.revive_end));
    }

    return ret;
}

bool within_version_range(const uint16_t lib_version,
                          const version_ranges& version_range)
{
    bool ret = false;
    if (version_range.intro_start <= lib_version &&
        lib_version < version_range.intro_end) {
        ret = true;
    }
    else if (version_range.revive_start != VER_NONE &&
             version_range.revive_start <= lib_version &&
             lib_version < version_range.revive_end) {
        ret = true;
    }
    return ret;
}

bool match_library_db(std::map<uint32_t, symbol_result>& list,
                      const uint16_t lib_version,
                      const std::string lib_subcategory_str,
                      const library_list* lib_db,
                      uint32_t xref_offset,
                      uint32_t xref_total,
                      const uint32_t lib_flags,
                      std::vector<std::string>& missing,
                      size_t& error_count,
                      bool bOptional = false)
{
    size_t lib_db_size = lib_db->size();
    size_t found_size = 0;

    // Search registered symbols from unit test's database.
    for (library_list::const_iterator xref = lib_db->begin();
         xref != lib_db->end();
         xref++) {

        // Skip if not within xref range
        if (xref->first < xref_offset ||
            xref->first >= xref_total + xref_offset) {
            lib_db_size--;
            // Handled inside verify_database_xref_range function.
            continue;
        }

        // If group of the symbols' range is bad, the function will output
        // error(s) then skip given symbol to verify.
        bool skip_verify = false;
        for (auto&& [symbol_str, version_range] : xref->second) {
            if (!verify_version_range(symbol_str, version_range)) {
                error_count++;
                skip_verify = true;
                continue;
            }
        }
        if (skip_verify) {
            continue;
        }

        bool within_range = false;
        for (auto&& [symbol_str, version_range] : xref->second) {
            if (within_version_range(lib_version, version_range)) {
                within_range = true;
            }
        }
        auto found_xref = list.find(xref->first);
        // If not within range, then verify if xref is also not found.
        if (!within_range) {
            lib_db_size--;
            // If xref is found, then we need to report it.
            if (found_xref != list.end()) {
                error_count++;
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, found_xref->second.symbol + " (b" + std::to_string(found_xref->second.build) + ") is detected!");
            }
            continue;
        }

        // Since xref is within range, check if symbol is found.
        // If a match is not found, then we need to push the generic symbol
        // name into missing list.
        if (found_xref == list.end()) {
            missing.push_back(XbSDB_SymbolReferenceToString(xref->first));
            continue;
        }

        auto found_str = xref->second.find(found_xref->second.symbol);

        if (found_str == xref->second.end()) {
            /*
            // Handled by missing_library_db, so we just skip it.
            // Although, somehow D3D_DestroyResource symbol didn't show up if
            not in entry? Why?
            std::cout << "ERROR: Symbol is missing from unit
            test's database: "
                      << found_xref->second.symbol
                      << "\n";
            error_count++;
            */
            continue;
        }

        // Skip if not matched library.
        if ((found_xref->second.library_flag & lib_flags) == 0) {
            continue;
        }
        found_size++;
        gen_result.SetLongValue(lib_subcategory_str.c_str(),
                                found_xref->second.symbol.c_str(),
                                found_xref->second.addr,
                                nullptr,
                                true);
#ifdef _VERBOSE // Output which symbol is detected.
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_INFO, found_xref->second.symbol + " (b" + std::to_string(found_xref->second.build) + ") found!");
#endif
    }

    if (found_size == 0) {
        // Force fail if symbols in subcategory doesn't exist in earlier XDK builds.
        if (lib_db_size == 0) {
            XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_INFO, "Symbols in subcategory does not exist.");
            return false;
        }
        // Force fail since some subcategories doesn't exist until later XDK build revisions.
        else if (missing.empty() && !bOptional) {
            XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "None of symbols are recognized!");
            return false;
        }
    }

#ifdef _VERBOSE
    XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_INFO, "Actual= " + std::to_string(lib_db->size()) + "; Current= " + std::to_string(lib_db_size) + "; Found= " + std::to_string(found_size));
#endif

    return found_size == lib_db_size;
}

void missing_library_db(std::map<uint32_t, symbol_result>& list,
                        const library_db& lib_db,
                        const uint32_t lib_flags,
                        size_t& error_count)
{
    // Report missing symbol registrations
    for (auto&& [xref_index, xref_entry] : list) {

        unsigned match_found = 0;
        for (const auto& subcategory : lib_db.subcategories) {
            if (subcategory->optional) {
                // If check xref register is missing
                auto found_xref = subcategory->optional->find(xref_index);
                if (found_xref != subcategory->optional->end()) {
                    // If check unregistered symbol is missing
                    auto found_str = found_xref->second.find(xref_entry.symbol);
                    if (found_str != found_xref->second.end()) {
                        match_found++;
                    }
                }
            }

            if (subcategory->min) {
                // If check xref register is missing
                auto found_xref = subcategory->min->find(xref_index);
                if (found_xref != subcategory->min->end()) {
                    // If check unregistered symbol is missing
                    auto found_str = found_xref->second.find(xref_entry.symbol);
                    if (found_str != found_xref->second.end()) {
                        match_found++;
                    }
                }
            }

            if (subcategory->full) {
                // If check xref register is missing
                auto found_xref = subcategory->full->find(xref_index);
                if (found_xref != subcategory->full->end()) {
                    // If check symbol register is missing
                    auto found_str = found_xref->second.find(xref_entry.symbol);
                    if (found_str != found_xref->second.end()) {
                        match_found++;
                    }
                }
            }
        }

        // Skip if not matched library.
        if ((xref_entry.library_flag & lib_flags) == 0) {
            if (match_found) {
                error_count++;
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Symbol is not registered in right place: " + xref_entry.symbol);
            }
            continue;
        }

        // Skip if not within range
        if (xref_index < lib_db.xref_offset ||
            xref_index >= lib_db.xref_total + lib_db.xref_offset) {
            // Handled inside verify_database_xref_range function.
            continue;
        }

        if (match_found) {
            continue;
        }


        error_count++;
        std::stringstream toHexStr;
        toHexStr << std::hex << xref_entry.addr;
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Unit test is missing " + xref_entry.symbol + " (b" + std::to_string(xref_entry.build) + ") symbol register! addr = 0x" + toHexStr.str());
    }
}

void verify_database_duplicate_compare(const char* lib_str,
                                       const uint32_t xref_index,
                                       const std::string xref_symbol,
                                       const library_list* db1,
                                       const library_list* db2,
                                       const library_list* db3,
                                       size_t& error_count)
{
    unsigned match_found = 0;

    if (db1) {
        // If check xref register exist
        const auto& lib_db_scan = *db1;
        auto found_xref = lib_db_scan.find(xref_index);
        if (found_xref != lib_db_scan.end()) {
            match_found++;
        }
    }

    if (db2) {
        // If check xref register exist
        const auto& lib_db_scan = *db2;
        auto found_xref = lib_db_scan.find(xref_index);
        if (found_xref != lib_db_scan.end()) {
            match_found++;
        }
    }

    if (db3) {
        // If check xref register exist
        const auto& lib_db_scan = *db3;
        auto found_xref = lib_db_scan.find(xref_index);
        if (found_xref != lib_db_scan.end()) {
            match_found++;
        }
    }

    // If there are duplicate match, then shame on contributor for doing
    // paste and not update new entry or making duplicate entries.
    if (match_found) {
        error_count++;
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Duplicate symbol registers detected from different database: " + xref_symbol + " (index: " + std::to_string(xref_index) + "), counter: " + std::to_string(match_found-1));
    }
}

void verify_database_duplicate_internal(const library_list* db,
    size_t& error_count)
{
    if (db) {
        for (auto unique_key = db->begin(); unique_key != db->end();) {
            const auto& xref_index = unique_key->first;
            const auto& xref_entry_str = unique_key->second.begin()->first;
            const auto& counter = db->count(xref_index);
            if (counter > 1) {
                error_count++;
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Duplicate symbol registers detected from same database: " + xref_entry_str + " (index: " + std::to_string(xref_index) + "), counter: " + std::to_string(counter-1));
            }
            // Skip duplicate keys, if found, to avoid repeat same message.
            unique_key = db->equal_range(xref_index).second;
        }
    }
}

// Make sure there are no duplicate xref entries from same library.
void verify_database_duplicate(const char* lib_str,
                               const library_db& lib_db,
                               size_t& error_count)
{
    for (const auto& subcategory_i : lib_db.subcategories) {

        verify_database_duplicate_internal(subcategory_i->optional, error_count);
        verify_database_duplicate_internal(subcategory_i->min, error_count);
        verify_database_duplicate_internal(subcategory_i->full, error_count);

        bool bFound = false;
        for (const auto& subcategory_ii : lib_db.subcategories) {
            // Skip if iterators aren't matched
            if (subcategory_i == subcategory_ii) {
                bFound = true;
            }
            if (!bFound) {
                continue;
            }
            // Start inspection once both iterators are matched and check second iterator.
            auto optional = subcategory_ii->optional;
            if (subcategory_i == subcategory_ii) {
                optional = nullptr;
            }
            if (subcategory_i->optional) {
                for (auto&& [xref_index, xref_entry] : *subcategory_i->optional) {
                    const std::string xref_symbol = xref_entry.begin()->first;

                    verify_database_duplicate_compare(lib_str, xref_index, xref_symbol, optional, subcategory_ii->min, subcategory_ii->full, error_count);
                }
            }

            auto min = subcategory_ii->min;
            if (subcategory_i == subcategory_ii) {
                min = nullptr;
            }
            if (subcategory_i->min) {
                for (auto&& [xref_index, xref_entry] : *subcategory_i->min) {
                    const std::string xref_symbol = xref_entry.begin()->first;

                    verify_database_duplicate_compare(lib_str, xref_index, xref_symbol, optional, min, subcategory_ii->full, error_count);
                }
            }

            auto full = subcategory_ii->full;
            if (subcategory_i == subcategory_ii) {
                full = nullptr;
            }
            if (subcategory_i->full) {
                for (auto&& [xref_index, xref_entry] : *subcategory_i->full) {
                    const std::string xref_symbol = xref_entry.begin()->first;

                    verify_database_duplicate_compare(lib_str, xref_index, xref_symbol, optional, min, full, error_count);
                }
            }
            // There's no need to verify subcategory->full with previous databases.
        }
    }

}

void verify_database_xref_range_compare(const library_list* lib_list,
                       const unsigned xref_min,
                       const unsigned xref_max,
                       size_t& error_count)
{
    if (lib_list) {
        for (auto&& [xref_index, xref_entry] : *lib_list) {
            // Report if not within library's xref range
            if (xref_index < xref_min ||
                xref_index >= xref_max) {
                error_count++;
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Reference index is not within range:" + xref_entry.begin()->first);
            }
        }
    }
}

// Check each xref indexes are within library's xref range.
void verify_database_xref_range(const char* lib_str,
                                const library_db& lib_db,
                                size_t& error_count)
{
    auto xref_min = lib_db.xref_offset;
    auto xref_max = lib_db.xref_total + xref_min;

    for (const auto& subcategory : lib_db.subcategories) {
        verify_database_xref_range_compare(subcategory->optional, xref_min, xref_max, error_count);
        verify_database_xref_range_compare(subcategory->min, xref_min, xref_max, error_count);
        verify_database_xref_range_compare(subcategory->full, xref_min, xref_max, error_count);
    }
}

void run_test_verify_library(const char* lib_str,
                              const library_db& lib_db,
                              size_t& error_count)
{
    size_t error_count_local = 0;
    verify_database_duplicate(lib_str, lib_db, error_count_local);
    verify_database_xref_range(lib_str, lib_db, error_count_local);

    // Get library's databases size.
    size_t lib_size = 0;
    for (const auto& subcategory : lib_db.subcategories) {
        if (subcategory->optional) {
            lib_size += subcategory->optional->size();
        }
        if (subcategory->min) {
            lib_size += subcategory->min->size();
        }
        if (subcategory->full) {
            lib_size += subcategory->full->size();
        }
    }
    // Make sure both libXbSymbolDatabase and unit test's databases has correct size.
    if ((lib_db.xref_total - lib_db.xref_exclude) != lib_size) {
        error_count_local++;
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, std::string(lib_str) + " (size: " + std::to_string(lib_size) + ") database is not in sync with libXbSymbolDatabase's (size: " + std::to_string(lib_db.xref_total - lib_db.xref_exclude) + ")!");
    }

    // Make verbose for exclude count.
    if (lib_db.xref_exclude) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_DEBUG, std::string(lib_str) + " has exclude " + std::to_string(lib_db.xref_exclude) + " xref(s).");
        std::cout << "\n";
    }
    else if (error_count_local) {
        std::cout << "\n";
    }

    error_count += error_count_local;
}

bool run_test_verify_libraries()
{
    size_t error_count = 0;
    library_db lib_db;
    getLibraryD3D8(lib_db);
    run_test_verify_library(LIB_D3D8, lib_db, error_count);

    getLibraryDSOUND(lib_db);
    run_test_verify_library(LIB_DSOUND, lib_db, error_count);

    getLibraryJVS(lib_db);
    run_test_verify_library(LIB_JVS, lib_db, error_count);

    getLibraryXACTENG(lib_db);
    run_test_verify_library(LIB_XACTENG, lib_db, error_count);

    getLibraryXAPILIB(lib_db);
    run_test_verify_library(LIB_XAPILIB, lib_db, error_count);

    getLibraryXGRAPHIC(lib_db);
    run_test_verify_library(LIB_XGRAPHC, lib_db, error_count);

    getLibraryXNET(lib_db);
    run_test_verify_library(LIB_XNET, lib_db, error_count);

    getLibraryXONLINE(lib_db);
    run_test_verify_library(LIB_XONLINE, lib_db, error_count);

    if (error_count) {
        return false;
    }

    return true;
}

template <bool required = true>
static bool run_test_output_results(const bool is_match,
                                    const std::vector<std::string>& symbols_missing,
                                    const std::string& lib_subcategory)
{
    if (!is_match) {
        for (auto& symbol : symbols_missing) {
            XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Title is missing one of " + symbol);
        }
        if (symbols_missing.empty()) {
            Custom_OutputMessage(XB_OUTPUT_MESSAGE_INFO, results_str, lib_subcategory, none_str);
            std::cout << "\n";
        }
        else {
            Custom_OutputMessage(XB_OUTPUT_MESSAGE_INFO, results_str, lib_subcategory, required ? fail_str : partial_str);
            std::cout << "\n";
        }
    }
    else {
        Custom_OutputMessage(XB_OUTPUT_MESSAGE_INFO, results_str, lib_subcategory, pass_str);
        std::cout << "\n";
        return true;
    }
    return false;
}

void run_test_verify_symbol(std::map<uint32_t, symbol_result>& symbols_list,
                            const char* lib_str,
                            const uint16_t lib_ver,
                            const uint32_t lib_flags,
                            const library_db& lib_db,
                            unsigned& full_lib_count,
                            size_t& error_count)
{
    std::vector<std::string> symbols_missing;
    bool is_match;
    bool lib_passed;

    if (lib_ver == 0) {
        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, std::string(lib_str) + " is not detected, skipping...");
        std::cout << "\n";
        return;
    }

    missing_library_db(symbols_list, lib_db, lib_flags, error_count);

    if (lib_db.subcategories.empty()) {
        error_count++;
        XbSUT_OutputMessage<true>(XB_OUTPUT_MESSAGE_ERROR, std::string(lib_str) + "'s database does not have any subcategories, skipping...");
        std::cout << "\n";
        return;
    }

    std::string library_prefix = std::string(lib_str) + " (";
    for (const auto& subcategory : lib_db.subcategories) {
        if (subcategory->optional != nullptr) {
            symbols_missing.clear();
            size_t error_count_local = 0;
            std::string lib_subcategory = library_prefix + subcategory->name +")";
            is_match = match_library_db(symbols_list, lib_ver, lib_subcategory, subcategory->optional, lib_db.xref_offset, lib_db.xref_total, lib_flags, symbols_missing, error_count_local, true);

            lib_subcategory += " optional";
            (void)run_test_output_results<false>(is_match, symbols_missing, lib_subcategory);
        }

        if (subcategory->min != nullptr) {

            symbols_missing.clear();
            std::string lib_subcategory = library_prefix + subcategory->name + ")";
            is_match = match_library_db(symbols_list, lib_ver, lib_subcategory, subcategory->min, lib_db.xref_offset, lib_db.xref_total, lib_flags, symbols_missing, error_count);

            lib_subcategory += " min";
            lib_passed = run_test_output_results(is_match, symbols_missing, lib_subcategory);
            if (!lib_passed && !symbols_missing.empty()) {
                continue;
            }
        }

        std::string lib_subcategory = library_prefix + subcategory->name + ")";
        if (subcategory->full == nullptr) {
            XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_WARN, lib_subcategory + " db is missing, skipping...");
            std::cout << "\n";
            continue;
        }
        symbols_missing.clear();
        is_match = match_library_db(symbols_list, lib_ver, lib_subcategory, subcategory->full, lib_db.xref_offset, lib_db.xref_total, lib_flags, symbols_missing, error_count);

        lib_subcategory += " full";
        lib_passed = run_test_output_results(is_match, symbols_missing, lib_subcategory);
        if (!lib_passed) {
            continue;
        }
        full_lib_count++;
    }
}

void run_test_verify_symbols(lib_versions& lib_vers,
                             std::map<uint32_t, symbol_result>& symbols_list,
                             unsigned& full_lib_count,
                             size_t& error_count)
{
    library_db lib_db;

    getLibraryD3D8(lib_db);
    if (lib_vers.d3d8ltcg) {
        constexpr auto XBSDBLIB_D3D8LTCG_flags =
            XBSDBLIB_D3D8LTCG | XBSDBLIB_D3D8;
        run_test_verify_symbol(symbols_list, LIB_D3D8LTCG, lib_vers.d3d8ltcg, XBSDBLIB_D3D8LTCG_flags, lib_db, full_lib_count, error_count);
    }
    else {
        run_test_verify_symbol(symbols_list, LIB_D3D8, lib_vers.d3d8, XBSDBLIB_D3D8, lib_db, full_lib_count, error_count);
    }

    getLibraryDSOUND(lib_db);
    run_test_verify_symbol(symbols_list, LIB_DSOUND, lib_vers.dsound, XBSDBLIB_DSOUND, lib_db, full_lib_count, error_count);

    getLibraryJVS(lib_db);
    run_test_verify_symbol(symbols_list, LIB_JVS, lib_vers.jvs, XBSDBLIB_JVS, lib_db, full_lib_count, error_count);

    getLibraryXACTENG(lib_db);
    run_test_verify_symbol(symbols_list, LIB_XACTENG, lib_vers.xacteng, XBSDBLIB_XACTENG, lib_db, full_lib_count, error_count);

    getLibraryXAPILIB(lib_db);
    run_test_verify_symbol(symbols_list, LIB_XAPILIB, lib_vers.xapilib, XBSDBLIB_XAPILIB, lib_db, full_lib_count, error_count);

    getLibraryXGRAPHIC(lib_db);
    run_test_verify_symbol(symbols_list, LIB_XGRAPHC, lib_vers.xgraphic, XBSDBLIB_XGRAPHC, lib_db, full_lib_count, error_count);

    getLibraryXNET(lib_db);
    constexpr auto XBSDBLIB_XNET_flags =
        XBSDBLIB_XNET | XBSDBLIB_XNETS | XBSDBLIB_XNETN |
        XBSDBLIB_XONLINE | XBSDBLIB_XONLINEN | XBSDBLIB_XONLINES | XBSDBLIB_XONLINLS;
    run_test_verify_symbol(symbols_list, LIB_XNET, lib_vers.xnet, XBSDBLIB_XNET_flags, lib_db, full_lib_count, error_count);

    getLibraryXONLINE(lib_db);
    constexpr auto XBSDBLIB_XONLINE_flags =
        XBSDBLIB_XONLINE | XBSDBLIB_XONLINEN | XBSDBLIB_XONLINES | XBSDBLIB_XONLINLS;
    run_test_verify_symbol(symbols_list, LIB_XONLINE, lib_vers.xonline, XBSDBLIB_XONLINE_flags, lib_db, full_lib_count, error_count);
}
