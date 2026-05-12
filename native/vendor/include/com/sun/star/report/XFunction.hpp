#ifndef INCLUDED_COM_SUN_STAR_REPORT_XFUNCTION_HPP
#define INCLUDED_COM_SUN_STAR_REPORT_XFUNCTION_HPP

#include "sal/config.h"

#include "com/sun/star/report/XFunction.hdl"

#include "com/sun/star/beans/Optional.hpp"
#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/container/XChild.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace report {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::report::XFunction const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.report.XFunction" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::report::XFunction > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::report::XFunction > >::get();
}

::css::uno::Type const & ::css::report::XFunction::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::report::XFunction >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::report::XFunction>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_REPORT_XFUNCTION_HPP
