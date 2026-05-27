#pragma once

#include <divvun_runtime.h>

#include <string>
#include <string_view>

namespace divvun {

// Thin façade over the canonical DRT_* ABI: marshals std::string_view <->
// rust_slice_t, owns the thread-local error callback, converts Rust errors
// into exceptions, and frees Rust-allocated return slices.
class RuntimeBridge {
public:
    static RuntimeBridge& instance();

    void* bundleFromBundle(std::string_view path);
    void* bundleFromPath(std::string_view path);
    void* bundleCreate(void* bundle, std::string_view configJson);
    std::string pipelineForward(void* handle, std::string_view input);
    std::string bundleErrorPreferences(void* bundle, std::string_view localesJson);

    void bundleDrop(void* bundle);
    void pipelineDrop(void* handle);

private:
    RuntimeBridge() = default;
    RuntimeBridge(const RuntimeBridge&) = delete;
    RuntimeBridge& operator=(const RuntimeBridge&) = delete;
};

class RuntimeError : public std::exception {
public:
    explicit RuntimeError(std::string msg) : mMsg(std::move(msg)) {}
    const char* what() const noexcept override { return mMsg.c_str(); }
private:
    std::string mMsg;
};

} // namespace divvun
