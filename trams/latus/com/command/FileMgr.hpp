#ifndef __LATUS_COM_CMD_FILEMGR_HPP
#define __LATUS_COM_CMD_FILEMGR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class BookingDay;
    class WorldSchedule;
    
    /** Class filling the CityPairList structure (representing
        a list of CityPair objects) from a given input file. */
    class FileMgr : CmdAbstract {
    public:

      /** Read the input values from a CSV file for the Demand. */
      static bool
      readAndProcessDemandInputFile (const std::string& iInputFileName,
                                     BookingDay&);
      
      /** Read the input values from a CSV file for the World Schedule. */
      static bool
      readAndProcessWorldScheduleInputFile (const std::string& iInputFileName,
                                            WorldSchedule&);

    };
  }
}
#endif // __LATUS_COM_CMD_FILEMGR_HPP
