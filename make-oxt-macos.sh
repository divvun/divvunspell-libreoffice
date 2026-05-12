#!/usr/bin/env bash
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
DIVVUN_RUNTIME_DIR="${DIVVUN_RUNTIME_DIR:-$HOME/git/necessary/divvun/divvun-runtime}"

if [ ! -x "$DIVVUN_RUNTIME_DIR/x" ]; then
    echo "divvun-runtime build script not found at $DIVVUN_RUNTIME_DIR/x" >&2
    echo "Set DIVVUN_RUNTIME_DIR to a checkout of divvun-runtime." >&2
    exit 1
fi

(cd "$DIVVUN_RUNTIME_DIR" && ./x build-lib)
RUNTIME_DYLIB="$DIVVUN_RUNTIME_DIR/target/release/libdivvun_runtime.dylib"
if [ ! -f "$RUNTIME_DYLIB" ]; then
    echo "Built runtime dylib not found at $RUNTIME_DYLIB" >&2
    exit 1
fi

(cd "$HERE/native" && make)
COMPONENT_DYLIB="$HERE/native/divvunspell.uno.dylib"
if [ ! -f "$COMPONENT_DYLIB" ]; then
    echo "Built UNO component not found at $COMPONENT_DYLIB" >&2
    exit 1
fi

STAGE="$(mktemp -d)"
trap 'rm -rf "$STAGE"' EXIT

rsync -a --exclude='__pycache__' --exclude='*.pyc' "$HERE/src/" "$STAGE/"
cp "$COMPONENT_DYLIB" "$STAGE/divvunspell.uno.dylib"
cp "$RUNTIME_DYLIB"   "$STAGE/libdivvun_runtime.dylib"

rm -f "$HERE/macos.oxt"
(cd "$STAGE" && zip -qr "$HERE/macos.oxt" .)
echo "Wrote $HERE/macos.oxt"
