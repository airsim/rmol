// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/EMDetruncator.hpp>

namespace RMOL {
    
  // ////////////////////////////////////////////////////////////////////
  void EMDetruncator::unconstrain
  (HistoricalBookingHolder& ioHistoricalBookingHolder) {
      
    // Number of flights.
    const short lNbOfFlights =
      ioHistoricalBookingHolder.getNbOfFlights();

    // Number of uncensored booking data.
    const short lNbOfUncensoredData =
      ioHistoricalBookingHolder.getNbOfUncensoredData();

    if (lNbOfUncensoredData > 1) {
      // Number of uncensored bookings.
      const stdair::NbOfBookings_T lNbOfUncensoredBookings =
        ioHistoricalBookingHolder.getNbOfUncensoredBookings();
        
      const double lMeanOfUncensoredBookings =
        static_cast<double>(lNbOfUncensoredBookings/lNbOfUncensoredData);

      const double lStdDevOfUncensoredBookings =
        ioHistoricalBookingHolder.getUncensoredStandardDeviation
        (lMeanOfUncensoredBookings, lNbOfUncensoredData);

      std::vector<bool> toBeUnconstrained =
        ioHistoricalBookingHolder.getListOfToBeUnconstrainedFlags();

      double lDemandMean = lMeanOfUncensoredBookings;
      double lStdDev = lStdDevOfUncensoredBookings;

      // DEBUG
      // STDAIR_LOG_DEBUG ("mean: " << lDemandMean << ", std: " << lStdDev);
        
      if (lStdDev != 0) {
        bool stopUnconstraining = false;
        while (stopUnconstraining == false) {
          stopUnconstraining = true;
            
          for (short i = 0; i < lNbOfFlights; ++i) {
            if (toBeUnconstrained.at(i) == true) {
              // Get the unconstrained demand of the (i+1)-th flight.
              const stdair::NbOfBookings_T demand =
                ioHistoricalBookingHolder.getUnconstrainedDemand (i);
              //STDAIR_LOG_DEBUG ("demand: " << demand);
                
              // Execute the Expectation step.
              const stdair::NbOfBookings_T expectedDemand =
                ioHistoricalBookingHolder.
                calculateExpectedDemand (lDemandMean, lStdDev, i, demand);
              //STDAIR_LOG_DEBUG ("expected: " << expectedDemand);
              assert (expectedDemand >= 0 || expectedDemand < 0);
                
              double absDiff =
                static_cast<double>(expectedDemand - demand);
                
              if (absDiff < 0) {
                absDiff = - absDiff;
              }
              if (absDiff < 0.001) {
                toBeUnconstrained.at (i) = false;
              }
              else {
                stopUnconstraining = false;
              }
                
              ioHistoricalBookingHolder.setUnconstrainedDemand (expectedDemand,
                                                                i);
            }
          }
            
          if (stopUnconstraining == false) {
            lDemandMean = ioHistoricalBookingHolder.getDemandMean();
            lStdDev =
              ioHistoricalBookingHolder.getStandardDeviation (lDemandMean);
          }
        }
      }
    }
      
  }
}
