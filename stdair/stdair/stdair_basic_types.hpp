#ifndef __STDAIR_STDAIR_BASIC_TYPES_HPP
#define __STDAIR_STDAIR_BASIC_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  // Basic types
  /** Event type */
  typedef std::string EventType_T;
  
  /** Count */
  typedef int Count_T;
  
  /** Location code (3-letter-code, e.g., LON). */
  typedef std::string LocationCode_T;
  
  /** Define a distance (kilometers). */
  typedef long int Distance_T;

  /** Define the Airport Code type (3-letter-code, e.g., LHR). */
  typedef LocationCode_T AirportCode_T;

  /** City code */
  typedef LocationCode_T CityCode_T;
  
  /** Define a identity number. */
  typedef unsigned long Identity_T;

  /** Trip type */
  typedef std::string TripType_T;
  
  /** Monetary value */
  typedef double MonetaryValue_T;
  
  /** Real number */
  typedef double RealNumber_T;
  
  /** Define a percentage value (between 0 and 100%). */
  typedef double Percentage_T;

  /** Define a price value (e.g., 1000.0 Euros). */
  typedef double PriceValue_T;

  /** Define a price currency (e.g., EUR for Euros). */
  typedef std::string PriceCurrency_T;

  /** Define an amount of revenue. */
  typedef double Revenue_T;

  /** Define the name of a multiplier. */
  typedef double Multiplier_T;

  /** Define the rate of overbooking */
  typedef double OverbookingRate_T;
  
  /** Define the number of seats (it can be non integer, because the
      overbooking can be applied at booking class or PNR level). */
  typedef double NbOfSeats_T;

  /** Define the number of seats required by a demand. */
  // typedef unsigned short NbOfSeats_T;

  // //////////////////////////////////////////////////////////////////////
  // Probability
  /** Probability */
  typedef float Probability_T;

}
#endif // __STDAIR_STDAIR_BASIC_TYPES_HPP
