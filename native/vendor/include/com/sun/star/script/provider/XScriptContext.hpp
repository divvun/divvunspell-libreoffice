#ifndef INCLUDED_COM_SUN_STAR_SCRIPT_PROVIDER_XSCRIPTCONTEXT_HPP
#define INCLUDED_COM_SUN_STAR_SCRIPT_PROVIDER_XSCRIPTCONTEXT_HPP

#include "sal/config.h"

#include "com/sun/star/script/provider/XScriptContext.hdl"

#include "com/sun/star/document/XScriptInvocationContext.hpp"
#include "com/sun/star/frame/XDesktop.hpp"
#include "com/sun/star/frame/XModel.hpp"
#include "com/sun/star/uno/XComponentContext.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace script { namespace provider {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::script::provider::XScriptContext const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.script.provider.XScriptContext" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::script::provider::XScriptContext > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::script::provider::XScriptContext > >::get();
}

::css::uno::Type const & ::css::script::provider::XScriptContext::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::script::provider::XScriptContext >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::script::provider::XScriptContext>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SCRIPT_PROVIDER_XSCRIPTCONTEXT_HPP
