#include "SettingsDialog.hxx"
#include "Engine.hxx"

#include <com/sun/star/awt/Rectangle.hpp>
#include <com/sun/star/awt/PosSize.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <rtl/ustring.hxx>
#include <syslog.h>

#include <set>
#include <sstream>

using namespace ::com::sun::star;

namespace divvun {

namespace {

::rtl::OUString toOU(const std::string& s) {
    return ::rtl::OUString::fromUtf8(::rtl::OString(s.data(), static_cast<sal_Int32>(s.size())));
}

void setProp(const uno::Reference<beans::XPropertySet>& props,
             const char* name, const uno::Any& value) {
    try { props->setPropertyValue(::rtl::OUString::createFromAscii(name), value); }
    catch (...) {}
}

template <typename T>
void setProp(const uno::Reference<beans::XPropertySet>& props,
             const char* name, T value) {
    setProp(props, name, uno::makeAny(value));
}

} // namespace

SettingsDialog::SettingsDialog(const uno::Reference<uno::XComponentContext>& ctx)
    : mCtx(ctx)
{
    syslog(LOG_NOTICE, "DivvunSpell SettingsDialog handler init");
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

uno::Reference<uno::XInterface>
SettingsDialog::addControl(const uno::Reference<awt::XControlContainer>& container,
                            const uno::Reference<awt::XToolkit>& toolkit,
                            const uno::Reference<awt::XWindowPeer>& parentPeer,
                            const ::rtl::OUString& modelService,
                            const ::rtl::OUString& name,
                            int x, int y, int w, int h)
{
    uno::Reference<lang::XMultiComponentFactory> sm = mCtx->getServiceManager();
    uno::Reference<awt::XControlModel> model(
        sm->createInstanceWithContext(modelService, mCtx), uno::UNO_QUERY);

    uno::Reference<beans::XPropertySet> mprops(model, uno::UNO_QUERY);
    if (mprops.is()) {
        setProp(mprops, "PositionX", static_cast<sal_Int32>(x));
        setProp(mprops, "PositionY", static_cast<sal_Int32>(y));
        setProp(mprops, "Width",     static_cast<sal_Int32>(w));
        setProp(mprops, "Height",    static_cast<sal_Int32>(h));
        setProp(mprops, "Name",      name);
    }

    ::rtl::OUString viewService = modelService;
    sal_Int32 idx = viewService.lastIndexOf(::rtl::OUString::createFromAscii("Model"));
    if (idx > 0) viewService = viewService.copy(0, idx);

    uno::Reference<awt::XControl> control(
        sm->createInstanceWithContext(viewService, mCtx), uno::UNO_QUERY);
    if (control.is()) {
        control->setModel(model);
        control->createPeer(toolkit, parentPeer);
        container->addControl(name, control);
    }
    return uno::Reference<uno::XInterface>(control, uno::UNO_QUERY);
}

void SettingsDialog::populate(const uno::Reference<awt::XWindow>& window) {
    if (mPopulated) return;
    if (!window.is()) return;

    uno::Reference<awt::XControl> ctl(window, uno::UNO_QUERY);
    if (!ctl.is()) {
        syslog(LOG_NOTICE, "SettingsDialog: window is not XControl");
        return;
    }
    uno::Reference<awt::XControlContainer> container(ctl, uno::UNO_QUERY);
    if (!container.is()) {
        syslog(LOG_NOTICE, "SettingsDialog: window is not XControlContainer");
        return;
    }
    uno::Reference<awt::XWindowPeer> peer = ctl->getPeer();

    uno::Reference<lang::XMultiComponentFactory> sm = mCtx->getServiceManager();
    uno::Reference<awt::XToolkit> toolkit(
        sm->createInstanceWithContext(
            ::rtl::OUString::createFromAscii("com.sun.star.awt.Toolkit"), mCtx),
        uno::UNO_QUERY);

    auto tags = Engine::instance().discoveredTags();
    int y = 6;
    int idx = 0;

    if (tags.empty()) {
        auto label = addControl(container, toolkit, peer,
            ::rtl::OUString::createFromAscii("com.sun.star.awt.UnoControlFixedTextModel"),
            ::rtl::OUString::createFromAscii("noBundles"), 6, y, 380, 14);
        if (label.is()) {
            uno::Reference<awt::XControl> c(label, uno::UNO_QUERY);
            if (c.is()) {
                uno::Reference<beans::XPropertySet> p(c->getModel(), uno::UNO_QUERY);
                if (p.is()) setProp(p, "Label",
                    ::rtl::OUString::createFromAscii(
                        "No DivvunSpell bundles installed in /Library/Services or "
                        "/Library/Application Support/Divvun"));
            }
        }
        mPopulated = true;
        return;
    }

    for (const auto& tag : tags) {
        ::rtl::OUString headerName = toOU("hdr_" + tag);
        auto headerCtl = addControl(container, toolkit, peer,
            ::rtl::OUString::createFromAscii("com.sun.star.awt.UnoControlFixedTextModel"),
            headerName, 6, y, 380, 14);
        if (headerCtl.is()) {
            uno::Reference<awt::XControl> c(headerCtl, uno::UNO_QUERY);
            if (c.is()) {
                uno::Reference<beans::XPropertySet> p(c->getModel(), uno::UNO_QUERY);
                if (p.is()) setProp(p, "Label", toOU("Locale: " + tag));
            }
        }
        y += 18;

        auto prefs = Engine::instance().errorPreferences(tag, "en");
        auto ignored = Engine::instance().ignoredRules(tag);
        for (const auto& [catId, title] : prefs) {
            std::string ctlName = "chk_" + tag + "_" + std::to_string(idx++);
            ::rtl::OUString cn = toOU(ctlName);
            auto chk = addControl(container, toolkit, peer,
                ::rtl::OUString::createFromAscii("com.sun.star.awt.UnoControlCheckBoxModel"),
                cn, 16, y, 380, 12);
            if (chk.is()) {
                uno::Reference<awt::XControl> c(chk, uno::UNO_QUERY);
                if (c.is()) {
                    uno::Reference<beans::XPropertySet> p(c->getModel(), uno::UNO_QUERY);
                    if (p.is()) {
                        setProp(p, "Label", toOU(title.empty() ? catId : title));
                        sal_Int16 state = ignored.count(catId) ? sal_Int16(0) : sal_Int16(1);
                        setProp(p, "State", state);
                    }
                }
            }
            mCheckBoxByName[ctlName] = {tag, catId};
            y += 14;
        }
        y += 6;
    }
    syslog(LOG_NOTICE, "SettingsDialog populated %zu checkboxes", mCheckBoxByName.size());
    mPopulated = true;
}

void SettingsDialog::readBackAndApply(const uno::Reference<awt::XWindow>& window) {
    uno::Reference<awt::XControl> ctl(window, uno::UNO_QUERY);
    if (!ctl.is()) return;
    uno::Reference<awt::XControlContainer> container(ctl, uno::UNO_QUERY);
    if (!container.is()) return;

    std::map<std::string, std::set<std::string>> ignoredByTag;
    std::set<std::string> tagsTouched;

    for (const auto& [name, ref] : mCheckBoxByName) {
        tagsTouched.insert(ref.tag);
        uno::Reference<awt::XControl> child = container->getControl(toOU(name));
        if (!child.is()) continue;
        uno::Reference<awt::XCheckBox> chk(child, uno::UNO_QUERY);
        if (!chk.is()) continue;
        sal_Int16 state = chk->getState();
        if (state == 0) ignoredByTag[ref.tag].insert(ref.categoryId);
    }

    for (const auto& tag : tagsTouched) {
        Engine::instance().setIgnoredRules(tag, ignoredByTag[tag]);
    }
    syslog(LOG_NOTICE, "SettingsDialog applied %zu tag(s)", tagsTouched.size());
}

::sal_Bool SAL_CALL SettingsDialog::callHandlerMethod(
    const uno::Reference<awt::XWindow>& window,
    const uno::Any& eventObject,
    const ::rtl::OUString& methodName)
{
    if (methodName != ::rtl::OUString::createFromAscii("external_event")) return false;
    ::rtl::OUString action;
    if (!(eventObject >>= action)) return false;

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
