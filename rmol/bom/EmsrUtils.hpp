#ifndef __RMOL_EMSRUTILS_HPP
#define __RMOL_EMSRUTILS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>

// Forward declarations.
namespace stdair {
  struct VirtualClassStruct;
}

namespace RMOL {
  
  /** Forward declarations. */
  
  class EmsrUtils {
  public:
    /** Compute the aggregated class/bucket of classes/buckets 1,..,j
        for EMSR-b algorithm. */
    static void computeAggregatedVirtualClass (stdair::VirtualClassStruct&,
                                               stdair::VirtualClassStruct&);

    /** Compute the protection level using the Little-Wood formular. */
    static const stdair::ProtectionLevel_T computeProtectionLevel (stdair::VirtualClassStruct&, stdair::VirtualClassStruct&);

    /** Compute the EMSR value of a class/bucket. */
    static const double computeEmsrValue (double, stdair::VirtualClassStruct&);
  };
}
#endif // __RMOL_EMSRUTILS_HPP
