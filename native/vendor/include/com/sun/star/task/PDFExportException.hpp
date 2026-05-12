#ifndef INCLUDED_COM_SUN_STAR_TASK_PDFEXPORTEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_TASK_PDFEXPORTEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/task/PDFExportException.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

namespace com { namespace sun { namespace star { namespace task {

inline PDFExportException::PDFExportException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , ErrorCodes()
{ }

inline PDFExportException::PDFExportException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::css::uno::Sequence< ::sal_Int32 >& ErrorCodes_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , ErrorCodes(ErrorCodes_)
{ }

#if !defined LIBO_INTERNAL_ONLY
PDFExportException::PDFExportException(PDFExportException const & the_other): ::css::uno::Exception(the_other), ErrorCodes(the_other.ErrorCodes) {}

PDFExportException::~PDFExportException() {}

PDFExportException & PDFExportException::operator =(PDFExportException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    ErrorCodes = the_other.ErrorCodes;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace task {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::task::PDFExportException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.task.PDFExportException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::task::PDFExportException const *) {
    return ::cppu::UnoType< ::css::task::PDFExportException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_TASK_PDFEXPORTEXCEPTION_HPP
