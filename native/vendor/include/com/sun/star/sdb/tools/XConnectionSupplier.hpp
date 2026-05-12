#ifndef INCLUDED_COM_SUN_STAR_SDB_TOOLS_XCONNECTIONSUPPLIER_HPP
#define INCLUDED_COM_SUN_STAR_SDB_TOOLS_XCONNECTIONSUPPLIER_HPP

#include "sal/config.h"

#include "com/sun/star/sdb/tools/XConnectionSupplier.hdl"

#include "com/sun/star/lang/XInitialization.hpp"
#include "com/sun/star/sdbc/XConnection.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace sdb { namespace tools {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdb::tools::XConnectionSupplier const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sdb.tools.XConnectionSupplier" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sdb::tools::XConnectionSupplier > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sdb::tools::XConnectionSupplier > >::get();
}

::css::uno::Type const & ::css::sdb::tools::XConnectionSupplier::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sdb::tools::XConnectionSupplier >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sdb::tools::XConnectionSupplier>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SDB_TOOLS_XCONNECTIONSUPPLIER_HPP
