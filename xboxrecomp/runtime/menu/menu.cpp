// The game's own menu (see menu.h). Everything on screen is the game's art, read from the player's disc:
// - the Spiral Hill painting (omake gallery), with the pause menu's mist drifting over it
// - the title logo (title_u.stm), the subtitle font and the loading scarecrow (default.xbe)
// - the pause menu's hook cursor, frames and vine, and the button glyphs and words of its prompts (sbuty_u.stm)
// It is drawn on a canvas 720 lines tall on the CPU and shown with gfx_show_canvas in the window the game then takes over.
// In game (F1) the same menu is drawn over the frame the game last showed, blurred and dimmed, instead of the painting.
#include "menu.h"

#include <windows.h>
#include <commdlg.h>
#include <shellapi.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "../config.h"
#include "../d3d8/renderer.h"
#include "../audio/audio_out.h"
#include "../x86.h"
#include "disc.h"
#include "menu_art.h"

void input_start();
bool pad_read(u16& buttons, s16& lx, s16& ly);
bool pad_controls(u8 out[PAD_BUTTONS]);

namespace {

int W = 1280;  // 16:9 before the game; in game, the shape of the game's picture
constexpr int H = 720;
constexpr uint32_t kText = 0xFFE2DED2, kDim = 0xFF96928C, kHot = 0xFFFFC45C, kValue = 0xFFBEBAB0;
const std::string kStm = "Disc/files/stm_data/";

// ---- the canvas ----
struct Canvas {
    std::vector<uint32_t> px = std::vector<uint32_t>(size_t(W) * H, 0xFF000000u);
    // straight-alpha "over"; tint multiplies the colour, opacity the alpha
    void blend(const Image& img, int x, int y, uint32_t tint = 0xFFFFFFFFu, float opacity = 1.f) {
        const float tr = ((tint >> 16) & 255) / 255.f, tg = ((tint >> 8) & 255) / 255.f, tb = (tint & 255) / 255.f;
        for (int j = std::max(0, -y); j < img.h && y + j < H; ++j)
            for (int i = std::max(0, -x); i < img.w && x + i < W; ++i) {
                uint32_t s = img.px[size_t(j) * img.w + i];
                float a = float(s >> 24) / 255.f * opacity;
                if (a <= 0.004f) continue;
                uint32_t& d = px[size_t(y + j) * W + x + i];
                float r = ((s >> 16) & 255) * tr, g = ((s >> 8) & 255) * tg, b = (s & 255) * tb;
                float dr = (d >> 16) & 255, dg = (d >> 8) & 255, db = d & 255;
                d = 0xFF000000u | uint32_t(dr + (r - dr) * a) << 16 | uint32_t(dg + (g - dg) * a) << 8 | uint32_t(db + (b - db) * a);
            }
    }
    void lighten(const Image& img, int x, int y) {  // light art on black (the scarecrow): the brighter of the two
        for (int j = std::max(0, -y); j < img.h && y + j < H; ++j)
            for (int i = std::max(0, -x); i < img.w && x + i < W; ++i) {
                uint32_t s = img.px[size_t(j) * img.w + i], &d = px[size_t(y + j) * W + x + i];
                uint32_t out = 0xFF000000u;
                for (int sh = 0; sh < 24; sh += 8) out |= std::max((s >> sh) & 255, (d >> sh) & 255) << sh;
                d = out;
            }
    }
    void fill(int x, int y, int w, int h, uint32_t argb) {
        float a = float(argb >> 24) / 255.f;
        float r = (argb >> 16) & 255, g = (argb >> 8) & 255, b = argb & 255;
        for (int j = std::max(0, y); j < std::min(H, y + h); ++j)
            for (int i = std::max(0, x); i < std::min(W, x + w); ++i) {
                uint32_t& d = px[size_t(j) * W + i];
                float dr = (d >> 16) & 255, dg = (d >> 8) & 255, db = d & 255;
                d = 0xFF000000u | uint32_t(dr + (r - dr) * a) << 16 | uint32_t(dg + (g - dg) * a) << 8 | uint32_t(db + (b - db) * a);
            }
    }
};

// ---- the game's subtitle font: a 21-wide grid of 24x24 cells in default.xbe ----
struct Font {
    Image cells[128];
    std::map<int, std::vector<Image>> sized;  // by scale x 100
    bool load() {
        Image font = xbe_image(0x2813C0, 512, 256), sym = xbe_image(0x2A1440, 512, 256);
        if (font.empty()) return false;
        auto cut = [](const Image& src, int index) {
            int cx = (index % 21) * 24, cy = (index / 21) * 24, l = 24, r = 0;
            for (int x = 0; x < 24; ++x)
                for (int y = 0; y < 24; ++y)
                    if ((src.at(cx + x, cy + y) >> 24) > 40) l = std::min(l, x), r = std::max(r, x + 1);
            return r > l ? crop(src, cx + l, cy, cx + r, cy + 24) : Image{};
        };
        const char* order = " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        for (int i = 1; order[i]; ++i) cells[(unsigned char)(order[i])] = cut(font, i);
        if (!sym.empty())  // punctuation on the symbol page: row 1 and 2 (and the dash on row 0)
            for (auto [ch, index] : std::initializer_list<std::pair<char, int>>{{':', 31}, {'!', 32}, {'?', 33}, {'(', 34}, {')', 35},
                                                                               {'\'', 40}, {',', 41}, {';', 42}, {'/', 45}, {'+', 47},
                                                                               {'=', 48}, {'.', 49}, {'-', 15}})
                cells[(unsigned char)(ch)] = cut(sym, index);
        return true;
    }
    const Image* glyph(char c, float s) {
        auto& v = sized[int(s * 100)];
        if (v.empty()) v.resize(128);
        int k = (unsigned char)(c) < 128 ? (unsigned char)(c) : '?';
        if (cells[k].empty()) k = cells[(unsigned char)('?')].empty() ? 0 : '?';
        if (cells[k].empty()) return nullptr;
        if (v[k].empty()) v[k] = scale(cells[k], std::max(1, int(cells[k].w * s + 0.5f)), int(24 * s + 0.5f));
        return &v[k];
    }
    int width(const std::string& t, float s) {
        int w = 0;
        for (char c : t) w += c == ' ' ? int(8 * s) : glyph(c, s) ? glyph(c, s)->w + int(2 * s) : 0;
        return w;
    }
    void draw(Canvas& cv, const std::string& t, int x, int y, float s, uint32_t color, float opacity = 1.f) {
        for (char c : t) {
            if (c == ' ') { x += int(8 * s); continue; }
            const Image* g = glyph(c, s);
            if (!g) continue;
            cv.blend(*g, x + int(3 * s / 2), y + int(3 * s / 2), 0xFF000000u, 0.75f * opacity);  // drop shadow
            cv.blend(*g, x, y, color, opacity);
            x += g->w + int(2 * s);
        }
    }
};

// ---- Config.toml, edited line by line like the launcher (launcher/GameConfig.cs) ----
struct Toml {
    std::vector<std::string> lines;
    static constexpr const char* path = "UserData\\Config.toml";
    Toml() {
        std::ifstream in(path);
        for (std::string l; std::getline(in, l);) lines.push_back(l);
    }
    static std::string strip(const std::string& l) {
        std::string s = l.substr(0, l.find('#'));
        size_t a = s.find_first_not_of(" \t\r"), b = s.find_last_not_of(" \t\r");
        return a == std::string::npos ? "" : s.substr(a, b - a + 1);
    }
    std::pair<int, int> section(const std::string& name) const {
        int s = -1;
        for (int i = 0; i < int(lines.size()); ++i) {
            std::string t = strip(lines[i]);
            if (s < 0 && t == "[" + name + "]") s = i;
            else if (s >= 0 && !t.empty() && t[0] == '[') return {s, i};
        }
        return {s, int(lines.size())};
    }
    int key_line(const std::string& sec, const std::string& key) const {
        auto [s, e] = section(sec);
        for (int i = s + 1; s >= 0 && i < e; ++i) {
            std::string t = strip(lines[i]);
            if (t.compare(0, key.size(), key) == 0) {
                size_t p = t.find_first_not_of(" \t", key.size());
                if (p != std::string::npos && t[p] == '=') return i;
            }
        }
        return -1;
    }
    std::string get(const std::string& sec, const std::string& key) const {  // raw value, quotes kept
        int i = key_line(sec, key);
        if (i < 0) return "";
        std::string t = strip(lines[i]);
        size_t p = t.find('=') + 1;
        return strip(t.substr(p));
    }
    void set(const std::string& sec, const std::string& key, const std::string& raw) {
        std::string line = key + " = " + raw;
        if (int i = key_line(sec, key); i >= 0) { lines[i] = line; return save(); }
        auto [s, e] = section(sec);
        if (s < 0) {
            if (!lines.empty() && !lines.back().empty()) lines.push_back("");
            lines.push_back("[" + sec + "]"), lines.push_back(line);
        } else {
            while (e > s + 1 && strip(lines[e - 1]).empty() && lines[e - 1].find('#') == std::string::npos) --e;
            lines.insert(lines.begin() + e, line);
        }
        save();
    }
    void remove(const std::string& sec, const std::string& key) {
        if (int i = key_line(sec, key); i >= 0) lines.erase(lines.begin() + i), save();
    }
    void save() const {
        CreateDirectoryA("UserData", nullptr);
        std::ofstream out(path, std::ios::trunc);
        for (auto& l : lines) out << l << "\n";
    }
};
std::string unquote(std::string v) {
    if (v.size() >= 2 && (v[0] == '"' || v[0] == '\'') && v.back() == v[0]) v = v.substr(1, v.size() - 2);
    std::transform(v.begin(), v.end(), v.begin(), [](char c) { return char(std::tolower((unsigned char)(c))); });
    return v;
}

// ---- what the pages offer ----
struct Choice { const char* label; const char* raw; };
struct Setting { const char* label; const char* section; const char* key; std::vector<Choice> choices; int fallback; };
const std::vector<Setting> kSettings = {
    {"Resolution", "display", "resolution",
     {{"Original (480)", "\"original\""}, {"720p", "\"720\""}, {"1080p", "\"1080\""}, {"1440p", "\"1440\""}, {"4K", "\"4k\""},
      {"Your screen", "\"screen\""}}, 4},
    {"Picture shape", "display", "aspect",
     {{"Your screen", "\"auto\""}, {"4:3", "\"4:3\""}, {"16:9", "\"16:9\""}, {"16:10", "\"16:10\""}, {"21:9", "\"21:9\""},
      {"32:9", "\"32:9\""}, {"Stretch 4:3", "\"stretch\""}}, 0},
    {"Frame rate", "display", "fps", {{"Match the screen", "\"auto\""}, {"60", "\"60\""}, {"120", "\"120\""}}, 0},
    {"Ray tracing", "display", "ray_tracing", {{"On", "true"}, {"Off", "false"}}, 0},
    {"Window", "display", "fullscreen", {{"Window", "false"}, {"Fullscreen", "true"}}, 0},
    {"Volume", "audio", "volume", {{"Off", "0"}, {"25", "25"}, {"50", "50"}, {"Xbox level", "100"}, {"150", "150"}, {"200", "200"}}, 3},
    {"Music", "audio", "music", {{"Off", "0"}, {"30", "30"}, {"50", "50"}, {"70", "70"}, {"As mixed", "100"}}, 4},
    {"Frame rate in title", "display", "show_fps", {{"Off", "false"}, {"On", "true"}}, 0},
};
struct Binding { const char* key; const char* label; const char* fallback; };
const std::vector<Binding> kBindings = {
    {"move_up", "Move up", "W"}, {"move_down", "Move down", "S"}, {"move_left", "Move left", "A"}, {"move_right", "Move right", "D"},
    {"camera_up", "Camera up", "Up"}, {"camera_down", "Camera down", "Down"}, {"camera_left", "Camera left", "Left"},
    {"camera_right", "Camera right", "Right"}, {"a", "A", "Space"}, {"b", "B", "LShift"}, {"x", "X", "R"}, {"y", "Y", "F"},
    {"black", "Black", "1"}, {"white", "White", "2"}, {"left_trigger", "Left trigger", "Q"}, {"right_trigger", "Right trigger", "E"},
    {"start", "Start (pause)", "Enter"}, {"back", "Back", "Tab"}, {"dpad_up", "D-pad up", "I"}, {"dpad_down", "D-pad down", "K"},
    {"dpad_left", "D-pad left", "J"}, {"dpad_right", "D-pad right", "L"}, {"left_stick_click", "Left stick click", "LCtrl"},
    {"right_stick_click", "Right stick click", "C"},
};

// the name Config.toml uses for a virtual key (key_code's inverse), "" if it has none
std::string key_name(int vk) {
    static const char* named[] = {"Space", "Enter", "Tab", "Escape", "Backspace", "LShift", "RShift", "LCtrl", "RCtrl", "LAlt", "RAlt",
                                  "Up", "Down", "Left", "Right", "Insert", "Delete", "Home", "End", "PageUp", "PageDown", "Comma",
                                  "Period", "Slash", "Semicolon", "Quote", "LBracket", "RBracket", "Minus", "Equals", "Backslash",
                                  "Backquote", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F12", "Num0", "Num1", "Num2",
                                  "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9"};
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) return std::string(1, char(vk));
    for (const char* n : named)
        if (key_code(n) == vk) return n;
    return "";
}

