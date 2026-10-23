# Assembles dist\OogiesRevenge: the game on top ("Oogie's Revenge.exe": its own menu sets the disc up on the first
# start), README.txt, and data\ for the disc files, settings, saves and mods. No disc data.
#   powershell -ExecutionPolicy Bypass -File tools\package-oogie.ps1 [-Build] [-Zip]
# -Build first rebuilds the game.
# -Zip also writes dist\OogiesRevenge.zip from a clean copy (never the player's disc, saves or settings).
# Updating dist in place only replaces program files: data\Disc and data\UserData (saves, Config.toml, mods) are kept.
# -GameExe <path> ships that game program instead of build\OogiesRevenge.exe (for example while that one is running).
[CmdletBinding()] param([switch]$Build, [switch]$Zip, [string]$GameExe)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$game = if ($GameExe) { (Resolve-Path $GameExe).Path } else { "$root\build\OogiesRevenge.exe" }
if ($Build) {
    & "$root\toolchain\CMake\bin\cmake.exe" --build "$root\build"
    if ($LASTEXITCODE -ne 0) { throw "game build failed" }
}
if (-not (Test-Path -LiteralPath $game)) { throw "build\OogiesRevenge.exe is missing (build the game first)" }

# Program files only: what a new download replaces.
function Stage([string]$to) {
    New-Item -ItemType Directory -Force "$to\data\UserData\mods" | Out-Null
    Copy-Item -LiteralPath $game -Destination "$to\Oogie's Revenge.exe" -Force
    Copy-Item -LiteralPath "$PSScriptRoot\package-README.txt" -Destination "$to\README.txt" -Force
    Copy-Item -LiteralPath "$root\THIRD-PARTY-NOTICES.md" -Destination "$to\THIRD-PARTY-NOTICES.md" -Force
    # an older release unzipped over this one: its WinForms launcher's game copy and icon are no longer used
    foreach ($old in "$to\data\OogiesRevenge.exe", "$to\data\icon.ico") { Remove-Item -LiteralPath $old -ErrorAction SilentlyContinue }
    # compiled shaders from test runs of this build: the first time an effect appears it does not stall to compile
    if (Test-Path -LiteralPath "$root\cache\shaders") {
        New-Item -ItemType Directory -Force "$to\data\cache\shaders" | Out-Null
        Copy-Item -Path "$root\cache\shaders\*.cso" -Destination "$to\data\cache\shaders" -Force
    }
}

$dist = "$root\dist\OogiesRevenge"
New-Item -ItemType Directory -Force $dist | Out-Null
Stage $dist
$size = [math]::Round((Get-ChildItem -LiteralPath $dist -Recurse -File | ? FullName -notmatch '\\data\\(Disc|UserData|cache)\\' | Measure-Object Length -Sum).Sum / 1MB)
Write-Host "DONE: $dist ($size MB of program files; data\Disc and data\UserData left as they were)"
if ($Zip) {
    $clean = Join-Path $env:TEMP "OogiesRevenge-zip\OogiesRevenge"
    Remove-Item -Recurse -Force (Split-Path $clean) -ErrorAction SilentlyContinue
    Stage $clean
    # Entries with forward slashes (Compress-Archive in Windows PowerShell 5.1 writes backslashes, which some unzip
    # tools reject).
    Add-Type -AssemblyName System.IO.Compression, System.IO.Compression.FileSystem
    $zipPath = "$root\dist\OogiesRevenge.zip"
    Remove-Item -LiteralPath $zipPath -ErrorAction SilentlyContinue
    $archive = [IO.Compression.ZipFile]::Open($zipPath, 'Create')
    try {
        $base = Split-Path $clean
        foreach ($f in Get-ChildItem -LiteralPath $clean -Recurse -File) {
            $name = $f.FullName.Substring($base.Length + 1).Replace('\', '/')
            [IO.Compression.ZipFileExtensions]::CreateEntryFromFile($archive, $f.FullName, $name, 'Optimal') | Out-Null
        }
        $archive.CreateEntry('OogiesRevenge/data/UserData/mods/') | Out-Null  # keep the empty mods folder
    } finally { $archive.Dispose() }
    Remove-Item -Recurse -Force (Split-Path $clean)
    Write-Host "DONE: $zipPath"
}
