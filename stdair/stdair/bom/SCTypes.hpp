// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SCTYPES_HPP
#define __STDAIR_BOM_SCTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class SC;
  
  /** Define the BomRootStructure. */
  typedef Structure<SC> SCStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<SC> SCHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<SC> SCList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<SC> SCMap_T;
  
}
#endif // __STDAIR_BOM_SCTYPES_HPP

