#ifndef __LATUS_DEG_CMD_DEMANDPARSER_HPP
#define __LATUS_DEG_CMD_DEMANDPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace DEG {

    /** Class parsing the demand input file and building the Demand Generation
        BOM structure. */
    class DemandParser : public COM::CmdAbstract {
    public:

      /** Parses the CSV file describing the demand for the
          simulator, and generates the demand objects (BOM) accordingly.
          @param const std::string& The file-name of the CSV-formatted demand
                 input file. */
      static COM::WholeDemand& generateDemands (const std::string& iFilename);
      
    private:

    };

  }
}
#endif // __LATUS_DEG_CMD_DEMANDPARSER_HPP
