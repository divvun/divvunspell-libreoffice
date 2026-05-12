#ifndef INCLUDED_COM_SUN_STAR_SYSTEM_WINDOWS_JUMPLISTITEM_HPP
#define INCLUDED_COM_SUN_STAR_SYSTEM_WINDOWS_JUMPLISTITEM_HPP

#include "sal/config.h"

#include "com/sun/star/system/windows/JumpListItem.hdl"

#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace system { namespace windows {

inline JumpListItem::JumpListItem()
    : name()
    , description()
    , arguments()
    , iconPath()
{
}

inline JumpListItem::JumpListItem(const ::rtl::OUString& name_, const ::rtl::OUString& description_, const ::rtl::OUString& arguments_, const ::rtl::OUString& iconPath_)
    : name(name_)
    , description(description_)
    , arguments(arguments_)
    , iconPath(iconPath_)
{
}


inline bool operator==(const JumpListItem& the_lhs, const JumpListItem& the_rhs)
{
    return the_lhs.name == the_rhs.name
        && the_lhs.description == the_rhs.description
        && the_lhs.arguments == the_rhs.arguments
        && the_lhs.iconPath == the_rhs.iconPath;
}

inline bool operator!=(const JumpListItem& the_lhs, const JumpListItem& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } } }

namespace com { namespace sun { namespace star { namespace system { namespace windows {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::system::windows::JumpListItem const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.system.windows.JumpListItem");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::system::windows::JumpListItem const *) {
    return ::cppu::UnoType< ::css::system::windows::JumpListItem >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SYSTEM_WINDOWS_JUMPLISTITEM_HPP
