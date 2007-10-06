// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/Logger.hpp>
#include <latus/com/basic/BasConst_TravelSolution.hpp>

// LATUS CRS
#include <latus/crs/command/Distributor.hpp>

namespace LATUS {

  namespace CRS {

    // //////////////////////////////////////////////////////////////////////
    Distributor::Distributor (const std::string& iInputFileName)
      : _inputFileName (iInputFileName), _worldSchedule (NULL) {

      // Read the input file and build the CityPairList
      const bool hasSucceeded = init();
      assert (hasSucceeded == true);
    }
      
    // //////////////////////////////////////////////////////////////////////
    Distributor::~Distributor() {
    }
    
    // //////////////////////////////////////////////////////////////////////
    bool Distributor::init () {
      return true;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Distributor::display () const {
    }

    // //////////////////////////////////////////////////////////////////////
    void Distributor::
    provideAvailabilities (COM::TravelSolution& iTraSol,
                           const COM::SeatNumber_T& iSN) {
      
      bool tsAvailability = iTraSol.buildCheapestAvailableSolution(iSN);
      if (tsAvailability == true) {
        iTraSol.calculateAvailabilities();
      }
      else {        
        iTraSol.setTSAvailability (COM::DEFAULT_CLASS_AVAILABILITY);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    bool Distributor::sell (const COM::TravelSolution& iTS,
                            const COM::BookingNumber_T& iPS) {

     
      return true;
    }

  }

}
