#ifndef __STDAIR_BOM_AIRLINEFEATURELIST_HPP
#define __STDAIR_BOM_AIRLINEFEATURELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/AirlineFeatureTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class AirlineFeature;
  
  /** Structure which handles the iterators for a booking class list. */
  struct AirlineFeatureList_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the booking class list iterators. */
    typedef BomIterator_T<AirlineFeature,
                          AirlineFeatureStructureList_T::const_iterator> iterator;
    typedef BomIterator_T<AirlineFeature,
                          AirlineFeatureStructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the booking class holder. */
    typedef BomChildrenHolderImp<AirlineFeature> AirlineFeatureHolder_T;
    
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
    AirlineFeatureList_T ();
    AirlineFeatureList_T (const AirlineFeatureList_T&);
    AirlineFeatureList_T (const AirlineFeatureHolder_T&);

    /** Destructor. */
    virtual ~AirlineFeatureList_T();

  private:
    // Attributes
    /** Reference structure. */
    const AirlineFeatureHolder_T& _airlineFeatureHolder;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURELIST_HPP

