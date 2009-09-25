#ifndef __RMOL_BOM_QFORECASTER_HPP
#define __RMOL_BOM_QFORECASTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL Bom
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/RMOL_Types.hpp>
#include <rmol/RMOL_FORECASTER_Types.hpp>

namespace RMOL {

  /** Accessary Class for Sellup considered forecast methods. */
  class QForecaster : public BomAbstract {

  public:

    /** The same method as the above but taking price data directly 
        instead of through BucketHolder. */
    static void calculateSellupProbability (SellupProbabilityVector_T&, 
                                            double& iQYield, 
                                            PriceHolder_T&, 
                                            SellupFactorHolder_T&);

    /** Calculate Q-equivalent demand distribution parameters and 
        partition it to each class/bucket. */
    static void calculateQEquivalentDemandParameters 
                                   (QEquivalentDemandParameterHolder_T&, 
                                    HistoricalDataHolderHolder_T&, 
                                    SellupProbabilityVector_T&);

    /** Calculate Q-equivalent demand distribution parameters and 
        partition it to each class/bucket. */
    static void partitionQEquivalentDemandParameters 
                                       (ForecastedDemandParameterList_T&,
                                        QEquivalentDemandParameterHolder_T&,
                                        SellupProbabilityVector_T&);

  };
}
#endif // __RMOL_BOM_QFORECASTER_HPP
