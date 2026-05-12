#ifndef INCLUDED_COM_SUN_STAR_SHEET_DATAPILOTFIELDSORTINFO_HPP
#define INCLUDED_COM_SUN_STAR_SHEET_DATAPILOTFIELDSORTINFO_HPP

#include "sal/config.h"

#include "com/sun/star/sheet/DataPilotFieldSortInfo.hdl"

#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace sheet {

inline DataPilotFieldSortInfo::DataPilotFieldSortInfo()
    : Field()
    , IsAscending(false)
    , Mode(0)
{
}

inline DataPilotFieldSortInfo::DataPilotFieldSortInfo(const ::rtl::OUString& Field_, const ::sal_Bool& IsAscending_, const ::sal_Int32& Mode_)
    : Field(Field_)
    , IsAscending(IsAscending_)
    , Mode(Mode_)
{
}


inline bool operator==(const DataPilotFieldSortInfo& the_lhs, const DataPilotFieldSortInfo& the_rhs)
{
    return the_lhs.Field == the_rhs.Field
        && the_lhs.IsAscending == the_rhs.IsAscending
        && the_lhs.Mode == the_rhs.Mode;
}

inline bool operator!=(const DataPilotFieldSortInfo& the_lhs, const DataPilotFieldSortInfo& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } }

namespace com { namespace sun { namespace star { namespace sheet {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sheet::DataPilotFieldSortInfo const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.sheet.DataPilotFieldSortInfo");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::sheet::DataPilotFieldSortInfo const *) {
    return ::cppu::UnoType< ::css::sheet::DataPilotFieldSortInfo >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SHEET_DATAPILOTFIELDSORTINFO_HPP
