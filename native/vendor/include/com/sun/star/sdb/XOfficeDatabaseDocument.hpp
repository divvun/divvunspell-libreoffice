#ifndef INCLUDED_COM_SUN_STAR_SDB_XOFFICEDATABASEDOCUMENT_HPP
#define INCLUDED_COM_SUN_STAR_SDB_XOFFICEDATABASEDOCUMENT_HPP

#include "sal/config.h"

#include "com/sun/star/sdb/XOfficeDatabaseDocument.hdl"

#include "com/sun/star/document/XDocumentSubStorageSupplier.hpp"
#include "com/sun/star/sdb/XFormDocumentsSupplier.hpp"
#include "com/sun/star/sdb/XReportDocumentsSupplier.hpp"
#include "com/sun/star/sdbc/XDataSource.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace sdb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdb::XOfficeDatabaseDocument const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sdb.XOfficeDatabaseDocument" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sdb::XOfficeDatabaseDocument > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sdb::XOfficeDatabaseDocument > >::get();
}

::css::uno::Type const & ::css::sdb::XOfficeDatabaseDocument::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sdb::XOfficeDatabaseDocument >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sdb::XOfficeDatabaseDocument>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SDB_XOFFICEDATABASEDOCUMENT_HPP
