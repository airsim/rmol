// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOMROOTTYPES_HPP
#define __STDAIR_BOM_BOMROOTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename BOM_CONTENT> class BomRootStructure;
  template <typename BOM_CONTENT> class BomRootKey;
  class BomRoot;
  
  /** Define the BomRootStructure. */
  typedef BomRootStructure<BomRoot> BomRootStructure_T;

  /** Define the BomRootStructureKey. */
  typedef BomRootKey<BomRoot> BomRootKey_T;

}
#endif // __STDAIR_BOM_BOMROOTTYPES_HPP

