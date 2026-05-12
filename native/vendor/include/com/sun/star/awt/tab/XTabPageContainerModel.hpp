#ifndef INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGECONTAINERMODEL_HPP
#define INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGECONTAINERMODEL_HPP

#include "sal/config.h"

#include "com/sun/star/awt/tab/XTabPageContainerModel.hdl"

#include "com/sun/star/awt/tab/XTabPageModel.hpp"
#include "com/sun/star/container/XContainer.hpp"
#include "com/sun/star/container/XIndexContainer.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt { namespace tab {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::tab::XTabPageContainerModel const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.awt.tab.XTabPageContainerModel" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::tab::XTabPageContainerModel > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::tab::XTabPageContainerModel > >::get();
}

::css::uno::Type const & ::css::awt::tab::XTabPageContainerModel::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::tab::XTabPageContainerModel >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::tab::XTabPageContainerModel>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_TAB_XTABPAGECONTAINERMODEL_HPP
