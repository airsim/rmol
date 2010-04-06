// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FDTYPES_HPP
#define __STDAIR_BOM_FDTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class FD;
  
  /** Define the BomRootStructure. */
  typedef Structure<FD> FDStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<FD> FDHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<FD> FDList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<FD> FDMap_T;
  
}
#endif // __STDAIR_BOM_FDTYPES_HPP

