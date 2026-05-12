#ifndef INCLUDED_COM_SUN_STAR_UI_XPANELS_HPP
#define INCLUDED_COM_SUN_STAR_UI_XPANELS_HPP

#include "sal/config.h"

#include "com/sun/star/ui/XPanels.hdl"

#include "com/sun/star/container/XIndexAccess.hpp"
#include "com/sun/star/container/XNameAccess.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ui {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ui::XPanels const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ui.XPanels" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ui::XPanels > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ui::XPanels > >::get();
}

::css::uno::Type const & ::css::ui::XPanels::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ui::XPanels >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ui::XPanels>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UI_XPANELS_HPP
