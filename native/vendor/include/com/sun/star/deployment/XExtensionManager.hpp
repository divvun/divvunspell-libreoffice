#ifndef INCLUDED_COM_SUN_STAR_DEPLOYMENT_XEXTENSIONMANAGER_HPP
#define INCLUDED_COM_SUN_STAR_DEPLOYMENT_XEXTENSIONMANAGER_HPP

#include "sal/config.h"

#include "com/sun/star/deployment/XExtensionManager.hdl"

#include "com/sun/star/beans/NamedValue.hpp"
#include "com/sun/star/deployment/XPackage.hpp"
#include "com/sun/star/deployment/XPackageTypeInfo.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/task/XAbortChannel.hpp"
#include "com/sun/star/ucb/XCommandEnvironment.hpp"
#include "com/sun/star/util/XModifyBroadcaster.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace deployment {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::deployment::XExtensionManager const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.deployment.XExtensionManager" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::deployment::XExtensionManager > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::deployment::XExtensionManager > >::get();
}

::css::uno::Type const & ::css::deployment::XExtensionManager::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::deployment::XExtensionManager >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::deployment::XExtensionManager>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DEPLOYMENT_XEXTENSIONMANAGER_HPP
