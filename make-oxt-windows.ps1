# Build the Windows .oxt for LibreOffice.
#
# Mirrors make-oxt-macos.sh: builds the divvun-runtime staticlib + the UNO DLL,
# stages everything in a temp dir with the .components URI rewritten to point
# at the .dll, and zips into windows.oxt.
#
# Run from a Developer Command Prompt for VS, or after invoking vcvars64.bat,
# so cl.exe / link.exe are on PATH.

[CmdletBinding()]
param(
    [string]$DivvunRuntimeDir = $env:DIVVUN_RUNTIME_DIR
)

$ErrorActionPreference = 'Stop'

$here = Split-Path -Parent $MyInvocation.MyCommand.Definition

if (-not $DivvunRuntimeDir -and (-not $env:RUNTIME_LIB -or -not $env:RUNTIME_INC)) {
    throw "Set `$env:DIVVUN_RUNTIME_DIR` (or both `$env:RUNTIME_LIB` and `$env:RUNTIME_INC`) to point at the divvun-runtime checkout."
}

$RuntimeLib = if ($env:RUNTIME_LIB) { $env:RUNTIME_LIB } else { Join-Path $DivvunRuntimeDir "target\release" }
$RuntimeInc = if ($env:RUNTIME_INC) { $env:RUNTIME_INC } else { Join-Path $DivvunRuntimeDir "bindings\c" }
if (-not (Test-Path (Join-Path $RuntimeLib "divvun_runtime.lib"))) {
    throw "Runtime staticlib not found at $RuntimeLib\divvun_runtime.lib. Build divvun-runtime first (./build.ps1 build-lib in that repo). This script does not."
}
if (-not (Test-Path (Join-Path $RuntimeInc "divvun_runtime.h"))) {
    throw "Runtime FFI header not found at $RuntimeInc\divvun_runtime.h."
}

& (Join-Path $here "native\build.ps1") -RuntimeLib $RuntimeLib -RuntimeInc $RuntimeInc
if ($LASTEXITCODE -ne 0) { throw "Native build failed" }

$dll = Join-Path $here "native\divvunspell.uno.dll"
if (-not (Test-Path $dll)) { throw "Built UNO component not found at $dll" }

$stage = Join-Path ([System.IO.Path]::GetTempPath()) ("divvunspell-oxt-" + [System.IO.Path]::GetRandomFileName())
New-Item -ItemType Directory -Path $stage | Out-Null
try {
    Copy-Item -Recurse -Force -Path (Join-Path $here "src\*") -Destination $stage `
        -Exclude "__pycache__", "*.pyc"
    Copy-Item -Path $dll -Destination (Join-Path $stage "divvunspell.uno.dll") -Force

    # Rewrite the platform-specific URI in DivvunSpell.components (.dylib -> .dll).
    $componentsFile = Join-Path $stage "DivvunSpell.components"
    if (Test-Path $componentsFile) {
        (Get-Content -Raw -Path $componentsFile) `
            -replace 'divvunspell\.uno\.dylib', 'divvunspell.uno.dll' |
            Set-Content -NoNewline -Encoding UTF8 -Path $componentsFile
    }

    $oxt = Join-Path $here "windows.oxt"
    if (Test-Path $oxt) { Remove-Item $oxt -Force }

    Push-Location $stage
    try {
        Compress-Archive -Path * -DestinationPath $oxt -CompressionLevel Optimal
    } finally {
        Pop-Location
    }

    Write-Host "Wrote $oxt"
} finally {
    Remove-Item -Recurse -Force $stage
}
