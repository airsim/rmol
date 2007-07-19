#ifndef __LATUS_CRS_CMD_INVENTORYMANAGER_HPP
#define __LATUS_CRS_CMD_INVENTORYMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace COM {
    // Forward declarations
    class WorldSchedule;
  }

  namespace INV {

    /** Class wrapping the distribution methods. */
    class InventoryManager : COM::CmdAbstract {
      // Only LATUS_INV can instantiate InventoryManager
      friend class LATUS_INV;
    public:
      // /////////// GETTERS //////////
      /** Get a reference on the (child) WorldSchedule object. */
      COM::WorldSchedule* getWorldSchedule() const {
        return _worldSchedule;
      }

      /** Get a reference on the (child) WorldSchedule object. */
      COM::WorldSchedule& getWorldScheduleRef() const {
        assert (_worldSchedule != NULL);
        return *_worldSchedule;
      }

      // /////////// SETTERS //////////

      
      // ////////// Main Methods ///////////      
      /** Calculate and return the availabilities corresponding to a given
          product.
          @return The vector of Travel Solutions (TS). */
      void provideAvailabilities (const COM::SegmentDateStruct_T& iOnD,
                                  COM::TravelSolutionList_T& ioTSL) const;

      /** Register the sell of a given number of travellers on a given
          Travel Solution.
          <br>The party size may be a floating number, so as to cope with
          overbooking. */
      bool sell (const COM::TravelSolutionList_T& iTS,
                 const COM::BookingNumber_T& iPartySize);


      // ///////// DISPLAY METHODS /////////
      /** Display the BOM objects. */
      void display () const;

      
    private:
      /** Constructors. */
      InventoryManager (const std::string& iInputFileName);
      
      /** Destructor. */
      virtual ~InventoryManager();

    private:
      /** Build the BOM thanks to the input file.
          <br>The BOM is composed of objects. */
      bool init ();

    private:
      // Filename of the input file (for test purposes)
      std::string _inputFileName;

      // BOM (the WorldSchedule class is the entry point to the BOM)
      COM::WorldSchedule* _worldSchedule;
    };

  }
}
#endif // __LATUS_CRS_CMD_INVENTORYMANAGER_HPP
