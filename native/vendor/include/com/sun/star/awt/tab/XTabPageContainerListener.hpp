#ifndef INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGECONTAINERLISTENER_HPP
#define INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGECONTAINERLISTENER_HPP

#include "sal/config.h"

#include "com/sun/star/awt/tab/XTabPageContainerListener.hdl"

#include "com/sun/star/awt/tab/TabPageActivatedEvent.hpp"
#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt { namespace tab {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::tab::XTabPageContainerListener const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.tab.XTabPageContainerListener" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::tab::XTabPageContainerListener > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::tab::XTabPageContainerListener > >::get();
}

::css::uno::Type const & ::css::awt::tab::XTabPageContainerListener::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::tab::XTabPageContainerListener >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::tab::XTabPageContainerListener>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGECONTAINERLISTENER_HPP
