// Xbox controller input (XAPI XInput*), replaced with Windows XInput plus a keyboard fallback.
// One controller in port 0; the Xbox USB driver stack (XPP) never starts.
#include <windows.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>

#include "config.h"
#include "d3d8/renderer.h"
#include "hle.h"

namespace {

constexpr u32 GAMEPAD_TYPE = 0x00257FEC;  // XbSymbolDatabase: g_DeviceType_Gamepad
constexpr u32 PAD_HANDLE = 0xC0DE0000;    // the guest's XInputOpen handle for port 0

struct WinPad {  // XINPUT_STATE of the Windows API
    DWORD packet;
    WORD buttons;
    BYTE lt, rt;
    SHORT lx, ly, rx, ry;
};
typedef DWORD(WINAPI* GetStateFn)(DWORD, WinPad*);
typedef DWORD(WINAPI* SetStateFn)(DWORD, WORD*);
GetStateFn g_get_state;
SetStateFn g_set_state;
bool g_reported;  // the gamepad's insertion has been reported once
DWORD g_packet;

// Windows' XInputGetState can stall for tens of milliseconds (a port with no controller is re-probed), and the game
// polls inside its frame: a thread of our own polls instead (every 2 ms, or once a second while nothing is
// connected) and the game reads the latest state.
std::mutex g_pad_mutex;
WinPad g_pad;
bool g_pad_connected;

void poll_pads() {
    for (;;) {
        WinPad p{};
        bool ok = g_get_state(0, &p) == 0;
        {
            std::lock_guard<std::mutex> l(g_pad_mutex);
            g_pad = p, g_pad_connected = ok;
        }
        Sleep(ok ? 2 : 1000);
    }
}

void load_xinput() {
    static bool tried;
    if (tried) return;
    tried = true;
    HMODULE m = LoadLibraryW(L"xinput1_4.dll");
    if (!m) m = LoadLibraryW(L"xinput9_1_0.dll");
    if (!m) return;
    g_get_state = reinterpret_cast<GetStateFn>(GetProcAddress(m, "XInputGetState"));
    g_set_state = reinterpret_cast<SetStateFn>(GetProcAddress(m, "XInputSetState"));
    if (g_get_state) std::thread(poll_pads).detach();
}

bool key(int vk) { return (GetAsyncKeyState(vk) & 0x8000) != 0; }

bool focused() {
    DWORD pid;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    return pid == GetCurrentProcessId();
}

// the PC controller's buttons in g_pad_button_names order, 0-255 (the triggers are analog)
void pad_buttons(const WinPad& p, u8 out[PAD_BUTTONS]) {
    static const u16 bits[PAD_BUTTONS] = {0x1000, 0x2000, 0x4000, 0x8000, 0x0200, 0x0100, 0, 0,
                                          0x0010, 0x0020, 0x0001, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080};
    for (int b = 0; b < PAD_BUTTONS; ++b) out[b] = p.buttons & bits[b] ? 255 : 0;
    out[6] = p.lt, out[7] = p.rt;
}

}  // namespace

void input_start() { load_xinput(); }
bool pad_controls(u8 out[PAD_BUTTONS]) {  // the menu's button capture
    std::lock_guard<std::mutex> l(g_pad_mutex);
    pad_buttons(g_pad, out);
    return g_pad_connected;
}
bool pad_read(u16& buttons, s16& lx, s16& ly) {  // the latest state of the port 0 pad (Windows XINPUT_GAMEPAD layout)
    std::lock_guard<std::mutex> l(g_pad_mutex);
    buttons = g_pad.buttons, lx = g_pad.lx, ly = g_pad.ly;
    return g_pad_connected;
}

HLE(XInitDevices) { return 0; }
HLE_REGISTER(XInitDevices)

HLE(XGetDevices) { return sarg(c, 0) == GAMEPAD_TYPE ? 1 : 0; }  // bit 0: port 0
HLE_REGISTER(XGetDevices)

HLE(XGetDeviceChanges) {
    bool pad = sarg(c, 0) == GAMEPAD_TYPE;
    u32 insert = pad && !g_reported ? 1 : 0;
    if (pad) g_reported = true;
    st<u32>(sarg(c, 1), insert);
    st<u32>(sarg(c, 2), 0);
    return insert != 0;
}
HLE_REGISTER(XGetDeviceChanges)

HLE(XInputOpen) {
    load_xinput();
    if (sarg(c, 0) != GAMEPAD_TYPE || sarg(c, 1) != 0) return 0;  // only the port 0 gamepad exists
    return PAD_HANDLE;
}
HLE_REGISTER(XInputOpen)

HLE(XInputClose) { return 0; }
HLE_REGISTER(XInputClose)

HLE(XInputGetCapabilities) {
    u32 caps = sarg(c, 1);
    std::memset(g_mem + caps, 0, 0x19);  // packed XINPUT_CAPABILITIES: SubType, Reserved, gamepad at +3, rumble at +0x15
    st<u8>(caps, 1);  // XINPUT_DEVSUBTYPE_GC_GAMEPAD
    // every input present: buttons, analog buttons and sticks at full range; rumble motors
    st<u16>(caps + 3, 0xFF);
    std::memset(g_mem + caps + 5, 0xFF, 8);
    for (int k = 0; k < 4; ++k) st<s16>(caps + 13 + 2 * k, s16(0xFFC0));
    st<u16>(caps + 0x15, 0xFFFF), st<u16>(caps + 0x17, 0xFFFF);
    return 0;
}
HLE_REGISTER(XInputGetCapabilities)

