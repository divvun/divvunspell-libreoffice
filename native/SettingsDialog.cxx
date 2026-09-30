#include "SettingsDialog.hxx"
#include "Engine.hxx"
#include "Platform.hxx"
#include "Strings.hxx"
#include "UiLocale.hxx"

#include <com/sun/star/awt/XLayoutConstrains.hpp>
#include <com/sun/star/awt/XListBox.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/i18n/Collator.hpp>
#include <com/sun/star/i18n/CollatorOptions.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/style/VerticalAlignment.hpp>
#include <com/sun/star/util/MeasureUnit.hpp>
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
constexpr sal_Int32 kMaxColumns = 3;

lang::Locale toLocale(const std::string& tag) {
    lang::Locale locale;
    const auto dash = tag.find('-');
    if (dash == std::string::npos) {
        locale.Language = toOU(tag);
    } else if (tag.find('-', dash + 1) == std::string::npos) {
        locale.Language = toOU(tag.substr(0, dash));
        locale.Country = toOU(tag.substr(dash + 1));
    } else {
        locale.Language = toOU("qlt");
        locale.Variant = toOU(tag);
    }
    return locale;
}

using TitleGroups = std::vector<std::pair<std::string, std::vector<std::string>>>;

// Alphabetical by title, as a reader of the titles' language orders them.
void sortByTitle(const uno::Reference<uno::XComponentContext>& ctx,
                 const std::string& locale, TitleGroups& groups)
{
    uno::Reference<i18n::XCollator> collator;
    for (const std::string& tag : {locale, std::string("en")}) {
        try {
            uno::Reference<i18n::XCollator> candidate = i18n::Collator::create(ctx);
            candidate->loadDefaultCollator(toLocale(tag), i18n::CollatorOptions::CollatorOptions_IGNORE_CASE);
            collator = candidate;
            break;
        } catch (const uno::Exception& e) {
            logLine("SettingsDialog: no collator for " + tag + ": " + fromOU(e.Message));
        }
    }

    std::vector<std::pair<::rtl::OUString, size_t>> keys;
    for (size_t i = 0; i < groups.size(); ++i) keys.emplace_back(toOU(groups[i].first), i);
    std::stable_sort(keys.begin(), keys.end(), [&](const auto& a, const auto& b) {
        if (collator.is()) return collator->compareString(a.first, b.first) < 0;
        return a.first.compareToIgnoreAsciiCase(b.first) < 0;
    });

    TitleGroups sorted;
    for (const auto& key : keys) sorted.push_back(std::move(groups[key.second]));
    groups = std::move(sorted);
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

    mUiLocale = uiLocale(mCtx);
    mTags = Engine::instance().discoveredTags();

    if (mTags.empty()) {
        std::ostringstream msg;
        msg << uiString(StringId::NoBundles, mUiLocale);
        for (const auto& dir : divvun::bundleSearchPaths()) msg << "\n    " << dir;
        addModel(dialogModel, "com.sun.star.awt.UnoControlFixedTextModel",
                 "noBundles", kMargin, kMargin, kWidth - 2 * kMargin, 60,
                 {{"MultiLine", uno::makeAny(true)}, {"Label", uno::makeAny(toOU(msg.str()))}});
        mPopulated = true;
        return;
    }

    const sal_Int32 labelWidth = 95;
    const sal_Int32 listX = kMargin + labelWidth;
    const sal_Int32 listWidth = 150;

    addModel(dialogModel, "com.sun.star.awt.UnoControlFixedTextModel",
             "languageLabel", kMargin, kMargin + 2, labelWidth, kRowHeight,
             {{"Label", uno::makeAny(toOU(uiString(StringId::ProofingLanguage, mUiLocale)))}});
    uno::Sequence<::rtl::OUString> items(static_cast<sal_Int32>(mTags.size()));
    for (size_t i = 0; i < mTags.size(); ++i) items.getArray()[i] = toOU(languageName(mTags[i], mUiLocale));
    addModel(dialogModel, "com.sun.star.awt.UnoControlListBoxModel",
             "language", listX, kMargin, listWidth, kListHeight,
             {{"Dropdown", uno::makeAny(true)},
              {"LineCount", uno::makeAny(sal_Int16(10))},
              {"StringItemList", uno::makeAny(items)},
              {"SelectedItems", uno::makeAny(uno::Sequence<sal_Int16>{0})}});

    for (const auto& tag : mTags) mFeedbackByTag[tag] = Engine::instance().messageLocale(tag);
    sal_Int16 feedbackSelected = 0;
    const auto feedbackItems = feedbackItemsFor(mTags[0], feedbackSelected);
    const sal_Int32 feedbackY = kMargin + kListHeight + 4;
    addModel(dialogModel, "com.sun.star.awt.UnoControlFixedTextModel",
             "feedbackLabel", kMargin, feedbackY + 2, labelWidth, kRowHeight,
             {{"Label", uno::makeAny(toOU(uiString(StringId::FeedbackLanguage, mUiLocale)))}});
    addModel(dialogModel, "com.sun.star.awt.UnoControlListBoxModel",
             "feedback", listX, feedbackY, listWidth, kListHeight,
             {{"Dropdown", uno::makeAny(true)},
              {"LineCount", uno::makeAny(sal_Int16(12))},
              {"StringItemList", uno::makeAny(feedbackItems)},
              {"SelectedItems", uno::makeAny(uno::Sequence<sal_Int16>{feedbackSelected})}});

    mDialogModel = dialogModel;
    mUnits.set(window, uno::UNO_QUERY);
    mCheckBoxTop = feedbackY + kListHeight + kMargin;
    for (const auto& tag : mTags) {
        mUnticked[tag] = Engine::instance().ignoredRules(tag);
        buildCheckBoxes(tag);
    }

    // A dropdown's SelectedItems set on the model before its control exists
    // doesn't show, so select on the controls as well.
    mLanguageBox.set(mContainer->getControl(toOU("language")), uno::UNO_QUERY);
    if (mLanguageBox.is()) {
        mLanguageBox->selectItemPos(0, true);
        mLanguageBox->addItemListener(this);
    }
    mFeedbackBox.set(mContainer->getControl(toOU("feedback")), uno::UNO_QUERY);
    if (mFeedbackBox.is()) {
        mFeedbackBox->selectItemPos(feedbackSelected, true);
        mFeedbackBox->addItemListener(this);
    }
    showLanguage(0);
    mPopulated = true;
}

