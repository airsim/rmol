#ifndef __LATUS_COM_BOM_EVENT_HPP
#define __LATUS_COM_BOM_EVENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    // Forward declaration
    class WTP;
  
    /** Define the key of a reservation / demand event. */
    typedef Duration_T EventKey_T;

    /** Define a reservation / demand event. */
    typedef std::pair<EventKey_T, WTP*> Event_T;
    
    /** Queue of reservations / events.
        <br>Each event is defined by a reservation time and by the full
        reservation details, provided through the WTP object.
        Indeed, that latter encompasses the city pair, the travel departure
        date and the class-path information (as the CityPair C++ class is the
        parent of the CityPairDate C++ class, itself parent of the WTP
        C++ class).
        <br>For example, an event can take the shape of a reservation for a
        $1000 price, made at (with a booking time of) 14:02:50
        for a NCE-MIA travel departing on 21-Apr-2007. */
    typedef std::multimap<Duration_T, WTP*> EventList_T;
  }
}
#endif // __LATUS_COM_BOM_EVENT_HPP