struct Art {
    Image painting, logo, background;  // background: the painting (or the game's frame), shade and logo, see compose
    Image mist, cursor, hook, hook_flip, vine, frames[4], button_a, button_b, word_confirm, word_back, panel_fill, panel_edge;
    int logo_bottom = 200;
};

Art load_art() {
    Art a;
    if (Image painting = stm_image(kStm + "omake.stm", "total/pig/total01.pig"); !painting.empty()) {
        Image p = crop(painting, 0, 0, 512, 392);  // its picture fills the top 392 lines
        a.painting = scale(p, 1280, 1280 * p.h / p.w);
    }
    Image logo = stm_image(kStm + "title_u.stm", "pig/tit0002.pig");
    if (!logo.empty()) {
        int x0 = logo.w, y0 = logo.h, x1 = 0, y1 = 0;  // its painted part
        for (int y = 0; y < logo.h; ++y)
            for (int x = 0; x < logo.w; ++x)
                if ((logo.at(x, y) >> 24) > 40) x0 = std::min(x0, x), y0 = std::min(y0, y), x1 = std::max(x1, x + 1), y1 = std::max(y1, y + 1);
        if (x1 > x0) {
            Image l = crop(logo, x0, y0, x1, y1);
            float k = std::min(270.f / l.w, 240.f / l.h);  // at most 270 wide and 240 tall
            a.logo = scale(l, int(l.w * k), int(l.h * k));
        }
    }
    const std::string sb = kStm + "sbuty_u.stm";
    if (Image m = stm_image(sb, "bg/pig/sb_mist.pig"); !m.empty()) {
        a.mist = scale(m, 768, 260);
        for (auto& p : a.mist.px) p = (p & 0xFFFFFF) | ((p >> 24) * 2 / 5) << 24;
    }
    if (Image m3 = stm_image(sb, "menu/pig/sbmenu03.pig"); !m3.empty()) {
        Image c = crop(m3, 3, 83, 52, 124);
        a.cursor = scale(c, c.w * 11 / 10, c.h * 11 / 10);
        a.hook = scale(crop(m3, 57, 81, 113, 127), 26, 22);
        a.hook_flip = flip_x(a.hook);
        a.panel_fill = crop(m3, 140, 186, 244, 247);
        a.panel_edge = crop(m3, 7, 181, 120, 252);
    }
    if (Image v = stm_image(sb, "menu/pig/sbmenu12.pig"); !v.empty()) a.vine = scale(crop(v, 132, 43, 252, 63), 300, 34);
    if (Image b = stm_image(sb, "common/pig/button00.pig"); !b.empty())
        a.button_a = scale(crop(b, 23, 1, 42, 23), 38, 44), a.button_b = scale(crop(b, 1, 1, 20, 23), 38, 44);
    if (Image w = stm_image(sb, "common/pig/exword00.pig"); !w.empty()) {
        Image c = crop(w, 130, 51, 214, 68), k = crop(w, 2, 3, 51, 20);
        a.word_confirm = scale(c, c.w * 8 / 5, c.h * 8 / 5), a.word_back = scale(k, k.w * 8 / 5, k.h * 8 / 5);
    }
    if (Image s = xbe_image(0x2CA988, 256, 256); !s.empty())
        for (int f = 0; f < 4; ++f) a.frames[f] = scale(crop(s, f * 64, 10, f * 64 + 64, 112), 128, 204);
    return a;
}

