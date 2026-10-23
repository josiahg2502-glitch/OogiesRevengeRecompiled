// SPDX-License-Identifier: MIT

// SPDX-FileCopyrightText: 2019 RadWolfie

#include <chrono>
#include <deque>

#include "cliConfig.hpp"

struct pair_str {
    std::string first;
    std::string second;
};

class cli_deque : public std::deque<pair_str> {

    public:
    cli_deque() = default;
    virtual ~cli_deque() = default;

    iterator find(const std::string& search)
    {
        auto i = begin();
        for (; i != end(); i++) {
            if (search == i->first) {
                break;
            }
        }
        return i;
    }

    void update(pair_str pair)
    {
        auto found = find(pair.first);
        if (found == end()) {
            push_back(pair);
            return;
        }

        found->second = pair.second;
    };
};

namespace cli_config {

// ---- Private usage ----

constexpr char str_quote[] = "\"";
constexpr char str_quote_space[] = "\" ";
constexpr char str_space_quote[] = " \"";
constexpr char str_space[] = " ";
constexpr char str_hyphen[] = "-";

cli_deque g_cli_args;

static std::string StripQuotes(std::string input)
{
    if (input.empty()) {
        return input;
    }

    input.erase(std::remove(input.begin(), input.end(), '\"'), input.end());

    return input;
}

argtype_callback argtype_fn = nullptr;

static std::string cliMapPairsToString(cli_deque& map_pairs_out)
{
    std::string to_string;

    auto i = map_pairs_out.begin();
    // If map pairs are empty, return empty string.
    // Or "exec" is not in first iterator by requirement, then return empty string.
    if (i == map_pairs_out.end() || i->first.compare(cli_config::exec)) {
        return to_string;
    }

    to_string += str_quote + i->second + str_quote_space;

    i++;

    // iterate keys to combine into string
    for (; i != map_pairs_out.end();) {
        // If argument has space inside, return as empty.
        size_t found = i->first.find(str_space);
        if (found != std::string::npos) {
            return std::string();
        }
        // If argument has quote inside, return as empty.
        found = i->first.find(str_quote);
        if (found != std::string::npos) {
            return std::string();
        }

        // For internal usage, filepath key will not be use.
        if (!i->first.compare(cli_config::filepath)) {
            // Verify file path is not empty before append.
            if (!i->second.empty()) {
                to_string += str_space_quote + i->second + str_quote;
            }
        }
        // Otherwise check with custom arguments are valid then combine.
        else {
            to_string += str_hyphen + i->first;

            const auto type = argtype_fn(i->first);
            switch (type) {
                case argtype::unknown:
                    [[fallthrough]];
                default:
                    return std::string();
                case argtype::single:
                    // Do nothing, already did this before switch statement.
                    break;
                case argtype::pair:
                    // if value is not set, then include quotes only.
                    if (i->second.empty()) {
                        to_string += std::string(str_space_quote) + str_quote;
                    }
                    else {
                        found = i->second.find(str_space);
                        // If found space inside, then escape with quote.
                        if (found != std::string::npos) {
                            // If argument has quote inside, return as empty.
                            found = i->second.find(str_quote);
                            if (found != std::string::npos) {
                                return std::string();
                            }

                            to_string += str_space_quote + i->second + str_quote;
                        }
                        else {
                            to_string += str_space + i->second;
                        }
                    }
            }
        }

        // If there are more, then add space
        i++;
        if (i != map_pairs_out.end()) {
            to_string += str_space;
        }
    }

    return to_string;
}

static bool inlineMapPair(char** argv, int argc, int& i, cli_deque& map_pairs, const std::string& first)
{
    // Do not allow overwrite argv[0].
    if (!first.compare(cli_config::exec)) {
        return false;
    }

    // Do not allow overwrite filepath.
    if (!first.compare(cli_config::filepath)) {
        return false;
    }

    const auto type = argtype_fn(first);
    switch (type) {
        case argtype::unknown:
            [[fallthrough]];
        default:
            return false;
        case argtype::single:
            map_pairs.update({ first, "" });
            return true;
        case argtype::pair:
            // If the count is at maximum, then simply do empty pair.
            if (i + 1 == argc) {
                map_pairs.update({ first, "" });
            }
            // For precaution, check if we are within range of argc before bind pair
            else if (i + 1 < argc) {
                std::string second = StripQuotes(argv[i + 1]);
                map_pairs.update({ first, second });
                i++;
            }
            return true;
    }
}

static cli_deque cliToMapPairs(char** argv, int argc)
{
    cli_deque map_pairs;

    // Always set first since first argument is the path to executable file.
    map_pairs.push_back({ cli_config::exec, argv[0] });

    for (int i = 1; i < argc; i++) {
        // Check for hyphen to trigger single or pair bind.
        std::string first = StripQuotes(argv[i]);
        if (first.at(0) == str_hyphen[0]) {
            if (first.at(1) != str_hyphen[0]) {
                first = first.substr(1);
            }
            else {
                first = first.substr(2);
            }
            // Check verify if we are able to map single or pair.
            if (!inlineMapPair(argv, argc, i, map_pairs, first)) {
                // Otherwise argument is invalid.
                return cli_deque();
            }
            continue;
        }

        auto found = map_pairs.find(cli_config::filepath);
        if (found == map_pairs.end()) {
            map_pairs.push_back({cli_config::filepath, first});
            continue;
        }

        // Otherwise, let's mark as invalid input
        return cli_deque();
    }
    return map_pairs;
}

// ---- Public usage ----

void SetArgTypeValidateCallback(argtype_callback callback)
{
    argtype_fn = callback;
}

bool GenConfig(char** argv, int argc)
{
    if (!argtype_fn) {
        return false;
    }
    g_cli_args = cliToMapPairs(argv, argc);
    return (g_cli_args.size() != 0);
}

size_t ConfigSize()
{
    return g_cli_args.size();
}

bool GenCMD(std::string& cmd_line_out)
{
    cmd_line_out = cliMapPairsToString(g_cli_args);
    return (cmd_line_out.length() != 0);
}

// Generic check if key exist
bool hasKey(std::string key)
{
    auto found = g_cli_args.find(key);
    if (found != g_cli_args.end()) {
        return true;
    }
    return false;
}

// Generic getter
bool GetValue(const std::string key, std::string* value)
{
    auto found = g_cli_args.find(key);
    if (found != g_cli_args.end() && found->second.length() != 0) {
        if (value != nullptr) {
            *value = found->second;
        }
        return true;
    }

    if (value != nullptr) {
        *value = "";
    }
    return false;
}
bool GetValue(const std::string key, int* value)
{
    auto found = g_cli_args.find(key);
    if (found != g_cli_args.end() && found->second.length() != 0) {
        if (value != nullptr) {
            *value = std::stoi(found->second, nullptr, 10);
        }
        return true;
    }

    if (value != nullptr) {
        *value = 0;
    }
    return false;
}
bool GetValue(const std::string key, long long* value)
{
    auto found = g_cli_args.find(key);
    if (found != g_cli_args.end() && found->second.length() != 0) {
        if (value != nullptr) {
            *value = std::stoll(found->second, nullptr, 10);
        }
        return true;
    }

    if (value != nullptr) {
        *value = 0;
    }
    return false;
}

// Generic setter
void SetValue(const std::string key, const std::string value)
{
    g_cli_args.update({ key, value });
}
void SetValue(const std::string key, const char* value)
{
    SetValue(key, std::string(value));
}
void SetValue(const std::string key, const void* value)
{
    SetValue(key, std::to_string((size_t)value));
}

}