// Feedback choices for a proofing language: the text's own language, the UI
// language, then each language its bundle has messages in. Fills
// mFeedbackCodes to match and points selected at the saved choice. A saved
// language the bundle no longer has messages in gets "same as the text",
// which is what the runtime falls back to for it anyway. When the bundle
// can't say (it failed to load), the saved language is kept and listed.
uno::Sequence<::rtl::OUString> SettingsDialog::feedbackItemsFor(const std::string& tag, sal_Int16& selected) {
    const auto available = Engine::instance().messageLocales(tag);
    mFeedbackCodes = {"", Engine::kSameAsUi};
    mFeedbackCodes.insert(mFeedbackCodes.end(), available.begin(), available.end());

    auto& saved = mFeedbackByTag[tag];
    auto it = std::find(mFeedbackCodes.begin(), mFeedbackCodes.end(), saved);
    if (it == mFeedbackCodes.end() && available.empty()) {
        mFeedbackCodes.push_back(saved);
        it = mFeedbackCodes.end() - 1;
    } else if (it == mFeedbackCodes.end()) {
        logLine("SettingsDialog " + tag + ": bundle has no messages in " + saved);
        saved.clear();
        it = mFeedbackCodes.begin();
    }
    selected = static_cast<sal_Int16>(it - mFeedbackCodes.begin());

    uno::Sequence<::rtl::OUString> items(static_cast<sal_Int32>(mFeedbackCodes.size()));
    items.getArray()[0] = toOU(uiString(StringId::SameAsText, mUiLocale));
    items.getArray()[1] = toOU(uiString(StringId::SameAsUi, mUiLocale));
    for (size_t i = 2; i < mFeedbackCodes.size(); ++i) items.getArray()[i] = toOU(languageName(mFeedbackCodes[i], mUiLocale));
    return items;
}

