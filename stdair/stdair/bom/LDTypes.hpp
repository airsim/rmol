// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LDTYPES_HPP
#define __STDAIR_BOM_LDTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class LD;
  
  /** Define the BomRootStructure. */
  typedef Structure<LD> LDStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<LD> LDHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<LD> LDList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<LD> LDMap_T;
  
}
#endif // __STDAIR_BOM_LDTYPES_HPP

