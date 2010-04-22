// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BUCKETTYPES_HPP
#define __STDAIR_BOM_BUCKETTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class Bucket;
  
  /** Define the BomRootStructure. */
  typedef Structure<Bucket> BucketStructure_T;

  /** Define the Inventory holder type. */
  typedef BomChildrenHolderImp<Bucket> BucketHolder_T;

  /** Define the Inventory list. */
  typedef BomList_T<Bucket> BucketList_T;
  
  /** Define the Inventory map. */
  typedef BomMap_T<Bucket> BucketMap_T;
  
}
#endif // __STDAIR_BOM_BUCKETTYPES_HPP

