// UserData\Config.toml: [section] / key = value lines (strings, numbers, booleans), as the launcher writes them.
#include "config.h"

#include <windows.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>

const char* const g_pad_input_names[PAD_INPUTS] = {
    "a", "b", "x", "y", "black", "white", "left_trigger", "right_trigger", "start", "back",
    "dpad_up", "dpad_down", "dpad_left", "dpad_right", "left_stick_click", "right_stick_click",
    "move_up", "move_down", "move_left", "move_right", "camera_up", "camera_down", "camera_left", "camera_right",
};

const char* const g_pad_button_names[PAD_BUTTONS] = {
    "A", "B", "X", "Y", "RB", "LB", "LT", "RT", "Start", "Back", "Up", "Down", "Left", "Right", "LS", "RS",
};

// the same defaults the launcher shows; like the other ports: WASD move, arrows camera
static const char* const g_default_keys[PAD_INPUTS] = {
    "Space", "LShift", "R", "F", "1", "2", "Q", "E", "Enter", "Tab",
    "I", "K", "J", "L", "LCtrl", "C",
    "W", "S", "A", "D", "Up", "Down", "Left", "Right",
};

int key_code(const std::string& name) {
    static const struct { const char* name; int vk; } named[] = {
        {"Space", VK_SPACE}, {"Enter", VK_RETURN}, {"Tab", VK_TAB}, {"Escape", VK_ESCAPE}, {"Backspace", VK_BACK},
        {"LShift", VK_LSHIFT}, {"RShift", VK_RSHIFT}, {"LCtrl", VK_LCONTROL}, {"RCtrl", VK_RCONTROL},
        {"LAlt", VK_LMENU}, {"RAlt", VK_RMENU}, {"Up", VK_UP}, {"Down", VK_DOWN}, {"Left", VK_LEFT}, {"Right", VK_RIGHT},
        {"Insert", VK_INSERT}, {"Delete", VK_DELETE}, {"Home", VK_HOME}, {"End", VK_END}, {"PageUp", VK_PRIOR},
        {"PageDown", VK_NEXT}, {"Comma", VK_OEM_COMMA}, {"Period", VK_OEM_PERIOD}, {"Slash", VK_OEM_2},
        {"Semicolon", VK_OEM_1}, {"Quote", VK_OEM_7}, {"LBracket", VK_OEM_4}, {"RBracket", VK_OEM_6},
        {"Minus", VK_OEM_MINUS}, {"Equals", VK_OEM_PLUS}, {"Backslash", VK_OEM_5}, {"Backquote", VK_OEM_3},
    };
    for (auto& n : named)
        if (_stricmp(n.name, name.c_str()) == 0) return n.vk;
    if (name.size() == 1 && std::isalnum(u_char(name[0]))) return std::toupper(u_char(name[0]));  // letters and digits
    if (name.size() >= 2 && (name[0] == 'F' || name[0] == 'f')) {
        int n = std::atoi(name.c_str() + 1);
        if (n >= 1 && n <= 12 && n != 10 && n != 11) return VK_F1 + n - 1;  // F10/F11 belong to the window
    }
    if (name.size() >= 4 && _strnicmp(name.c_str(), "Num", 3) == 0 && std::isdigit(u_char(name[3]))) return VK_NUMPAD0 + name[3] - '0';
    return 0;
}

static std::string trim(std::string s) {
    size_t a = s.find_first_not_of(" \t\r"), b = s.find_last_not_of(" \t\r");
    return a == std::string::npos ? "" : s.substr(a, b - a + 1);
}

static Config load() {
    Config c;
    for (int k = 0; k < PAD_INPUTS; ++k) c.keys[k] = key_code(g_default_keys[k]);
    for (int k = 0; k < PAD_BUTTONS; ++k) c.pad[k] = k;
    std::ifstream in("UserData\\Config.toml");
    std::string line, section;
    while (std::getline(in, line)) {
        bool quoted = false;  // a '#' outside quotes starts a comment
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '"' || line[i] == '\'') quoted = !quoted;
            if (line[i] == '#' && !quoted) {
                line.resize(i);
                break;
            }
        }
        line = trim(line);
        if (line.empty()) continue;
        if (line.front() == '[' && line.back() == ']') {
            section = trim(line.substr(1, line.size() - 2));
            continue;
        }
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = trim(line.substr(0, eq)), v = trim(line.substr(eq + 1));
        if (v.size() >= 2 && (v.front() == '"' || v.front() == '\'') && v.back() == v.front()) v = v.substr(1, v.size() - 2);
        bool yes = v == "true" || v == "1";
        if (section == "display") {
            if (key == "resolution") {  // "4k", "1440p", "1080p", "720p", "original", "screen" or a number of lines
                if (v == "screen") c.resolution = 0;
                else if (v == "4k" || v == "4K") c.resolution = 2160;
                else if (v == "original") c.resolution = 480;
                else if (int n = std::atoi(v.c_str()); n >= 480 && n <= 4320) c.resolution = n;
            } else if (key == "aspect") {  // "auto" (the screen's), "4:3", "16:9", "21:9", "32:9"... or "stretch"
                float w = 0, h = 0;
                c.stretch = v == "stretch";
                if (c.stretch) c.aspect = 4.f / 3;
                else if (std::sscanf(v.c_str(), "%f:%f", &w, &h) == 2 && w > 0 && h > 0) c.aspect = std::clamp(w / h, 4.f / 3, 4.f);
                else c.aspect = 0;
            } else if (key == "ray_tracing") {
                c.ray_tracing = yes;
            } else if (key == "fps") {  // "auto", "60" or "120"
                c.fps = v == "60" ? 60 : v == "120" ? 120 : 0;
            } else if (key == "fullscreen") {
                c.fullscreen = yes;
            } else if (key == "show_fps") {
                c.show_fps = yes;
            }
        } else if (section == "audio" && (key == "volume" || key == "music")) {
            int n = std::atoi(v.c_str());
            (key == "music" ? c.music : c.volume) = n < 0 ? 0 : n > 200 ? 200 : n;
        } else if (section == "gamepad") {
            for (int k = 0; k < PAD_BUTTONS; ++k)
                if (key == g_pad_input_names[k]) {
                    c.pad[k] = -1;  // "none", or a name not known
                    for (int b = 0; b < PAD_BUTTONS; ++b)
                        if (_stricmp(v.c_str(), g_pad_button_names[b]) == 0) c.pad[k] = b;
                }
        } else if (section == "keyboard") {
            for (int k = 0; k < PAD_INPUTS; ++k)
                if (key == g_pad_input_names[k]) c.keys[k] = v.empty() || v == "none" ? 0 : key_code(v);
        }
    }
    return c;
}

static Config& live() {
    static Config c = load();
    return c;
}
const Config& config() { return live(); }

void config_reload() {
    Config c = load();
    const Config& was = live();
    c.resolution = was.resolution, c.aspect = was.aspect, c.stretch = was.stretch, c.fps = was.fps;
    live() = c;
}
