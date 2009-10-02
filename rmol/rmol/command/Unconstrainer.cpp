// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// #include <fstream>
// RMOL
#include <rmol/service/Logger.hpp>
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/command/Utilities.hpp>
#include <rmol/command/Unconstrainer.hpp>
#include <rmol/bom/ExpectationMaximization.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void Unconstrainer::dataUnconstrainByExpectationMaximization 
  (ConstrainedDataHolder_T& ioConstrainedDataHolder, 
   UnconstrainedDataHolder_T& iUnconstrainedDataHolder,
   StoppingCriterion_T& iStoppingCriterion) {
    
    // Debug message
    std::ostringstream oDebugStr;
    oDebugStr << "\nProvided unconstrained data:  "
              << Utilities::vectorToString(iUnconstrainedDataHolder)
              << "Constrained data: "
              << Utilities::vectorToString(ioConstrainedDataHolder);

    // Unconstrain
    ExpectationMaximization::unconstrainData 
      (ioConstrainedDataHolder, iUnconstrainedDataHolder, iStoppingCriterion);
    
    // Debug message
    oDebugStr << "After unconstraining, the constrained data became "
              << Utilities::vectorToString(ioConstrainedDataHolder);

    RMOL_LOG_DEBUG (oDebugStr.str());
 
  }

  // //////////////////////////////////////////////////////////////////////  

}
