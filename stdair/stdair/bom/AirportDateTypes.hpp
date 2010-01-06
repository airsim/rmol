// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_AIRPORTDATETYPES_HPP
#define __STDAIR_BOM_AIRPORTDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class AirportDateStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class AirportDate;
  
  /** Define the AirportDate structure. */
  typedef AirportDateStructure<AirportDate> AirportDateStructure_T;
  
  /** Define the airport-date structure list. */
  typedef std::vector<AirportDateStructure_T*> AirportDateStructureList_T;

  /** Define the airport-date structure map. */
  typedef std::map<const std::string, AirportDateStructure_T*> AirportDateStructureMap_T;
  
 /** Define the airport-date list. */
  typedef BomList_T<AirportDate> AirportDateList_T;

  /** Define the airport-date map. */
  typedef BomMap_T<AirportDate> AirportDateMap_T;
}
#endif // __STDAIR_BOM_AIRPORTDATETYPES_HPP

