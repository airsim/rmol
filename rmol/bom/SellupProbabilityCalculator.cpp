// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
// RMOL Bom
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/SellupProbabilityCalculator.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void SellupProbabilityCalculator::calculateSellupProbability 
  (BucketHolder& iBucketHolder,
   const double iQYield,
   const SellupFactorHolder_T& iSellupFactorHolder, 
   SellupProbabilityVector_T& ioSellupProbabilityVector) {
    // Compute sell-up probability for each bucket and store it in a vector
    short j = 0;
    for (iBucketHolder.begin();
         iBucketHolder.hasNotReachedEnd();
         iBucketHolder.iterate()) {
      Bucket& lCurrentBucket = iBucketHolder.getCurrentBucket();
      const double lYield = lCurrentBucket.getAverageYield();
      const double probSellup =
        exp(-iSellupFactorHolder.at(j) *lYield/iQYield);
      ioSellupProbabilityVector.push_back(probSellup);
      j++;
    }
  }
}
