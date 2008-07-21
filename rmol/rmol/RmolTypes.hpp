#ifndef __RMOL_RMOLTYPES_HPP
#define __RMOL_RMOLTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <list>

namespace RMOL {

  /** Define the capacity.
      <br>It is a double, as it allows for overbooking. */
  typedef double ResourceCapacity_T;

  /** Define the Booking Limit.
      <br>It is a double, as it allows for overbooking. */
  typedef double BookingLimit_T;

  /** Define the Bid-Price Vector.
      <br> It is a vector of double. */
  typedef std::vector<double> BidPriceVector_T;

  /** Define the list of EMSR values for the EMSR algorith. */
  typedef std::list<double> EmsrValueList_T;

  /** Define the vector of booking limits.
      <br> It is a vector of double. */
  typedef std::vector<double> BookingLimitVector_T;

}
#endif // __RMOL_RMOLTYPES_HPP
