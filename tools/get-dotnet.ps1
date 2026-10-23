# Returns the path of a dotnet.exe with the .NET 8 SDK: the portable one in toolchain\dotnet, installed there on first
# use with Microsoft's dotnet-install.ps1 (nothing is installed system-wide).
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$dir = Join-Path $root 'toolchain\dotnet'
$dotnet = Join-Path $dir 'dotnet.exe'
if (-not (Test-Path -LiteralPath $dotnet)) {
    New-Item -ItemType Directory -Force $dir | Out-Null
    $installer = Join-Path $dir 'dotnet-install.ps1'
    Write-Host "Downloading the .NET 8 SDK into $dir ..."
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    Invoke-WebRequest -UseBasicParsing 'https://dot.net/v1/dotnet-install.ps1' -OutFile $installer
    & $installer -Channel 8.0 -InstallDir $dir -NoPath | Out-Host
    if (-not (Test-Path -LiteralPath $dotnet)) { throw ".NET SDK install failed ($dir)" }
}
$dotnet
