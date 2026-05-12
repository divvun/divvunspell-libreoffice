#ifndef INCLUDED_COM_SUN_STAR_SDB_APPLICATION_XDATABASEDOCUMENTUI_HPP
#define INCLUDED_COM_SUN_STAR_SDB_APPLICATION_XDATABASEDOCUMENTUI_HPP

#include "sal/config.h"

#include "com/sun/star/sdb/application/XDatabaseDocumentUI.hdl"

#include "com/sun/star/awt/XWindow.hpp"
#include "com/sun/star/beans/Pair.hpp"
#include "com/sun/star/beans/PropertyValue.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/sdbc/XConnection.hpp"
#include "com/sun/star/sdbc/XDataSource.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace sdb { namespace application {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sdb::application::XDatabaseDocumentUI const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.sdb.application.XDatabaseDocumentUI" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::sdb::application::XDatabaseDocumentUI > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::sdb::application::XDatabaseDocumentUI > >::get();
}

::css::uno::Type const & ::css::sdb::application::XDatabaseDocumentUI::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::sdb::application::XDatabaseDocumentUI >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::sdb::application::XDatabaseDocumentUI>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SDB_APPLICATION_XDATABASEDOCUMENTUI_HPP
