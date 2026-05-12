#ifndef INCLUDED_COM_SUN_STAR_UCB_UNSUPPORTEDNAMECLASHEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_UCB_UNSUPPORTEDNAMECLASHEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/ucb/UnsupportedNameClashException.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

namespace com { namespace sun { namespace star { namespace ucb {

inline UnsupportedNameClashException::UnsupportedNameClashException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , NameClash(0)
{ }

inline UnsupportedNameClashException::UnsupportedNameClashException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::sal_Int32& NameClash_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , NameClash(NameClash_)
{ }

#if !defined LIBO_INTERNAL_ONLY
UnsupportedNameClashException::UnsupportedNameClashException(UnsupportedNameClashException const & the_other): ::css::uno::Exception(the_other), NameClash(the_other.NameClash) {}

UnsupportedNameClashException::~UnsupportedNameClashException() {}

UnsupportedNameClashException & UnsupportedNameClashException::operator =(UnsupportedNameClashException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    NameClash = the_other.NameClash;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace ucb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ucb::UnsupportedNameClashException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.ucb.UnsupportedNameClashException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::ucb::UnsupportedNameClashException const *) {
    return ::cppu::UnoType< ::css::ucb::UnsupportedNameClashException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_UCB_UNSUPPORTEDNAMECLASHEXCEPTION_HPP
