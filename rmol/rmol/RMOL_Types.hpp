#ifndef __RMOL_RMOL_TYPES_HPP
#define __RMOL_RMOL_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <list>

namespace RMOL {

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
  /** Define the capacity.
      <br>It is a double, as it allows for overbooking. */
  typedef double ResourceCapacity_T;

  /** Define the Booking Limit.
      <br>It is a double, as it allows for overbooking. */
  typedef double BookingLimit_T;

  /** Define the Bid-Price Vector.
      <br> It is a vector of double. */
  typedef std::vector<double> BidPriceVector_T;

  /** Define the list of EMSR values for the EMSR algorithm. */
  typedef std::vector<double> EmsrValueList_T;

  /** Define the vector of booking limits.
      <br> It is a vector of double. */
  typedef std::vector<double> BookingLimitVector_T;

  /** Define the sellup probability vector applicable to EMSR*/
  typedef std::vector<double> SellupProbabilityVector_T;
}
#endif // __RMOL_RMOL_TYPES_HPP
