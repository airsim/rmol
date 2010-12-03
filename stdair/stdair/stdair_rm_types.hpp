#ifndef __STDAIR_STDAIR_RM_TYPES_HPP
#define __STDAIR_STDAIR_RM_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// StdAir
#include <stdair/stdair_basic_types.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /** Frequency of the Data Collection Point description (daily, monthly or
      detailed). */
  typedef std::string DCPModeFrequency_T;

  /** Mode of the Data Collection Point description (Forecaster only,
      Optimizer only or both of them). */
  typedef std::string DCPMode_T;

  /** Mode of the forecaster. */
  typedef std::string ForecasterMode_T;

  /** Limit of similar flight-dates used in the forecaster. */
  typedef short HistoricalDataLimit_T;

  /** Mode of the forecaster. */
  typedef std::string OptimizerMode_T;

  /** Mode of the forecaster. */
  typedef std::string DicoOptimizerMode_T;

  /** Define the name of sell-up probability flag for RMS optimizer. */
  typedef bool SellupFlagForOptimizer_T;

  /** Define the name of sell-up probability for RMS optimizer. */
  typedef double SellupProbabilityForOptimizer_T;

  /** Define the name of sell-up probability vector for RMS optimizer. */
  typedef std::vector<SellupProbabilityForOptimizer_T> SellupProbabilityVector_T;

  /** Define the demand for a policy. */
  typedef NbOfBookings_T PolicyDemand_T;

  /** Define the total revenue of an unconstrained policy. */
  typedef double PolicyRevenue_T;

  /** Define the total revenue of an unconstrained policy. */
  typedef double PolicyRevenue_T;

}
#endif // __STDAIR_STDAIR_RM_TYPES_HPP
