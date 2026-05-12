#ifndef INCLUDED_OOO_VBA_EXCEL_RANGE_HPP
#define INCLUDED_OOO_VBA_EXCEL_RANGE_HPP

#include "sal/config.h"

#include <cassert>

#include "com/sun/star/table/XCellRange.hpp"
#include "com/sun/star/uno/DeploymentException.hpp"
#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/RuntimeException.hpp"
#include "com/sun/star/uno/XComponentContext.hpp"
#include "ooo/vba/XHelperInterface.hpp"
#include "ooo/vba/excel/XRange.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.h"
#include "rtl/ustring.hxx"

#if defined ANDROID || defined IOS //TODO
#include <com/sun/star/lang/XInitialization.hpp>
#include <osl/detail/component-defines.h>
#endif

#if defined LO_URE_CURRENT_ENV && defined LO_URE_CTOR_ENV_ooo_dot_vba_dot_excel_dot_Range && (LO_URE_CURRENT_ENV) == (LO_URE_CTOR_ENV_ooo_dot_vba_dot_excel_dot_Range) && defined LO_URE_CTOR_FUN_ooo_dot_vba_dot_excel_dot_Range
extern "C" ::css::uno::XInterface * SAL_CALL LO_URE_CTOR_FUN_ooo_dot_vba_dot_excel_dot_Range(::css::uno::XComponentContext *, ::css::uno::Sequence< ::css::uno::Any > const &);
#endif

namespace ooo { namespace vba { namespace excel {

class Range {
public:
    static ::css::uno::Reference< ::ooo::vba::excel::XRange > createRangeFromXCellRange(::css::uno::Reference< ::css::uno::XComponentContext > const & the_context, const ::css::uno::Reference< ::ooo::vba::XHelperInterface >& Parent, const ::css::uno::Reference< ::css::table::XCellRange >& Range) {
        assert(the_context.is());
        ::css::uno::Sequence< ::css::uno::Any > the_arguments(2);
        ::css::uno::Any* the_arguments_array = the_arguments.getArray();
        the_arguments_array[0] <<= Parent;
        the_arguments_array[1] <<= Range;
        ::css::uno::Reference< ::ooo::vba::excel::XRange > the_instance;
        try {
#if defined LO_URE_CURRENT_ENV && defined LO_URE_CTOR_ENV_ooo_dot_vba_dot_excel_dot_Range && (LO_URE_CURRENT_ENV) == (LO_URE_CTOR_ENV_ooo_dot_vba_dot_excel_dot_Range) && defined LO_URE_CTOR_FUN_ooo_dot_vba_dot_excel_dot_Range
            the_instance = ::css::uno::Reference< ::ooo::vba::excel::XRange >(::css::uno::Reference< ::css::uno::XInterface >(static_cast< ::css::uno::XInterface * >((*LO_URE_CTOR_FUN_ooo_dot_vba_dot_excel_dot_Range)(the_context.get(), the_arguments)), ::SAL_NO_ACQUIRE), ::css::uno::UNO_QUERY);
            ::css::uno::Reference< ::css::lang::XInitialization > init(the_instance, ::css::uno::UNO_QUERY);
            if (init.is()) {
                init->initialize(the_arguments);
            }
#else
            the_instance = ::css::uno::Reference< ::ooo::vba::excel::XRange >(the_context->getServiceManager()->createInstanceWithArgumentsAndContext( "ooo.vba.excel.Range", the_arguments, the_context), ::css::uno::UNO_QUERY);
#endif
        } catch (const ::css::uno::RuntimeException &) {
            throw;
        } catch (const ::css::uno::Exception & the_exception) {
            throw ::css::uno::DeploymentException(::rtl::OUString("component context fails to supply service ") + "ooo.vba.excel.Range" + " of type " + "ooo.vba.excel.XRange" + ": " + the_exception.Message, the_context);
        }
        if (!the_instance.is()) {
            throw ::css::uno::DeploymentException(::rtl::OUString("component context fails to supply service ") + "ooo.vba.excel.Range" + " of type " + "ooo.vba.excel.XRange", the_context);
        }
        return the_instance;
    }

private:
    Range(); // not implemented
    Range(Range &); // not implemented
    ~Range(); // not implemented
    void operator =(Range); // not implemented
};

} } }

#endif // INCLUDED_OOO_VBA_EXCEL_RANGE_HPP
