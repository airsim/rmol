// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::SegmentCabin (const Key_T& iKey,
                              Structure_T& ioSegmentStructure)
    : SegmentCabinContent (iKey), _structure (ioSegmentStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::~SegmentCabin () {
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::init () {
    _structure.initChildrenHolder<BookingClass> ();
    _structure.initChildrenHolder<LegCabin> ();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentCabin::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string SegmentCabin::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassList_T SegmentCabin::getBookingClassList () const {
    return _structure.getChildrenHolder<BookingClass>();
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassMap_T SegmentCabin::getBookingClassMap () const {
    return _structure.getChildrenHolder<BookingClass>();
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClass* SegmentCabin::
  getBookingClass (const ClassCode_T& iClassCode) const {
    return _structure.getChildPtr<BookingClass> (iClassCode);
  }
  
}

