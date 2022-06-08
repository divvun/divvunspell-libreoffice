#!/bin/sh
set -ex

echo "::add-mask::$MACOS_NOTARIZATION_APP_PWD"
rm -rf tmp || echo "no tmp dir; continuing"
rm -rf build || echo "no build dir; continuing"

export MACOS_DEVELOPMENT_TEAM="2K5J2584NX"
export MACOS_CODE_SIGN_IDENTITY="Developer ID Application: The University of Tromso (2K5J2584NX)"
export MACOS_CODE_SIGN_IDENTITY_INSTALLER="Developer ID Installer: The University of Tromso (2K5J2584NX)"

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
    LibreOfficeOXT-unsigned.pkg

productsign --sign "$MACOS_CODE_SIGN_IDENTITY_INSTALLER" LibreOfficeOXT-unsigned.pkg "$PKG_NAME"
pkgutil --check-signature "$PKG_NAME"

echo "Notarizing installer"
xcnotary notarize "$PKG_NAME" --override-path-type pkg -d "$MACOS_DEVELOPER_ACCOUNT" -p "$MACOS_NOTARIZATION_APP_PWD"
stapler validate "$PKG_NAME"
