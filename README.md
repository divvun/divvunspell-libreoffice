# divvunspell-libreoffice

LibreOffice extension for divvunspell, supporting Windows and macOS. Support for Linux could be added in the future.

## LibreOffice extension listing (macOS)

There's no way of installing the OXT automatically using Divvun Manager, it must be installed manually by downloading the OXT and installing it using the LibreOffice extension GUI. To increase discoverability and ease of access, the extension is also listed on the LO extension site:

- [LibreOffice extension page](https://extensions.libreoffice.org)
    - [The Divvun speller extension](https://extensions.libreoffice.org/en/extensions/show/27383) (macOS only - no need for a Windows version)
- [LO extension management](https://extensions.libreoffice.org/admin/extensions/LibreOffice-Extensions-Extension) (requires login)

The data used in the listing can be found [here](docs/index.md).

## License

The repository for `divvunspell-libreoffice` is licensed under either of

 * Apache License, Version 2.0 ([LICENSE-APACHE](LICENSE-APACHE) or http://www.apache.org/licenses/LICENSE-2.0)
 * MIT license ([LICENSE-MIT](LICENSE-MIT) or http://opensource.org/licenses/MIT)

at your option.

## Build

### macOS

To run this script you need to have the files `libdivvun_runtime.dylib`(for your architecture) and `sme.drb` in this directory.

```zsh
# Remove the previous bundle
rm src/divvunspell.oxt

# Spell checking
curl -Ls "https://pahkat.uit.no/devtools/download/libdivvunspell?platform=macos&channel=nightly" -o libdivvunspell.txz
xz -d libdivvunspell.txz
tar xvf libdivvunspell.tar
mkdir -p src/lib/darwin-x86_64
mkdir -p src/lib/darwin-arm64
mv lib/x86_64/* src/lib/darwin-x86_64
mv lib/aarch64/* src/lib/darwin-arm64
rm -Rf lib

# Grammar checking
cp libdivvun_runtime.dylib src/lib/darwin-arm64
mkdir -p src/resources
cp sme.drb src/resources

# Bundling
cd src
zip -r divvunspell.zip *
mv divvunspell.zip divvunspell.oxt
cd ..
rm -Rf src/lib
rm -Rf src/resources
```