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
    oDebugStr << "Before unconstraining, the constrained Data are "
              << Utilities::vectorToString(ioConstrainedDataHolder) << "."
              << "Unconstrained Data are "
              << Utilities::vectorToString(iUnconstrainedDataHolder) 
              << "." ;

    // Unconstrain
    ExpectationMaximization::unconstrainData 
      (ioConstrainedDataHolder, iUnconstrainedDataHolder, iStoppingCriterion);
    
    // Debug message
    oDebugStr << "After unconstraining, the constrained Data are "
              << Utilities::vectorToString(ioConstrainedDataHolder) << ".";

    RMOL_LOG_DEBUG (oDebugStr.str());
 
  }

  // //////////////////////////////////////////////////////////////////////  

}
