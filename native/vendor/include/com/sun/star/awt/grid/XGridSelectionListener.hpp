#ifndef INCLUDED_COM_SUN_STAR_AWT_GRID_XGRIDSELECTIONLISTENER_HPP
#define INCLUDED_COM_SUN_STAR_AWT_GRID_XGRIDSELECTIONLISTENER_HPP

#include "sal/config.h"

#include "com/sun/star/awt/grid/XGridSelectionListener.hdl"

#include "com/sun/star/awt/grid/GridSelectionEvent.hpp"
#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt { namespace grid {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::grid::XGridSelectionListener const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.grid.XGridSelectionListener" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::grid::XGridSelectionListener > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::grid::XGridSelectionListener > >::get();
}

::css::uno::Type const & ::css::awt::grid::XGridSelectionListener::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::grid::XGridSelectionListener >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::grid::XGridSelectionListener>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_GRID_XGRIDSELECTIONLISTENER_HPP
