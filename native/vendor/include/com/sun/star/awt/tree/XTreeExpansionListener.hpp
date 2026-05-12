#ifndef INCLUDED_COM_SUN_STAR_AWT_TREE_XTREEEXPANSIONLISTENER_HPP
#define INCLUDED_COM_SUN_STAR_AWT_TREE_XTREEEXPANSIONLISTENER_HPP

#include "sal/config.h"

#include "com/sun/star/awt/tree/XTreeExpansionListener.hdl"

#include "com/sun/star/awt/tree/TreeExpansionEvent.hpp"
#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt { namespace tree {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::tree::XTreeExpansionListener const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.tree.XTreeExpansionListener" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::tree::XTreeExpansionListener > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::tree::XTreeExpansionListener > >::get();
}

::css::uno::Type const & ::css::awt::tree::XTreeExpansionListener::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::tree::XTreeExpansionListener >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::tree::XTreeExpansionListener>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_TREE_XTREEEXPANSIONLISTENER_HPP
