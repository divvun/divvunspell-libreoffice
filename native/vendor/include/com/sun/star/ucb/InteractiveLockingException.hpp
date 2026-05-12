#ifndef INCLUDED_COM_SUN_STAR_UCB_INTERACTIVELOCKINGEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_INTERACTIVELOCKINGEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/InteractiveLockingException.hdl"

#include "com/sun/star/task/ClassifiedInteractionRequest.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline InteractiveLockingException::InteractiveLockingException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::task::ClassifiedInteractionRequest(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Url()
{ }

inline InteractiveLockingException::InteractiveLockingException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::rtl::OUString& Url_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::task::ClassifiedInteractionRequest(Message_, Context_, Classification_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Url(Url_)
{ }

#if !defined LIBO_INTERNAL_ONLY
InteractiveLockingException::InteractiveLockingException(InteractiveLockingException const & the_other): ::css::task::ClassifiedInteractionRequest(the_other), Url(the_other.Url) {}

InteractiveLockingException::~InteractiveLockingException() {}

InteractiveLockingException & InteractiveLockingException::operator =(InteractiveLockingException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::task::ClassifiedInteractionRequest::operator =(the_other);
    Url = the_other.Url;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveLockingException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.InteractiveLockingException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveLockingException const *) {
    return ::cppu::UnoType< ::css::ucb::InteractiveLockingException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_INTERACTIVELOCKINGEXCEPTION_HPP
