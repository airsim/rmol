// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cmath>
// RMOL Bom
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/QEquivalentBookingCalculator.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void QEquivalentBookingCalculator::calculateQEquivalentBooking 
  (HistoricalBookingHolderHolder& iHistoricalBookingHolderHolder, 
   SellupProbabilityVector_T& iSellupProbabilityVector,
   HolderOfQEquivalentBookingsPerSimilarFlight_T& 
                            oHolderOfQEquivalentBookingsPerSimilarFlight) {

//     // Get the number of Buckets
//     const double nbOfBuckets = ioBucketHolder.getSize();

//     for (int j = 0; 
//          j < iHistoricalBookingHolderHolder.getNumberOfSimilarFlights();
//          j++) {

//       HistoricalBookingHolder& lHistoricalBookingHolder = 
//                                       iHistoricalBookingHolderHolder.at(j);

//       double qEquivalentBooking = 0.0;
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
