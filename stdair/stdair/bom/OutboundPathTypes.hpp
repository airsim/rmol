// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_OUTBOUNDPATHTYPES_HPP
#define __STDAIR_BOM_OUTBOUNDPATHTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class OutboundPathStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class OutboundPath;
  
  /** Define the booking class structure. */
  typedef OutboundPathStructure<OutboundPath> OutboundPathStructure_T;
  
  /** Define the booking class structure list. */
  typedef std::vector<OutboundPathStructure_T*> OutboundPathStructureList_T;

  /** Define the booking class structure map. */
  typedef std::map<const std::string, OutboundPathStructure_T*> OutboundPathStructureMap_T;

  /** Define the booking class list. */
  typedef BomList_T<OutboundPath> OutboundPathList_T;

  /** Define the booking class map. */
  typedef BomMap_T<OutboundPath> OutboundPathMap_T;
  
  typedef std::vector<std::vector<stdair::OutboundPath*> >OutboundPathListList_T;
  typedef std::vector<stdair::OutboundPath*> OutboundPathLightList_T;
  
}
#endif // __STDAIR_BOM_OUTBOUNDPATHTYPES_HPP

