// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <cassert>
// STDAIR
#include <stdair/bom/SegmentDate.hpp>
// RMOL 
#include <rmol/bom/FlightDate.hpp>
#include <rmol/bom/SegmentDate.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (BomStructure_T& ioSegmentStructure)
    : _segmentDateStructure (ioSegmentStructure) {
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

}

