#ifndef INCLUDED_COM_SUN_STAR_AWT_ADJUSTMENTTYPE_HPP
#define INCLUDED_COM_SUN_STAR_AWT_ADJUSTMENTTYPE_HPP

#include "sal/config.h"

#include "com/sun/star/awt/AdjustmentType.hdl"

#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::AdjustmentType const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_ENUM, "com.sun.star.awt.AdjustmentType" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::awt::AdjustmentType const *) {
    return ::cppu::UnoType< ::css::awt::AdjustmentType >::get();
}

#endif // INCLUDED_COM_SUN_STAR_AWT_ADJUSTMENTTYPE_HPP
