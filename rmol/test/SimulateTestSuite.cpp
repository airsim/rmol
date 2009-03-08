// STL
#include <iostream>
#include <sstream>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_randist.h>
// CPPUNIT
#include <test/com/CppUnitCore.hpp>
// RMOL Test Suite
#include <test/SimulateTestSuite.hpp>

// Random Generator Type
const gsl_rng_type* _rngTypePtr = NULL;

// Random Generator
gsl_rng* _rngExponentialPtr = NULL;
gsl_rng* _rngPoissonPtr = NULL;

// ///////////////////////////////////////////////////
void init () {
  // Random Generator type
  _rngTypePtr = gsl_rng_default;

  // Initialise the Random Generator
  gsl_rng_env_setup ();

  // Allocate the memory for the random generator
  _rngExponentialPtr = gsl_rng_alloc (_rngTypePtr);
  _rngPoissonPtr = gsl_rng_alloc (_rngTypePtr);
}

// ///////////////////////////////////////////////////
double generateExponentialVariate (const double iLambda) {
  const double lMu = 1/iLambda;
  double result = gsl_ran_exponential (_rngExponentialPtr, lMu);
  return result;
}

// ///////////////////////////////////////////////////
double generatePoissonVariate (const double iMu) {
  double result = gsl_ran_poisson (_rngPoissonPtr, iMu);
  return result;
}

// ///////////////////////////////////////////////////
void finalise () {
  gsl_rng_free (_rngExponentialPtr);
  gsl_rng_free (_rngPoissonPtr);
}

// //////////////////////////////////////////////////////////////////////
void testSimulateHelper() {
  try {
    
    // Output log File
    std::string lLogFilename ("SimulateTestSuite.log");
    
    // Time duration representing a full day
    // (i.e., 24h or 1,440 minutes or 86,400 seconds)
    const boost::posix_time::time_duration kDay (24, 0, 0, 0);
    
    // Length of the Simulation (time-length)
    const int kSimulationLength = 365;
    
    // Number of draws
    const int K = 1000;

    // Rate, expressed as a number of events per day
    // (lambda => mu = 1/ lambda)
    const double lambda = 10.0;
    // mu = 0.1 (= 2.4h, i.e., in average, an event occurs every 2.4h)

    // Initialisation of random generators
    init();

    // Generate k draws
    // std::cout << "Event#; Time; " << std::endl;
    for (int i=1; i != kSimulationLength; i++) {

      // Current time
      boost::posix_time::time_duration lCurrentTime (0, 0, 0, 0);

      // Current number of events
      int lEventNumber = 0;

      // Repeat until the current time exceeds 24h (i.e., 86,400 seconds)
      while (lCurrentTime <= kDay) {
        const double lExponentialVariateDay =
          generateExponentialVariate (lambda);
        const long int lExponentialVariateHours =
          static_cast<long int> (lExponentialVariateDay * 24);
        const boost::posix_time::time_duration lExponentialVariateSeconds =
          boost::posix_time::hours (lExponentialVariateHours);

        // Add an event
        lEventNumber++;

        // Add the inter-arrival time to the current time
        lCurrentTime += lExponentialVariateSeconds;
        
        // const double lPoissonVariate = generatePoissonVariate (lambda);
        
        // std::cout << lEventNumber << "; " << lCurrentTime << "; " << std::endl;
      }
    }
    
    // Cleaning of random generators
    finalise();

    // TODO: check that the average number of events corresponds to the given
    // input
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    
  } catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }
}

// //////////////////////////////////////////////////////////////////////
void SimulateTestSuite::testSimulate() {
  CPPUNIT_ASSERT_NO_THROW (testSimulateHelper(););
}

// //////////////////////////////////////////////////////////////////////
// void SimulateTestSuite::errorCase () {
//  CPPUNIT_ASSERT (false);
// }

// //////////////////////////////////////////////////////////////////////
SimulateTestSuite::SimulateTestSuite () {
  _describeKey << "Running test on RMOL Simulation function";  
}

// /////////////// M A I N /////////////////
CPPUNIT_MAIN()
