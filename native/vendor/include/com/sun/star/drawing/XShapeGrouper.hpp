#ifndef INCLUDED_COM_SUN_STAR_DRAWING_XSHAPEGROUPER_HPP
#define INCLUDED_COM_SUN_STAR_DRAWING_XSHAPEGROUPER_HPP

#include "sal/config.h"

#include "com/sun/star/drawing/XShapeGrouper.hdl"

#include "com/sun/star/drawing/XShapeGroup.hpp"
#include "com/sun/star/drawing/XShapes.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace drawing {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::drawing::XShapeGrouper const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.drawing.XShapeGrouper" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::drawing::XShapeGrouper > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::drawing::XShapeGrouper > >::get();
}

::css::uno::Type const & ::css::drawing::XShapeGrouper::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::drawing::XShapeGrouper >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::drawing::XShapeGrouper>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DRAWING_XSHAPEGROUPER_HPP
