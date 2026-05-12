#ifndef INCLUDED_COM_SUN_STAR_CONFIGURATION_MISSINGBOOTSTRAPFILEEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_CONFIGURATION_MISSINGBOOTSTRAPFILEEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/configuration/MissingBootstrapFileException.hdl"

#include "com/sun/star/configuration/CannotLoadConfigurationException.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace configuration {

inline MissingBootstrapFileException::MissingBootstrapFileException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::configuration::CannotLoadConfigurationException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , BootstrapFileURL()
{ }

inline MissingBootstrapFileException::MissingBootstrapFileException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::rtl::OUString& BootstrapFileURL_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::configuration::CannotLoadConfigurationException(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , BootstrapFileURL(BootstrapFileURL_)
{ }

#if !defined LIBO_INTERNAL_ONLY
MissingBootstrapFileException::MissingBootstrapFileException(MissingBootstrapFileException const & the_other): ::css::configuration::CannotLoadConfigurationException(the_other), BootstrapFileURL(the_other.BootstrapFileURL) {}

MissingBootstrapFileException::~MissingBootstrapFileException() {}

MissingBootstrapFileException & MissingBootstrapFileException::operator =(MissingBootstrapFileException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::configuration::CannotLoadConfigurationException::operator =(the_other);
    BootstrapFileURL = the_other.BootstrapFileURL;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace configuration {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::configuration::MissingBootstrapFileException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.configuration.MissingBootstrapFileException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::configuration::MissingBootstrapFileException const *) {
    return ::cppu::UnoType< ::css::configuration::MissingBootstrapFileException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_CONFIGURATION_MISSINGBOOTSTRAPFILEEXCEPTION_HPP
