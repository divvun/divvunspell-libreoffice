#ifndef INCLUDED_COM_SUN_STAR_SCRIPT_XINVOCATIONADAPTERFACTORY_HPP
#define INCLUDED_COM_SUN_STAR_SCRIPT_XINVOCATIONADAPTERFACTORY_HPP

#include "sal/config.h"

#include "com/sun/star/script/XInvocationAdapterFactory.hdl"

#include "com/sun/star/script/XInvocation.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace script {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::script::XInvocationAdapterFactory const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.script.XInvocationAdapterFactory" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::script::XInvocationAdapterFactory > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::script::XInvocationAdapterFactory > >::get();
}

::css::uno::Type const & ::css::script::XInvocationAdapterFactory::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::script::XInvocationAdapterFactory >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::script::XInvocationAdapterFactory>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SCRIPT_XINVOCATIONADAPTERFACTORY_HPP
