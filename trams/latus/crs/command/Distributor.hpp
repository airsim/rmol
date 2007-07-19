#ifndef __LATUS_CRS_CMD_DISTRIBUTOR_HPP
#define __LATUS_CRS_CMD_DISTRIBUTOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/cmd/CmdAbstract.hpp>

namespace LATUS {

  namespace CRS {

    /** Class wrapping the distribution methods. */
    class Distributor : CmdAbstract {
      // Only LATUS_CRS can instantiate Simulator
      friend class LATUS_CRS;
    public:
      // /////////// GETTERS //////////
      /** Get a reference on the (child) BookingDay object. */
      COM::WorldInventory* getWorldInventory() const {
        return _worldInventory;
      }

      /** Get a reference on the (child) WorldInventory object. */
      COM::WorldInventory& getWorldInventoryRef() const {
        assert (_worldInventory != NULL);
        return *_worldInventory;
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
      Distributor (const std::string& iInputFileName);
      
      /** Destructor. */
      virtual ~Distributor();

    private:
      /** Build the BOM thanks to the input file.
          <br>The BOM is composed of objects. */
      bool init ();

    private:
      // Filename of the input file (for test purposes)
      std::string _inputFileName;

      // BOM (the WorldInventory class is the entry point to the BOM)
      COM::WorldInventory* _worldInventory;
    };

  }
}
#endif // __LATUS_CRS_CMD_DISTRIBUTOR_HPP
