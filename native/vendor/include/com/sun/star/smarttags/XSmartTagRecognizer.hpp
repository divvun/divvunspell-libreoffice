#ifndef INCLUDED_COM_SUN_STAR_SMARTTAGS_XSMARTTAGRECOGNIZER_HPP
#define INCLUDED_COM_SUN_STAR_SMARTTAGS_XSMARTTAGRECOGNIZER_HPP

#include "sal/config.h"

#include "com/sun/star/smarttags/XSmartTagRecognizer.hdl"

#include "com/sun/star/frame/XController.hpp"
#include "com/sun/star/i18n/XBreakIterator.hpp"
#include "com/sun/star/lang/Locale.hpp"
#include "com/sun/star/lang/XInitialization.hpp"
#include "com/sun/star/smarttags/SmartTagRecognizerMode.hpp"
#include "com/sun/star/text/XTextMarkup.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace smarttags {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::smarttags::XSmartTagRecognizer const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.smarttags.XSmartTagRecognizer" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::smarttags::XSmartTagRecognizer > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::smarttags::XSmartTagRecognizer > >::get();
}

::css::uno::Type const & ::css::smarttags::XSmartTagRecognizer::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::smarttags::XSmartTagRecognizer >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::smarttags::XSmartTagRecognizer>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_SMARTTAGS_XSMARTTAGRECOGNIZER_HPP
