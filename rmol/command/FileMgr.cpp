// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <istream>
#include <sstream>
#include <fstream>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/Demand.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/bom/BucketHolder.hpp>
#include <rmol/factory/FacDemand.hpp>
#include <rmol/factory/FacBucket.hpp>
#include <rmol/factory/FacBucketHolder.hpp>
#include <rmol/command/FileMgr.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void FileMgr::readAndProcessInputFile (const std::string& iInputFileName,
                                         BucketHolder& ioBucketHolder) {

    // Open the input file
    std::ifstream inputFile (iInputFileName.c_str());
    if (! inputFile) {
      STDAIR_LOG_ERROR ("Can not open input file \"" << iInputFileName << "\"");
      throw new FileNotFoundException();
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
        Demand& aDemand = 
          FacDemand::instance().create (aDistribParams, aYieldRange);
        Bucket& aBucket = FacBucket::instance().create (aYieldRange, aDemand);
        FacBucketHolder::instance().addBucket (ioBucketHolder, aBucket);
      }

    }
    
    if (!inputFile.eof()) {
      std::cerr << "Problem when reading input file \"" << iInputFileName
                << "\"" << std::endl;
    } else {
      if (i == 2) {
        //const Demand& aDemand = 
	//  FacDemand::instance().create (aDistribParams, aYieldRange);
        Bucket& aBucket = FacBucket::instance().create (aYieldRange);
	FacBucketHolder::instance().addBucket (ioBucketHolder, aBucket);
      }
    }

  }
  
}
