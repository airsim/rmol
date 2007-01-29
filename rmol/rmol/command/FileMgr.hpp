#ifndef __RMOL_CMD_FILEMGR_HPP
#define __RMOL_CMD_FILEMGR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <string>

namespace RMOL {

  class BucketHolder;
  
  /** Class filling the BucketHolder structure (representing
      a list of classes/buckets) from a given input file. */
  class FileMgr {
  public:
    /** Read the input values from a CSV file. */
    static void readAndProcessInputFile (const std::string& iInputFileName,
                                         BucketHolder&);
    
  };
}
#endif // __RMOL_CMD_FILEMGR_HPP
