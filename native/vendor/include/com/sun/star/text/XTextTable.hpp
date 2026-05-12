#ifndef INCLUDED_COM_SUN_STAR_TEXT_XTEXTTABLE_HPP
#define INCLUDED_COM_SUN_STAR_TEXT_XTEXTTABLE_HPP

#include "sal/config.h"

#include "com/sun/star/text/XTextTable.hdl"

#include "com/sun/star/table/XCell.hpp"
#include "com/sun/star/table/XTableColumns.hpp"
#include "com/sun/star/table/XTableRows.hpp"
#include "com/sun/star/text/XTextContent.hpp"
#include "com/sun/star/text/XTextTableCursor.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace text {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::text::XTextTable const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.text.XTextTable" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::text::XTextTable > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::text::XTextTable > >::get();
}

::css::uno::Type const & ::css::text::XTextTable::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::text::XTextTable >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::text::XTextTable>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TEXT_XTEXTTABLE_HPP
