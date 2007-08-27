#ifndef __LATUS_COM_FAC_FACINVENTORY_HPP
#define __LATUS_COM_FAC_FACINVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    struct InventoryKey_T;
    class Inventory;
    class FlightDate;
    
    /** Factory for Inventory objects. */
    class FacInventory : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacInventory& */
      static FacInventory& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacInventory::instance() */
      virtual ~FacInventory();

      /** Create a new Inventory object.
          <br>This new object is added to the list of instantiated objects.
          @param const InventoryKey_T&.
          @return Inventory& The newly created object. */
      Inventory& create (const InventoryKey_T&);

      /** Initialise the link between a Inventory and a Schedule.
          @param Inventory&
          @param FlightDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithFlightDate (Inventory&, FlightDate&);

      /** Create the routing between the legs and segments for all the
          FlightDates of the given Inventory object. */
      static void createRouting (Inventory& ioInventory);

      
    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacInventory () {}

    private:
      /** The unique instance.*/
      static FacInventory* _instance;
    };

  }

}

#endif // __LATUS_COM_FAC_FACINVENTORY_HPP
