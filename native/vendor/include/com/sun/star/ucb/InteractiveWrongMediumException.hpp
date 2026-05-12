#ifndef INCLUDED_COM_SUN_STAR_UCB_INTERACTIVEWRONGMEDIUMEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_INTERACTIVEWRONGMEDIUMEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/InteractiveWrongMediumException.hdl"

#include "com/sun/star/task/ClassifiedInteractionRequest.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline InteractiveWrongMediumException::InteractiveWrongMediumException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::task::ClassifiedInteractionRequest(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Medium()
{ }

inline InteractiveWrongMediumException::InteractiveWrongMediumException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::css::uno::Any& Medium_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::task::ClassifiedInteractionRequest(Message_, Context_, Classification_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Medium(Medium_)
{ }

#if !defined LIBO_INTERNAL_ONLY
InteractiveWrongMediumException::InteractiveWrongMediumException(InteractiveWrongMediumException const & the_other): ::css::task::ClassifiedInteractionRequest(the_other), Medium(the_other.Medium) {}

InteractiveWrongMediumException::~InteractiveWrongMediumException() {}

InteractiveWrongMediumException & InteractiveWrongMediumException::operator =(InteractiveWrongMediumException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::task::ClassifiedInteractionRequest::operator =(the_other);
    Medium = the_other.Medium;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveWrongMediumException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.InteractiveWrongMediumException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveWrongMediumException const *) {
    return ::cppu::UnoType< ::css::ucb::InteractiveWrongMediumException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_INTERACTIVEWRONGMEDIUMEXCEPTION_HPP
