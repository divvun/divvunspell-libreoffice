#ifndef INCLUDED_COM_SUN_STAR_RDF_XREIFIEDSTATEMENT_HPP
#define INCLUDED_COM_SUN_STAR_RDF_XREIFIEDSTATEMENT_HPP

#include "sal/config.h"

#include "com/sun/star/rdf/XReifiedStatement.hdl"

#include "com/sun/star/rdf/Statement.hpp"
#include "com/sun/star/rdf/XResource.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace rdf {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::rdf::XReifiedStatement const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.rdf.XReifiedStatement" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::rdf::XReifiedStatement > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::rdf::XReifiedStatement > >::get();
}

::css::uno::Type const & ::css::rdf::XReifiedStatement::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::rdf::XReifiedStatement >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::rdf::XReifiedStatement>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_RDF_XREIFIEDSTATEMENT_HPP
