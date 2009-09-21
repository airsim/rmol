// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
#include <algorithm>
#include <numeric>
// RMOL Bom
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/QForecaster.hpp>
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // // //////////////////////////////////////////////////////////////////////
  // void QForecaster::calculateSellupProbability 
  // (BucketHolder& iBucketHolder,
  //  const double iQYield,
  //  const SellupFactorHolder_T& iSellupFactorHolder, 
  //  SellupProbabilityVector_T& ioSellupProbabilityVector) {
  //   // Compute sell-up probability for each bucket and store it in a vector
  //   short j = 0;
  //   for (iBucketHolder.begin();
  //        iBucketHolder.hasNotReachedEnd();
  //        iBucketHolder.iterate()) {
  //     Bucket& lCurrentBucket = iBucketHolder.getCurrentBucket();
  //     const double lYield = lCurrentBucket.getAverageYield();
  //     const double probSellup =
  //       exp(-iSellupFactorHolder.at(j) *lYield/iQYield);
  //     ioSellupProbabilityVector.push_back(probSellup);
  //     j++;
  //   }
  // }

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::calculateSellupProbability
   (SellupProbabilityVector_T* ioSellupProbabilityVector, double* iPtrQYield,
    PriceHolder_T& iPriceHolder, SellupFactorHolder_T& iSellupFactorHolder) {
    ioSellupProbabilityVector->clear();
    for (unsigned short j = 0; j < iPriceHolder.size(); j++){ 
      const double lYield = iPriceHolder.at(j);
      const double probSellup = 
        exp(-iSellupFactorHolder.at(j) * lYield / (*iPtrQYield));
      ioSellupProbabilityVector->push_back(probSellup);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::calculateQEquivalentDemandParameters
   (QEquivalentDemandParameterHolder_T* ioQEquivalentDemandParameterHolder, 
    HistoricalDataHolderHolder_T& iHistoricalDataHolderHolder, 
    SellupProbabilityVector_T* lSellupProbabilityVector) {
    // 1. Calculate Q-equivalent demand parameters
    // Initialize a holder for Q-equivalent Demands
    std::vector<double> aZeroVector (lSellupProbabilityVector->size(), 0);
    std::vector<double>& lQEquivalentDemandHolder = aZeroVector;

    for (unsigned int j = 0; j < iHistoricalDataHolderHolder.size(); j++) {
      // Retrieve HistoricalDataHolder which are the data of the same product
      // over different dates
      std::vector<double>& lHistoricalDataHolder = 
                           iHistoricalDataHolderHolder.at(j);
      double lSellupProbability = lSellupProbabilityVector->at(j);

      // Apply sellup probability to historical data
      Utilities::MultiplyAValueToAVector (lHistoricalDataHolder, 
                                          1/lSellupProbability);

      // Collect historical data by date
      Utilities::AddTwoVectors (lQEquivalentDemandHolder, 
                                lHistoricalDataHolder);
    }

    // 2. Compute Q-equivalent demand mean and standard deviation
    Utilities::getMeanAndStandardDeviation (ioQEquivalentDemandParameterHolder,
                                            lQEquivalentDemandHolder);  
  }

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::partitionQEquivalentDemandParameters 
   (ForecastedDemandParameterList_T oForecastedDemandParameterList, 
    QEquivalentDemandParameterHolder_T* iQEquivalentDemandParameterHolder, 
    SellupProbabilityVector_T* iSellupProbabilityVector) {

    unsigned int noOfClasses = iSellupProbabilityVector->size();

    // Sort sellup probabilities in increasing order and copy into a vector
    std::vector<double> lSortedSellupProbabilityVector(noOfClasses);
    std::partial_sort_copy (iSellupProbabilityVector->begin(), 
                       iSellupProbabilityVector->end(),
                       lSortedSellupProbabilityVector.begin(),
                       lSortedSellupProbabilityVector.end());

    // Compute the probability to sell-up to class i but not i-1 (class 
    // with the next higher fare) and copy into a vector
    std::vector<double> lSellupProbabilityDifferenceVector(noOfClasses);
    adjacent_difference (lSortedSellupProbabilityVector.begin(),
                              lSortedSellupProbabilityVector.end(),
                              lSellupProbabilityDifferenceVector.begin());

    // Partition Q-equivalent demand mean and S.D. into each class
    oForecastedDemandParameterList.clear();
    for (unsigned short k=0; k < noOfClasses; k++) {
      // Locate the current sell-up probability in the sorted one
      std::vector<double>::iterator pos = 
                 std::lower_bound (lSortedSellupProbabilityVector.begin(),
                                   lSortedSellupProbabilityVector.end(),
                                   iSellupProbabilityVector->at(k));
      int posOfCurrentSellupProbInSortedVector = 
               std::distance(lSortedSellupProbabilityVector.begin(), pos);

      // Find the corresponding sell-up probability difference
      double correspondingSellupProbability = 
        lSellupProbabilityDifferenceVector.at(
                                    posOfCurrentSellupProbInSortedVector);
      
      // Compute mean and S.D. of each class
      // class mean = Q-eq mean * sell-up prob difference
      // class S.D. = Q-eq S.D. * sell-up prob difference
      oForecastedDemandParameterList.push_back
                                     (*iQEquivalentDemandParameterHolder);
      std::vector<double>& forecastedDemandParameters = 
                                     oForecastedDemandParameterList.at(k);
      Utilities::MultiplyAValueToAVector (forecastedDemandParameters,
                                     correspondingSellupProbability);
    }
  }


}
