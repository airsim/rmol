// //////////////////////////////////////////////////////////////////////
#ifndef __RMOL_BOM_BOMROOTTYPES_HPP
#define __RMOL_BOM_BOMROOTTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class BomStructureRoot;
  template <typename BOM_CONTENT> class BomStructureRootKey;
  template <typename BOM_CHILD> class BomContentRoot;
}

namespace RMOL {

  // Forward declarations.
  class Inventory;

  /** Define the BomContentRoot. */
  typedef stdair::BomContentRoot<Inventory> BomContentRoot_T;

  /** Define the BomStructureRoot. */
  typedef stdair::BomStructureRoot<BomContentRoot_T> BomStructureRoot_T;

  /** Define the BomStructureRootKey. */
  typedef stdair::BomStructureRootKey<BomContentRoot_T> BomStructureRootKey_T;

}
#endif // __RMOL_BOM_BOMROOTTYPES_HPP

