// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BOOKINGCLASSTYPES_HPP
#define __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class BookingClassStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class BookingClass;
  
  /** Define the booking class structure. */
  typedef BookingClassStructure<BookingClass> BookingClassStructure_T;
  
  /** Define the booking class structure list. */
  typedef std::vector<BookingClassStructure_T*> BookingClassStructureList_T;

  /** Define the booking class structure map. */
  typedef std::map<const std::string, BookingClassStructure_T*> BookingClassStructureMap_T;

  /** Define the booking class list. */
  typedef BomList_T<BookingClass> BookingClassList_T;

  /** Define the booking class map. */
  typedef BomMap_T<BookingClass> BookingClassMap_T;
}
#endif // __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

