#ifndef INCLUDED_COM_SUN_STAR_IO_XDATAIMPORTER_HPP
#define INCLUDED_COM_SUN_STAR_IO_XDATAIMPORTER_HPP

#include "sal/config.h"

#include "com/sun/star/io/XDataImporter.hdl"

#include "com/sun/star/io/XActiveDataSource.hpp"
#include "com/sun/star/io/XDataTransferEventListener.hpp"
#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace io {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::io::XDataImporter const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.io.XDataImporter" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::io::XDataImporter > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::io::XDataImporter > >::get();
}

::css::uno::Type const & ::css::io::XDataImporter::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::io::XDataImporter >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::io::XDataImporter>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_IO_XDATAIMPORTER_HPP
