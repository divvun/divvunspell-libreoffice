//! oxtreg — register LibreOffice OXT extensions by writing the user-profile
//! extension cache directly, without running unopkg.
//!
//! What `unopkg add` leaves on disk was reverse-engineered from
//! LibreOffice core (desktop/source/deployment/) and verified against a live
//! registered profile. At startup soffice reads the component list from the
//! user-cache `unorc` (via URE_MORE_SERVICES in fundamentalrc) and extension
//! configuration from `configmgr.ini` (via CONFIGURATION_LAYERS); the pmap
//! and backenddb.xml files are Extension Manager bookkeeping. We write all of
//! them so LibreOffice fully owns the extension afterwards (it shows up in
//! the Extension Manager and `unopkg remove` works on it).

mod oxt;
mod pmap;
mod registry;

use std::io;
use std::path::{Path, PathBuf};

use clap::{Parser, Subcommand};

use pmap::ActiveEntry;
use registry::{
    BundleDb, BundleExtension, BundleItem, ConfDb, ConfEntry, ConfigmgrIni, Unorc,
    BUNDLE_BACKEND, COMPONENT_BACKEND, CONFIGURATION_BACKEND, HELP_BACKEND,
};

const PACKAGE_BUNDLE: &str = "application/vnd.sun.star.package-bundle";
const MT_COMPONENTS: &str = "application/vnd.sun.star.uno-components";
const MT_CONFIG_SCHEMA: &str = "application/vnd.sun.star.configuration-schema";
const MT_CONFIG_DATA: &str = "application/vnd.sun.star.configuration-data";

#[derive(Parser)]
#[command(version, about = "Register LibreOffice OXT extensions without unopkg")]
struct Cli {
    /// LibreOffice user profile directory (default: the platform's
    /// LibreOffice/4/user location)
    #[arg(long, global = true)]
    profile: Option<PathBuf>,

    /// Register into the shared (all-users) extension cache of the given
    /// LibreOffice installation directory instead of the per-user profile.
    /// The cache is written under <DIR>/share/uno_packages/cache. Takes
    /// precedence over --profile.
    #[arg(long, global = true, value_name = "LIBREOFFICE_DIR")]
    shared: Option<PathBuf>,

    #[command(subcommand)]
    command: Command,
}

#[derive(Subcommand)]
enum Command {
    /// Register an OXT for the current user (replaces any same-id extension)
    Install { oxt: PathBuf },
    /// Unregister an extension by identifier
    Uninstall { identifier: String },
    /// List registered extensions
    List,
}

fn default_profile() -> Option<PathBuf> {
    #[cfg(target_os = "macos")]
    {
        let home = std::env::var_os("HOME")?;
        Some(PathBuf::from(home).join("Library/Application Support/LibreOffice/4/user"))
    }
    #[cfg(target_os = "windows")]
    {
        let appdata = std::env::var_os("APPDATA")?;
        Some(PathBuf::from(appdata).join("LibreOffice").join("4").join("user"))
    }
    #[cfg(not(any(target_os = "macos", target_os = "windows")))]
    {
        let home = std::env::var_os("HOME")?;
        Some(PathBuf::from(home).join(".config/libreoffice/4/user"))
    }
}

pub fn atomic_write(path: &Path, data: &[u8]) -> io::Result<()> {
    if let Some(parent) = path.parent() {
        std::fs::create_dir_all(parent)?;
    }
    let tmp = path.with_extension("oxtreg-tmp");
    std::fs::write(&tmp, data)?;
    std::fs::rename(&tmp, path)
}

struct Cache {
    root: PathBuf, // .../uno_packages/cache
    // The bootstrap variable LO expands the rc-terms from. User and shared
    // caches share an identical on-disk layout; only this prefix differs.
    cache_var: &'static str,
}

impl Cache {
    /// Per-user profile cache (`$UNO_USER_PACKAGES_CACHE`).
    fn user(profile: &Path) -> Cache {
        Cache {
            root: profile.join("uno_packages/cache"),
            cache_var: "UNO_USER_PACKAGES_CACHE",
        }
    }

    /// Shared (all-users) cache of a LibreOffice installation:
    /// `$UNO_SHARED_PACKAGES_CACHE` = `<install>/share/uno_packages/cache`.
    fn shared(install_dir: &Path) -> Cache {
        Cache {
            root: install_dir.join("share/uno_packages/cache"),
            cache_var: "UNO_SHARED_PACKAGES_CACHE",
        }
    }

    fn pmap_path(&self) -> PathBuf {
        self.root.join("uno_packages.pmap")
    }

