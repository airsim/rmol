// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <exception>
// StdAir
//#include <stdair/bom/YieldStore.hpp>
#include <stdair/service/Logger.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>
#include <airrac/command/YieldManager.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  void YieldManager::
  calculateYield (stdair::TravelSolutionStruct& iTravelSolution,
                  const stdair::BomRoot& iBomRoot) {

      
      // Calculate/retrieve the yield for the given travel solution
      //YieldStore::calculateYield (ioYield, iTravelSolution);

      // TODO: update the statistical attributes of the yield.
    
  }

}
