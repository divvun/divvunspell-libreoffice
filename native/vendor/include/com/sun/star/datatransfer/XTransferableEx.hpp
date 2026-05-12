#ifndef INCLUDED_COM_SUN_STAR_DATATRANSFER_XTRANSFERABLEEX_HPP
#define INCLUDED_COM_SUN_STAR_DATATRANSFER_XTRANSFERABLEEX_HPP

#include "sal/config.h"

#include "com/sun/star/datatransfer/XTransferableEx.hdl"

#include "com/sun/star/datatransfer/DataFlavor.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace datatransfer {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::datatransfer::XTransferableEx const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.datatransfer.XTransferableEx" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::datatransfer::XTransferableEx > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::datatransfer::XTransferableEx > >::get();
}

::css::uno::Type const & ::css::datatransfer::XTransferableEx::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::datatransfer::XTransferableEx >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::datatransfer::XTransferableEx>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DATATRANSFER_XTRANSFERABLEEX_HPP
