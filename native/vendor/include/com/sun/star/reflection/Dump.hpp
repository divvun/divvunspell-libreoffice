#ifndef INCLUDED_COM_SUN_STAR_REFLECTION_DUMP_HPP
#define INCLUDED_COM_SUN_STAR_REFLECTION_DUMP_HPP

#include "sal/config.h"

#include <cassert>

#include "com/sun/star/reflection/XDump.hpp"
#include "com/sun/star/uno/DeploymentException.hpp"
#include "com/sun/star/uno/XComponentContext.hpp"
#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.h"
#include "rtl/ustring.hxx"

#if defined ANDROID || defined IOS //TODO
#include <com/sun/star/lang/XInitialization.hpp>
#include <osl/detail/component-defines.h>
#endif

#if defined LO_URE_CURRENT_ENV && defined LO_URE_CTOR_ENV_com_dot_sun_dot_star_dot_reflection_dot_Dump && (LO_URE_CURRENT_ENV) == (LO_URE_CTOR_ENV_com_dot_sun_dot_star_dot_reflection_dot_Dump) && defined LO_URE_CTOR_FUN_com_dot_sun_dot_star_dot_reflection_dot_Dump
extern "C" ::css::uno::XInterface * SAL_CALL LO_URE_CTOR_FUN_com_dot_sun_dot_star_dot_reflection_dot_Dump(::css::uno::XComponentContext *, ::css::uno::Sequence< ::css::uno::Any > const &);
#endif

namespace com { namespace sun { namespace star { namespace reflection {

class Dump {
public:
    static ::css::uno::Reference< ::css::reflection::XDump > get(::css::uno::Reference< ::css::uno::XComponentContext > const & the_context) {
        assert(the_context.is());
        ::css::uno::Reference< ::css::reflection::XDump > instance;
#if defined LO_URE_CURRENT_ENV && defined LO_URE_CTOR_ENV_com_dot_sun_dot_star_dot_reflection_dot_Dump && (LO_URE_CURRENT_ENV) == (LO_URE_CTOR_ENV_com_dot_sun_dot_star_dot_reflection_dot_Dump) && defined LO_URE_CTOR_FUN_com_dot_sun_dot_star_dot_reflection_dot_Dump
        instance = ::css::uno::Reference< ::css::reflection::XDump >(::css::uno::Reference< ::css::uno::XInterface >(static_cast< ::css::uno::XInterface * >((*LO_URE_CTOR_FUN_com_dot_sun_dot_star_dot_reflection_dot_Dump)(the_context.get(), ::css::uno::Sequence< ::css::uno::Any >())), ::SAL_NO_ACQUIRE), ::css::uno::UNO_QUERY);
#else
        the_context->getValueByName(::rtl::OUString( "/singletons/com.sun.star.reflection.Dump" )) >>= instance;
#endif
        if (!instance.is()) {
            throw ::css::uno::DeploymentException(::rtl::OUString( "component context fails to supply singleton com.sun.star.reflection.Dump of type com.sun.star.reflection.XDump" ), the_context);
        }
        return instance;
    }

private:
    Dump(); // not implemented
    Dump(Dump &); // not implemented
    ~Dump(); // not implemented
    void operator =(Dump); // not implemented
};

} } } }

#endif // INCLUDED_COM_SUN_STAR_REFLECTION_DUMP_HPP
