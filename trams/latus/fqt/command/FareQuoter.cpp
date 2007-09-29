// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/TravelSolutionList.hpp>
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS Fare Quote
#include <latus/fqt/command/FareQuoter.hpp>

namespace LATUS {

  namespace FQT {

    // //////////////////////////////////////////////////////////////////////
    void FareQuoter::
    quoteTravelSolutions (COM::TravelSolutionBlock& ioTSL) {
      
      const COM::TravelSolutionList_T& lTravelSolutionList = ioTSL.getTravelSolutionList();
      
       for (COM::TravelSolutionList_T::const_iterator itTravelSolution =
             lTravelSolutionList.begin();
           itTravelSolution != lTravelSolutionList.end(); ++itTravelSolution) {
        COM::TravelSolution* lTravelSolution_ptr = itTravelSolution->second;
        assert (lTravelSolution_ptr != NULL);
        
        lTravelSolution_ptr->fareQuote();
      }
    }

  }
}
