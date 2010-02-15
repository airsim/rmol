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
  template <typename BOM_CONTENT> class DemandStreamStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class DemandStream;
  
  /** Define the airline feature structure. */
  typedef DemandStreamStructure<DemandStream> DemandStreamStructure_T;
  
  /** Define the airline feature structure list. */
  typedef std::vector<DemandStreamStructure_T*> DemandStreamStructureList_T;

  /** Define the airline feature structure map. */
  typedef std::map<const std::string, DemandStreamStructure_T*> DemandStreamStructureMap_T;

  /** Define the airline feature list. */
  typedef BomList_T<DemandStream> DemandStreamList_T;

  /** Define the airline feature map. */
  typedef BomMap_T<DemandStream> DemandStreamMap_T;
  
}
#endif // __STDAIR_BOM_DEMANDSTREAMTYPES_HPP
