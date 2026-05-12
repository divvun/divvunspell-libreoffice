#ifndef INCLUDED_COM_SUN_STAR_SDB_XREPORTDOCUMENTSSUPPLIER_HPP
#define INCLUDED_COM_SUN_STAR_SDB_XREPORTDOCUMENTSSUPPLIER_HPP

#include "sal/config.h"

#include "com/sun/star/sdb/XReportDocumentsSupplier.hdl"

#include "com/sun/star/container/XNameAccess.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace sdb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdb::XReportDocumentsSupplier const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sdb.XReportDocumentsSupplier" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sdb::XReportDocumentsSupplier > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sdb::XReportDocumentsSupplier > >::get();
}

::css::uno::Type const & ::css::sdb::XReportDocumentsSupplier::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sdb::XReportDocumentsSupplier >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sdb::XReportDocumentsSupplier>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SDB_XREPORTDOCUMENTSSUPPLIER_HPP
