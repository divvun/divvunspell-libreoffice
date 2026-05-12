#ifndef INCLUDED_COM_SUN_STAR_SECURITY_XDOCUMENTDIGITALSIGNATURES_HPP
#define INCLUDED_COM_SUN_STAR_SECURITY_XDOCUMENTDIGITALSIGNATURES_HPP

#include "sal/config.h"

#include "com/sun/star/security/XDocumentDigitalSignatures.hdl"

#include "com/sun/star/awt/XWindow.hpp"
#include "com/sun/star/beans/PropertyValue.hpp"
#include "com/sun/star/embed/XStorage.hpp"
#include "com/sun/star/graphic/XGraphic.hpp"
#include "com/sun/star/io/XInputStream.hpp"
#include "com/sun/star/io/XStream.hpp"
#include "com/sun/star/security/CertificateKind.hpp"
#include "com/sun/star/security/DocumentSignatureInformation.hpp"
#include "com/sun/star/security/XCertificate.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace security {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::security::XDocumentDigitalSignatures const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.security.XDocumentDigitalSignatures" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::security::XDocumentDigitalSignatures > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::security::XDocumentDigitalSignatures > >::get();
}

::css::uno::Type const & ::css::security::XDocumentDigitalSignatures::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::security::XDocumentDigitalSignatures >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::security::XDocumentDigitalSignatures>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SECURITY_XDOCUMENTDIGITALSIGNATURES_HPP
