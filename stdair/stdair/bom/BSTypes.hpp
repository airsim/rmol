// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BSTYPES_HPP
#define __STDAIR_BOM_BSTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  class BS;
  
  /** Define the BomRootStructure. */
  typedef Structure<BS> BSStructure_T;

  /** Define the BS holder type. */
  typedef BomChildrenHolderImp<BS> BSHolder_T;

}
#endif // __STDAIR_BOM_BSTYPES_HPP

