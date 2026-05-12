#ifndef INCLUDED_COM_SUN_STAR_SDBC_SQLEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_SDBC_SQLEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/sdbc/SQLException.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

namespace com { namespace sun { namespace star { namespace sdbc {

inline SQLException::SQLException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , SQLState()
    , ErrorCode(0)
    , NextException()
{ }

inline SQLException::SQLException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::rtl::OUString& SQLState_, const ::sal_Int32& ErrorCode_, const ::css::uno::Any& NextException_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , SQLState(SQLState_)
    , ErrorCode(ErrorCode_)
    , NextException(NextException_)
{ }

#if !defined LIBO_INTERNAL_ONLY
SQLException::SQLException(SQLException const & the_other): ::css::uno::Exception(the_other), SQLState(the_other.SQLState), ErrorCode(the_other.ErrorCode), NextException(the_other.NextException) {}

SQLException::~SQLException() {}

SQLException & SQLException::operator =(SQLException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    SQLState = the_other.SQLState;
    ErrorCode = the_other.ErrorCode;
    NextException = the_other.NextException;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace sdbc {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdbc::SQLException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.sdbc.SQLException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::sdbc::SQLException const *) {
    return ::cppu::UnoType< ::css::sdbc::SQLException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SDBC_SQLEXCEPTION_HPP
