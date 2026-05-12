#ifndef INCLUDED_COM_SUN_STAR_UCB_CONTENTCREATIONEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_CONTENTCREATIONEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/ContentCreationException.hdl"

#include "com/sun/star/ucb/ContentCreationError.hpp"
#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace ucb {

inline ContentCreationException::ContentCreationException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , eError(::css::ucb::ContentCreationError_UNKNOWN)
{ }

inline ContentCreationException::ContentCreationException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::ucb::ContentCreationError& eError_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , eError(eError_)
{ }

#if !defined LIBO_INTERNAL_ONLY
ContentCreationException::ContentCreationException(ContentCreationException const & the_other): ::css::uno::Exception(the_other), eError(the_other.eError) {}

ContentCreationException::~ContentCreationException() {}

ContentCreationException & ContentCreationException::operator =(ContentCreationException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    eError = the_other.eError;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::ContentCreationException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.ContentCreationException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::ContentCreationException const *) {
    return ::cppu::UnoType< ::css::ucb::ContentCreationException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_CONTENTCREATIONEXCEPTION_HPP
