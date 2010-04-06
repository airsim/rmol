// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_NDTYPES_HPP
#define __STDAIR_BOM_NDTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class ND;
  
  /** Define the BomRootStructure. */
  typedef Structure<ND> NDStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<ND> NDHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<ND> NDList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<ND> NDMap_T;
  
}
#endif // __STDAIR_BOM_NDTYPES_HPP

