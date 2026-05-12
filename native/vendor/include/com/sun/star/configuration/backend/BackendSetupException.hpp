#ifndef INCLUDED_COM_SUN_STAR_CONFIGURATION_BACKEND_BACKENDSETUPEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_CONFIGURATION_BACKEND_BACKENDSETUPEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/configuration/backend/BackendSetupException.hdl"

#include "com/sun/star/configuration/CannotLoadConfigurationException.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace configuration { namespace backend {

inline BackendSetupException::BackendSetupException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::configuration::CannotLoadConfigurationException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , BackendException()
{ }

inline BackendSetupException::BackendSetupException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::uno::Any& BackendException_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::configuration::CannotLoadConfigurationException(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , BackendException(BackendException_)
{ }

#if !defined LIBO_INTERNAL_ONLY
BackendSetupException::BackendSetupException(BackendSetupException const & the_other): ::css::configuration::CannotLoadConfigurationException(the_other), BackendException(the_other.BackendException) {}

BackendSetupException::~BackendSetupException() {}

BackendSetupException & BackendSetupException::operator =(BackendSetupException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::configuration::CannotLoadConfigurationException::operator =(the_other);
    BackendException = the_other.BackendException;
    return *this;
}
#endif

} } } } }

namespace com { namespace sun { namespace star { namespace configuration { namespace backend {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::configuration::backend::BackendSetupException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.configuration.backend.BackendSetupException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::configuration::backend::BackendSetupException const *) {
    return ::cppu::UnoType< ::css::configuration::backend::BackendSetupException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_CONFIGURATION_BACKEND_BACKENDSETUPEXCEPTION_HPP
