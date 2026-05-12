#ifndef INCLUDED_COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST2_HPP
#define INCLUDED_COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST2_HPP

#include "sal/config.h"

#include "com/sun/star/task/DocumentPasswordRequest2.hdl"

#include "com/sun/star/task/DocumentPasswordRequest.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

namespace com { namespace sun { namespace star { namespace task {

inline DocumentPasswordRequest2::DocumentPasswordRequest2(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::task::DocumentPasswordRequest(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , IsRequestPasswordToModify(false)
{ }

inline DocumentPasswordRequest2::DocumentPasswordRequest2(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::task::InteractionClassification& Classification_, const ::css::task::PasswordRequestMode& Mode_, const ::rtl::OUString& Name_, const ::sal_Bool& IsRequestPasswordToModify_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::task::DocumentPasswordRequest(Message_, Context_, Classification_, Mode_, Name_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , IsRequestPasswordToModify(IsRequestPasswordToModify_)
{ }

#if !defined LIBO_INTERNAL_ONLY
DocumentPasswordRequest2::DocumentPasswordRequest2(DocumentPasswordRequest2 const & the_other): ::css::task::DocumentPasswordRequest(the_other), IsRequestPasswordToModify(the_other.IsRequestPasswordToModify) {}

DocumentPasswordRequest2::~DocumentPasswordRequest2() {}

DocumentPasswordRequest2 & DocumentPasswordRequest2::operator =(DocumentPasswordRequest2 const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::task::DocumentPasswordRequest::operator =(the_other);
    IsRequestPasswordToModify = the_other.IsRequestPasswordToModify;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace task {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::task::DocumentPasswordRequest2 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.task.DocumentPasswordRequest2" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::task::DocumentPasswordRequest2 const *) {
    return ::cppu::UnoType< ::css::task::DocumentPasswordRequest2 >::get();
}

#endif // INCLUDED_COM_SUN_STAR_TASK_DOCUMENTPASSWORDREQUEST2_HPP
