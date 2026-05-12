#ifndef INCLUDED_COM_SUN_STAR_UI_DIALOGS_XWIZARD_HPP
#define INCLUDED_COM_SUN_STAR_UI_DIALOGS_XWIZARD_HPP

#include "sal/config.h"

#include "com/sun/star/ui/dialogs/XWizard.hdl"

#include "com/sun/star/awt/XWindow.hpp"
#include "com/sun/star/ui/dialogs/XExecutableDialog.hpp"
#include "com/sun/star/ui/dialogs/XWizardPage.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ui { namespace dialogs {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ui::dialogs::XWizard const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ui.dialogs.XWizard" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ui::dialogs::XWizard > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ui::dialogs::XWizard > >::get();
}

::css::uno::Type const & ::css::ui::dialogs::XWizard::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ui::dialogs::XWizard >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ui::dialogs::XWizard>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UI_DIALOGS_XWIZARD_HPP
