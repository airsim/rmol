// STL
#include <iostream>
#include <sstream>
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
double generatePoissonVariate (const double iLambda) {
  const double lMu = 1/iLambda;
  double result = gsl_ran_poisson (_rngPoissonPtr, lMu);
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
    
    // Number of draws
    int K = 1000;

    // Rate (lambda => mu = 1/ lambda)
    double lambda = 10.0;

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
    std::cout << "Index; Exponential; Poisson; " << std::endl;
    for (int i=1; i != K; i++) {
      const double lExponentialVariate = generateExponentialVariate (lambda);
      const double lPoissonVariate = generatePoissonVariate (lambda);
      std::cout << i << "; " << lExponentialVariate << "; "
		<< lPoissonVariate << "; " << std::endl;
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
