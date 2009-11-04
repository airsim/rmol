#ifndef __STDAIR_BOM_BOOKINGCLASSMAP_HPP
#define __STDAIR_BOM_BOOKINGCLASSMAP_HPP

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
  
  /** Structure which handles the iterators for a booking class map. */
  struct BookingClassMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the booking class map iterators. */
    typedef BomIterator_T<BookingClass,
                          BookingClassStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<BookingClass,
                          BookingClassStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the booking class holder. */
    typedef BomChildrenHolderImp<BookingClass> BookingClassHolder_T;
    
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the map. */
    iterator begin () const;
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the map. */
    iterator end () const;

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the map. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the map. */
    reverse_iterator rend () const;

     /** Retrieve, if existing, the BookingClass corresponding to the
        given key. */
    iterator find (const MapKey_T&) const;

  public:
    /** Default constructors. */
    BookingClassMap_T ();
    BookingClassMap_T (const BookingClassMap_T&);
    BookingClassMap_T (const BookingClassHolder_T&);

    /** Destructor. */
    virtual ~BookingClassMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const BookingClassHolder_T& _bookingClassHolder;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSMAP_HPP

