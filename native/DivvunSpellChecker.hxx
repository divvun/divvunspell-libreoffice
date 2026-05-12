#pragma once

#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceDisplayName.hpp>
#include <com/sun/star/linguistic2/XSpellChecker.hpp>
#include <com/sun/star/linguistic2/XLinguServiceEventBroadcaster.hpp>
#include <com/sun/star/linguistic2/XSpellAlternatives.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase5.hxx>
#include <cppuhelper/implbase1.hxx>

namespace divvun {

class DivvunSpellAlternatives
    : public ::cppu::WeakImplHelper1<::com::sun::star::linguistic2::XSpellAlternatives>
{
public:
    DivvunSpellAlternatives(::rtl::OUString word,
                            ::com::sun::star::uno::Sequence<::rtl::OUString> alternatives,
                            ::com::sun::star::lang::Locale locale);

    virtual ::rtl::OUString SAL_CALL getWord() override;
    virtual ::com::sun::star::lang::Locale SAL_CALL getLocale() override;
    virtual ::sal_Int16 SAL_CALL getFailureType() override;
    virtual ::sal_Int16 SAL_CALL getAlternativesCount() override;
    virtual ::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL getAlternatives() override;

private:
    ::rtl::OUString mWord;
    ::com::sun::star::uno::Sequence<::rtl::OUString> mAlternatives;
    ::com::sun::star::lang::Locale mLocale;
};

class DivvunSpellChecker
    : public ::cppu::WeakImplHelper5<
        ::com::sun::star::linguistic2::XSpellChecker,
        ::com::sun::star::linguistic2::XLinguServiceEventBroadcaster,
        ::com::sun::star::lang::XServiceInfo,
        ::com::sun::star::lang::XInitialization,
        ::com::sun::star::lang::XServiceDisplayName>
{
public:
    DivvunSpellChecker();
    virtual ~DivvunSpellChecker() override;

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() override;
    virtual ::sal_Bool      SAL_CALL supportsService(const ::rtl::OUString& serviceName) override;
    virtual ::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL getSupportedServiceNames() override;

    // XSupportedLocales
    virtual ::com::sun::star::uno::Sequence<::com::sun::star::lang::Locale> SAL_CALL getLocales() override;
    virtual ::sal_Bool SAL_CALL hasLocale(const ::com::sun::star::lang::Locale& locale) override;

    // XSpellChecker
    virtual ::sal_Bool SAL_CALL isValid(
        const ::rtl::OUString& word,
        const ::com::sun::star::lang::Locale& locale,
        const ::com::sun::star::uno::Sequence<::com::sun::star::beans::PropertyValue>& properties) override;
    virtual ::com::sun::star::uno::Reference<::com::sun::star::linguistic2::XSpellAlternatives> SAL_CALL spell(
        const ::rtl::OUString& word,
        const ::com::sun::star::lang::Locale& locale,
        const ::com::sun::star::uno::Sequence<::com::sun::star::beans::PropertyValue>& properties) override;

    // XLinguServiceEventBroadcaster
    virtual ::sal_Bool SAL_CALL addLinguServiceEventListener(
        const ::com::sun::star::uno::Reference<::com::sun::star::linguistic2::XLinguServiceEventListener>& listener) override;
    virtual ::sal_Bool SAL_CALL removeLinguServiceEventListener(
        const ::com::sun::star::uno::Reference<::com::sun::star::linguistic2::XLinguServiceEventListener>& listener) override;

    // XInitialization
    virtual void SAL_CALL initialize(
        const ::com::sun::star::uno::Sequence<::com::sun::star::uno::Any>& aArguments) override;

    // XServiceDisplayName
    virtual ::rtl::OUString SAL_CALL getServiceDisplayName(
        const ::com::sun::star::lang::Locale& aLocale) override;

    static constexpr const char* IMPL_NAME = "no.divvun.DivvunSpell";
    static constexpr const char* SERVICE_NAME = "com.sun.star.linguistic2.SpellChecker";

    static ::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface> SAL_CALL
    create(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>&);
};

} // namespace divvun
