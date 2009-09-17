// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
// RMOL Bom
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/QForecaster.hpp>
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::calculateSellupProbability 
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

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::calculateSellupProbability
   (SellupProbabilityVector_T& ioSellupProbabilityVector, const double iQYield,
    PriceHolder_T& iPriceHolder, SellupFactorHolder_T& iSellupFactorHolder) {
    ioSellupProbabilityVector.clear();
    for (unsigned short j=0; j < iPriceHolder.size(); j++){ 
      const double lYield = iPriceHolder.at(j);
      const double probSellup = 
        exp(-iSellupFactorHolder.at(j) *lYield/iQYield);
      ioSellupProbabilityVector.push_back(probSellup);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::calculateQEquivalentDemandParametersAndPartition 
   (ForecastedDemandParameterList_T oForecastedDemandParameterList, 
    HistoricalDataHolderHolder_T& iHistoricalDataHolderHolder, 
    SellupProbabilityVector_T& lSellupProbabilityVector) {
    // 1. Calculate Q-equivalent demand parameters
    // Initialize a holder for Q-equivalent Demands
    std::vector<double> lQEquivalentDemandHolder
                                      (lSellupProbabilityVector.size(), 0);

    for (unsigned int j = 0; j < iHistoricalDataHolderHolder.size(); j++) {
      // Retrieve HistoricalDataHolder which are the data of the same product
      // over different dates
      std::vector<double>& lHistoricalDataHolder = 
                           iHistoricalDataHolderHolder.at(j);
      double lSellupProbability = lSellupProbabilityVector.at(j);
      Utilities::MultiplyAValueToAVector (lHistoricalDataHolder, 
                                          1/lSellupProbability);
      // TODO: Collect historical data by date
      Utilities::AddTwoVectors(lQEquivalentDemandHolder, lHistoricalDataHolder);
    }

    // 2. Partition the Q-eq demand to each class/bucket 
    
  }

}