// the menu's backdrop at the canvas's size: the painting (scaled to the width, bottom-aligned) or the game's frame
// (blurred by a quarter-size round trip and dimmed), a shade on the left under the menu, the logo
void compose(Art& a, const Image* scene) {
    Canvas base;
    if (scene) {
        Image soft = scale(scale(*scene, W / 4, H / 4), W, H);
        for (auto& p : soft.px) p = 0xFF000000u | (p >> 1 & 0x7F7F7F);
        base.blend(soft, 0, 0);
    } else if (!a.painting.empty()) {
        base.blend(a.painting, (W - a.painting.w) / 2, H - a.painting.h + 40);
    }
    for (int x = 0; x < W; ++x) {
        int alpha = std::clamp(230 - int(x * 0.42f), 0, 230);
        if (!alpha) break;
        Image col;
        col.w = 1, col.h = H, col.px.assign(H, uint32_t(alpha) << 24);
        base.blend(col, x, 0);
    }
    if (!a.logo.empty()) base.blend(a.logo, 70, 20), a.logo_bottom = 20 + a.logo.h;
    a.background.w = W, a.background.h = H, a.background.px = base.px;
}

// a panel from the pause menu's rough box: its fill, dark and translucent, and its outline, corners kept at 2x
void panel(Canvas& cv, const Art& art, int x, int y, int w, int h) {
    if (!art.panel_fill.empty()) {
        Image f = scale(art.panel_fill, w, h);
        for (auto& p : f.px) p = 0x0E060Au | ((p >> 24) * 4 / 5) << 24;
        cv.blend(f, x, y);
    }
    const Image& e = art.panel_edge;
    if (e.empty()) return;
    const int b = 16, d = 32;  // source border, drawn border
    auto piece = [&](int sx0, int sy0, int sx1, int sy1, int dx, int dy, int dw, int dh) {
        if (dw > 0 && dh > 0) cv.blend(scale(crop(e, sx0, sy0, sx1, sy1), dw, dh), dx, dy);
    };
    piece(0, 0, b, b, x - 10, y - 10, d, d), piece(e.w - b, 0, e.w, b, x + w + 10 - d, y - 10, d, d);
    piece(0, e.h - b, b, e.h, x - 10, y + h + 10 - d, d, d), piece(e.w - b, e.h - b, e.w, e.h, x + w + 10 - d, y + h + 10 - d, d, d);
    piece(b, 0, e.w - b, b, x - 10 + d, y - 10, w + 20 - 2 * d, d), piece(b, e.h - b, e.w - b, e.h, x - 10 + d, y + h + 10 - d, w + 20 - 2 * d, d);
    piece(0, b, b, e.h - b, x - 10, y - 10 + d, d, h + 20 - 2 * d), piece(e.w - b, b, e.w, e.h - b, x + w + 10 - d, y - 10 + d, d, h + 20 - 2 * d);
}

