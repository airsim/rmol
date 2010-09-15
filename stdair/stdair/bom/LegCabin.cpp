// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/LegCabin.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabin::LegCabin (const Key_T& iKey)
    : _key (iKey), _parent (NULL),
      _offeredCapacity (DEFAULT_CABIN_CAPACITY),
      _physicalCapacity (DEFAULT_CABIN_CAPACITY),
      _soldSeat (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _commitedSpace (DEFAULT_COMMITED_SPACE),
      _availabilityPool (DEFAULT_AVAILABILITY),
      _availability (DEFAULT_AVAILABILITY),
      _bidPriceVector (DEFAULT_BID_PRICE_VECTOR),
      _currentBidPrice (DEFAULT_BID_PRICE) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabin::~LegCabin () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string LegCabin::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void LegCabin::updateFromReservation (const NbOfBookings_T& iNbOfBookings) {
    _commitedSpace += iNbOfBookings;
    _availabilityPool = _offeredCapacity - _commitedSpace;
  }

}

