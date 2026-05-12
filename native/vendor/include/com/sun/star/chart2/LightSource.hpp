#ifndef INCLUDED_COM_SUN_STAR_CHART2_LIGHTSOURCE_HPP
#define INCLUDED_COM_SUN_STAR_CHART2_LIGHTSOURCE_HPP

#include "sal/config.h"

#include "com/sun/star/chart2/LightSource.hdl"

#include "com/sun/star/drawing/Direction3D.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace chart2 {

inline LightSource::LightSource()
    : nDiffuseColor(0)
    , aDirection()
    , bIsEnabled(false)
    , bSpecular(false)
{
}

inline LightSource::LightSource(const ::sal_Int32& nDiffuseColor_, const ::css::drawing::Direction3D& aDirection_, const ::sal_Bool& bIsEnabled_, const ::sal_Bool& bSpecular_)
    : nDiffuseColor(nDiffuseColor_)
    , aDirection(aDirection_)
    , bIsEnabled(bIsEnabled_)
    , bSpecular(bSpecular_)
{
}


inline bool operator==(const LightSource& the_lhs, const LightSource& the_rhs)
{
    return the_lhs.nDiffuseColor == the_rhs.nDiffuseColor
        && the_lhs.aDirection == the_rhs.aDirection
        && the_lhs.bIsEnabled == the_rhs.bIsEnabled
        && the_lhs.bSpecular == the_rhs.bSpecular;
}

inline bool operator!=(const LightSource& the_lhs, const LightSource& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } }

namespace com { namespace sun { namespace star { namespace chart2 {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::chart2::LightSource const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.chart2.LightSource");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::chart2::LightSource const *) {
    return ::cppu::UnoType< ::css::chart2::LightSource >::get();
}

#endif // INCLUDED_COM_SUN_STAR_CHART2_LIGHTSOURCE_HPP
