#include "DivvunSpellChecker.hxx"
#include "Engine.hxx"

#include <com/sun/star/linguistic2/SpellFailure.hpp>
#include <rtl/ustring.hxx>
#include <syslog.h>

using namespace ::com::sun::star;

namespace divvun {

namespace {

::rtl::OUString toOUString(const std::string& s) {
    return ::rtl::OUString::fromUtf8(::rtl::OString(s.data(), static_cast<sal_Int32>(s.size())));
}

std::string fromOUString(const ::rtl::OUString& s) {
    ::rtl::OString os = ::rtl::OUStringToOString(s, RTL_TEXTENCODING_UTF8);
    return std::string(os.getStr(), os.getLength());
}

std::string bcp47Tag(const lang::Locale& loc) {
    if (loc.Language == "qlt") return fromOUString(loc.Variant);
    if (loc.Language.isEmpty()) return {};
    auto lang = fromOUString(loc.Language);
    if (loc.Country.isEmpty()) return lang;
    return lang + "-" + fromOUString(loc.Country);
}

} // namespace

// ===== DivvunSpellAlternatives =====

DivvunSpellAlternatives::DivvunSpellAlternatives(
    ::rtl::OUString word,
    uno::Sequence<::rtl::OUString> alternatives,
    lang::Locale locale)
    : mWord(std::move(word))
    , mAlternatives(std::move(alternatives))
    , mLocale(std::move(locale))
{}

::rtl::OUString SAL_CALL DivvunSpellAlternatives::getWord() { return mWord; }
lang::Locale SAL_CALL DivvunSpellAlternatives::getLocale() { return mLocale; }
::sal_Int16 SAL_CALL DivvunSpellAlternatives::getFailureType() {
    return linguistic2::SpellFailure::SPELLING_ERROR;
}
::sal_Int16 SAL_CALL DivvunSpellAlternatives::getAlternativesCount() {
    return static_cast<sal_Int16>(mAlternatives.getLength());
}
uno::Sequence<::rtl::OUString> SAL_CALL DivvunSpellAlternatives::getAlternatives() {
    return mAlternatives;
}

// ===== DivvunSpellChecker =====

DivvunSpellChecker::DivvunSpellChecker() {
    syslog(LOG_NOTICE, "DivvunSpellChecker init");
}

DivvunSpellChecker::~DivvunSpellChecker() = default;

::rtl::OUString SAL_CALL DivvunSpellChecker::getImplementationName() {
    return ::rtl::OUString::createFromAscii(IMPL_NAME);
}

::sal_Bool SAL_CALL DivvunSpellChecker::supportsService(const ::rtl::OUString& serviceName) {
    auto names = getSupportedServiceNames();
    for (const auto& n : names) if (n == serviceName) return true;
    return false;
}

uno::Sequence<::rtl::OUString> SAL_CALL DivvunSpellChecker::getSupportedServiceNames() {
    uno::Sequence<::rtl::OUString> seq(1);
    seq.getArray()[0] = ::rtl::OUString::createFromAscii(SERVICE_NAME);
    return seq;
}

uno::Sequence<lang::Locale> SAL_CALL DivvunSpellChecker::getLocales() {
    auto locs = Engine::instance().locales();
    uno::Sequence<lang::Locale> out(static_cast<sal_Int32>(locs.size()));
    auto* arr = out.getArray();
    for (size_t i = 0; i < locs.size(); ++i) {
        arr[i].Language = toOUString(locs[i].language);
        arr[i].Country  = toOUString(locs[i].country);
    }
    return out;
}

::sal_Bool SAL_CALL DivvunSpellChecker::hasLocale(const lang::Locale& locale) {
    return Engine::instance().hasTag(bcp47Tag(locale));
}

::sal_Bool SAL_CALL DivvunSpellChecker::isValid(
    const ::rtl::OUString& word,
    const lang::Locale& locale,
    const uno::Sequence<beans::PropertyValue>& /*properties*/)
{
    auto tag = bcp47Tag(locale);
    if (!Engine::instance().hasTag(tag)) return true;
    auto result = Engine::instance().spellCheck(tag, fromOUString(word));
    return result.valid;
}

uno::Reference<linguistic2::XSpellAlternatives> SAL_CALL DivvunSpellChecker::spell(
    const ::rtl::OUString& word,
    const lang::Locale& locale,
    const uno::Sequence<beans::PropertyValue>& /*properties*/)
{
    auto tag = bcp47Tag(locale);
    if (!Engine::instance().hasTag(tag)) return nullptr;
    auto result = Engine::instance().spellCheck(tag, fromOUString(word));
    if (result.valid) return nullptr;

    uno::Sequence<::rtl::OUString> sugs(static_cast<sal_Int32>(result.suggestions.size()));
    auto* arr = sugs.getArray();
    for (size_t i = 0; i < result.suggestions.size(); ++i) {
        arr[i] = toOUString(result.suggestions[i]);
    }
    return new DivvunSpellAlternatives(word, sugs, locale);
}

::sal_Bool SAL_CALL DivvunSpellChecker::addLinguServiceEventListener(
    const uno::Reference<linguistic2::XLinguServiceEventListener>&)
{
    return false;
}

::sal_Bool SAL_CALL DivvunSpellChecker::removeLinguServiceEventListener(
    const uno::Reference<linguistic2::XLinguServiceEventListener>&)
{
    return false;
}

void SAL_CALL DivvunSpellChecker::initialize(const uno::Sequence<uno::Any>& /*args*/) {}

::rtl::OUString SAL_CALL DivvunSpellChecker::getServiceDisplayName(const lang::Locale& /*loc*/) {
    return ::rtl::OUString::createFromAscii("DivvunSpell");
}

uno::Reference<uno::XInterface> SAL_CALL DivvunSpellChecker::create(
    const uno::Reference<uno::XComponentContext>& /*ctx*/)
{
    return static_cast<cppu::OWeakObject*>(new DivvunSpellChecker());
}

} // namespace divvun
