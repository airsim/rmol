// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/UnconstrainingMethod.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/HistoricalBookingHolder.hpp>
#include <rmol/bom/EMDetruncator.hpp>
#include <rmol/command/Detruncator.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////  
  void Detruncator::
  unconstrain (HistoricalBookingHolder& ioHBHolder,
               const stdair::UnconstrainingMethod& iMethod) {
    const stdair::UnconstrainingMethod::EN_UnconstrainingMethod& lUnconstrainingMethod =
      iMethod.getMethod();
    switch (lUnconstrainingMethod) {
    case stdair::UnconstrainingMethod::EM: {
      EMDetruncator::unconstrain (ioHBHolder);
      break;
    }
    default: {
      assert (false);
      break;
    }
    }
  }
}
  
