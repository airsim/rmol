// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/command/Forecaster.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void Forecaster::qEquivalentBookingCalculation 
           (BucketHolder& ioBucketHolder,
            SellupFactorHolder_T& iSellupFactorHolder,
            HistoricalBookingVectorHolder_T& iHistoricalBookingVectorHolder){

    const double qYield = ioBucketHolder.getLowestAverageYield ();



  }

}
