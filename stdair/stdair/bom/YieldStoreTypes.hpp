// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_YIELDSTORETYPES_HPP
#define __STDAIR_BOM_YIELDSTORETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {

  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class YieldStore;
  
  /** Define the BomRootStructure. */
  typedef Structure<YieldStore> YieldStoreStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<YieldStore> YieldStoreHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<YieldStore> YieldStoreList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<YieldStore> YieldStoreMap_T;
  
}
#endif // __STDAIR_BOM_YIELDSTORETYPES_HPP

