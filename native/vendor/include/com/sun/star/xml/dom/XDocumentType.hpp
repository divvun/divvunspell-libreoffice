#ifndef INCLUDED_COM_SUN_STAR_XML_DOM_XDOCUMENTTYPE_HPP
#define INCLUDED_COM_SUN_STAR_XML_DOM_XDOCUMENTTYPE_HPP

#include "sal/config.h"

#include "com/sun/star/xml/dom/XDocumentType.hdl"

#include "com/sun/star/xml/dom/XNamedNodeMap.hpp"
#include "com/sun/star/xml/dom/XNode.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace xml { namespace dom {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xml::dom::XDocumentType const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.xml.dom.XDocumentType" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::xml::dom::XDocumentType > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::xml::dom::XDocumentType > >::get();
}

::css::uno::Type const & ::css::xml::dom::XDocumentType::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::xml::dom::XDocumentType >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::xml::dom::XDocumentType>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_XML_DOM_XDOCUMENTTYPE_HPP
