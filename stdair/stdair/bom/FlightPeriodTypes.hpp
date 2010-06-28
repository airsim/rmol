// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FLIGHTPERIODTYPES_HPP
#define __STDAIR_BOM_FLIGHTPERIODTYPES_HPP

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
  class FlightPeriod;
  
  /** Define the FlightPeriod structure. */
  typedef Structure<FlightPeriod> FlightPeriodStructure_T;
  
  /** Define the FlightPeriod holder. */
  typedef BomChildrenHolderImp<FlightPeriod> FlightPeriodHolder_T;

  /** Define the flight-period list. */
  typedef BomList_T<FlightPeriod> FlightPeriodList_T;

  /** Define the flight-period map. */
  typedef BomMap_T<FlightPeriod> FlightPeriodMap_T;
}
#endif // __STDAIR_BOM_FLIGHTPERIODTYPES_HPP

