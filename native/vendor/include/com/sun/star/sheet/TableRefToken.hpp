#ifndef INCLUDED_COM_SUN_STAR_SHEET_TABLEREFTOKEN_HPP
#define INCLUDED_COM_SUN_STAR_SHEET_TABLEREFTOKEN_HPP

#include "sal/config.h"

#include "com/sun/star/sheet/TableRefToken.hdl"

#include "com/sun/star/sheet/ComplexReference.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace sheet {

inline TableRefToken::TableRefToken()
    : Index(0)
    , Item(0)
    , Reference()
{
}

inline TableRefToken::TableRefToken(const ::sal_Int32& Index_, const ::sal_Int16& Item_, const ::css::sheet::ComplexReference& Reference_)
    : Index(Index_)
    , Item(Item_)
    , Reference(Reference_)
{
}


inline bool operator==(const TableRefToken& the_lhs, const TableRefToken& the_rhs)
{
    return the_lhs.Index == the_rhs.Index
        && the_lhs.Item == the_rhs.Item
        && the_lhs.Reference == the_rhs.Reference;
}

inline bool operator!=(const TableRefToken& the_lhs, const TableRefToken& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } }

namespace com { namespace sun { namespace star { namespace sheet {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::sheet::TableRefToken const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.sheet.TableRefToken");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::sheet::TableRefToken const *) {
    return ::cppu::UnoType< ::css::sheet::TableRefToken >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SHEET_TABLEREFTOKEN_HPP
