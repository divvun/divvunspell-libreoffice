#ifndef INCLUDED_COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP
#define INCLUDED_COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP

#include "sal/config.h"

#include "com/sun/star/container/XIndexContainer.hdl"

#include "com/sun/star/container/XIndexReplace.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace container {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::container::XIndexContainer const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.container.XIndexContainer" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::container::XIndexContainer > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::container::XIndexContainer > >::get();
}

::css::uno::Type const & ::css::container::XIndexContainer::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::container::XIndexContainer >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::container::XIndexContainer>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP
