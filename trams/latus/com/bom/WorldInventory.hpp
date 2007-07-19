#ifndef __LATUS_COM_BOM_WORLDINVENTORY_HPP
#define __LATUS_COM_BOM_WORLDINVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/InventoryList.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the inventories of all the available airlines. */
    class WorldInventory : public BomAbstract {
      friend class FacWorldInventory;
    public:

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      WorldInventory (); 

      /** Destructor. */
      virtual ~WorldInventory();

      /** Get the list of (children) WorldInventory objects. */
      const InventoryList_T& getInventoryList () const {
        return _inventoryList;
      }

      /** Retrieve, if existing, the WorldInventory corresponding to the
          given departure date.
          <br>If not existing, return the NULL pointer. */
      Inventory* getInventory (const std::string& iDescription) const;
      
    private:
      // Attributes
      /** Children: list of Inventory objects. */
      InventoryList_T _inventoryList;


    };

  }

}

#endif // __LATUS_COM_BOM_WORLDINVENTORY_HPP
