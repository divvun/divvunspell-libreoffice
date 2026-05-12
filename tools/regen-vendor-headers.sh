#!/usr/bin/env bash
set -euo pipefail

# One-shot script: vendors UNO C++ headers + cppumaker-generated type stubs into
# native/vendor/include/. Output is committed to the repo. Re-run when bumping
# the LO version we target.
#
# Uses Fedora's libreoffice-sdk in Docker for cppumaker. The generated headers
# come from the macOS LO's offapi.rdb so they match the runtime LO version.

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
VENDOR_INC="$REPO_ROOT/native/vendor/include"
VENDOR_NLOHMANN_DIR="$REPO_ROOT/native/vendor/nlohmann"
LO_TYPES_DIR="/Applications/LibreOffice.app/Contents/Resources/types"
LO_URE_DIR="/Applications/LibreOffice.app/Contents/Resources/ure/share/misc"
NLOHMANN_VERSION="${NLOHMANN_VERSION:-3.11.3}"

if [ ! -f "$LO_TYPES_DIR/offapi.rdb" ]; then
    echo "ERROR: $LO_TYPES_DIR/offapi.rdb not found." >&2
    echo "Install LibreOffice.app or update LO_TYPES_DIR." >&2
    exit 1
fi

if ! docker version >/dev/null 2>&1; then
    echo "ERROR: docker is not running. Start OrbStack/Docker first." >&2
    exit 1
fi

mkdir -p "$VENDOR_INC" "$VENDOR_NLOHMANN_DIR"

echo "==> Copying hand-written headers + generating UNO type stubs (Fedora 44 libreoffice-sdk)"
docker run --rm \
    -v "$VENDOR_INC":/out \
    -v "$LO_TYPES_DIR":/types:ro \
    -v "$LO_URE_DIR":/ure:ro \
    fedora:44 \
    bash -c '
set -e
dnf install -q -y libreoffice-sdk >/dev/null 2>&1
SDK=/usr/lib64/libreoffice/sdk
for sub in sal cppu cppuhelper typelib uno osl rtl salhelper; do
    if [ -d "$SDK/include/$sub" ]; then
        rm -rf /out/$sub
        cp -R "$SDK/include/$sub" /out/
        echo "    + $sub"
    fi
done
# Also copy hand-written com/sun/star/uno/*.h, *.hxx (Any.h, Reference.h, etc.)
mkdir -p /out/com/sun/star/uno
cp "$SDK"/include/com/sun/star/uno/*.h /out/com/sun/star/uno/ 2>/dev/null || true
cp "$SDK"/include/com/sun/star/uno/*.hxx /out/com/sun/star/uno/ 2>/dev/null || true
echo "    + com/sun/star/uno/ hand-written headers"
"$SDK"/bin/cppumaker -O/out -L \
    /ure/types.rdb /types/offapi.rdb /types/oovbaapi.rdb
echo "    cppumaker done (full type closure)"
'

echo "==> Vendoring nlohmann/json single-header v${NLOHMANN_VERSION}"
curl -fsSL "https://github.com/nlohmann/json/releases/download/v${NLOHMANN_VERSION}/json.hpp" \
    -o "$VENDOR_NLOHMANN_DIR/json.hpp"

GENERATED=$(find "$VENDOR_INC/com" -name '*.hpp' 2>/dev/null | wc -l | tr -d ' ')
HANDWRITTEN=$(ls "$VENDOR_INC" | grep -v '^com$' | tr '\n' ' ')
echo "==> Done"
echo "    Generated headers: $GENERATED"
echo "    Hand-written modules: $HANDWRITTEN"
