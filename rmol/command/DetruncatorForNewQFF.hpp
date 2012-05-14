#ifndef __RMOL_COMMAND_DETRUNCATORFORNEWQFF_HPP
#define __RMOL_COMMAND_DETRUNCATORFORNEWQFF_HPP

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
  
  /** Class wrapping the principal unconstraining algorithms. */
  class DetruncatorForNewQFF {
  public:
    /**
     * Unconstrain booking figures between two DCP's.
     */
    static void unconstrain (const stdair::SegmentCabin&, 
                             const stdair::SimpleNestingStruct&,
                             const stdair::DCP_T&,
                             const stdair::DCP_T&,
                             const stdair::Date_T&,
                             stdair::MeanStdDevPairVector_T&, 
                             const unsigned int& iDCPIdx);
    
  private:
    /**
     * Unconstrain the booking figures for a given class on
     * Q-equivalent class. 
     */
    static void unconstrain (const stdair::SegmentSnapshotTable&,
                                         const stdair::DCP_T&,
                                         const stdair::DCP_T&,
                                         const stdair::NbOfSegments_T&,
                                         const stdair::ClassIndex_T&,
                                         const stdair::SegmentCabin&,
                                         const stdair::Date_T&,
                                         const stdair::SellupProbability_T&,
                                         stdair::UncDemVector_T& oDemand);
  };
}
#endif // __RMOL_COMMAND_DETRUNCATORFORNEWQFF_HPP


