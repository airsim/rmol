// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_WorldSchedule.hpp>
#include <stdair/bom/FlightDateContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  FlightDateContent::FlightDateContent (const BomKey_T& iKey)
    : _key (iKey),
      _bookingCounter (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _flightRevenue (DEFAULT_REVENUE_VALUE),
      _flightAverageFare (DEFAULT_CLASS_FARE_VALUE),
      _flightASK (DEFAULT_DISTANCE_VALUE),
      _flightYield (DEFAULT_REVENUE_VALUE),
      _flightRPK (DEFAULT_DISTANCE_VALUE),
      _flightUnitRevenue (DEFAULT_REVENUE_VALUE),
      _flightLoadFactor (DEFAULT_REVENUE_VALUE) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDateContent::~FlightDateContent () {
  }

}

