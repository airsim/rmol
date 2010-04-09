// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BKTYPES_HPP
#define __STDAIR_BOM_BKTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class BK;
  
  /** Define the BomRootStructure. */
  typedef Structure<BK> BKStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<BK> BKHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<BK> BKList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<BK> BKMap_T;
  
}
#endif // __STDAIR_BOM_BKTYPES_HPP

