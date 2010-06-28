// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <algorithm>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod::SegmentPeriod (const Key_T& iKey,
                          Structure_T& ioSegmentStructure)
    : SegmentPeriodContent (iKey), _structure (ioSegmentStructure) {
    init ();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod::~SegmentPeriod () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriod::init() {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriod::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentPeriod::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string SegmentPeriod::toString() const {
    std::ostringstream oStr;
    
    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentPeriod::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  bool SegmentPeriod::
  isConnectable (const SegmentPeriod& iSegmentPeriod) const {
    bool oIsConnectable = false;
    
    return oIsConnectable;
  }

  // ////////////////////////////////////////////////////////////////////
  const SegmentPeriod::Parent_T& SegmentPeriod::getParent () const {
    return _structure.getParent().getContent();
  }

  // ////////////////////////////////////////////////////////////////////
  const DatePeriod_T& SegmentPeriod::getDeparturePeriod () const {
    return getParent().getDeparturePeriod();
  }

  // ////////////////////////////////////////////////////////////////////
  const DoWStruct_T& SegmentPeriod::getDoW () const {
    return getParent().getDoW();
  }
  
}

