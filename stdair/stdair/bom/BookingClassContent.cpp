// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/bom/BookingClassContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  BookingClassContent::BookingClassContent (const Key_T& iKey)
    : _key (iKey),
      _nbOfBookings (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _totalNbOfBookings (DEFAULT_CLASS_TOTAL_NB_OF_BOOKINGS),
      _lastDCPTotalNbOfBookings (DEFAULT_CLASS_TOTAL_NB_OF_BOOKINGS),
      _unconstrainedDemand (DEFAULT_CLASS_UNCONSTRAINED_DEMAND),
      _nbOfCancellations (DEFAULT_CLASS_NB_OF_CANCELLATIONS),
      _nbOfNoShows (DEFAULT_CLASS_NB_OF_NOSHOWS),
      _availability (DEFAULT_CLASS_AVAILABILITY),
      _classRevenue (DEFAULT_REVENUE_VALUE),
      _currentCensorshipFlag (DEFAULT_CLASS_CENSORSHIPFLAG),
      _censorshipFlagList (DEFAULT_CLASS_CENSORSHIPFLAG_LIST),
      _bookingLimit (DEFAULT_CLASS_BOOKING_LIMIT),
      _authorizationLevel(DEFAULT_CLASS_AUTHORIZATION_LEVEL),
      _MAX (DEFAULT_CLASS_MAX_AUTHORIZATION_LEVEL),
      _MIN (DEFAULT_CLASS_MIN_AUTHORIZATION_LEVEL),
      _overbookingRate (1 + DEFAULT_CLASS_OVERBOOKING_RATE),
      _fare (DEFAULT_CLASS_FARE_VALUE),
      _adjustedYield (DEFAULT_YIELD_VALUE),
      _yield (DEFAULT_YIELD_VALUE),
      _remainingDemandMean (DEFAULT_CLASS_REMAINING_DEMAND_MEAN),
      _remainingProductDemandMean (DEFAULT_CLASS_REMAINING_DEMAND_MEAN),
      _remainingDemandSD (DEFAULT_CLASS_REMAINING_DEMAND_STANDARD_DEVIATION),
      _remainingProductDemandSD (DEFAULT_CLASS_REMAINING_DEMAND_STANDARD_DEVIATION) {
  }

  // ////////////////////////////////////////////////////////////////////
  BookingClassContent::~BookingClassContent () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  void BookingClassContent::setRemainingDemandMean(NbOfBookings_T& iMean) {
    _remainingDemandMean = iMean;
    _remainingProductDemandMean = iMean;
  }

  // ////////////////////////////////////////////////////////////////////
  void BookingClassContent::setRemainingDemandSD(NbOfBookings_T& iSD) {
    _remainingDemandSD = iSD;
    _remainingProductDemandSD = iSD;
  }
  
}

