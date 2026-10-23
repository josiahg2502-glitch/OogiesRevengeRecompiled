# Puts the pinned build tools (llvm-mingw, CMake, Ninja) in toolchain\. Archives are hash-checked;
# nothing is installed system-wide. -Seed copies an already-extracted toolchain folder with the same
# versions (for example another recomp project's toolchain\) instead of downloading.
[CmdletBinding()]
param([string]$Seed)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 3.0

$root = Split-Path -Parent $PSScriptRoot
$toolchain = Join-Path $root 'toolchain'
$downloads = Join-Path $toolchain 'downloads'

# Same pins as the WiiCompiled-based projects, so a toolchain can be shared between them.
$packages = @(
    [pscustomobject]@{
        Name = 'llvm-mingw'; File = 'llvm-mingw-20260616-ucrt-x86_64.zip'; Check = 'bin\x86_64-w64-mingw32-clang++.exe'
        Uri = 'https://github.com/mstorsjo/llvm-mingw/releases/download/20260616/llvm-mingw-20260616-ucrt-x86_64.zip'
        Sha256 = 'b9b68a4d276e16fa25802aaba458e4638f64b3884c290aaccdc2d87083b6ca35'; Root = 'llvm-mingw-20260616-ucrt-x86_64'
    },
    [pscustomobject]@{
        Name = 'CMake'; File = 'cmake-4.3.3-windows-x86_64.zip'; Check = 'bin\cmake.exe'
        Uri = 'https://github.com/Kitware/CMake/releases/download/v4.3.3/cmake-4.3.3-windows-x86_64.zip'
        Sha256 = '935ade9e5e8723583c07f44c5592cea2a1c8f65c56ca7e07b34c025c880e0bd6'; Root = 'cmake-4.3.3-windows-x86_64'
    },
    [pscustomobject]@{
        Name = 'Ninja'; File = 'ninja-win-1.13.2.zip'; Check = 'ninja.exe'
        Uri = 'https://github.com/ninja-build/ninja/releases/download/v1.13.2/ninja-win.zip'
        Sha256 = '07fc8261b42b20e71d1720b39068c2e14ffcee6396b76fb7a795fb460b78dc65'; Root = $null
    }
)

[IO.Directory]::CreateDirectory($toolchain) | Out-Null
foreach ($package in $packages) {
    $target = Join-Path $toolchain $package.Name
    if (Test-Path -LiteralPath (Join-Path $target $package.Check)) { continue }

    if ($Seed -and (Test-Path -LiteralPath (Join-Path (Join-Path $Seed $package.Name) $package.Check))) {
        Write-Host "Copying $($package.Name) from $Seed..."
        Copy-Item -LiteralPath (Join-Path $Seed $package.Name) -Destination $target -Recurse
        continue
    }

    [IO.Directory]::CreateDirectory($downloads) | Out-Null
    $archive = Join-Path $downloads $package.File
    if (-not (Test-Path -LiteralPath $archive -PathType Leaf) -or
        (Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash.ToLowerInvariant() -ne $package.Sha256) {
        Write-Host "Downloading $($package.Name)..."
        $partial = $archive + '.partial'
        Remove-Item -LiteralPath $partial -Force -ErrorAction SilentlyContinue
        Invoke-WebRequest -UseBasicParsing -Uri $package.Uri -OutFile $partial
        $actual = (Get-FileHash -LiteralPath $partial -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($actual -ne $package.Sha256) { throw "$($package.Name) hash mismatch: $actual" }
        Move-Item -LiteralPath $partial -Destination $archive -Force
    }
    $extract = Join-Path $toolchain ('.extract-' + $package.Name)
    if (Test-Path -LiteralPath $extract) { Remove-Item -LiteralPath $extract -Recurse -Force }
    Expand-Archive -LiteralPath $archive -DestinationPath $extract
    $source = if ($package.Root) { Join-Path $extract $package.Root } else { $extract }
    if (-not (Test-Path -LiteralPath $source -PathType Container)) { throw "$($package.Name) archive layout changed." }
    Move-Item -LiteralPath $source -Destination $target
    if (Test-Path -LiteralPath $extract) { Remove-Item -LiteralPath $extract -Recurse -Force }
}

foreach ($package in $packages) {
    if (-not (Test-Path -LiteralPath (Join-Path (Join-Path $toolchain $package.Name) $package.Check))) {
        throw "Toolchain incomplete: $($package.Name)"
    }
}
@"
Build tools in this folder (not part of the game)

LLVM-MinGW 20260616 (LLVM/Clang/LLD, mingw-w64, libc++)  https://github.com/mstorsjo/llvm-mingw
CMake 4.3.3                                              https://cmake.org/
Ninja 1.13.2 (Apache License 2.0)                        https://github.com/ninja-build/ninja
Each tool's license is in its own folder.
"@ | Set-Content -LiteralPath (Join-Path $toolchain 'README-LICENSES.txt') -Encoding UTF8
Write-Host "Toolchain ready: $toolchain"
