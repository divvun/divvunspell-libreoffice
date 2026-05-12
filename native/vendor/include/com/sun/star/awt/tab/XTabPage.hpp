#ifndef INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGE_HPP
#define INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGE_HPP

#include "sal/config.h"

#include "com/sun/star/awt/tab/XTabPage.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt { namespace tab {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::tab::XTabPage const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.tab.XTabPage" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::tab::XTabPage > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::tab::XTabPage > >::get();
}

::css::uno::Type const & ::css::awt::tab::XTabPage::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::tab::XTabPage >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::tab::XTabPage>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGE_HPP
