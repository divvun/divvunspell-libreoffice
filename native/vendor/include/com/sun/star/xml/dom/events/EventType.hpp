#ifndef INCLUDED_COM_SUN_STAR_XML_DOM_EVENTS_EVENTTYPE_HPP
#define INCLUDED_COM_SUN_STAR_XML_DOM_EVENTS_EVENTTYPE_HPP

#include "sal/config.h"

#include "com/sun/star/xml/dom/events/EventType.hdl"

#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace xml { namespace dom { namespace events {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xml::dom::events::EventType const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_type_init( &the_type, typelib_TypeClass_ENUM, "com.sun.star.xml.dom.events.EventType" );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::xml::dom::events::EventType const *) {
    return ::cppu::UnoType< ::css::xml::dom::events::EventType >::get();
}

#endif // INCLUDED_COM_SUN_STAR_XML_DOM_EVENTS_EVENTTYPE_HPP
