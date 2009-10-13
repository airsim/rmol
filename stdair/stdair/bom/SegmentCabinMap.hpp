#ifndef __STDAIR_BOM_SEGMENTCABINMAP_HPP
#define __STDAIR_BOM_SEGMENTCABINMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentCabinTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class SegmentCabin;
  
  /** Structure which handles the iterators for a segment-cabin map. */
  struct SegmentCabinMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-cabin map iterators. */
    typedef BomIterator_T<SegmentCabin,
                          SegmentCabinStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<SegmentCabin,
                          SegmentCabinStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the segment-cabin holder. */
    typedef BomChildrenHolderImp<SegmentCabin> SegmentCabinHolder_T;
    
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
    SegmentCabinMap_T ();
    SegmentCabinMap_T (const SegmentCabinMap_T&);
    SegmentCabinMap_T (const SegmentCabinHolder_T&);

    /** Destructor. */
    virtual ~SegmentCabinMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const SegmentCabinHolder_T& _segmentCabinHolder;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABINMAP_HPP

