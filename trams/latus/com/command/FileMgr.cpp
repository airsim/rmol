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
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/factory/FacBookingDay.hpp>
#include <latus/com/factory/FacWorldSchedule.hpp>
#include <latus/com/command/FileMgr.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    /* Samples for demand.csv:
      NCE-LAX; 2007-04-21; H; H; 50.0;
      NCE-LAX; 2007-04-21; K; K; 75.0;
      NCE-LAX; 2007-04-30; H; H; 5.0;
      NCE-LAX; 2007-04-30; K; K; 10.0;
      NCE-LAX; 2007-06-20; H; H; 1.0;
      NCE-LAX; 2007-06-20; K; K; 4.0;
      NCE-MIA; 2007-04-21; H; H; 25.0;
      NCE-MIA; 2007-04-21; K; K; 37.5;
      NCE-MIA; 2007-04-30; H; H; 2.5;
      NCE-MIA; 2007-04-30; K; K; 0.5;
      NCE-MIA; 2007-06-20; H; H; 0.5;
      NCE-MIA; 2007-06-20; K; K; 2.0;
    */


    // ////////////////////////////////////////////////////////////////////
    bool FileMgr::
    readAndProcessDemandInputFile (const std::string& iInputFileName,
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

      std::string aOriginStr;
      std::string aDestinationStr;
      std::string aCabinCode;
      std::string aClassCode;
      boost::gregorian::date aDepDate;
      double aMean = 0.0;
    
      while (inputFile.getline (buffer, sizeof (buffer), ';')) {
        std::istringstream iStringStr (buffer);

        bool hasRead = false;

        if (i == 1) {
          hasAllPArams = true;
        }

        if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5) {
          hasRead = (iStringStr >> dvalStr);
        }

        if (i == 6) {
          hasRead = (iStringStr >> dval);

        }

        if (hasRead) {
          if (i == 1) {
            aOriginStr = dvalStr;

          } else if (i == 2) {
            aDestinationStr = dvalStr;
            // std::cout << "City Pair = '" << aOriginStr
            //   << "-" << aDestinationStr << "'" << std::endl;
            
          } else if (i == 3) {
            aDepDate = boost::gregorian::from_simple_string (dvalStr);
            //  std::cout << "Date = '" << aDepDate << "'" << std::endl;

          } else if (i == 4) {
            aCabinCode = dvalStr;
            //  std::cout << "Cabin Code = '" << aCabinCode << "'" << std::endl;

          } else if (i == 5) {
            aClassCode = dvalStr;
            //  std::cout << "Class Code = '" << aClassCode << "'" << std::endl;

          } else if (i == 6) {
            aMean = dval;
            // std::cout << "Mean = '" << aMean << "'" << std::endl;

            const double lStdDev = 0.0;
            FacBookingDay::createClassPath (ioBookingDay,aOriginStr,
                                            aDestinationStr, aDepDate,
                                            aCabinCode, aClassCode,
                                            aMean, lStdDev);
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


    /* Samples from world_schedule.csv:
       AirlineCode; FlightNumber; DateRangeStart; DateRangeEnd; DOW;
        (list) BoardPoint; OffPoint; BoardTime; OffTime; ElapsedTime;
                 (list)  CabinCode; Capacity;
       BA; 9; 2007-04-20; 2007-04-30; 3;
               LHR; BKK; 22:00; 15:15; 11:15; C; 12; M; 300;
               BKK; SYD; 18:10; 06:05; 08:55; C; 20; M; 250;
       BA; 9; 2007-04-20; 2007-04-30; 124;
               LHR; BKK; 22:00; 15:15; 11:15; C; 12; M; 300;
               BKK; SYD; 18:10; 06:05; 08:55; C; 20; M; 250;
       BA; 179; 2007-04-20; 2007-04-30; 3;
               LHR; JFK; 18:05; 20:45; 07:40; C; 12; M; 300;
       BA; 179; 2007-04-20; 2007-04-30; 124;
               LHR; JFK; 18:05; 20:45; 07:40; C; 12; M; 300;
       AA; 585; 2007-04-20; 2007-04-30; 3;
               JFK; MIA; 15:40; 18:50; 03:10; C; 12; M; 300;
       AA; 585; 2007-04-20; 2007-04-30; 124;
               JFK; MIA; 15:40; 18:50; 03:10; C; 12; M; 300;
       AA; 181; 2007-04-20; 2007-04-30; 3;
               JFK; LAX; 17:00; 20:00; 06:00; C; 12; M; 300;
       AA; 181; 2007-04-20; 2007-04-30; 124;
               JFK; LAX; 17:00; 20:00; 06:00; C; 12; M; 300;
    */
    
    // ////////////////////////////////////////////////////////////////////
    bool FileMgr::
    readAndProcessWorldScheduleInputFile (const std::string& iInputFileName,
                                          WorldSchedule& ioWorldSchedule) {
/*
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
            FacBookingDay::createClassPath (ioBookingDay, aCityPairStr,
                                            aDepDate, aClassPath,
                                            aMean, lStdDev);

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
*/
      return true;
    }
    
  }  
}
