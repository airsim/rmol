// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FLIGHTDATETYPES_HPP
#define __STDAIR_BOM_FLIGHTDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// STDAIR
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class FlightDate;

  /** Define the flight-date list. */
  typedef std::list<FlightDate*> FlightDateList_T;

  /** Define the flight-date map. */
  typedef std::map<const MapKey_T, FlightDate*> FlightDateMap_T;
}
#endif // __STDAIR_BOM_FLIGHTDATETYPES_HPP

