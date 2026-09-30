#include "Strings.hxx"

#include <map>
#include <vector>

namespace divvun {

namespace {

struct Translation {
    const char* locale;
    std::map<StringId, const char*> strings;
    std::map<std::string, const char*> languageNames;
};

// One block per UI language, keyed by BCP-47 tag ("nb", or "nb-NO" where a
// region needs its own wording). To add a translation, copy the "en" block and
// translate its values; anything left out falls back to English.
const std::vector<Translation>& translations() {
    static const std::vector<Translation> table = {
        {"en",
         {
             {StringId::ProofingLanguage, "Proofing tool language:"},
             {StringId::FeedbackLanguage, "Feedback language:"},
             {StringId::SameAsText, "Same as the text"},
             {StringId::SameAsUi, "Same as the user interface language"},
             {StringId::NoBundles, "No DivvunSpell bundles installed in:"},
         },
         {
             {"da", "Danish"},
             {"de", "German"},
             {"en", "English"},
             {"et", "Estonian"},
             {"fi", "Finnish"},
             {"fo", "Faroese"},
             {"is", "Icelandic"},
             {"kl", "Greenlandic"},
             {"kpv", "Komi-Zyrian"},
             {"myv", "Erzya"},
             {"nb", "Norwegian Bokmål"},
             {"nn", "Norwegian Nynorsk"},
             {"ru", "Russian"},
             {"se", "Northern Sami"},
             {"sjd", "Kildin Sami"},
             {"sje", "Pite Sami"},
             {"sju", "Ume Sami"},
             {"sma", "Southern Sami"},
             {"smj", "Lule Sami"},
             {"smn", "Inari Sami"},
             {"sms", "Skolt Sami"},
             {"sv", "Swedish"},
         }},
    };
    return table;
}

bool sameTag(const std::string& a, const char* b) {
    size_t i = 0;
    for (; i < a.size() && b[i]; ++i) {
        char x = a[i] == '_' ? '-' : a[i];
        char y = b[i];
        if (x >= 'A' && x <= 'Z') x = static_cast<char>(x - 'A' + 'a');
        if (y >= 'A' && y <= 'Z') y = static_cast<char>(y - 'A' + 'a');
        if (x != y) return false;
    }
    return i == a.size() && !b[i];
}

// Translations to try, most specific first, ending with English.
std::vector<const Translation*> candidates(const std::string& uiLocale) {
    const std::string language = uiLocale.substr(0, uiLocale.find_first_of("-_"));
    std::vector<const Translation*> found;
    for (const std::string& tag : {uiLocale, language, std::string("en")}) {
        if (tag.empty()) continue;
        for (const auto& t : translations()) {
            if (sameTag(tag, t.locale)) found.push_back(&t);
        }
    }
    return found;
}

} // namespace

std::string uiString(StringId id, const std::string& uiLocale) {
    for (const Translation* t : candidates(uiLocale)) {
        auto it = t->strings.find(id);
        if (it != t->strings.end()) return it->second;
    }
    return {};
}

std::string languageName(const std::string& code, const std::string& uiLocale) {
    for (const Translation* t : candidates(uiLocale)) {
        auto it = t->languageNames.find(code);
        if (it != t->languageNames.end()) return std::string(it->second) + " (" + code + ")";
    }
    return code;
}

} // namespace divvun
