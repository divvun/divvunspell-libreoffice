#ifndef INCLUDED_COM_SUN_STAR_DOCUMENT_FONTSDISALLOWEDITINGREQUEST_HPP
#define INCLUDED_COM_SUN_STAR_DOCUMENT_FONTSDISALLOWEDITINGREQUEST_HPP

#include "sal/config.h"

#include "com/sun/star/document/FontsDisallowEditingRequest.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace document {

inline FontsDisallowEditingRequest::FontsDisallowEditingRequest(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , aFontNames()
{ }

inline FontsDisallowEditingRequest::FontsDisallowEditingRequest(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::rtl::OUString& aFontNames_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , aFontNames(aFontNames_)
{ }

#if !defined LIBO_INTERNAL_ONLY
FontsDisallowEditingRequest::FontsDisallowEditingRequest(FontsDisallowEditingRequest const & the_other): ::css::uno::Exception(the_other), aFontNames(the_other.aFontNames) {}

FontsDisallowEditingRequest::~FontsDisallowEditingRequest() {}

FontsDisallowEditingRequest & FontsDisallowEditingRequest::operator =(FontsDisallowEditingRequest const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    aFontNames = the_other.aFontNames;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace document {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::document::FontsDisallowEditingRequest const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.document.FontsDisallowEditingRequest" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::document::FontsDisallowEditingRequest const *) {
    return ::cppu::UnoType< ::css::document::FontsDisallowEditingRequest >::get();
}

#endif // INCLUDED_COM_SUN_STAR_DOCUMENT_FONTSDISALLOWEDITINGREQUEST_HPP
