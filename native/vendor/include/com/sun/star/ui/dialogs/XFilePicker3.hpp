#ifndef INCLUDED_COM_SUN_STAR_UI_DIALOGS_XFILEPICKER3_HPP
#define INCLUDED_COM_SUN_STAR_UI_DIALOGS_XFILEPICKER3_HPP

#include "sal/config.h"

#include "com/sun/star/ui/dialogs/XFilePicker3.hdl"

#include "com/sun/star/lang/XComponent.hpp"
#include "com/sun/star/ui/dialogs/XFilePicker2.hpp"
#include "com/sun/star/ui/dialogs/XFilePickerNotifier.hpp"
#include "com/sun/star/ui/dialogs/XFilterGroupManager.hpp"
#include "com/sun/star/ui/dialogs/XFilterManager.hpp"
#include "com/sun/star/util/XCancellable.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace ui { namespace dialogs {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::ui::dialogs::XFilePicker3 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.ui.dialogs.XFilePicker3" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::ui::dialogs::XFilePicker3 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::ui::dialogs::XFilePicker3 > >::get();
}

::css::uno::Type const & ::css::ui::dialogs::XFilePicker3::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::ui::dialogs::XFilePicker3 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::ui::dialogs::XFilePicker3>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_UI_DIALOGS_XFILEPICKER3_HPP
