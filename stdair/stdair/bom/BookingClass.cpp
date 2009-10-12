// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR
#include <stdair/bom/BookingClassStructure.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClass::BookingClass (BomStructure_T& ioBookingClassStructure)
    : _bookingClassStructure (ioBookingClassStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  BookingClass::~BookingClass () {
  }

  // //////////////////////////////////////////////////////////////////////
  void BookingClass::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void BookingClass::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string BookingClass::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string BookingClass::describeKey() const {
    return _bookingClassStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string BookingClass::describeShortKey() const {
    return _bookingClassStructure.describeShortKey();
  }
  
}

