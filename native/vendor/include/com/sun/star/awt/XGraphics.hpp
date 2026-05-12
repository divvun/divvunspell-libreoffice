#ifndef INCLUDED_COM_SUN_STAR_AWT_XGRAPHICS_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XGRAPHICS_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XGraphics.hdl"

#include "com/sun/star/awt/FontDescriptor.hpp"
#include "com/sun/star/awt/Gradient.hpp"
#include "com/sun/star/awt/RasterOperation.hpp"
#include "com/sun/star/awt/SimpleFontMetric.hpp"
#include "com/sun/star/awt/XDevice.hpp"
#include "com/sun/star/awt/XDisplayBitmap.hpp"
#include "com/sun/star/awt/XFont.hpp"
#include "com/sun/star/awt/XRegion.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/util/Color.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XGraphics const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XGraphics" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XGraphics > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XGraphics > >::get();
}

::css::uno::Type const & ::css::awt::XGraphics::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XGraphics >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XGraphics>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XGRAPHICS_HPP
