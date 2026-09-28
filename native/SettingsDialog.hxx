#pragma once

#include <com/sun/star/awt/XContainerWindowEventHandler.hpp>
#include <com/sun/star/awt/XControl.hpp>
#include <com/sun/star/awt/XControlContainer.hpp>
#include <com/sun/star/awt/XControlModel.hpp>
#include <com/sun/star/awt/XItemListener.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase3.hxx>
#include <rtl/ustring.hxx>

#include <initializer_list>
#include <map>
#include <string>
#include <vector>

namespace divvun {

class SettingsDialog
    : public ::cppu::WeakImplHelper3<
        ::com::sun::star::awt::XContainerWindowEventHandler,
        ::com::sun::star::awt::XItemListener,
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

    // XItemListener: the language dropdown.
    virtual void SAL_CALL itemStateChanged(const ::com::sun::star::awt::ItemEvent& event) override;
    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& event) override;

    static constexpr const char* IMPL_NAME = "no.divvun.SettingsDialog";
    // Must not be a LibreOffice service name: registering under one (it once
    // claimed com.sun.star.awt.ContainerWindowProvider) replaces LO's own
    // implementation. Matches EventHandlerService in OptionsDialog.xcu.
    static constexpr const char* SERVICE_NAME = "no.divvun.SettingsDialogHandler";

    static ::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface> SAL_CALL
    create(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>& ctx);

private:
    // One checkbox per distinct category title: bundles give several
    // categories the same title, and separate rows for them are
    // indistinguishable.
    struct CheckBoxRef {
        std::string tag;
        std::vector<std::string> categoryIds;
    };

    void populate(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindow>& window);
    void readBackAndApply(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindow>& window);
    void showLanguage(size_t index);

    void addModel(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XControlModel>& dialogModel,
                  const char* modelService,
                  const std::string& name,
                  sal_Int32 x, sal_Int32 y, sal_Int32 w, sal_Int32 h,
                  std::initializer_list<std::pair<const char*, ::com::sun::star::uno::Any>> props);

    ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext> mCtx;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::XControlContainer> mContainer;
    std::vector<std::string> mTags;
    std::vector<std::string> mFeedbackCodes;
    std::map<std::string, std::vector<std::string>> mCheckBoxNamesByTag;
    std::map<std::string, CheckBoxRef> mCheckBoxByName;
    bool mPopulated = false;
};

} // namespace divvun
