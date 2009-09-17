#ifndef __RMOL_BOM_QFORECASTER_HPP
#define __RMOL_BOM_QFORECASTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL Bom
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>

namespace RMOL {

  // Forward declaration
  class BucketHolder;

  /** Accessary Class for Sellup considered forecast methods. */
  class QForecaster : public BomAbstract {

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

    /** The same method as the above but taking price data directly 
        instead of through BucketHolder. */
    static void calculateSellupProbability (SellupProbabilityVector_T&, 
                                            const double iQYield, 
                                            PriceHolder_T&, 
                                            SellupFactorHolder_T&);

    /** Calculate Q-equivalent demand distribution parameters and 
        partition it to each class/bucket. */
    static void calculateQEquivalentDemandParametersAndPartition 
                                       (ForecastedDemandParameterList_T, 
                                        HistoricalDataHolderHolder_T&, 
                                        SellupProbabilityVector_T&);

  };
}
#endif // __RMOL_BOM_QFORECASTER_HPP
