#ifndef INCLUDED_COM_SUN_STAR_FORM_SUBMISSION_XSUBMISSION_HPP
#define INCLUDED_COM_SUN_STAR_FORM_SUBMISSION_XSUBMISSION_HPP

#include "sal/config.h"

#include "com/sun/star/form/submission/XSubmission.hdl"

#include "com/sun/star/form/submission/XSubmissionVetoListener.hpp"
#include "com/sun/star/task/XInteractionHandler.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace form { namespace submission {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::form::submission::XSubmission const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.form.submission.XSubmission" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::form::submission::XSubmission > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::form::submission::XSubmission > >::get();
}

::css::uno::Type const & ::css::form::submission::XSubmission::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::form::submission::XSubmission >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::form::submission::XSubmission>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_FORM_SUBMISSION_XSUBMISSION_HPP
