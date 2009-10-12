#ifndef __STDAIR_BOM_SEGMENTCABINMAP_HPP
#define __STDAIR_BOM_SEGMENTCABINMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>

namespace stdair {
// Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;

  /** Structure which handles the iterators for a segment-date map. */
  struct SegmentCabinMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-date map iterators. */
    typedef BomIterator_T<SegmentCabin,
                          SegmentCabinStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<SegmentCabin,
                          SegmentCabinStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the map. */
    iterator begin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the map. */
    iterator end () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the map. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the map. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    SegmentCabinMap_T ();
    SegmentCabinMap_T (const SegmentCabinMap_T&);
    SegmentCabinMap_T (const SegmentDateStructure_T&);

    /** Destructor. */
    virtual ~SegmentCabinMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const SegmentDateStructure_T& _segmentDateStructure;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABINMAP_HPP

