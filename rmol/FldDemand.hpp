#ifndef __RMOL_DEMAND_HPP
#define __RMOL_DEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include "FldDistributionParameters.hpp"

namespace RMOL {

  /** Class modelling the demand. It holds:
      - Demand parameters: mean and standard deviation.
      - Yield range: upper yield and average yield. */
  class Demand {
  public:
    /** Constructors. */
    Demand ();
    Demand (const Demand&);
    Demand (const FldDistributionParameters&, const double iAverageYield);

    // Getters
    /** Getter for the demand distribution parmaters (i.e., mean and
        standard deviation). */
    FldDistributionParameters getParameters() const {
      return _params;
    }
    /** Getter for the average yield per unit of demand. */
    double getAverageYield() const {
      return _averageYield;
    }
    
    /** Destructors. */
    virtual ~Demand();
    
  private:
    /** Average yield (average revenue per unit of demand). */
    double _averageYield;

    /** Distribution parameters (i.e., mean and standard deviation). */
    FldDistributionParameters _params;
  };
}
#endif // __RMOL_DEMAND_HPP
