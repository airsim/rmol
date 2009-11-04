#ifndef __STDAIR_BOM_FLIGHTDATEMAP_HPP
#define __STDAIR_BOM_FLIGHTDATEMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/FlightDateTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class FlightDate;
  
  /** Structure which handles the iterators for a flight-date map. */
  struct FlightDateMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the flight-date map iterators. */
    typedef BomIterator_T<FlightDate,
                          FlightDateStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<FlightDate,
                          FlightDateStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the flight-date holder. */
    typedef BomChildrenHolderImp<FlightDate> FlightDateHolder_T;
    
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

    /** Retrieve, if existing, the FlightDate corresponding to the
        given key. */
    iterator find (const MapKey_T&) const;
    
  public:
    /** Default constructors. */
    FlightDateMap_T ();
    FlightDateMap_T (const FlightDateMap_T&);
    FlightDateMap_T (const FlightDateHolder_T&);

    /** Destructor. */
    virtual ~FlightDateMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const FlightDateHolder_T& _flightDateHolder;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATEMAP_HPP

