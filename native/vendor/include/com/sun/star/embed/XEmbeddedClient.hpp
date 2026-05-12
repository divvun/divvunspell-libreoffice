#ifndef INCLUDED_COM_SUN_STAR_EMBED_XEMBEDDEDCLIENT_HPP
#define INCLUDED_COM_SUN_STAR_EMBED_XEMBEDDEDCLIENT_HPP

#include "sal/config.h"

#include "com/sun/star/embed/XEmbeddedClient.hdl"

#include "com/sun/star/embed/XComponentSupplier.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace embed {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::embed::XEmbeddedClient const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.embed.XEmbeddedClient" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::embed::XEmbeddedClient > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::embed::XEmbeddedClient > >::get();
}

::css::uno::Type const & ::css::embed::XEmbeddedClient::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::embed::XEmbeddedClient >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::embed::XEmbeddedClient>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_EMBED_XEMBEDDEDCLIENT_HPP
