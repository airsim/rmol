// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 19)
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
#include <vector>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/bom/DPOptimiser.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void DPOptimiser::
  optimalOptimisationByDP (const ResourceCapacity_T iCabinCapacity,
                           BucketHolder& ioBucketHolder,
                           BidPriceVector_T& ioBidPriceVector) {
     // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    // Number of values of x to compute for each Vj(x).
    const int maxValue =
      1 + static_cast<int> (iCabinCapacity * DEFAULT_PRECISION);

    // Vector of the Expected Maximal Revenue (Vj).
    std::vector< std::vector<double> > MERVectorHolder;

    // Vector of V_0(x).
    std::vector<double> initialMERVector (maxValue+1, 0.0);
    MERVectorHolder.push_back (initialMERVector);

    // Current cumulative protection level (y_j * DEFAULT_PRECISION).
    // Initialise with y_0 = 0.
    int currentProtection = 0;

    int currentBucketIndex = 1;
    ioBucketHolder.begin();
    
    while (currentProtection < maxValue && currentBucketIndex <= nbOfClasses) {
      std::vector<double> currentMERVector;
      
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      const double meanDemand = currentBucket.getMean();
      const double SDDemand = currentBucket.getStandardDeviation();
      const double currentYield = currentBucket.getAverageYield();
      const double errorFactor = gsl_cdf_gaussian_Q (-meanDemand, SDDemand);
      
      // For x <= currentProtection (y_(j-1)), V_j(x) = V_(j-1)(x).
      for (int x = 0; x <= currentProtection; ++x) {
        const double MERValue = MERVectorHolder.at(currentBucketIndex-1).at(x);
        currentMERVector.push_back(MERValue);
      }
      
      // Compute V_j(x) for x > currentProtection (y_(j-1)).
      for (int x = currentProtection + 1; x <= maxValue; ++x) {
        const double lowerBound = static_cast<double> (x - currentProtection);
        
        // Compute the first integral in the V_j(x) formulation (see
        // the memo of Jerome Contant).
        const double power1 = - 0.5 * meanDemand * meanDemand /
          (SDDemand * SDDemand);
        const double e1 = exp (power1);
        const double power2 = 
          - 0.5 * (lowerBound - meanDemand) * (lowerBound - meanDemand) /
          (SDDemand * SDDemand);
        const double e2 = exp (power2);
        const double integralResult1 =
          currentYield * (e1 - e2) * SDDemand / sqrt (2 * 3.14159265);
        
        double integralResult2 = 0.0;
        for (int s = 0; s < lowerBound; ++s) {
          const double partialResult =
            2 * MERVectorHolder.at(currentBucketIndex-1).at(x-s) *
            gsl_ran_gaussian_pdf (s/DEFAULT_PRECISION - meanDemand, SDDemand);
          
          integralResult2 += partialResult;
        }
        integralResult2 -= MERVectorHolder.at(currentBucketIndex-1).at(x) *
          gsl_ran_gaussian_pdf (-meanDemand, SDDemand);
          
        integralResult2 += 
          MERVectorHolder.at(currentBucketIndex-1).at(x - lowerBound) *
          gsl_ran_gaussian_pdf (lowerBound - meanDemand, SDDemand);
             
        integralResult2 /= 2 * DEFAULT_PRECISION;
               
        const double firstElement =
          (integralResult1 + integralResult2) / errorFactor;
        
        // Compute the second integral in the V_j(x) formulation (see
        // the memo of Jerome Contant).
        const double constCoefOfSecondElement =
          currentYield * lowerBound / DEFAULT_PRECISION +
          MERVectorHolder.at(currentBucketIndex-1).at(currentProtection);
        const double secondElement = constCoefOfSecondElement * 
          gsl_cdf_gaussian_Q(lowerBound - meanDemand, SDDemand) / errorFactor;

        const double MERValue = firstElement + secondElement;
        currentMERVector.push_back (MERValue);
        
      }
      
      MERVectorHolder.push_back (currentMERVector);
      
      ioBucketHolder.iterate();
      ++currentBucketIndex;
    }
    
    
  }
}
