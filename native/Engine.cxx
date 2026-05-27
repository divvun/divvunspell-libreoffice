#include "Engine.hxx"
#include "ErrorClass.hxx"
#include "Platform.hxx"

#include <nlohmann/json.hpp>

#include <algorithm>
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

std::string truncatedForLog(std::string_view s, size_t max = 1000) {
    if (s.size() <= max) return std::string(s);
    return std::string(s.substr(0, max)) + "...[truncated " + std::to_string(s.size() - max) + " bytes]";
}

std::string locatesJsonPath() {
    auto dir = componentDir();
    if (dir.empty()) return "locales.json";
    return (fs::path(dir) / "locales.json").string();
}

void scanInto(const std::string& base, std::map<std::string, std::string>& out) {
    std::error_code ec;
    if (!fs::is_directory(base, ec)) return;

    for (auto it = fs::recursive_directory_iterator(base, fs::directory_options::skip_permission_denied, ec);
         !ec && it != fs::recursive_directory_iterator(); it.increment(ec)) {
        const auto& entry = *it;
        if (entry.is_regular_file(ec) && entry.path().extension() == ".drb") {
            auto tag = toBcp47Tag(entry.path().stem().string());
            out.try_emplace(tag, entry.path().string());
            auto bt = baseTag(tag);
            if (bt != tag) out.try_emplace(bt, entry.path().string());
        } else if (entry.is_directory(ec)) {
            std::error_code mec;
            if (fs::is_regular_file(entry.path() / "pipeline.json", mec)) {
                auto tag = toBcp47Tag(entry.path().filename().string());
                out.try_emplace(tag, entry.path().string());
                auto bt = baseTag(tag);
                if (bt != tag) out.try_emplace(bt, entry.path().string());
                it.disable_recursion_pending();
            }
        }
    }
}

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

std::string Engine::buildConfigJsonLocked(const std::string& tag) const {
    nlohmann::json suggest = { {"encoding", "utf-16"} };
    auto it = mIgnoredByTag.find(tag);
    if (it != mIgnoredByTag.end() && !it->second.empty()) {
        suggest["ignore"] = std::vector<std::string>(it->second.begin(), it->second.end());
    }
    nlohmann::json j = { {"suggest", suggest} };
    return j.dump();
}

void Engine::dropPipelineForTagLocked(const std::string& tag) {
    auto it = mPipelines.find(tag);
    if (it != mPipelines.end()) {
        RuntimeBridge::instance().pipelineDrop(it->second);
        mPipelines.erase(it);
    }
    mPipelineLocks.erase(tag);
    mSpellCache.erase(tag);
}

void Engine::dropAllPipelinesLocked() {
    for (auto& [tag, h] : mPipelines) RuntimeBridge::instance().pipelineDrop(h);
    mPipelines.clear();
    mPipelineLocks.clear();
}

void Engine::dropSpellCacheLocked() {
    mSpellCache.clear();
}

void* Engine::ensureBundleLocked(const std::string& resolvedTag) {
    auto bit = mBundles.find(resolvedTag);
    if (bit != mBundles.end()) return bit->second;
    auto pit = mBundlePaths.find(resolvedTag);
    if (pit == mBundlePaths.end()) return nullptr;
    const auto& path = pit->second;
    void* bundle;
    if (path.size() >= 4 && path.compare(path.size() - 4, 4, ".drb") == 0) {
        bundle = RuntimeBridge::instance().bundleFromBundle(path);
    } else {
        bundle = RuntimeBridge::instance().bundleFromPath(path);
    }
    mBundles.emplace(resolvedTag, bundle);
    return bundle;
}

std::string Engine::run(const std::string& tag, std::string_view text) {
    if (!ready()) return {};
    auto resolved = resolveTag(tag);

    void* handle = nullptr;
    std::mutex* tagLock = nullptr;
    {
        std::lock_guard<std::mutex> lk(mLock);
        auto pit = mBundlePaths.find(resolved);
        if (pit == mBundlePaths.end()) return {};

        auto hit = mPipelines.find(resolved);
        if (hit != mPipelines.end()) {
            handle = hit->second;
            tagLock = mPipelineLocks[resolved].get();
        } else {
            void* bundle = ensureBundleLocked(resolved);
            if (!bundle) return {};
            auto config = buildConfigJsonLocked(resolved);
            handle = RuntimeBridge::instance().bundleCreate(bundle, config);
            mPipelines.emplace(resolved, handle);
            mPipelineLocks.emplace(resolved, std::make_unique<std::mutex>());
            tagLock = mPipelineLocks[resolved].get();
        }
    }

    if (traceEnabled()) {
        trace("forward[" + resolved + "] in: " + truncatedForLog(text));
    }
    std::string out;
    {
        std::lock_guard<std::mutex> tl(*tagLock);
        out = RuntimeBridge::instance().pipelineForward(handle, text);
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
    {
        std::lock_guard<std::mutex> lk(mLock);
        bundle = ensureBundleLocked(resolved);
    }
    if (!bundle) return {};

    nlohmann::json locales = nlohmann::json::array();
    if (!uiLocale.empty()) locales.push_back(uiLocale);
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

std::string Engine::prefsPath() const {
    return divvun::prefsPath();
}

void Engine::loadPrefs() {
    std::ifstream f(prefsPath());
    if (!f) return;
    try {
        nlohmann::json j;
        f >> j;
        if (!j.is_object() || !j.contains("ignored") || !j["ignored"].is_object()) return;
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
