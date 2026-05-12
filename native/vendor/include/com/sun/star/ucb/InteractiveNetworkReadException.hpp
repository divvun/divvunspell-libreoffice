#ifndef INCLUDED_COM_SUN_STAR_UCB_INTERACTIVENETWORKREADEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_INTERACTIVENETWORKREADEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/InteractiveNetworkReadException.hdl"

#include "com/sun/star/ucb/InteractiveNetworkException.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline InteractiveNetworkReadException::InteractiveNetworkReadException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::ucb::InteractiveNetworkException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Diagnostic()
{ }

inline InteractiveNetworkReadException::InteractiveNetworkReadException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::rtl::OUString& Diagnostic_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::ucb::InteractiveNetworkException(Message_, Context_, Classification_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Diagnostic(Diagnostic_)
{ }

#if !defined LIBO_INTERNAL_ONLY
InteractiveNetworkReadException::InteractiveNetworkReadException(InteractiveNetworkReadException const & the_other): ::css::ucb::InteractiveNetworkException(the_other), Diagnostic(the_other.Diagnostic) {}

InteractiveNetworkReadException::~InteractiveNetworkReadException() {}

InteractiveNetworkReadException & InteractiveNetworkReadException::operator =(InteractiveNetworkReadException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::ucb::InteractiveNetworkException::operator =(the_other);
    Diagnostic = the_other.Diagnostic;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveNetworkReadException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.InteractiveNetworkReadException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveNetworkReadException const *) {
    return ::cppu::UnoType< ::css::ucb::InteractiveNetworkReadException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_INTERACTIVENETWORKREADEXCEPTION_HPP
