// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/SegmentCabinContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinContent::SegmentCabinContent (const Key_T& iKey)
    : _key (iKey),
      _capacity (DEFAULT_CABIN_CAPACITY),
      _blockSpace (DEFAULT_BLOCK_SPACE),
      _bookingCounter (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _commitedSpace (DEFAULT_COMMITED_SPACE),
      _availabilityPool (DEFAULT_CLASS_AVAILABILITY),
      _bidPriceVector (DEFAULT_BID_PRICE_VECTOR),
      _currentBidPrice (DEFAULT_BID_PRICE),
      _cabinRevenue (DEFAULT_REVENUE_VALUE),
      _cabinAverageFare (DEFAULT_CLASS_FARE_VALUE),
      _cabinUnitRevenue (DEFAULT_REVENUE_VALUE),
      _cabinRPK (DEFAULT_DISTANCE_VALUE) {
  }

  // ////////////////////////////////////////////////////////////////////
  SegmentCabinContent::~SegmentCabinContent () {
  }

}

