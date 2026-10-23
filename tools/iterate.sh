#!/bin/sh
# Regenerate, rebuild and run for a while: tools/iterate.sh [seconds] (env passes through)
cd "$(dirname "$0")/.." || exit 1
python xboxrecomp/codegen.py Disc/files/default.xbe generated 32 symbols/xdk_symbols.tsv > build-logs/codegen.log 2>&1 || { tail build-logs/codegen.log; exit 1; }
tail -1 build-logs/codegen.log
toolchain/CMake/bin/cmake --build build > build-logs/build.txt 2>&1 || { grep -E 'error' build-logs/build.txt | head; exit 1; }
timeout "${1:-40}" build/OogiesRevenge.exe > build-logs/run.txt 2>&1
echo "exit $?"
