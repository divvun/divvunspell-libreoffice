#ifndef INCLUDED_COM_SUN_STAR_SHEET_SENSITIVITYREPORT_HPP
#define INCLUDED_COM_SUN_STAR_SHEET_SENSITIVITYREPORT_HPP

#include "sal/config.h"

#include "com/sun/star/sheet/SensitivityReport.hdl"

#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace sheet {

inline SensitivityReport::SensitivityReport()
    : HasReport(false)
    , ObjCoefficients()
    , ObjReducedCosts()
    , ObjAllowableDecreases()
    , ObjAllowableIncreases()
    , ConstrValues()
    , ConstrRHS()
    , ConstrShadowPrices()
    , ConstrAllowableDecreases()
    , ConstrAllowableIncreases()
{
}

inline SensitivityReport::SensitivityReport(const ::sal_Bool& HasReport_, const ::css::uno::Sequence< double >& ObjCoefficients_, const ::css::uno::Sequence< double >& ObjReducedCosts_, const ::css::uno::Sequence< double >& ObjAllowableDecreases_, const ::css::uno::Sequence< double >& ObjAllowableIncreases_, const ::css::uno::Sequence< double >& ConstrValues_, const ::css::uno::Sequence< double >& ConstrRHS_, const ::css::uno::Sequence< double >& ConstrShadowPrices_, const ::css::uno::Sequence< double >& ConstrAllowableDecreases_, const ::css::uno::Sequence< double >& ConstrAllowableIncreases_)
    : HasReport(HasReport_)
    , ObjCoefficients(ObjCoefficients_)
    , ObjReducedCosts(ObjReducedCosts_)
    , ObjAllowableDecreases(ObjAllowableDecreases_)
    , ObjAllowableIncreases(ObjAllowableIncreases_)
    , ConstrValues(ConstrValues_)
    , ConstrRHS(ConstrRHS_)
    , ConstrShadowPrices(ConstrShadowPrices_)
    , ConstrAllowableDecreases(ConstrAllowableDecreases_)
    , ConstrAllowableIncreases(ConstrAllowableIncreases_)
{
}


inline bool operator==(const SensitivityReport& the_lhs, const SensitivityReport& the_rhs)
{
    return the_lhs.HasReport == the_rhs.HasReport
        && the_lhs.ObjCoefficients == the_rhs.ObjCoefficients
        && the_lhs.ObjReducedCosts == the_rhs.ObjReducedCosts
        && the_lhs.ObjAllowableDecreases == the_rhs.ObjAllowableDecreases
        && the_lhs.ObjAllowableIncreases == the_rhs.ObjAllowableIncreases
        && the_lhs.ConstrValues == the_rhs.ConstrValues
        && the_lhs.ConstrRHS == the_rhs.ConstrRHS
        && the_lhs.ConstrShadowPrices == the_rhs.ConstrShadowPrices
        && the_lhs.ConstrAllowableDecreases == the_rhs.ConstrAllowableDecreases
        && the_lhs.ConstrAllowableIncreases == the_rhs.ConstrAllowableIncreases;
}

inline bool operator!=(const SensitivityReport& the_lhs, const SensitivityReport& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } }

namespace com { namespace sun { namespace star { namespace sheet {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sheet::SensitivityReport const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.sheet.SensitivityReport");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::sheet::SensitivityReport const *) {
    return ::cppu::UnoType< ::css::sheet::SensitivityReport >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SHEET_SENSITIVITYREPORT_HPP
