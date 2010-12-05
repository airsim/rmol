// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FLIGHTPERIODTYPES_HPP
#define __STDAIR_BOM_FLIGHTPERIODTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class FlightPeriod;

  /** Define the flight-period list. */
  typedef std::list<FlightPeriod*> FlightPeriodList_T;

  /** Define the flight-period map. */
  typedef std::map<const MapKey_T, FlightPeriod*> FlightPeriodMap_T;
}
#endif // __STDAIR_BOM_FLIGHTPERIODTYPES_HPP

