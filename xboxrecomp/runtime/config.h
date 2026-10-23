// Player settings from UserData\Config.toml (written by the launcher); missing keys keep their defaults.
#pragma once
#include <string>

// Xbox pad inputs a keyboard key can drive ([keyboard] <name> = "<key>")
enum PadInput {
    PAD_A, PAD_B, PAD_X, PAD_Y, PAD_BLACK, PAD_WHITE, PAD_LT, PAD_RT, PAD_START, PAD_BACK,
    PAD_UP, PAD_DOWN, PAD_LEFT, PAD_RIGHT, PAD_LCLICK, PAD_RCLICK,
    MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, CAM_UP, CAM_DOWN, CAM_LEFT, CAM_RIGHT,
    PAD_INPUTS
};
extern const char* const g_pad_input_names[PAD_INPUTS];
// The PC controller's buttons a pad input can come from ([gamepad] <name> = "<button>"), in the order of the Xbox
// inputs they stand for by default (RB = Black, LB = White, as the Xbox 360 pad took over the Xbox's layout)
constexpr int PAD_BUTTONS = 16;
extern const char* const g_pad_button_names[PAD_BUTTONS];

struct Config {
    int resolution = 2160;     // [display] resolution: internal height in lines (480 = original); 0 = the screen's
    bool stretch = false;      // [display] aspect = "stretch" fills the window with the 4:3 picture
    float aspect = 0;          // [display] aspect: picture shape, wider than 4:3 shows more at the sides; 0 = the screen's ("auto")
    bool ray_tracing = true;   // [display] ray_tracing: ray-traced ambient occlusion on the 3D world
    int fps = 0;               // [display] fps: 60, or 120 (an in-between picture per game frame); 0 = auto (120 on a 120 Hz screen)
    bool fullscreen = false;   // [display] fullscreen (F11 toggles in game)
    bool show_fps = false;     // [display] show_fps: frame rate in the window title
    int volume = 100;          // [audio] volume, percent (100 = the Xbox level; up to 200, limited)
    int music = 100;           // [audio] music: the music stream's level, percent of the game's own
    int keys[PAD_INPUTS] = {};  // [keyboard]: Windows virtual-key code per input (0 = none)
    int pad[PAD_BUTTONS] = {};  // [gamepad]: the PC controller's button per Xbox button input (index into g_pad_button_names, -1 = none)
};

const Config& config();
// Reads Config.toml again (the in-game menu changed it). Resolution, picture shape and frame rate stay as the
// window and device were made: they change when the game next starts.
void config_reload();
int key_code(const std::string& name);  // "Space", "LShift", "W", "Up", "F1"... -> virtual-key code, 0 if unknown
