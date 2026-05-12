#include "DivvunProofreader.hxx"
#include "DivvunSpellChecker.hxx"
#include "SettingsDialog.hxx"

#include <com/sun/star/lang/XSingleComponentFactory.hpp>
#include <cppuhelper/factory.hxx>
#include <rtl/ustring.hxx>
#include <sal/types.h>

using namespace ::com::sun::star;

namespace {

void* makeFactory(const char* implName, const char* serviceName,
                  ::cppu::ComponentFactoryFunc create)
{
    uno::Sequence<::rtl::OUString> services(1);
    services.getArray()[0] = ::rtl::OUString::createFromAscii(serviceName);

    uno::Reference<lang::XSingleComponentFactory> factory =
        ::cppu::createSingleComponentFactory(
            create,
            ::rtl::OUString::createFromAscii(implName),
            services);

    factory->acquire();
    return factory.get();
}

} // namespace

extern "C" SAL_DLLPUBLIC_EXPORT void* component_getFactory(
    const char* implName, void* /*serviceManager*/, void* /*registryKey*/)
{
    if (!implName) return nullptr;
    if (rtl_str_compare(implName, divvun::DivvunProofreader::IMPL_NAME) == 0) {
        return makeFactory(divvun::DivvunProofreader::IMPL_NAME,
                           divvun::DivvunProofreader::SERVICE_NAME,
                           &divvun::DivvunProofreader::create);
    }
    if (rtl_str_compare(implName, divvun::DivvunSpellChecker::IMPL_NAME) == 0) {
        return makeFactory(divvun::DivvunSpellChecker::IMPL_NAME,
                           divvun::DivvunSpellChecker::SERVICE_NAME,
                           &divvun::DivvunSpellChecker::create);
    }
    if (rtl_str_compare(implName, divvun::SettingsDialog::IMPL_NAME) == 0) {
        return makeFactory(divvun::SettingsDialog::IMPL_NAME,
                           divvun::SettingsDialog::SERVICE_NAME,
                           &divvun::SettingsDialog::create);
    }
    return nullptr;
}
