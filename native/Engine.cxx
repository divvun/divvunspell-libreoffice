#include "Engine.hxx"
#include "ErrorClass.hxx"
#include "Platform.hxx"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace divvun {

namespace {

namespace fs = std::filesystem;

std::string toBcp47Tag(std::string s) {
    std::replace(s.begin(), s.end(), '_', '-');
    return s;
}

std::string baseTag(const std::string& tag) {
    auto pos = tag.find('-');
    return pos == std::string::npos ? tag : tag.substr(0, pos);
}

// Lower-cased, '-'-separated, for comparing locale tags.
std::string normalizedTag(std::string s) {
    std::replace(s.begin(), s.end(), '_', '-');
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

std::string truncatedForLog(std::string_view s, size_t max = 1000) {
    if (s.size() <= max) return std::string(s);
    return std::string(s.substr(0, max)) + "...[truncated " + std::to_string(s.size() - max) + " bytes]";
}

std::string locatesJsonPath() {
    auto dir = componentDir();
    if (dir.empty()) return "locales.json";
    return (fs::path(dir) / "locales.json").string();
}

void addDrb(const fs::path& p, std::map<std::string, std::string>& out) {
    auto tag = toBcp47Tag(p.stem().string());
    out.try_emplace(tag, p.string());
    auto bt = baseTag(tag);
    if (bt != tag) out.try_emplace(bt, p.string());
}

#if defined(__APPLE__)

// On macOS the .drb files live inside service bundles in the Services dir:
//   <base>/no.divvun.proofing.<tag>.bundle/Contents/Resources/<tag>.drb
// Mirror MacDivvun: walk bundles matching the no.divvun.proofing. prefix and
// scan their Contents/Resources for .drb files.
void scanInto(const std::string& base, std::map<std::string, std::string>& out) {
    static const std::string kPrefix = "no.divvun.proofing.";
    static const std::string kSuffix = ".bundle";

    std::error_code ec;
    if (!fs::is_directory(base, ec)) return;

    for (auto it = fs::directory_iterator(base, fs::directory_options::skip_permission_denied, ec);
         !ec && it != fs::directory_iterator(); it.increment(ec)) {
        const auto name = it->path().filename().string();
        if (name.size() < kPrefix.size() + kSuffix.size()) continue;
        if (name.compare(0, kPrefix.size(), kPrefix) != 0) continue;
        if (name.compare(name.size() - kSuffix.size(), kSuffix.size(), kSuffix) != 0) continue;

        const auto resources = it->path() / "Contents" / "Resources";
        std::error_code rec;
        if (!fs::is_directory(resources, rec)) continue;
        for (auto rit = fs::directory_iterator(resources, fs::directory_options::skip_permission_denied, rec);
             !rec && rit != fs::directory_iterator(); rit.increment(rec)) {
            if (rit->is_regular_file(rec) && rit->path().extension() == ".drb") {
                addDrb(rit->path(), out);
            }
        }
    }
}

#else

// Windows/Linux: flat <tag>.drb files directly in the proofing dir.
void scanInto(const std::string& base, std::map<std::string, std::string>& out) {
    std::error_code ec;
    if (!fs::is_directory(base, ec)) return;

    for (auto it = fs::directory_iterator(base, fs::directory_options::skip_permission_denied, ec);
         !ec && it != fs::directory_iterator(); it.increment(ec)) {
        const auto& entry = *it;
        if (entry.is_regular_file(ec) && entry.path().extension() == ".drb") {
            addDrb(entry.path(), out);
        }
    }
}

#endif

} // namespace

Engine& Engine::instance() {
    static Engine inst;
    return inst;
}

bool Engine::traceEnabled() {
    static const bool enabled = []() {
        const char* v = std::getenv("DIVVUNSPELL_TRACE");
        return v && v[0] != '\0' && std::string(v) != "0";
    }();
    return enabled;
}

void Engine::trace(const std::string& msg) {
    if (!traceEnabled()) return;
    logLine(std::string("TRACE ") + msg);
}

Engine::Engine() {
    scanBundlePaths();
    loadBundleLocales();

    auto path = locatesJsonPath();
    std::ifstream f(path);
    if (f) {
        try {
            nlohmann::json j;
            f >> j;
            if (j.is_object()) {
                for (auto& [k, v] : j.items()) {
                    if (v.is_array()) {
                        std::vector<std::string> vs;
                        for (auto& c : v) if (c.is_string()) vs.push_back(c.get<std::string>());
                        mLocaleVariants.emplace(k, std::move(vs));
                    }
                }
            }
        } catch (const std::exception& e) {
            logLine(std::string("Engine: locales.json parse failed: ") + e.what());
        }
    } else {
        logLine("Engine: locales.json missing at " + path);
    }

    loadPrefs();

    std::ostringstream s;
    s << "Engine: discovered " << mBundlePaths.size() << " bundle entries";
    for (auto& [k, v] : mBundlePaths) s << "\n    " << k << " -> " << v;
    if (!mIgnoredByTag.empty()) {
        s << "\nEngine: loaded prefs for " << mIgnoredByTag.size() << " tag(s)";
        for (const auto& [tag, set] : mIgnoredByTag) {
            s << "\n    " << tag << ": ";
            for (const auto& r : set) s << r << " ";
        }
    }
    logLine(s.str());
}

Engine::~Engine() {
    std::lock_guard<std::mutex> lk(mLock);
    dropAllPipelinesLocked();
    for (auto& [tag, b] : mBundles) RuntimeBridge::instance().bundleDrop(b);
    mBundles.clear();
}

void Engine::scanBundlePaths() {
    for (auto& base : bundleSearchPaths()) scanInto(base, mBundlePaths);
}

// Read each bundle's declared locales. This only touches the archive's metadata
// trailer, not its pipeline, so it stays cheap enough to do for every installed
// bundle at startup — loading them here would parse gigabytes.
void Engine::loadBundleLocales() {
    std::set<std::string> visited;
    for (const auto& [tag, path] : mBundlePaths) {
        // addDrb registers both the full tag and its base against one file.
        if (!visited.insert(path).second) continue;

        std::string csv;
        try {
            csv = RuntimeBridge::instance().bundleMetadataAttr(path, "drb.locales");
        } catch (const RuntimeError& e) {
            logLine("Engine: could not read drb.locales from " + path + ": " + e.what());
            continue;
        }
        if (csv.empty()) continue; // built before the attribute existed

        std::vector<std::string> tags;
        std::istringstream ss(csv);
        std::string item;
        while (std::getline(ss, item, ',')) {
            if (!item.empty()) tags.push_back(toBcp47Tag(item));
        }
        if (!tags.empty()) mBundleLocales[baseTag(tag)] = std::move(tags);
    }
}

bool Engine::ready() const {
    return true;
}

bool Engine::hasTag(const std::string& tag) const {
    if (tag.empty() || !ready()) return false;
    if (mBundlePaths.count(tag)) return true;
    return mBundlePaths.count(baseTag(tag)) > 0;
}

std::string Engine::resolveTag(const std::string& tag) const {
    if (mBundlePaths.count(tag)) return tag;
    return baseTag(tag);
}

std::string Engine::buildConfigJsonLocked(const std::string& tag) {
    nlohmann::json suggest = { {"encoding", "utf-16"} };
    // Messages in the user's chosen language, else the checked language; the
    // runtime falls back to "en" and then any loaded bundle on its own.
    auto locales = nlohmann::json::array();
    const auto messages = effectiveMessageLocaleLocked(tag, messageLocaleLocked(tag));
    if (messages != tag) locales.push_back(messages);
    locales.push_back(tag);
    suggest["locales"] = locales;
    auto it = mIgnoredByTag.find(tag);
    if (it != mIgnoredByTag.end() && !it->second.empty()) {
        suggest["ignore"] = std::vector<std::string>(it->second.begin(), it->second.end());
    }
    nlohmann::json j = { {"suggestions", suggest} };
    return j.dump();
}

// Erasing only drops the map's reference: in-flight Engine::run calls hold
// their own shared_ptr, so the handle/lock outlive the erase until they finish.
void Engine::dropPipelineForTagLocked(const std::string& tag) {
    mPipelines.erase(tag);
    mSpellCache.erase(tag);
}

// Settings are kept per base tag, but a bundle filed under a full tag gets
// its pipeline keyed by that.
void Engine::dropPipelinesForBaseTagLocked(const std::string& base) {
    for (auto it = mPipelines.begin(); it != mPipelines.end();) {
        if (baseTag(it->first) == base) it = mPipelines.erase(it);
        else ++it;
    }
}

void Engine::dropAllPipelinesLocked() {
    mPipelines.clear();
}

void Engine::dropSpellCacheLocked() {
    mSpellCache.clear();
}

void* Engine::ensureBundleLocked(const std::string& resolvedTag) {
    auto bit = mBundles.find(resolvedTag);
    if (bit != mBundles.end()) return bit->second;
    auto pit = mBundlePaths.find(resolvedTag);
    if (pit == mBundlePaths.end()) return nullptr;
    void* bundle = RuntimeBridge::instance().bundleFromBundle(pit->second);
    mBundles.emplace(resolvedTag, bundle);
    return bundle;
}

std::string Engine::run(const std::string& tag, std::string_view text) {
    if (!ready()) return {};
    auto resolved = resolveTag(tag);

    std::shared_ptr<PipelineEntry> entry;
    {
        std::lock_guard<std::mutex> lk(mLock);
        auto pit = mBundlePaths.find(resolved);
        if (pit == mBundlePaths.end()) return {};

        auto hit = mPipelines.find(resolved);
        if (hit != mPipelines.end()) {
            entry = hit->second;
        } else {
            void* bundle = ensureBundleLocked(resolved);
            if (!bundle) return {};
            auto config = buildConfigJsonLocked(resolved);
            entry = std::make_shared<PipelineEntry>(
                RuntimeBridge::instance().bundleCreate(bundle, config));
            mPipelines.emplace(resolved, entry);
        }
    }

    if (traceEnabled()) {
        trace("forward[" + resolved + "] in: " + truncatedForLog(text));
    }
    std::string out;
    {
        std::lock_guard<std::mutex> tl(entry->lock);
        out = RuntimeBridge::instance().pipelineForward(entry->handle, text);
    }
    if (traceEnabled()) {
        trace("forward[" + resolved + "] out: " + truncatedForLog(out));
    }
    return out;
}

std::vector<LocaleTag> Engine::locales() const {
    std::lock_guard<std::mutex> lk(mLock);
    std::vector<LocaleTag> out;
    for (const auto& [tag, _] : mBundlePaths) {
        auto dashes = std::count(tag.begin(), tag.end(), '-');
        if (dashes > 1) continue;
        if (dashes == 1) {
            auto pos = tag.find('-');
            out.push_back({ tag.substr(0, pos), tag.substr(pos + 1) });
        } else {
            out.push_back({ tag, "" });
            // The bundle's own declaration wins: it comes from the language's
            // manifest, where locales.json is a snapshot of LibreOffice's table
            // taken once and never regenerated.
            auto bit = mBundleLocales.find(tag);
            if (bit != mBundleLocales.end()) {
                for (const auto& full : bit->second) {
                    auto pos = full.find('-');
                    // LocaleTag holds only language+country. Anything richer
                    // (script or extension subtags) needs the qlt/Variant form
                    // LibreOffice expects, which this cannot express, so drop
                    // it loudly rather than truncate it into the wrong locale.
                    if (pos == std::string::npos
                        || full.find('-', pos + 1) != std::string::npos) {
                        logLine("Engine: skipping unsupported locale tag " + full
                                + " declared by bundle " + tag);
                        continue;
                    }
                    out.push_back({ full.substr(0, pos), full.substr(pos + 1) });
                }
                continue;
            }
            auto vit = mLocaleVariants.find(tag);
            if (vit != mLocaleVariants.end()) {
                for (const auto& country : vit->second) {
                    out.push_back({ tag, country });
                }
            }
        }
    }
    return out;
}

std::vector<std::string> Engine::discoveredTags() const {
    std::lock_guard<std::mutex> lk(mLock);
    std::vector<std::string> out;
    for (const auto& [tag, _] : mBundlePaths) {
        if (tag.find('-') == std::string::npos) out.push_back(tag);
    }
    return out;
}

std::vector<std::pair<std::string, std::string>>
Engine::errorPreferences(const std::string& tag, const std::string& uiLocale) {
    if (!ready()) return {};
    auto resolved = resolveTag(tag);
    std::pair<std::string, std::string> cacheKey{resolved, uiLocale};

    {
        std::lock_guard<std::mutex> lk(mLock);
        auto it = mErrorPrefsCache.find(cacheKey);
        if (it != mErrorPrefsCache.end()) return it->second;
    }

    void* bundle = nullptr;
    try {
        std::lock_guard<std::mutex> lk(mLock);
        bundle = ensureBundleLocked(resolved);
    } catch (const RuntimeError& e) {
        logLine("Engine::errorPreferences bundle load failed for " + resolved + ": " + e.what());
        return {};
    }
    if (!bundle) return {};

    nlohmann::json locales = nlohmann::json::array();
    if (!uiLocale.empty()) locales.push_back(uiLocale);
    if (resolved != uiLocale) locales.push_back(resolved);
    if (uiLocale != "en") locales.push_back("en");

    std::string responseJson;
    try {
        responseJson = RuntimeBridge::instance().bundleErrorPreferences(bundle, locales.dump());
    } catch (const RuntimeError& e) {
        logLine(std::string("Engine::errorPreferences error: ") + e.what());
        return {};
    }

    std::vector<std::pair<std::string, std::string>> result;
    try {
        auto parsed = nlohmann::json::parse(responseJson);
        if (parsed.is_object()) {
            for (auto& [k, v] : parsed.items()) {
                if (v.is_string()) result.emplace_back(k, v.get<std::string>());
            }
        }
    } catch (const std::exception& e) {
        logLine(std::string("Engine::errorPreferences json error: ") + e.what());
        return {};
    }

    {
        std::lock_guard<std::mutex> lk(mLock);
        mErrorPrefsCache[cacheKey] = result;
    }
    return result;
}

std::set<std::string> Engine::ignoredRules(const std::string& tag) const {
    std::lock_guard<std::mutex> lk(mLock);
    auto resolved = mBundlePaths.count(tag) ? tag : baseTag(tag);
    auto it = mIgnoredByTag.find(resolved);
    return it == mIgnoredByTag.end() ? std::set<std::string>{} : it->second;
}

void Engine::setIgnoredRules(const std::string& tag, std::set<std::string> rules) {
    {
        std::lock_guard<std::mutex> lk(mLock);
        auto resolved = mBundlePaths.count(tag) ? tag : baseTag(tag);
        mIgnoredByTag[resolved] = std::move(rules);
        dropPipelineForTagLocked(resolved);
    }
    savePrefs();
    logLine("Engine: ignore set replaced for " + tag);
}

void Engine::addIgnoredRule(const std::string& tag, const std::string& ruleId) {
    if (ruleId.empty()) return;
    {
        std::lock_guard<std::mutex> lk(mLock);
        auto resolved = mBundlePaths.count(tag) ? tag : baseTag(tag);
        if (!mIgnoredByTag[resolved].insert(ruleId).second) return;
        dropPipelineForTagLocked(resolved);
    }
    savePrefs();
    logLine("Engine: ignore rule added: " + tag + "/" + ruleId);
}

void Engine::resetIgnoredRules() {
    {
        std::lock_guard<std::mutex> lk(mLock);
        if (mIgnoredByTag.empty()) return;
        mIgnoredByTag.clear();
        dropAllPipelinesLocked();
        dropSpellCacheLocked();
    }
    savePrefs();
    logLine("Engine: ignore rules reset");
}

std::string Engine::messageLocaleLocked(const std::string& tag) const {
    auto it = mMessageLocaleByTag.find(baseTag(tag));
    return it == mMessageLocaleByTag.end() ? std::string{} : it->second;
}

std::string Engine::messageLocale(const std::string& tag) const {
    std::lock_guard<std::mutex> lk(mLock);
    return messageLocaleLocked(tag);
}

void Engine::setMessageLocale(const std::string& tag, const std::string& locale) {
    const auto base = baseTag(tag);
    {
        std::lock_guard<std::mutex> lk(mLock);
        if (messageLocaleLocked(base) == locale) return;
        if (locale.empty()) mMessageLocaleByTag.erase(base);
        else mMessageLocaleByTag[base] = locale;
        dropPipelinesForBaseTagLocked(base);
    }
    savePrefs();
    logLine("Engine: message locale for " + base + " set to "
            + (locale.empty() ? std::string("<checked language>") : locale));
}

// Not cached when the bundle fails to load, so a later call can retry.
const std::vector<std::string>& Engine::messageLocalesLocked(const std::string& resolvedTag) {
    static const std::vector<std::string> kNone;
    auto cached = mMessageLocalesCache.find(resolvedTag);
    if (cached != mMessageLocalesCache.end()) return cached->second;

    void* bundle = nullptr;
    try {
        bundle = ensureBundleLocked(resolvedTag);
    } catch (const RuntimeError& e) {
        logLine("Engine::messageLocales bundle load failed for " + resolvedTag + ": " + e.what());
        return kNone;
    }
    if (!bundle) return kNone;

    std::vector<std::string> result;
    try {
        auto parsed = nlohmann::json::parse(RuntimeBridge::instance().bundleMessageLocales(bundle));
        if (parsed.is_array()) {
            for (auto& v : parsed) if (v.is_string()) result.push_back(v.get<std::string>());
        }
    } catch (const std::exception& e) {
        logLine("Engine::messageLocales failed for " + resolvedTag + ": " + e.what());
    }
    return mMessageLocalesCache[resolvedTag] = std::move(result);
}

std::vector<std::string> Engine::messageLocales(const std::string& tag) {
    if (!ready()) return {};
    std::lock_guard<std::mutex> lk(mLock);
    return messageLocalesLocked(resolveTag(tag));
}

std::string Engine::effectiveMessageLocaleLocked(const std::string& resolvedTag, const std::string& setting) {
    if (setting.empty()) return resolvedTag;
    if (setting != kSameAsUi) return setting;
    if (mUiLocale.empty()) return resolvedTag;

    // An exact match first, then by language alone: "nb-NO" gets "nb".
    const auto& available = messageLocalesLocked(resolvedTag);
    const auto ui = normalizedTag(mUiLocale);
    for (const auto& code : available) {
        if (normalizedTag(code) == ui) return code;
    }
    for (const auto& code : available) {
        if (baseTag(normalizedTag(code)) == baseTag(ui)) return code;
    }
    return resolvedTag;
}

std::string Engine::effectiveMessageLocale(const std::string& tag, const std::string& setting) {
    std::lock_guard<std::mutex> lk(mLock);
    return effectiveMessageLocaleLocked(resolveTag(tag), setting);
}

void Engine::setUiLocale(const std::string& locale) {
    {
        std::lock_guard<std::mutex> lk(mLock);
        if (mUiLocale == locale) return;
        mUiLocale = locale;
        for (const auto& [base, setting] : mMessageLocaleByTag) {
            if (setting == kSameAsUi) dropPipelinesForBaseTagLocked(base);
        }
    }
    logLine("Engine: UI locale is " + (locale.empty() ? std::string("<unknown>") : locale));
}

std::string Engine::prefsPath() const {
    return divvun::prefsPath();
}

void Engine::loadPrefs() {
    std::ifstream f(prefsPath());
    if (!f) return;
    try {
        nlohmann::json j;
        f >> j;
        if (!j.is_object()) return;
        if (j.contains("messageLocale") && j["messageLocale"].is_object()) {
            for (auto& [tag, code] : j["messageLocale"].items()) {
                if (code.is_string() && !code.get<std::string>().empty())
                    mMessageLocaleByTag[tag] = code.get<std::string>();
            }
        } else if (j.contains("messageLocale") && j["messageLocale"].is_string()) {
            // Older files held one setting for every language. Keep it for
            // each installed one: where a bundle lacks that locale the
            // runtime falls back to the checked language, as it did then.
            const auto code = j["messageLocale"].get<std::string>();
            if (!code.empty()) {
                for (const auto& [tag, _] : mBundlePaths) mMessageLocaleByTag[baseTag(tag)] = code;
            }
        }
        if (!j.contains("ignored") || !j["ignored"].is_object()) return;
        for (auto& [tag, arr] : j["ignored"].items()) {
            if (!arr.is_array()) continue;
            std::set<std::string> set;
            for (auto& v : arr) if (v.is_string()) set.insert(v.get<std::string>());
            if (!set.empty()) mIgnoredByTag[tag] = std::move(set);
        }
    } catch (const std::exception& e) {
        logLine(std::string("Engine::loadPrefs error: ") + e.what());
    }
}

void Engine::savePrefs() const {
    auto path = prefsPath();
    fs::path p(path);
    std::error_code ec;
    fs::create_directories(p.parent_path(), ec);

    nlohmann::json j;
    j["version"] = 1;
    nlohmann::json ignored = nlohmann::json::object();
    {
        std::lock_guard<std::mutex> lk(mLock);
        for (const auto& [tag, set] : mIgnoredByTag) {
            ignored[tag] = std::vector<std::string>(set.begin(), set.end());
        }
        j["messageLocale"] = mMessageLocaleByTag;
    }
    j["ignored"] = ignored;

    auto tmp = path + ".tmp";
    {
        std::ofstream f(tmp);
        if (!f) {
            logLine("Engine::savePrefs: could not open " + tmp);
            return;
        }
        f << j.dump(2);
    }
    std::error_code mec;
    fs::rename(tmp, path, mec);
    if (mec) logLine("Engine::savePrefs rename failed: " + mec.message());
}

// Results are cached alongside single words. A bundle that can't do the
// lookup is remembered, so it's logged once and then rejected like before;
// a bundle that fails to load isn't, so a later call can retry.
bool Engine::multiWordIsCorrect(const std::string& resolvedTag, const std::string& words) {
    void* bundle = nullptr;
    try {
        std::lock_guard<std::mutex> lk(mLock);
        if (mNoLexiconLookup.count(resolvedTag)) return false;
        bundle = ensureBundleLocked(resolvedTag);
    } catch (const RuntimeError& e) {
        logLine("Engine::spellCheck bundle load failed for " + resolvedTag + ": " + e.what());
        return false;
    }
    if (!bundle) return false;

    bool valid = false;
    try {
        valid = RuntimeBridge::instance().bundleIsCorrect(bundle, words);
    } catch (const RuntimeError& e) {
        logLine("Engine::spellCheck lexicon lookup failed for " + resolvedTag + ": " + e.what());
        std::lock_guard<std::mutex> lk(mLock);
        mNoLexiconLookup.insert(resolvedTag);
        return false;
    }

    {
        std::lock_guard<std::mutex> lk(mLock);
        mSpellCache[resolvedTag][words] = SpellResult{valid, {}};
    }
    if (traceEnabled()) {
        trace("spellCheck[" + resolvedTag + "] lexicon word=" + words
              + " valid=" + (valid ? "true" : "false"));
    }
    return valid;
}

SpellResult Engine::spellCheck(const std::string& tag, const std::string& word) {
    if (!ready() || word.empty()) return {true, {}};

    auto resolved = resolveTag(tag);

    {
        std::lock_guard<std::mutex> lk(mLock);
        auto outerIt = mSpellCache.find(resolved);
        if (outerIt != mSpellCache.end()) {
            auto innerIt = outerIt->second.find(word);
            if (innerIt != outerIt->second.end()) {
                if (traceEnabled()) {
                    trace("spellCheck[" + resolved + "] CACHE HIT word=" + word
                          + " valid=" + (innerIt->second.valid ? "true" : "false"));
                }
                return innerIt->second;
            }
        }
    }
    if (traceEnabled()) trace("spellCheck[" + resolved + "] CACHE MISS word=" + word);

    // Writer re-checks a misspelled word joined with a neighbour ("okta okta")
    // to find multi-word dictionary entries, and drops the underline when that
    // comes back valid. The pipeline would only say every token in it is
    // spelled correctly, which is not the same thing, so ask the speller's
    // lexicon whether the whole string is one entry.
    if (word.find_first_of(" \t\r\n") != std::string::npos) {
        return {multiWordIsCorrect(resolved, word), {}};
    }

    std::string responseJson;
    try {
        responseJson = run(tag, word);
    } catch (const RuntimeError& e) {
        logLine(std::string("Engine::spellCheck error: ") + e.what());
        return {true, {}};
    }
    if (responseJson.empty()) return {true, {}};

    SpellResult res{true, {}};
    try {
        auto parsed = nlohmann::json::parse(responseJson);
        if (parsed.is_object() && parsed.contains("errors") && parsed["errors"].is_array()) {
            for (auto& err : parsed["errors"]) {
                if (!err.is_object()) continue;
                auto errorId = err.value("error_id", std::string{});
                if (!isSpellError(errorId)) continue;
                res.valid = false;
                if (err.contains("suggestions") && err["suggestions"].is_array()) {
                    for (auto& s : err["suggestions"]) {
                        if (s.is_string()) res.suggestions.push_back(s.get<std::string>());
                    }
                }
                break;
            }
        }
    } catch (const std::exception& e) {
        logLine(std::string("Engine::spellCheck json error: ") + e.what());
        return {true, {}};
    }

    {
        std::lock_guard<std::mutex> lk(mLock);
        mSpellCache[resolved][word] = res;
    }
    if (traceEnabled()) {
        std::ostringstream s;
        s << "spellCheck[" << resolved << "] result word=" << word
          << " valid=" << (res.valid ? "true" : "false")
          << " suggestions=" << res.suggestions.size();
        for (const auto& sug : res.suggestions) s << "\n    \"" << sug << "\"";
        trace(s.str());
    }
    return res;
}

} // namespace divvun
