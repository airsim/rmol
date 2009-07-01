#ifndef __STDAIR_STDAIR_TYPES_HPP
#define __STDAIR_STDAIR_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <list>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace stdair {

   // ///////// Exceptions ///////////
  class RootException : public std::exception {
  };

  class FileNotFoundException : public RootException {
  };
  
  class NonInitialisedServiceException : public RootException {
  };

  class MemoryAllocationException : public RootException {
  };

  class ObjectNotFoundException : public RootException {
  };

  class DocumentNotFoundException : public RootException {
  };


  // /////////////// Log /////////////
  /** Level of logs. */
  namespace LOG {
    typedef enum {
      CRITICAL = 0,
      ERROR,
      NOTIFICATION,
      WARNING,
      DEBUG,
      VERBOSE,
      LAST_VALUE
    } EN_LogLevel;
  }

  // //////// Type definitions /////////
  /** Define the type for airline codes. */
  typedef std::string AirlineCode_T;

  /** Define the type for flight numbers. */
  typedef unsigned int FlightNumber_T;
  
  /** Define the type for durations (e.g., elapsed in-flight time). */
  typedef boost::posix_time::time_duration Duration_T;

  /** Define the type for date (e.g., departure date of a flight). */
  typedef boost::gregorian::date Date_T;
    
  /** Define the type for airport codes. */
  typedef std::string AirportCode_T;
  
}
#endif // __STDAIR_STDAIR_TYPES_HPP
