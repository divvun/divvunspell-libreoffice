#ifndef INCLUDED_COM_SUN_STAR_XML_SAX_XLOCATOR_HPP
#define INCLUDED_COM_SUN_STAR_XML_SAX_XLOCATOR_HPP

#include "sal/config.h"

#include "com/sun/star/xml/sax/XLocator.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace xml { namespace sax {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xml::sax::XLocator const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.xml.sax.XLocator" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::xml::sax::XLocator > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::xml::sax::XLocator > >::get();
}

::css::uno::Type const & ::css::xml::sax::XLocator::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::xml::sax::XLocator >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::xml::sax::XLocator>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_XML_SAX_XLOCATOR_HPP
