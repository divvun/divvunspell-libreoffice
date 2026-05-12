#ifndef INCLUDED_COM_SUN_STAR_TEXT_XTEXT_HPP
#define INCLUDED_COM_SUN_STAR_TEXT_XTEXT_HPP

#include "sal/config.h"

#include "com/sun/star/text/XText.hdl"

#include "com/sun/star/text/XSimpleText.hpp"
#include "com/sun/star/text/XTextContent.hpp"
#include "com/sun/star/text/XTextRange.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace text {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::text::XText const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.text.XText" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::text::XText > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::text::XText > >::get();
}

::css::uno::Type const & ::css::text::XText::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::text::XText >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::text::XText>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TEXT_XTEXT_HPP
