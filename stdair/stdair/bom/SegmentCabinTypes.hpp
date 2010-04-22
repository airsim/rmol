// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTCABINTYPES_HPP
#define __STDAIR_BOM_SEGMENTCABINTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class SegmentCabin;
  
  /** Define the SegmentCabin structure. */
  typedef Structure<SegmentCabin> SegmentCabinStructure_T;
  
  /** Define the SegmentCabin holder. */
  typedef BomChildrenHolderImp<SegmentCabin> SegmentCabinHolder_T;
  
 /** Define the segment-cabin list. */
  typedef BomList_T<SegmentCabin> SegmentCabinList_T;

  /** Define the segment-cabin map. */
  typedef BomMap_T<SegmentCabin> SegmentCabinMap_T;

}
#endif // __STDAIR_BOM_SEGMENTCABINTYPES_HPP

