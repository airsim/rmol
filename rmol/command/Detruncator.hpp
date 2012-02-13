#ifndef __RMOL_COMMAND_DETRUNCATOR_HPP
#define __RMOL_COMMAND_DETRUNCATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations.
namespace stdair {
  class SegmentSnapshotTable;
  class SegmentCabin;
}

namespace RMOL {
  // Forward declarations.
  struct HistoricalBookingHolder;
  
  /** Class wrapping the principal unconstraining algorithms and 
      some accessory algorithms. */
  class Detruncator {
  public:
    /**
     * Unconstrain booking figures between two DCP's.
     */
    static void unconstrainUsingAddPkUp (const stdair::SegmentCabin&, 
                                         stdair::BookingClassUncDemVectorMap_T&,
                                         stdair::UncDemVector_T&,
                                         const stdair::DCP_T&,
                                         const stdair::DCP_T&,
                                         const stdair::Date_T&);
    
  private:
    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingAddPkUp (const stdair::SegmentSnapshotTable&,
                                         stdair::UncDemVector_T&,
                                         const stdair::DCP_T&,
                                         const stdair::DCP_T&,
                                         const stdair::NbOfSegments_T&,
                                         const stdair::ClassIndex_T&);
    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingAddPkUp (const stdair::SegmentSnapshotTable&,
                                         stdair::UncDemVector_T&,
                                         const stdair::DCP_T&,
                                         const stdair::DCP_T&,
                                         const stdair::NbOfSegments_T&,
                                         const stdair::ClassIndex_T&,
                                         const stdair::SegmentCabin&,
                                         const stdair::Date_T&);
  };
}
#endif // __RMOL_COMMAND_DETRUNCATOR_HPP


