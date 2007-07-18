#ifndef __COM_BAS_BASCOMTYPES_HPP
#define __COM_BAS_BASCOMTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// Boost
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace LATUS {
  
  namespace COM {

    // ////////  ////////
    /** Define the Airline Code type (2-letter-code, e.g., BA). */
    typedef std::string AirlineCode_T;

    /** Define the Flight Number (integer, e.g., 341). */
    typedef short FlightNumber_T;

    /** Define the Airport Code type (3-letter-code, e.g., LHR). */
    typedef std::string AirportCode_T;

    /** Define the Date (e.g., flight-date departure date). */
    typedef boost::gregorian::date DateTime_T;

    /** Define the Duration (e.g., elapsed in-flight time). */
    typedef boost::posix_time::time_duration Duration_T;

    /** Define the cabin code (class of service, e.g., first, business,
        economy). */
    typedef std::string CabinCode_T;
    
    /** Define the cabin capacity (resource, e.g., 200 seats).
        <br>The capacity is expressed as a double to cope with overbooking. */
    typedef double CabinCapacity_T;

    /** Define a list of availabilities. */
    typedef std::vector<double> BucketAvailabilities_T;

    /** Define a number (of travellers) in party. */
    typedef int BookingNumber_T;

    /** Define the key elements of a flight-segment. */
    struct SegmentDateStruct_T {
      AirlineCode_T airlineCode;
      FlightNumber_T flightNumber;
      AirportCode_T boardPoint;
      AirportCode_T offPoint;
      DateTime_T boardDate;
      SegmentDateStruct_T (const AirlineCode_T& iAirlineCode,
                           const FlightNumber_T& iFlightNumber,
                           const AirportCode_T& iBoardPoint,
                           const AirportCode_T& iOffPoint,
                           const DateTime_T& iBoardDate)
        : airlineCode (iAirlineCode), flightNumber (iFlightNumber),
          boardPoint (iBoardPoint), offPoint (iOffPoint),
          boardDate (iBoardDate) {}
    };
    
    /** Define a Travel Solution (TS). */
    typedef std::vector<SegmentDateStruct_T> TravelSolution_T;

    /** Define a list of travel solutions. */
    typedef std::vector<TravelSolution_T> TravelSolutionList_T;

  }
  
}
#endif // __COM_BAS_BASCOMTYPES_HPP
