#ifndef INCLUDED_COM_SUN_STAR_AWT_XDISPLAYCONNECTION_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XDISPLAYCONNECTION_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XDisplayConnection.hdl"

#include "com/sun/star/awt/XEventHandler.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XDisplayConnection const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XDisplayConnection" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XDisplayConnection > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XDisplayConnection > >::get();
}

::css::uno::Type const & ::css::awt::XDisplayConnection::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XDisplayConnection >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XDisplayConnection>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XDISPLAYCONNECTION_HPP
