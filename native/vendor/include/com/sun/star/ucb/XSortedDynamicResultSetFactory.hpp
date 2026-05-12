#ifndef INCLUDED_COM_SUN_STAR_UCB_XSORTEDDYNAMICRESULTSETFACTORY_HPP
#define INCLUDED_COM_SUN_STAR_UCB_XSORTEDDYNAMICRESULTSETFACTORY_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/XSortedDynamicResultSetFactory.hdl"

#include "com/sun/star/ucb/NumberedSortingInfo.hpp"
#include "com/sun/star/ucb/XAnyCompareFactory.hpp"
#include "com/sun/star/ucb/XDynamicResultSet.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::XSortedDynamicResultSetFactory const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ucb.XSortedDynamicResultSetFactory" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ucb::XSortedDynamicResultSetFactory > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ucb::XSortedDynamicResultSetFactory > >::get();
}

::css::uno::Type const & ::css::ucb::XSortedDynamicResultSetFactory::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ucb::XSortedDynamicResultSetFactory >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ucb::XSortedDynamicResultSetFactory>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UCB_XSORTEDDYNAMICRESULTSETFACTORY_HPP
