#ifndef INCLUDED_COM_SUN_STAR_AWT_XUNOCONTROLDIALOG_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XUNOCONTROLDIALOG_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XUnoControlDialog.hdl"

#include "com/sun/star/awt/XControl.hpp"
#include "com/sun/star/awt/XControlContainer.hpp"
#include "com/sun/star/awt/XDialog2.hpp"
#include "com/sun/star/awt/XTopWindow.hpp"
#include "com/sun/star/awt/XWindow.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XUnoControlDialog const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XUnoControlDialog" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XUnoControlDialog > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XUnoControlDialog > >::get();
}

::css::uno::Type const & ::css::awt::XUnoControlDialog::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XUnoControlDialog >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XUnoControlDialog>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XUNOCONTROLDIALOG_HPP
