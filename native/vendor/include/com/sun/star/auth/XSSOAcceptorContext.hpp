#ifndef INCLUDED_COM_SUN_STAR_AUTH_XSSOACCEPTORCONTEXT_HPP
#define INCLUDED_COM_SUN_STAR_AUTH_XSSOACCEPTORCONTEXT_HPP

#include "sal/config.h"

#include "com/sun/star/auth/XSSOAcceptorContext.hdl"

#include "com/sun/star/auth/XSSOContext.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace auth {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::auth::XSSOAcceptorContext const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.auth.XSSOAcceptorContext" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::auth::XSSOAcceptorContext > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::auth::XSSOAcceptorContext > >::get();
}

::css::uno::Type const & ::css::auth::XSSOAcceptorContext::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::auth::XSSOAcceptorContext >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::auth::XSSOAcceptorContext>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AUTH_XSSOACCEPTORCONTEXT_HPP
