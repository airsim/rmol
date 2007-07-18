#ifndef __LATUS_LATUSTYPES_HPP
#define __LATUS_LATUSTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <exception>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>

namespace LATUS {
  
  // ///////// Exceptions ///////////
  class RootException : public std::exception {
  };

  class ObjectNotFoundException : public RootException {
  };

  class FlightDateNotFoundException : public RootException {
  };

  class SegmentDateNotFoundException : public RootException {
  };

  class SegmentCabinNotFoundException : public RootException {
  };

  class LegDateNotFoundException : public RootException {
  };

  class LegCabinNotFoundException : public RootException {
  };

  // //////// Log ////////
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


  /** Define the capacity.
      <br>It is a double, as it allows for overbooking. */
  typedef double ResourceCapacity_T;

  /** Define the Booking Limit.
      <br>It is a double, as it allows for overbooking. */
  typedef double BookingLimit_T;

}
#endif // __LATUS_LATUSTYPES_HPP
