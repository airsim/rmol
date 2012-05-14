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
    static void computeDistributionParameters (const stdair::UncDemVector_T&, double&, double&);
    
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
    static stdair::NbOfSegments_T getNbOfDepartedSimilarSegments (const stdair::SegmentCabin&, const stdair::Date_T&);

    /**
     * Build the map of mean and standard deviation pair for each booking class
     * of the fare family list. If the boolean is true the mean and the 
     * standard deviation is cumulated.
     */
    static const BookingClassMeanStdDevPairMap_T 
      createBookingClassMeanStdDevPairMap(const stdair::FareFamilyList_T&,
                                          const bool isCumulated = false);

    /**
     * Build the map of sell up curve for each booking class of 
     * the booking class list. If the boolean is true the probability
     * is cumulated.
     */
    static const stdair::BookingClassSellUpCurveMap_T 
      createBookingClassSellUpCurveMap(const stdair::BookingClassList_T&, 
                                       const bool isCumulated = false);

   
  };
    
}

#endif // __RMOL_BOM_UTILITIES_HPP
