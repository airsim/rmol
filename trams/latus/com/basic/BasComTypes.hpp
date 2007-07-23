#ifndef __COM_BAS_BASCOMTYPES_HPP
#define __COM_BAS_BASCOMTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <sstream>
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

    /** Define a Day Of the Week (DOW) sequence.
        <br>For instance, 1..11.1 means that the period is active on
        Mon., Thu., Fri. and Sun. */
    typedef std::vector<bool> DOW_T;

  }
}
#endif // __COM_BAS_BASCOMTYPES_HPP
