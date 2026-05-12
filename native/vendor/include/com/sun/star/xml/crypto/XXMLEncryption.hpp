#ifndef INCLUDED_COM_SUN_STAR_XML_CRYPTO_XXMLENCRYPTION_HPP
#define INCLUDED_COM_SUN_STAR_XML_CRYPTO_XXMLENCRYPTION_HPP

#include "sal/config.h"

#include "com/sun/star/xml/crypto/XXMLEncryption.hdl"

#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/xml/crypto/XSecurityEnvironment.hpp"
#include "com/sun/star/xml/crypto/XXMLEncryptionTemplate.hpp"
#include "com/sun/star/xml/crypto/XXMLSecurityContext.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace xml { namespace crypto {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xml::crypto::XXMLEncryption const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.xml.crypto.XXMLEncryption" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::xml::crypto::XXMLEncryption > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::xml::crypto::XXMLEncryption > >::get();
}

::css::uno::Type const & ::css::xml::crypto::XXMLEncryption::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::xml::crypto::XXMLEncryption >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::xml::crypto::XXMLEncryption>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_XML_CRYPTO_XXMLENCRYPTION_HPP
