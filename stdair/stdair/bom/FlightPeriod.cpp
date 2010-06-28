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
  FlightPeriod::FlightPeriod (const Key_T& iKey,
                          Structure_T& ioFlightStructure)
    : FlightPeriodContent (iKey), _structure (ioFlightStructure) {
    init ();
  }

  // ////////////////////////////////////////////////////////////////////
  FlightPeriod::~FlightPeriod () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightPeriod::init() {
    _structure.initChildrenHolder<SegmentPeriod>();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void FlightPeriod::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightPeriod::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string FlightPeriod::toString() const {
    std::ostringstream oStr;
    
    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string FlightPeriod::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const FlightPeriod::Parent_T& FlightPeriod::getParent () const {
    return _structure.getParent().getContent();
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodList_T FlightPeriod::getSegmentPeriodList () const {
    return _structure.getChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriodMap_T FlightPeriod::getSegmentPeriodMap () const {
    return _structure.getChildrenHolder<SegmentPeriod>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentPeriod* FlightPeriod::getSegmentPeriod (const SegmentPeriodKey_T& iKey) const {
    return _structure.getChildPtr<SegmentPeriod> (iKey.toString() );
  }
}