    fn packages_dir(&self) -> PathBuf {
        self.root.join("uno_packages")
    }

    fn backend_dir(&self, backend: &str) -> PathBuf {
        self.root.join("registry").join(backend)
    }

    /// rc-term for a path under the activation dir, as LO writes it.
    fn rcterm(&self, temp_name: &str, oxt_file: &str, sub: &str) -> String {
        let mut s = format!("${}/uno_packages/{}_/{}", self.cache_var, temp_name, oxt_file);
        if !sub.is_empty() {
            s.push('/');
            s.push_str(sub);
        }
        s
    }

    fn expand_url(rcterm: &str) -> String {
        format!("vnd.sun.star.expand:{}", rcterm)
    }
}

fn generate_temp_name(packages_dir: &Path) -> String {
    use rand::Rng;
    let mut rng = rand::rng();
    loop {
        let suffix: String =
            (0..11).map(|_| rng.sample(rand::distr::Alphanumeric) as char).collect();
        let name = format!("lu{}.tmp", suffix.to_lowercase());
        if !packages_dir.join(&name).exists() && !packages_dir.join(format!("{name}_")).exists() {
            return name;
        }
    }
}

fn warn_if_office_running() {
    #[cfg(unix)]
    {
        let running = std::process::Command::new("pgrep")
            .arg("-x")
            .arg("soffice")
            .output()
            .map(|o| o.status.success())
            .unwrap_or(false);
        if running {
            eprintln!(
                "warning: LibreOffice is running; the extension will be available after restart"
            );
        }
    }
}

fn install(cache: &Cache, oxt_path: &Path) -> io::Result<()> {
    let parsed = oxt::parse(oxt_path)?;
    let oxt_file = oxt_path
        .file_name()
        .ok_or_else(|| io::Error::new(io::ErrorKind::InvalidInput, "OXT path has no file name"))?
        .to_string_lossy()
        .into_owned();

    warn_if_office_running();

    // Idempotent reinstall: drop any previous registration of this identifier.
    let mut entries = pmap::read(&cache.pmap_path())?;
    if entries.contains_key(&ActiveEntry::key(&parsed.identifier)) {
        uninstall_locked(cache, &mut entries, &parsed.identifier)?;
    }

    // Activation layer: marker file + dir, extracted OXT, properties file.
    let packages_dir = cache.packages_dir();
    std::fs::create_dir_all(&packages_dir)?;
    let temp_name = generate_temp_name(&packages_dir);
    std::fs::write(packages_dir.join(&temp_name), b"")?;
    let activation_dir = packages_dir.join(format!("{temp_name}_"));
    let extract_dir = activation_dir.join(&oxt_file);
    std::fs::create_dir_all(&extract_dir)?;
    oxt::extract(oxt_path, &extract_dir)?;
    std::fs::write(
        activation_dir.join(format!("{oxt_file}properties")),
        b"SUPPRESS_LICENSE=0",
    )?;

    // Backend registrations, driven by the manifest media-types.
    let mut unorc = Unorc::load(&cache.backend_dir(COMPONENT_BACKEND), cache.cache_var)?;
    let mut ini = ConfigmgrIni::load(&cache.backend_dir(CONFIGURATION_BACKEND))?;
    let mut confdb = ConfDb::load(&cache.backend_dir(CONFIGURATION_BACKEND))?;
    let mut bundledb = BundleDb::load(&cache.backend_dir(BUNDLE_BACKEND))?;

    // Mirror LO's registration order (dp_package.cxx "sort: schema before
    // config data, typelibs before components"): schemas lead, components and
    // config data trail.
    let mut ordered: Vec<&oxt::ManifestEntry> = parsed.entries.iter().collect();
    ordered.sort_by_key(|e| match e.media_type.as_str() {
        MT_CONFIG_SCHEMA => 0,
        MT_COMPONENTS => 2,
        MT_CONFIG_DATA => 3,
        _ => 1,
    });

    let mut bundle_items = Vec::new();
    for entry in ordered {
        let rcterm = cache.rcterm(&temp_name, &oxt_file, &entry.full_path);
        let url = Cache::expand_url(&rcterm);
        match entry.media_type.as_str() {
            MT_COMPONENTS => unorc.services.push(format!("?{rcterm}")),
            MT_CONFIG_SCHEMA => {
                ini.schemas.push(rcterm.clone());
                confdb.entries.push(ConfEntry { url: url.clone(), ini_entry: rcterm.clone() });
            }
            MT_CONFIG_DATA => {
                ini.data.push(rcterm.clone());
                confdb.entries.push(ConfEntry { url: url.clone(), ini_entry: rcterm.clone() });
            }
            other => {
                eprintln!(
                    "warning: unsupported media-type {other} for {} (recorded in bundle db only)",
                    entry.full_path
                );
            }
        }
        bundle_items.push(BundleItem { url, media_type: entry.media_type.clone() });
    }
    bundledb.extensions.push(BundleExtension {
        url: Cache::expand_url(&cache.rcterm(&temp_name, &oxt_file, "")),
        items: bundle_items,
    });

    unorc.save()?;
    ini.save()?;
    confdb.save()?;
    bundledb.save()?;
    registry::ensure_help_db(&cache.backend_dir(HELP_BACKEND))?;

    // Finally the active-packages record.
    let active = ActiveEntry {
        identifier: parsed.identifier.clone(),
        temporary_name: temp_name,
        file_name: oxt_file,
        media_type: PACKAGE_BUNDLE.into(),
        version: parsed.version,
        failed_prerequisites: "0".into(),
    };
    entries.insert(ActiveEntry::key(&active.identifier), active.to_value());
    pmap::write(&cache.pmap_path(), &entries)?;

    println!("registered {}", parsed.identifier);
    Ok(())
}

