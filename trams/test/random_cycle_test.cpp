// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

// Random Generator Type
const gsl_rng_type* _rngTypePtr = NULL;

// Random Generator
gsl_rng* _rngUniformIntPtr = NULL;

typedef std::vector<int> EventNumberList_T;

// ///////////////////////////////////////////////////
void init () {
  // Random Generator type
  _rngTypePtr = gsl_rng_default;

  // Initialise the Random Generator
  gsl_rng_env_setup ();

  // Allocate the memory for the random generator
  _rngUniformIntPtr = gsl_rng_alloc (gsl_rng_rand);
}

// ///////////////////////////////////////////////////
int generateUniformIntVariate (const int iUpperBound) {
  const int result = gsl_rng_uniform_int (_rngUniformIntPtr, iUpperBound);
  return result;
}

// ///////////////////////////////////////////////////
void finalise () {
  gsl_rng_free (_rngUniformIntPtr);
}

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {

    // Initialise random generators
    init();

    // Upper Bound of the uniform integer draws
    int N = 20;

    // Number of loops on N
    int lNumberOfLoops = 100;
    
    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> N;
    }

    if (argc >= 2 && argv[2] != NULL) {
      std::istringstream istr (argv[2]);
      istr >> lNumberOfLoops;
    }
    
    // Counters of events
    EventNumberList_T lEventNbList;

    // Initialise the counters of events to 0
    lEventNbList.reserve (N);
    for (int i=0; i < N; i++) {
      lEventNbList.push_back (0);
    }    

    // Generate/draw the events
    for (int i=0; i < lNumberOfLoops * N; i++) {
      const int lDraw = generateUniformIntVariate (N);
      assert (lDraw >= 0 && lDraw < N);
      
      int& lDrawNb = lEventNbList.at (lDraw);
      lDrawNb++;
    }

    // Display
    EventNumberList_T::const_iterator itEventNb = lEventNbList.begin();
    std::cout << "DTD; # of Draws" << std::endl;
    double std_dev = 0.0;
    for (int i = 0; itEventNb != lEventNbList.end(); itEventNb++, i++) {
      const int lEventNb = *itEventNb;
      const int lDiff = lEventNb - lNumberOfLoops;
      std_dev += lDiff * lDiff;
      
      std::cout << i << "; " << lEventNb << std::endl;
    }
    std_dev = sqrt (std_dev);
    
    std::cout << "std_dev = " << std_dev << std::endl;
    
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
