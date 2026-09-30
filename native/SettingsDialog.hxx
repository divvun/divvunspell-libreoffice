#pragma once

#include <com/sun/star/awt/XContainerWindowEventHandler.hpp>
#include <com/sun/star/awt/XControl.hpp>
#include <com/sun/star/awt/XControlContainer.hpp>
#include <com/sun/star/awt/XControlModel.hpp>
#include <com/sun/star/awt/XItemListener.hpp>
#include <com/sun/star/awt/XKeyListener.hpp>
#include <com/sun/star/awt/XListBox.hpp>
#include <com/sun/star/awt/XMouseListener.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/awt/grid/XGridControl.hpp>
#include <com/sun/star/awt/grid/XGridRowSelection.hpp>
#include <com/sun/star/awt/grid/XGridSelectionListener.hpp>
#include <com/sun/star/awt/grid/XMutableGridDataModel.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase6.hxx>
#include <rtl/ustring.hxx>

#include <initializer_list>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace divvun {

class SettingsDialog
    : public ::cppu::WeakImplHelper6<
        ::com::sun::star::awt::XContainerWindowEventHandler,
        ::com::sun::star::awt::XItemListener,
        ::com::sun::star::awt::XMouseListener,
        ::com::sun::star::awt::XKeyListener,
        ::com::sun::star::awt::grid::XGridSelectionListener,
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

    // XItemListener: the language and feedback language dropdowns.
    virtual void SAL_CALL itemStateChanged(const ::com::sun::star::awt::ItemEvent& event) override;

    // XMouseListener, XKeyListener: ticking categories in the grid.
    virtual void SAL_CALL mousePressed(const ::com::sun::star::awt::MouseEvent& event) override;
    virtual void SAL_CALL mouseReleased(const ::com::sun::star::awt::MouseEvent&) override {}
    virtual void SAL_CALL mouseEntered(const ::com::sun::star::awt::MouseEvent&) override {}
    virtual void SAL_CALL mouseExited(const ::com::sun::star::awt::MouseEvent&) override {}
    virtual void SAL_CALL keyPressed(const ::com::sun::star::awt::KeyEvent& event) override;
    virtual void SAL_CALL keyReleased(const ::com::sun::star::awt::KeyEvent&) override {}

    // XGridSelectionListener: shows the selected category's full title.
    virtual void SAL_CALL selectionChanged(const ::com::sun::star::awt::grid::GridSelectionEvent& event) override;

    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& event) override;

    static constexpr const char* IMPL_NAME = "no.divvun.SettingsDialog";
    // Must not be a LibreOffice service name: registering under one (it once
    // claimed com.sun.star.awt.ContainerWindowProvider) replaces LO's own
    // implementation. Matches EventHandlerService in OptionsDialog.xcu.
    static constexpr const char* SERVICE_NAME = "no.divvun.SettingsDialogHandler";

    static ::com::sun::star::uno::Reference<::com::sun::star::uno::XInterface> SAL_CALL
    create(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>& ctx);

private:
    // One grid row per distinct category title: bundles give several
    // categories the same title, and separate rows for them are
    // indistinguishable.
    struct CategoryRow {
        std::string tag;
        std::string title;
        std::vector<std::string> categoryIds;
    };

    void populate(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XWindow>& window);
    void readBackAndApply();
    void showLanguage(size_t index);
    ::com::sun::star::uno::Sequence<::rtl::OUString> feedbackItemsFor(const std::string& tag, sal_Int16& selected);
    void showFeedbackFor(const std::string& tag);
    std::string titleLocale(const std::string& tag) const;
    void addGrid(sal_Int32 x, sal_Int32 y, sal_Int32 w, sal_Int32 h);
    void fillGrid(const std::string& tag);
    bool isTicked(const CategoryRow& row) const;
    void toggleRow(sal_Int32 row);
    void showTitle(sal_Int32 row);

    void addModel(const ::com::sun::star::uno::Reference<::com::sun::star::awt::XControlModel>& dialogModel,
                  const char* modelService,
                  const std::string& name,
                  sal_Int32 x, sal_Int32 y, sal_Int32 w, sal_Int32 h,
                  std::initializer_list<std::pair<const char*, ::com::sun::star::uno::Any>> props);

    ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext> mCtx;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::XControlContainer> mContainer;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::XControlModel> mDialogModel;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::XListBox> mLanguageBox;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::XListBox> mFeedbackBox;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::grid::XGridControl> mGrid;
    ::com::sun::star::uno::Reference<::com::sun::star::awt::grid::XMutableGridDataModel> mGridData;
    // LibreOffice's UI language, which the page's own text is shown in.
    std::string mUiLocale;
    std::vector<std::string> mTags;
    // Feedback choices listed for the shown language, and the choice per
    // language: "" for the text's own, Engine::kSameAsUi, or a locale code.
    std::vector<std::string> mFeedbackCodes;
    std::map<std::string, std::string> mFeedbackByTag;
    // The grid's rows, for the shown language.
    std::vector<CategoryRow> mRows;
    // Unticked category ids per tag, kept per category rather than per
    // row so they survive rebuilds that regroup the titles.
    std::map<std::string, std::set<std::string>> mUnticked;
    size_t mLanguageIndex = 0;
    bool mRefreshingFeedback = false;
    bool mPopulated = false;
};

} // namespace divvun
