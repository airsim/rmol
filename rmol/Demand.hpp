#ifndef __RMOL_DEMAND_HPP
#define __RMOL_DEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include "FldDistributionParameters.hpp"
#include "FldYieldRange.hpp"

namespace RMOL {

  /** Class modelling the demand. It holds:
      - Demand parameters: mean and standard deviation.
      - Yield range: upper yield and average yield. */
  class Demand {
  public:
    /** Constructors. */
    Demand ();
    Demand (const Demand&);
    Demand (const FldDistributionParameters&, const FldYieldRange&);

    // Getters
    /** Getter for the demand distribution parmaters (i.e., mean and
        standard deviation). */
    const FldDistributionParameters& getDistributionParameters() const {
      return _distributionParameters;
    }
    /** Getter for the average yield per unit of demand. */
    const FldYieldRange& getYieldRange() const {
      return _yieldRange;
    }
    /** Getter for the upper yield of the range. */
    double getUpperYield() const;
    /** Getter for the average yield of the range. */
    double getAverageYield() const;
    /** Getter for the lower yield of the range. */
    double getLowerYield();
    /** Getter for the mean value. */
    double getMean() const;
    /** Getter for the standard deviation value. */
    double getStandardDeviation() const;
    /** Getter for the variance value. */
    double getVariance() const;
    
    /** Destructors. */
    virtual ~Demand();
    
  private:
    /** Yield range, i.e., upper and lower yields, as well as average yield
	(average revenue per unit of demand). */
    FldYieldRange _yieldRange;

    /** Distribution parameters (i.e., mean and standard deviation). */
    FldDistributionParameters _distributionParameters;
  };
}
#endif // __RMOL_DEMAND_HPP
