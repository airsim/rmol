#ifndef __STDAIR_BAS_BASCONST_BOOKINGCLASS_HPP
#define __STDAIR_BAS_BASCONST_BOOKINGCLASS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_fare_types.hpp>

namespace stdair {

  // //////// (Segment-)Class-related BOM ///////
  /** Default distance value (kilometers). */
  extern const Distance_T DEFAULT_DISTANCE_VALUE;

  /** Default closed class code. */
  extern const ClassCode_T DEFAULT_CLOSED_CLASS_CODE;

  /** Default number of bookings (with counted cancellation)
      for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS;

  /** Default number of bookings (without cancellation)
      for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_TOTAL_NB_OF_BOOKINGS;

  /** Default unconstrained demand for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_UNCONSTRAINED_DEMAND;

  /** Default remaining future demand mean for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_REMAINING_DEMAND_MEAN;

  /** Default remaining futre demand standard deviation for BookingClass. */
  extern const NbOfBookings_T DEFAULT_CLASS_REMAINING_DEMAND_STANDARD_DEVIATION;

  /** Default number of cancellations for BookingClass. */
  extern const NbOfCancellations_T DEFAULT_CLASS_NB_OF_CANCELLATIONS;

  /** Default number of no-shows for BookingClass. */
  extern const NbOfNoShows_T DEFAULT_CLASS_NB_OF_NOSHOWS;

  /** Default cabin capacity for Leg cabins. */
  extern const CabinCapacity_T DEFAULT_CABIN_CAPACITY;

  /** Default commited space value for Leg cabins. */
  extern const CommitedSpace_T DEFAULT_COMMITED_SPACE;

  /** Default commited space value for Leg cabins. */
  extern const BlockSpace_T DEFAULT_BLOCK_SPACE;
    
  /** Default availability. */
  extern const Availability_T DEFAULT_AVAILABILITY;

  /** Default boolean for censorship flag given the status of 
      availability for BookingClass. */
  extern const CensorshipFlag_T DEFAULT_CLASS_CENSORSHIPFLAG;

  /** Default list of censorship flag given the status of 
      availability for BookingClass. */
  extern const CensorshipFlagList_T DEFAULT_CLASS_CENSORSHIPFLAG_LIST;

  /** Default booking limit value for BookingClass. */
  extern const BookingLimit_T DEFAULT_CLASS_BOOKING_LIMIT;

  /** Default authorization level for BookingClass. */
  extern const AuthorizationLevel_T DEFAULT_CLASS_AUTHORIZATION_LEVEL;
    
  /** Default MAX value of authorization level for BookingClass. */
  extern const AuthorizationLevel_T DEFAULT_CLASS_MAX_AUTHORIZATION_LEVEL;
    
  /** Default MIN value of authorization level for BookingClass. */
  extern const AuthorizationLevel_T DEFAULT_CLASS_MIN_AUTHORIZATION_LEVEL;

  /** Default over-booking rate for BookingClass. */
  extern const OverbookingRate_T DEFAULT_CLASS_OVERBOOKING_RATE;

  /** Default fare. */
  extern const Fare_T DEFAULT_FARE_VALUE;

  /** Default revenue value for BookingClass. */
  extern const Revenue_T DEFAULT_REVENUE_VALUE;

  /** Default currency (euro). */
  extern const PriceCurrency_T DEFAULT_CURRENCY;

  /** Default load factor value (100%). */
  extern const Percentage_T DEFAULT_LOAD_FACTOR_VALUE;

  /** Default number of duration days (0). */
  extern const DayDuration_T DEFAULT_DAY_DURATION;

  /** Default epsilon value between customer requirements
      and a fare rule. */
  extern const double DEFAULT_EPSILON_VALUE;

}
#endif // __STDAIR_BAS_BASCONST_BOOKINGCLASS_HPP
