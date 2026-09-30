#pragma once

#include <com/sun/star/uno/XComponentContext.hpp>

#include <string>

namespace divvun {

// LibreOffice's UI language as a BCP-47 tag, e.g. "nb-NO"; empty when it
// can't be determined.
std::string uiLocale(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>& ctx);

// Hands uiLocale(ctx) to the Engine, which resolves the "same as the user
// interface language" feedback setting with it. Never throws.
void publishUiLocale(const ::com::sun::star::uno::Reference<::com::sun::star::uno::XComponentContext>& ctx);

} // namespace divvun
