// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LCTYPES_HPP
#define __STDAIR_BOM_LCTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class LC;
  
  /** Define the BomRootStructure. */
  typedef Structure<LC> LCStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<LC> LCHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<LC> LCList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<LC> LCMap_T;
  
}
#endif // __STDAIR_BOM_LCTYPES_HPP

