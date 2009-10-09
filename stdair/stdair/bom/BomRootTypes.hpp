// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOMROOTTYPES_HPP
#define __STDAIR_BOM_BOMROOTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename BOM_CONTENT> class BomStructureRoot;
  template <typename BOM_CONTENT> class BomStructureRootKey;
  template <typename BOM_CHILD> class BomContentRoot;
  class Inventory;

  /** Define the BomContentRoot. */
  typedef BomContentRoot<Inventory> BomContentRoot_T;

  /** Define the BomStructureRoot. */
  typedef BomStructureRoot<BomContentRoot_T> BomStructureRoot_T;

  /** Define the BomStructureRootKey. */
  typedef BomStructureRootKey<BomContentRoot_T> BomStructureRootKey_T;

}
#endif // __STDAIR_BOM_BOMROOTTYPES_HPP

