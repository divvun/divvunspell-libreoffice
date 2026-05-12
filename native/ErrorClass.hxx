#pragma once

#include <string_view>

namespace divvun {

inline bool isSpellError(std::string_view errorId) {
    if (errorId.empty()) return false;
    if (errorId == "typo" || errorId == "spelling-error") return true;
    if (errorId.size() >= 5 && errorId.substr(0, 5) == "real-") return true;
    if (errorId.size() >= 5 && errorId.substr(0, 5) == "orth-") return true;
    return false;
}

} // namespace divvun
