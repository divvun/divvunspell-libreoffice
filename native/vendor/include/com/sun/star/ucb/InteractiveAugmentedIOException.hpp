#ifndef INCLUDED_COM_SUN_STAR_UCB_INTERACTIVEAUGMENTEDIOEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_INTERACTIVEAUGMENTEDIOEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/InteractiveAugmentedIOException.hdl"

#include "com/sun/star/ucb/InteractiveIOException.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline InteractiveAugmentedIOException::InteractiveAugmentedIOException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::ucb::InteractiveIOException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Arguments()
{ }

inline InteractiveAugmentedIOException::InteractiveAugmentedIOException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::css::ucb::IOErrorCode& Code_, const ::css::uno::Sequence< ::css::uno::Any >& Arguments_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::ucb::InteractiveIOException(Message_, Context_, Classification_, Code_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Arguments(Arguments_)
{ }

#if !defined LIBO_INTERNAL_ONLY
InteractiveAugmentedIOException::InteractiveAugmentedIOException(InteractiveAugmentedIOException const & the_other): ::css::ucb::InteractiveIOException(the_other), Arguments(the_other.Arguments) {}

InteractiveAugmentedIOException::~InteractiveAugmentedIOException() {}

InteractiveAugmentedIOException & InteractiveAugmentedIOException::operator =(InteractiveAugmentedIOException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::ucb::InteractiveIOException::operator =(the_other);
    Arguments = the_other.Arguments;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveAugmentedIOException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.InteractiveAugmentedIOException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::InteractiveAugmentedIOException const *) {
    return ::cppu::UnoType< ::css::ucb::InteractiveAugmentedIOException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_INTERACTIVEAUGMENTEDIOEXCEPTION_HPP
