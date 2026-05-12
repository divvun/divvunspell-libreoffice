#ifndef INCLUDED_COM_SUN_STAR_SDB_XCOLUMN_HPP
#define INCLUDED_COM_SUN_STAR_SDB_XCOLUMN_HPP

#include "sal/config.h"

#include "com/sun/star/sdb/XColumn.hdl"

#include "com/sun/star/container/XNameAccess.hpp"
#include "com/sun/star/io/XInputStream.hpp"
#include "com/sun/star/sdbc/XArray.hpp"
#include "com/sun/star/sdbc/XBlob.hpp"
#include "com/sun/star/sdbc/XClob.hpp"
#include "com/sun/star/sdbc/XRef.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/util/Date.hpp"
#include "com/sun/star/util/DateTime.hpp"
#include "com/sun/star/util/Time.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace sdb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdb::XColumn const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sdb.XColumn" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sdb::XColumn > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sdb::XColumn > >::get();
}

::css::uno::Type const & ::css::sdb::XColumn::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sdb::XColumn >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sdb::XColumn>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SDB_XCOLUMN_HPP
