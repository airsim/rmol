// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_NETWORKTYPES_HPP
#define __STDAIR_BOM_NETWORKTYPES_HPP

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
  class Network;
  
  /** Define the Network structure. */
  typedef Structure<Network> NetworkStructure_T;
  
  /** Define the Network holder. */
  typedef BomChildrenHolderImp<Network> NetworkHolder_T;

  /** Define the Network list. */
  typedef BomList_T<Network> NetworkList_T;

  /** Define the Network map. */
  typedef BomMap_T<Network> NetworkMap_T;
  
}
#endif // __STDAIR_BOM_NETWORKTYPES_HPP

