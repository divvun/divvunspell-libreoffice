#ifndef INCLUDED_COM_SUN_STAR_SYSTEM_SYSTEMSHELLEXECUTEEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_SYSTEM_SYSTEMSHELLEXECUTEEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/system/SystemShellExecuteException.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

namespace com { namespace sun { namespace star { namespace system {

inline SystemShellExecuteException::SystemShellExecuteException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , PosixError(0)
{ }

inline SystemShellExecuteException::SystemShellExecuteException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::sal_Int32& PosixError_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , PosixError(PosixError_)
{ }

#if !defined LIBO_INTERNAL_ONLY
SystemShellExecuteException::SystemShellExecuteException(SystemShellExecuteException const & the_other): ::css::uno::Exception(the_other), PosixError(the_other.PosixError) {}

SystemShellExecuteException::~SystemShellExecuteException() {}

SystemShellExecuteException & SystemShellExecuteException::operator =(SystemShellExecuteException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    PosixError = the_other.PosixError;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace system {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::system::SystemShellExecuteException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.system.SystemShellExecuteException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::system::SystemShellExecuteException const *) {
    return ::cppu::UnoType< ::css::system::SystemShellExecuteException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SYSTEM_SYSTEMSHELLEXECUTEEXCEPTION_HPP
