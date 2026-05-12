#ifndef INCLUDED_COM_SUN_STAR_UCB_XCONTENTEVENTLISTENER_HPP
#define INCLUDED_COM_SUN_STAR_UCB_XCONTENTEVENTLISTENER_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/XContentEventListener.hdl"

#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/ucb/ContentEvent.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::XContentEventListener const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ucb.XContentEventListener" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ucb::XContentEventListener > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ucb::XContentEventListener > >::get();
}

::css::uno::Type const & ::css::ucb::XContentEventListener::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ucb::XContentEventListener >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ucb::XContentEventListener>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UCB_XCONTENTEVENTLISTENER_HPP
