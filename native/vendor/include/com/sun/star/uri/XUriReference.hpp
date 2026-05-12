#ifndef INCLUDED_COM_SUN_STAR_URI_XURIREFERENCE_HPP
#define INCLUDED_COM_SUN_STAR_URI_XURIREFERENCE_HPP

#include "sal/config.h"

#include "com/sun/star/uri/XUriReference.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace uri {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::uri::XUriReference const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.uri.XUriReference" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::uri::XUriReference > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::uri::XUriReference > >::get();
}

::css::uno::Type const & ::css::uri::XUriReference::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::uri::XUriReference >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::uri::XUriReference>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_URI_XURIREFERENCE_HPP
