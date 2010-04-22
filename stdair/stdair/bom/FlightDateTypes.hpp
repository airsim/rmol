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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class FlightDate;
  
  /** Define the FlightDate structure. */
  typedef Structure<FlightDate> FlightDateStructure_T;
  
  /** Define the FlightDate holder. */
  typedef BomChildrenHolderImp<FlightDate> FlightDateHolder_T;

  /** Define the flight-date list. */
  typedef BomList_T<FlightDate> FlightDateList_T;

  /** Define the flight-date map. */
  typedef BomMap_T<FlightDate> FlightDateMap_T;
}
#endif // __STDAIR_BOM_FLIGHTDATETYPES_HPP

