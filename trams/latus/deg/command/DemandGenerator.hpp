#ifndef __LATUS_DEG_CMD_DEMANDGENERATOR_HPP
#define __LATUS_DEG_CMD_DEMANDGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class WholeDemand;
  }
  
  namespace DEG {

    // Forward declarations
    struct DemandStruct_T;

    /** Class generating the Demand BOM structure. */
    class DemandGenerator : public COM::CmdAbstract {
    public:
      static void createDemands (COM::WholeDemand&, const DemandStruct_T&);
    private:
    };

  }
}
#endif // __LATUS_DEG_CMD_DEMANDGENERATOR_HPP
