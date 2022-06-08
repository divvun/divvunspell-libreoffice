#!/bin/sh
set -ex

rm -rf tmp || echo "no tmp dir; continuing"
rm -rf build || echo "no build dir; continuing"

PKG_NAME="LibreOfficeOXT.pkg"

mkdir -p divvunspell-libreoffice.bundle/Contents/Resources
cp divvunspell.oxt divvunspell-libreoffice.bundle/Contents/Resources
cp Info.plist divvunspell-libreoffice.bundle/Contents

VERSION=`/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" "divvunspell-libreoffice.bundle/Contents/Info.plist"`

pkgbuild --component divvunspell-libreoffice.bundle \
    --ownership recommended \
    --install-location "/Library/Application Support/divvun-libreoffice" \
    --version $VERSION \
    --scripts scripts \
    no.divvun.LibreOfficeOXT.pkg

productbuild --distribution dist.xml \
    --version $VERSION \
    --package-path . \
    $PKG_NAME
