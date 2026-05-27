#pragma once

#include <string>
#include <vector>

namespace divvun {

// Append a line to the per-session log file (and OS log on macOS).
// Safe to call before any other Engine state exists.
void logLine(const std::string& msg);

// Directories scanned for installed Divvun bundles (.drb or pipeline.json).
// Order matters: earlier entries win on tag collisions.
std::vector<std::string> bundleSearchPaths();

// Absolute path to the per-user prefs JSON. Parent dirs created on first save.
std::string prefsPath();

// Directory containing the host shared library (the UNO component itself).
// Used to find sibling resources like locales.json.
std::string componentDir();

} // namespace divvun
