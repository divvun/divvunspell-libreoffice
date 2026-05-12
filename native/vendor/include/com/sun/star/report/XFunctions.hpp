#ifndef INCLUDED_COM_SUN_STAR_REPORT_XFUNCTIONS_HPP
#define INCLUDED_COM_SUN_STAR_REPORT_XFUNCTIONS_HPP

#include "sal/config.h"

#include "com/sun/star/report/XFunctions.hdl"

#include "com/sun/star/container/XChild.hpp"
#include "com/sun/star/container/XContainer.hpp"
#include "com/sun/star/container/XIndexContainer.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/report/XFunction.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace report {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::report::XFunctions const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.report.XFunctions" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::report::XFunctions > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::report::XFunctions > >::get();
}

::css::uno::Type const & ::css::report::XFunctions::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::report::XFunctions >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::report::XFunctions>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_REPORT_XFUNCTIONS_HPP
