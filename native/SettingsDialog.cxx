#include "SettingsDialog.hxx"
#include "Engine.hxx"
#include "Platform.hxx"

#include <com/sun/star/awt/XListBox.hpp>
#include <com/sun/star/beans/NamedValue.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <rtl/ustring.hxx>

#include <algorithm>
#include <initializer_list>
#include <set>
#include <sstream>

using namespace ::com::sun::star;

namespace divvun {

namespace {

::rtl::OUString toOU(const std::string& s) {
    return ::rtl::OUString::fromUtf8(::rtl::OString(s.data(), static_cast<sal_Int32>(s.size())));
}

std::string fromOU(const ::rtl::OUString& s) {
    ::rtl::OString os = ::rtl::OUStringToOString(s, RTL_TEXTENCODING_UTF8);
    return std::string(os.getStr(), os.getLength());
}

void setProp(const uno::Reference<beans::XPropertySet>& props,
             const char* name, const uno::Any& value) {
    try { props->setPropertyValue(::rtl::OUString::createFromAscii(name), value); }
    catch (const uno::Exception& e) {
        logLine(std::string("SettingsDialog: setting ") + name + " failed: " + fromOU(e.Message));
    }
}

template <typename T>
void setProp(const uno::Reference<beans::XPropertySet>& props,
             const char* name, T value) {
    setProp(props, name, uno::makeAny(value));
}

// Dialog-model units (APPFONT); matches the page size in DivvunSettings.xdl.
constexpr sal_Int32 kWidth = 330;
constexpr sal_Int32 kHeight = 290;
constexpr sal_Int32 kMargin = 6;
constexpr sal_Int32 kListHeight = 14;
constexpr sal_Int32 kRowHeight = 11;

// Languages offered for grammar messages besides the installed bundles
// own. A bundle without messages in the chosen language falls back to the
// checked language and then English, so offering one it lacks is harmless.
const char* const kExtraMessageLocales[] = { "en", "nb", "nn", "sv", "fi" };

std::string languageName(const std::string& code) {
    static const std::map<std::string, std::string> names = {
        {"en", "English"},
        {"fi", "Finnish"},
        {"nb", "Norwegian Bokm\u00e5l"},
        {"nn", "Norwegian Nynorsk"},
        {"se", "Northern Sami"},
        {"sjd", "Kildin Sami"},
        {"sma", "Southern Sami"},
        {"smj", "Lule Sami"},
        {"smn", "Inari Sami"},
        {"sms", "Skolt Sami"},
        {"sv", "Swedish"},
    };
    auto it = names.find(code);
    return it == names.end() ? code : it->second + " (" + code + ")";
}

// LibreOffice's UI language, e.g. "nb-NO"; empty when it follows the system.
std::string uiLocale(const uno::Reference<uno::XComponentContext>& ctx) {
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
        return fromOU(locale);
    } catch (const uno::Exception& e) {
        logLine("SettingsDialog: could not read UI locale: " + fromOU(e.Message));
        return {};
    }
}

} // namespace

SettingsDialog::SettingsDialog(const uno::Reference<uno::XComponentContext>& ctx)
    : mCtx(ctx)
{
    logLine("DivvunSpell SettingsDialog handler init");
}

SettingsDialog::~SettingsDialog() = default;

::rtl::OUString SAL_CALL SettingsDialog::getImplementationName() {
    return ::rtl::OUString::createFromAscii(IMPL_NAME);
}

::sal_Bool SAL_CALL SettingsDialog::supportsService(const ::rtl::OUString& serviceName) {
    auto names = getSupportedServiceNames();
    for (const auto& n : names) if (n == serviceName) return true;
    return false;
}

uno::Sequence<::rtl::OUString> SAL_CALL SettingsDialog::getSupportedServiceNames() {
    uno::Sequence<::rtl::OUString> seq(1);
    seq.getArray()[0] = ::rtl::OUString::createFromAscii(SERVICE_NAME);
    return seq;
}

