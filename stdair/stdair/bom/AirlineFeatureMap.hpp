#ifndef __STDAIR_BOM_AIRLINEFEATUREMAP_HPP
#define __STDAIR_BOM_AIRLINEFEATUREMAP_HPP

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
  
  /** Structure which handles the iterators for a booking class map. */
  struct AirlineFeatureMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the booking class map iterators. */
    typedef BomIterator_T<AirlineFeature,
                          AirlineFeatureStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<AirlineFeature,
                          AirlineFeatureStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the booking class holder. */
    typedef BomChildrenHolderImp<AirlineFeature> AirlineFeatureHolder_T;
    
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

    /** Retrieve, if existing, the AirlineFeature corresponding to the
        given key. */
    iterator find (const MapKey_T&) const;

  public:
    /** Default constructors. */
    AirlineFeatureMap_T ();
    AirlineFeatureMap_T (const AirlineFeatureMap_T&);
    AirlineFeatureMap_T (const AirlineFeatureHolder_T&);

    /** Destructor. */
    virtual ~AirlineFeatureMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const AirlineFeatureHolder_T& _airlineFeatureHolder;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATUREMAP_HPP

