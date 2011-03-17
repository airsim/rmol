#ifndef __AIRRAC_CMD_YIELDMANAGER_HPP
#define __AIRRAC_CMD_YIELDMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
  struct TravelSolutionStruct;
}

namespace AIRRAC {

  /** Command wrapping the travel request process. */
  class YieldManager {
    friend class AIRRAC_Service;
  private:

    /** Calculate/retrieve the yield for a given travel solution. */
    static void calculateYield (stdair::TravelSolutionStruct&,
                                const stdair::BomRoot&);

  private:
    /** Constructors. */
    YieldManager() {}
    YieldManager(const YieldManager&) {}
    /** Destructor. */
    ~YieldManager() {}
  };

}
#endif // __AIRRAC_CMD_YIELDMANAGER_HPP
