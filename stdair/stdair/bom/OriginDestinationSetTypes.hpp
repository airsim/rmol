// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_ORIGINDESTINATIONSETTYPES_HPP
#define __STDAIR_BOM_ORIGINDESTINATIONSETTYPES_HPP

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
  class OriginDestinationSet;
  
  /** Define the OriginDestinationSet structure. */
  typedef Structure<OriginDestinationSet> OriginDestinationSetStructure_T;
  
  /** Define the OriginDestinationSet holder. */
  typedef BomChildrenHolderImp<OriginDestinationSet> OriginDestinationSetHolder_T;

  /** Define the OriginDestinationSet list. */
  typedef BomList_T<OriginDestinationSet> OriginDestinationSetList_T;

  /** Define the OriginDestinationSet map. */
  typedef BomMap_T<OriginDestinationSet> OriginDestinationSetMap_T;
  
}
#endif // __STDAIR_BOM_ORIGINDESTINATIONSETTYPES_HPP

