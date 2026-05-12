#ifndef INCLUDED_COM_SUN_STAR_SHEET_XSCENARIOS_HPP
#define INCLUDED_COM_SUN_STAR_SHEET_XSCENARIOS_HPP

#include "sal/config.h"

#include "com/sun/star/sheet/XScenarios.hdl"

#include "com/sun/star/container/XNameAccess.hpp"
#include "com/sun/star/table/CellRangeAddress.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace sheet {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sheet::XScenarios const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sheet.XScenarios" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sheet::XScenarios > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sheet::XScenarios > >::get();
}

::css::uno::Type const & ::css::sheet::XScenarios::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sheet::XScenarios >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sheet::XScenarios>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SHEET_XSCENARIOS_HPP
