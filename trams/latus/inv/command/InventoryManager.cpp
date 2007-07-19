// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_WorldSchedule.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/factory/FacWorldSchedule.hpp>
#include <latus/com/command/FileMgr.hpp>
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

      // Initialise the BookingDay object, which is the main entry point
      // for the demand-related event generation.
      _worldSchedule = &COM::FacWorldSchedule::instance().
        create (COM::DEFAULT_WORLD_SCHEDULE_UPDATE_DATE);
      assert (_worldSchedule != NULL);
      
      // Read input data and parameters from a CSV-type file
      const bool hasFileBeenRead = 
        COM::FileMgr::readAndProcessWorldScheduleInputFile (_inputFileName,
                                                            *_worldSchedule);
      if (hasFileBeenRead == false) {
        LATUS_LOG_ERROR ("Can not parse the \"" << _inputFileName 
                         << "\" file (hint: check that it exists).");
        return false;
      }

      return true;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void InventoryManager::display () const {
      const COM::WorldSchedule& lWorldSchedule = getWorldScheduleRef();
      lWorldSchedule.display();
    }

    // //////////////////////////////////////////////////////////////////////
    void InventoryManager::
    provideAvailabilities (const COM::SegmentDateStruct_T& iOnD,
                           COM::TravelSolutionList_T& ioTSL) const {

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
    bool InventoryManager::sell (const COM::TravelSolutionList_T& iTS,
                                 const COM::BookingNumber_T& iPartySize) {
      return true;
    }

  }

}