// ---- input: keyboard (while the window has focus) and the pad, with key repeat on directions ----
struct Input {
    bool up = false, down = false, left = false, right = false, confirm = false, back = false, pad_used = false;
};
struct InputReader {
    bool held[6] = {};
    ULONGLONG next[6] = {};
    bool pad_last = false;
    bool any() const { return std::find(std::begin(held), std::end(held), true) != std::end(held); }
    Input read() {
        DWORD pid;
        GetWindowThreadProcessId(GetForegroundWindow(), &pid);
        bool focus = pid == GetCurrentProcessId();
        auto k = [&](int vk) { return focus && (GetAsyncKeyState(vk) & 0x8000) != 0; };
        u16 b = 0;
        s16 lx = 0, ly = 0;
        bool pad = pad_read(b, lx, ly);
        bool now[6] = {
            k(VK_UP) || k('W') || (pad && ((b & 0x1) || ly > 16000)), k(VK_DOWN) || k('S') || (pad && ((b & 0x2) || ly < -16000)),
            k(VK_LEFT) || k('A') || (pad && ((b & 0x4) || lx < -16000)), k(VK_RIGHT) || k('D') || (pad && ((b & 0x8) || lx > 16000)),
            k(VK_RETURN) || k(VK_SPACE) || (pad && (b & 0x1010)), k(VK_ESCAPE) || k(VK_BACK) || (pad && (b & 0x2000)),
        };
        bool pad_any = pad && (b || std::abs(lx) > 16000 || std::abs(ly) > 16000);
        bool key_any = false;
        for (int vk : {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, VK_SPACE, VK_ESCAPE, VK_BACK, int('W'), int('A'), int('S'), int('D')})
            key_any |= k(vk);
        if (pad_any) pad_last = true;
        else if (key_any) pad_last = false;
        Input in;
        in.pad_used = pad_last;
        bool* out[6] = {&in.up, &in.down, &in.left, &in.right, &in.confirm, &in.back};
        ULONGLONG t = GetTickCount64();
        for (int i = 0; i < 6; ++i) {
            if (now[i] && !held[i]) *out[i] = true, next[i] = t + 380;
            else if (now[i] && i < 4 && t >= next[i]) *out[i] = true, next[i] = t + 90;  // directions repeat while held
            held[i] = now[i];
        }
        return in;
    }
};

void save_canvas(const Canvas& cv, const std::string& path) {  // testing
    FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) return;
    uint32_t size = 54 + W * H * 4;
    uint8_t h[54] = {'B', 'M'};
    auto put = [&](int at, uint32_t v) { for (int k = 0; k < 4; ++k) h[at + k] = uint8_t(v >> (8 * k)); };
    put(2, size), put(10, 54), put(14, 40), put(18, W), put(22, uint32_t(-H)), h[26] = 1, h[28] = 32, put(34, W * H * 4);
    std::fwrite(h, 1, 54, f), std::fwrite(cv.px.data(), 4, size_t(W) * H, f), std::fclose(f);
}

// ---- the first start: setting the disc up. The game's font and art are on the disc, so this screen uses Windows'
// font and the program's icon (Jack, from the game's own save icon). ----

// t in Segoe UI, `size` pixels, wrapped at `wrap` pixels (0: one line); returns the height used
int sys_text(Canvas& cv, const std::string& t, int x, int y, int size, uint32_t color, int wrap = 0, bool bold = false) {
    HDC dc = CreateCompatibleDC(nullptr);
    HFONT font = CreateFontW(-size, 0, 0, 0, bold ? FW_BOLD : FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0, L"Segoe UI");
    HGDIOBJ old_font = SelectObject(dc, font);
    auto width = [&](const std::string& l) {
        SIZE z = {};
        GetTextExtentPoint32A(dc, l.c_str(), int(l.size()), &z);
        return int(z.cx);
    };
    std::vector<std::string> lines;
    std::string line;
    for (size_t p = 0; p <= t.size();) {  // greedy word wrap
        size_t q = std::min(t.find(' ', p), t.size());
        std::string word = t.substr(p, q - p), next = line.empty() ? word : line + " " + word;
        if (wrap && !line.empty() && width(next) > wrap) lines.push_back(line), line = word;
        else line = next;
        p = q + 1;
    }
    if (!line.empty()) lines.push_back(line);
    const int lh = size * 4 / 3;
    for (const std::string& l : lines) {
        int w = std::max(1, width(l));
        BITMAPINFO bi = {};
        bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -lh, 1, 32, BI_RGB};
        void* bits = nullptr;
        HBITMAP bm = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!bm) break;
        HGDIOBJ old_bm = SelectObject(dc, bm);
        SetBkColor(dc, 0), SetTextColor(dc, 0xFFFFFF);
        TextOutA(dc, 0, 0, l.c_str(), int(l.size()));
        GdiFlush();
        Image img;  // white on black: the brightness is the coverage
        img.w = w, img.h = lh, img.px.resize(size_t(w) * lh);
        const uint32_t* src = static_cast<const uint32_t*>(bits);
        for (size_t i = 0; i < img.px.size(); ++i) img.px[i] = ((src[i] >> 8) & 255) << 24 | (color & 0xFFFFFF);
        cv.blend(img, x + int(size / 12), y + int(size / 12), 0xFF000000u, 0.7f);  // drop shadow
        cv.blend(img, x, y);
        SelectObject(dc, old_bm), DeleteObject(bm);
        y += lh;
    }
    SelectObject(dc, old_font), DeleteObject(font), DeleteDC(dc);
    return int(lines.size()) * lh;
}

