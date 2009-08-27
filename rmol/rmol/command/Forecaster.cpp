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

    // Get the number of Buckets
    const double nbOfBuckets = ioBucketHolder.getSize();

    // Initialize a vector for sell-up probabilities
    std::vector<double> lSellupProbabilityVector;

    /** Sell-up probability calculator */
    // Compute sell-up probability for each bucket and store it in a vector
    short j = 0;
    for (ioBucketHolder.begin(); 
         ioBucketHolder.hasNotReachedEnd(); 
         ioBucketHolder.iterate()) {
      Bucket& lCurrentBucket = ioBucketHolder.getCurrentBucket();
      const double lYield = lCurrentBucket.getAverageYield();
      const double probSellup = 
                            exp(-iSellupFactorHolder.at(j) *lYield/qYield);  
      lSellupProbabilityVector.push_back(probSellup);
      j++;
    }
    
//     /** Q-equivqlent booking calculator */
//     // Compute total Q-equivalent bookings
//     for (int j = 0; 
//          j < iHistoricalBookingHolderHolder.getNumberOfSimilarFlights();
//          j++) {

//       HistoricalBookingHolder& lHistoricalBookingHolder = 
//                                       iHistoricalBookingHolderHolder.at(j);

//       double qEquivqlentBooking = 0.0;
//       for (short k = 0; k < nbOfBuckets; k++) {
//         HistoricalBooking& lHistoricalBooking = 
//                    lCurrentHistoricalBookingVector.getHistoricalBooking(k);
//         const double& lHBValue = lHistoricalBooking.getNumberOfBookings();
//         qEquivqlentBooking = qEquivqlentBooking + 
//                              lHBValue * lSellupProbabilityVector[k];
//       }

//       oQEquivalentBookingsPerSimilarFlight.push_back(qEquivqlentBooking);
//     }

// //     SUM_{buckets} histBooking_{bucket i} / ProbSellup_{bucket i}
// //             where
// //               ProbSellup_{bucket i} =
// //               EXP(-sellupfactor*(yield_{bucket i}/lowest yield_{buckets}))

  }
  
}