void SettingsDialog::showFeedbackFor(const std::string& tag) {
    uno::Reference<container::XNameAccess> models(mDialogModel, uno::UNO_QUERY);
    if (!models.is() || !models->hasByName(toOU("feedback"))) return;
    uno::Reference<beans::XPropertySet> model(models->getByName(toOU("feedback")), uno::UNO_QUERY);
    if (!model.is()) return;

    sal_Int16 selected = 0;
    const auto items = feedbackItemsFor(tag, selected);
    // Replacing the items may report selection changes that aren't the user's.
    struct Refreshing {
        bool& flag;
        explicit Refreshing(bool& f) : flag(f) { flag = true; }
        ~Refreshing() { flag = false; }
    } refreshing(mRefreshingFeedback);
    setProp(model, "StringItemList", items);
    setProp(model, "SelectedItems", uno::Sequence<sal_Int16>{selected});
    if (mFeedbackBox.is()) mFeedbackBox->selectItemPos(selected, true);
}

// Category titles in the language the tag's messages will be shown in.
std::string SettingsDialog::titleLocale(const std::string& tag) const {
    auto it = mFeedbackByTag.find(tag);
    const std::string setting = it == mFeedbackByTag.end() ? std::string{} : it->second;
    const std::string locale = Engine::instance().effectiveMessageLocale(tag, setting);
    return locale.empty() ? "en" : locale;
}

void SettingsDialog::buildCheckBoxes(const std::string& tag) {
    const std::string prefix = "chk_" + std::to_string(++mGeneration) + "_";
    const std::string locale = titleLocale(tag);

    auto prefs = Engine::instance().errorPreferences(tag, locale);
    const auto& unticked = mUnticked[tag];

    TitleGroups groups;
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
    sortByTitle(mCtx, locale, groups);

    std::vector<std::string> names;
    std::vector<std::string> titles;
    for (const auto& [shown, ids] : groups) {
        std::string name = prefix + std::to_string(names.size());
        bool allUnticked = std::all_of(ids.begin(), ids.end(),
                                       [&](const std::string& id) { return unticked.count(id) > 0; });
        addModel(mDialogModel, "com.sun.star.awt.UnoControlCheckBoxModel", name,
                 kMargin, mCheckBoxTop, kWidth - 2 * kMargin, kRowHeight,
                 {{"Label", uno::makeAny(toOU(shown))},
                  {"MultiLine", uno::makeAny(true)},
                  {"VerticalAlign", uno::makeAny(style::VerticalAlignment_TOP)},
                  {"State", uno::makeAny(allUnticked ? sal_Int16(0) : sal_Int16(1))}});
        mCheckBoxByName[name] = {tag, ids};
        mCheckBoxNamesByTag[tag].push_back(name);
        names.push_back(name);
        titles.push_back(shown);
    }
    layoutCheckBoxes(names, titles);
    logLine("SettingsDialog " + tag + ": " + std::to_string(prefs.size()) + " categories in "
            + std::to_string(groups.size()) + " checkboxes, titles in " + locale);
}

