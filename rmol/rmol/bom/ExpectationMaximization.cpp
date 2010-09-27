// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <cmath>
// Boost Math
#include <boost/math/distributions/normal.hpp>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
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
      Utilities::updateSquaredError (lSqErrorOfUnconstrainedData, 
                                     iUnconstrainedDataHolder, 
                                     lCompleteDataMean);
      lCompleteDataSD = sqrt(lSqErrorOfUnconstrainedData / 
                             (NoOfUnconstrainedData-1));
      
      // If there are constrained data
      if (NoOfConstrainededData > 0) {
        double lEstimatedMean, lEstimatedSD;
        double lSqErrorOfConstrainedData = DEFAULT_INITIALIZER_DOUBLE_NEGATIVE;
        
        // A holder for unconstrained results at each iteration
        UnconstrainedDataHolder_T lUnconstrainedDataDuringIteration; 
        do {
          if (lSqErrorOfConstrainedData != DEFAULT_INITIALIZER_DOUBLE_NEGATIVE) { 
            lCompleteDataMean = lEstimatedMean;
            lCompleteDataSD = lEstimatedSD;
          }

          // Expectation step
          expectedValueOfNormallyDistributedConstrainedData 
            (lUnconstrainedDataDuringIteration, ioConstrainedDataHolder, 
             lCompleteDataMean, lCompleteDataSD);

          // Debug
          STDAIR_LOG_DEBUG ("\nUnconstrained data: " 
                          << Utilities::vectorToString
                          (lUnconstrainedDataDuringIteration));
          // Maximization step
          // Mean
          Utilities::sumUpElements (lEstimatedMean, 
                                    lUnconstrainedDataDuringIteration);
          lEstimatedMean = (lEstimatedMean + lSumOfUnconstrainedData) / 
                           lTotalNumberOfData;
          // S.D.
          Utilities::updateSquaredError (lSqErrorOfUnconstrainedData,
                                         iUnconstrainedDataHolder, 
                                         lEstimatedMean);
          Utilities::updateSquaredError (lSqErrorOfConstrainedData,
                                         lUnconstrainedDataDuringIteration, 
                                         lEstimatedMean);
          lEstimatedSD = sqrt((lSqErrorOfUnconstrainedData + 
                          lSqErrorOfConstrainedData) / (lTotalNumberOfData-1));          

          // Debug
          STDAIR_LOG_DEBUG ("\nEstimated Mean: " << lEstimatedMean 
                          << "\nnEstimated s.d.: " << lEstimatedSD);

        } while(fabs(lCompleteDataMean - lEstimatedMean ) > iStoppingCriterion
                || fabs(lCompleteDataSD - lEstimatedSD ) > iStoppingCriterion);
        // Should mean and s.d. of unconstrained data be outputed: 
        // lCompleteDataMean = lEstimatedMean; lCompleteDataSD = lEstimatedSD;

        // Update constrained data with unconstrained ones
        ioConstrainedDataHolder = lUnconstrainedDataDuringIteration;
      }
      // Job finished as all are unconstrained or nothing to be unconstrained
      
    } else {
      STDAIR_LOG_ERROR ("At least one unconstrained data is required to " 
                        << "correct constrained data with Expectation "
                        << "Maximization algorithm.");
    }
  }

  // //////////////////////////////////////////////////////////////////////  
  void ExpectationMaximization::
  expectedValueOfNormallyDistributedConstrainedData
  (UnconstrainedDataHolder_T& ioUnconstrainedDataHolder,
   ConstrainedDataHolder_T& iConstrainedDataHolder, 
   Mean_T& iMean, StandardDeviation_T& iSD) {

    ioUnconstrainedDataHolder.clear();
    for (unsigned int k = 0; k < iConstrainedDataHolder.size(); ++k) {
      const double kthCensoredData = iConstrainedDataHolder.at(k);

      /* Compute E[X | X >= d] where X ~ N(mu, sigma)
                         integral_B^infinity f(x) dx 
         E[X | X >= B] =  ----------------------------  
                         integral_B^infinity xf(x) dx 
                       = mu + d2 / d1
      */
      double e, d1, d2;
      const double lerror = kthCensoredData - iMean;

      //
      boost::math::normal lNormalDistribution (iMean, iSD);
      d1 = boost::math::cdf (boost::math::complement (lNormalDistribution,
                                                      kthCensoredData));
      e = -lerror*lerror * 0.5 / (iSD*iSD);
      d2 = exp(e) * iSD / sqrt (2 * 3.14159265);
      if (d1 < DEFAULT_EPSILON) {
        ioUnconstrainedDataHolder.push_back (kthCensoredData);

      } else {
        ioUnconstrainedDataHolder.push_back (iMean + d2/d1);
      }
    }

  }

}
