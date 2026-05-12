#ifndef INCLUDED_COM_SUN_STAR_TABLE_XTABLE_HPP
#define INCLUDED_COM_SUN_STAR_TABLE_XTABLE_HPP

#include "sal/config.h"

#include "com/sun/star/table/XTable.hdl"

#include "com/sun/star/beans/XFastPropertySet.hpp"
#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/table/XCellCursor.hpp"
#include "com/sun/star/table/XCellRange.hpp"
#include "com/sun/star/table/XColumnRowRange.hpp"
#include "com/sun/star/util/XModifiable.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace table {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::table::XTable const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.table.XTable" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::table::XTable > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::table::XTable > >::get();
}

::css::uno::Type const & ::css::table::XTable::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::table::XTable >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::table::XTable>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TABLE_XTABLE_HPP
