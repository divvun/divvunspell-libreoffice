#ifndef INCLUDED_COM_SUN_STAR_DATATRANSFER_CLIPBOARD_XSYSTEMCLIPBOARD_HPP
#define INCLUDED_COM_SUN_STAR_DATATRANSFER_CLIPBOARD_XSYSTEMCLIPBOARD_HPP

#include "sal/config.h"

#include "com/sun/star/datatransfer/clipboard/XSystemClipboard.hdl"

#include "com/sun/star/datatransfer/clipboard/XClipboardEx.hpp"
#include "com/sun/star/datatransfer/clipboard/XClipboardNotifier.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace datatransfer { namespace clipboard {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::datatransfer::clipboard::XSystemClipboard const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.datatransfer.clipboard.XSystemClipboard" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::datatransfer::clipboard::XSystemClipboard > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::datatransfer::clipboard::XSystemClipboard > >::get();
}

::css::uno::Type const & ::css::datatransfer::clipboard::XSystemClipboard::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::datatransfer::clipboard::XSystemClipboard >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::datatransfer::clipboard::XSystemClipboard>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DATATRANSFER_CLIPBOARD_XSYSTEMCLIPBOARD_HPP
