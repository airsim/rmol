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
  template <typename BOM_CONTENT> class SegmentCabinStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class SegmentCabin;
  
  /** Define the SegmentCabin structure. */
  typedef SegmentCabinStructure<SegmentCabin> SegmentCabinStructure_T;
  
  /** Define the segment-cabin structure list. */
  typedef std::vector<SegmentCabinStructure_T*> SegmentCabinStructureList_T;

  /** Define the segment-cabin structure map. */
  typedef std::map<const std::string, SegmentCabinStructure_T*> SegmentCabinStructureMap_T;
  
 /** Define the segment-cabin list. */
  typedef BomList_T<SegmentCabin> SegmentCabinList_T;

  /** Define the segment-cabin map. */
  typedef BomMap_T<SegmentCabin> SegmentCabinMap_T;

}
#endif // __STDAIR_BOM_SEGMENTCABINTYPES_HPP

