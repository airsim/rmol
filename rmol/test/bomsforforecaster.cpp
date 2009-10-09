// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
// #include <cassert>
// STL
#include <sstream>
#include <fstream>
#include <string>
// #include <iostream>
// RMOL
#include <RMOL_Service.hpp>
#include <rmol/service/Logger.hpp>

namespace RMOL {

  /**--------------  BOM: Booking class/bucket data ----------------------- */ 
    struct BookingClassData {

      // Attributes
      double _bookingCount;
      double _fare;
      double _sellupFactor;
      bool _censorshipFlag;
      
      // Constructer
      BookingClassData (double iBookingCount, double iFare, 
                        double iSellupFactor, bool iCensorshipFlag) : 
        _bookingCount(iBookingCount), _fare(iFare), 
        _sellupFactor(iSellupFactor), _censorshipFlag(iCensorshipFlag) {
      }
      
      // Getters
      double getFare () {
        return _fare;
      }
      
      bool getCensorshipFlag () {
        return _censorshipFlag;
      }

      // Display
      std::string toString() const {
        std::ostringstream oStr;
        oStr <<  std::endl 
             << "[Booking class data information]" << std::endl
             << "Booking counter: " << _bookingCount << std::endl
             << "Fare: " << _fare << std::endl
             << "Sell-up Factor: " << _sellupFactor << std::endl
             << "censorshipFlag: " << _censorshipFlag << std::endl;
        return oStr.str();
      }

    };
 
  /**--------------  BOM: Set of BookingClassData ----------------------- */ 
  struct BookingClassDataSet {

    typedef std::vector<BookingClassData*> BookingClassDataList_T;

    // Attributes 
    int _numberOfClass;
    double _minimumFare;
    bool _censorshipFlag; // true if any of the classes is censored
    BookingClassDataList_T _bookingClassDataList;

    // Constructor
    BookingClassDataSet ()
      : _numberOfClass(0), _minimumFare(0),
        _censorshipFlag(false), _bookingClassDataList(NULL) {
    }

    // Add BookingClassData
    void addBookingClassData (BookingClassData* iBookingClassData) {
      _bookingClassDataList.push_back(iBookingClassData);
    }

    // Getters
    int getNumberOfClass () {
      return _bookingClassDataList.size();
    }

    double getMinimumFare () {
      return _minimumFare;
    }

    bool getCensorshipFlag () {
      return _censorshipFlag;
    }

    // Setters
    void setMinimumFare (double iMinFare) {
      _minimumFare = iMinFare;
    }

    void setCensorshipFlag (bool iCensorshipFlag) {
      _censorshipFlag = iCensorshipFlag;
    }

    // compute minimum fare 
    void calculateMinimumFare() {
      double minFare = 1000000;
      BookingClassDataList_T::iterator itBookingClassDataList;
      for (itBookingClassDataList = _bookingClassDataList.begin();
           itBookingClassDataList != _bookingClassDataList.end();
           ++itBookingClassDataList) {
        BookingClassData* lBookingClassData = *itBookingClassDataList;
        double lFare = lBookingClassData->getFare();
        if (lFare < minFare) { 
          minFare = lFare; 
        }
      }
      setMinimumFare(minFare);
    }

    // compute censorship flag for the data set
    void calculateCensorshipFlag () {
      bool censorshipFlag = false;
      BookingClassDataList_T::iterator itBookingClassDataList;
      for (itBookingClassDataList = _bookingClassDataList.begin();
           itBookingClassDataList != _bookingClassDataList.end();
           ++itBookingClassDataList) {
        BookingClassData* lBookingClassData = *itBookingClassDataList;
        bool lCensorshipFlagOfAClass = lBookingClassData -> getCensorshipFlag();
        if (lCensorshipFlagOfAClass) {
          censorshipFlag = true;
          break;
        }
      }
      setCensorshipFlag(censorshipFlag);
    }
    
    // Display
    std::string toString() const {
      std::ostringstream oStr;
      oStr << std::endl
           << "[Booking class data set information]" << std::endl
           << "Number of classes: " << _numberOfClass << std::endl
           << "Minimum fare: " << _minimumFare << std::endl
           << "The data of the class set are sensored: " << _censorshipFlag
           << std::endl;
      return oStr.str();
    }

  };

  // /**-------------- BOM : Q-Forecaster ----------------------- */ 
  // struct QForecaster {

  //   // Function focused BOM

  //   // 1. calculate sell up probability for Q-eq

  //   // 2. calculate Q-Equivalent Booking
  //   double calculateQEqBooking (BookingClassDataSet& iBookingClassDataSet) {
  //     double lQEqBooking = 0.0;
  //     double lMinFare = iBookingClassDataSet.getMinimumFare();


  //     return lQEqBooking;
  //   }
    
  //   /* Calculate Q-equivalent demand 
  //      [<- performed by unconstrainer if necessary (Using ExpMax BOM)] 
  //   */

   
  //   // 3. Partition to each class

  //   // 
    
  // };

}

// ////////////// M A I N ///////////////
int main (int argc, char* argv[]) {

  // Output log File
  std::string lLogFilename ("./bomsforforecaster.log");
  std::ofstream logOutputFile;

  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  RMOL::RMOL_Service lRmolService(logOutputFile);

  // Register BCDataSet
  RMOL::BookingClassDataSet lBookingClassDataSet;

  // Register BookingClassData
  RMOL::BookingClassData QClassData (10, 100, 1, false );
  RMOL::BookingClassData MClassData (5, 150, 0.8, true);
  RMOL::BookingClassData BClassData (0, 200, 0.6, false);
  RMOL::BookingClassData YClassData (0, 300, 0.3, false);

  // Display
  RMOL_LOG_DEBUG(QClassData.toString());
  RMOL_LOG_DEBUG(MClassData.toString());
  RMOL_LOG_DEBUG(BClassData.toString());
  RMOL_LOG_DEBUG(YClassData.toString());

  // Add BookingClassData into the BCDataSet
  lBookingClassDataSet.addBookingClassData( &QClassData );
  lBookingClassDataSet.addBookingClassData( &MClassData );
  lBookingClassDataSet.addBookingClassData( &BClassData );
  lBookingClassDataSet.addBookingClassData( &YClassData );

  //Display
  RMOL_LOG_DEBUG( lBookingClassDataSet.toString() );

  // Number of classes
  int lNoOfClass = lBookingClassDataSet.getNumberOfClass();
  RMOL_LOG_DEBUG( "Number of Classes: " << lNoOfClass );

  // Minimum fare
  lBookingClassDataSet.calculateMinimumFare();
  double lMinFare = lBookingClassDataSet.getMinimumFare();
  RMOL_LOG_DEBUG( "Minimum fare: " << lMinFare );

  // Censorship flag
  lBookingClassDataSet.calculateCensorshipFlag();
  double lCensorshipFlag = lBookingClassDataSet.getCensorshipFlag();
  RMOL_LOG_DEBUG( "Censorship Flag: " << lCensorshipFlag );

  // Close the log output file
  logOutputFile.close();
  return 0;

}
