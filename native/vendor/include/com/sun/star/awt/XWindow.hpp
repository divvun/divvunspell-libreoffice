#ifndef INCLUDED_COM_SUN_STAR_AWT_XWINDOW_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XWINDOW_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XWindow.hdl"

#include "com/sun/star/awt/Rectangle.hpp"
#include "com/sun/star/awt/XFocusListener.hpp"
#include "com/sun/star/awt/XKeyListener.hpp"
#include "com/sun/star/awt/XMouseListener.hpp"
#include "com/sun/star/awt/XMouseMotionListener.hpp"
#include "com/sun/star/awt/XPaintListener.hpp"
#include "com/sun/star/awt/XWindowListener.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XWindow const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XWindow" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XWindow > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XWindow > >::get();
}

::css::uno::Type const & ::css::awt::XWindow::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XWindow >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XWindow>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XWINDOW_HPP
