// STL
#include <iostream>
#include <sstream>
// Boost Date-Time
#include <boost/date_time/posix_time/posix_time.hpp>
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/variate_generator.hpp>
// Boost Math
#include <boost/math/distributions/normal.hpp>
// Extra-CPPUnit
#include <extracppunit/CppUnitCore.hpp>
// RMOL Test Suite
#include <test/rmol/SimulateTestSuite.hpp>

// ////////// Type definitions //////////
/** Type definition for a random number generator base (mt19937). */
typedef boost::minstd_rand base_generator_type;

/** Type definition for the random generator seed.
    <br>That seed must be unsigned, otherwise the wrong overload may be
    selected when using mt19937 as the base_generator_type. */
typedef unsigned int random_generator_seed_type;

/** Type definiton for the Poisson distribution (characteristics). */
typedef boost::poisson_distribution<> poisson_dist_type;
    
/** Type definiton for the exponential distribution (characteristics). */
typedef boost::exponential_distribution<> exponential_dist_type;
    
/** Type definition for the Poisson distribution random generator. */
typedef boost::variate_generator<base_generator_type&, 
                                 poisson_dist_type> poisson_gen_type;

/** Type definition for the exponential distribution random generator. */
typedef boost::variate_generator<base_generator_type&, 
                                 exponential_dist_type> exponential_gen_type;

// //////////////////////////////////////////////////////////////////////
void testSimulateHelper() {

  try {
    
    // Output log File
    std::string lLogFilename ("SimulateTestSuite.log");
    
    // Set the log parameters
    std::ofstream logOutputFile;
    
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Time duration representing a full day
    // (i.e., 24h or 1,440 minutes or 86,400 seconds)
    const boost::posix_time::time_duration kDay (24, 0, 0, 0);
    
    // Length of the Simulation (time-length)
    const int kSimulationLength = 365;
    
    // Rate, expressed as a number of events per day
    // (lambda => mu = 1 / lambda)
    const double lambda = 10.0;
    const double mu = 1 / lambda;
    // mu = 0.1 (= 2.4h, i.e., in average, an event occurs every 2.4h)

    // Initialisation of random generators
    /** Base for the random generator. */
    base_generator_type lGenerator (42u);

    /** Poisson distribution. */
    exponential_dist_type lExponentialDistribution (mu);

    /** Random generator for the Poisson distribution. */
    exponential_gen_type lExponentialDistributionGenerator (lGenerator,
                                                            lExponentialDistribution);

    /** Poisson distribution. */
    poisson_dist_type lPoissonDistribution (lambda);

    /** Random generator for the Poisson distribution. */
    poisson_gen_type lPoissonDistributionGenerator (lGenerator,
                                                    lPoissonDistribution);

    // Generate k draws
    logOutputFile << "Event#; Time; " << std::endl;
    for (int i=1; i != kSimulationLength; i++) {

      // Current time
      boost::posix_time::time_duration lCurrentTime (0, 0, 0, 0);

      // Current number of events
      int lEventNumber = 0;

      // Repeat until the current time exceeds 24h (i.e., 86,400 seconds)
      while (lCurrentTime <= kDay) {
        const double lExponentialVariateDay =
          lExponentialDistributionGenerator();
        const long int lExponentialVariateHours =
          static_cast<long int> (lExponentialVariateDay * 24);
        const boost::posix_time::time_duration lExponentialVariateSeconds =
          boost::posix_time::hours (lExponentialVariateHours);

        // Add an event
        ++lEventNumber;

        // Add the inter-arrival time to the current time
        lCurrentTime += lExponentialVariateSeconds;
        
        // const double lPoissonVariate = lPoissonDistributionGenerator();
        logOutputFile << lEventNumber << "; " << lCurrentTime << "; "
                      << std::endl;
      }
    }
    
    // TODO: check that the average number of events corresponds to the given
    // input

    // Close the log file
    logOutputFile.close();
    
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
