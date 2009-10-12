#ifndef __STDAIR_BOM_LEGCABINMAP_HPP
#define __STDAIR_BOM_LEGCABINMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {
// Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;

  /** Structure which handles the iterators for a leg-date map. */
  struct LegCabinMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the leg-date map iterators. */
    typedef BomIterator_T<LegCabin,
                          LegCabinStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<LegCabin,
                          LegCabinStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////

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
    LegCabinMap_T ();
    LegCabinMap_T (const LegCabinMap_T&);
    LegCabinMap_T (const LegDateStructure_T&);

    /** Destructor. */
    virtual ~LegCabinMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const LegDateStructure_T& _legDateStructure;
  };

}
#endif // __STDAIR_BOM_LEGCABINMAP_HPP