HLE(XInputGetState) {
    u32 out = sarg(c, 1);
    u16 buttons = 0;
    u8 analog[8] = {};  // A B X Y Black White LeftTrigger RightTrigger
    s16 lx = 0, ly = 0, rx = 0, ry = 0;
    WinPad p{};
    bool connected;
    {
        std::lock_guard<std::mutex> l(g_pad_mutex);
        p = g_pad, connected = g_pad_connected;
    }
    if (connected) {  // each Xbox button from the PC button bound to it in Config.toml [gamepad]
        u8 pc[PAD_BUTTONS];
        pad_buttons(p, pc);
        static const u16 bits[] = {0x10, 0x20, 0x01, 0x02, 0x04, 0x08, 0x40, 0x80};  // start back d-pad, stick clicks
        for (int i = 0; i < PAD_BUTTONS; ++i) {
            int from = config().pad[i];
            u8 v = from < 0 ? 0 : pc[from];
            if (i < 8) analog[i] = std::max(analog[i], v);  // A B X Y Black White, triggers
            else if (v > 30) buttons |= bits[i - 8];       // a trigger bound to a digital button: past its dead zone
        }
        lx = p.lx, ly = p.ly, rx = p.rx, ry = p.ry;
    }
    // OOGIE_PRESS=start@5,a@8.5,walk@70:4: press buttons (or push the left stick: walk/sidel/sider, the right
    // one: lookl/lookr; retreat walks backwards) at those game seconds (presented frames / 60) for 0.2 s or `:seconds`, so automated runs
    // line up with OOGIE_FRAMES whatever the loading speed
    static const char* script = std::getenv("OOGIE_PRESS");
    if (script) {
        double now = g_presents / 60.0;
        for (const char* p = script; *p;) {
            char name[16] = {};
            double at = 0, hold = 0.2;
            int n = 0;
            if (std::sscanf(p, "%15[a-z]@%lf%n", name, &at, &n) < 2) break;
            p += n;
            if (*p == ':') hold = std::strtod(p + 1, const_cast<char**>(&p));
            p += *p == ',';
            if (now < at || now > at + hold) continue;
            std::string b = name;
            if (b == "walk") ly = 32767;
            else if (b == "retreat") ly = -32768;
            else if (b == "sidel") lx = -32768;
            else if (b == "sider") lx = 32767;
            else if (b == "lookl") rx = -32768;
            else if (b == "lookr") rx = 32767;
            else if (b == "start") buttons |= 0x10;
            else if (b == "back") buttons |= 0x20;
            else if (b == "a") analog[0] = 255;
            else if (b == "b") analog[1] = 255;
            else if (b == "x") analog[2] = 255;
            else if (b == "y") analog[3] = 255;
            else if (b == "up") buttons |= 0x01;
            else if (b == "down") buttons |= 0x02;
            else if (b == "left") buttons |= 0x04;
            else if (b == "right") buttons |= 0x08;
        }
    }
    if (focused()) {  // the keyboard, bound in Config.toml [keyboard]
        const int* k = config().keys;
        auto down = [&](int input) { return k[input] && key(k[input]); };
        for (int i = 0; i < 8; ++i)  // A B X Y Black White, triggers
            if (down(PAD_A + i)) analog[i] = 255;
        static const u16 bits[] = {0x10, 0x20, 0x01, 0x02, 0x04, 0x08, 0x40, 0x80};  // start back d-pad, stick clicks
        for (int i = 0; i < 8; ++i)
            if (down(PAD_START + i)) buttons |= bits[i];
        if (down(MOVE_UP)) ly = 32767;
        if (down(MOVE_DOWN)) ly = -32768;
        if (down(MOVE_LEFT)) lx = -32768;
        if (down(MOVE_RIGHT)) lx = 32767;
        if (down(CAM_UP)) ry = 32767;
        if (down(CAM_DOWN)) ry = -32768;
        if (down(CAM_LEFT)) rx = -32768;
        if (down(CAM_RIGHT)) rx = 32767;
    }
    st<u32>(out, ++g_packet);  // shortcut: a new packet every poll; the game only compares states
    st<u16>(out + 4, buttons);
    std::memcpy(g_mem + out + 6, analog, 8);
    st<s16>(out + 14, lx), st<s16>(out + 16, ly), st<s16>(out + 18, rx), st<s16>(out + 20, ry);
    return 0;
}
HLE_REGISTER(XInputGetState)

HLE(XInputSetState) {
    u32 fb = sarg(c, 1);  // XINPUT_FEEDBACK: 0x42-byte header { dwStatus, hEvent, ... } then rumble { left, right }
    if (g_set_state) {
        WORD motors[2] = {ld<u16>(fb + 0x42), ld<u16>(fb + 0x44)};
        g_set_state(0, motors);
    }
    st<u32>(fb, 0);  // dwStatus: done
    return 0;
}
HLE_REGISTER(XInputSetState)
