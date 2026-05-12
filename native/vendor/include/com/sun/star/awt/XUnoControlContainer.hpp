#ifndef INCLUDED_COM_SUN_STAR_AWT_XUNOCONTROLCONTAINER_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XUNOCONTROLCONTAINER_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XUnoControlContainer.hdl"

#include "com/sun/star/awt/XTabController.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XUnoControlContainer const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.XUnoControlContainer" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XUnoControlContainer > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XUnoControlContainer > >::get();
}

::css::uno::Type const & ::css::awt::XUnoControlContainer::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XUnoControlContainer >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XUnoControlContainer>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XUNOCONTROLCONTAINER_HPP
