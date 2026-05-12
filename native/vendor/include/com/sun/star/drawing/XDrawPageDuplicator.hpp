#ifndef INCLUDED_COM_SUN_STAR_DRAWING_XDRAWPAGEDUPLICATOR_HPP
#define INCLUDED_COM_SUN_STAR_DRAWING_XDRAWPAGEDUPLICATOR_HPP

#include "sal/config.h"

#include "com/sun/star/drawing/XDrawPageDuplicator.hdl"

#include "com/sun/star/drawing/XDrawPage.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace drawing {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::drawing::XDrawPageDuplicator const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.drawing.XDrawPageDuplicator" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::drawing::XDrawPageDuplicator > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::drawing::XDrawPageDuplicator > >::get();
}

::css::uno::Type const & ::css::drawing::XDrawPageDuplicator::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::drawing::XDrawPageDuplicator >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::drawing::XDrawPageDuplicator>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DRAWING_XDRAWPAGEDUPLICATOR_HPP
