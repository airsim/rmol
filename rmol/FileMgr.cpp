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
        if (i == 1) {
          aYieldRange.setUpperYield (dval);
          aYieldRange.setAverageYield (dval);
          // std::cout << "Yield[" << i << "] = '" << dval << "'" << std::endl;

        } else if (i == 2) {
          aDistribParams.setMean (dval);
          // std::cout << "Mean[" << i << "] = '" << dval << "'" << std::endl;

        } else if (i == 3) {
          aDistribParams.setStandardDeviation (dval);
          //std::cout << "stdDev[" << i << "] = '" << dval << "'" << std::endl;
          i = 0;
        }
        i++;
          
      } else {
        hasAllPArams = false;
      }

      if (hasAllPArams && i == 1) {
        const Demand aDemand (aDistribParams, aYieldRange);
        Bucket aBucket (aYieldRange, aDemand);
        ioBucketHolder.addBucket (aBucket);
      }

    }
    
    if (!inputFile.eof()) {
      std::cerr << "Problem when reading input file \"" << iInputFileName
                << "\"" << std::endl;
    } else {
        const Demand aDemand (aDistribParams, aYieldRange);
        Bucket aBucket (aYieldRange);
        ioBucketHolder.addBucket (aBucket);
    }

  }
  
}
