#ifndef __LATUS_COM_FAC_FACWORLDINVENTORY_HPP
#define __LATUS_COM_FAC_FACWORLDINVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class WorldInventory;
    class Inventory;
    
    /** Factory for WorldInventory objects. */
    class FacWorldInventory : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacWorldInventory& */
      static FacWorldInventory& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacWorldInventory::instance() */
      virtual ~FacWorldInventory();

      /** Create a new WorldInventory object.
          <br>This new object is added to the list of instantiated objects.
          @return WorldInventory& The newly created object. */
      WorldInventory& create ();

      /** Initialise the link between a WorldInventory and a Inventory.
          @param WorldInventory&
          @param Inventory&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithInventory (WorldInventory&, Inventory&);

      /** Create a new LegCabin object with the given parameters.
          <br>This new object is added to the list of instantiated objects.
          <br>Any missing intermediary object (Inventory and/or FlightDate)
          will be created and added to the corresponding children list. */
      static void createLegCabin (WorldInventory&,
                                  const AirlineCode_T&, const FlightNumber_T&,
                                  const AirportCode_T&, const AirportCode_T&,
                                  const DateTime_T&, const CabinCode_T&);
      

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacWorldInventory () {}

    private:
      /** The unique instance.*/
      static FacWorldInventory* _instance;
    };

  }

}

#endif // __LATUS_COM_FAC_FACWORLDINVENTORY_HPP
