#ifndef INCLUDED_COM_SUN_STAR_URI_XVNDSUNSTARSCRIPTURLREFERENCE_HPP
#define INCLUDED_COM_SUN_STAR_URI_XVNDSUNSTARSCRIPTURLREFERENCE_HPP

#include "sal/config.h"

#include "com/sun/star/uri/XVndSunStarScriptUrlReference.hdl"

#include "com/sun/star/uri/XUriReference.hpp"
#include "com/sun/star/uri/XVndSunStarScriptUrl.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace uri {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::uri::XVndSunStarScriptUrlReference const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.uri.XVndSunStarScriptUrlReference" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::uri::XVndSunStarScriptUrlReference > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::uri::XVndSunStarScriptUrlReference > >::get();
}

::css::uno::Type const & ::css::uri::XVndSunStarScriptUrlReference::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::uri::XVndSunStarScriptUrlReference >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::uri::XVndSunStarScriptUrlReference>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_URI_XVNDSUNSTARSCRIPTURLREFERENCE_HPP
