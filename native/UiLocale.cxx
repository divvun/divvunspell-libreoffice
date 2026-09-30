#include "UiLocale.hxx"
#include "Engine.hxx"
#include "Platform.hxx"

#include <com/sun/star/beans/NamedValue.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XLocalizable.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <rtl/ustring.hxx>

using namespace ::com::sun::star;

namespace divvun {

namespace {

std::string fromOU(const ::rtl::OUString& s) {
    ::rtl::OString os = ::rtl::OUStringToOString(s, RTL_TEXTENCODING_UTF8);
    return std::string(os.getStr(), os.getLength());
}

std::string toTag(const lang::Locale& locale) {
    if (locale.Language == "qlt") return fromOU(locale.Variant);
    if (locale.Language.isEmpty() || locale.Language == "*") return {};
    if (locale.Country.isEmpty()) return fromOU(locale.Language);
    return fromOU(locale.Language) + "-" + fromOU(locale.Country);
}

} // namespace

// The Setup/L10N ooLocale setting when the user picked a UI language.
// Otherwise ("default - follows the system") LibreOffice resolves one at
// startup and localizes its default configuration provider to it, so ask the
// provider.
std::string uiLocale(const uno::Reference<uno::XComponentContext>& ctx) {
    if (!ctx.is()) return {};
    try {
        uno::Reference<lang::XMultiServiceFactory> provider(
            ctx->getServiceManager()->createInstanceWithContext(
                ::rtl::OUString::createFromAscii("com.sun.star.configuration.ConfigurationProvider"), ctx),
            uno::UNO_QUERY_THROW);
        uno::Sequence<uno::Any> args(1);
        args.getArray()[0] <<= beans::NamedValue(
            ::rtl::OUString::createFromAscii("nodepath"),
            uno::makeAny(::rtl::OUString::createFromAscii("/org.openoffice.Setup/L10N")));
        uno::Reference<container::XNameAccess> node(
            provider->createInstanceWithArguments(
                ::rtl::OUString::createFromAscii("com.sun.star.configuration.ConfigurationAccess"), args),
            uno::UNO_QUERY_THROW);
        ::rtl::OUString locale;
        node->getByName(::rtl::OUString::createFromAscii("ooLocale")) >>= locale;
        if (!locale.isEmpty()) return fromOU(locale);

        uno::Reference<lang::XLocalizable> localizable(provider, uno::UNO_QUERY);
        if (localizable.is()) return toTag(localizable->getLocale());
    } catch (const uno::Exception& e) {
        logLine("Could not read UI locale: " + fromOU(e.Message));
    }
    return {};
}

void publishUiLocale(const uno::Reference<uno::XComponentContext>& ctx) {
    try {
        Engine::instance().setUiLocale(uiLocale(ctx));
    } catch (const std::exception& e) {
        logLine(std::string("Could not publish UI locale: ") + e.what());
    } catch (...) {
        logLine("Could not publish UI locale: unknown exception");
    }
}

} // namespace divvun
