#ifndef INCLUDED_COM_SUN_STAR_AWT_GRADIENT2_HPP
#define INCLUDED_COM_SUN_STAR_AWT_GRADIENT2_HPP

#include "sal/config.h"

#include "com/sun/star/awt/Gradient2.hdl"

#include "com/sun/star/awt/ColorStopSequence.hpp"
#include "com/sun/star/awt/Gradient.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace awt {

inline Gradient2::Gradient2()
    : ::css::awt::Gradient()
    , ColorStops()
{
}

inline Gradient2::Gradient2(const ::css::awt::GradientStyle& Style_, const ::sal_Int32& StartColor_, const ::sal_Int32& EndColor_, const ::sal_Int16& Angle_, const ::sal_Int16& Border_, const ::sal_Int16& XOffset_, const ::sal_Int16& YOffset_, const ::sal_Int16& StartIntensity_, const ::sal_Int16& EndIntensity_, const ::sal_Int16& StepCount_, const ::css::uno::Sequence< ::css::awt::ColorStop >& ColorStops_)
    : ::css::awt::Gradient(Style_, StartColor_, EndColor_, Angle_, Border_, XOffset_, YOffset_, StartIntensity_, EndIntensity_, StepCount_)
    , ColorStops(ColorStops_)
{
}


inline bool operator==(const Gradient2& the_lhs, const Gradient2& the_rhs)
{
    return operator==( static_cast<const ::css::awt::Gradient&>(the_lhs), static_cast<const ::css::awt::Gradient&>(the_rhs) )

        && the_lhs.ColorStops == the_rhs.ColorStops;
}

inline bool operator!=(const Gradient2& the_lhs, const Gradient2& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } }

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::Gradient2 const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.awt.Gradient2");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::awt::Gradient2 const *) {
    return ::cppu::UnoType< ::css::awt::Gradient2 >::get();
}

#endif // INCLUDED_COM_SUN_STAR_AWT_GRADIENT2_HPP
