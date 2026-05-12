#ifndef INCLUDED_COM_SUN_STAR_REFLECTION_XDUMP_HPP
#define INCLUDED_COM_SUN_STAR_REFLECTION_XDUMP_HPP

#include "sal/config.h"

#include "com/sun/star/reflection/XDump.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace reflection {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::reflection::XDump const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.reflection.XDump" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::reflection::XDump > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::reflection::XDump > >::get();
}

::css::uno::Type const & ::css::reflection::XDump::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::reflection::XDump >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::reflection::XDump>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_REFLECTION_XDUMP_HPP
