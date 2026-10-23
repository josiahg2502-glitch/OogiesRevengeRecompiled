# Builds Oogie's Revenge from your own disc: toolchain, symbol scan, recompilation, compile.
#   powershell -ExecutionPolicy Bypass -File tools\build-oogie.ps1 [-Iso <image.iso>] [-Jobs N]
# Needs Python 3. Logs: build-logs\.
[CmdletBinding()]
param([string]$Iso, [int]$Jobs = [Environment]::ProcessorCount, [string]$ToolchainSeed)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 3.0

$root = Split-Path -Parent $PSScriptRoot
$logs = Join-Path $root 'build-logs'
$toolchain = Join-Path $root 'toolchain'
$xbe = Join-Path $root 'Disc\files\default.xbe'
[IO.Directory]::CreateDirectory($logs) | Out-Null

function Invoke-Step([string]$name, [string]$exe, [string[]]$arguments) {
    Write-Host "== $name"
    $log = Join-Path $logs "$name.log"
    & $exe @arguments *>&1 | ForEach-Object { "$_" } | Out-File -LiteralPath $log -Encoding utf8
    if ($LASTEXITCODE -ne 0) { Get-Content -LiteralPath $log -Tail 20; throw "$name failed (see $log)" }
}

# 0. Game files
if (-not (Test-Path -LiteralPath $xbe)) {
    if (-not $Iso) { $Iso = Get-ChildItem -LiteralPath (Join-Path $root 'Disc') -Filter *.iso -ErrorAction SilentlyContinue |
                         Select-Object -First 1 -ExpandProperty FullName }
    if (-not $Iso) { throw 'No game files: pass -Iso <your Oogie''s Revenge (USA) Xbox disc image>' }
    Invoke-Step 'extract' 'python' @('-I', (Join-Path $root 'tools\extract_xiso.py'), $Iso, (Join-Path $root 'Disc\files'))
}

# 1. Tools
$seedArgs = if ($ToolchainSeed) { @('-Seed', $ToolchainSeed) } else { @() }
& (Join-Path $PSScriptRoot 'get-toolchain.ps1') @seedArgs
$cmake = Join-Path $toolchain 'CMake\bin\cmake.exe'
$ninja = Join-Path $toolchain 'Ninja\ninja.exe'
$cc = Join-Path $toolchain 'llvm-mingw\bin\clang.exe'
$cxx = Join-Path $toolchain 'llvm-mingw\bin\clang++.exe'
& python -c 'import capstone' 2>$null
if ($LASTEXITCODE -ne 0) { Invoke-Step 'capstone' 'python' @('-m', 'pip', 'install', '--user', 'capstone==5.0.7') }

# 2. Name the XDK libraries in the XBE (XbSymbolDatabase, vendored in third_party\)
$xbsdbBuild = Join-Path $root 'build-xbsdb'
Invoke-Step 'xbsdb-configure' $cmake @('-S', (Join-Path $root 'third_party\XbSymbolDatabase'), '-B', $xbsdbBuild, '-G', 'Ninja',
    "-DCMAKE_MAKE_PROGRAM=$ninja", "-DCMAKE_C_COMPILER=$cc", "-DCMAKE_CXX_COMPILER=$cxx", '-DCMAKE_BUILD_TYPE=Release',
    '-DXBSDB_BUILD_UNITTEST=OFF')
Invoke-Step 'xbsdb-build' $cmake @('--build', $xbsdbBuild, '--target', 'XbSymbolDatabaseCLI')
Invoke-Step 'symbols' 'python' @((Join-Path $root 'xboxrecomp\symbols.py'), $xbe,
    (Join-Path $xbsdbBuild 'projects\cli\XbSymbolDatabaseCLI.exe'), (Join-Path $root 'symbols'))

# 3. Recompile the XBE to C++
Invoke-Step 'codegen' 'python' @((Join-Path $root 'xboxrecomp\codegen.py'), $xbe, (Join-Path $root 'generated'), '32',
    (Join-Path $root 'symbols\xdk_symbols.tsv'))

# 4. Compile
$build = Join-Path $root 'build'
Invoke-Step 'configure' $cmake @('-S', $root, '-B', $build, '-G', 'Ninja', "-DCMAKE_MAKE_PROGRAM=$ninja",
    "-DCMAKE_CXX_COMPILER=$cxx", '-DCMAKE_BUILD_TYPE=Release')
Invoke-Step 'compile' $cmake @('--build', $build, '--parallel', "$Jobs")
Write-Host "Built $build\OogiesRevenge.exe"
