#ifndef INCLUDED_COM_SUN_STAR_SCANNER_XSCANNERMANAGER_HPP
#define INCLUDED_COM_SUN_STAR_SCANNER_XSCANNERMANAGER_HPP

#include "sal/config.h"

#include "com/sun/star/scanner/XScannerManager.hdl"

#include "com/sun/star/awt/XBitmap.hpp"
#include "com/sun/star/lang/XEventListener.hpp"
#include "com/sun/star/scanner/ScanError.hpp"
#include "com/sun/star/scanner/ScannerContext.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace scanner {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::scanner::XScannerManager const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.scanner.XScannerManager" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::scanner::XScannerManager > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::scanner::XScannerManager > >::get();
}

::css::uno::Type const & ::css::scanner::XScannerManager::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::scanner::XScannerManager >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::scanner::XScannerManager>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SCANNER_XSCANNERMANAGER_HPP
