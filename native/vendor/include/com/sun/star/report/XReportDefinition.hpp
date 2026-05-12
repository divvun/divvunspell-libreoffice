#ifndef INCLUDED_COM_SUN_STAR_REPORT_XREPORTDEFINITION_HPP
#define INCLUDED_COM_SUN_STAR_REPORT_XREPORTDEFINITION_HPP

#include "sal/config.h"

#include "com/sun/star/report/XReportDefinition.hdl"

#include "com/sun/star/document/XDocumentSubStorageSupplier.hpp"
#include "com/sun/star/document/XEventBroadcaster.hpp"
#include "com/sun/star/document/XStorageBasedDocument.hpp"
#include "com/sun/star/document/XViewDataSupplier.hpp"
#include "com/sun/star/embed/XVisualObject.hpp"
#include "com/sun/star/frame/XLoadable.hpp"
#include "com/sun/star/frame/XModel.hpp"
#include "com/sun/star/report/XFunctionsSupplier.hpp"
#include "com/sun/star/report/XGroups.hpp"
#include "com/sun/star/report/XReportComponent.hpp"
#include "com/sun/star/report/XSection.hpp"
#include "com/sun/star/sdbc/XConnection.hpp"
#include "com/sun/star/style/XStyleFamiliesSupplier.hpp"
#include "com/sun/star/ui/XUIConfigurationManagerSupplier.hpp"
#include "com/sun/star/util/XCloseable.hpp"
#include "com/sun/star/util/XModifiable2.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace report {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::report::XReportDefinition const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_INTERFACE, "com.sun.star.report.XReportDefinition" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::report::XReportDefinition > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::report::XReportDefinition > >::get();
}

::css::uno::Type const & ::css::report::XReportDefinition::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::report::XReportDefinition >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::report::XReportDefinition>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_REPORT_XREPORTDEFINITION_HPP
