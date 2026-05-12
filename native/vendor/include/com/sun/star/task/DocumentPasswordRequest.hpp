#ifndef INCLUDED_COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST_HPP
#define INCLUDED_COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST_HPP

#include "sal/config.h"

#include "com/sun/star/task/DocumentPasswordRequest.hdl"

#include "com/sun/star/task/PasswordRequest.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace task {

inline DocumentPasswordRequest::DocumentPasswordRequest(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::task::PasswordRequest(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Name()
{ }

inline DocumentPasswordRequest::DocumentPasswordRequest(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::css::task::PasswordRequestMode& Mode_, const ::rtl::OUString& Name_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::task::PasswordRequest(Message_, Context_, Classification_, Mode_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Name(Name_)
{ }

#if !defined LIBO_INTERNAL_ONLY
DocumentPasswordRequest::DocumentPasswordRequest(DocumentPasswordRequest const & the_other): ::css::task::PasswordRequest(the_other), Name(the_other.Name) {}

DocumentPasswordRequest::~DocumentPasswordRequest() {}

DocumentPasswordRequest & DocumentPasswordRequest::operator =(DocumentPasswordRequest const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::task::PasswordRequest::operator =(the_other);
    Name = the_other.Name;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace task {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::task::DocumentPasswordRequest const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.task.DocumentPasswordRequest" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::task::DocumentPasswordRequest const *) {
    return ::cppu::UnoType< ::css::task::DocumentPasswordRequest >::get();
}

#endif // INCLUDED_COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST_HPP
