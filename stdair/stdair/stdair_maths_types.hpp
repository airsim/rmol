#ifndef __STDAIR_STDAIR_MATHS_TYPES_HPP
#define __STDAIR_STDAIR_MATHS_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <map>
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /** Define the replication number. */
  typedef unsigned int ReplicationNumber_T;

  /** Define the seed type of an Exponential function. */
  typedef unsigned long int ExponentialSeed_T;

  /** Define the seed type of an Uniform function. */
  typedef unsigned long int UniformSeed_T;

  /** Seed for the random generation, so that it can be reproductible. */
  typedef unsigned long int RandomSeed_T;
  
  /** Random number generator. */
  typedef boost::minstd_rand BaseGenerator_T;

  /** Uniform random generator. */
  typedef boost::variate_generator<stdair::BaseGenerator_T&,
                                   boost::uniform_real<> > UniformGenerator_T;

  /** Define a mean value (e.g., 20.2). */
  typedef double MeanValue_T;

  /** Define a standard deviation value (e.g., 1.5). */
  typedef double StdDevValue_T;

  /** Probability */
  typedef float Probability_T;

}
#endif // __STDAIR_STDAIR_MATHS_TYPES_HPP
