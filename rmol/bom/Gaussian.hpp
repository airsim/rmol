#ifndef __RMOL_BOM_GAUSSIAN_HPP
#define __RMOL_BOM_GAUSSIAN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
// RMOL
#include <rmol/basic/DistributionParameters.hpp>

namespace RMOL {

  // ////////// Type definitions //////////
  /** Type definition for the random generator seed.
      <br>That seed must be unsigned, otherwise the wrong overload may be
      selected when using mt19937 as the base_generator_type. */
  typedef unsigned int random_generator_seed_type;

  
  /** Wrapper around a random generator following a normal distribution. */
  struct Gaussian {
  private:
    // ////////// Type definitions //////////
    /** Type definition for a random number generator base (mt19937). */
    typedef boost::minstd_rand base_generator_type;

    /** Type definiton for the normal distribution (characteristics). */
    typedef boost::normal_distribution<> normal_dist_type;
    
    /** Type definition for the normal distribution random generator. */
    typedef boost::variate_generator<base_generator_type&, 
                                     normal_dist_type> normal_gen_type;
  
  public:
    /** Constructor with mean and sigma (standard deviation) for
        the normal Distribution.
        <br>See also
        http://www.boost.org/doc/libs/1_44_0/doc/html/boost/normal_distribution.html */
    Gaussian (const DistributionParameters&);
    
    /** Destructor. */
    ~Gaussian();

    /** Default constructors.
     <br>They are kept private so that the class can be instantiated only
     with the public constructor. */
    Gaussian ();
    Gaussian (const Gaussian&);
    /** Initialise the random generator. */
    void init();
    
  public:
    // /////////////////// Getters //////////////////
    /** Getter for the mean value. */
    double getMean() const;

    /** Getter for the standard deviation value. */
    double getStandardDeviation() const;

    /** Getter for the variance value. */
    double getVariance() const;

    
    /** Generate a Gaussian random variate (following the Gaussian
        distribution). */
    double generateVariate();
    
  private:
    /** Seed of the random generator. */
    const random_generator_seed_type _seed;

    /** Base for the random generator. */
    base_generator_type _generator;

    /** Normal distribution. */
    normal_dist_type _normalDistribution;
    
    /** Random generator for the normal distribution. */
    normal_gen_type _normalDistributionGenerator;
  };

}
#endif // __RMOL_BOM_GAUSSIAN_HPP
