#ifndef INCLUDED_OOO_VBA_MSFORMS_XUSERFORM_HPP
#define INCLUDED_OOO_VBA_MSFORMS_XUSERFORM_HPP

#include "sal/config.h"

#include "ooo/vba/msforms/XUserForm.hdl"

#include "com/sun/star/script/XInvocation.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace ooo { namespace vba { namespace msforms {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::msforms::XUserForm const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "ooo.vba.msforms.XUserForm" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::ooo::vba::msforms::XUserForm > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::ooo::vba::msforms::XUserForm > >::get();
}

::css::uno::Type const & ::ooo::vba::msforms::XUserForm::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::ooo::vba::msforms::XUserForm >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::ooo::vba::msforms::XUserForm>: ::std::true_type {};
}
#endif

#endif // INCLUDED_OOO_VBA_MSFORMS_XUSERFORM_HPP
