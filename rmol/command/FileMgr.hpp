#ifndef __RMOL_CMD_FILEMGR_HPP
#define __RMOL_CMD_FILEMGR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <string>

// Forward declarations.
namespace stdair {
  class BomRoot;
}

namespace RMOL {  
  /** Class filling the virtual class list (representing
      a list of classes/buckets) from a given input file. */
  class FileMgr {
  public:
    /** Read the input values from a CSV file. */
    static void readAndProcessInputFile (const std::string& iInputFileName,
                                         stdair::BomRoot& ioBomRoot);
    
  };
}
#endif // __RMOL_CMD_FILEMGR_HPP
