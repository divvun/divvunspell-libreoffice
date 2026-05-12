#ifndef INCLUDED_COM_SUN_STAR_I18N_XLOCALEDATA_HPP
#define INCLUDED_COM_SUN_STAR_I18N_XLOCALEDATA_HPP

#include "sal/config.h"

#include "com/sun/star/i18n/XLocaleData.hdl"

#include "com/sun/star/i18n/Calendar.hpp"
#include "com/sun/star/i18n/Currency.hpp"
#include "com/sun/star/i18n/ForbiddenCharacters.hpp"
#include "com/sun/star/i18n/FormatElement.hpp"
#include "com/sun/star/i18n/Implementation.hpp"
#include "com/sun/star/i18n/LanguageCountryInfo.hpp"
#include "com/sun/star/i18n/LocaleDataItem.hpp"
#include "com/sun/star/lang/Locale.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace i18n {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::i18n::XLocaleData const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.i18n.XLocaleData" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::i18n::XLocaleData > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::i18n::XLocaleData > >::get();
}

::css::uno::Type const & ::css::i18n::XLocaleData::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::i18n::XLocaleData >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::i18n::XLocaleData>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_I18N_XLOCALEDATA_HPP
