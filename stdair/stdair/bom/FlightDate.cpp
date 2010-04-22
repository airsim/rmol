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
  FlightDate::FlightDate (const Key_T& iKey,
                          Structure_T& ioFlightStructure)
    : FlightDateContent (iKey), _structure (ioFlightStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDate::init() {
    _structure.initChildrenHolder<SegmentDate>();
    _structure.initChildrenHolder<LegDate>();
  }
  
  // ////////////////////////////////////////////////////////////////////
  void FlightDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void FlightDate::fromStream (std::istream& ioIn) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    std::ostringstream oStr;
    
    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDateList_T FlightDate::getSegmentDateList () const {
    return _structure.getChildrenHolder<SegmentDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDateMap_T FlightDate::getSegmentDateMap () const {
    return _structure.getChildrenHolder<SegmentDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateList_T FlightDate::getLegDateList () const {
    return _structure.getChildrenHolder<LegDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateMap_T FlightDate::getLegDateMap () const {
    return _structure.getChildrenHolder<LegDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  LegDate* FlightDate::getLegDate (const AirportCode_T& iBoardingPoint) const {
    return _structure.getChildPtr<LegDate> (iBoardingPoint);
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentDate* FlightDate::getSegmentDate (const SegmentDateKey_T& iKey) const {
    return _structure.getChildPtr<SegmentDate> (iKey.toString() );
  }
}