// Controls go in through the dialog model: inserting a model makes the dialog
// control create, position and show the matching control itself. Creating
// peers by hand leaves them unlaid-out and invisible.
void SettingsDialog::addModel(const uno::Reference<awt::XControlModel>& dialogModel,
                         const char* modelService,
                         const std::string& name,
                         sal_Int32 x, sal_Int32 y, sal_Int32 w, sal_Int32 h,
                         std::initializer_list<std::pair<const char*, uno::Any>> props)
{
    uno::Reference<lang::XMultiServiceFactory> factory(dialogModel, uno::UNO_QUERY_THROW);
    uno::Reference<container::XNameContainer> names(dialogModel, uno::UNO_QUERY_THROW);

    uno::Reference<beans::XPropertySet> model(
        factory->createInstance(::rtl::OUString::createFromAscii(modelService)),
        uno::UNO_QUERY_THROW);
    setProp(model, "PositionX", x);
    setProp(model, "PositionY", y);
    setProp(model, "Width", w);
    setProp(model, "Height", h);
    setProp(model, "Name", toOU(name));
    // Style properties such as Dropdown only apply if set before insertion,
    // which is when the control gets created.
    for (const auto& [prop, value] : props) setProp(model, prop, value);
    names->insertByName(toOU(name), uno::makeAny(model));
}

