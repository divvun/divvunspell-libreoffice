#ifndef INCLUDED_OOO_VBA_EXCEL_XWINDOW_HPP
#define INCLUDED_OOO_VBA_EXCEL_XWINDOW_HPP

#include "sal/config.h"

#include "ooo/vba/excel/XWindow.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "ooo/vba/excel/XPane.hpp"
#include "ooo/vba/excel/XRange.hpp"
#include "ooo/vba/excel/XWorksheet.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace ooo { namespace vba { namespace excel {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::excel::XWindow const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "ooo.vba.excel.XWindow" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::ooo::vba::excel::XWindow > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::ooo::vba::excel::XWindow > >::get();
}

::css::uno::Type const & ::ooo::vba::excel::XWindow::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::ooo::vba::excel::XWindow >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::ooo::vba::excel::XWindow>: ::std::true_type {};
}
#endif

#endif // INCLUDED_OOO_VBA_EXCEL_XWINDOW_HPP
