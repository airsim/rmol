// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_SEGMENTCABINTYPES_HPP
#define __STDAIR_BOM_SEGMENTCABINTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class SegmentCabin;
  
  /** Define the segment-cabin list. */
  typedef std::list<SegmentCabin*> SegmentCabinList_T;

  /** Define the segment-cabin map. */
  typedef std::map<const MapKey_T, SegmentCabin*> SegmentCabinMap_T;

}
#endif // __STDAIR_BOM_SEGMENTCABINTYPES_HPP

