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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class BookingClass;
  
  /** Define the booking class structure. */
  typedef Structure<BookingClass> BookingClassStructure_T;
  
  /** Define the booking class holder. */
  typedef BomChildrenHolderImp<BookingClass> BookingClassHolder_T;

  /** Define the booking class list. */
  typedef BomList_T<BookingClass> BookingClassList_T;

  /** Define the booking class map. */
  typedef BomMap_T<BookingClass> BookingClassMap_T;
  
  /** Define the STL list of booking classes. */
  typedef std::vector<BookingClass*> BookingClassSTLList_T;
      
}
#endif // __STDAIR_BOM_BOOKINGCLASSTYPES_HPP

