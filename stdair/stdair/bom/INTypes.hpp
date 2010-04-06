// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_INTYPES_HPP
#define __STDAIR_BOM_INTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  class IN;
  
  /** Define the BomRootStructure. */
  typedef Structure<IN> INStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<IN> INHolder_T;

}
#endif // __STDAIR_BOM_INTYPES_HPP

