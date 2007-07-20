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


    // /////////////// Structures //////////////
    /** Define a period (for instance, for a flight schedule). */
    struct Period_T {
      DateTime_T startDate;
      DateTime_T endDate;
      DOW_T dow;
      /** Constructor. */
      Period_T (const DateTime_T& iStartDate, const DateTime_T& iEndDate, 
                const DOW_T& iDow)
        : startDate (iStartDate), endDate (iEndDate), dow (iDow) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << startDate << "; " << endDate << "; ";
        for (DOW_T::const_iterator itDay = dow.begin(); itDay != dow.end();
             itDay++) { ostr << *itDay; }
        ostr << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a flight. */
    struct FlightKey_T {
      AirlineCode_T airlineCode;
      FlightNumber_T flightNumber;
      /** Constructor. */
      FlightKey_T (const AirlineCode_T& iAirlineCode,
                   const FlightNumber_T& iFlightNumber)
        : airlineCode (iAirlineCode), flightNumber (iFlightNumber) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << airlineCode << "; " << flightNumber << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a flight-period. */
    struct FlightPeriodKey_T {
      FlightKey_T flightKey;
      Period_T period;
      FlightPeriodKey_T (const FlightKey_T& iFlightKey,
                         const Period_T& iPeriod)
        : flightKey (iFlightKey), period (iPeriod) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << flightKey.describe() << "; " << period.describe() << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a leg-period. */
    struct LegPeriodKey_T {
      FlightKey_T flightKey;
      AirportCode_T boardPoint;
      /** Constructor. */
      LegPeriodKey_T (const FlightKey_T& iFlightKey,
                      const AirportCode_T& iBoardPoint)
        : flightKey (iFlightKey), boardPoint (iBoardPoint) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << flightKey.describe() << "; " << boardPoint << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of an airport pair. */
    struct AirportPair_T {
      AirportCode_T boardPoint;
      AirportCode_T offPoint;
      /** Constructor. */
      AirportPair_T (const AirportCode_T& iBoardPoint,
                     const AirportCode_T& iOffPoint)
      : boardPoint (iBoardPoint), offPoint (iOffPoint) {
      }
      /** Display of the airport pair. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << boardPoint << "; " << offPoint << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a segment-period. */
    struct SegmentPeriodKey_T {
      FlightKey_T flightKey;
      AirportPair_T airportPair;
      /** Constructor. */
      SegmentPeriodKey_T (const FlightKey_T& iFlightKey,
                          const AirportPair_T& iAirportPair)
        : flightKey (iFlightKey), airportPair (iAirportPair) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << flightKey.describe() << "; " << airportPair.describe() << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a flight-date. */
    struct FlightDateKey_T {
      FlightKey_T flightKey;
      DateTime_T flightDate;
      /** Constructor. */
      FlightDateKey_T (const FlightKey_T& iFlightKey,
                       const DateTime_T& iFlightDate)
        : flightKey (iFlightKey), flightDate (iFlightDate) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << flightKey.describe() << "; " << flightDate << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a leg-date. */
    struct LegDateKey_T {
      FlightKey_T flightKey;
      DateTime_T boardDate;
      AirportCode_T boardPoint;
      /** Constructor. */
      LegDateKey_T (const FlightKey_T& iFlightKey,
                    const DateTime_T& iBoardDate,
                    const AirportCode_T& iBoardPoint)
        : flightKey (iFlightKey), boardDate (iBoardDate),
          boardPoint (iBoardPoint) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << flightKey.describe() << boardPoint << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a leg-cabin. */
    struct LegCabinKey_T {
      LegDateKey_T legDateKey;
      CabinCode_T cabinCode;
      /** Constructor. */
      LegCabinKey_T (const LegDateKey_T& iLegDateKey,
                     const CabinCode_T& iCabinCode)
        : legDateKey (iLegDateKey), cabinCode (iCabinCode) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << legDateKey.describe() << "; " << cabinCode << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a segment-date. */
    struct SegmentDateKey_T {
      FlightKey_T flightKey;
      DateTime_T boardDate;
      AirportPair_T airportPair;
      /** Constructor. */
      SegmentDateKey_T (const FlightKey_T& iFlightKey,
                        const DateTime_T& iBoardDate,
                        const AirportPair_T& iAirportPair)
        : flightKey (iFlightKey), boardDate (iBoardDate),
          airportPair (iAirportPair) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << flightKey.describe() << "; " << airportPair.describe() << "; ";
        return ostr.str();
      }
    };
    
    /** Define the key elements of a segment-cabin. */
    struct SegmentCabinKey_T {
      SegmentDateKey_T segmentDateKey;
      CabinCode_T cabinCode;
      /** Constructor. */
      SegmentCabinKey_T (const SegmentDateKey_T& iSegmentDateKey,
                         const CabinCode_T& iCabinCode)
        : segmentDateKey (iSegmentDateKey), cabinCode (iCabinCode) {
      }
      /** Display of the key. */
      const std::string describe() const {
        std::ostringstream ostr;
        ostr << segmentDateKey.describe() << "; " << cabinCode << "; ";
        return ostr.str();
      }
    };
    
    /** Define a Travel Solution (TS). */
    typedef std::vector<SegmentDateKey_T> TravelSolutionKey_T;

    /** Define a list of travel solutions. */
    typedef std::vector<TravelSolutionKey_T> TravelSolutionKeyList_T;

  }
}
#endif // __COM_BAS_BASCOMTYPES_HPP
