#ifndef INCLUDED_COM_SUN_STAR_UCB_COMMANDFAILEDEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_COMMANDFAILEDEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/CommandFailedException.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline CommandFailedException::CommandFailedException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Reason()
{ }

inline CommandFailedException::CommandFailedException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::uno::Any& Reason_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Reason(Reason_)
{ }

#if !defined LIBO_INTERNAL_ONLY
CommandFailedException::CommandFailedException(CommandFailedException const & the_other): ::css::uno::Exception(the_other), Reason(the_other.Reason) {}

CommandFailedException::~CommandFailedException() {}

CommandFailedException & CommandFailedException::operator =(CommandFailedException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    Reason = the_other.Reason;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::CommandFailedException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.CommandFailedException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::CommandFailedException const *) {
    return ::cppu::UnoType< ::css::ucb::CommandFailedException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_COMMANDFAILEDEXCEPTION_HPP
