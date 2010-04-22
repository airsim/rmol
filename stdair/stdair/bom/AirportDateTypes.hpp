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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class AirportDate;
  
  /** Define the AirportDate structure. */
  typedef Structure<AirportDate> AirportDateStructure_T;
  
  /** Define the AirportDate holder. */
  typedef BomChildrenHolderImp<AirportDate> AirportDateHolder_T;
  
 /** Define the airport-date list. */
  typedef BomList_T<AirportDate> AirportDateList_T;

  /** Define the airport-date map. */
  typedef BomMap_T<AirportDate> AirportDateMap_T;
}
#endif // __STDAIR_BOM_AIRPORTDATETYPES_HPP

