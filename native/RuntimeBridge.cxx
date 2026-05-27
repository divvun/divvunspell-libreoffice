#include "RuntimeBridge.hxx"

#include <cstring>
#include <stdexcept>

namespace divvun {

namespace {

thread_local std::string tlsErrorMessage;

void errorCallbackTrampoline(void* ptr, rust_usize_t len) {
    if (ptr && len > 0) {
        tlsErrorMessage.assign(static_cast<const char*>(ptr), len);
    } else {
        tlsErrorMessage = "Unknown divvun-runtime error";
    }
}

rust_slice_t toSlice(std::string_view sv) {
    return rust_slice_t{ const_cast<void*>(static_cast<const void*>(sv.data())), sv.size() };
}

void clearError() { tlsErrorMessage.clear(); }
void throwIfError() {
    if (!tlsErrorMessage.empty()) {
        std::string msg = std::move(tlsErrorMessage);
        tlsErrorMessage.clear();
        throw RuntimeError(std::move(msg));
    }
}

} // namespace

RuntimeBridge& RuntimeBridge::instance() {
    static RuntimeBridge inst;
    return inst;
}

void* RuntimeBridge::bundleFromBundle(std::string_view path) {
    clearError();
    void* b = DRT_Bundle_fromBundle(toSlice(path), &errorCallbackTrampoline);
    throwIfError();
    if (!b) throw RuntimeError("Bundle.from_bundle returned null");
    return b;
}

void* RuntimeBridge::bundleFromPath(std::string_view path) {
    clearError();
    void* b = DRT_Bundle_fromPath(toSlice(path), &errorCallbackTrampoline);
    throwIfError();
    if (!b) throw RuntimeError("Bundle.from_path returned null");
    return b;
}

void* RuntimeBridge::bundleCreate(void* bundle, std::string_view configJson) {
    clearError();
    void* h = DRT_Bundle_create(bundle, toSlice(configJson), &errorCallbackTrampoline);
    throwIfError();
    if (!h) throw RuntimeError("Bundle.create returned null");
    return h;
}

std::string RuntimeBridge::pipelineForward(void* handle, std::string_view input) {
    clearError();
    rust_slice_t out = DRT_PipelineHandle_forward(handle, toSlice(input), &errorCallbackTrampoline);
    throwIfError();
    std::string result;
    if (out.data && out.len > 0) {
        result.assign(static_cast<const char*>(out.data), out.len);
    }
    if (out.data) DRT_Vec_drop(out);
    return result;
}

std::string RuntimeBridge::bundleErrorPreferences(void* bundle, std::string_view localesJson) {
    clearError();
    rust_slice_t out = DRT_Bundle_errorPreferences(bundle, toSlice(localesJson), &errorCallbackTrampoline);
    throwIfError();
    std::string result;
    if (out.data && out.len > 0) {
        result.assign(static_cast<const char*>(out.data), out.len);
    }
    if (out.data) DRT_Vec_drop(out);
    return result;
}

void RuntimeBridge::bundleDrop(void* bundle) {
    if (bundle) DRT_Bundle_drop(bundle);
}

void RuntimeBridge::pipelineDrop(void* handle) {
    if (handle) DRT_PipelineHandle_drop(handle);
}

} // namespace divvun
