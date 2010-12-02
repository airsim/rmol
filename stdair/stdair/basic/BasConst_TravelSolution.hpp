#ifndef __STDAIR_BAS_BASCONST_TRAVELSOLUTION_HPP
#define __STDAIR_BAS_BASCONST_TRAVELSOLUTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_types.hpp>

namespace stdair {

  /** Default flight speed (number of kilometers per hour). */
  extern const unsigned int DEFAULT_FLIGHT_SPEED;

  // //////// Travel Solutions ///////
  /** Default distance value (kilometers). */
  extern const Distance_T DEFAULT_DISTANCE_VALUE;
    
  /** Default Minimal connection time. */
  extern const Duration_T DEFAULT_MINIMAL_CONNECTION_TIME;
    
  /** Default maximal connection time. */
  extern const Duration_T DEFAULT_MAXIMAL_CONNECTION_TIME;

  /** Null time duration (in boost::time_duration unit).*/
  extern const Duration_T NULL_BOOST_TIME_DURATION;

  /** Default airlineCode value ('XX'). */
  extern const AirlineCode_T DEFAULT_AIRLINE_CODE;

  /** Default epsilon value. */
  extern const double DEFAULT_EPSILON_VALUE;

  /** Default classCode value ('X'). */
  extern const ClassCode_T DEFAULT_CLASS_CODE;

  /** Default flightPathCode value (''). */
  extern const FlightPathCode_T DEFAULT_FLIGHTPATH_CODE;

  /** Default value of Availability. */
  extern const Availability_T DEFAULT_CLASS_AVAILABILITY;

  /** Default availability status for a travel solution. */
  extern const AvailabilityStatus_T DEFAULT_AVAILABILITY_STATUS;

  /** Default number of bookings. */
  extern const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS;

  /** Default value of Fare. */
  extern const Fare_T DEFAULT_FARE_VALUE;

  /** Default nember of required seats by the demand. */
  extern const unsigned short DEFAULT_NUMBER_OF_REQUIRED_SEATS;

  /** Default Matching Indicator value between customer requirements
      and a fare rule. */
  extern const MatchingIndicator_T DEFAULT_MATCHING_INDICATOR;

  /** Default epsilon value between customer requirements
      and a fare rule. */
  extern const double DEFAULT_EPSILON_VALUE;

  /** Default revenue value. */
  extern const Revenue_T DEFAULT_REVENUE_VALUE;

  /** Default currency (euro). */
  extern const PriceCurrency_T DEFAULT_CURRENCY;

  /** Default DICO studied airline. */
  extern const AirlineCode_T DEFAULT_DICO_STUDIED_AIRLINE;

  /** Default DICO studied date. */
  extern const Date_T DEFAULT_DICO_STUDIED_DATE;
    
}
#endif // __STDAIR_BAS_BASCONST_TRAVELSOLUTION_HPP
