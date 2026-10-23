// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2019 RadWolfie

#pragma once

#include <string>

// Command Line Interface functions

namespace cli_config {

// Reserved arguments:
static constexpr char exec[] = "exec";
static constexpr char filepath[] = "filepath";

enum class argtype {
    unknown = 0,
    single,
    pair
};

typedef argtype (*argtype_callback)(const std::string& arg);

void SetArgTypeValidateCallback(argtype_callback callback);

// Please call SetArgTypeValidateCallback first before call GenConfig.
bool GenConfig(char** argv, int argc);
size_t ConfigSize();
bool GenCMD(std::string& cmd_line_out);

// Generic check if key exist
bool hasKey(const std::string key);
// Generic getter
bool GetValue(const std::string key, std::string* value);

void SetValue(const std::string key, const std::string value);
void SetValue(const std::string key, const char* value);
void SetValue(const std::string key, const void* value);
template<class T>
static void SetValue(const std::string key, const T value)
{
    SetValue(key, std::to_string(value));
}

}
