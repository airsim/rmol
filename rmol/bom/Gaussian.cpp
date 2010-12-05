
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_randist.h>
// RMOL
#include <rmol/bom/Gaussian.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  Gaussian::Gaussian () :
    _rngTypePtr (gsl_rng_default), _rngPtr (NULL),
    _params (FldDistributionParameters()) {
    initRandomGenerator();
  }
  
  // //////////////////////////////////////////////////////////////////////
  Gaussian::Gaussian (const Gaussian& iGaussian) :
    _rngTypePtr (gsl_rng_default), _rngPtr (NULL),
    _params (iGaussian.getDistributionParameters()) {
    initRandomGenerator();
  }

  // //////////////////////////////////////////////////////////////////////
  Gaussian::Gaussian (const FldDistributionParameters& iParams) :
    _rngTypePtr (gsl_rng_default), _rngPtr (NULL),
    _params (FldDistributionParameters (iParams.getMean(), 
					iParams.getStandardDeviation())) {
    initRandomGenerator();
  }
  
  // //////////////////////////////////////////////////////////////////////
  Gaussian::~Gaussian() {
    // Release the memory for the random generator
    gsl_rng_free (_rngPtr);
  }
  
  // //////////////////////////////////////////////////////////////////////
  double Gaussian::getMean() const {
    return _params.getMean();
  }
  
  // //////////////////////////////////////////////////////////////////////
  double Gaussian::getStandardDeviation() const {
    return _params.getStandardDeviation();
  }

  
  // //////////////////////////////////////////////////////////////////////
  double Gaussian::getVariance() const {
    return _params.getVariance();
  }

  // //////////////////////////////////////////////////////////////////////
  void Gaussian::initRandomGenerator () {
    // Initialise the Random Generator
    gsl_rng_env_setup ();

    // Allocate the memory for the random generator
    _rngPtr = gsl_rng_alloc (_rngTypePtr);
  }

  // //////////////////////////////////////////////////////////////////////
  double Gaussian::generateVariate () const {

    const double mean = getMean();
    const double standardDeviation = getStandardDeviation();
    
    double result = gsl_ran_gaussian (_rngPtr, standardDeviation);
    result += mean;
    
    return result;
  }

}
