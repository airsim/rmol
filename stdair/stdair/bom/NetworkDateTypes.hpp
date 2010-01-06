// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_NETWORKDATETYPES_HPP
#define __STDAIR_BOM_NETWORKDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class NetworkDateStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class NetworkDate;
  
  /** Define the NetworkDate structure. */
  typedef NetworkDateStructure<NetworkDate> NetworkDateStructure_T;
  
  /** Define the NetworkDate structure list. */
  typedef std::vector<NetworkDateStructure_T*> NetworkDateStructureList_T;

  /** Define the NetworkDate structure map. */
  typedef std::map<const std::string, NetworkDateStructure_T*> NetworkDateStructureMap_T;

  /** Define the NetworkDate list. */
  typedef BomList_T<NetworkDate> NetworkDateList_T;

  /** Define the NetworkDate map. */
  typedef BomMap_T<NetworkDate> NetworkDateMap_T;
  
}
#endif // __STDAIR_BOM_NETWORKDATETYPES_HPP

