#ifndef INCLUDED_COM_SUN_STAR_FRAME_XTASKSSUPPLIER_HPP
#define INCLUDED_COM_SUN_STAR_FRAME_XTASKSSUPPLIER_HPP

#include "sal/config.h"

#include "com/sun/star/frame/XTasksSupplier.hdl"

#include "com/sun/star/container/XEnumerationAccess.hpp"
#include "com/sun/star/frame/XTask.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace frame {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::frame::XTasksSupplier const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.frame.XTasksSupplier" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::frame::XTasksSupplier > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::frame::XTasksSupplier > >::get();
}

::css::uno::Type const & ::css::frame::XTasksSupplier::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::frame::XTasksSupplier >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::frame::XTasksSupplier>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_FRAME_XTASKSSUPPLIER_HPP
