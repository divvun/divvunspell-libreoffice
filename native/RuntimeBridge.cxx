#include "RuntimeBridge.hxx"

#include <dlfcn.h>
#include <cstring>
#include <filesystem>
#include <stdexcept>

namespace divvun {

namespace {

thread_local std::string tlsErrorMessage;

void errorCallbackTrampoline(void* ptr, std::uintptr_t len) {
    if (ptr && len > 0) {
        tlsErrorMessage.assign(static_cast<const char*>(ptr), len);
    } else {
        tlsErrorMessage = "Unknown divvun-runtime error";
    }
}

RustSlice toSlice(std::string_view sv) {
    return RustSlice{ const_cast<void*>(static_cast<const void*>(sv.data())), sv.size() };
}

void clearError() { tlsErrorMessage.clear(); }
void throwIfError() {
    if (!tlsErrorMessage.empty()) {
        std::string msg = std::move(tlsErrorMessage);
        tlsErrorMessage.clear();
        throw RuntimeError(std::move(msg));
    }
}

std::string siblingDylibPath() {
    Dl_info info{};
    if (dladdr(reinterpret_cast<void*>(&errorCallbackTrampoline), &info) != 0 && info.dli_fname) {
        std::filesystem::path self(info.dli_fname);
        auto sibling = self.parent_path() / "libdivvun_runtime.dylib";
        return sibling.string();
    }
    return "libdivvun_runtime.dylib";
}

} // namespace

RuntimeBridge& RuntimeBridge::instance() {
    static RuntimeBridge inst;
    return inst;
}

RuntimeBridge::RuntimeBridge() {
    load();
}

void RuntimeBridge::load() {
    auto path = siblingDylibPath();
    mLib = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!mLib) {
        const char* err = dlerror();
        mLoadError = err ? err : "dlopen failed";
        return;
    }

    auto sym = [&](const char* name) -> void* {
        void* p = dlsym(mLib, name);
        if (!p) {
            const char* err = dlerror();
            mLoadError = std::string("dlsym ") + name + ": " + (err ? err : "unknown");
        }
        return p;
    };

    mBundleFromBundle  = reinterpret_cast<FnBundleFromBundle>(sym("DRT_Bundle_fromBundle"));
    mBundleFromPath    = reinterpret_cast<FnBundleFromPath>  (sym("DRT_Bundle_fromPath"));
    mBundleCreate      = reinterpret_cast<FnBundleCreate>    (sym("DRT_Bundle_create"));
    mBundleDrop        = reinterpret_cast<FnBundleDrop>      (sym("DRT_Bundle_drop"));
    mPipelineDrop      = reinterpret_cast<FnPipelineDrop>    (sym("DRT_PipelineHandle_drop"));
    mPipelineForward   = reinterpret_cast<FnPipelineForward> (sym("DRT_PipelineHandle_forward"));
    mBundleErrorPrefs  = reinterpret_cast<FnBundleErrPrefs>  (sym("DRT_Bundle_errorPreferences"));
    mVecDrop           = reinterpret_cast<FnVecDrop>         (sym("DRT_Vec_drop"));

    mReady = mBundleFromBundle && mBundleFromPath && mBundleCreate
          && mBundleDrop && mPipelineDrop && mPipelineForward
          && mBundleErrorPrefs && mVecDrop;
}

void* RuntimeBridge::bundleFromBundle(std::string_view path) {
    if (!mReady) throw RuntimeError("runtime not loaded: " + mLoadError);
    clearError();
    void* b = mBundleFromBundle(toSlice(path), &errorCallbackTrampoline);
    throwIfError();
    if (!b) throw RuntimeError("Bundle.from_bundle returned null");
    return b;
}

void* RuntimeBridge::bundleFromPath(std::string_view path) {
    if (!mReady) throw RuntimeError("runtime not loaded: " + mLoadError);
    clearError();
    void* b = mBundleFromPath(toSlice(path), &errorCallbackTrampoline);
    throwIfError();
    if (!b) throw RuntimeError("Bundle.from_path returned null");
    return b;
}

void* RuntimeBridge::bundleCreate(void* bundle, std::string_view configJson) {
    if (!mReady) throw RuntimeError("runtime not loaded: " + mLoadError);
    clearError();
    void* h = mBundleCreate(bundle, toSlice(configJson), &errorCallbackTrampoline);
    throwIfError();
    if (!h) throw RuntimeError("Bundle.create returned null");
    return h;
}

std::string RuntimeBridge::pipelineForward(void* handle, std::string_view input) {
    if (!mReady) throw RuntimeError("runtime not loaded: " + mLoadError);
    clearError();
    RustSlice out = mPipelineForward(handle, toSlice(input), &errorCallbackTrampoline);
    throwIfError();
    std::string result;
    if (out.ptr && out.len > 0) {
        result.assign(static_cast<const char*>(out.ptr), out.len);
    }
    if (out.ptr) mVecDrop(out);
    return result;
}

std::string RuntimeBridge::bundleErrorPreferences(void* bundle, std::string_view localesJson) {
    if (!mReady) throw RuntimeError("runtime not loaded: " + mLoadError);
    clearError();
    RustSlice out = mBundleErrorPrefs(bundle, toSlice(localesJson), &errorCallbackTrampoline);
    throwIfError();
    std::string result;
    if (out.ptr && out.len > 0) {
        result.assign(static_cast<const char*>(out.ptr), out.len);
    }
    if (out.ptr) mVecDrop(out);
    return result;
}

void RuntimeBridge::bundleDrop(void* bundle) {
    if (mReady && bundle) mBundleDrop(bundle);
}

void RuntimeBridge::pipelineDrop(void* handle) {
    if (mReady && handle) mPipelineDrop(handle);
}

} // namespace divvun
