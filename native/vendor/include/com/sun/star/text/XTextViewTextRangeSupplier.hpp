#ifndef INCLUDED_COM_SUN_STAR_TEXT_XTEXTVIEWTEXTRANGESUPPLIER_HPP
#define INCLUDED_COM_SUN_STAR_TEXT_XTEXTVIEWTEXTRANGESUPPLIER_HPP

#include "sal/config.h"

#include "com/sun/star/text/XTextViewTextRangeSupplier.hdl"

#include "com/sun/star/awt/Point.hpp"
#include "com/sun/star/text/XTextRange.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace text {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::text::XTextViewTextRangeSupplier const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.text.XTextViewTextRangeSupplier" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::text::XTextViewTextRangeSupplier > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::text::XTextViewTextRangeSupplier > >::get();
}

::css::uno::Type const & ::css::text::XTextViewTextRangeSupplier::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::text::XTextViewTextRangeSupplier >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::text::XTextViewTextRangeSupplier>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_TEXT_XTEXTVIEWTEXTRANGESUPPLIER_HPP
