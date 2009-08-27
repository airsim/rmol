#ifndef __RMOL_BOM_SELLUPPROBABILITYCALCULATOR_HPP
#define __RMOL_BOM_SELLUPPROBABILITYCALCULATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL Bom
#include <rmol/bom/BomAbstract.hpp>

namespace RMOL {

  // Forward declaration
  class BucketHolder;

  /** Accessary Class for Sellup considered forecast methods. */
  class SellupProbabilityCalculator : public BomAbstract {

  public:

    /** Calculate sell-up probability for given sell-up factor,
        and yield ratio between the sell-up occurs.<br> 
        The formular was proposed by Belobaba and Hopperstad:
        Algorithms for Revenue Management in Unrestricted Fare Markets, 
        AGIFORS, Auckland, New Zealand, Jan 2004    */
    static void calculateSellupProbability (BucketHolder&, 
                                            const double iQYield, 
                                            const SellupFactorHolder_T&, 
                                            SellupProbabilityVector_T&);
  };

}
#endif // __RMOL_BOM_SELLUPPROBABILITYCALCULATOR_HPP
