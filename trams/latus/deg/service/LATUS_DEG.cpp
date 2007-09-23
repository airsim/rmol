// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS DEG
#include <latus/deg/command/DemandParser.hpp>
#include <latus/deg/service/LATUS_DEG.hpp>

namespace LATUS {
  
  namespace DEG {

    // //////////////////////////////////////////////////////////////////////
    LATUS_DEG::LATUS_DEG () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_DEG::~LATUS_DEG () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::generateDemands () {
      // Retrieve the demand input filename from the DEG specific
      // service context
      const std::string& lDemandInputFilename = getDemandInputFilename ();

      // Parse the demand input file, and generate the Demand (BOM) objects.
      COM::WholeDemand& lWholeDemand =
        DemandParser::generateDemands (lDemandInputFilename);

      // Store the WholeDemand within the DEG specific service context
      setWholeDemand (lWholeDemand);

      // DEBUG
      LATUS_LOG_DEBUG ("Generated WholeDemand:");
      lWholeDemand.display();
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::generateEvent () const {

    }

  }
}