Image exe_icon(int size) {
    Image img;
    HICON icon = HICON(LoadImageW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(1), IMAGE_ICON, size, size, 0));
    if (!icon) return img;
    HDC dc = CreateCompatibleDC(nullptr);
    BITMAPINFO bi = {};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), size, -size, 1, 32, BI_RGB};
    void* bits = nullptr;
    if (HBITMAP bm = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0)) {
        HGDIOBJ old = SelectObject(dc, bm);
        DrawIconEx(dc, 0, 0, icon, size, size, 0, nullptr, DI_NORMAL);
        GdiFlush();
        img.w = img.h = size;
        img.px.assign(static_cast<const uint32_t*>(bits), static_cast<const uint32_t*>(bits) + size * size);
        SelectObject(dc, old), DeleteObject(bm);
    }
    DeleteDC(dc), DestroyIcon(icon);
    return img;
}

// Returns once Disc\files holds the game; Quit ends the process.
void setup_screen() {
    W = 1280;
    const Image icon = exe_icon(256);
    InputReader reader;
    reader.read();
    Canvas cv;
    int sel = 0;
    std::string message;  // the last attempt's problem
    std::atomic<int> done{0}, total{0};
    std::atomic<bool> busy{false};
    std::string result;   // the worker's answer, read once busy is false
    std::thread worker;
    // OOGIE_SETUP_FROM=<image or default.xbe>: starts at once with that file, no dialog; OOGIE_SETUP_SHOTS=dir saves the
    // screen twice a second (testing)
    const char* from_env = std::getenv("OOGIE_SETUP_FROM");
    const char* shots = std::getenv("OOGIE_SETUP_SHOTS");
    bool auto_started = false;
    int shot = 0;
    ULONGLONG start = GetTickCount64(), next_shot = start;
    std::fprintf(stderr, "[menu] disc setup\n");
    std::fflush(stderr);
    for (;;) {
        gfx_pump();
        Input in = reader.read();
        if (!busy && worker.joinable()) {
            worker.join();
            std::fprintf(stderr, "[menu] disc setup: %s (%d of %d files)\n", result.empty() ? "done" : result.c_str(), done.load(), total.load());
            std::fflush(stderr);
            if (result.empty() && disc_ready()) return;
            message = result;
        }
        if (!busy) {
            if (in.up || in.down) sel ^= 1;
            if (in.confirm && sel == 1) std::_Exit(0);
            std::wstring file;
            if (from_env && !auto_started) {
                auto_started = true;
                file.assign(from_env, from_env + std::strlen(from_env));
            } else if (in.confirm && sel == 0) {
                wchar_t name[MAX_PATH] = L"";
                OPENFILENAMEW o = {};
                o.lStructSize = sizeof o;
                o.hwndOwner = GetActiveWindow();
                o.lpstrFilter = L"Xbox disc image or game (*.iso;*.xiso;default.xbe)\0*.iso;*.xiso;default.xbe\0All files (*.*)\0*.*\0";
                o.lpstrFile = name, o.nMaxFile = MAX_PATH;
                o.lpstrTitle = L"Choose your Oogie's Revenge disc image (or default.xbe in an extracted game folder)";
                o.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
                if (GetOpenFileNameW(&o)) file = name;
                reader = InputReader{}, reader.read();  // the Enter that closed the dialog does not act again
            }
            if (!file.empty()) {
                busy = true, done = 0, total = 0, message.clear();
                worker = std::thread([&, file] { result = disc_setup(file, done, total), busy = false; });
            }
        }

        double t = (GetTickCount64() - start) / 1000.0;
        for (int y = 0; y < H; ++y) {  // night sky: deep purple to black, a faint moon glow behind the icon
            uint32_t* row = &cv.px[size_t(y) * W];
            for (int x = 0; x < W; ++x) {
                float dx = (x - 1010) / 420.f, dy = (y - 330) / 420.f, glow = std::max(0.f, 1 - std::sqrt(dx * dx + dy * dy));
                float k = 1 - float(y) / H * 0.7f;
                int r = int(26 * k + 70 * glow * glow), g = int(12 * k + 60 * glow * glow), b = int(40 * k + 40 * glow * glow);
                row[x] = 0xFF000000u | uint32_t(std::min(r, 255)) << 16 | uint32_t(std::min(g, 255)) << 8 | uint32_t(std::min(b, 255));
            }
        }
        if (!icon.empty()) cv.blend(icon, 1010 - 128, 330 - 128 + int(6 * std::sin(t * 1.5)));
        int y = 90;
        y += sys_text(cv, "The Nightmare Before Christmas", 90, y, 30, kValue);
        y += sys_text(cv, "Oogie's Revenge", 90, y, 64, kHot, 0, true) + 24;
        y += sys_text(cv, "This PC port needs your own copy of the game: an Xbox disc image (a Redump .iso or an xiso), "
                          "or the default.xbe in a game folder extracted from one. Only the USA version runs. Its files are "
                          "copied next to this program once; after that the game starts straight away.", 90, y, 24, kText, 620) + 36;
        const char* items[] = {"Choose your disc...", "Quit"};
        for (int i = 0; i < 2; ++i, y += 58) {
            bool hot = i == sel && !busy;
            if (hot) cv.fill(70, y - 8, 520, 54, 0x2EFFA028);
            sys_text(cv, items[i], 90, y, 30, busy ? kDim : hot ? kHot : kText, 0, hot);
        }
        y += 20;
        if (busy) {
            int n = done, of = std::max(1, total.load());
            cv.fill(90, y, 560, 18, 0x60FFFFFF);
            cv.fill(92, y + 2, 556 * n / of, 14, 0xFFFFC45C);
            sys_text(cv, total ? "Copying the game files: " + std::to_string(n) + " of " + std::to_string(total) : std::string("Reading the disc..."),
                     90, y + 30, 22, kValue);
        } else if (!message.empty()) {
            sys_text(cv, message, 90, y, 22, 0xFFFF8A70, 620);
        }
        sys_text(cv, in.pad_used ? "A  Choose        Left stick or D-pad  Move" : "Enter  Choose        Arrow keys  Move",
                 90, H - 70, 22, kDim);
        if (shots && GetTickCount64() >= next_shot && shot < 60) {
            char path[300];
            std::snprintf(path, sizeof path, "%s/s%02d.bmp", shots, shot++);
            save_canvas(cv, path);
            next_shot += 500;
        }
        gfx_show_canvas(cv.px.data(), W, H);
        static ULONGLONG last_frame;
        ULONGLONG now = GetTickCount64();
        if (now - last_frame < 16) Sleep(DWORD(16 - (now - last_frame)));
        last_frame = GetTickCount64();
    }
}

}  // namespace

