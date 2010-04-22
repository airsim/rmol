// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LEGDATETYPES_HPP
#define __STDAIR_BOM_LEGDATETYPES_HPP

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
  class LegDate;
  
  /** Define the LegDate structure. */
  typedef Structure<LegDate> LegDateStructure_T;
  
  /** Define the LegDate holder. */
  typedef BomChildrenHolderImp<LegDate> LegDateHolder_T;

 /** Define the leg-date list. */
  typedef BomList_T<LegDate> LegDateList_T;

  /** Define the leg-date map. */
  typedef BomMap_T<LegDate> LegDateMap_T;
}
#endif // __STDAIR_BOM_LEGDATETYPES_HPP

