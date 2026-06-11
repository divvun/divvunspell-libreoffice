//! LibreOffice PersistentMap ("Pmp1") codec.
//!
//! Format (desktop/source/deployment/dp_persmap.cxx):
//!   - magic "Pmp1"
//!   - per entry: encoded-key '\n' encoded-value '\n', in byte-sorted key order
//!   - terminated by a single empty line
//!   - encoding: bytes 0x00..=0x0F -> "%0".."%F"; '%' -> "%%"; all else raw
//!     (0xFF field separators pass through unescaped)

use std::collections::BTreeMap;
use std::io;
use std::path::Path;

const MAGIC: &[u8; 4] = b"Pmp1";

/// ActivePackages new-format key prefix and field separator
/// (desktop/source/deployment/manager/dp_activepackages.cxx).
pub const SEP: u8 = 0xff;

pub type Entries = BTreeMap<Vec<u8>, Vec<u8>>;

fn encode(raw: &[u8], out: &mut Vec<u8>) {
    for &b in raw {
        if b <= 0x0f {
            out.push(b'%');
            out.push(if b <= 9 { b'0' + b } else { b'A' + (b - 10) });
        } else if b == b'%' {
            out.extend_from_slice(b"%%");
        } else {
            out.push(b);
        }
    }
}

fn decode(line: &[u8]) -> Vec<u8> {
    let mut out = Vec::with_capacity(line.len());
    let mut it = line.iter().copied();
    while let Some(b) = it.next() {
        if b != b'%' {
            out.push(b);
            continue;
        }
        match it.next() {
            Some(c @ b'0'..=b'9') => out.push(c - b'0'),
            Some(c @ b'A'..=b'F') => out.push(c - b'A' + 10),
            Some(b'%') => out.push(b'%'),
            Some(c) => out.push(c),
            None => break,
        }
    }
    out
}

pub fn read(path: &Path) -> io::Result<Entries> {
    let mut entries = Entries::new();
    let data = match std::fs::read(path) {
        Ok(d) => d,
        Err(e) if e.kind() == io::ErrorKind::NotFound => return Ok(entries),
        Err(e) => return Err(e),
    };
    let Some(body) = data.strip_prefix(MAGIC) else {
        return Err(io::Error::new(
            io::ErrorKind::InvalidData,
            format!("{}: bad PersistentMap magic", path.display()),
        ));
    };
    let mut lines = body.split(|&b| b == b'\n').map(|l| l.strip_suffix(b"\r").unwrap_or(l));
    while let Some(key) = lines.next() {
        if key.is_empty() {
            break;
        }
        let Some(value) = lines.next() else { break };
        entries.insert(decode(key), decode(value));
    }
    Ok(entries)
}

pub fn write(path: &Path, entries: &Entries) -> io::Result<()> {
    let mut buf = Vec::new();
    buf.extend_from_slice(MAGIC);
    for (k, v) in entries {
        encode(k, &mut buf);
        buf.push(b'\n');
        encode(v, &mut buf);
        buf.push(b'\n');
    }
    buf.push(b'\n');
    crate::atomic_write(path, &buf)
}

/// One ActivePackages record (new format).
pub struct ActiveEntry {
    pub identifier: String,
    pub temporary_name: String,
    pub file_name: String,
    pub media_type: String,
    pub version: String,
    pub failed_prerequisites: String,
}

impl ActiveEntry {
    pub fn key(identifier: &str) -> Vec<u8> {
        let mut k = vec![SEP];
        k.extend_from_slice(identifier.as_bytes());
        k
    }

    pub fn to_value(&self) -> Vec<u8> {
        let fields = [
            self.temporary_name.as_str(),
            self.file_name.as_str(),
            self.media_type.as_str(),
            self.version.as_str(),
            self.failed_prerequisites.as_str(),
        ];
        let mut v = Vec::new();
        for (i, f) in fields.iter().enumerate() {
            if i > 0 {
                v.push(SEP);
            }
            v.extend_from_slice(f.as_bytes());
        }
        v
    }

    pub fn parse(key: &[u8], value: &[u8]) -> Option<ActiveEntry> {
        let identifier = String::from_utf8(key.strip_prefix(&[SEP])?.to_vec()).ok()?;
        let mut fields = value.split(|&b| b == SEP).map(|f| String::from_utf8_lossy(f).into_owned());
        Some(ActiveEntry {
            identifier,
            temporary_name: fields.next()?,
            file_name: fields.next()?,
            media_type: fields.next()?,
            version: fields.next().unwrap_or_default(),
            failed_prerequisites: fields.next().unwrap_or_default(),
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn roundtrip_escaping() {
        let mut raw = vec![0x00, 0x0a, 0x0f, b'%', b'a', 0xff];
        raw.extend_from_slice(b"plain");
        let mut enc = Vec::new();
        encode(&raw, &mut enc);
        assert_eq!(enc, b"%0%A%F%%a\xffplain");
        assert_eq!(decode(&enc), raw);
    }

    #[test]
    fn gold_layout() {
        // Mirrors the byte-exact state unopkg wrote on a real machine.
        let e = ActiveEntry {
            identifier: "no.divvun.DivvunSpell".into(),
            temporary_name: "lu792599kkov8.tmp".into(),
            file_name: "macos.oxt".into(),
            media_type: "application/vnd.sun.star.package-bundle".into(),
            version: "0.5.0".into(),
            failed_prerequisites: "0".into(),
        };
        let mut entries = Entries::new();
        entries.insert(ActiveEntry::key(&e.identifier), e.to_value());
        let mut buf = Vec::new();
        buf.extend_from_slice(MAGIC);
        for (k, v) in &entries {
            encode(k, &mut buf);
            buf.push(b'\n');
            encode(v, &mut buf);
            buf.push(b'\n');
        }
        buf.push(b'\n');
        let expected: &[u8] = b"Pmp1\xffno.divvun.DivvunSpell\nlu792599kkov8.tmp\xffmacos.oxt\xffapplication/vnd.sun.star.package-bundle\xff0.5.0\xff0\n\n";
        assert_eq!(buf, expected);
    }
}
