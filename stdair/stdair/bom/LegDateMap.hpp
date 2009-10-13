#ifndef __STDAIR_BOM_LEGDATEMAP_HPP
#define __STDAIR_BOM_LEGDATEMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegDateTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class LegDate;
  
  /** Structure which handles the iterators for a leg-date map. */
  struct LegDateMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the leg-date map iterators. */
    typedef BomIterator_T<LegDate,
                          LegDateStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<LegDate,
                          LegDateStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the leg-date holder. */
    typedef BomChildrenHolderImp<LegDate> LegDateHolder_T;
    
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the map. */
    iterator begin () const;
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the map. */
    iterator end () const;

    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the map. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the end of the map. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    LegDateMap_T ();
    LegDateMap_T (const LegDateMap_T&);
    LegDateMap_T (const LegDateHolder_T&);

    /** Destructor. */
    virtual ~LegDateMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const LegDateHolder_T& _legDateHolder;
  };

}
#endif // __STDAIR_BOM_LEGDATEMAP_HPP

