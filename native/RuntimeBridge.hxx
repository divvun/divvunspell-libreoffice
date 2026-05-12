#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace divvun {

struct RustSlice {
    void* ptr;
    std::uintptr_t len;
};

using ErrorCallback = void (*)(void* ptr, std::uintptr_t len);

// Singleton bridge to libdivvun_runtime.dylib. dlopen lazily on first use,
// looks up the DRT_* symbols, hides ownership and the error-callback dance.
class RuntimeBridge {
public:
    static RuntimeBridge& instance();

    bool ready() const { return mReady; }
    const std::string& loadError() const { return mLoadError; }

    void* bundleFromBundle(std::string_view path);
    void* bundleFromPath(std::string_view path);
    void* bundleCreate(void* bundle, std::string_view configJson);
    std::string pipelineForward(void* handle, std::string_view input);
    std::string bundleErrorPreferences(void* bundle, std::string_view localesJson);

    void bundleDrop(void* bundle);
    void pipelineDrop(void* handle);

private:
    RuntimeBridge();
    RuntimeBridge(const RuntimeBridge&) = delete;
    RuntimeBridge& operator=(const RuntimeBridge&) = delete;

    void load();

    void* mLib = nullptr;
    bool mReady = false;
    std::string mLoadError;

    using FnBundleFromBundle = void* (*)(RustSlice, ErrorCallback);
    using FnBundleFromPath   = void* (*)(RustSlice, ErrorCallback);
    using FnBundleCreate     = void* (*)(void*, RustSlice, ErrorCallback);
    using FnBundleDrop       = void  (*)(void*);
    using FnPipelineDrop     = void  (*)(void*);
    using FnPipelineForward  = RustSlice (*)(void*, RustSlice, ErrorCallback);
    using FnBundleErrPrefs   = RustSlice (*)(void*, RustSlice, ErrorCallback);
    using FnVecDrop          = void  (*)(RustSlice);

    FnBundleFromBundle  mBundleFromBundle  = nullptr;
    FnBundleFromPath    mBundleFromPath    = nullptr;
    FnBundleCreate      mBundleCreate      = nullptr;
    FnBundleDrop        mBundleDrop        = nullptr;
    FnPipelineDrop      mPipelineDrop      = nullptr;
    FnPipelineForward   mPipelineForward   = nullptr;
    FnBundleErrPrefs    mBundleErrorPrefs  = nullptr;
    FnVecDrop           mVecDrop           = nullptr;
};

class RuntimeError : public std::exception {
public:
    explicit RuntimeError(std::string msg) : mMsg(std::move(msg)) {}
    const char* what() const noexcept override { return mMsg.c_str(); }
private:
    std::string mMsg;
};

} // namespace divvun
