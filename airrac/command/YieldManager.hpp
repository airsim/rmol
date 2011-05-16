#ifndef __AIRRAC_CMD_YIELDMANAGER_HPP
#define __AIRRAC_CMD_YIELDMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>

/// Forward declarations
namespace stdair {
  class BomRoot;
  class SegmentDate;
  class TimePeriod;
}

namespace AIRRAC {

  /**
   * @brief Command wrapping the travel request process.
   */
  class YieldManager {
    /**
     * Only the AIRRAC_Service may access to the methods of that class.
     */
    friend class AIRRAC_Service;

  private:
    /**
     * Calculate/retrieve the yield for a given travel solution.
     */
    static void calculateYield (stdair::TravelSolutionList_T&,
                                const stdair::BomRoot&);

    /**
     * Calculate/retrieve the yield for a given travel solution.
     */
    static void calculateYield (stdair::TravelSolutionStruct&,
                                const stdair::BomRoot&);

    /**
     * Update the yield for all the classes.
     */
    static void updateYields (const stdair::BomRoot&);
    static void updateYields (const stdair::SegmentDate&,
                              const stdair::TimePeriod&,
                              const stdair::AirlineCode_T&);

  private:
    /**
     * Constructor.
     */
    YieldManager();

    /**
     * Copy constructor.
     */
    YieldManager(const YieldManager&);

    /**
     * Destructor.
     */
    ~YieldManager();
  };

}
#endif // __AIRRAC_CMD_YIELDMANAGER_HPP
