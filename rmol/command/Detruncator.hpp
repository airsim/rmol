#ifndef __RMOL_COMMAND_DETRUNCATOR_HPP
#define __RMOL_COMMAND_DETRUNCATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/UnconstrainingMethod.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>


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
    static void unconstrain (HistoricalBookingHolder&,
                 const stdair::UnconstrainingMethod&);
    
  };
}
#endif // __RMOL_COMMAND_DETRUNCATOR_HPP


