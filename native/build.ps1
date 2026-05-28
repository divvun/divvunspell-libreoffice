# Build the divvunspell.uno.dll UNO C++ component for Windows.
#
# Uses LLVM's clang-cl + lld-link (drop-in MSVC-compatible compiler / linker
# that ship inside VS BuildTools under VC\Tools\Llvm). Run from a Developer
# Command Prompt for VS, or invoke vcvars64.bat (or msvc-env) first so the
# LLVM bin dir is on PATH and INCLUDE / LIB are populated.
#
# Inputs:
#   -RuntimeLib  Absolute path to divvun_runtime.lib (the Rust staticlib).
#                Defaults to $DivvunRuntimeDir/target/release/divvun_runtime.lib.
#   -DivvunRuntimeDir  Directory of the divvun-runtime checkout.
#                Defaults to $env:DIVVUN_RUNTIME_DIR, then ~/git/necessary/divvun/divvun-runtime.
#   -Clean       Remove intermediate .obj files and the output DLL, then exit.
#
# Output: divvunspell.uno.dll alongside this script.

[CmdletBinding()]
param(
    [string]$DivvunRuntimeDir = $env:DIVVUN_RUNTIME_DIR,
    [string]$RuntimeLib = "",
    [string]$RuntimeInc = "",
    [switch]$Clean
)

$ErrorActionPreference = 'Stop'

$here = Split-Path -Parent $MyInvocation.MyCommand.Definition
Push-Location $here
try {
    if ($Clean) {
        Get-ChildItem -Filter "*.obj" -ErrorAction SilentlyContinue | Remove-Item -Force
        foreach ($f in "divvunspell.uno.dll", "divvunspell.uno.exp", "divvunspell.uno.lib") {
            if (Test-Path $f) { Remove-Item $f -Force }
        }
        return
    }

    # Always discard stale intermediates. The compile-cache check below uses
    # .cxx-vs-.obj mtimes only, which doesn't detect flag changes (e.g. /MD
    # → /MT) and leaves objects with the wrong CRT linkage in place.
    Get-ChildItem -Filter "*.obj" -ErrorAction SilentlyContinue | Remove-Item -Force

    if (-not $RuntimeLib -or -not $RuntimeInc) {
        if (-not $DivvunRuntimeDir) {
            throw "Set -DivvunRuntimeDir or `$env:DIVVUN_RUNTIME_DIR` (or pass both -RuntimeLib and -RuntimeInc) to point at the divvun-runtime checkout."
        }
        if (-not $RuntimeLib) { $RuntimeLib = Join-Path $DivvunRuntimeDir "target\release" }
        if (-not $RuntimeInc) { $RuntimeInc = Join-Path $DivvunRuntimeDir "bindings\c" }
    }
    $RuntimeLibFile = Join-Path $RuntimeLib "divvun_runtime.lib"
    if (-not (Test-Path $RuntimeLibFile)) {
        throw "Runtime staticlib not found at $RuntimeLibFile. Build divvun-runtime first; ensure its Cargo.toml lists `staticlib` in [lib].crate-type."
    }
    if (-not (Test-Path (Join-Path $RuntimeInc "divvun_runtime.h"))) {
        throw "Runtime FFI header not found at $RuntimeInc\divvun_runtime.h."
    }
    if (-not (Get-Command clang-cl.exe -ErrorAction SilentlyContinue)) {
        throw "clang-cl.exe not on PATH. Run from a Developer Command Prompt or invoke vcvars64.bat (or msvc-env) first; the LLVM toolset ships inside VS BuildTools."
    }
    if (-not (Get-Command lld-link.exe -ErrorAction SilentlyContinue)) {
        throw "lld-link.exe not on PATH. Same fix as clang-cl above."
    }

    $vendorInc = "vendor\include"
    $vendorNlohmann = "vendor"

    $cxxFlags = @(
        '/nologo',
        '/std:c++17',
        '/EHsc',
        '/O2',
        '/MT',                          # /MT matches divvun-runtime's MSVC target (crt-static = +crt-static)
        '/DWIN32',
        '/D_WINDOWS',
        '/DWNT',                        # LO/UNO Windows platform define
        '/D_WIN32_WINNT=0x0A00',
        '/DNOMINMAX',
        '/D_CRT_SECURE_NO_WARNINGS',
        '/DUNICODE', '/D_UNICODE',
        "/I$vendorInc",
        "/I$vendorNlohmann",
        "/I$RuntimeInc",
        '/I.'
    )

    $sources = @(
        'component.cxx',
        'DivvunProofreader.cxx',
        'DivvunSpellChecker.cxx',
        'SettingsDialog.cxx',
        'Engine.cxx',
        'RuntimeBridge.cxx',
        'Platform.cxx'
    )

    $objs = @()
    foreach ($src in $sources) {
        $obj = [System.IO.Path]::ChangeExtension($src, '.obj')
        $needs = -not (Test-Path $obj)
        if (-not $needs) {
            $needs = (Get-Item $src).LastWriteTime -gt (Get-Item $obj).LastWriteTime
        }
        if ($needs) {
            Write-Host "clang-cl $src"
            & clang-cl.exe @cxxFlags /c $src "/Fo$obj"
            if ($LASTEXITCODE -ne 0) { throw "clang-cl.exe failed on $src" }
        }
        $objs += $obj
    }

    # Authoritative system-libs list comes from running
    #   cargo rustc --release --features ffi --crate-type staticlib -- --print native-static-libs
    # inside divvun-runtime on the same host. Extend here if link emits LNK2019.
    $systemLibs = @(
        'kernel32.lib', 'user32.lib', 'gdi32.lib', 'advapi32.lib',
        'ntdll.lib', 'userenv.lib', 'ws2_32.lib', 'iphlpapi.lib',
        'dbghelp.lib', 'shell32.lib', 'ole32.lib', 'oleaut32.lib',
        'bcrypt.lib', 'ncrypt.lib', 'secur32.lib', 'crypt32.lib',
        'legacy_stdio_definitions.lib'
        # No msvcrt.lib here: /MT pulls in libcmt.lib (static CRT) via
        # auto-link pragmas. Adding msvcrt.lib (dynamic CRT) would conflict.
    )

    # UNO runtime import libs vendored under vendor/lib/. PE requires a .lib
    # at link time even for symbols that get resolved by LO at load.
    $unoLibPath = "vendor\lib"
    $unoLibs = @(
        'isal.lib',
        'icppu.lib',
        'icppuhelper.lib',
        'isalhelper.lib',
        'ipurpenvhelper.lib'
    )

    $linkFlags = @(
        '/nologo',
        '/DLL',
        '/MACHINE:X64',
        '/OUT:divvunspell.uno.dll',
        '/DEF:divvunspell.uno.def',
        "/LIBPATH:$unoLibPath"
    )

    # UNO discovers the component via `component_getFactory`; without a .def
    # lld-link would only export __declspec(dllexport) symbols, which our
    # source uses via SAL_DLLPUBLIC_EXPORT, so the .def is belt-and-braces.
    Set-Content -Path divvunspell.uno.def -Encoding ASCII -Value @"
LIBRARY divvunspell.uno
EXPORTS
    component_getFactory
"@

    Write-Host "lld-link divvunspell.uno.dll"
    & lld-link.exe @linkFlags @objs $RuntimeLibFile @unoLibs @systemLibs
    if ($LASTEXITCODE -ne 0) { throw "lld-link.exe failed" }

    Write-Host "Built $here\divvunspell.uno.dll"
} finally {
    Pop-Location
}
