// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
#include <latus/com/basic/BasConst_WholeDemand.hpp>
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/factory/FacWholeDemand.hpp>
// LATUS DEG
#include <latus/deg/command/DemandParserHelper.hpp>
#include <latus/deg/command/DemandParser.hpp>
#include <latus/deg/command/DemandGenerator.hpp>

namespace LATUS {

  namespace DEG {

    // //////////////////////////////////////////////////////////////////////
    COM::WholeDemand& DemandParser::
    generateDemands (const std::string& iFilename) {
      COM::WholeDemand& oWholeDemand = COM::FacWholeDemand::instance().
        create (COM::DEFAULT_WHOLE_DEMAND_UPDATE_DATE);

      // Initialise the demand file parser.
      DemandFileParser lDemandFileParser (oWholeDemand, iFilename);

      // Parse the CSV-formatted demand input file, and generate the
      // corresponding Demand objects (BOM) for the airlines.
      lDemandFileParser.generateDemands ();

      return oWholeDemand;
    }

  }
}
