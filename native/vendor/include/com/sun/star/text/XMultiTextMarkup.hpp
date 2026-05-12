#ifndef INCLUDED_COM_SUN_STAR_TEXT_XMULTITEXTMARKUP_HPP
#define INCLUDED_COM_SUN_STAR_TEXT_XMULTITEXTMARKUP_HPP

#include "sal/config.h"

#include "com/sun/star/text/XMultiTextMarkup.hdl"

#include "com/sun/star/text/TextMarkupDescriptor.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace text {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::text::XMultiTextMarkup const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.text.XMultiTextMarkup" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::text::XMultiTextMarkup > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::text::XMultiTextMarkup > >::get();
}

::css::uno::Type const & ::css::text::XMultiTextMarkup::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::text::XMultiTextMarkup >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::text::XMultiTextMarkup>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TEXT_XMULTITEXTMARKUP_HPP
