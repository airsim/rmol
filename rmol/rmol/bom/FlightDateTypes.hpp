// //////////////////////////////////////////////////////////////////////
#ifndef __RMOL_BOM_FLIGHTDATETYPES_HPP
#define __RMOL_BOM_FLIGHTDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class FlightDate;
  template <typename BOM_CONTENT> class FlightDateKey;
}

namespace RMOL {

  // Forward declarations.
  class FlightDate;
  
  /** Define the FlightDate structure. */
  typedef stdair::FlightDate<FlightDate> FlightDateStructure_T;
  
  /** Define the FlightDate key. */
  typedef stdair::FlightDateKey<FlightDate> FlightDateKey_T;
  
  /** Define the flight-date structure list. */
  typedef std::vector<FlightDateStructure_T*> FlightDateStructureList_T;

  /** Define the flight-date structure map. */
  typedef std::map<const std::string, FlightDateStructure_T*> FlightDateStructureMap_T;

}
#endif // __RMOL_BOM_FLIGHTDATETYPES_HPP

