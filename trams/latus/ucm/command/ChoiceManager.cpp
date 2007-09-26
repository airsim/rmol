// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/SegmentDateKey.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS User Choice
#include <latus/ucm/command/ChoiceManager.hpp>

namespace LATUS {

  namespace UCM {

    // //////////////////////////////////////////////////////////////////////
    void ChoiceManager::
    chooseTravelSolution (const COM::AirportCode_T& iOrigin,
                          const COM::AirportCode_T& iDestination,
                          const COM::DateTime_T& iDate,
                          COM::TravelSolutionKeyList_T& ioTSL) {
      // DEBUG
      LATUS_LOG_DEBUG ("Fare Quote for " << iOrigin << "-" << iDestination
                       << " " << iDate << " and: ");
      for (COM::TravelSolutionKeyList_T::const_iterator itTravelSolution =
           ioTSL.begin();
           itTravelSolution != ioTSL.end(); ++itTravelSolution) {
        const COM::OutboundPathKey_T& lTravelSolutionKey = *itTravelSolution;
      }
    }

  }
}
