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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMultimap_T;
  class OutboundPath;
  
  /** Define the outbound path structure. */
  typedef Structure<OutboundPath> OutboundPathStructure_T;
  
  /** Define the outbound path holder. */
  typedef BomChildrenHolderImp<OutboundPath> OutboundPathHolder_T;

  /** Define the outbound path list. */
  typedef BomList_T<OutboundPath> OutboundPathList_T;

  /** Define the outbound path map. */
  typedef BomMultimap_T<OutboundPath> OutboundPathMultimap_T;
  
  typedef std::vector<std::vector<stdair::OutboundPath*> >OutboundPathListList_T;
  typedef std::vector<stdair::OutboundPath*> OutboundPathLightList_T;
  
}
#endif // __STDAIR_BOM_OUTBOUNDPATHTYPES_HPP

