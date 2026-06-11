//! The per-backend registration files under uno_packages/cache/registry/.
//!
//! Formats reverse-engineered from desktop/source/deployment/registry/ and
//! verified byte-for-byte against a live unopkg-registered profile:
//!
//!   component/.../unorc          ORIGIN= + UNO_SERVICES= (space-sep, '?'-prefixed)
//!   configuration/.../configmgr.ini   SCHEMA= and DATA= (space-sep rc-terms)
//!   configuration/.../backenddb.xml   <conf:configuration-backend-db>
//!   bundle/.../backenddb.xml          <ext:extension-backend-db>
//!   help/.../backenddb.xml            empty <help:help-backend-db/>

use std::io;
use std::path::{Path, PathBuf};

use quick_xml::events::Event;
use quick_xml::Reader;

use crate::atomic_write;

pub const COMPONENT_BACKEND: &str = "com.sun.star.comp.deployment.component.PackageRegistryBackend";
pub const CONFIGURATION_BACKEND: &str =
    "com.sun.star.comp.deployment.configuration.PackageRegistryBackend";
pub const BUNDLE_BACKEND: &str = "com.sun.star.comp.deployment.bundle.PackageRegistryBackend";
pub const HELP_BACKEND: &str = "com.sun.star.comp.deployment.help.PackageRegistryBackend";

const EXT_NS: &str = "http://openoffice.org/extensionmanager/extension-registry/2010";
const CONF_NS: &str = "http://openoffice.org/extensionmanager/configuration-registry/2010";
const HELP_NS: &str = "http://openoffice.org/extensionmanager/help-registry/2010";

fn xml_escape(s: &str) -> String {
    s.replace('&', "&amp;").replace('<', "&lt;").replace('>', "&gt;").replace('"', "&quot;")
}

// ===== line-token rc files (unorc, configmgr.ini) =====

/// Read the space-separated token list of the line starting with `prefix`.
fn read_tokens(content: &str, prefix: &str) -> Vec<String> {
    for line in content.lines() {
        if let Some(rest) = line.strip_prefix(prefix) {
            return rest
                .split(' ')
                .map(str::trim)
                .filter(|t| !t.is_empty())
                .map(String::from)
                .collect();
        }
    }
    Vec::new()
}

fn read_to_string_opt(path: &Path) -> io::Result<String> {
    match std::fs::read_to_string(path) {
        Ok(s) => Ok(s),
        Err(e) if e.kind() == io::ErrorKind::NotFound => Ok(String::new()),
        Err(e) => Err(e),
    }
}

/// unorc: keeps ORIGIN constant, edits the UNO_SERVICES token list.
pub struct Unorc {
    path: PathBuf,
    pub services: Vec<String>,
}

impl Unorc {
    pub fn load(backend_dir: &Path) -> io::Result<Unorc> {
        let path = backend_dir.join("unorc");
        let content = read_to_string_opt(&path)?;
        Ok(Unorc { path, services: read_tokens(&content, "UNO_SERVICES=") })
    }

    pub fn save(&self) -> io::Result<()> {
        let mut buf = format!("ORIGIN=$UNO_USER_PACKAGES_CACHE/registry/{}\n", COMPONENT_BACKEND);
        if !self.services.is_empty() {
            buf.push_str("UNO_SERVICES=");
            buf.push_str(&self.services.join(" "));
            buf.push('\n');
        }
        atomic_write(&self.path, buf.as_bytes())
    }
}

/// configmgr.ini: SCHEMA= and DATA= token lists.
pub struct ConfigmgrIni {
    path: PathBuf,
    pub schemas: Vec<String>,
    pub data: Vec<String>,
}

impl ConfigmgrIni {
    pub fn load(backend_dir: &Path) -> io::Result<ConfigmgrIni> {
        let path = backend_dir.join("configmgr.ini");
        let content = read_to_string_opt(&path)?;
        Ok(ConfigmgrIni {
            path,
            schemas: read_tokens(&content, "SCHEMA="),
            data: read_tokens(&content, "DATA="),
        })
    }

    pub fn save(&self) -> io::Result<()> {
        let mut buf = String::new();
        if !self.schemas.is_empty() {
            buf.push_str("SCHEMA=");
            buf.push_str(&self.schemas.join(" "));
            buf.push('\n');
        }
        if !self.data.is_empty() {
            buf.push_str("DATA=");
            buf.push_str(&self.data.join(" "));
            buf.push('\n');
        }
        atomic_write(&self.path, buf.as_bytes())
    }
}

// ===== backenddb.xml files =====

fn local_name(qname: &[u8]) -> &[u8] {
    match qname.iter().rposition(|&b| b == b':') {
        Some(i) => &qname[i + 1..],
        None => qname,
    }
}

fn url_attr(e: &quick_xml::events::BytesStart) -> Option<String> {
    for attr in e.attributes().flatten() {
        if local_name(attr.key.as_ref()) == b"url" {
            return Some(String::from_utf8_lossy(&attr.value).into_owned());
        }
    }
    None
}

pub struct BundleItem {
    pub url: String,
    pub media_type: String,
}

pub struct BundleExtension {
    pub url: String,
    pub items: Vec<BundleItem>,
}

/// bundle backenddb.xml — one <ext:extension> per registered OXT.
pub struct BundleDb {
    path: PathBuf,
    pub extensions: Vec<BundleExtension>,
}

