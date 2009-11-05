// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FLIGHTDATETYPES_HPP
#define __STDAIR_BOM_FLIGHTDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class FlightDateStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class FlightDate;
  
  /** Define the FlightDate structure. */
  typedef FlightDateStructure<FlightDate> FlightDateStructure_T;
  
  /** Define the flight-date structure list. */
  typedef std::vector<FlightDateStructure_T*> FlightDateStructureList_T;

  /** Define the flight-date structure map. */
  typedef std::map<const std::string, FlightDateStructure_T*> FlightDateStructureMap_T;

  /** Define the flight-date list. */
  typedef BomList_T<FlightDate> FlightDateList_T;

  /** Define the flight-date map. */
  typedef BomMap_T<FlightDate> FlightDateMap_T;
}
#endif // __STDAIR_BOM_FLIGHTDATETYPES_HPP