// Height in APPFONT a checkbox needs to show its whole title wrapped to the
// given width.
sal_Int32 SettingsDialog::measureHeight(const std::string& name, const std::string& title,
                                        sal_Int32 width) const
{
    try {
        uno::Reference<awt::XControl> control;
        if (mContainer.is()) control = mContainer->getControl(toOU(name));
        uno::Reference<awt::XLayoutConstrains> layout(control, uno::UNO_QUERY);
        if (layout.is() && mUnits.is()) {
            awt::Size px = mUnits->convertSizeToPixel(awt::Size(width, kRowHeight), util::MeasureUnit::APPFONT);
            if (px.Width > 0) {
                awt::Size fit = layout->calcAdjustedSize(awt::Size(px.Width, 1));
                awt::Size logic = mUnits->convertSizeToLogic(fit, util::MeasureUnit::APPFONT);
                if (logic.Height > 0) return std::max(kRowHeight, logic.Height + 2);
            }
        }
    } catch (const uno::Exception& e) {
        logLine("SettingsDialog: measuring " + name + " failed: " + fromOU(e.Message));
    }

    // An APPFONT unit is a quarter of an average character wide and an eighth
    // of a line high; the check box itself takes about 12.
    sal_Int32 chars = 0;
    for (unsigned char c : title) if ((c & 0xC0) != 0x80) ++chars;
    const sal_Int32 textWidth = std::max<sal_Int32>(1, width - 12);
    const sal_Int32 lines = std::max<sal_Int32>(1, (chars * 4 + textWidth - 1) / textWidth);
    return std::max(kRowHeight, lines * 8 + 3);
}

// Fewest columns that show every title in full, wrapped where needed. When
// even kMaxColumns can't, titles are cut to one line in as many columns as it
// takes, with the full title as a tooltip.
void SettingsDialog::layoutCheckBoxes(const std::vector<std::string>& names,
                                      const std::vector<std::string>& titles)
{
    uno::Reference<container::XNameAccess> models(mDialogModel, uno::UNO_QUERY);
    if (!models.is() || names.empty()) return;
    auto modelOf = [&](const std::string& name) {
        return uno::Reference<beans::XPropertySet>(models->getByName(toOU(name)), uno::UNO_QUERY_THROW);
    };

    const sal_Int32 width = kWidth - 2 * kMargin;
    const sal_Int32 height = kHeight - mCheckBoxTop - kMargin;
    const size_t count = names.size();

    for (sal_Int32 cols = 1; cols <= kMaxColumns; ++cols) {
        const sal_Int32 colWidth = width / cols;
        std::vector<sal_Int32> heights(count), columns(count), tops(count);
        sal_Int32 col = 0, y = 0;
        bool fits = true;
        for (size_t i = 0; i < count && fits; ++i) {
            heights[i] = measureHeight(names[i], titles[i], colWidth - 2);
            if (y > 0 && y + heights[i] > height) { ++col; y = 0; }
            fits = col < cols && heights[i] <= height;
            columns[i] = col;
            tops[i] = y;
            y += heights[i];
        }
        if (!fits) continue;
        for (size_t i = 0; i < count; ++i) {
            auto model = modelOf(names[i]);
            setProp(model, "PositionX", kMargin + columns[i] * colWidth);
            setProp(model, "PositionY", mCheckBoxTop + tops[i]);
            setProp(model, "Width", colWidth - 2);
            setProp(model, "Height", heights[i]);
        }
        return;
    }

    const sal_Int32 rows = std::max<sal_Int32>(1, height / kRowHeight);
    const sal_Int32 cols = (static_cast<sal_Int32>(count) + rows - 1) / rows;
    const sal_Int32 colWidth = width / cols;
    for (size_t i = 0; i < count; ++i) {
        const sal_Int32 n = static_cast<sal_Int32>(i);
        auto model = modelOf(names[i]);
        setProp(model, "MultiLine", false);
        setProp(model, "HelpText", toOU(titles[i]));
        setProp(model, "PositionX", kMargin + (n / rows) * colWidth);
        setProp(model, "PositionY", mCheckBoxTop + (n % rows) * kRowHeight);
        setProp(model, "Width", colWidth - 2);
        setProp(model, "Height", kRowHeight);
    }
}

