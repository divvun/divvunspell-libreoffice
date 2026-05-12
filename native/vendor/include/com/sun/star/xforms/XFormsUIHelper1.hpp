#ifndef INCLUDED_COM_SUN_STAR_XFORMS_XFORMSUIHELPER1_HPP
#define INCLUDED_COM_SUN_STAR_XFORMS_XFORMSUIHELPER1_HPP

#include "sal/config.h"

#include "com/sun/star/xforms/XFormsUIHelper1.hdl"

#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/frame/XModel.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/xforms/XModel.hpp"
#include "com/sun/star/xml/dom/XDocument.hpp"
#include "com/sun/star/xml/dom/XNode.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace xforms {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xforms::XFormsUIHelper1 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.xforms.XFormsUIHelper1" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::xforms::XFormsUIHelper1 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::xforms::XFormsUIHelper1 > >::get();
}

::css::uno::Type const & ::css::xforms::XFormsUIHelper1::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::xforms::XFormsUIHelper1 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::xforms::XFormsUIHelper1>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_XFORMS_XFORMSUIHELPER1_HPP
