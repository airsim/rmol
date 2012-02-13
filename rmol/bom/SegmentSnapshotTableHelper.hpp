#ifndef __RMOL_BOM_SEGMENTSNAPSHOTTABLEHELPER_HPP
#define __RMOL_BOM_SEGMENTSNAPSHOTTABLEHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_date_time_types.hpp>

// Forward declarations
namespace stdair {
  class SegmentSnapshotTable;
  class SegmentCabin;
}

namespace RMOL {
  
  /** Class representing the actual business functions for
      an airline guillotine block. */
  class SegmentSnapshotTableHelper {
  public:
    // ////////// Business Methods /////////
    /**
     * Retrieve the number of similar segments which already passed the
     * given DTD.
     */
    static stdair::NbOfSegments_T getNbOfSegmentAlreadyPassedThisDTD (const stdair::SegmentSnapshotTable&, const stdair::DTD_T&, const stdair::Date_T&);

    /**
     * Check if the given segment has passed the given DTD.
     */
    static bool hasPassedThisDTD (const stdair::SegmentCabin&,
                                  const stdair::DTD_T&, const stdair::Date_T&);
  };

}
#endif // __RMOL_BOM_SEGMENTSNAPSHOTTABLEHELPER_HPP
