// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS INV
#include <latus/inv/command/InventoryManager.hpp>

namespace LATUS {

  namespace INV {

    // //////////////////////////////////////////////////////////////////////
    InventoryManager::InventoryManager (const std::string& iInputFileName)
      : _worldSchedule (NULL), _inputFileName (iInputFileName) {

      // Read the input file and build the CityPairList
      const bool hasSucceeded = init();
      assert (hasSucceeded == true);
    }
      
    // //////////////////////////////////////////////////////////////////////
    InventoryManager::~InventoryManager() {
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool InventoryManager::init () {
      return true;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryManager::display () const {
    }

    // //////////////////////////////////////////////////////////////////////
    void InventoryManager::
    provideAvailabilities (const COM::SegmentDateKey_T& iOnD,
                           COM::TravelSolutionKeyList_T& ioTSL) const {

      // TODO: Remove the hard coding
      // Hard-code a few TSL
      const COM::AirportCode_T lMUC ("MUC");
      const COM::AirportCode_T lMIA ("MIA");
      const COM::AirportCode_T lLAX ("LAX");
      const COM::CabinCode_T lSHBusiness ("C");
      const COM::CabinCode_T lSHEconomy ("M");
      const COM::CabinCode_T lFirst ("F");
      const COM::CabinCode_T lLHBusiness ("J");
      const COM::CabinCode_T lTravelPlus ("W");
      const COM::CabinCode_T lLHEconomy ("M");
    }

    // //////////////////////////////////////////////////////////////////////
    bool InventoryManager::sell (const COM::TravelSolutionKeyList_T& iTS,
                                 const COM::BookingNumber_T& iPartySize) {
      return true;
    }

  }

}
