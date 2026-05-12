#ifndef INCLUDED_COM_SUN_STAR_JAVA_MISSINGJAVARUNTIMEEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_JAVA_MISSINGJAVARUNTIMEEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/java/MissingJavaRuntimeException.hdl"

#include "com/sun/star/java/JavaInitializationException.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

namespace com { namespace sun { namespace star { namespace java {

inline MissingJavaRuntimeException::MissingJavaRuntimeException(
#if defined LIBO_USE_SOURCE_LOCATION
    o3tl::source_location location
#endif
)
    : ::css::java::JavaInitializationException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
    , URLRuntimeLib()
{ }

inline MissingJavaRuntimeException::MissingJavaRuntimeException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_, const ::rtl::OUString& URLRuntimeLib_
#if defined LIBO_USE_SOURCE_LOCATION
    , o3tl::source_location location
#endif
)
    : ::css::java::JavaInitializationException(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
    , URLRuntimeLib(URLRuntimeLib_)
{ }

#if !defined LIBO_INTERNAL_ONLY
MissingJavaRuntimeException::MissingJavaRuntimeException(MissingJavaRuntimeException const & the_other): ::css::java::JavaInitializationException(the_other), URLRuntimeLib(the_other.URLRuntimeLib) {}

MissingJavaRuntimeException::~MissingJavaRuntimeException() {}

MissingJavaRuntimeException & MissingJavaRuntimeException::operator =(MissingJavaRuntimeException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::java::JavaInitializationException::operator =(the_other);
    URLRuntimeLib = the_other.URLRuntimeLib;
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace java {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::java::MissingJavaRuntimeException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.java.MissingJavaRuntimeException" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::java::MissingJavaRuntimeException const *) {
    return ::cppu::UnoType< ::css::java::MissingJavaRuntimeException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_JAVA_MISSINGJAVARUNTIMEEXCEPTION_HPP
