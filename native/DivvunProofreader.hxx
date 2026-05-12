#pragma once

#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceDisplayName.hpp>
#include <com/sun/star/lang/XSingleComponentFactory.hpp>
#include <com/sun/star/linguistic2/XProofreader.hpp>
#include <cppuhelper/implbase4.hxx>
#include <cppuhelper/factory.hxx>

namespace divvun {

class DivvunProofreader
    : public ::cppu::WeakImplHelper4<
        ::com::sun::star::linguistic2::XProofreader,
        ::com::sun::star::lang::XServiceInfo,
        ::com::sun::star::lang::XInitialization,
        ::com::sun::star::lang::XServiceDisplayName>
{
public:
    DivvunProofreader();
    virtual ~DivvunProofreader() override;

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() override;
    virtual ::sal_Bool      SAL_CALL supportsService(const ::rtl::OUString& serviceName) override;
    virtual ::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL getSupportedServiceNames() override;

    // XSupportedLocales
    virtual ::com::sun::star::uno::Sequence<::com::sun::star::lang::Locale> SAL_CALL getLocales() override;
    virtual ::sal_Bool SAL_CALL hasLocale(const ::com::sun::star::lang::Locale& locale) override;

    // XProofreader
    virtual ::sal_Bool SAL_CALL isSpellChecker() override;
    virtual ::com::sun::star::linguistic2::ProofreadingResult SAL_CALL doProofreading(
        const ::rtl::OUString& aDocumentIdentifier,
        const ::rtl::OUString& aText,
        const ::com::sun::star::lang::Locale& aLocale,
        ::sal_Int32 nStartOfSentencePosition,
        ::sal_Int32 nSuggestedBehindEndOfSentencePosition,
        const ::com::sun::star::uno::Sequence<::com::sun::star::beans::PropertyValue>& aProperties) override;
    virtual void SAL_CALL ignoreRule(
        const ::rtl::OUString& aRuleIdentifier,
        const ::com::sun::star::lang::Locale& aLocale) override;
    virtual void SAL_CALL resetIgnoreRules() override;

    // XInitialization
    virtual void SAL_CALL initialize(
        const ::com::sun::star::uno::Sequence<::com::sun::star::uno::Any>& aArguments) override;

    // XServiceDisplayName
    virtual ::rtl::OUString SAL_CALL getServiceDisplayName(
        const ::com::sun::star::lang::Locale& aLocale) override;

    // Factory entry
    static constexpr const char* IMPL_NAME = "no.divvun.DivvunProofreader";
    static constexpr const char* SERVICE_NAME = "com.sun.star.linguistic2.Proofreader";

    static ::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface> SAL_CALL
    create(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>&);
};

} // namespace divvun
