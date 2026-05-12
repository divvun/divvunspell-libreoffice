#ifndef INCLUDED_OOO_VBA_WORD_XLISTFORMAT_HPP
#define INCLUDED_OOO_VBA_WORD_XLISTFORMAT_HPP

#include "sal/config.h"

#include "ooo/vba/word/XListFormat.hdl"

#include "ooo/vba/XHelperInterface.hpp"
#include "ooo/vba/word/XListTemplate.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace ooo { namespace vba { namespace word {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::word::XListFormat const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "ooo.vba.word.XListFormat" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::ooo::vba::word::XListFormat > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::ooo::vba::word::XListFormat > >::get();
}

::css::uno::Type const & ::ooo::vba::word::XListFormat::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::ooo::vba::word::XListFormat >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::ooo::vba::word::XListFormat>: ::std::true_type {};
}
#endif

#endif // INCLUDED_OOO_VBA_WORD_XLISTFORMAT_HPP
