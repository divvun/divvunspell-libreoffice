#!/usr/bin/env bash
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"

if [ -z "${DIVVUN_RUNTIME_DIR:-}" ] && { [ -z "${RUNTIME_LIB:-}" ] || [ -z "${RUNTIME_INC:-}" ]; }; then
    echo "Set DIVVUN_RUNTIME_DIR (or both RUNTIME_LIB and RUNTIME_INC) to point at the divvun-runtime checkout." >&2
    exit 1
fi
RUNTIME_LIB="${RUNTIME_LIB:-$DIVVUN_RUNTIME_DIR/target/release}"
RUNTIME_INC="${RUNTIME_INC:-$DIVVUN_RUNTIME_DIR/bindings/c}"

if [ ! -f "$RUNTIME_LIB/libdivvun_runtime.a" ]; then
    echo "Runtime staticlib not found at $RUNTIME_LIB/libdivvun_runtime.a" >&2
    echo "Build divvun-runtime first (./x build-lib in that repo). This script does not." >&2
    exit 1
fi
if [ ! -f "$RUNTIME_INC/divvun_runtime.h" ]; then
    echo "Runtime FFI header not found at $RUNTIME_INC/divvun_runtime.h" >&2
    exit 1
fi

(cd "$HERE/native" && make -f Makefile.linux RUNTIME_LIB="$RUNTIME_LIB" RUNTIME_INC="$RUNTIME_INC")
COMPONENT_SO="$HERE/native/divvunspell.uno.so"
if [ ! -f "$COMPONENT_SO" ]; then
    echo "Built UNO component not found at $COMPONENT_SO" >&2
    exit 1
fi

STAGE="$(mktemp -d)"
trap 'rm -rf "$STAGE"' EXIT

rsync -a --exclude='__pycache__' --exclude='*.pyc' "$HERE/src/" "$STAGE/"
cp "$COMPONENT_SO" "$STAGE/divvunspell.uno.so"
strip --strip-unneeded "$STAGE/divvunspell.uno.so"

# Rewrite the platform-specific URI in DivvunSpell.components (.dylib -> .so).
sed -i 's/divvunspell\.uno\.dylib/divvunspell.uno.so/' "$STAGE/DivvunSpell.components"

rm -f "$HERE/linux.oxt"
(cd "$STAGE" && zip -qr "$HERE/linux.oxt" .)
echo "Wrote $HERE/linux.oxt"
