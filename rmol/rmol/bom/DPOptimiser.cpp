// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 19)
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
// C
#include <assert.h>
// STL
#include <sstream>
#include <vector>
#include <cmath>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/bom/DPOptimiser.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/service/Logger.hpp>

namespace RMOL {
  
  // ////////////////////////////////////////////////////////////////////
  void DPOptimiser::
  optimalOptimisationByDP (const ResourceCapacity_T iCabinCapacity,
                           BucketHolder& ioBucketHolder,
                           BidPriceVector_T& ioBidPriceVector) {
     // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    // Number of values of x to compute for each Vj(x).
    const int maxValue = static_cast<int> (iCabinCapacity * DEFAULT_PRECISION);

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
    
    while (currentProtection < maxValue && currentBucketIndex < nbOfClasses) {
    //while (currentBucketIndex == 1) {
      bool protectionChanged = false;
      double nextProtection = 0.0;
      std::vector<double> currentMERVector;
      // double testGradient = 10000;
      
      Bucket& currentBucket = ioBucketHolder.getCurrentBucket();
      const double meanDemand = currentBucket.getMean();
      const double SDDemand = currentBucket.getStandardDeviation();
      const double currentYield = currentBucket.getAverageYield();
      const double errorFactor = 1;//gsl_cdf_gaussian_Q (-meanDemand, SDDemand);

      Bucket& nextBucket = ioBucketHolder.getNextBucket();
      const double nextYield = nextBucket.getAverageYield();
      
      // For x <= currentProtection (y_(j-1)), V_j(x) = V_(j-1)(x).
      for (int x = 0; x <= currentProtection; ++x) {
        const double MERValue = MERVectorHolder.at(currentBucketIndex-1).at(x);
        currentMERVector.push_back(MERValue);
      }
      
      // Vector of gaussian pdf values.
      std::vector<double> pdfVector;
      for (int s = 0; s <= maxValue - currentProtection; ++s) {
        const double pdfValue =
          gsl_ran_gaussian_pdf (s/DEFAULT_PRECISION - meanDemand, SDDemand);
        pdfVector.push_back(pdfValue);
      }

      // Vector of gaussian cdf values.
      std::vector<double> cdfVector;
      for (int s = 0; s <= maxValue - currentProtection; ++s) {
        const double cdfValue =
          cdfGaussianQ (s/DEFAULT_PRECISION - meanDemand, SDDemand);
        cdfVector.push_back(cdfValue);
      }
      
      // Compute V_j(x) for x > currentProtection (y_(j-1)).
      for (int x = currentProtection + 1; x <= maxValue; ++x) {
        const double lowerBound = static_cast<double> (x - currentProtection);
        
        // Compute the first integral in the V_j(x) formulation (see
        // the memo of Jerome Contant).
        const double power1 = - 0.5 * meanDemand * meanDemand /
          (SDDemand * SDDemand);
        const double e1 = std::exp (power1);
        const double power2 = 
          - 0.5 * (lowerBound / DEFAULT_PRECISION - meanDemand) *
          (lowerBound / DEFAULT_PRECISION - meanDemand) /
          (SDDemand * SDDemand);
        const double e2 = exp (power2);
        /*
        const double integralResult1 = currentYield * 
          ((e1 - e2) * SDDemand / sqrt (2 * 3.14159265) +
           meanDemand * gsl_cdf_gaussian_Q (-meanDemand, SDDemand) -
           meanDemand * gsl_cdf_gaussian_Q (lowerBound / DEFAULT_PRECISION - meanDemand, SDDemand));
        */
        const double integralResult1 = currentYield * 
          ((e1 - e2) * SDDemand / sqrt (2 * 3.14159265) +
           meanDemand * cdfGaussianQ (-meanDemand, SDDemand) -
           meanDemand * cdfGaussianQ (lowerBound / DEFAULT_PRECISION - meanDemand, SDDemand));
        
        double integralResult2 = 0.0;
        
        for (int s = 0; s < lowerBound; ++s) {
          const double partialResult =
            2 * MERVectorHolder.at(currentBucketIndex-1).at(x-s) *
            pdfVector.at(s);
          
          integralResult2 += partialResult;
        }
        integralResult2 -= MERVectorHolder.at(currentBucketIndex-1).at(x) *
          pdfVector.at(0);
        
        const int intLowerBound = static_cast<int>(lowerBound);
        integralResult2 += 
          MERVectorHolder.at(currentBucketIndex-1).at(x - intLowerBound) *
          pdfVector.at(intLowerBound);
        
        integralResult2 /= 2 * DEFAULT_PRECISION;
        /*
        for (int s = 0; s < lowerBound; ++s) {
          const double partialResult =
            (MERVectorHolder.at(currentBucketIndex-1).at(x-s) +
             MERVectorHolder.at(currentBucketIndex-1).at(x-s-1)) *
            (cdfVector.at(s+1) - cdfVector.at(s)) / 2;
          integralResult2 += partialResult;
        }
        */
        const double firstElement = integralResult1 + integralResult2;
        
        // Compute the second integral in the V_j(x) formulation (see
        // the memo of Jerome Contant).
        const double constCoefOfSecondElement =
          currentYield * lowerBound / DEFAULT_PRECISION +
          MERVectorHolder.at(currentBucketIndex-1).at(currentProtection);
        const double secondElement = constCoefOfSecondElement * 
    //gsl_cdf_gaussian_Q(lowerBound / DEFAULT_PRECISION - meanDemand, SDDemand);
          cdfGaussianQ (lowerBound / DEFAULT_PRECISION - meanDemand, SDDemand);
        const double MERValue = (firstElement + secondElement) / errorFactor;

        
        assert (currentMERVector.size() > 0);
        const double lastMERValue = currentMERVector.back();

        const double currentGradient = 
          (MERValue - lastMERValue) * DEFAULT_PRECISION;

        //assert (currentGradient >= 0);
        if (currentGradient < -0) {
          std::ostringstream ostr;
          ostr << currentGradient  << std::endl
               << "x = " << x << std::endl
               << "class: " << currentBucketIndex << std::endl;
          RMOL_LOG_DEBUG (ostr.str());
        }
          
        /*
        assert (currentGradient <= testGradient);
        testGradient = currentGradient;
        */
        if (protectionChanged == false && currentGradient <= nextYield) {
          nextProtection = x - 1;
          protectionChanged = true;
        }

         if (protectionChanged == true && currentGradient > nextYield) {
          protectionChanged = false;
        }
        
        if (protectionChanged == false && x == maxValue) {
          nextProtection = maxValue;
        }
        
        currentMERVector.push_back (MERValue); 
      }

      // DEBUG
      RMOL_LOG_DEBUG ("Vmaxindex = " << currentMERVector.back());
        
      MERVectorHolder.push_back (currentMERVector);
     
      const double realProtection = nextProtection / DEFAULT_PRECISION;
      const double bookingLimit = iCabinCapacity - realProtection;

      currentBucket.setCumulatedProtection (realProtection);
      nextBucket.setCumulatedBookingLimit (bookingLimit);

      currentProtection = static_cast<int> (std::floor (nextProtection));
      
      ioBucketHolder.iterate();
      ++currentBucketIndex;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  double DPOptimiser::cdfGaussianQ (const double c, const double sd) {
    const double power = - c * c * 0.625 / (sd * sd);
    const double e = std::sqrt (1 - std::exp (power));
    double result = 0.0;
    
    if (c >= 0) {
      result = 0.5 * (1 - e);

    } else {
      result = 0.5 * (1 + e);
    }
    
    return result;
  }
  
}
