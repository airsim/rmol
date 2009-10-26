// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/SegmentDateStructure.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinList.hpp>
#include <stdair/bom/SegmentCabinMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const BomKey_T& iKey,
                            BomStructure_T& ioSegmentStructure)
    : SegmentDateContent (iKey), _segmentDateStructure (ioSegmentStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void SegmentDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SegmentDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeKey() const {
    return _segmentDateStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeShortKey() const {
    return _segmentDateStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinList_T SegmentDate::getSegmentCabinList () const {
    return _segmentDateStructure.getChildrenList();
  }

  // //////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T SegmentDate::getSegmentCabinMap () const {
    return _segmentDateStructure.getChildrenList();
  }
  
}

