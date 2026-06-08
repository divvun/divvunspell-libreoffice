#pragma once

#include <string>
#include <vector>

namespace divvun {

// Append a line to the per-session log file (and OS log on macOS).
// Safe to call before any other Engine state exists.
void logLine(const std::string& msg);

// Directories scanned for installed Divvun proofing bundles. On macOS these are
// the Services dirs holding no.divvun.proofing.<tag>.bundle (the Engine scan
// descends into Contents/Resources for the .drb); on Windows/Linux they are a
// flat Divvun/Proofing dir of <tag>.drb files.
// Order matters: earlier entries win on tag collisions.
std::vector<std::string> bundleSearchPaths();

// Absolute path to the per-user prefs JSON. Parent dirs created on first save.
std::string prefsPath();

// Directory containing the host shared library (the UNO component itself).
// Used to find sibling resources like locales.json.
std::string componentDir();

} // namespace divvun
