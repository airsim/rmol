#ifndef __RMOL_BOM_UTILITIES_HPP
#define __RMOL_BOM_UTILITIES_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class SegmentCabin;
}

namespace RMOL {

  /** Class holding helper methods. */
  class Utilities {
  public:
    /** Compute the mean and the standard deviation from a set of samples. */
    static void computeDistributionParameters (const stdair::UncDemVector_T&,
                                               stdair::MeanValue_T&,
                                               stdair::StdDevValue_T&);
    
    /**
     * Build the list of remaining DCP's for the segment-date.
     */
    static stdair::DCPList_T buildRemainingDCPList (const stdair::DTD_T&);

    /**
     * Build the list of past DCP's for the segment-date.
     */
    static stdair::DCPList_T buildPastDCPList (const stdair::DTD_T&);

    /**
     * Retrieve the number of departed similar segments.
     */
    static stdair::NbOfSegments_T 
    getNbOfDepartedSimilarSegments (const stdair::SegmentCabin&,
                                    const stdair::Date_T&);
    
    /**
     * Precompute the sell-up factors for each class and each DCP.
     */
    static stdair::BookingClassSellUpCurveMap_T 
    computeSellUpFactorCurves (const stdair::FRAT5Curve_T&,
                               const stdair::BookingClassList_T&);

    /**
     * Precompute the dispatching factors for each class and each DCP.
     */
    static stdair::BookingClassDispatchingCurveMap_T 
    computeDispatchingFactorCurves (const stdair::FRAT5Curve_T&,
                                    const stdair::BookingClassList_T&);

    /**
     * Dispatching the demand forecast to all classes.
     */
    static void 
    dispatchDemandForecast (const stdair::BookingClassDispatchingCurveMap_T&,
                            const stdair::MeanValue_T&,
                            const stdair::StdDevValue_T&,
                            const stdair::DTD_T&);

    /**
     * Dispatching the demand forecast to all classes for FA.
     */
    static void 
    dispatchDemandForecastForFA (const stdair::BookingClassSellUpCurveMap_T&,
                                 const stdair::MeanValue_T&,
                                 const stdair::StdDevValue_T&,
                                 const stdair::DTD_T&);
  };
    
}

#endif // __RMOL_BOM_UTILITIES_HPP
