#ifndef INCLUDED_COM_SUN_STAR_TEXT_XWORDCURSOR_HPP
#define INCLUDED_COM_SUN_STAR_TEXT_XWORDCURSOR_HPP

#include "sal/config.h"

#include "com/sun/star/text/XWordCursor.hdl"

#include "com/sun/star/text/XTextCursor.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace text {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::text::XWordCursor const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.text.XWordCursor" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::text::XWordCursor > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::text::XWordCursor > >::get();
}

::css::uno::Type const & ::css::text::XWordCursor::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::text::XWordCursor >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::text::XWordCursor>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TEXT_XWORDCURSOR_HPP
