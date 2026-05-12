#ifndef INCLUDED_COM_SUN_STAR_REGISTRY_XIMPLEMENTATIONREGISTRATION2_HPP
#define INCLUDED_COM_SUN_STAR_REGISTRY_XIMPLEMENTATIONREGISTRATION2_HPP

#include "sal/config.h"

#include "com/sun/star/registry/XImplementationRegistration2.hdl"

#include "com/sun/star/registry/XImplementationRegistration.hpp"
#include "com/sun/star/registry/XSimpleRegistry.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace registry {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::registry::XImplementationRegistration2 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.registry.XImplementationRegistration2" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::registry::XImplementationRegistration2 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::registry::XImplementationRegistration2 > >::get();
}

::css::uno::Type const & ::css::registry::XImplementationRegistration2::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::registry::XImplementationRegistration2 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::registry::XImplementationRegistration2>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_REGISTRY_XIMPLEMENTATIONREGISTRATION2_HPP
