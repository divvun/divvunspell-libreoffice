#include "DivvunProofreader.hxx"
#include "Engine.hxx"
#include "ErrorClass.hxx"
#include "Platform.hxx"

#include <com/sun/star/linguistic2/ProofreadingResult.hpp>
#include <com/sun/star/linguistic2/SingleProofreadingError.hpp>
#include <com/sun/star/text/TextMarkupType.hpp>
#include <rtl/ustring.hxx>

#include <nlohmann/json.hpp>
#include <sstream>

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

DivvunProofreader::DivvunProofreader() {
    logLine("DivvunProofreader init");
}

DivvunProofreader::~DivvunProofreader() = default;

::rtl::OUString SAL_CALL DivvunProofreader::getImplementationName() {
    return ::rtl::OUString::createFromAscii(IMPL_NAME);
}

::sal_Bool SAL_CALL DivvunProofreader::supportsService(const ::rtl::OUString& serviceName) {
    auto names = getSupportedServiceNames();
    for (const auto& n : names) if (n == serviceName) return true;
    return false;
}

uno::Sequence<::rtl::OUString> SAL_CALL DivvunProofreader::getSupportedServiceNames() {
    uno::Sequence<::rtl::OUString> seq(1);
    seq.getArray()[0] = ::rtl::OUString::createFromAscii(SERVICE_NAME);
    return seq;
}

uno::Sequence<lang::Locale> SAL_CALL DivvunProofreader::getLocales() {
    auto locs = Engine::instance().locales();
    uno::Sequence<lang::Locale> out(static_cast<sal_Int32>(locs.size()));
    auto* arr = out.getArray();
    for (size_t i = 0; i < locs.size(); ++i) {
        arr[i].Language = toOUString(locs[i].language);
        arr[i].Country  = toOUString(locs[i].country);
    }
    return out;
}

::sal_Bool SAL_CALL DivvunProofreader::hasLocale(const lang::Locale& locale) {
    return Engine::instance().hasTag(bcp47Tag(locale));
}

::sal_Bool SAL_CALL DivvunProofreader::isSpellChecker() {
    return false;
}

