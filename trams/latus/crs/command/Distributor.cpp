// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/WorldInventory.hpp>
#include <latus/com/factory/FacWorldInventory.hpp>
// LATUS CRS
#include <latus/crs/cmd/Distributor.hpp>

namespace LATUS {

  namespace CRS {

    // //////////////////////////////////////////////////////////////////////
    Distributor::Distributor (const std::string& iInputFileName)
      : _worldInventory (NULL), _inputFileName (iInputFileName) {

      // Read the input file and build the CityPairList
      const bool hasSucceeded = init();
      assert (hasSucceeded == true);
    }
      
    // //////////////////////////////////////////////////////////////////////
    Distributor::~Distributor() {
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool Distributor::init () {

      // Initialise the BookingDay object, which is the main entry point
      // for the demand-related event generation.
      _worldInventory = &COM::FacWorldInventory::instance().create ();
      assert (_worldInventory != NULL);
      
      // Read input data and parameters from a CSV-type file
      const bool hasFileBeenRead = 
        COM::FileMgr::readAndProcessWorldInventoryInputFile (_inputFileName,
                                                            *_worldInventory);
      if (hasFileBeenRead == false) {
        LATUS_LOG_ERROR ("Can not parse the \"" << _inputFileName 
                         << "\" file (hint: check that it exists).");
        return false;
      }

      return true;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Distributor::display () const {
      const COM::WorldInventory& lWorldInventory = getWorldInventoryRef();
      lWorldInventory.display();
    }

    // //////////////////////////////////////////////////////////////////////
    void Distributor::
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
    bool Distributor::sell (const COM::TravelSolutionList_T& iTS,
                            const COM::BookingNumber_T& iPartySize) {
      return true;
    }

  }

}
