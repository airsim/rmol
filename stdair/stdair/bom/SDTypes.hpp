// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SDTYPES_HPP
#define __STDAIR_BOM_SDTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class SD;
  
  /** Define the BomRootStructure. */
  typedef Structure<SD> SDStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<SD> SDHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<SD> SDList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<SD> SDMap_T;
  
}
#endif // __STDAIR_BOM_SDTYPES_HPP

