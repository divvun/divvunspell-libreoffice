#!/bin/sh
set -ex

HERE="$(cd "$(dirname "$0")" && pwd)"
REPO="$(dirname "$HERE")"

rm -rf "$HERE/tmp" "$HERE/build" "$HERE/payload"

PKG_NAME="LibreOfficeOXT.pkg"

# Universal oxtreg binary.
(cd "$REPO/oxtreg" && cargo build --release --target aarch64-apple-darwin && cargo build --release --target x86_64-apple-darwin)
mkdir -p "$HERE/payload"
lipo -create \
    "$REPO/oxtreg/target/aarch64-apple-darwin/release/oxtreg" \
    "$REPO/oxtreg/target/x86_64-apple-darwin/release/oxtreg" \
    -output "$HERE/payload/oxtreg"

cp "$HERE/divvunspell.oxt" "$HERE/payload/divvunspell.oxt"

VERSION=`/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" "$HERE/Info.plist"`

pkgbuild --root "$HERE/payload" \
    --identifier no.divvun.LibreOfficeOXT \
    --ownership recommended \
    --install-location "/Library/Application Support/Divvun/LibreOffice" \
    --version $VERSION \
    --scripts "$HERE/scripts" \
    "$HERE/no.divvun.LibreOfficeOXT.pkg"

productbuild --distribution "$HERE/dist.xml" \
    --version $VERSION \
    --package-path "$HERE" \
    "$HERE/$PKG_NAME"
