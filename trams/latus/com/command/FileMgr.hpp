#ifndef __LATUS_COM_CMD_FILEMGR_HPP
#define __LATUS_COM_CMD_FILEMGR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>
#include <latus/com/bom/CityPairList.hpp>

namespace LATUS {

  namespace COM {
    
    /** Class filling the CityPairList structure (representing
        a list of CityPair objects) from a given input file. */
    class FileMgr : CmdAbstract {
    public:

      /** Read the input values from a CSV file for the Demand. */
      static bool
      readAndProcessDemandInputFile (const std::string& iInputFileName,
                                     BookingDay&);
      
    };
  }
}
#endif // __LATUS_COM_CMD_FILEMGR_HPP
