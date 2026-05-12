#ifndef INCLUDED_COM_SUN_STAR_OFFICE_XANNOTATION_HPP
#define INCLUDED_COM_SUN_STAR_OFFICE_XANNOTATION_HPP

#include "sal/config.h"

#include "com/sun/star/office/XAnnotation.hdl"

#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/geometry/RealPoint2D.hpp"
#include "com/sun/star/geometry/RealSize2D.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/text/XText.hpp"
#include "com/sun/star/util/DateTime.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace office {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::office::XAnnotation const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.office.XAnnotation" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::office::XAnnotation > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::office::XAnnotation > >::get();
}

::css::uno::Type const & ::css::office::XAnnotation::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::office::XAnnotation >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::office::XAnnotation>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_OFFICE_XANNOTATION_HPP
