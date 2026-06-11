//! OXT (zip) parsing: description.xml and META-INF/manifest.xml.

use std::fs::File;
use std::io::{self, Read};
use std::path::Path;

use quick_xml::events::Event;
use quick_xml::Reader;
use zip::ZipArchive;

pub struct ManifestEntry {
    pub full_path: String,
    pub media_type: String,
}

pub struct Oxt {
    pub identifier: String,
    pub version: String,
    pub entries: Vec<ManifestEntry>,
}

fn local_name(qname: &[u8]) -> &[u8] {
    match qname.iter().rposition(|&b| b == b':') {
        Some(i) => &qname[i + 1..],
        None => qname,
    }
}

fn attr_by_local_name(e: &quick_xml::events::BytesStart, name: &[u8]) -> Option<String> {
    for attr in e.attributes().flatten() {
        if local_name(attr.key.as_ref()) == name {
            return Some(String::from_utf8_lossy(&attr.value).into_owned());
        }
    }
    None
}

fn parse_description(xml: &str) -> (Option<String>, Option<String>) {
    let mut reader = Reader::from_str(xml);
    let mut identifier = None;
    let mut version = None;
    loop {
        match reader.read_event() {
            Ok(Event::Start(e)) | Ok(Event::Empty(e)) => match local_name(e.name().as_ref()) {
                b"identifier" => identifier = attr_by_local_name(&e, b"value"),
                b"version" => version = attr_by_local_name(&e, b"value"),
                _ => {}
            },
            Ok(Event::Eof) | Err(_) => break,
            _ => {}
        }
    }
    (identifier, version)
}

fn parse_manifest(xml: &str) -> Vec<ManifestEntry> {
    let mut reader = Reader::from_str(xml);
    let mut entries = Vec::new();
    loop {
        match reader.read_event() {
            Ok(Event::Start(e)) | Ok(Event::Empty(e)) => {
                if local_name(e.name().as_ref()) == b"file-entry" {
                    if let (Some(full_path), Some(media_type)) = (
                        attr_by_local_name(&e, b"full-path"),
                        attr_by_local_name(&e, b"media-type"),
                    ) {
                        entries.push(ManifestEntry { full_path, media_type });
                    }
                }
            }
            Ok(Event::Eof) | Err(_) => break,
            _ => {}
        }
    }
    entries
}

fn read_zip_file(zip: &mut ZipArchive<File>, name: &str) -> io::Result<Option<String>> {
    match zip.by_name(name) {
        Ok(mut f) => {
            let mut s = String::new();
            f.read_to_string(&mut s)?;
            Ok(Some(s))
        }
        Err(zip::result::ZipError::FileNotFound) => Ok(None),
        Err(e) => Err(io::Error::other(e)),
    }
}

pub fn parse(path: &Path) -> io::Result<Oxt> {
    let mut zip = ZipArchive::new(File::open(path)?).map_err(io::Error::other)?;

    let manifest = read_zip_file(&mut zip, "META-INF/manifest.xml")?.ok_or_else(|| {
        io::Error::new(io::ErrorKind::InvalidData, "OXT has no META-INF/manifest.xml")
    })?;
    let entries = parse_manifest(&manifest);

    let (identifier, version) = match read_zip_file(&mut zip, "description.xml")? {
        Some(desc) => parse_description(&desc),
        None => (None, None),
    };
    // Per dp_identifier.cxx, an extension without an explicit identifier gets
    // the legacy identifier derived from its file name.
    let identifier = identifier.unwrap_or_else(|| {
        let file = path.file_name().unwrap_or_default().to_string_lossy();
        format!("org.openoffice.legacy.{}", file)
    });

    Ok(Oxt {
        identifier,
        version: version.unwrap_or_default(),
        entries,
    })
}

/// Extract the whole OXT into `dest` (created by the caller).
pub fn extract(path: &Path, dest: &Path) -> io::Result<()> {
    let mut zip = ZipArchive::new(File::open(path)?).map_err(io::Error::other)?;
    for i in 0..zip.len() {
        let mut entry = zip.by_index(i).map_err(io::Error::other)?;
        let Some(rel) = entry.enclosed_name() else {
            continue; // zip-slip or absolute path: skip
        };
        let out = dest.join(rel);
        if entry.is_dir() {
            std::fs::create_dir_all(&out)?;
            continue;
        }
        if let Some(parent) = out.parent() {
            std::fs::create_dir_all(parent)?;
        }
        let mut f = File::create(&out)?;
        io::copy(&mut entry, &mut f)?;
        #[cfg(unix)]
        {
            use std::os::unix::fs::PermissionsExt;
            if let Some(mode) = entry.unix_mode() {
                std::fs::set_permissions(&out, std::fs::Permissions::from_mode(mode))?;
            }
        }
    }
    Ok(())
}
