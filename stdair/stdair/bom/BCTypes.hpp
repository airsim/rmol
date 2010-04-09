// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BCTYPES_HPP
#define __STDAIR_BOM_BCTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class BC;
  
  /** Define the BomRootStructure. */
  typedef Structure<BC> BCStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<BC> BCHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<BC> BCList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<BC> BCMap_T;
  
}
#endif // __STDAIR_BOM_BCTYPES_HPP