void SettingsDialog::populate(const uno::Reference<awt::XWindow>& window) {
    if (mPopulated) return;

    uno::Reference<awt::XControl> ctl(window, uno::UNO_QUERY);
    if (!ctl.is()) {
        logLine("SettingsDialog: window is not XControl");
        return;
    }
    uno::Reference<awt::XControlModel> dialogModel = ctl->getModel();
    mContainer.set(window, uno::UNO_QUERY);
    if (!dialogModel.is() || !mContainer.is()) {
        logLine("SettingsDialog: window has no model or is not a control container");
        return;
    }

    mTags = Engine::instance().discoveredTags();

    if (mTags.empty()) {
        std::ostringstream msg;
        msg << "No DivvunSpell bundles installed in:";
        for (const auto& dir : divvun::bundleSearchPaths()) msg << "\n    " << dir;
        addModel(dialogModel, "com.sun.star.awt.UnoControlFixedTextModel",
                 "noBundles", kMargin, kMargin, kWidth - 2 * kMargin, 60,
                 {{"MultiLine", uno::makeAny(true)}, {"Label", uno::makeAny(toOU(msg.str()))}});
        mPopulated = true;
        return;
    }

    const sal_Int32 labelWidth = 80;
    const sal_Int32 listX = kMargin + labelWidth;
    const sal_Int32 listWidth = 150;

    addModel(dialogModel, "com.sun.star.awt.UnoControlFixedTextModel",
             "languageLabel", kMargin, kMargin + 2, labelWidth, kRowHeight,
             {{"Label", uno::makeAny(toOU("Language:"))}});
    uno::Sequence<::rtl::OUString> items(static_cast<sal_Int32>(mTags.size()));
    for (size_t i = 0; i < mTags.size(); ++i) items.getArray()[i] = toOU(languageName(mTags[i]));
    addModel(dialogModel, "com.sun.star.awt.UnoControlListBoxModel",
             "language", listX, kMargin, listWidth, kListHeight,
             {{"Dropdown", uno::makeAny(true)},
              {"LineCount", uno::makeAny(sal_Int16(10))},
              {"StringItemList", uno::makeAny(items)},
              {"SelectedItems", uno::makeAny(uno::Sequence<sal_Int16>{0})}});

    // Feedback language: "" means the checked language itself.
    const std::string messageLocale = Engine::instance().messageLocale();
    mFeedbackCodes = {""};
    for (const auto& tag : mTags) mFeedbackCodes.push_back(tag);
    for (const char* code : kExtraMessageLocales) {
        if (std::find(mFeedbackCodes.begin(), mFeedbackCodes.end(), code) == mFeedbackCodes.end())
            mFeedbackCodes.push_back(code);
    }
    if (std::find(mFeedbackCodes.begin(), mFeedbackCodes.end(), messageLocale) == mFeedbackCodes.end())
        mFeedbackCodes.push_back(messageLocale);

    uno::Sequence<::rtl::OUString> feedbackItems(static_cast<sal_Int32>(mFeedbackCodes.size()));
    sal_Int16 feedbackSelected = 0;
    for (size_t i = 0; i < mFeedbackCodes.size(); ++i) {
        const auto& code = mFeedbackCodes[i];
        feedbackItems.getArray()[i] = toOU(code.empty() ? "Same as the text" : languageName(code));
        if (code == messageLocale) feedbackSelected = static_cast<sal_Int16>(i);
    }
    const sal_Int32 feedbackY = kMargin + kListHeight + 4;
    addModel(dialogModel, "com.sun.star.awt.UnoControlFixedTextModel",
             "feedbackLabel", kMargin, feedbackY + 2, labelWidth, kRowHeight,
             {{"Label", uno::makeAny(toOU("Feedback language:"))}});
    addModel(dialogModel, "com.sun.star.awt.UnoControlListBoxModel",
             "feedback", listX, feedbackY, listWidth, kListHeight,
             {{"Dropdown", uno::makeAny(true)},
              {"LineCount", uno::makeAny(sal_Int16(12))},
              {"StringItemList", uno::makeAny(feedbackItems)},
              {"SelectedItems", uno::makeAny(uno::Sequence<sal_Int16>{feedbackSelected})}});

    // Category titles in the feedback language when one is chosen, otherwise
    // in LibreOffice's own UI language.
    std::string titleLocale = messageLocale.empty() ? uiLocale(mCtx) : messageLocale;
    if (titleLocale.empty()) titleLocale = "en";

    const sal_Int32 top = feedbackY + kListHeight + kMargin;
    const sal_Int32 rows = (kHeight - top - kMargin) / kRowHeight;
    int idx = 0;

    for (const auto& tag : mTags) {
        auto prefs = Engine::instance().errorPreferences(tag, titleLocale);
        auto ignored = Engine::instance().ignoredRules(tag);

        std::vector<std::pair<std::string, std::vector<std::string>>> groups;
        std::map<std::string, size_t> groupByTitle;
        for (const auto& [catId, title] : prefs) {
            const std::string& shown = title.empty() ? catId : title;
            auto it = groupByTitle.find(shown);
            if (it == groupByTitle.end()) {
                groupByTitle.emplace(shown, groups.size());
                groups.push_back({shown, {catId}});
            } else {
                groups[it->second].second.push_back(catId);
            }
        }

        const sal_Int32 count = static_cast<sal_Int32>(groups.size());
        const sal_Int32 cols = std::max<sal_Int32>(1, (count + rows - 1) / rows);
        const sal_Int32 colWidth = (kWidth - 2 * kMargin) / cols;

        for (sal_Int32 i = 0; i < count; ++i) {
            const auto& [shown, ids] = groups[i];
            std::string name = "chk_" + std::to_string(idx++);
            bool allIgnored = std::all_of(ids.begin(), ids.end(),
                                          [&](const std::string& id) { return ignored.count(id) > 0; });
            addModel(dialogModel, "com.sun.star.awt.UnoControlCheckBoxModel", name,
                     kMargin + (i / rows) * colWidth, top + (i % rows) * kRowHeight,
                     colWidth - 2, kRowHeight,
                     {{"Label", uno::makeAny(toOU(shown))},
                      {"State", uno::makeAny(allIgnored ? sal_Int16(0) : sal_Int16(1))}});
            mCheckBoxByName[name] = {tag, ids};
            mCheckBoxNamesByTag[tag].push_back(name);
        }
        logLine("SettingsDialog " + tag + ": " + std::to_string(prefs.size()) + " categories in "
                + std::to_string(count) + " checkboxes, " + std::to_string(cols) + " column(s)");
    }

    // A dropdown's SelectedItems set on the model before its control exists
    // doesn't show, so select on the controls as well.
    uno::Reference<awt::XListBox> listBox(mContainer->getControl(toOU("language")), uno::UNO_QUERY);
    if (listBox.is()) {
        listBox->selectItemPos(0, true);
        listBox->addItemListener(this);
    }
    uno::Reference<awt::XListBox> feedbackBox(mContainer->getControl(toOU("feedback")), uno::UNO_QUERY);
    if (feedbackBox.is()) feedbackBox->selectItemPos(feedbackSelected, true);
    showLanguage(0);
    mPopulated = true;
}

void SettingsDialog::showLanguage(size_t index) {
    if (!mContainer.is()) return;
    for (size_t i = 0; i < mTags.size(); ++i) {
        for (const auto& name : mCheckBoxNamesByTag[mTags[i]]) {
            uno::Reference<awt::XWindow> w(mContainer->getControl(toOU(name)), uno::UNO_QUERY);
            if (w.is()) w->setVisible(i == index);
        }
    }
}

