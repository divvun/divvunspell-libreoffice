#ifndef INCLUDED_COM_SUN_STAR_SCRIPT_PROVIDER_XSCRIPT_HPP
#define INCLUDED_COM_SUN_STAR_SCRIPT_PROVIDER_XSCRIPT_HPP

#include "sal/config.h"

#include "com/sun/star/script/provider/XScript.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace script { namespace provider {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::script::provider::XScript const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.script.provider.XScript" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::script::provider::XScript > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::script::provider::XScript > >::get();
}

::css::uno::Type const & ::css::script::provider::XScript::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::script::provider::XScript >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::script::provider::XScript>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SCRIPT_PROVIDER_XSCRIPT_HPP
