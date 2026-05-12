#ifndef INCLUDED_OOO_VBA_TYPEANDIID_HPP
#define INCLUDED_OOO_VBA_TYPEANDIID_HPP

#include "sal/config.h"

#include "ooo/vba/TypeAndIID.hdl"

#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace ooo { namespace vba {

inline TypeAndIID::TypeAndIID()
    : Type()
    , IID()
{
}

inline TypeAndIID::TypeAndIID(const ::css::uno::Type& Type_, const ::rtl::OUString& IID_)
    : Type(Type_)
    , IID(IID_)
{
}


inline bool operator==(const TypeAndIID& the_lhs, const TypeAndIID& the_rhs)
{
    return the_lhs.Type == the_rhs.Type
        && the_lhs.IID == the_rhs.IID;
}

inline bool operator!=(const TypeAndIID& the_lhs, const TypeAndIID& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} }

namespace ooo { namespace vba {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::ooo::vba::TypeAndIID const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "ooo.vba.TypeAndIID");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::ooo::vba::TypeAndIID const *) {
    return ::cppu::UnoType< ::ooo::vba::TypeAndIID >::get();
}

#endif // INCLUDED_OOO_VBA_TYPEANDIID_HPP
