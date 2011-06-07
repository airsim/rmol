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
  class GuillotineBlock;
  class SegmentCabin;
}

namespace RMOL {
  /** Class wrapping the principal unconstraining algorithms and 
      some accessory algorithms. */
  class Detruncator {
  public:
    /**
     * Unconstrain booking figures between two DCP's.
     */
    static void unconstrain (const stdair::SegmentCabin&, 
			     BookingClassUnconstrainedDemandMap_T&,
                             UnconstrainedDemandVector_T&,
			     const stdair::DCP_T&, const stdair::DCP_T&,
                             const stdair::Date_T&);

  private:
    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrain (const stdair::GuillotineBlock&,
                             UnconstrainedDemandVector_T&,
                             const stdair::DCP_T&, const stdair::DCP_T&,
                             const stdair::NbOfSegments_T&,
                             const stdair::BlockIndex_T&);         
  };
}
#endif // __RMOL_COMMAND_DETRUNCATOR_HPP


