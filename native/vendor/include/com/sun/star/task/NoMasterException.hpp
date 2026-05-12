#ifndef INCLUDED_COM_SUN_STAR_TASK_NOMASTEREXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_TASK_NOMASTEREXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/task/NoMasterException.hdl"

#include "com/sun/star/task/PasswordRequestMode.hpp"
#include "com/sun/star/uno/RuntimeException.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace task {

inline NoMasterException::NoMasterException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::RuntimeException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Mode(::css::task::PasswordRequestMode_PASSWORD_CREATE)
{ }

inline NoMasterException::NoMasterException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::PasswordRequestMode& Mode_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::RuntimeException(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Mode(Mode_)
{ }

#if !defined LIBO_INTERNAL_ONLY
NoMasterException::NoMasterException(NoMasterException const & the_other): ::css::uno::RuntimeException(the_other), Mode(the_other.Mode) {}

NoMasterException::~NoMasterException() {}

NoMasterException & NoMasterException::operator =(NoMasterException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::RuntimeException::operator =(the_other);
    Mode = the_other.Mode;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace task {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::task::NoMasterException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.task.NoMasterException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::task::NoMasterException const *) {
    return ::cppu::UnoType< ::css::task::NoMasterException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_TASK_NOMASTEREXCEPTION_HPP
