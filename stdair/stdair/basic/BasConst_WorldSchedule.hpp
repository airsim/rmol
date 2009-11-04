#ifndef __STDAIR_BAS_BASCONST_WORLDSCHEDULE_HPP
#define __STDAIR_BAS_BASCONST_WORLDSCHEDULE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  /** Default epsilon value. */
  extern const double DEFAULT_EPSILON_VALUE;

  /** Default flight speed (number of kilometers per hour). */
  extern const unsigned int DEFAULT_FLIGHT_SPEED;

  /** Default cabin capacity for Leg cabins. */
  extern const CabinCapacity_T DEFAULT_CABIN_CAPACITY;

  /** Default number of generated flight dates . */
  extern const NbOfFlightDates_T DEFAULT_NB_OF_FLIGHTDATES;

  /** Default number of bookings for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS;

  /** Default distance value (kilometers). */
  extern const Distance_T DEFAULT_DISTANCE_VALUE;

  /** Default value of Fare. */
  extern const Fare_T DEFAULT_CLASS_FARE_VALUE;

  /** Default revenue value. */
  extern const Revenue_T DEFAULT_REVENUE_VALUE;

  /** Default booking rate for OnD bookings over overall class bookings. */
  extern const BookingRatio_T DEFAULT_OND_BOOKING_RATE;

}
#endif // __STDAIR_BAS_BASCONST_WORLDSCHEDULE_HPP
