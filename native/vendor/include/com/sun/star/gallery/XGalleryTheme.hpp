#ifndef INCLUDED_COM_SUN_STAR_GALLERY_XGALLERYTHEME_HPP
#define INCLUDED_COM_SUN_STAR_GALLERY_XGALLERYTHEME_HPP

#include "sal/config.h"

#include "com/sun/star/gallery/XGalleryTheme.hdl"

#include "com/sun/star/container/XIndexAccess.hpp"
#include "com/sun/star/graphic/XGraphic.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace gallery {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::gallery::XGalleryTheme const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.gallery.XGalleryTheme" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::gallery::XGalleryTheme > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::gallery::XGalleryTheme > >::get();
}

::css::uno::Type const & ::css::gallery::XGalleryTheme::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::gallery::XGalleryTheme >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::gallery::XGalleryTheme>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_GALLERY_XGALLERYTHEME_HPP