impl BundleDb {
    pub fn load(backend_dir: &Path) -> io::Result<BundleDb> {
        let path = backend_dir.join("backenddb.xml");
        let content = read_to_string_opt(&path)?;
        let mut extensions = Vec::new();
        if !content.is_empty() {
            let mut reader = Reader::from_str(&content);
            let mut cur: Option<BundleExtension> = None;
            let mut cur_item_url: Option<String> = None;
            let mut text_target: Option<&'static str> = None;
            loop {
                match reader.read_event() {
                    Ok(Event::Start(e)) | Ok(Event::Empty(e)) => {
                        match local_name(e.name().as_ref()) {
                            b"extension" => {
                                cur = Some(BundleExtension {
                                    url: url_attr(&e).unwrap_or_default(),
                                    items: Vec::new(),
                                })
                            }
                            b"url" => text_target = Some("url"),
                            b"media-type" => text_target = Some("media-type"),
                            _ => {}
                        }
                    }
                    Ok(Event::Text(t)) => {
                        let text = String::from_utf8_lossy(&t).into_owned();
                        match text_target.take() {
                            Some("url") => cur_item_url = Some(text),
                            Some("media-type") => {
                                if let (Some(ext), Some(url)) = (cur.as_mut(), cur_item_url.take())
                                {
                                    ext.items.push(BundleItem { url, media_type: text });
                                }
                            }
                            _ => {}
                        }
                    }
                    Ok(Event::End(e)) => {
                        if local_name(e.name().as_ref()) == b"extension" {
                            if let Some(ext) = cur.take() {
                                extensions.push(ext);
                            }
                        }
                    }
                    Ok(Event::Eof) | Err(_) => break,
                    _ => {}
                }
            }
        }
        Ok(BundleDb { path, extensions })
    }

    pub fn save(&self) -> io::Result<()> {
        let mut buf = String::from("<?xml version=\"1.0\"?>\n");
        buf.push_str(&format!("<ext:extension-backend-db xmlns:ext=\"{}\">", EXT_NS));
        for ext in &self.extensions {
            buf.push_str(&format!("<ext:extension url=\"{}\">", xml_escape(&ext.url)));
            buf.push_str("<ext:extension-items>");
            for item in &ext.items {
                buf.push_str(&format!(
                    "<ext:item><ext:url>{}</ext:url><ext:media-type>{}</ext:media-type></ext:item>",
                    xml_escape(&item.url),
                    xml_escape(&item.media_type)
                ));
            }
            buf.push_str("</ext:extension-items>");
            buf.push_str("</ext:extension>");
        }
        buf.push_str("</ext:extension-backend-db>\n");
        atomic_write(&self.path, buf.as_bytes())
    }
}

pub struct ConfEntry {
    pub url: String,
    pub ini_entry: String,
}

/// configuration backenddb.xml — one <conf:configuration> per .xcs/.xcu.
pub struct ConfDb {
    path: PathBuf,
    pub entries: Vec<ConfEntry>,
}

impl ConfDb {
    pub fn load(backend_dir: &Path) -> io::Result<ConfDb> {
        let path = backend_dir.join("backenddb.xml");
        let content = read_to_string_opt(&path)?;
        let mut entries = Vec::new();
        if !content.is_empty() {
            let mut reader = Reader::from_str(&content);
            let mut cur_url: Option<String> = None;
            let mut in_ini = false;
            loop {
                match reader.read_event() {
                    Ok(Event::Start(e)) | Ok(Event::Empty(e)) => {
                        match local_name(e.name().as_ref()) {
                            b"configuration" => cur_url = url_attr(&e),
                            b"ini-entry" => in_ini = true,
                            _ => {}
                        }
                    }
                    Ok(Event::Text(t)) => {
                        if in_ini {
                            if let Some(url) = cur_url.take() {
                                entries.push(ConfEntry {
                                    url,
                                    ini_entry: String::from_utf8_lossy(&t).into_owned(),
                                });
                            }
                            in_ini = false;
                        }
                    }
                    Ok(Event::Eof) | Err(_) => break,
                    _ => {}
                }
            }
        }
        Ok(ConfDb { path, entries })
    }

    pub fn save(&self) -> io::Result<()> {
        let mut buf = String::from("<?xml version=\"1.0\"?>\n");
        buf.push_str(&format!("<conf:configuration-backend-db xmlns:conf=\"{}\">", CONF_NS));
        for e in &self.entries {
            buf.push_str(&format!(
                "<conf:configuration url=\"{}\"><conf:ini-entry>{}</conf:ini-entry></conf:configuration>",
                xml_escape(&e.url),
                xml_escape(&e.ini_entry)
            ));
        }
        buf.push_str("</conf:configuration-backend-db>\n");
        atomic_write(&self.path, buf.as_bytes())
    }
}

/// help backenddb.xml — we register no help packages; just ensure an empty db
/// exists so the layout matches what unopkg leaves behind.
pub fn ensure_help_db(backend_dir: &Path) -> io::Result<()> {
    let path = backend_dir.join("backenddb.xml");
    if path.exists() {
        return Ok(());
    }
    std::fs::create_dir_all(backend_dir)?;
    let buf =
        format!("<?xml version=\"1.0\"?>\n<help:help-backend-db xmlns:help=\"{}\"/>\n", HELP_NS);
    atomic_write(&path, buf.as_bytes())
}
