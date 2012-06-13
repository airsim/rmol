/*!
 * \page bomsforforecaster_cpp Command-Line Test to Demonstrate How To Test the RMOL Project
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <limits>
#include <sstream>
#include <fstream>
#include <string>
// Boost Unit Test Framework (UTF)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE OptimiseTestSuite
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/config/rmol-paths.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("bomsforforecaster_utfresults.xml");

/**
 * Configuration for the Boost Unit Test Framework (UTF)
 */
struct UnitTestConfig {
  /** Constructor. */
  UnitTestConfig() {
    boost_utf::unit_test_log.set_stream (utfReportStream);
    boost_utf::unit_test_log.set_format (boost_utf::XML);
    boost_utf::unit_test_log.set_threshold_level (boost_utf::log_test_units);
    //boost_utf::unit_test_log.set_threshold_level (boost_utf::log_successful_tests);
  }

  /** Destructor. */
  ~UnitTestConfig() {
  }
};

namespace RMOL {

  /**--------------  BOM: Booking class/bucket data ----------------------- */ 
  struct BookingClassData {

    // Attributes
    double _bookingCount;
    double _fare;
    double _sellupFactor;
    bool _censorshipFlag;
      
    // Constructer
    BookingClassData (const double iBookingCount, const double iFare, 
                      const double iSellupFactor, const bool iCensorshipFlag)
      : _bookingCount(iBookingCount), _fare(iFare), 
        _sellupFactor(iSellupFactor), _censorshipFlag(iCensorshipFlag) {
    }
      
    // Getters
    double getFare () const {
      return _fare;
    }
      
    bool getCensorshipFlag () const {
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
        _censorshipFlag(false) {
    }

    // Add BookingClassData
    void addBookingClassData (BookingClassData& ioBookingClassData) {
      _bookingClassDataList.push_back (&ioBookingClassData);
    }

    // Getters
    stdair::NbOfClasses_T getNumberOfClass () const {
      return _bookingClassDataList.size();
    }

    double getMinimumFare () const {
      return _minimumFare;
    }

    bool getCensorshipFlag () const {
      return _censorshipFlag;
    }

    // Setters
    void setMinimumFare (const double iMinFare) {
      _minimumFare = iMinFare;
    }

    void setCensorshipFlag (const bool iCensorshipFlag) {
      _censorshipFlag = iCensorshipFlag;
    }

    // compute minimum fare 
    void updateMinimumFare() {
      double minFare = std::numeric_limits<double>::max();
      BookingClassDataList_T::iterator itBookingClassDataList;
      for (itBookingClassDataList = _bookingClassDataList.begin();
           itBookingClassDataList != _bookingClassDataList.end();
           ++itBookingClassDataList) {
        BookingClassData* lBookingClassData = *itBookingClassDataList;
        assert (lBookingClassData != NULL);
        
        const double lFare = lBookingClassData->getFare();
        if (lFare < minFare) { 
          minFare = lFare; 
        }
      }
      //
      setMinimumFare(minFare);
    }

    // compute censorship flag for the data set
    void updateCensorshipFlag () {
      bool censorshipFlag = false;
      BookingClassDataList_T::iterator itBookingClassDataList;
      for (itBookingClassDataList = _bookingClassDataList.begin();
           itBookingClassDataList != _bookingClassDataList.end();
           ++itBookingClassDataList) {
        BookingClassData* lBookingClassData = *itBookingClassDataList;
        assert (lBookingClassData != NULL);
        
        const bool lCensorshipFlagOfAClass =
          lBookingClassData->getCensorshipFlag();
        if (lCensorshipFlagOfAClass) {
          censorshipFlag = true;
          break;
        }
      }
      //
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

// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

/**
 * Main test suite
 */
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test the forecasting techniques.
 */
BOOST_AUTO_TEST_CASE (rmol_forecaster) {

  // Output log File
  std::string lLogFilename ("bomsforforecaster.log");
  std::ofstream logOutputFile;

  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();

  // Initialise the RMOL service
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);

  // Initialise the RMOL service
  RMOL::RMOL_Service rmolService (lLogParams);

  // Build a sample BOM tree
  rmolService.buildSampleBom();

  // Register BCDataSet
  RMOL::BookingClassDataSet lBookingClassDataSet;

  // Register BookingClassData
  RMOL::BookingClassData QClassData (10, 100, 1, false);
  RMOL::BookingClassData MClassData (5, 150, 0.8, true);
  RMOL::BookingClassData BClassData (0, 200, 0.6, false);
  RMOL::BookingClassData YClassData (0, 300, 0.3, false);

  // Display
  STDAIR_LOG_DEBUG (QClassData.toString());
  STDAIR_LOG_DEBUG (MClassData.toString());
  STDAIR_LOG_DEBUG (BClassData.toString());
  STDAIR_LOG_DEBUG (YClassData.toString());

  // Add BookingClassData into the BCDataSet
  lBookingClassDataSet.addBookingClassData (QClassData);
  lBookingClassDataSet.addBookingClassData (MClassData);
  lBookingClassDataSet.addBookingClassData (BClassData);
  lBookingClassDataSet.addBookingClassData (YClassData);

  // DEBUG
  STDAIR_LOG_DEBUG (lBookingClassDataSet.toString());

  // Number of classes
  const stdair::NbOfClasses_T lNbOfClass = lBookingClassDataSet.getNumberOfClass();

  // DEBUG
  STDAIR_LOG_DEBUG ("Number of Classes: " << lNbOfClass);

  // Minimum fare
  BOOST_CHECK_NO_THROW (lBookingClassDataSet.updateMinimumFare());
  const double lMinFare = lBookingClassDataSet.getMinimumFare();

  // DEBUG
  STDAIR_LOG_DEBUG ("Minimum fare: " << lMinFare);

  // Censorship flag
  BOOST_CHECK_NO_THROW (lBookingClassDataSet.updateCensorshipFlag());
  const bool lCensorshipFlag = lBookingClassDataSet.getCensorshipFlag();

  // DEBUG
  STDAIR_LOG_DEBUG ("Censorship Flag: " << lCensorshipFlag);

  // Close the log output file
  logOutputFile.close();
}

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */
