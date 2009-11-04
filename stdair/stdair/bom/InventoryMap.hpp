#ifndef __STDAIR_BOM_INVENTORYMAP_HPP
#define __STDAIR_BOM_INVENTORYMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/InventoryTypes.hpp>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_STRUCTURE> class BomChildrenHolderImp;
  class Inventory;
  
  /** Structure which handles the iterators for a inventory map. */
  struct InventoryMap_T {

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the inventory map iterators. */
    typedef BomIterator_T<Inventory,
                          InventoryStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<Inventory,
                          InventoryStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
    
    /** Define the inventory holder. */
    typedef BomChildrenHolderImp<Inventory> InventoryHolder_T;
    
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
    
    /** Retrieve, if existing, the Inventory corresponding to the
        given key. */
    iterator find (const MapKey_T&) const;

  public:
    /** Default constructors. */
    InventoryMap_T ();
    InventoryMap_T (const InventoryMap_T&);
    InventoryMap_T (const InventoryHolder_T&);

    /** Destructor. */
    virtual ~InventoryMap_T();

  private:
    // Attributes
    /** Reference structure. */
    const InventoryHolder_T& _inventoryHolder;
  };

}
#endif // __STDAIR_BOM_INVENTORYMAP_HPP

