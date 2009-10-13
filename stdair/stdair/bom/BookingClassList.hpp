#ifndef __STDAIR_BOM_BOOKINGCLASSLIST_HPP
#define __STDAIR_BOM_BOOKINGCLASSLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class BookingClass;
  
  /** Structure which handles the iterators for a booking class list. */
  struct BookingClassList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the booking class list iterators. */
    typedef BomIterator_T<BookingClass,
                          BookingClassStructureList_T::const_iterator> iterator;
    typedef BomIterator_T<BookingClass,
                          BookingClassStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the booking class holder. */
    typedef BomChildrenHolderImp<BookingClass> BookingClassHolder_T;
    
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the list. */
    iterator begin () const;
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the list. */
    iterator end () const;

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    BookingClassList_T ();
    BookingClassList_T (const BookingClassList_T&);
    BookingClassList_T (const BookingClassHolder_T&);

    /** Destructor. */
    virtual ~BookingClassList_T();

  private:
    // Attributes
    /** Reference structure. */
    const BookingClassHolder_T& _bookingClassHolder;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSLIST_HPP

