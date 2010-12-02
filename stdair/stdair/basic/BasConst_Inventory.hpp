#ifndef __STDAIR_BAS_BASCONST_INVENTORY_HPP
#define __STDAIR_BAS_BASCONST_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_types.hpp>

namespace stdair {

  // //////// Inventory-related BOM ///////
  /** Default Bid-Price. */
  extern const BidPrice_T DEFAULT_BID_PRICE;

  /** Default Bid-Price Vector. */
  extern const BidPriceVector_T DEFAULT_BID_PRICE_VECTOR;

  /** Maximal number of legs linked to a single flight-date.
      <br>Note that the number of derived segments is n*(n+1)/2 if n
      is the number of legs. */
  extern const unsigned short MAXIMAL_NUMBER_OF_LEGS_IN_FLIGHT;
  
  /** Maximal number of segments linked to a single O&D
      (Origin & Destination). */
  extern const unsigned short MAXIMAL_NUMBER_OF_SEGMENTS_IN_OND;

  /** Maximal offered capacity in a cabin. */
  extern const Availability_T MAXIMAL_AVAILABILITY;
    
}
#endif // __STDAIR_BAS_BASCONST_INVENTORY_HPP
