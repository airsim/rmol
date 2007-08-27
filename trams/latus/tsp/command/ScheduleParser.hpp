#ifndef __LATUS_TSP_CMD_SCHEDULEPARSER_HPP
#define __LATUS_TSP_CMD_SCHEDULEPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace COM {
    class WorldSchedule;
  }
  
  namespace TSP {

    /** Class wrapping the parser entry point. */
    class ScheduleParser : public COM::CmdAbstract {
    public:
      /** Parses the CSV file describing the airline schedules for the
          simulator, and generates the inventories accordingly.
          @param const std::string& The file-name of the CSV-formatted schedule
                 input file. */
      static COM::WorldSchedule& generateInventories (const std::string& iFilename);
    };
    
  }
}
#endif // __LATUS_TSP_CMD_SCHEDULEPARSER_HPP
