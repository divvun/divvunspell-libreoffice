#ifndef INCLUDED_COM_SUN_STAR_UCB_XUNIVERSALCONTENTBROKER_HPP
#define INCLUDED_COM_SUN_STAR_UCB_XUNIVERSALCONTENTBROKER_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/XUniversalContentBroker.hdl"

#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/ucb/XCommandProcessor2.hpp"
#include "com/sun/star/ucb/XContentIdentifierFactory.hpp"
#include "com/sun/star/ucb/XContentProvider.hpp"
#include "com/sun/star/ucb/XContentProviderManager.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::XUniversalContentBroker const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ucb.XUniversalContentBroker" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ucb::XUniversalContentBroker > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ucb::XUniversalContentBroker > >::get();
}

::css::uno::Type const & ::css::ucb::XUniversalContentBroker::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ucb::XUniversalContentBroker >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ucb::XUniversalContentBroker>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UCB_XUNIVERSALCONTENTBROKER_HPP
