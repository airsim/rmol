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

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    
    // Time duration representing a full day
    // (i.e., 24h or 1,440 minutes or 86,400 seconds)
    const boost::posix_time::time_duration kDay (24, 0, 0, 0);
    
    // Length of the Simulation (time-length)
    const int kSimulationLength = 365;
    
    // Number of draws
    int K = 1000;

    // Rate, expressed as a number of events per day
    // (lambda => mu = 1/ lambda)
    double lambda = 10.0;
    // mu = 0.1 (= 2.4h, i.e., in average, an event occurs every 2.4h)

    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> K;
    }

    if (argc >= 2 && argv[1] != NULL) {
      std::istringstream istr (argv[2]);
      istr >> lambda;
    }

    // Initialisation of random generators
    init();

    // Generate k draws
    std::cout << "Event#; Time; " << std::endl;
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
        
        std::cout << lEventNumber << "; " << lCurrentTime << "; " << std::endl;
      }
    }
    
    // Cleaning of random generators
    finalise();
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
