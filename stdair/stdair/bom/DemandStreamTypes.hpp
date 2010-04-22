#ifndef __STDAIR_BOM_DEMANDSTREAMTYPES_HPP
#define __STDAIR_BOM_DEMANDSTREAMTYPES_HPP

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
  class DemandStream;
  
  /** Define the airline feature structure. */
  typedef Structure<DemandStream> DemandStreamStructure_T;
  
  /** Define the airline feature holder. */
  typedef BomChildrenHolderImp<DemandStream> DemandStreamHolder_T;

  /** Define the airline feature list. */
  typedef BomList_T<DemandStream> DemandStreamList_T;

  /** Define the airline feature map. */
  typedef BomMap_T<DemandStream> DemandStreamMap_T;
  
}
#endif // __STDAIR_BOM_DEMANDSTREAMTYPES_HPP
