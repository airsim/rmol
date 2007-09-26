// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS CRS
#include <latus/crs/command/Distributor.hpp>

namespace LATUS {

  namespace CRS {

    // //////////////////////////////////////////////////////////////////////
    Distributor::Distributor (const std::string& iInputFileName)
      : _worldSchedule (NULL), _inputFileName (iInputFileName) {

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
    provideAvailabilities (const COM::SegmentDateKey_T& iOnD,
                           COM::TravelSolutionKeyList_T& ioTSL) const {

    }

    // //////////////////////////////////////////////////////////////////////
    bool Distributor::sell (const COM::TravelSolutionKeyList_T& iTS,
                            const COM::BookingNumber_T& iPartySize) {

      // const TravelSolutionKey_T* iTravelSolutionKey_ptr = NULL;
        
      // if (iTS.size() == 0) {
      //  return iTravelSolutionKey_ptr;
      // }
      return true;
    }

  }

}
