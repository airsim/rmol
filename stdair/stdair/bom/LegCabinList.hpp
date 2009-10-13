#ifndef __STDAIR_BOM_LEGCABINLIST_HPP
#define __STDAIR_BOM_LEGCABINLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class LegCabin;
  
  /** Structure which handles the iterators for a leg-cabin list. */
  struct LegCabinList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the leg-cabin list iterators. */
    typedef BomIterator_T<LegCabin,
                          LegCabinStructureList_T::const_iterator> iterator;
    typedef BomIterator_T<LegCabin,
                          LegCabinStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the leg-cabin holder. */
    typedef BomChildrenHolderImp<LegCabin> LegCabinHolder_T;
    
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on leg cabin:
        return the iterator at the begining of the list. */
    iterator begin () const;
    
    /** Initialise the internal iterator on leg cabin:
        return the iterator at the end of the list. */
    iterator end () const;

    /** Initialise the internal reverse iterator on leg cabin:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const;
    
    /** Initialise the internal reverse iterator on leg cabin:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const;

  public:
    /** Default constructors. */
    LegCabinList_T ();
    LegCabinList_T (const LegCabinList_T&);
    LegCabinList_T (const LegCabinHolder_T&);

    /** Destructor. */
    virtual ~LegCabinList_T();

  private:
    // Attributes
    /** Reference structure. */
    const LegCabinHolder_T& _legCabinHolder;
  };

}
#endif // __STDAIR_BOM_LEGCABINLIST_HPP

