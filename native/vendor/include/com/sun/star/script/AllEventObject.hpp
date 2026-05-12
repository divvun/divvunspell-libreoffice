#ifndef INCLUDED_COM_SUN_STAR_SCRIPT_ALLEVENTOBJECT_HPP
#define INCLUDED_COM_SUN_STAR_SCRIPT_ALLEVENTOBJECT_HPP

#include "sal/config.h"

#include "com/sun/star/script/AllEventObject.hdl"

#include "com/sun/star/lang/EventObject.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

namespace com { namespace sun { namespace star { namespace script {

inline AllEventObject::AllEventObject()
    : ::css::lang::EventObject()
    , Helper()
    , ListenerType()
    , MethodName()
    , Arguments()
{
}

inline AllEventObject::AllEventObject(const ::css::uno::Reference< ::css::uno::XInterface >& Source_, const ::css::uno::Any& Helper_, const ::css::uno::Type& ListenerType_, const ::rtl::OUString& MethodName_, const ::css::uno::Sequence< ::css::uno::Any >& Arguments_)
    : ::css::lang::EventObject(Source_)
    , Helper(Helper_)
    , ListenerType(ListenerType_)
    , MethodName(MethodName_)
    , Arguments(Arguments_)
{
}


inline bool operator==(const AllEventObject& the_lhs, const AllEventObject& the_rhs)
{
    return operator==( static_cast<const ::css::lang::EventObject&>(the_lhs), static_cast<const ::css::lang::EventObject&>(the_rhs) )

        && the_lhs.Helper == the_rhs.Helper
        && the_lhs.ListenerType == the_rhs.ListenerType
        && the_lhs.MethodName == the_rhs.MethodName
        && the_lhs.Arguments == the_rhs.Arguments;
}

inline bool operator!=(const AllEventObject& the_lhs, const AllEventObject& the_rhs)
{
return !operator==(the_lhs, the_rhs);
}
} } } }

namespace com { namespace sun { namespace star { namespace script {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::script::AllEventObject const *) {
    //TODO: On certain platforms with weak memory models, the following code can result in some threads observing that the_type points to garbage
    static ::typelib_TypeDescriptionReference * the_type = 0;
    if (the_type == 0) {
        ::typelib_static_type_init(&the_type, typelib_TypeClass_STRUCT, "com.sun.star.script.AllEventObject");
    }
    return *reinterpret_cast< ::css::uno::Type * >(&the_type);
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::script::AllEventObject const *) {
    return ::cppu::UnoType< ::css::script::AllEventObject >::get();
}

#endif // INCLUDED_COM_SUN_STAR_SCRIPT_ALLEVENTOBJECT_HPP
