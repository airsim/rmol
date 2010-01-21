// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/QForecaster.hpp>
#include <rmol/command/Forecaster.hpp>
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // // //////////////////////////////////////////////////////////////////////
  // void Forecaster::qEquivalentBookingCalculation 
  //      (BucketHolder& ioBucketHolder,
  //       SellupFactorHolder_T& iSellupFactorHolder,
  //       HistoricalBookingHolderHolder& iHistoricalBookingHolderHolder,
  //       HolderOfQEquivalentBookingsPerSimilarFlight_T& 
  //                                     oQEquivalentBookingsPerSimilarFlight){

  //   // Get the lowest yield of the given buckets
  //   const double qYield = ioBucketHolder.getLowestAverageYield ();

  //   // Initialize a vector for sell-up probabilities
  //   std::vector<double> lSellupProbabilityVector;

  //   // Compute sell-up probability for each bucket and store it in a vector
  //   QForecaster::calculateSellupProbability
  //     (ioBucketHolder, qYield, iSellupFactorHolder, lSellupProbabilityVector);
    
  //   // Compute total Q-equivalent bookings
  //   // QEquivalentBookingCalculator::calculateQEquivalentBooking 
  //   //   (iHistoricalBookingHolderHolder, 
  //   //    lSellupProbabilityVector, 
  //   //    oQEquivalentBookingsPerSimilarFlight);
  // }

  // //////////////////////////////////////////////////////////////////////  
  void Forecaster::demandForecastByQForecasting 
       (ForecastedDemandParameterList_T& ioForecastedDemandParameterList,
        HistoricalDataHolderHolder_T& iHistoricalDataHolderHolder,
        PriceHolder_T& iPriceHolder, 
        SellupFactorHolder_T& iSellupFactorHolder) {
    // Run Q-Forecasting algorithm
    // 1. Obtain forecasted Q-eqivalent demand mean and s.d.(mu_Q, sigma_Q)
    // 2. Partition to each class
    //    E(alpha x Q)=alpha x mu_Q, S.D.(alpha x Q) = |alpha| X sigma_Q

    // Debug 
    std::ostringstream oDebugStr;
    oDebugStr << "Prices are "
              << Utilities::vectorToString(iPriceHolder) << std::endl
              << "Sell up factors are "
              << Utilities::vectorToString(iSellupFactorHolder) << std::endl;
              
    // Find the class with the lowest yield
    double lQYield;
    Utilities::updateMinimumElement (lQYield, iPriceHolder);
    // Debug
    oDebugStr << "The minimum yield is " << lQYield << std::endl;

    // Initialize a holder for sell-up probabilities
    SellupProbabilityVector_T lSellupProbabilityVector;
    // Compute sell-up probability for each class/bucket & store it in a vector
    QForecaster::calculateSellupProbability
      (lSellupProbabilityVector, lQYield, iPriceHolder, iSellupFactorHolder);
    // Debug
    oDebugStr << "Sell-up Probabilities are " 
              << Utilities::vectorToString (lSellupProbabilityVector) << std::endl;

    // Initialize a holder for Q-equivalent Demand Parameters
    QEquivalentDemandParameterHolder_T lQEquivalentDemandParameterHolder;
    // Calculate Q-equivalent demand distribution parameters.
    QForecaster::calculateQEquivalentDemandParameters 
     (lQEquivalentDemandParameterHolder, iHistoricalDataHolderHolder,
      lSellupProbabilityVector);
    // Debug
    oDebugStr << "Q-equivalent demand parameters [mean, SD] = " 
              << Utilities::vectorToString (lQEquivalentDemandParameterHolder)
              << std::endl;

    // Calculate Q-equivalent demand distribution parameters and 
    // partition it to each class/bucket
    QForecaster::partitionQEquivalentDemandParameters 
     (ioForecastedDemandParameterList, lQEquivalentDemandParameterHolder, 
      lSellupProbabilityVector);
    // debug
    ForecastedDemandParameterList_T::iterator itForecastedDemandParameterList;
    for (itForecastedDemandParameterList = ioForecastedDemandParameterList.begin(); 
         itForecastedDemandParameterList != ioForecastedDemandParameterList.end();
         ++itForecastedDemandParameterList) {
      std::vector<double> lMeanAndSDOfAClass = *itForecastedDemandParameterList;
      oDebugStr << "Q-equivalent distribution parameters per class " 
                << Utilities::vectorToString (lMeanAndSDOfAClass);
    }

    // DEBUG
    STDAIR_LOG_DEBUG(oDebugStr.str());
  }
}
