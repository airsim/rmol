// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <fstream>
#include <string>
// MPL
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <test/stdair/StdairTestLib.hpp>

/**
 * Namespace gathering classes and structures for test purposes
 */
namespace stdair_test {
  
  /** BookingClass */
  struct BookingClass {
    std::string _classCode;
    /** Constructor. */
    BookingClass (const std::string& iClassCode)
      : _classCode (iClassCode) {
    }
    
    /** Display .*/
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _classCode;
      return oStr.str();
    }
  };
  
  /** Cabin */
  struct Cabin {
    BookingClass _bookingClass;
    Cabin (const BookingClass& iBkgClass)
      : _bookingClass (iBkgClass) {
    }
    
    /** Display .*/
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _bookingClass._classCode;
      return oStr.str();
    }
    
    /** Child type. */
    typedef BookingClass child;
  };
}

// //////////////////////////////////////////////////////////////////////
void StdairTestLib::testMPLStructure() {

  // Output log File
  const std::string lLogFilename ("testMPLStructure.log");
    
  // Set the log parameters
  std::ofstream logOutputFile;

  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the stdair BOM
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);
    
  // DEBUG
  STDAIR_LOG_DEBUG ("StdAir service initialised");
  
  typedef boost::mpl::vector<stdair_test::BookingClass> MPL_BookingClass;
  typedef boost::mpl::push_back<MPL_BookingClass,
                                stdair_test::Cabin>::type types;

  const stdair_test::BookingClass lA ("A");
  const stdair_test::Cabin lCabin (lA);

  // lCabin::type
  if (boost::is_same<stdair_test::BookingClass,
                     stdair_test::Cabin::child>::value) {
    STDAIR_LOG_DEBUG ("The type of the child of a Cabin is a BookingClass");

  } else {
    STDAIR_LOG_DEBUG ("The type of " << lCabin.toString()
                              << " is unknown");
  }
  
  if (boost::is_same<boost::mpl::at_c<types, 1>::type,
                     stdair_test::Cabin>::value) {
    STDAIR_LOG_DEBUG ("The 2nd type is STDAIR::Cabin");
    
  } else {
    STDAIR_LOG_ERROR ("Problem!");
  }

BOOST_MPL_ASSERT ((boost::is_same<boost::mpl::at_c<types, 1>::type,
                                  stdair_test::Cabin>));
}

// //////////////////////////////////////////////////////////////////////
void StdairTestLib::testServiceInitialisation() {

  // Output log File
  const std::string lLogFilename ("testServiceInitialisation.log");
    
  // Set the log parameters
  std::ofstream logOutputFile;
  
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  // Initialise the stdair BOM
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);

  // DEBUG
  STDAIR_LOG_DEBUG ("StdAir service initialised");
}

// //////////////////////////////////////////////////////////////////////
void StdairTestLib::testBomStructureInstantiation() {
  
  // Test create objects.
    
  // Output log File
  std::string lLogFilename ("testBomStructureInstantiation.log");
  
  // Set the log parameters
  std::ofstream logOutputFile;
  // open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
  
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  stdair::STDAIR_Service stdairService (lLogParams);
  
  // DEBUG
  STDAIR_LOG_DEBUG ("StdAir service initialised");
    
  // Close the Log outputFile
  logOutputFile.close();
}

// //////////////////////////////////////////////////////////////////////
bool StdairTestLib::testErrorCase() {
  return false;
}
