#ifndef INCLUDED_COM_SUN_STAR_CONTAINER_XIMPLICITIDACCESS_HPP
#define INCLUDED_COM_SUN_STAR_CONTAINER_XIMPLICITIDACCESS_HPP

#include "sal/config.h"

#include "com/sun/star/container/XImplicitIDAccess.hdl"

#include "com/sun/star/container/XElementAccess.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace container {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::container::XImplicitIDAccess const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.container.XImplicitIDAccess" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::container::XImplicitIDAccess > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::container::XImplicitIDAccess > >::get();
}

::css::uno::Type const & ::css::container::XImplicitIDAccess::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::container::XImplicitIDAccess >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::container::XImplicitIDAccess>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_CONTAINER_XIMPLICITIDACCESS_HPP
