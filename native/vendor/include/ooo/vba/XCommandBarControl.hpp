#ifndef INCLUDED_OOO_VBA_XCOMMANDBARCONTROL_HPP
#define INCLUDED_OOO_VBA_XCOMMANDBARCONTROL_HPP

#include "sal/config.h"

#include "ooo/vba/XCommandBarControl.hdl"

#include "ooo/vba/XHelperInterface.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace ooo { namespace vba {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::XCommandBarControl const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "ooo.vba.XCommandBarControl" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::ooo::vba::XCommandBarControl > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::ooo::vba::XCommandBarControl > >::get();
}

::css::uno::Type const & ::ooo::vba::XCommandBarControl::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::ooo::vba::XCommandBarControl >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::ooo::vba::XCommandBarControl>: ::std::true_type {};
}
#endif

#endif // INCLUDED_OOO_VBA_XCOMMANDBARCONTROL_HPP
