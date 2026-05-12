#ifndef INCLUDED_COM_SUN_STAR_UTIL_XIMPORTABLE_HPP
#define INCLUDED_COM_SUN_STAR_UTIL_XIMPORTABLE_HPP

#include "sal/config.h"

#include "com/sun/star/util/XImportable.hdl"

#include "com/sun/star/beans/PropertyValue.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace util {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::util::XImportable const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.util.XImportable" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::util::XImportable > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::util::XImportable > >::get();
}

::css::uno::Type const & ::css::util::XImportable::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::util::XImportable >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::util::XImportable>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UTIL_XIMPORTABLE_HPP
