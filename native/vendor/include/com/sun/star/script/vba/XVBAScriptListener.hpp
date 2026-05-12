#ifndef INCLUDED_COM_SUN_STAR_SCRIPT_VBA_XVBASCRIPTLISTENER_HPP
#define INCLUDED_COM_SUN_STAR_SCRIPT_VBA_XVBASCRIPTLISTENER_HPP

#include "sal/config.h"

#include "com/sun/star/script/vba/XVBAScriptListener.hdl"

#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/script/vba/VBAScriptEvent.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace script { namespace vba {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::script::vba::XVBAScriptListener const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.script.vba.XVBAScriptListener" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::script::vba::XVBAScriptListener > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::script::vba::XVBAScriptListener > >::get();
}

::css::uno::Type const & ::css::script::vba::XVBAScriptListener::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::script::vba::XVBAScriptListener >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::script::vba::XVBAScriptListener>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SCRIPT_VBA_XVBASCRIPTLISTENER_HPP
