#ifndef INCLUDED_COM_SUN_STAR_UTIL_XCHANGESNOTIFIER_HPP
#define INCLUDED_COM_SUN_STAR_UTIL_XCHANGESNOTIFIER_HPP

#include "sal/config.h"

#include "com/sun/star/util/XChangesNotifier.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/util/XChangesListener.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace util {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::util::XChangesNotifier const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.util.XChangesNotifier" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::util::XChangesNotifier > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::util::XChangesNotifier > >::get();
}

::css::uno::Type const & ::css::util::XChangesNotifier::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::util::XChangesNotifier >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::util::XChangesNotifier>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UTIL_XCHANGESNOTIFIER_HPP
