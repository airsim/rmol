// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <math.h>
// RMOL
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/HistoricalBookingHolderHolder.hpp>
#include <rmol/bom/SellupProbabilityCalculator.hpp>
#include <rmol/bom/QEquivalentBookingCalculator.hpp>
#include <rmol/command/Forecaster.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void Forecaster::qEquivalentBookingCalculation 
       (BucketHolder& ioBucketHolder,
        SellupFactorHolder_T& iSellupFactorHolder,
        HistoricalBookingHolderHolder& iHistoricalBookingHolderHolder,
        HolderOfQEquivalentBookingsPerSimilarFlight_T& 
                                      oQEquivalentBookingsPerSimilarFlight){

    // Get the lowest yield of the given buckets
    const double qYield = ioBucketHolder.getLowestAverageYield ();

    // Initialize a vector for sell-up probabilities
    std::vector<double> lSellupProbabilityVector;

    // Compute sell-up probability for each bucket and store it in a vector
    SellupProbabilityCalculator::calculateSellupProbability
      (ioBucketHolder, qYield, iSellupFactorHolder, lSellupProbabilityVector);
    
    // Compute total Q-equivalent bookings
    QEquivalentBookingCalculator::calculateQEquivalentBooking 
      (iHistoricalBookingHolderHolder, 
       lSellupProbabilityVector, 
       oQEquivalentBookingsPerSimilarFlight);
  }

  // //////////////////////////////////////////////////////////////////////  
  void Forecaster::demandForecastByQForecasting () {
    // qEquivalentBookingCalculation 
    //        (BucketHolder& ioBucketHolder,
    //         SellupFactorHolder_T& iSellupFactorHolder,
    //         HistoricalBookingHolderHolder& iHistoricalBookingHolderHolder,
    //         HolderOfQEquivalentBookingsPerSimilarFlight_T& 
    //         oQEquivalentBookingsPerSimilarFlight);

  }
}
