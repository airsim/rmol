// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOOKINGCLASSTYPES_HPP
#define __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class BookingClass;

  /** Define the booking class list. */
  typedef std::list<BookingClass*> BookingClassList_T;

  /** Define the booking class map. */
  typedef std::map<const MapKey_T, BookingClass*> BookingClassMap_T;      
}
#endif // __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

