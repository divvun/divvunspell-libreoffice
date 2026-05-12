#ifndef INCLUDED_COM_SUN_STAR_UCB_INTERACTIVENETWORKRESOLVENAMEEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_INTERACTIVENETWORKRESOLVENAMEEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/InteractiveNetworkResolveNameException.hdl"

#include "com/sun/star/ucb/InteractiveNetworkException.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline InteractiveNetworkResolveNameException::InteractiveNetworkResolveNameException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::ucb::InteractiveNetworkException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Server()
{ }

inline InteractiveNetworkResolveNameException::InteractiveNetworkResolveNameException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::rtl::OUString& Server_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::ucb::InteractiveNetworkException(Message_, Context_, Classification_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Server(Server_)
{ }

#if !defined LIBO_INTERNAL_ONLY
InteractiveNetworkResolveNameException::InteractiveNetworkResolveNameException(InteractiveNetworkResolveNameException const & the_other): ::css::ucb::InteractiveNetworkException(the_other), Server(the_other.Server) {}

InteractiveNetworkResolveNameException::~InteractiveNetworkResolveNameException() {}

InteractiveNetworkResolveNameException & InteractiveNetworkResolveNameException::operator =(InteractiveNetworkResolveNameException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::ucb::InteractiveNetworkException::operator =(the_other);
    Server = the_other.Server;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveNetworkResolveNameException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.InteractiveNetworkResolveNameException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveNetworkResolveNameException const *) {
    return ::cppu::UnoType< ::css::ucb::InteractiveNetworkResolveNameException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_INTERACTIVENETWORKRESOLVENAMEEXCEPTION_HPP
