# Third-party notices

## Part of the released program

- **LLVM libc++, libc++abi and libunwind** (statically linked into `Oogie's Revenge.exe` by LLVM-MinGW), Apache License
  2.0 with LLVM Exceptions, Copyright (c) the LLVM project contributors.
- **mingw-w64 runtime** (statically linked), MIT/ZPL and public domain parts, Copyright (c) the mingw-w64 project.

No part of the game (code, art, sound or text) is included; the player supplies their own disc.

## Used to build (not part of the released game)

- **XbSymbolDatabase** (`third_party/XbSymbolDatabase`, vendored from
  [Cxbx-Reloaded/XbSymbolDatabase](https://github.com/Cxbx-Reloaded/XbSymbolDatabase) at the commit in
  `VENDORED.txt`), MIT License, Copyright (c) 2023 The XbSymbolDatabase authors. Its license is in
  `third_party/XbSymbolDatabase/LICENSE`. Names the Xbox SDK library functions inside the game's executable.
- **Capstone** disassembler (Python package, installed by `tools/build-oogie.ps1`), BSD 3-Clause License.
- **Xbox kernel export table** (`xboxrecomp/xboxkrnl.def`), from [XboxDev/nxdk](https://github.com/XboxDev/nxdk).
- **LLVM-MinGW, CMake, Ninja** (downloaded into `toolchain/` by `tools/get-toolchain.ps1`); their licenses are in
  their folders.
