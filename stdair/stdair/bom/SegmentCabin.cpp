// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/SegmentCabin.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::SegmentCabin (const Key_T& iKey)
    : _key (iKey), _parent (NULL),
      _capacity (DEFAULT_CABIN_CAPACITY),
      _blockSpace (DEFAULT_BLOCK_SPACE),
      _bookingCounter (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _commitedSpace (DEFAULT_COMMITED_SPACE),
      _availabilityPool (DEFAULT_AVAILABILITY),
      _bidPriceVector (DEFAULT_BID_PRICE_VECTOR),
      _currentBidPrice (DEFAULT_BID_PRICE) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabin::~SegmentCabin () {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string SegmentCabin::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  void SegmentCabin::updateFromReservation (const NbOfBookings_T& iNbOfBookings){
    _commitedSpace += iNbOfBookings;
  }

}

