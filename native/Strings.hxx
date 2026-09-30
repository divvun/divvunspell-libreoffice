#pragma once

#include <string>

namespace divvun {

// Text the extension shows in LibreOffice's UI. Translations live in the
// table in Strings.cxx.
enum class StringId {
    ProofingLanguage,
    FeedbackLanguage,
    SameAsText,
    SameAsUi,
    NoBundles,
};

// The string in the given UI language (a BCP-47 tag such as "nb-NO"), matched
// on the full tag, then its language subtag, then English.
std::string uiString(StringId id, const std::string& uiLocale);

// "Name (code)" for a language code, the name in the UI language when there is
// one and in English otherwise; the bare code when neither has a name for it.
std::string languageName(const std::string& code, const std::string& uiLocale);

} // namespace divvun
