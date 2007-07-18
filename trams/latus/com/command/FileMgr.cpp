// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/factory/FacBookingDay.hpp>
#include <latus/com/command/FileMgr.hpp>

namespace LATUS {

  namespace COM {

    /* Samples for demand.csv:
      NCE-LAX; 2007-04-21; H-H; 50.0;
      NCE-LAX; 2007-04-21; K-K; 75.0;
      NCE-LAX; 2007-04-30; H-H; 5.0;
      NCE-LAX; 2007-04-30; K-K; 10.0;
      NCE-LAX; 2007-06-20; H-H; 1.0;
      NCE-LAX; 2007-06-20; K-K; 4.0;
      NCE-MIA; 2007-04-21; H-H; 25.0;
      NCE-MIA; 2007-04-21; K-K; 37.5;
      NCE-MIA; 2007-04-30; H-H; 2.5;
      NCE-MIA; 2007-04-30; K-K; 0.5;
      NCE-MIA; 2007-06-20; H-H; 0.5;
      NCE-MIA; 2007-06-20; K-K; 2.0;
    */


    // ////////////////////////////////////////////////////////////////////
    bool FileMgr::
    readAndProcessInputFile (const std::string& iInputFileName,
                             BookingDay& ioBookingDay) {
      
      // Open the input file
      std::ifstream inputFile (iInputFileName.c_str());
      if (! inputFile) {
        return false;
      }
    
      char buffer[80];
      double dval = 0.0;
      std::string dvalStr;
      short i = 1;
      bool hasAllPArams = true;

      std::string aCityPairStr;
      std::string aClassPath;
      boost::gregorian::date aDepDate;
      double aMean = 0.0;
    
      while (inputFile.getline (buffer, sizeof (buffer), ';')) {
        std::istringstream iStringStr (buffer);

        bool hasRead = false;

        if (i == 1) {
          hasAllPArams = true;
        }

        if (i == 1 || i == 2 || i == 3) {
          hasRead = (iStringStr >> dvalStr);
        }

        if (i == 4) {
          hasRead = (iStringStr >> dval);
        }
      
        if (hasRead) {
          if (i == 1) {
            aCityPairStr = dvalStr;
            // std::cout << "City Pair = '" << aCityPairStr << "'" << std::endl;

          } else if (i == 2) {
            aDepDate = boost::gregorian::from_simple_string (dvalStr);
            // std::cout << "Date = '" << aDepDate << "'" << std::endl;

          } else if (i == 3) {
            aClassPath = dvalStr;
            // std::cout << "Class Path = '" << aClassPath << "'" << std::endl;

          } else if (i == 4) {
            aMean = dval;
            // std::cout << "Mean = '" << aMean << "'" << std::endl;

            const double lStdDev = 0.0;
            FacBookingDay::instance().
              createClassPath (ioBookingDay, aCityPairStr, aDepDate,
                               aClassPath, aMean, lStdDev);

            i = 0;
          }
          i++;
          
        } else {
          hasAllPArams = false;
        }
      }
    
      if (!inputFile.eof()) {
        std::cerr << "Problem when reading input file \"" << iInputFileName
                  << "\"" << std::endl;
      }

      return true;
    }
  }  
}
