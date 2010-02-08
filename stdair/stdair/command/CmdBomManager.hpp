#ifndef __STDAIR_CMD_CMDBOMMANAGER_HPP
#define __STDAIR_CMD_CMDBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace stdair {

  // Forward declarations
  class BomRoot;
  class Inventory;

  /** Class wrapping utility functions for handling the BOM tree objects. */
  class CmdBomManager : public CmdAbstract {
  public:

    /** If needed, create the Inventory corresponding to the given airline code
        (Inventory key), link it to the BomRoot object and to the
        associated AirlineFeature object, itself retrieved from the
        AirlineFeatureSet object.
        Otherwise, just retrieve the reference on the existing Inventory object
        corresponding to the given airline code.
        <br>If not existing, a ObjectNotFoundException exception is thrown.
        @param BomRoot& Root of the BOM tree.
        @param const AirlineCode_T& Airline code for the inventory to be
               created . */
    static Inventory& getOrCreateInventory (BomRoot&, const AirlineCode_T&);
      
    /** Initialise the AirlineFeatureSet object, and attach it to the
        BomRoot.
        @param BomRoot& Root of the BOM tree.  */
    static void initAirlineFeatureSet (BomRoot&);
    
    /** Add the airline-specific AirlineFeature object to its AirlineFeatureSet
        parent.
        @param BomRoot& Root of the BOM tree.
        @param const AirlineCode_T& Airline code for the inventory to be
               created . */
    static void addAirlineFeature (BomRoot&, const AirlineCode_T& iAirlineCode);
    
  private:
    // ///////////////////// Internal support methods ////////////////////////
    /** Create the Inventory corresponding to the given airline code
        (Inventory key).
        @param BomRoot& Root of the BOM tree.
        @param const AirlineCode_T& Airline code for the inventory to be
               created . */
    static Inventory& createInventoryInternal (BomRoot&, const AirlineCode_T&);
  };

}
#endif // ___STDAIR_CMD_CMDBOMMANAGER_HPP