void SettingsDialog::captureCheckBoxStates() {
    uno::Reference<container::XNameAccess> models(mDialogModel, uno::UNO_QUERY);
    if (!models.is()) return;
    for (const auto& [name, ref] : mCheckBoxByName) {
        if (!models->hasByName(toOU(name))) continue;
        uno::Reference<beans::XPropertySet> props(models->getByName(toOU(name)), uno::UNO_QUERY);
        if (!props.is()) continue;
        sal_Int16 state = 1;
        props->getPropertyValue(::rtl::OUString::createFromAscii("State")) >>= state;
        auto& unticked = mUnticked[ref.tag];
        for (const auto& id : ref.categoryIds) {
            if (state == 0) unticked.insert(id);
            else unticked.erase(id);
        }
    }
}

void SettingsDialog::removeCheckBoxes(const std::string& tag) {
    uno::Reference<container::XNameContainer> models(mDialogModel, uno::UNO_QUERY);
    for (const auto& name : mCheckBoxNamesByTag[tag]) {
        if (models.is() && models->hasByName(toOU(name))) models->removeByName(toOU(name));
        mCheckBoxByName.erase(name);
    }
    mCheckBoxNamesByTag.erase(tag);
}

void SettingsDialog::showLanguage(size_t index) {
    if (!mContainer.is()) return;
    mLanguageIndex = index;
    for (size_t i = 0; i < mTags.size(); ++i) {
        for (const auto& name : mCheckBoxNamesByTag[mTags[i]]) {
            uno::Reference<awt::XWindow> w(mContainer->getControl(toOU(name)), uno::UNO_QUERY);
            if (w.is()) w->setVisible(i == index);
        }
    }
}

// Must not throw: an exception escaping into LO aborts the process.
void SAL_CALL SettingsDialog::itemStateChanged(const awt::ItemEvent& event) {
    try {
        if (event.Selected < 0 || mRefreshingFeedback) return;
        const size_t selected = static_cast<size_t>(event.Selected);
        if (mFeedbackBox.is() && event.Source == uno::Reference<uno::XInterface>(mFeedbackBox, uno::UNO_QUERY)) {
            if (mLanguageIndex >= mTags.size() || selected >= mFeedbackCodes.size()) return;
            const std::string& tag = mTags[mLanguageIndex];
            mFeedbackByTag[tag] = mFeedbackCodes[selected];
            captureCheckBoxStates();
            removeCheckBoxes(tag);
            buildCheckBoxes(tag);
            showLanguage(mLanguageIndex);
        } else if (selected < mTags.size()) {
            showLanguage(selected);
            showFeedbackFor(mTags[selected]);
        }
    } catch (const uno::Exception& e) {
        logLine("SettingsDialog selection change failed: " + fromOU(e.Message));
    } catch (const std::exception& e) {
        logLine(std::string("SettingsDialog selection change failed: ") + e.what());
    } catch (...) {
        logLine("SettingsDialog selection change failed: unknown exception");
    }
}

void SAL_CALL SettingsDialog::disposing(const lang::EventObject&) {
    mContainer.clear();
    mLanguageBox.clear();
    mFeedbackBox.clear();
}

void SettingsDialog::readBackAndApply() {
    if (!mPopulated) return;
    captureCheckBoxStates();
    for (const auto& tag : mTags) Engine::instance().setIgnoredRules(tag, mUnticked[tag]);

    // The shown language's choice, in case its change event went missing.
    if (mFeedbackBox.is() && mLanguageIndex < mTags.size()) {
        const sal_Int16 selected = mFeedbackBox->getSelectedItemPos();
        if (selected >= 0 && static_cast<size_t>(selected) < mFeedbackCodes.size())
            mFeedbackByTag[mTags[mLanguageIndex]] = mFeedbackCodes[selected];
    }
    for (const auto& tag : mTags) Engine::instance().setMessageLocale(tag, mFeedbackByTag[tag]);
    logLine("SettingsDialog applied " + std::to_string(mTags.size()) + " tag(s)");
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
            readBackAndApply();
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
    publishUiLocale(ctx);
    return static_cast<cppu::OWeakObject*>(new SettingsDialog(ctx));
}

} // namespace divvun
