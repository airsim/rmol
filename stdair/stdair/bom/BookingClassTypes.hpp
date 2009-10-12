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
  template <typename BOM_CONTENT> class BookingClassKey;
  class BookingClass;
  
  /** Define the BookingClass structure. */
  typedef BookingClassStructure<BookingClass> BookingClassStructure_T;
  
  /** Define the BookingClass key. */
  typedef BookingClassKey<BookingClass> BookingClassKey_T;
  
  /** Define the segment-cabin structure list. */
  typedef std::vector<BookingClassStructure_T*> BookingClassStructureList_T;

  /** Define the segment-cabin structure map. */
  typedef std::map<const std::string, BookingClassStructure_T*> BookingClassStructureMap_T;

}
#endif // __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

