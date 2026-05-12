#ifndef INCLUDED_COM_SUN_STAR_AWT_XEXTENDEDTOOLKIT_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XEXTENDEDTOOLKIT_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XExtendedToolkit.hdl"

#include "com/sun/star/awt/XFocusListener.hpp"
#include "com/sun/star/awt/XKeyHandler.hpp"
#include "com/sun/star/awt/XTopWindow.hpp"
#include "com/sun/star/awt/XTopWindowListener.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XExtendedToolkit const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XExtendedToolkit" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XExtendedToolkit > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XExtendedToolkit > >::get();
}

::css::uno::Type const & ::css::awt::XExtendedToolkit::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XExtendedToolkit >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XExtendedToolkit>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XEXTENDEDTOOLKIT_HPP
