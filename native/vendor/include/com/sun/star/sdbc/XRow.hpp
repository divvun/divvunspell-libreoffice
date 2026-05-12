#ifndef INCLUDED_COM_SUN_STAR_SDBC_XROW_HPP
#define INCLUDED_COM_SUN_STAR_SDBC_XROW_HPP

#include "sal/config.h"

#include "com/sun/star/sdbc/XRow.hdl"

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

namespace com { namespace sun { namespace star { namespace sdbc {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdbc::XRow const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sdbc.XRow" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sdbc::XRow > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sdbc::XRow > >::get();
}

::css::uno::Type const & ::css::sdbc::XRow::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sdbc::XRow >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sdbc::XRow>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SDBC_XROW_HPP
