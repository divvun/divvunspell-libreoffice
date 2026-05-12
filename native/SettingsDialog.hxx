#pragma once

#include <com/sun/star/awt/XContainerWindowEventHandler.hpp>
#include <com/sun/star/awt/XControl.hpp>
#include <com/sun/star/awt/XControlContainer.hpp>
#include <com/sun/star/awt/XControlModel.hpp>
#include <com/sun/star/awt/XCheckBox.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/awt/XWindowPeer.hpp>
#include <com/sun/star/awt/XToolkit.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase2.hxx>
#include <rtl/ustring.hxx>

#include <map>
#include <string>

namespace divvun {

class SettingsDialog
    : public ::cppu::WeakImplHelper2<
        ::com::sun::star::awt::XContainerWindowEventHandler,
        ::com::sun::star::lang::XServiceInfo>
{
public:
    explicit SettingsDialog(
        const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>& ctx);
    virtual ~SettingsDialog() override;

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() override;
    virtual ::sal_Bool      SAL_CALL supportsService(const ::rtl::OUString& serviceName) override;
    virtual ::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL getSupportedServiceNames() override;

    // XContainerWindowEventHandler
    virtual ::sal_Bool SAL_CALL callHandlerMethod(
        const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindow>& window,
        const ::com::sun::star::uno::Any& eventObject,
        const ::rtl::OUString& methodName) override;
    virtual ::com::sun::star::uno::Sequence<::rtl::OUString> SAL_CALL getSupportedMethodNames() override;

    static constexpr const char* IMPL_NAME = "no.divvun.SettingsDialog";
    // Custom service name that LO's OptionsDialog framework will instantiate
    // when the user navigates to our page; matches the EventHandlerService in
    // OptionsDialog.xcu.
    static constexpr const char* SERVICE_NAME = "no.divvun.SettingsDialogHandler";

    static ::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface> SAL_CALL
    create(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>& ctx);

private:
    struct CheckBoxRef {
        std::string tag;
        std::string categoryId;
    };

    void populate(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindow>& window);
    void readBackAndApply(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindow>& window);

    ::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface>
    addControl(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XControlContainer>& container,
               const ::com::sun::star::uno::Reference<::com::sun::star::awt::XToolkit>& toolkit,
               const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindowPeer>& parentPeer,
               const ::rtl::OUString& modelService,
               const ::rtl::OUString& name,
               int x, int y, int w, int h);

    ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext> mCtx;
    std::map<std::string, CheckBoxRef> mCheckBoxByName;
    bool mPopulated = false;
};

} // namespace divvun
