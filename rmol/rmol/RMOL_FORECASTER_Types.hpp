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
      per booking class. Each row contains [class key, [mean, s.d.]] */
  typedef std::map<std::string, std::vector<double> > 
                                           ForecastedDemandParameterList_T;

}
#endif // __RMOL_RMOL_FORECASTER_TYPES_HPP
