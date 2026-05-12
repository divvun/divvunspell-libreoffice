#ifndef INCLUDED_COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP
#define INCLUDED_COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP

#include "sal/config.h"

#include "com/sun/star/form/XFormComponent.hdl"

#include "com/sun/star/container/XChild.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace form {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::form::XFormComponent const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.form.XFormComponent" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::form::XFormComponent > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::form::XFormComponent > >::get();
}

::css::uno::Type const & ::css::form::XFormComponent::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::form::XFormComponent >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::form::XFormComponent>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_FORM_XFORMCOMPONENT_HPP
