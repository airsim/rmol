// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_REACHABLEUNIVERSETYPES_HPP
#define __STDAIR_BOM_REACHABLEUNIVERSETYPES_HPP

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
  class ReachableUniverse;
  
  /** Define the ReachableUniverse structure. */
  typedef Structure<ReachableUniverse> ReachableUniverseStructure_T;
  
  /** Define the ReachableUniverse holder. */
  typedef BomChildrenHolderImp<ReachableUniverse> ReachableUniverseHolder_T;
  
 /** Define the reachable-universe list. */
  typedef BomList_T<ReachableUniverse> ReachableUniverseList_T;

  /** Define the reachable-universe map. */
  typedef BomMap_T<ReachableUniverse> ReachableUniverseMap_T;
}
#endif // __STDAIR_BOM_REACHABLEUNIVERSETYPES_HPP

