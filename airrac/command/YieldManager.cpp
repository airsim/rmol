// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
//#include <stdair/bom/YieldStore.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/service/Logger.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>
#include <airrac/command/YieldManager.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  YieldManager::YieldManager() {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  YieldManager::YieldManager (const YieldManager&) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  YieldManager::~YieldManager() {
  }

  // //////////////////////////////////////////////////////////////////////
  void YieldManager::
  calculateYield (stdair::TravelSolutionList_T& ioTravelSolutionList,
                  const stdair::BomRoot& iBomRoot) {

    // Browse the list of TravelSolution structures
    for (stdair::TravelSolutionList_T::iterator itTravelSolution =
           ioTravelSolutionList.begin();
         itTravelSolution != ioTravelSolutionList.end(); ++itTravelSolution) {
      stdair::TravelSolutionStruct& lTravelSolution = *itTravelSolution;
      
      //
      YieldManager::calculateYield (lTravelSolution, iBomRoot);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void YieldManager::
  calculateYield (stdair::TravelSolutionStruct& ioTravelSolution,
                  const stdair::BomRoot& iBomRoot) {

    // Calculate/retrieve the yield for the given travel solution
    //YieldStore::calculateYield (ioYield, ioTravelSolution);

    // TODO: update the statistical attributes of the yield.
  }

}
