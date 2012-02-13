#ifndef __RMOL_BOM_UTILITIES_HPP
#define __RMOL_BOM_UTILITIES_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
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

  };

}

#endif // __RMOL_BOM_UTILITIES_HPP
