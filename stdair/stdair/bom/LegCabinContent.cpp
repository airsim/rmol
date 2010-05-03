// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/LegCabinContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabinContent::LegCabinContent (const Key_T& iKey)
  : _key (iKey),
    _capacity (DEFAULT_CABIN_CAPACITY),
    _soldSeat (DEFAULT_CLASS_NB_OF_BOOKINGS),
    _commitedSpace (DEFAULT_COMMITED_SPACE),
    _availabilityPool (DEFAULT_AVAILABILITY),
    _availability (DEFAULT_AVAILABILITY),
    _bidPriceVector (DEFAULT_BID_PRICE_VECTOR),
    _currentBidPrice (DEFAULT_BID_PRICE) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinContent::~LegCabinContent () {
  }

}

