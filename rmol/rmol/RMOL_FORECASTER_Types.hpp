#ifndef __RMOL_RMOL_FORECASTER_TYPES_HPP
#define __RMOL_RMOL_FORECASTER_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <map>

namespace RMOL {

  // //////// Type definitions /////////

  /** Define the map of a class code - segment (origine/destination)
      and a vector of (unconstrained) demand of the similar flight-dates. */
  typedef std::map<std::string, std::vector<double> > 
                                           SimilarFlightsDemandList_T;

  /** Define the holder of forecasted demand parameters (mean, std. deviation) 
      per booking class. The order of the parameters corresponds to the vector 
      inputs resulted the parameters themselves.*/
  typedef std::vector<double> ForecastedDemandParameterList_T;

  /** Define a vector of fares. */
  typedef std::vector<double> PriceHolder_T;

//   /** Define historical data vector*/
//   typedef std::vector<double> HistoricalDataHolder_T;

  /** Define vector of historical data vector*/
  typedef std::vector< std::vector<double> > HistoricalDataHolderHolder_T;

}
#endif // __RMOL_RMOL_FORECASTER_TYPES_HPP