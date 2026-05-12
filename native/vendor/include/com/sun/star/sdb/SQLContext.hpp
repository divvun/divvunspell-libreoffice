#ifndef INCLUDED_COM_SUN_STAR_SDB_SQLCONTEXT_HPP
#define INCLUDED_COM_SUN_STAR_SDB_SQLCONTEXT_HPP

#include "sal/config.h"

#include "com/sun/star/sdb/SQLContext.hdl"

#include "com/sun/star/sdbc/SQLWarning.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace sdb {

inline SQLContext::SQLContext(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::sdbc::SQLWarning(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , Details()
{ }

inline SQLContext::SQLContext(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::rtl::OUString& SQLState_, const ::sal_Int32& ErrorCode_, const ::css::uno::Any& NextException_, const ::rtl::OUString& Details_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::sdbc::SQLWarning(Message_, Context_, SQLState_, ErrorCode_, NextException_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , Details(Details_)
{ }

#if !defined LIBO_INTERNAL_ONLY
SQLContext::SQLContext(SQLContext const & the_other): ::css::sdbc::SQLWarning(the_other), Details(the_other.Details) {}

SQLContext::~SQLContext() {}

SQLContext & SQLContext::operator =(SQLContext const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::sdbc::SQLWarning::operator =(the_other);
    Details = the_other.Details;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace sdb {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdb::SQLContext const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.sdb.SQLContext" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::sdb::SQLContext const *) {
    return ::cppu::UnoType< ::css::sdb::SQLContext >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SDB_SQLCONTEXT_HPP
