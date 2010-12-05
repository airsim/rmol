#ifndef __MYPROVIDER_INVENTORY_HPP
#define __MYPROVIDER_INVENTORY_HPP
/*!
 * \page test_archi_inv_hpp Specific Implementation of an Airline Inventory
 * \code
 */

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// StdAir
#include <stdair/bom/Inventory.hpp>

namespace myprovider {
  
  class Inventory : public stdair::Inventory {
  public:
    // /////////// Display support methods /////////
    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;
    
  public:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    Inventory (const Key_T&);
    /** Destructor. */
    ~Inventory();
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
  };
  
  // ////////// Type definitions /////////
  /** Type for the list of inventories. */
  typedef std::list<Inventory*> InventoryList_T;
  
}
/*!
 * \endcode
 */
#endif // __MYPROVIDER_INVENTORY_HPP