static void run(bool overlay, bool setup) {
    if (!overlay) {  // the game's window and device; its own CreateDevice finds them open
        gfx_init(640, 480), input_start();
        if (setup || !disc_ready()) setup_screen();
    }
    static Font font;
    static const bool have_font = font.load();
    static Art art = load_art();
    Image scene;
    W = 1280;
    if (overlay) {
        uint32_t sw = 0, sh = 0;
        scene.px = gfx_scene_pixels(sw, sh);
        scene.w = int(sw), scene.h = int(sh);
        for (auto& p : scene.px) p |= 0xFF000000u;  // the game's alpha channel is not part of the picture
        if (!scene.empty()) W = std::clamp(int(H * float(sw) / float(sh) + 0.5f), 960, 2560);
        audio_pause(true);
    }
    compose(art, scene.empty() ? nullptr : &scene);
    std::fprintf(stderr, "[menu] %s: font %s, art %s\n", overlay ? "open in game" : "open", have_font ? "read" : "missing",
                 art.painting.empty() ? "missing" : "read");
    std::fflush(stderr);  // the log is buffered; nothing else flushes it while the menu is up
    Toml toml;
    InputReader reader;
    reader.read();  // keys already down (a held button) do not act
    Canvas cv;
    enum Page { MAIN, SETTINGS, CONTROLS, MODS } page = MAIN;
    const char* items[] = {overlay ? "Resume" : "Play", "Settings", "Controls", "Mods", "Quit"};
    const char* hints[] = {overlay ? "Back to the game" : "Start the game", "Picture, frame rate, ray tracing and sound",
                           "Keyboard keys and gamepad buttons", "Turn mods on or off",
                           overlay ? "Leave the game (unsaved progress is lost)" : "Leave"};
    bool resume = false;  // in game: back to it
    int main_sel = 0, row = 0, scroll = 0;
    bool capturing = false, changed = false, keys_down[256] = {};
    bool pad_list = false;  // Controls: the gamepad's buttons instead of the keyboard's keys (left/right switches)
    u8 pad_held[PAD_BUTTONS] = {};
    // Controls rows: the keyboard's 24 inputs or the gamepad's 16 Xbox buttons (kBindings from "a" on), then a reset
    auto binding = [&](int r) { return kBindings[pad_list ? r + 8 : r]; };
    auto control_rows = [&] { return (pad_list ? PAD_BUTTONS : int(kBindings.size())) + 1; };
    auto bind = [&](const std::string& raw) {
        toml.set(pad_list ? "gamepad" : "keyboard", binding(row).key, raw), capturing = false;
        config_reload();  // the game reads its keys and buttons from here
    };
    std::vector<std::string> mods;
    auto load_mods = [&] {
        mods.clear();
        WIN32_FIND_DATAA fd;
        HANDLE f = FindFirstFileA("UserData\\mods\\*", &fd);
        if (f == INVALID_HANDLE_VALUE) return;
        do {
            std::string n = fd.cFileName;
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && n != "." && n != ".." && n != "files") mods.push_back(n);
        } while (FindNextFileA(f, &fd));
        FindClose(f);
        std::sort(mods.begin(), mods.end());
    };
    auto setting_index = [&](const Setting& s) {
        std::string v = unquote(toml.get(s.section, s.key));
        for (int i = 0; i < int(s.choices.size()); ++i)
            if (unquote(s.choices[i].raw) == v) return i;
        if (s.key == std::string("resolution") && v == "2160") return 4;
        return s.fallback;
    };
    ULONGLONG start = GetTickCount64(), fade_from = 0;
    // OOGIE_MENU_SCRIPT=dir,down,confirm,...: one input every 0.6 s, the canvas saved to dir after each (testing)
    std::vector<std::string> script;
    std::string shot_dir;
    if (const char* sc = std::getenv("OOGIE_MENU_SCRIPT")) {
        std::string s = sc;
        for (size_t p = 0, q; p <= s.size(); p = q + 1) {
            q = s.find(',', p);
            if (q == std::string::npos) q = s.size();
            (shot_dir.empty() ? shot_dir : script.emplace_back()) = s.substr(p, q - p);
        }
    }
    size_t script_at = 0;
    ULONGLONG script_next = start + 1500;
    auto save_shot = [&](const std::string& name) { save_canvas(cv, shot_dir + "/" + name + ".bmp"); };
    for (;;) {
        gfx_pump();
        double t = (GetTickCount64() - start) / 1000.0;
        Input in = reader.read();
        bool shot_due = false;
        if (!shot_dir.empty() && GetTickCount64() >= script_next) {
            if (script_at > 0) shot_due = true;  // the frame after an input shows its result
            if (script_at < script.size()) {
                const std::string& k = script[script_at];
                in.up = k == "up", in.down = k == "down", in.left = k == "left", in.right = k == "right";
                in.confirm = k == "confirm", in.back = k == "back", in.pad_used = k == "pad";
            } else if (script_at > script.size()) {
                if (!overlay) std::_Exit(0);
                resume = true, shot_dir.clear();
            }
            ++script_at, script_next = GetTickCount64() + 600;
        }

        // ---- input ----
        if (gfx_menu_requested() && overlay && !capturing) resume = true;  // F1 again
        if (fade_from || resume) {
        } else if (capturing) {
            for (int vk = 8; vk < 255 && capturing; ++vk) {
                bool down = (GetAsyncKeyState(vk) & 0x8000) != 0;
                if (down && !keys_down[vk] && vk != VK_SHIFT && vk != VK_CONTROL && vk != VK_MENU) {
                    if (vk == VK_ESCAPE) capturing = false;
                    else if (vk == VK_DELETE) bind("\"none\"");
                    else if (std::string n = key_name(vk); !n.empty() && !pad_list) bind("\"" + n + "\"");
                }
                keys_down[vk] = down;
            }
            u8 now[PAD_BUTTONS];
            if (capturing && pad_list && pad_controls(now))
                for (int b = 0; b < PAD_BUTTONS && capturing; ++b) {
                    bool down = now[b] > 128;  // a trigger counts once pressed halfway
                    if (down && !pad_held[b]) bind(std::string("\"") + g_pad_button_names[b] + "\"");
                    pad_held[b] = down;  // the button that began the capture binds only after it is let go
                }
            if (!capturing) reader = InputReader{}, reader.read();  // the key that ended the capture does not act again
        } else if (page == MAIN) {
            if (in.up) main_sel = (main_sel + 4) % 5;
            if (in.down) main_sel = (main_sel + 1) % 5;
            if (in.back && overlay) resume = true;
            if (in.confirm) {
                if (main_sel == 0 && overlay) resume = true;
                else if (main_sel == 0) fade_from = GetTickCount64();
                else if (main_sel == 4) std::_Exit(0);
                else page = Page(main_sel), row = scroll = 0, load_mods();
            }
        } else {
            int rows = page == SETTINGS ? int(kSettings.size()) : page == CONTROLS ? control_rows() : int(mods.size()) + 1;
            if (in.up) row = (row + rows - 1) % rows;
            if (in.down) row = (row + 1) % rows;
            if (in.back) page = MAIN;
            if (page == SETTINGS && (in.left || in.right || in.confirm)) {
                const Setting& s = kSettings[row];
                int n = int(s.choices.size()), i = (setting_index(s) + (in.left ? n - 1 : 1)) % n;
                toml.set(s.section, s.key, s.choices[i].raw);
                config_reload(), gfx_set_fullscreen(config().fullscreen);  // sound, keys, ray tracing, window: at once
                std::string k = s.key;
                changed |= k == "resolution" || k == "aspect" || k == "fps";  // the window and device were made with these
            }
            if (page == CONTROLS && (in.left || in.right)) pad_list = !pad_list, row = scroll = 0;
            if (page == CONTROLS && in.confirm && row == control_rows() - 1) {  // reset this list to the defaults
                for (int r = 0; r < control_rows() - 1; ++r) toml.remove(pad_list ? "gamepad" : "keyboard", binding(r).key);
                config_reload();
            } else if (page == CONTROLS && in.confirm) {
                capturing = true;
                for (int vk = 0; vk < 256; ++vk) keys_down[vk] = (GetAsyncKeyState(vk) & 0x8000) != 0;
                u8 now[PAD_BUTTONS] = {};
                pad_controls(now);
                for (int b = 0; b < PAD_BUTTONS; ++b) pad_held[b] = now[b] > 128;
            }
            if (page == MODS && in.confirm) {
                if (row == int(mods.size())) {
                    CreateDirectoryA("UserData\\mods", nullptr);
                    ShellExecuteA(nullptr, "open", "UserData\\mods", nullptr, nullptr, SW_SHOWNORMAL);
                } else {
                    std::string flag = "UserData\\mods\\" + mods[row] + "\\disabled";
                    if (GetFileAttributesA(flag.c_str()) != INVALID_FILE_ATTRIBUTES) DeleteFileA(flag.c_str());
                    else if (FILE* f = std::fopen(flag.c_str(), "wb")) std::fclose(f);
                }
            }
        }

        // ---- drawing ----
        cv.px = art.background.empty() ? std::vector<uint32_t>(size_t(W) * H, 0xFF000000u) : art.background.px;
        if (!art.mist.empty()) {  // the pause menu's mist, drifting
            int off = int(t * 14) % 700;
            for (int k = -1; k * 700 - 200 < W; ++k) cv.blend(art.mist, k * 700 - 200 + off, H - 170 - int(10 * std::sin(t * 0.4 + k)));
        }
        int y = art.logo_bottom + 18;
        for (int i = 0; i < 5; ++i) {
            bool hot = page == MAIN ? i == main_sel : i == int(page);
            uint32_t color = hot ? kHot : page == MAIN ? kText : kDim;
            if (hot && page == MAIN && !art.cursor.empty())
                cv.blend(art.cursor, 120 - art.cursor.w - 10 + int(4 * std::sin(t * 5)), y + 6);
            font.draw(cv, items[i], 120, y, hot && page == MAIN ? 2.2f : 2.0f, color);
            y += 54;
        }
        if (page == MAIN) {
            if (!art.vine.empty()) cv.blend(art.vine, 60, y - 6);
            font.draw(cv, hints[main_sel], 70, y + 30, 1.2f, kValue);
        }
        if (page != MAIN) {
            const int px = W - 780, py = 80, pw = 700, ph = 540;
            panel(cv, art, px, py, pw, ph);
            const char* title = page == SETTINGS ? "Settings" : page == CONTROLS ? (pad_list ? "Gamepad" : "Keyboard") : "Mods";
            int tw = font.width(title, 1.9f), tx = px + (pw - tw) / 2;
            font.draw(cv, title, tx, py - 46, 1.9f, kHot);
            if (page == CONTROLS && !art.hook.empty())  // left and right switch the list
                cv.blend(art.hook_flip, tx - 40, py - 38), cv.blend(art.hook, tx + tw + 14, py - 38);
            const int visible = 8, left = px + 40, right = px + pw - 50;
            int rows = page == SETTINGS ? int(kSettings.size()) : page == CONTROLS ? control_rows() : int(mods.size()) + 1;
            if (row < scroll) scroll = row;
            if (row >= scroll + visible) scroll = row - visible + 1;
            int ry = py + 40;
            for (int r = scroll; r < std::min(rows, scroll + visible); ++r, ry += 54) {
                bool hot = r == row;
                std::string label, value;
                if (page == SETTINGS) label = kSettings[r].label, value = kSettings[r].choices[setting_index(kSettings[r])].label;
                else if (page == CONTROLS && r == rows - 1) {
                    label = pad_list ? "Reset the gamepad" : "Reset the keyboard";
                } else if (page == CONTROLS) {
                    label = binding(r).label;
                    std::string v = toml.get(pad_list ? "gamepad" : "keyboard", binding(r).key);
                    value = !v.empty() ? (v.size() >= 2 && v[0] == '"' ? v.substr(1, v.size() - 2) : v)
                            : pad_list ? g_pad_button_names[r] : binding(r).fallback;
                    if (unquote(value) == "none") value = "(none)";
                    for (int b = 0; pad_list && b < PAD_BUTTONS; ++b)  // as the game reads it: any case
                        if (_stricmp(value.c_str(), g_pad_button_names[b]) == 0) value = g_pad_button_names[b];
                    if (hot && capturing) value = pad_list ? "Press a button" : "Press a key";
                } else if (r < int(mods.size())) {
                    label = mods[r];
                    value = GetFileAttributesA(("UserData\\mods\\" + mods[r] + "\\disabled").c_str()) == INVALID_FILE_ATTRIBUTES ? "On" : "Off";
                } else {
                    label = "Open the mods folder";
                }
                if (hot) cv.fill(left - 24, ry - 6, right - left + 48, 50, 0x2EFFA028);
                font.draw(cv, label, left, ry, 1.5f, hot ? kHot : kText);
                int vw = font.width(value, 1.5f);
                bool arrows = hot && page == SETTINGS;
                font.draw(cv, value, right - vw - (arrows ? 34 : 0), ry, 1.5f, hot ? kHot : kValue);
                if (arrows && !art.hook.empty())
                    cv.blend(art.hook, right - 24, ry + 8), cv.blend(art.hook_flip, right - vw - 34 - 32, ry + 8);
            }
            const char* note = page == SETTINGS ? (overlay && changed ? "Resolution, shape and frame rate change at the next start."
                                                                       : "Saved and used at once.")
                               : page == CONTROLS ? (capturing ? "Esc cancels, Delete leaves it unbound."
                                                     : pad_list ? "Choose a button, then press the new one on the pad."
                                                                : "Choose a key, then press the new one. Left/right: gamepad.")
                               : mods.empty() ? "No mods yet: put them in UserData\\mods."
                               : overlay ? "Mods are loaded when the game starts." : "A mod's files\\ folder replaces the game's files.";
            float ns = std::min(1.2f, 1.2f * float(pw - 80) / float(std::max(1, font.width(note, 1.2f))));  // fits the panel
            font.draw(cv, note, left, py + ph - 40, ns, kValue);
            if (rows > visible) {  // where the list is
                int bar_h = (ph - 80) * visible / rows, bar_y = py + 40 + (ph - 80 - bar_h) * scroll / std::max(1, rows - visible);
                cv.fill(px + pw - 14, bar_y, 4, bar_h, 0x80FFC45C);
            }
        }
        if (page == MAIN && !art.frames[0].empty()) cv.lighten(art.frames[int(t * 7) % 4], W - 180, H - 250);
        // prompts: the game's own button glyphs and words on a pad, key names on a keyboard
        int x = 60;
        if (in.pad_used && !art.button_a.empty() && !art.word_confirm.empty()) {
            cv.blend(art.button_a, x, H - 64), cv.blend(art.word_confirm, x + 46, H - 58);
            x += 46 + art.word_confirm.w + 30;
            if (page != MAIN) cv.blend(art.button_b, x, H - 64), cv.blend(art.word_back, x + 46, H - 58);
        } else {
            font.draw(cv, "Enter", x, H - 60, 1.3f, kHot);
            x += font.width("Enter", 1.3f) + 12;
            font.draw(cv, page == CONTROLS ? "Change" : "Confirm", x, H - 60, 1.3f, kText);
            x += font.width("Confirm", 1.3f) + 30;
            if (page != MAIN) {
                font.draw(cv, "Esc", x, H - 60, 1.3f, kHot);
                font.draw(cv, "Back", x + font.width("Esc", 1.3f) + 12, H - 60, 1.3f, kText);
            }
        }
        if (fade_from) {  // Play: a short fade to black, then the game
            float f = std::min(1.f, (GetTickCount64() - fade_from) / 400.f);
            cv.fill(0, 0, W, H, uint32_t(f * 255) << 24);
            if (f >= 1.f) {
                gfx_show_canvas(cv.px.data(), W, H);
                if (changed) {  // the window and device were made with the old settings: start again with the new ones
                    wchar_t exe[MAX_PATH];
                    GetModuleFileNameW(nullptr, exe, MAX_PATH);
                    std::wstring cmd = L"\"" + std::wstring(exe) + L"\" --play";
                    STARTUPINFOW si = {sizeof si};
                    PROCESS_INFORMATION pi;
                    if (CreateProcessW(exe, cmd.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
                        CloseHandle(pi.hThread), CloseHandle(pi.hProcess);
                        std::_Exit(0);
                    }
                }
                return;
            }
        }
        if (resume) {  // back to the game once the keys that closed the menu are up (it would read them too)
            gfx_show_canvas(cv.px.data(), W, H);
            for (ULONGLONG until = GetTickCount64() + 1000; GetTickCount64() < until && (reader.read(), reader.any());)
                gfx_pump(), Sleep(16);
            audio_pause(false);
            return;
        }
        if (shot_due) {
            char name[16];
            std::snprintf(name, sizeof name, "m%02zu", script_at - 1);
            save_shot(name);
        }
        gfx_show_canvas(cv.px.data(), W, H);
        static ULONGLONG last_frame;  // at most 60 a second, also when the display gives no vertical blanks (asleep)
        ULONGLONG now = GetTickCount64();
        if (now - last_frame < 16) Sleep(DWORD(16 - (now - last_frame)));
        last_frame = GetTickCount64();
    }
}

void menu_run(bool setup) { run(false, setup); }
void menu_overlay() { run(true, false); }
