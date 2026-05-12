#ifndef INCLUDED_COM_SUN_STAR_FRAME_XCONTROLLERBORDER_HPP
#define INCLUDED_COM_SUN_STAR_FRAME_XCONTROLLERBORDER_HPP

#include "sal/config.h"

#include "com/sun/star/frame/XControllerBorder.hdl"

#include "com/sun/star/awt/Rectangle.hpp"
#include "com/sun/star/frame/BorderWidths.hpp"
#include "com/sun/star/frame/XBorderResizeListener.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace frame {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::frame::XControllerBorder const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.frame.XControllerBorder" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::frame::XControllerBorder > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::frame::XControllerBorder > >::get();
}

::css::uno::Type const & ::css::frame::XControllerBorder::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::frame::XControllerBorder >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::frame::XControllerBorder>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_FRAME_XCONTROLLERBORDER_HPP
