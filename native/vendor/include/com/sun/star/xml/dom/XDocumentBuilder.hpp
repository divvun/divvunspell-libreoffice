#ifndef INCLUDED_COM_SUN_STAR_XML_DOM_XDOCUMENTBUILDER_HPP
#define INCLUDED_COM_SUN_STAR_XML_DOM_XDOCUMENTBUILDER_HPP

#include "sal/config.h"

#include "com/sun/star/xml/dom/XDocumentBuilder.hdl"

#include "com/sun/star/io/XInputStream.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/xml/dom/XDOMImplementation.hpp"
#include "com/sun/star/xml/dom/XDocument.hpp"
#include "com/sun/star/xml/sax/XEntityResolver.hpp"
#include "com/sun/star/xml/sax/XErrorHandler.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace xml { namespace dom {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xml::dom::XDocumentBuilder const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.xml.dom.XDocumentBuilder" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::xml::dom::XDocumentBuilder > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::xml::dom::XDocumentBuilder > >::get();
}

::css::uno::Type const & ::css::xml::dom::XDocumentBuilder::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::xml::dom::XDocumentBuilder >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::xml::dom::XDocumentBuilder>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_XML_DOM_XDOCUMENTBUILDER_HPP
