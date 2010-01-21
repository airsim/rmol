// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <fstream>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_UTILITY_Types.hpp>
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
   (SellupProbabilityVector_T& ioSellupProbabilityVector, double& iQYield,
    PriceHolder_T& iPriceHolder, SellupFactorHolder_T& iSellupFactorHolder) {
    ioSellupProbabilityVector.clear();
    for (unsigned short j = 0; j < iPriceHolder.size(); j++){ 
      const double lYield = iPriceHolder.at(j);
      const double probSellup = 
        std::exp(-iSellupFactorHolder.at(j) * (lYield / iQYield - 1));
      ioSellupProbabilityVector.push_back(probSellup);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::calculateQEquivalentDemandParameters
   (QEquivalentDemandParameterHolder_T& ioQEquivalentDemandParameterHolder, 
    HistoricalDataHolderHolder_T& iHistoricalDataHolderHolder, 
    SellupProbabilityVector_T& iSellupProbabilityVector) {

    // Debug
    std::ostringstream oDebugStr;
    oDebugStr << "\n";

    // 1. Calculate Q-equivalent demand parameters
    // Initialize a holder for Q-equivalent Demands
    // 0 vector with the size of a data holder
    HistoricalDataHolder_T aHistoricalDataHolder = 
                                          iHistoricalDataHolderHolder.at(0);
    QEquivalentDemandHolder_T lQEquivalentDemandHolder 
                                          (aHistoricalDataHolder.size(), 0);
    // Index 
    unsigned int j = 0;
    std::vector<HistoricalDataHolder_T>::iterator itHDHolderHolder;
    for (itHDHolderHolder = iHistoricalDataHolderHolder.begin(); 
         itHDHolderHolder != iHistoricalDataHolderHolder.end(); 
         ++itHDHolderHolder, ++j) {
      // Retrieve HistoricalDataHolder which are the data of the same product
      // over different dates
      HistoricalDataHolder_T lHistoricalDataHolder = *itHDHolderHolder;
      const SellupProbability_T lSellupProbability = 
                                              iSellupProbabilityVector.at(j);
      const double lQDemandRate = static_cast<double> (1/lSellupProbability);

      // Apply sellup probability to historical data
      Utilities::multiplyAValueToAVector (lHistoricalDataHolder, 
                                          lQDemandRate);
      oDebugStr << "Q-equivalent demand of a product for each date " 
                << Utilities::vectorToString (lHistoricalDataHolder);

      // Collect historical data by date
      Utilities::addTwoVectors (lQEquivalentDemandHolder, 
                                lHistoricalDataHolder);
    }
    oDebugStr << "Q-equivalent demand of a day " 
              << Utilities::vectorToString (lQEquivalentDemandHolder);

    // 2. Compute Q-equivalent demand mean and standard deviation
    Utilities::updateMeanAndStandardDeviation (ioQEquivalentDemandParameterHolder,
                                            lQEquivalentDemandHolder);

    // DEBUG
    STDAIR_LOG_DEBUG (oDebugStr.str());
  }

  // //////////////////////////////////////////////////////////////////////
  void QForecaster::partitionQEquivalentDemandParameters 
   (ForecastedDemandParameterList_T& ioForecastedDemandParameterList, 
    QEquivalentDemandParameterHolder_T& iQEquivalentDemandParameterHolder, 
    SellupProbabilityVector_T& iSellupProbabilityVector) {

    const NumberOfProducts_T noOfClasses = iSellupProbabilityVector.size();

    // Sort sellup probabilities in increasing order and copy into a vector
    SellupProbabilityVector_T lSortedSellupProbabilityVector(noOfClasses);
    std::partial_sort_copy (iSellupProbabilityVector.begin(), 
                            iSellupProbabilityVector.end(),
                            lSortedSellupProbabilityVector.begin(),
                            lSortedSellupProbabilityVector.end());

    // Compute the probability to sell-up to class i but not i-1 (class 
    // with the next higher fare) and copy into a vector
    SellupProbabilityVector_T lSellupProbabilityDifferenceVector(noOfClasses);
    std::adjacent_difference (lSortedSellupProbabilityVector.begin(),
                         lSortedSellupProbabilityVector.end(),
                         lSellupProbabilityDifferenceVector.begin());

    // Partition Q-equivalent demand mean and S.D. into each class
    unsigned int k = 0;
    ioForecastedDemandParameterList.clear();
    SellupProbabilityVector_T::iterator itSellupProbabilityVector;
    for (itSellupProbabilityVector = iSellupProbabilityVector.begin(); 
         itSellupProbabilityVector != iSellupProbabilityVector.end();
         ++itSellupProbabilityVector, ++k) {
      // Locate the current sell-up probability in the sorted one
      SellupProbability_T sellupProbabilityInUnsortedVector = 
                                              *itSellupProbabilityVector;
      SellupProbabilityVector_T::iterator pos = 
                 std::lower_bound (lSortedSellupProbabilityVector.begin(),
                                   lSortedSellupProbabilityVector.end(),
                                   sellupProbabilityInUnsortedVector);
      const PositionInAVector_T posOfCurrentSellupProbInSortedVector = 
               std::distance(lSortedSellupProbabilityVector.begin(), pos);

      // Find the corresponding sell-up probability difference
      const SellupProbability_T correspondingSellupProbability = 
        lSellupProbabilityDifferenceVector.at(
                                    posOfCurrentSellupProbInSortedVector);
      
      // Compute mean and S.D. of each class
      // class mean = Q-eq mean * sell-up prob difference
      // class S.D. = Q-eq S.D. * sell-up prob difference
      ioForecastedDemandParameterList.push_back
                                     (iQEquivalentDemandParameterHolder);
      ForecastedDemandParameters_T& lForecastedDemandParameters = 
                                    ioForecastedDemandParameterList.at(k);
      Utilities::multiplyAValueToAVector (lForecastedDemandParameters,
                                          correspondingSellupProbability);
    }
  }


}
