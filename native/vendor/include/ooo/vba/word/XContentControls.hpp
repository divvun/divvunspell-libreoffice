#ifndef INCLUDED_OOO_VBA_WORD_XCONTENTCONTROLS_HPP
#define INCLUDED_OOO_VBA_WORD_XCONTENTCONTROLS_HPP

#include "sal/config.h"

#include "ooo/vba/word/XContentControls.hdl"

#include "ooo/vba/XCollection.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace ooo { namespace vba { namespace word {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::word::XContentControls const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "ooo.vba.word.XContentControls" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::ooo::vba::word::XContentControls > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::ooo::vba::word::XContentControls > >::get();
}

::css::uno::Type const & ::ooo::vba::word::XContentControls::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::ooo::vba::word::XContentControls >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::ooo::vba::word::XContentControls>: ::std::true_type {};
}
#endif

#endif // INCLUDED_OOO_VBA_WORD_XCONTENTCONTROLS_HPP
