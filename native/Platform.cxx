#include "Platform.hxx"

#include <cstdlib>
#include <filesystem>
#include <fstream>

#if defined(_WIN32)
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>
#else
  #include <dlfcn.h>
  #include <syslog.h>
#endif

namespace divvun {

namespace {

namespace fs = std::filesystem;

std::string envOrEmpty(const char* name) {
    if (const char* v = std::getenv(name)) return std::string(v);
    return {};
}

#if defined(_WIN32)

std::string wideToUtf8(const wchar_t* data, size_t len) {
    if (!data || len == 0) return {};
    int n = ::WideCharToMultiByte(CP_UTF8, 0, data, static_cast<int>(len),
                                  nullptr, 0, nullptr, nullptr);
    if (n <= 0) return {};
    std::string out(static_cast<size_t>(n), '\0');
    ::WideCharToMultiByte(CP_UTF8, 0, data, static_cast<int>(len),
                          out.data(), n, nullptr, nullptr);
    return out;
}

std::string tempLogPath() {
    wchar_t buf[MAX_PATH + 1];
    DWORD n = ::GetTempPathW(MAX_PATH + 1, buf);
    if (n == 0) return "divvunspell-libreoffice.log";
    fs::path p(std::wstring(buf, n));
    p /= L"divvunspell-libreoffice.log";
    auto w = p.wstring();
    return wideToUtf8(w.c_str(), w.size());
}

std::string moduleDirImpl() {
    HMODULE h = nullptr;
    if (!::GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(&moduleDirImpl), &h)) {
        return {};
    }
    wchar_t buf[MAX_PATH + 1];
    DWORD n = ::GetModuleFileNameW(h, buf, MAX_PATH + 1);
    if (n == 0) return {};
    fs::path p(std::wstring(buf, n));
    auto parent = p.parent_path().wstring();
    return wideToUtf8(parent.c_str(), parent.size());
}

#else // POSIX

std::string moduleDirImpl() {
    Dl_info info{};
    if (::dladdr(reinterpret_cast<void*>(&moduleDirImpl), &info) != 0 && info.dli_fname) {
        fs::path p(info.dli_fname);
        return p.parent_path().string();
    }
    return {};
}

#endif

} // namespace

void logLine(const std::string& msg) {
#if !defined(_WIN32)
    ::syslog(LOG_NOTICE, "%s", msg.c_str());
    const std::string path = "/tmp/divvunspell-libreoffice.log";
#else
    const std::string path = tempLogPath();
#endif
    std::ofstream f(path, std::ios::app);
    if (f) f << msg << '\n';
}

std::vector<std::string> bundleSearchPaths() {
    std::vector<std::string> out;
#if defined(_WIN32)
    if (auto pd = envOrEmpty("ProgramData"); !pd.empty()) {
        out.emplace_back(pd + "\\Divvun\\Grammar");
    }
    if (auto local = envOrEmpty("LOCALAPPDATA"); !local.empty()) {
        out.emplace_back(local + "\\Divvun\\Grammar");
    }
    if (auto roaming = envOrEmpty("APPDATA"); !roaming.empty()) {
        out.emplace_back(roaming + "\\Divvun\\Grammar");
    }
#elif defined(__APPLE__)
    out.emplace_back("/Library/Application Support/Divvun/Grammar");
    if (auto home = envOrEmpty("HOME"); !home.empty()) {
        out.emplace_back(home + "/Library/Application Support/Divvun/Grammar");
    }
#else // Linux / other XDG-style POSIX
    out.emplace_back("/usr/share/divvun/grammar");
    out.emplace_back("/usr/local/share/divvun/grammar");
    if (auto xdg = envOrEmpty("XDG_DATA_HOME"); !xdg.empty()) {
        out.emplace_back(xdg + "/divvun/grammar");
    } else if (auto home = envOrEmpty("HOME"); !home.empty()) {
        out.emplace_back(home + "/.local/share/divvun/grammar");
    }
#endif
    return out;
}

std::string prefsPath() {
#if defined(_WIN32)
    if (auto roaming = envOrEmpty("APPDATA"); !roaming.empty()) {
        return roaming + "\\Divvun\\divvunspell-prefs.json";
    }
    return "divvunspell-prefs.json";
#elif defined(__APPLE__)
    auto home = envOrEmpty("HOME");
    std::string base = home.empty() ? "/tmp" : home;
    return base + "/Library/Application Support/Divvun/divvunspell-prefs.json";
#else // Linux / other XDG-style POSIX
    if (auto xdg = envOrEmpty("XDG_CONFIG_HOME"); !xdg.empty()) {
        return xdg + "/divvun/divvunspell-prefs.json";
    }
    if (auto home = envOrEmpty("HOME"); !home.empty()) {
        return home + "/.config/divvun/divvunspell-prefs.json";
    }
    return "/tmp/divvunspell-prefs.json";
#endif
}

std::string componentDir() {
    return moduleDirImpl();
}

} // namespace divvun
