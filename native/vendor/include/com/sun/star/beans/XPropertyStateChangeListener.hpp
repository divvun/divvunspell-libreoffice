#ifndef INCLUDED_COM_SUN_STAR_BEANS_XPROPERTYSTATECHANGELISTENER_HPP
#define INCLUDED_COM_SUN_STAR_BEANS_XPROPERTYSTATECHANGELISTENER_HPP

#include "sal/config.h"

#include "com/sun/star/beans/XPropertyStateChangeListener.hdl"

#include "com/sun/star/beans/PropertyStateChangeEvent.hpp"
#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace beans {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::beans::XPropertyStateChangeListener const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.beans.XPropertyStateChangeListener" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::beans::XPropertyStateChangeListener > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::beans::XPropertyStateChangeListener > >::get();
}

::css::uno::Type const & ::css::beans::XPropertyStateChangeListener::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::beans::XPropertyStateChangeListener >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::beans::XPropertyStateChangeListener>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_BEANS_XPROPERTYSTATECHANGELISTENER_HPP
