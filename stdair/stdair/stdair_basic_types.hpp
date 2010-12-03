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
  
  /** Location code (3-letter-code, e.g., LON). */
  typedef std::string LocationCode_T;
  
  /** Define a distance (kilometers). */
  typedef long int Distance_T;

  /** Define the Airport Code type (3-letter-code, e.g., LHR). */
  typedef LocationCode_T AirportCode_T;

  /** City code */
  typedef LocationCode_T CityCode_T;
  
  /** Define the Airline Code type (2-letter-code, e.g., BA). */
  typedef std::string AirlineCode_T;

  /** Define the type for flight numbers. */
  typedef unsigned short FlightNumber_T;

  /** Define the cabin code (class of service, e.g., first, business,
      economy). */
  typedef std::string CabinCode_T;

  /** Define the code of the fare family (e.g., 1, 2, 3, etc.). */
  typedef std::string FamilyCode_T;

  /** Define the booking class code (product segment class, e.g., H,
      B, K, etc.). */
  typedef std::string ClassCode_T;

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

  /** Count */
  typedef int Count_T;
  
  /** Number of passengers (in a group) for a booking. */
  typedef unsigned short PartySize_T;

  /** Define a number of requests. */
  typedef double NbOfRequests_T;

  /** Define a number of bookings. */
  typedef NbOfRequests_T NbOfBookings_T;

  /** Define a number of travel solutions
      (in a travel solution block). */
  typedef unsigned short NbOfTravelSolutions_T;

  /** Define the list of class codes as a string. */
  typedef std::string ClassList_String_T;

  /** Define a number of segment-dates (in a path). */
  typedef unsigned short NbOfSegments_T;

  /** Define a number of airlines (in a path). */
  typedef unsigned short NbOfAirlines_T;

  /** Define an availability. */
  typedef double Availability_T;

  /** Define the price of a travel solution. */
  typedef double Fare_T;

  // ///////////// Technical ////////////////
  /** File or directory name.
      <br>It may contain paths, relative or absolute (e.g., /foo/bar
      or C:\foo\bar). */
  typedef std::string Filename_T;
  
  /** Define the file address type (e.g. "a_directory/a_filename").
      <br>NOTE: That type should be deprecated. */
  typedef std::string FileAddress_T;

}
#endif // __STDAIR_STDAIR_BASIC_TYPES_HPP
