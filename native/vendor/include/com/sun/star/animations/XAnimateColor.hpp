#ifndef INCLUDED_COM_SUN_STAR_ANIMATIONS_XANIMATECOLOR_HPP
#define INCLUDED_COM_SUN_STAR_ANIMATIONS_XANIMATECOLOR_HPP

#include "sal/config.h"

#include "com/sun/star/animations/XAnimateColor.hdl"

#include "com/sun/star/animations/XAnimate.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace animations {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::animations::XAnimateColor const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.animations.XAnimateColor" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::animations::XAnimateColor > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::animations::XAnimateColor > >::get();
}

::css::uno::Type const & ::css::animations::XAnimateColor::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::animations::XAnimateColor >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::animations::XAnimateColor>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_ANIMATIONS_XANIMATECOLOR_HPP
