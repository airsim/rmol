#ifndef __STDAIR_BOM_BOOKINGCLASSMAP_HPP
#define __STDAIR_BOM_BOOKINGCLASSMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
// Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;

  /** Structure which handles the iterators for a segment-cabin map. */
  struct BookingClassMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-cabin map iterators. */
    typedef BomIterator_T<BookingClass,
                          BookingClassStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<BookingClass,
                          BookingClassStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on segment cabin:
        return the iterator at the begining of the map. */
    iterator begin () const;
    
    /** Initialise the internal iterator on segment cabin:
        return the iterator at the end of the map. */
    iterator end () const;

    /** Initialise the internal reverse iterator on segment cabin:
        return the reverse iterator at the rbegining of the map. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on segment cabin:
        return the reverse iterator at the end of the map. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    BookingClassMap_T ();
    BookingClassMap_T (const BookingClassMap_T&);
    BookingClassMap_T (const SegmentCabinStructure_T&);

    /** Destructor. */
    virtual ~BookingClassMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const SegmentCabinStructure_T& _segmentCabinStructure;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSMAP_HPP

