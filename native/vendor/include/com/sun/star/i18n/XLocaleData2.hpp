#ifndef INCLUDED_COM_SUN_STAR_I18N_XLOCALEDATA2_HPP
#define INCLUDED_COM_SUN_STAR_I18N_XLOCALEDATA2_HPP

#include "sal/config.h"

#include "com/sun/star/i18n/XLocaleData2.hdl"

#include "com/sun/star/i18n/Currency2.hpp"
#include "com/sun/star/i18n/XLocaleData.hpp"
#include "com/sun/star/lang/Locale.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace i18n {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::i18n::XLocaleData2 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.i18n.XLocaleData2" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::i18n::XLocaleData2 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::i18n::XLocaleData2 > >::get();
}

::css::uno::Type const & ::css::i18n::XLocaleData2::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::i18n::XLocaleData2 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::i18n::XLocaleData2>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_I18N_XLOCALEDATA2_HPP