/// Remove one identifier from an already-loaded pmap + all backend state.
fn uninstall_locked(cache: &Cache, entries: &mut pmap::Entries, identifier: &str) -> io::Result<()> {
    let key = ActiveEntry::key(identifier);
    let Some(value) = entries.remove(&key) else {
        return Err(io::Error::new(
            io::ErrorKind::NotFound,
            format!("{identifier} is not registered"),
        ));
    };
    let entry = ActiveEntry::parse(&key, &value)
        .ok_or_else(|| io::Error::new(io::ErrorKind::InvalidData, "corrupt pmap entry"))?;

    // Anything referencing the activation dir is this extension's.
    let needle = format!("/{}_/", entry.temporary_name);

    let mut unorc = Unorc::load(&cache.backend_dir(COMPONENT_BACKEND), cache.cache_var)?;
    unorc.services.retain(|t| !t.contains(&needle));
    unorc.save()?;

    let mut ini = ConfigmgrIni::load(&cache.backend_dir(CONFIGURATION_BACKEND))?;
    ini.schemas.retain(|t| !t.contains(&needle));
    ini.data.retain(|t| !t.contains(&needle));
    ini.save()?;

    let mut confdb = ConfDb::load(&cache.backend_dir(CONFIGURATION_BACKEND))?;
    confdb.entries.retain(|e| !e.url.contains(&needle));
    confdb.save()?;

    let mut bundledb = BundleDb::load(&cache.backend_dir(BUNDLE_BACKEND))?;
    bundledb.extensions.retain(|e| !e.url.contains(&needle));
    bundledb.save()?;

    let packages_dir = cache.packages_dir();
    let _ = std::fs::remove_file(packages_dir.join(&entry.temporary_name));
    let _ = std::fs::remove_dir_all(packages_dir.join(format!("{}_", entry.temporary_name)));

    Ok(())
}

fn uninstall(cache: &Cache, identifier: &str) -> io::Result<()> {
    warn_if_office_running();
    let mut entries = pmap::read(&cache.pmap_path())?;
    uninstall_locked(cache, &mut entries, identifier)?;
    pmap::write(&cache.pmap_path(), &entries)?;
    println!("unregistered {identifier}");
    Ok(())
}

fn list(cache: &Cache) -> io::Result<()> {
    let entries = pmap::read(&cache.pmap_path())?;
    for (key, value) in &entries {
        if let Some(e) = ActiveEntry::parse(key, value) {
            println!("{}\t{}\t{}", e.identifier, e.version, e.file_name);
        }
    }
    Ok(())
}

fn main() {
    let cli = Cli::parse();
    let cache = match cli.shared.as_deref() {
        Some(install_dir) => Cache::shared(install_dir),
        None => {
            let profile = cli.profile.clone().or_else(default_profile).unwrap_or_else(|| {
                eprintln!(
                    "error: could not determine the LibreOffice profile directory; pass --profile or --shared"
                );
                std::process::exit(2);
            });
            Cache::user(&profile)
        }
    };

    let result = match &cli.command {
        Command::Install { oxt } => install(&cache, oxt),
        Command::Uninstall { identifier } => uninstall(&cache, identifier),
        Command::List => list(&cache),
    };
    if let Err(e) = result {
        eprintln!("error: {e}");
        std::process::exit(1);
    }
}
