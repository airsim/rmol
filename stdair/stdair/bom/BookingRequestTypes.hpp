// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOOKINGCLASSTYPES_HPP
#define __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations.
  struct BookingRequestStruct;
  
      // Type definitions.
  /** Define the smart pointer to a booking request. */
  typedef boost::shared_ptr<BookingRequestStruct> BookingRequestPtr_T;
  
}
#endif // __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

