#ifndef __STDAIR_BOM_FLIGHTDATEMAP_HPP
#define __STDAIR_BOM_FLIGHTDATEMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightDateTypes.hpp>

namespace stdair {
// Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;

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

  public:
    /** Default constructors. */
    FlightDateMap_T ();
    FlightDateMap_T (const FlightDateMap_T&);
    FlightDateMap_T (const InventoryStructure_T&);

    /** Destructor. */
    virtual ~FlightDateMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const InventoryStructure_T& _inventoryStructure;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATEMAP_HPP

