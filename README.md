# Oogie's Revenge Recomp

A native PC port of **Tim Burton's The Nightmare Before Christmas: Oogie's Revenge** (Xbox, USA, title ID 42560004),
made by statically recompiling the game's x86 code to C++ with `xboxrecomp`. No emulator.

**No game data is included.** You need your own disc image.

**Status:** playable start. The whole executable is recompiled and runs its own game logic at a steady 60 fps
with sound. Direct3D 8 is replaced by a Direct3D 11 renderer that translates the game's vertex shaders and
register-combiner pixel shaders to HLSL; intro, menus, NEW GAME and the first level (Town Square) render correctly
at 4K. The game's own menu (drawn with its art from the disc) is the launcher: it copies the player's disc on the
first start, then offers Play, Settings, Controls and Mods, and F1 opens it during play.

![Town Square](screenshots/fixed4k_f04140_small.png)

## Building

Windows 10/11 x64 with Python 3. The build downloads its own pinned toolchain into `toolchain\`.

```powershell
powershell -ExecutionPolicy Bypass -File tools\build-oogie.ps1 -Iso "C:\path\to\Oogie's Revenge (USA).iso"
build\OogiesRevenge.exe
```

The disc is extracted to `Disc\files` once; after that `-Iso` can be left out. Player data lives in `UserData\`:
`Config.toml` (settings), `hdd\` (the Xbox hard disk; saves in `hdd\Partition1\UDATA`), `mods\<mod>\files\<disc
path>` (replacement disc files such as upscaled `movie\*.bik`; a file named `disabled` switches a mod off) and
`log.txt` (when started without a console). Compiled shaders are kept in `cache\shaders`.

`UserData\Config.toml` (the menu writes it): `[display]` `resolution` = "original", "720", "1080", "1440", "4k"
or "screen", `aspect` = "auto" (the screen's shape), "4:3", "16:9", "21:9", "32:9"... or "stretch" (wider shows more
of the world; the HUD, menus and movies keep 4:3), `fps` = "auto" (120 on a 120 Hz+ screen), "60" or "120" (the game
still steps at 60; each frame is preceded by a picture halfway to it, drawn from the recorded draws of the two frames),
`ray_tracing` (true: ambient occlusion from rays marched through each frame's depth, after the 3D world and before
the HUD), `fullscreen`, `show_fps`; `[audio]` `volume` and `music` (0-200); `[gamepad]` the PC controller button
("A", "B", "X", "Y", "RB", "LB", "LT", "RT", "Start", "Back", "Up"... "LS", "RS" or "none") per Xbox button (`a` ... `right_stick_click`;
default: the same-named one, RB = Black, LB = White); `[keyboard]` one
key per Xbox input (`a`, `b`, `move_up`, `camera_left`, ...; see `xboxrecomp/runtime/config.cpp`). In game: **F11**
or **Alt+Enter** toggles fullscreen, and **F1** opens the game's menu over the paused game (`menu_overlay`: the
guest lock is held and the mixer is silent while it is up; settings apply at once except resolution, aspect and fps). Gamepads work through XInput (RB = Black, LB = White); keyboard defaults: WASD
move, arrows camera, Space/Left Shift/R/F = A/B/X/Y, Q/E triggers, 1/2 Black/White, Enter Start, Tab Back, IJKL
d-pad. `OOGIE_SCALE=N` (1 to 9, fractions allowed) overrides the resolution with a multiple of the Xbox's.

Frames are paced by the Xbox's 59.94 Hz vertical blank (synced to the display when it runs at 60 Hz), so the game
keeps its speed on any monitor. Without an audio device the sound runs silently against a real-time clock (movies
wait for their sound) and the device is retried every 2 seconds.

Release: `tools\package-oogie.ps1 [-Build] [-Zip]` assembles `dist\OogiesRevenge` (the game as "Oogie's
Revenge.exe" on top, `data\` beside it for the disc files, settings, saves and mods, no game data) and the zip. The
game works in `data\` when it is there. Its first start asks for the disc (`xboxrecomp/runtime/menu/disc.cpp`:
Redump .iso, xiso or an extracted folder, checked against the USA default.xbe's SHA-256); `--setup` asks again.
Tests: `OOGIE_SETUP_FROM=<image>` skips the file dialog, `OOGIE_SETUP_SHOTS=<dir>` saves the setup screen. The old
WinForms launcher (`launcher\`) is no longer shipped; its icon `launcher\oogie.ico` is still the exe's. Automated runs set `OOGIE_NO_DIALOGS=1` so a fatal error doesn't wait on a
message box.

Debugging: `OOGIE_SCREENSHOT=file.bmp` saves every presented frame; `OOGIE_CLEAR_COLOR=AARRGGBB` replaces the
game's clear color (shows which clears reach the screen); `OOGIE_TRACE=1` logs every kernel call, file open and where threads are when preempted;
`OOGIE_TRACE_XDK=D3D8,DSOUND` (or `all`) logs every call into those Xbox SDK libraries.
`OOGIE_FRAMES=dir,first,count` saves consecutive frames; `OOGIE_FRAME_LOG=first,count` prints draws per frame;
`OOGIE_THREADS=1` prints every guest thread's priority and kernel call every 5 s; `OOGIE_PRESS=start@5,a@8`
presses buttons at those game seconds (presented frames / 60, so scripts line up with `OOGIE_FRAMES`).
`OOGIE_SOLID_PS=1` paints every draw magenta, `OOGIE_NO_Z=1` drops the depth test, and `OOGIE_CYCLE_DEBUG=1` cycles
every 60 frames through normal / no depth / no blending / no alpha test / full color mask / no culling, so a frame
recording shows which state blanks a scene. `OOGIE_PRINT_SHADERS=1` prints the HLSL of every translated shader;
`OOGIE_DUMP_SHADERS=file` and `OOGIE_DUMP_TEXTURES=dir` dump what draws use. The frame statistics line shows where
time goes (vertex packing, texture hashing, host draw calls, file reads).
`OOGIE_SNAP=frame,step,from,to,dir` takes one frame apart: it logs every draw and D3D call of that frame, saves the
back buffer every `step` draws, and after each draw from `from` to `to` also its render target and texture, so a
contact sheet shows the draw (or call) that breaks the picture.

## How it works

- `tools/extract_xiso.py` pulls the game partition out of the disc image.
- `xboxrecomp/symbols.py` names the Xbox SDK libraries linked into `default.xbe` (D3D8, DSOUND, XAPI, XACT) with
  XbSymbolDatabase, and lists the D3D functions the game calls (`symbols/d3d_calls.tsv`).
- `xboxrecomp/analyze.py` finds every function; `xboxrecomp/codegen.py` translates each one to C++ in `generated/`.
  Functions the SDK scan named get a hook at their entry, so the runtime can replace them by name.
- `xboxrecomp/runtime/` is what the generated code runs on: CPU helpers (`x86.h`), the guest address space
  (`memory.cpp`), the XBE loader and dispatch (`main.cpp`), the reimplemented Xbox kernel (`kernel.cpp`,
  `kthreads.cpp` for threads/waits/timers/DPCs, `kfile.cpp` for files) and SDK replacements (`hle.cpp`):
  `d3d8/` (Direct3D 8 on Direct3D 11) and `input.cpp` (controllers).
- `xboxrecomp/tests/` checks the instruction helpers against the real CPU.

## Credits

- Port: JosiahG
- See [`THIRD-PARTY-NOTICES.md`](THIRD-PARTY-NOTICES.md) for XbSymbolDatabase, nxdk and the build tools.

The Nightmare Before Christmas: Oogie's Revenge © Capcom / Disney. Unofficial fan project, not affiliated with or
endorsed by them. The repository contains no game code or assets; the game's data is read from your own copy.
