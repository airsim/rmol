// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClass::BookingClass (const Key_T& iKey,
                              Structure_T& ioBookingClassStructure)
    : BookingClassContent (iKey),
      _structure (ioBookingClassStructure) {
    init ();
  }
  
  // ////////////////////////////////////////////////////////////////////
  BookingClass::~BookingClass () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::init () {
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string BookingClass::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string BookingClass::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const AirlineCode_T& BookingClass::getAirlineCode () const {
    return _structure.getParent().getParent().
      getParent().getParent().getKey().getAirlineCode();
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClass::sell (const NbOfBookings_T& iNbOfBookings) {
    _nbOfBookings += iNbOfBookings;
  }
  
}

