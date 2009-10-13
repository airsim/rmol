#ifndef __STDAIR_BOM_SEGMENTDATELIST_HPP
#define __STDAIR_BOM_SEGMENTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentDateTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class SegmentDate;
  
  /** Structure which handles the iterators for a segment-date list. */
  struct SegmentDateList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-date list iterators. */
    typedef BomIterator_T<SegmentDate,
                          SegmentDateStructureList_T::const_iterator> iterator;
    typedef BomIterator_T<SegmentDate,
                          SegmentDateStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the segment-date holder. */
    typedef BomChildrenHolderImp<SegmentDate> SegmentDateHolder_T;
    
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the list. */
    iterator begin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the list. */
    iterator end () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    SegmentDateList_T ();
    SegmentDateList_T (const SegmentDateList_T&);
    SegmentDateList_T (const SegmentDateHolder_T&);

    /** Destructor. */
    virtual ~SegmentDateList_T();

  private:
    // Attributes
    /** Reference structure. */
    const SegmentDateHolder_T& _segmentDateHolder;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATELIST_HPP

