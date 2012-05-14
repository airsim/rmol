/*!
 * \page MRTForNewQFFTestSuite_cpp Command-Line Test to Demonstrate How To Test the RMOL Project
 * \code
 */
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <fstream>
#include <string>
// Boost Unit Test Framework (UTF)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE MRTForNewQFFTestSuite
#include <boost/test/unit_test.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/config/rmol-paths.hpp>

namespace boost_utf = boost::unit_test;

// (Boost) Unit Test XML Report
std::ofstream utfReportStream ("MRTForNewQFFTestSuite_utfresults.xml");

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


// //////////////////////////////////////////////////////////////////////
int testMRTForNewQFFHelper () {

  // Return value
  int oExpectedBookingLimit = 0;

  // Output log File
  std::ostringstream oStr;
  oStr << "MRTForNewQFFTestSuite.log";
  const stdair::Filename_T lLogFilename (oStr.str());
       
  // Set the log parameters
  std::ofstream logOutputFile;
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();

  // Initialise the RMOL service
  const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
  RMOL::RMOL_Service rmolService (lLogParams);

  // Build the default sample BOM tree and build a dummy BOM tree.
  rmolService.buildSampleBom();

  // DEBUG
  STDAIR_LOG_DEBUG ("MRT for New QFF");
  rmolService.MRTForNewQFF();
  const bool isForFareFamilies = true;
  const stdair::SegmentCabin& lSegmentCabin = 
    rmolService.retrieveDummySegmentCabin(isForFareFamilies);
  const stdair::PolicyList_T& lPolicies = lSegmentCabin.getConvexHull();
  //STDAIR_LOG_DEBUG ("Convex Hull: ");
  stdair::PolicyList_T::const_iterator itHull = lPolicies.begin();
  // The first point of the convex hull is the origin
  BOOST_CHECK_MESSAGE (lPolicies.empty() == false,
                       "The convex hull is empty and he should not be.");
  assert(itHull != lPolicies.end());
  const stdair::PolicyStruct& lFirstPolicy = (*itHull);
  const stdair::BookingClassList_T& lFirstPolicyBCList =
    lFirstPolicy.getBookingClasses();
  BOOST_CHECK_MESSAGE (lFirstPolicyBCList.empty() == true,
                       "The booking class list of the first policy of the "
                       "convex hull is not empty and it should be.");
  const stdair::NbOfBookings_T& lFirstPolicyDemand = lFirstPolicy.getDemand();
  BOOST_CHECK_MESSAGE (lFirstPolicyDemand == 0.0,
                       "The demand of the first policy of the convex hull is "
                       << lFirstPolicyDemand << " and it should be 0.");                    
  const stdair::Revenue_T lFirstPolicyRevenue =  lFirstPolicy.getRevenue();
  BOOST_CHECK_MESSAGE (lFirstPolicyRevenue == 0.0,
                       "The revenue of the first policy of the convex hull is "
                       << lFirstPolicyRevenue << " and it should be 0.");   
  ++itHull;
  BOOST_CHECK_MESSAGE (itHull != lPolicies.end(),
                       "The convex hull as only one policy and it should not.");
  assert(itHull != lPolicies.end());
  // The next points have to have a decreasing yield
  stdair::PolicyList_T::const_iterator itNextHull = itHull;
  ++itNextHull;
  for (; itNextHull != lPolicies.end(); ++itNextHull, ++itHull) {
    assert(itHull != lPolicies.end());
    const stdair::PolicyStruct& lHullPolicy = *itHull;
    const stdair::Yield_T& lHullPolicyYield = lHullPolicy.getYield();
    assert(itNextHull != lPolicies.end());
    const stdair::PolicyStruct& lNextHullPolicy = *itNextHull;
    const stdair::Yield_T& lNextHullPolicyYield = lNextHullPolicy.getYield();
    BOOST_CHECK_MESSAGE (lNextHullPolicyYield < lHullPolicyYield,
                         "The yield of the next policy in the convex hull ("
                         << lNextHullPolicyYield << ") is greater or equal than"
                         << " the yield of the current policy ("
                         << lHullPolicyYield << ").");             
    assert(lNextHullPolicyYield < lHullPolicyYield);
  }
  
  STDAIR_LOG_DEBUG ("Convex Hull OK");
  const stdair::SimpleNestingStruct& lNestingStruct = 
    lSegmentCabin.getNestingStruct();
  const stdair::NestingNodeMap_T& lNestingNodeMap = 
    lNestingStruct.getNestingNodeMap();
  itHull = lPolicies.begin();
  itNextHull = itHull;
  ++itNextHull;
  for (stdair::NestingNodeMap_T::const_reverse_iterator itNS = 
       lNestingNodeMap.rbegin(); itNextHull != lPolicies.end(); 
       ++itNextHull, ++itHull, ++itNS) {
    assert(itNS != lNestingNodeMap.rend());
    const stdair::NestingNode_T& lNestingNode = *itNS;
    const stdair::Yield_T& lNestingStructYield = lNestingNode.first;
    assert(itNextHull != lPolicies.end());
    const stdair::PolicyStruct& lHullPolicy = *itNextHull;
    const stdair::Yield_T& lConvexHullYield = lHullPolicy.getYield();
    BOOST_CHECK_MESSAGE (lNestingStructYield == lConvexHullYield,
                         "The yield in the nesting structure ("
                         << lNestingStructYield << ") is different from "
                         "the yield of the convex hull ("
                         << lConvexHullYield << ")");
    assert(lNestingStructYield == lConvexHullYield);
  }
  STDAIR_LOG_DEBUG ("Nesting Structure OK");

  // Close the log file
  logOutputFile.close();
  
  return oExpectedBookingLimit;
}


// /////////////// Main: Unit Test Suite //////////////

// Set the UTF configuration (re-direct the output to a specific file)
BOOST_GLOBAL_FIXTURE (UnitTestConfig);

/**
 * Test different a suite of different revenue management optimisation
 * pieces of algorithm.
 */
BOOST_AUTO_TEST_SUITE (master_test_suite)

/**
 * Test the Monte-Carlo (MC) algorithm
 */
BOOST_AUTO_TEST_CASE (rmol_mrt_for_new_qff) {
  
  // State whether the BOM tree should be built-in or parsed from an input file
  
  BOOST_CHECK_NO_THROW (testMRTForNewQFFHelper(););
}

// End the test suite
BOOST_AUTO_TEST_SUITE_END()

/*!
 * \endcode
 */
