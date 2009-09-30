// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
# include <math.h>
// RMOL
#include <rmol/service/Logger.hpp>
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/command/Utilities.hpp>
#include <rmol/bom/ExpectationMaximization.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void ExpectationMaximization::unconstrainData 
  (ConstrainedDataHolder_T& ioConstrainedDataHolder, 
   UnconstrainedDataHolder_T& iUnconstrainedDataHolder,
   StoppingCriterion_T& iStoppingCriterion) {
    
    if (iStoppingCriterion <= 0) {
      iStoppingCriterion = DEFAULT_STOPPING_CRITERION;
    }

    const unsigned int NoOfConstrainededData = 
                                          ioConstrainedDataHolder.size();
    const unsigned int NoOfUnconstrainedData = 
                                          iUnconstrainedDataHolder.size();

    // Unconstraining process
    if (NoOfUnconstrainedData > 0) {
      Mean_T lCompleteDataMean = 0.0;
      StandardDeviation_T lCompleteDataSD = 0.0;
      double lSumOfUnconstrainedData, lSqErrorOfUnconstrainedData = 0.0;
      double lTotalNumberOfData = NoOfConstrainededData + 
                                  NoOfUnconstrainedData;
      // Mean and S.D. of unconstrained data
      Utilities::sumUpElements (lSumOfUnconstrainedData, 
                                iUnconstrainedDataHolder);
      lCompleteDataMean = lSumOfUnconstrainedData / NoOfUnconstrainedData;
      Utilities::getSquaredError (lSqErrorOfUnconstrainedData, 
                                  iUnconstrainedDataHolder, lCompleteDataMean);
      lCompleteDataSD = sqrt(lSqErrorOfUnconstrainedData / 
                             (NoOfUnconstrainedData-1));
      
      // If there are constrained data
      if (NoOfConstrainededData > 0) {
        double lEstimatedMean, lEstimatedSD, lSqErrorOfConstrainedData = 
          DEFAULT_INITIALIZER_DOUBLE_NEGATIVE;
        
        do {
          if (lEstimatedMean != DEFAULT_INITIALIZER_DOUBLE_NEGATIVE) { 
            lCompleteDataMean = lEstimatedMean;
            lCompleteDataSD = lEstimatedSD;
          }

          // TO-DO: Expectation step
          expectedValueOfNormallyDistributedConstrainedData 
            (ioConstrainedDataHolder, lCompleteDataMean, lCompleteDataSD);
          // Maximization step
          // Mean
          Utilities::sumUpElements (lEstimatedMean, ioConstrainedDataHolder);
          lEstimatedMean = (lEstimatedMean + lSumOfUnconstrainedData) / 
            lTotalNumberOfData;
          // S.D.
          Utilities::getSquaredError (lSqErrorOfUnconstrainedData,
                                      iUnconstrainedDataHolder, lEstimatedMean);
          Utilities::getSquaredError (lSqErrorOfConstrainedData,
                                      ioConstrainedDataHolder, lEstimatedMean);
          lEstimatedSD = sqrt((lSqErrorOfUnconstrainedData + 
                          lSqErrorOfConstrainedData) / (lTotalNumberOfData-1));          
        }  while ( fabs(lCompleteDataMean - lEstimatedMean ) > iStoppingCriterion );
        // If should mean and s.d. of unconstrained data be outputed 
        // lCompleteDataMean = lEstimatedMean; lCompleteDataSD = lEstimatedSD;
      }
      // Job finished as all are unconstrained or nothing to be unconstrained
    }
    else {
      RMOL_LOG_ERROR ("At least one unconstrained data is required to " 
                      << "correct constrained data with Expectation "
                      << "Maximization algorithm.");
    }
 
  }

  // //////////////////////////////////////////////////////////////////////  
  void ExpectationMaximization::
  expectedValueOfNormallyDistributedConstrainedData
  (ConstrainedDataHolder_T& ioConstrainedDataHolder, 
   Mean_T& iMean, StandardDeviation_T& iSD) {
    
  }

}
