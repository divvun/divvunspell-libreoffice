#ifndef INCLUDED_COM_SUN_STAR_TASK_XPASSWORDCONTAINER2_HPP
#define INCLUDED_COM_SUN_STAR_TASK_XPASSWORDCONTAINER2_HPP

#include "sal/config.h"

#include "com/sun/star/task/XPasswordContainer2.hdl"

#include "com/sun/star/task/XMasterPasswordHandling2.hpp"
#include "com/sun/star/task/XPasswordContainer.hpp"
#include "com/sun/star/task/XUrlContainer.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace task {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::task::XPasswordContainer2 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.task.XPasswordContainer2" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::task::XPasswordContainer2 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::task::XPasswordContainer2 > >::get();
}

::css::uno::Type const & ::css::task::XPasswordContainer2::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::task::XPasswordContainer2 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::task::XPasswordContainer2>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TASK_XPASSWORDCONTAINER2_HPP
