#ifndef INCLUDED_OOO_VBA_XCONTROLPROVIDER_HPP
#define INCLUDED_OOO_VBA_XCONTROLPROVIDER_HPP

#include "sal/config.h"

#include "ooo/vba/XControlProvider.hdl"

#include "com/sun/star/drawing/XControlShape.hpp"
#include "com/sun/star/frame/XModel.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "ooo/vba/msforms/XControl.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace ooo { namespace vba {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::XControlProvider const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "ooo.vba.XControlProvider" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::ooo::vba::XControlProvider > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::ooo::vba::XControlProvider > >::get();
}

::css::uno::Type const & ::ooo::vba::XControlProvider::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::ooo::vba::XControlProvider >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::ooo::vba::XControlProvider>: ::std::true_type {};
}
#endif

#endif // INCLUDED_OOO_VBA_XCONTROLPROVIDER_HPP
