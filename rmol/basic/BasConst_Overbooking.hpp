#ifndef __RMOL_BAS_BASCONST_OVERBOOKING_HPP
#define __RMOL_BAS_BASCONST_OVERBOOKING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace RMOL {

  /** Default value for the load factor used for overbooking calculation. */
  extern const double DEFAULT_OVERBOOKING_LOAD_FACTOR;

  /** Default value for the capacity used for overbooking calculation. */
  extern const unsigned int DEFAULT_OVERBOOKING_CAPACITY;
  
  /** Default value for the net bookings used for overbooking calculation. */
  extern const unsigned int DEFAULT_OVERBOOKING_NET_BOOKINGS;
  
  /** Default value for the overbooking used for overbooking calculation. */
  extern const double DEFAULT_OVERBOOKING_OVERBOOKING_PERCENTAGE;

  /** Default value for the mean used for overbooking calculation. */
  extern const double DEFAULT_OVERBOOKING_MEAN;

  /** Default value for the standard deviation used for overbooking
      calculation. */
  extern const double DEFAULT_OVERBOOKING_STANDARD_DEVIATION;

}
#endif // __RMOL_BAS_BASCONST_OVERBOOKING_HPP
