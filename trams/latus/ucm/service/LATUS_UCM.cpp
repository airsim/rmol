// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS UCM
#include <latus/ucm/command/ChoiceManager.hpp>
#include <latus/ucm/service/LATUS_UCM.hpp>

namespace LATUS {

  namespace UCM {

    // //////////////////////////////////////////////////////////////////////
    LATUS_UCM::LATUS_UCM () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_UCM::~LATUS_UCM () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_UCM::
    chooseTravelSolution (const COM::AirportCode_T& iOrigin,
                          const COM::AirportCode_T& iDestination,
                          const COM::DateTime_T& iDate,
                          COM::TravelSolutionKeyList_T& ioTSL) {

      ChoiceManager::chooseTravelSolution (iOrigin, iDestination, iDate, ioTSL);
    }

  }
}
