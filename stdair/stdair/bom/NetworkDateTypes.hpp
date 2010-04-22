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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class NetworkDate;
  
  /** Define the NetworkDate structure. */
  typedef Structure<NetworkDate> NetworkDateStructure_T;
  
  /** Define the NetworkDate holder. */
  typedef BomChildrenHolderImp<NetworkDate> NetworkDateHolder_T;

  /** Define the NetworkDate list. */
  typedef BomList_T<NetworkDate> NetworkDateList_T;

  /** Define the NetworkDate map. */
  typedef BomMap_T<NetworkDate> NetworkDateMap_T;
  
}
#endif // __STDAIR_BOM_NETWORKDATETYPES_HPP

