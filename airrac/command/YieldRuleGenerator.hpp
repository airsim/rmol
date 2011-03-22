#ifndef __AIRRAC_CMD_YIELDRULEGENERATOR_HPP
#define __AIRRAC_CMD_YIELDRULEGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/command/CmdAbstract.hpp>
// AirRAC
#include <airrac/AIRRAC_Types.hpp>

namespace stdair {
  class BomRoot;
  class YieldRule;
}

namespace AIRRAC {

  // Forward declarations
  struct YieldRuleStruct;
  namespace YieldParserHelper {
    struct doEndYield;
  }
    
  /** Class handling the generation / instantiation of the Yield BOM. */
  class YieldRuleGenerator : public stdair::CmdAbstract {
    // Only the following class may use methods of YieldGenerator.
    // Indeed, as those methods build the BOM, it is not good to expose
    // them public.
    friend class YieldFileParser;
    friend struct YieldParserHelper::doEndYield;
    friend class YieldParser;
  private:
    /** Generate the yield objects corresponding to the given
        yieldRule and add them to the given BomRoot. */
    static void createYieldRule (stdair::BomRoot&,
                                YieldRuleStruct&);
  };

}
#endif // __AIRRAC_CMD_YIELDRULEGENERATOR_HPP
