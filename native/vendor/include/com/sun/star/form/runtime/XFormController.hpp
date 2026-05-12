#ifndef INCLUDED_COM_SUN_STAR_FORM_RUNTIME_XFORMCONTROLLER_HPP
#define INCLUDED_COM_SUN_STAR_FORM_RUNTIME_XFORMCONTROLLER_HPP

#include "sal/config.h"

#include "com/sun/star/form/runtime/XFormController.hdl"

#include "com/sun/star/awt/XControl.hpp"
#include "com/sun/star/awt/XTabController.hpp"
#include "com/sun/star/container/XChild.hpp"
#include "com/sun/star/container/XEnumerationAccess.hpp"
#include "com/sun/star/container/XIndexAccess.hpp"
#include "com/sun/star/form/XConfirmDeleteBroadcaster.hpp"
#include "com/sun/star/form/XDatabaseParameterBroadcaster2.hpp"
#include "com/sun/star/form/XFormControllerListener.hpp"
#include "com/sun/star/form/runtime/XFormControllerContext.hpp"
#include "com/sun/star/form/runtime/XFormOperations.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/sdb/XRowSetApproveBroadcaster.hpp"
#include "com/sun/star/sdb/XSQLErrorBroadcaster.hpp"
#include "com/sun/star/task/XInteractionHandler.hpp"
#include "com/sun/star/util/XModeSelector.hpp"
#include "com/sun/star/util/XModifyBroadcaster.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace form { namespace runtime {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::form::runtime::XFormController const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.form.runtime.XFormController" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::form::runtime::XFormController > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::form::runtime::XFormController > >::get();
}

::css::uno::Type const & ::css::form::runtime::XFormController::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::form::runtime::XFormController >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::form::runtime::XFormController>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_FORM_RUNTIME_XFORMCONTROLLER_HPP
