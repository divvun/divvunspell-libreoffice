#ifndef INCLUDED_COM_SUN_STAR_UNO_XINTERFACE_HPP
#define INCLUDED_COM_SUN_STAR_UNO_XINTERFACE_HPP

#include "sal/config.h"

#include "com/sun/star/uno/XInterface.hdl"

#include "com/sun/star/uno/RuntimeException.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "sal/types.h"
#include "typelib/typeclass.h"
#include "typelib/typedescription.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER const ::css::uno::Reference< ::css::uno::XInterface > *) {
    return ::cppu::UnoType< ::css::uno::XInterface >::get();
}

::css::uno::Type const & ::css::uno::XInterface::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::uno::XInterface >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<typename> struct IsUnoInterfaceType: ::std::false_type {};
template<typename T> inline constexpr auto isUnoInterfaceType = sizeof (T) && IsUnoInterfaceType<T>::value;
template<> struct IsUnoInterfaceType<::css::uno::XInterface>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UNO_XINTERFACE_HPP