linguistic2::ProofreadingResult SAL_CALL DivvunProofreader::doProofreading(
    const ::rtl::OUString& aDocumentIdentifier,
    const ::rtl::OUString& aText,
    const lang::Locale& aLocale,
    ::sal_Int32 nStartOfSentencePosition,
    ::sal_Int32 nSuggestedBehindEndOfSentencePosition,
    const uno::Sequence<beans::PropertyValue>& /*aProperties*/)
{
    linguistic2::ProofreadingResult result;
    result.aDocumentIdentifier = aDocumentIdentifier;
    result.aText = aText;
    result.aLocale = aLocale;
    result.nStartOfSentencePosition = nStartOfSentencePosition;
    result.nBehindEndOfSentencePosition = nSuggestedBehindEndOfSentencePosition;
    result.nStartOfNextSentencePosition = nSuggestedBehindEndOfSentencePosition;
    result.aErrors = uno::Sequence<linguistic2::SingleProofreadingError>(0);
    result.aProperties = uno::Sequence<beans::PropertyValue>(0);
    result.xProofreader = uno::Reference<linguistic2::XProofreader>(this);

    auto tag = bcp47Tag(aLocale);
    if (!Engine::instance().hasTag(tag)) return result;

    if (nSuggestedBehindEndOfSentencePosition <= nStartOfSentencePosition) return result;
    if (nStartOfSentencePosition < 0 || nSuggestedBehindEndOfSentencePosition > aText.getLength()) return result;

    ::rtl::OUString chunkOU = aText.copy(
        nStartOfSentencePosition,
        nSuggestedBehindEndOfSentencePosition - nStartOfSentencePosition);
    if (chunkOU.isEmpty()) return result;

    auto chunkUtf8 = fromOUString(chunkOU);
    if (Engine::traceEnabled()) {
        Engine::trace("doProofreading[" + tag + "] sentence ["
                      + std::to_string(nStartOfSentencePosition) + ","
                      + std::to_string(nSuggestedBehindEndOfSentencePosition) + "): "
                      + chunkUtf8);
    }
    std::string responseJson;
    try {
        responseJson = Engine::instance().run(tag, chunkUtf8);
    } catch (const RuntimeError& e) {
        logLine(std::string("doProofreading runtime error: ") + e.what());
        return result;
    }
    if (responseJson.empty()) return result;

    nlohmann::json parsed;
    try {
        parsed = nlohmann::json::parse(responseJson);
    } catch (const std::exception& e) {
        logLine(std::string("doProofreading json parse error: ") + e.what());
        return result;
    }

    if (!parsed.is_object() || !parsed.contains("errors") || !parsed["errors"].is_array()) {
        return result;
    }

    auto& errs = parsed["errors"];
    uno::Sequence<linguistic2::SingleProofreadingError> outSeq(static_cast<sal_Int32>(errs.size()));
    auto* arr = outSeq.getArray();
    sal_Int32 idx = 0;
    for (auto& err : errs) {
        if (!err.is_object()) continue;
        auto errorId = err.value("error_id", std::string{});
        if (isSpellError(errorId)) continue;
        auto title   = err.value("title", std::string{});
        auto descr   = err.value("description", std::string{});

        auto& spe = arr[idx++];
        spe.nErrorStart = nStartOfSentencePosition + err.value("start", 0);
        spe.nErrorLength = err.value("end", 0) - err.value("start", 0);
        spe.nErrorType = text::TextMarkupType::PROOFREADING;
        spe.aShortComment = !title.empty() ? toOUString(title) : toOUString(errorId);
        spe.aFullComment = toOUString(descr);
        spe.aRuleIdentifier = toOUString(errorId);
        if (err.contains("suggestions") && err["suggestions"].is_array()) {
            auto& sugs = err["suggestions"];
            uno::Sequence<::rtl::OUString> sugSeq(static_cast<sal_Int32>(sugs.size()));
            auto* sugArr = sugSeq.getArray();
            for (size_t i = 0; i < sugs.size(); ++i) {
                if (sugs[i].is_string()) sugArr[i] = toOUString(sugs[i].get<std::string>());
            }
            spe.aSuggestions = sugSeq;
        }
    }
    outSeq.realloc(idx);
    result.aErrors = outSeq;
    if (Engine::traceEnabled()) {
        std::ostringstream s;
        s << "doProofreading[" << tag << "] emitted " << idx << " grammar errors";
        for (sal_Int32 i = 0; i < idx; ++i) {
            const auto& e = result.aErrors[i];
            s << "\n    [" << e.nErrorStart << "+" << e.nErrorLength
              << "] rule=" << fromOUString(e.aRuleIdentifier)
              << " short=\"" << fromOUString(e.aShortComment) << "\""
              << " sugs=" << e.aSuggestions.getLength();
            for (sal_Int32 j = 0; j < e.aSuggestions.getLength(); ++j) {
                s << " \"" << fromOUString(e.aSuggestions[j]) << "\"";
            }
        }
        Engine::trace(s.str());
    }
    return result;
}

void SAL_CALL DivvunProofreader::ignoreRule(
    const ::rtl::OUString& aRuleIdentifier,
    const lang::Locale& aLocale)
{
    Engine::instance().addIgnoredRule(bcp47Tag(aLocale), fromOUString(aRuleIdentifier));
}

void SAL_CALL DivvunProofreader::resetIgnoreRules() {
    Engine::instance().resetIgnoredRules();
}

void SAL_CALL DivvunProofreader::initialize(const uno::Sequence<uno::Any>& /*args*/) {}

::rtl::OUString SAL_CALL DivvunProofreader::getServiceDisplayName(const lang::Locale& /*loc*/) {
    return ::rtl::OUString::createFromAscii("DivvunSpell");
}

uno::Reference<uno::XInterface> SAL_CALL DivvunProofreader::create(
    const uno::Reference<uno::XComponentContext>& /*ctx*/)
{
    return static_cast<cppu::OWeakObject*>(new DivvunProofreader());
}

} // namespace divvun