void SAL_CALL SettingsDialog::itemStateChanged(const awt::ItemEvent& event) {
    try {
        if (event.Selected >= 0) showLanguage(static_cast<size_t>(event.Selected));
    } catch (const uno::Exception& e) {
        logLine("SettingsDialog language switch failed: " + fromOU(e.Message));
    }
}

void SAL_CALL SettingsDialog::disposing(const lang::EventObject&) {
    mContainer.clear();
}

void SettingsDialog::readBackAndApply(const uno::Reference<awt::XWindow>& window) {
    uno::Reference<awt::XControl> ctl(window, uno::UNO_QUERY);
    if (!ctl.is()) return;
    uno::Reference<container::XNameAccess> names(ctl->getModel(), uno::UNO_QUERY);
    if (!names.is()) return;

    std::map<std::string, std::set<std::string>> ignoredByTag;
    std::set<std::string> tagsTouched;

    for (const auto& [name, ref] : mCheckBoxByName) {
        tagsTouched.insert(ref.tag);
        uno::Reference<beans::XPropertySet> props(names->getByName(toOU(name)), uno::UNO_QUERY);
        if (!props.is()) continue;
        sal_Int16 state = 1;
        props->getPropertyValue(::rtl::OUString::createFromAscii("State")) >>= state;
        if (state == 0) ignoredByTag[ref.tag].insert(ref.categoryIds.begin(), ref.categoryIds.end());
    }

    for (const auto& tag : tagsTouched) {
        Engine::instance().setIgnoredRules(tag, ignoredByTag[tag]);
    }

    uno::Reference<beans::XPropertySet> feedback;
    if (names->hasByName(toOU("feedback"))) feedback.set(names->getByName(toOU("feedback")), uno::UNO_QUERY);
    if (feedback.is()) {
        uno::Sequence<sal_Int16> selected;
        feedback->getPropertyValue(::rtl::OUString::createFromAscii("SelectedItems")) >>= selected;
        if (selected.getLength() == 1 && selected[0] >= 0
            && static_cast<size_t>(selected[0]) < mFeedbackCodes.size()) {
            Engine::instance().setMessageLocale(mFeedbackCodes[selected[0]]);
        }
    }
    logLine("SettingsDialog applied " + std::to_string(tagsTouched.size()) + " tag(s)");
}

::sal_Bool SAL_CALL SettingsDialog::callHandlerMethod(
    const uno::Reference<awt::XWindow>& window,
    const uno::Any& eventObject,
    const ::rtl::OUString& methodName)
{
    if (methodName != ::rtl::OUString::createFromAscii("external_event")) return false;
    ::rtl::OUString action;
    if (!(eventObject >>= action)) return false;

    // Anything escaping into LO here is thrown past the Options dialog's
    // scheduler, which aborts the whole process on an unhandled exception.
    try {
        if (action == ::rtl::OUString::createFromAscii("initialize")) {
            populate(window);
            return true;
        }
        if (action == ::rtl::OUString::createFromAscii("ok")
            || action == ::rtl::OUString::createFromAscii("apply")) {
            readBackAndApply(window);
            return true;
        }
        if (action == ::rtl::OUString::createFromAscii("back")) {
            return true;
        }
    } catch (const uno::Exception& e) {
        logLine("SettingsDialog " + fromOU(action) + " failed: " + fromOU(e.Message));
    } catch (const std::exception& e) {
        logLine("SettingsDialog " + fromOU(action) + " failed: " + e.what());
    } catch (...) {
        logLine("SettingsDialog " + fromOU(action) + " failed: unknown exception");
    }
    return false;
}

uno::Sequence<::rtl::OUString> SAL_CALL SettingsDialog::getSupportedMethodNames() {
    uno::Sequence<::rtl::OUString> seq(1);
    seq.getArray()[0] = ::rtl::OUString::createFromAscii("external_event");
    return seq;
}

uno::Reference<uno::XInterface> SAL_CALL SettingsDialog::create(
    const uno::Reference<uno::XComponentContext>& ctx)
{
    return static_cast<cppu::OWeakObject*>(new SettingsDialog(ctx));
}

} // namespace divvun
