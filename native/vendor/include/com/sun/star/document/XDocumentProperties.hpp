#ifndef INCLUDED_COM_SUN_STAR_DOCUMENT_XDOCUMENTPROPERTIES_HPP
#define INCLUDED_COM_SUN_STAR_DOCUMENT_XDOCUMENTPROPERTIES_HPP

#include "sal/config.h"

#include "com/sun/star/document/XDocumentProperties.hdl"

#include "com/sun/star/beans/NamedValue.hpp"
#include "com/sun/star/beans/PropertyValue.hpp"
#include "com/sun/star/beans/XPropertyContainer.hpp"
#include "com/sun/star/embed/XStorage.hpp"
#include "com/sun/star/lang/Locale.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/util/DateTime.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace document {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::document::XDocumentProperties const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.document.XDocumentProperties" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::document::XDocumentProperties > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::document::XDocumentProperties > >::get();
}

::css::uno::Type const & ::css::document::XDocumentProperties::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::document::XDocumentProperties >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::document::XDocumentProperties>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DOCUMENT_XDOCUMENTPROPERTIES_HPP
