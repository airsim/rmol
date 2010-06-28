// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_TravelSolution.hpp>
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentDate::SegmentDate (const Key_T& iKey,
                            Structure_T& ioSegmentStructure)
    : SegmentDateContent (iKey), _structure (ioSegmentStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentDate::~SegmentDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDate::init () {
    _structure.initChildrenHolder<SegmentCabin>();
    _structure.initChildrenHolder<LegDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentDate::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentDate::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentDate::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinList_T SegmentDate::getSegmentCabinList () const {
    return _structure.getChildrenHolder<SegmentCabin>();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinMap_T SegmentDate::getSegmentCabinMap () const {
    return _structure.getChildrenHolder<SegmentCabin>();
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateMap_T SegmentDate::getLegDateMap () const {
    return _structure.getChildrenHolder<LegDate>();
  }
  
  // ////////////////////////////////////////////////////////////////////
  LegDateList_T SegmentDate::getLegDateList () const {
    return _structure.getChildrenHolder<LegDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  const AirlineCode_T& SegmentDate::getAirlineCode () const {
    return _structure.getParent().getParent().getKey().getAirlineCode();
  }

  // ////////////////////////////////////////////////////////////////////
  const FlightNumber_T& SegmentDate::getFlightNumber () const {
    return _structure.getParent().getKey().getFlightNumber();
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin* SegmentDate::
  getSegmentCabin (const CabinCode_T& iCabinCode) const {
    return _structure.getChildPtr<SegmentCabin> (iCabinCode);
  }
  
}

