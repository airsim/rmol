#ifndef __RMOL_GAUSSIAN_HPP
#define __RMOL_GAUSSIAN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// RMOL
#include "FldDistributionParameters.hpp"

namespace RMOL {

  /** Gaussian Distribution-based Utilities. */
  class Gaussian {
  public:
    /** Constructors. */
    Gaussian ();
    Gaussian (const Gaussian&);

    /** Constructor with mean and standard deviation of
        the Gaussian Distribution. */
    Gaussian (const double iMean, const double iStandardDeviation);

    /** Destructors. */
    virtual ~Gaussian();

    // Getters
    /** Getter for the parameters for the Gaussian distribution (i.e.,
        mean and standard deviation). */
    FldDistributionParameters getDistributionParameters() const {
      return _params;
    }
    
    /** Getter for the mean value. */
    double getMean() const;

    /** Getter for the standard deviation value. */
    double getStandardDeviation() const;

    /** Getter for the variance value. */
    double getVariance() const;

    
    /** Generate a Gaussian random variate (following the Gaussian
        distribution). */
    double generateVariate () const;
    
  private:
    // Wrapper on GSL Random Generators (type and generator)
    const gsl_rng_type* _rngTypePtr;
    gsl_rng* _rngPtr;

    // Gaussian distribution characteristics
    FldDistributionParameters _params;

  private:
    // Initialise the Random Generator
    void initRandomGenerator();
  };

}
#endif // __RMOL_GAUSSIAN_HPP
