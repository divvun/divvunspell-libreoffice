#ifndef INCLUDED_COM_SUN_STAR_AWT_XTOOLKIT3_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XTOOLKIT3_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XToolkit3.hdl"

#include "com/sun/star/awt/XFontMappingUse.hpp"
#include "com/sun/star/awt/XToolkit2.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XToolkit3 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XToolkit3" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XToolkit3 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XToolkit3 > >::get();
}

::css::uno::Type const & ::css::awt::XToolkit3::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XToolkit3 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XToolkit3>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XTOOLKIT3_HPP
