// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS Fare Quote
#include <latus/fqt/command/FareQuoter.hpp>

namespace LATUS {

  namespace FQT {

    // //////////////////////////////////////////////////////////////////////
    void FareQuoter::
    quoteTravelSolutions (const COM::AirportDate& ioAirportDate,
                          COM::TravelSolutionKeyList_T& ioTSL) {
      
      for (COM::TravelSolutionKeyList_T::const_iterator itTravelSolution =
           ioTSL.begin();
           itTravelSolution != ioTSL.end(); ++itTravelSolution) {
        const COM::OutboundPathKey_T& lTravelSolutionKey = *itTravelSolution;

        COM::OutboundPath* lOutboundPath_ptr = ioAirportDate.
          getOutboundPath(lTravelSolutionKey.describeShort());
        lOutboundPath_ptr->fareQuote();
        
      }
    }

  }
}
