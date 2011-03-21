#ifndef __RMOL_CMD_INVENTORYPARSER_HPP
#define __RMOL_CMD_INVENTORYPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/command/CmdAbstract.hpp>

/// Forward declarations
namespace stdair {
  class BomRoot;
  class LegCabin;
  class SegmentCabin;
}

namespace RMOL {  

  /**
   * @brief Class filling the virtual class list (representing a list
   * of classes/buckets) from a given input inventory.
   */
  class InventoryParser : public stdair::CmdAbstract {
  public:
    /**
     * Get the sample leg-cabin (for optimisation).
     *
     * @param stdair::BomRoot& The BOM tree.
     */
    static stdair::LegCabin& getSampleLegCabin (stdair::BomRoot&);
    
    /**
     * Get the sample leg-cabin (for optimisation).
     *
     * @param stdair::BomRoot& The BOM tree.
     */
    static stdair::SegmentCabin& getSampleSegmentCabin (stdair::BomRoot&);
    
    /**
     * Parse the input values from a CSV-formatted inventory file.
     *
     * @param const std::string& iInputFileName Inventory file to be parsed.
     * @param stdair::BomRoot& The BOM tree.
     * @return bool Whether or not the parsing was successful.
     */
    static bool parseInputFileAndBuildBom (const std::string& iInputFileName,
                                           stdair::BomRoot&);
  };
}
#endif // __RMOL_CMD_INVENTORYPARSER_HPP
