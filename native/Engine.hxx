#pragma once

#include "RuntimeBridge.hxx"

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace divvun {

struct LocaleTag {
    std::string language;
    std::string country;
};

struct SpellResult {
    bool valid;
    std::vector<std::string> suggestions;
};

// Shared-ownership wrapper for a runtime pipeline handle and its forward()
// serialization lock. Engine::run copies the shared_ptr out of the map under
// mLock, so dropPipelineForTag* can erase the map entry while a forward is in
// flight: the Rust handle and the mutex stay alive until the last user is done.
struct PipelineEntry {
    explicit PipelineEntry(void* h) : handle(h) {}
    ~PipelineEntry() { RuntimeBridge::instance().pipelineDrop(handle); }
    PipelineEntry(const PipelineEntry&) = delete;
    PipelineEntry& operator=(const PipelineEntry&) = delete;

    void* handle;
    std::mutex lock;
};

class Engine {
public:
    static Engine& instance();

    // Globally accessible trace logger. Reads DIVVUNSPELL_TRACE env at first use.
    // Routes through divvun::logLine (per-platform: temp-dir log file, plus
    // syslog on POSIX).
    static bool traceEnabled();
    static void trace(const std::string& msg);

    bool ready() const;

    // Locale lookup mirrors Python _Engine.has_tag/resolve_tag:
    bool hasTag(const std::string& tag) const;
    std::string resolveTag(const std::string& tag) const;

    // Run pipeline for the locale's bundle on the given UTF-8 text.
    // Returns the JSON response as a UTF-8 string.
    // Returns empty string if no bundle for tag (caller should treat as no-errors).
    std::string run(const std::string& tag, std::string_view text);

    // Per-word spell check, with caching. Returns valid=true and empty suggestions
    // when no spell-class error covers the entire word.
    SpellResult spellCheck(const std::string& tag, const std::string& word);

    // Returns all locale tags + variants from locales.json expansion.
    std::vector<LocaleTag> locales() const;

    // Discovered base tags (one per bundle, e.g. {"se","fo"}).
    std::vector<std::string> discoveredTags() const;

    // Categories + localized titles for a bundle. uiLocale falls back to "en".
    // Returns insertion-ordered vector of (category_id, localized_title).
    std::vector<std::pair<std::string, std::string>>
        errorPreferences(const std::string& tag, const std::string& uiLocale);

    // Read/write per-locale ignore set.
    std::set<std::string> ignoredRules(const std::string& tag) const;
    void setIgnoredRules(const std::string& tag, std::set<std::string> rules);

    // Implements XProofreader.ignoreRule(rule, locale): adds to per-tag set.
    void addIgnoredRule(const std::string& tag, const std::string& ruleId);
    // Implements XProofreader.resetIgnoreRules(): clears every tag's set.
    void resetIgnoredRules();

private:
    Engine();
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void scanBundlePaths();
    std::string buildConfigJsonLocked(const std::string& tag) const;
    void dropPipelineForTagLocked(const std::string& tag);
    void dropAllPipelinesLocked();
    void dropSpellCacheLocked();
    void* ensureBundleLocked(const std::string& resolvedTag);

    void loadPrefs();
    void savePrefs() const;
    std::string prefsPath() const;

    mutable std::mutex mLock;
    std::map<std::string, std::string> mBundlePaths;             // tag -> file/dir
    std::map<std::string, void*> mBundles;                       // tag -> bundle*
    std::map<std::string, std::shared_ptr<PipelineEntry>> mPipelines;
    std::map<std::string, std::set<std::string>> mIgnoredByTag;  // tag -> ignored category ids

    std::map<std::string, std::vector<std::string>> mLocaleVariants; // from locales.json

    // Per-tag word cache: tag -> word -> SpellResult.
    std::map<std::string, std::map<std::string, SpellResult>> mSpellCache;

    // Cached error_preferences result keyed by (tag, uiLocale).
    std::map<std::pair<std::string, std::string>,
             std::vector<std::pair<std::string, std::string>>> mErrorPrefsCache;
};

} // namespace divvun
