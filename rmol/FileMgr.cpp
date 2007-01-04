// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
// RMOL
#include "BucketHolder.hpp"
#include "FileMgr.hpp"

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void FileMgr::readAndProcessInputFile (const std::string& iInputFileName,
                                         BucketHolder& ioBucketHolder) {

    // Open the input file
    std::ifstream inputFile (iInputFileName.c_str());
    if (! inputFile) {
      std::cerr << "Can not open input file \"" << iInputFileName << "\""
                << std::endl;
      return;
    }
    
    char buffer[80];
    double dval;
    short i = 1;
    bool hasAllPArams = true;
    FldYieldRange aYieldRange;
    FldDistributionParameters aDistribParams;
    
    while (inputFile.getline (buffer, sizeof (buffer), ';')) {
      std::istringstream iStringStr (buffer);


      if (i == 1) {
        hasAllPArams = true;
      }
      
      if (iStringStr >> dval) {
        std::cout << "value[" << i << "] = '" << dval << "'" << std::endl;
        if (i == 1) {
          aYieldRange.setUpperYield (dval);
          aYieldRange.setAverageYield (dval);
        } else if (i == 2) {
          aDistribParams.setMean (dval);
        } else if (i == 3) {
          aDistribParams.setStandardDeviation (dval);
        }
        i++;
          
      } else {
        hasAllPArams = false;
      }

      if (hasAllPArams) {
        const Demand aDemand (aDistribParams, aYieldRange);
        Bucket aBucket (aYieldRange, aDemand);
        ioBucketHolder.addBucket (aBucket);
      }

    }
    
    if (!inputFile.eof()) {
      std::cerr << "Problem when reading input file \"" << iInputFileName
                << "\"" << std::endl;
    }
  }
  
}
