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
  template <typename BOM_CONTENT> class NetworkStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class Network;
  
  /** Define the Network structure. */
  typedef NetworkStructure<Network> NetworkStructure_T;
  
  /** Define the Network structure list. */
  typedef std::vector<NetworkStructure_T*> NetworkStructureList_T;

  /** Define the Network structure map. */
  typedef std::map<const std::string, NetworkStructure_T*> NetworkStructureMap_T;

  /** Define the Network list. */
  typedef BomList_T<Network> NetworkList_T;

  /** Define the Network map. */
  typedef BomMap_T<Network> NetworkMap_T;
  
}
#endif // __STDAIR_BOM_NETWORKTYPES_HPP

