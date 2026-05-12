#ifndef INCLUDED_COM_SUN_STAR_UI_XUICONFIGURATIONMANAGER2_HPP
#define INCLUDED_COM_SUN_STAR_UI_XUICONFIGURATIONMANAGER2_HPP

#include "sal/config.h"

#include "com/sun/star/ui/XUIConfigurationManager2.hdl"

#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/ui/XAcceleratorConfiguration.hpp"
#include "com/sun/star/ui/XUIConfiguration.hpp"
#include "com/sun/star/ui/XUIConfigurationManager.hpp"
#include "com/sun/star/ui/XUIConfigurationPersistence.hpp"
#include "com/sun/star/ui/XUIConfigurationStorage.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ui {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ui::XUIConfigurationManager2 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ui.XUIConfigurationManager2" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ui::XUIConfigurationManager2 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ui::XUIConfigurationManager2 > >::get();
}

::css::uno::Type const & ::css::ui::XUIConfigurationManager2::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ui::XUIConfigurationManager2 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ui::XUIConfigurationManager2>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UI_XUICONFIGURATIONMANAGER2_HPP
