// STL
#include <iostream>
#include <sstream>
// Boost Date-Time
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/variate_generator.hpp>
// Boost Math
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/weibull.hpp>
// Boost Accumulators
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
// Extra-CPPUnit
#include <extracppunit/CppUnitCore.hpp>
// RMOL Test Suite
#include <test/rmol/SimulateTestSuite.hpp>

// using namespace boost;
namespace ba = boost::accumulators;

// ////////// Type definitions //////////
/** Type definition for a random number generator base (mt19937). */
typedef boost::minstd_rand base_generator_type;

/** Type definition for the random generator seed.
    <br>That seed must be unsigned, otherwise the wrong overload may be
    selected when using mt19937 as the base_generator_type. */
typedef unsigned int random_generator_seed_type;

/** Type definiton for the normal distribution (characteristics). */
typedef boost::normal_distribution<> normal_dist_type;

/** Type definiton for the Poisson distribution (characteristics). */
typedef boost::poisson_distribution<> poisson_dist_type;
    
/** Type definiton for the exponential distribution (characteristics). */
typedef boost::exponential_distribution<> exponential_dist_type;
    
/** Type definition for the normal distribution random generator. */
typedef boost::variate_generator<base_generator_type&, 
                                 normal_dist_type> normal_gen_type;

/** Type definition for the Poisson distribution random generator. */
typedef boost::variate_generator<base_generator_type&, 
                                 poisson_dist_type> poisson_gen_type;

/** Type definition for the exponential distribution random generator. */
typedef boost::variate_generator<base_generator_type&, 
                                 exponential_dist_type> exponential_gen_type;

/** Type definition to gather statistics. */
typedef ba::accumulator_set<double,
                            ba::stats<ba::tag::min, ba::tag::max,
                                      ba::tag::mean (ba::immediate),
                                      ba::tag::sum,
                                      ba::tag::lazy_variance> > stat_acc_type;

class simulation_exception : public std::exception {
public:
  /** Constructor. */
  simulation_exception (const std::string& iWhat) throw() : _what () {}
  ~simulation_exception () throw() {}
  /** Gives the reason of the exception. */
  const char* what() const throw() { return _what.c_str(); }
private:
  std::string _what;
};

// ///////////////////////////////////////////////////
double calculateDailyRate (const boost::gregorian::date iStartDate,
                           const boost::gregorian::date iCurrentDate,
                           const boost::gregorian::date iEndDate,
                           const double iFinalDemandMean) {

  /**
     Note that the following method of pro-rating the daily rate, from
     the final annual demand, may appear cumbersome, as:
     1. We discretise a continuous distribution, just to get a typical
     S-curve booking pattern.
     2. We normalise that distribution, so as to get the corresponding
     cdf (cumulative distribution function) equal to 1 on [0, infinite[.
     3. Moreover, in reality, we should first fit the parameters of that
     S-curve distribution with the corresponding observations.
          
     Therefore, in the final version, we'll certainly use directly the
     discrete distributions corresponding to the observations (historical
     date) made beforehand. But as those observations may be difficult
     to obtain, the following method is just handy for now.
  */

  /**
     The result is the daily rate, expressed as a number of events (per day).
     (lambda => mu = 1/ lambda), e.g., lambda = 10 => mu = 0.1 (= 2.4h,
     i.e., in average, an event occurs every 2.4h).
  */
  double lambda = 0.0001;

  // The first day open to reservation, there is no reservation (lambda = 0)
  if (iStartDate == iCurrentDate) {
    return lambda;
  }
  
  // Simulation length-time (expressed as a number of days)
  const boost::gregorian::date_duration lSimulationLength =
    iEndDate - iStartDate;
  const int lSimulationLengthInDays =
    static_cast<const int> (lSimulationLength.days());

  // DEBUG
  return (iFinalDemandMean / lSimulationLengthInDays);
  
  // Current length-time (expressed as a number of days)
  const boost::gregorian::date_duration lCurrentDuration =
    iCurrentDate - iStartDate;
  const double lCurrentDurationInDays =
    static_cast<const double> (lCurrentDuration.days());
  
  /** Ratio on the x-absciss for the Weibull distribution
      (see ref: http://www.boost.org/doc/libs/1_44_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/dist_ref/dists/weibull.html). */
  const double lXRatio = 2.0 / lSimulationLengthInDays;

  /** The daily rate is pro-rated/weighted according to the
      Weibull distribution (see above for the Boost reference).
      The a and b parameters are taken equal to respectively 2 and 3. */
  boost::math::weibull weibull_distribution (2, 3);
  const double lCurrentDurationInWeibullX = lCurrentDurationInDays * lXRatio;
  const double lPreviousDurationInWeibullX =
    (lCurrentDurationInDays - 1.0) * lXRatio;

  /**
     There's also a normalisation factor, so as the CDF be equal
     to one when x is equal to lSimulationLengthInDays.
     Hence, we're looking for a normalisation constant (let's name it nc)
     such as: f_pdf (x) = nc . Weibull_pdf (lXRatio . x).
     We get:
     nc = lXRatio / Weibull_cdf (lXRatio . lSimulationLengthInDays), and:
     f_cdf (x) = Weibull_cdf (lXRatio . x)
     / Weibull_cdf (lXRatio . lSimulationLengthInDays).
  */
  const double lSimulationLengthInWeibullX = lSimulationLengthInDays * lXRatio;
  const double lNormalisationConstant =
    1 / boost::math::cdf (weibull_distribution, lSimulationLengthInWeibullX);
  // gsl_cdf_weibull_P (lSimulationLengthInWeibullX, 2, 3);
  
  const double lDailyIncrementalRate = lNormalisationConstant
    * (boost::math::cdf (weibull_distribution, lCurrentDurationInWeibullX)
       - boost::math::cdf (weibull_distribution, lPreviousDurationInWeibullX));

  lambda = iFinalDemandMean * lDailyIncrementalRate;

  return lambda;
}

// //////////////////////////////////////////////////////////////////////
void testSimulateHelper() {

  // Output log File
  std::string lLogFilename ("SimulateTestSuite.log");
    
  // Set the log parameters
  std::ofstream logOutputFile;
    
  // Open and clean the log outputfile
  logOutputFile.open (lLogFilename.c_str());
  logOutputFile.clear();
    
  // Time duration representing a full day
  // (i.e., 24h or 1,440 minutes or 86,400 seconds)
  const boost::posix_time::time_duration kDay = boost::posix_time::hours(24);
  const int kDayInSeconds = static_cast<const int> (kDay.total_seconds());
  const boost::gregorian::date_duration kDayDuration (1);
    
  // Simulation length (time length) / date range for the simulation
  const boost::gregorian::date kStartDate (2007, boost::gregorian::Jan, 1);
  const boost::gregorian::date kEndDate (2008, boost::gregorian::Jan, 1);
    
  // Length of the Simulation (number of runs)
  int K = 10;

  // Final demand (i.e., number of passengers) for the given simulated
  // flight-date
  const double lFinalDemandMean = 300.0;
  const double lFinalDemandStandardDeviation = 17.32;

  // Initialisation of random generators
  /** Base for the random generator. */
  base_generator_type lGenerator (42u);

  // Statistical accumulators for the respective numbers to watch
  stat_acc_type lLambdaSumAcc;
  stat_acc_type lTotalEventNumberAcc;
  stat_acc_type lGaussianVariateAcc;

  // Total number of events
  int lTotalEventNumber = 0;
    
  // Consistency check: check that the sum of the daily lambdas equals to the
  // final demand mean
  double lLambdaSum = 0.0;
        
  // Perform K simulations    
  for (int i=0; i != K; i++) {
    // Re-initialisaton of the current date
    boost::gregorian::date lCurrentDate = kStartDate;
      
    // Generate 1 year of draws

    // Reset the total number of events for the current simulation
    lTotalEventNumber = 0;

    // Reset the sum of lambdas
    lLambdaSum = 0.0;
        
    // DEBUG
    /*
      std::cout << "Start date: " << kStartDate << "; End date: " << kEndDate
      << std::endl;
    */
        
    while (lCurrentDate < kEndDate) {
      // Calculate the daily rate of events (bookings)
      const double lambda = calculateDailyRate (kStartDate, lCurrentDate,
                                                kEndDate, lFinalDemandMean);
      // const double mu = 1 / lambda;

      // DEBUG
      /*
        std::cout << "Current date: " << lCurrentDate
        << "; Final demand mean: " << lFinalDemandMean
        << "; Lambda: " << lambda << "; mu: " << mu << std::endl;
      */

      /** Poisson distribution. */
      poisson_dist_type lPoissonDistribution (lambda);

      /** Random generator for the Poisson distribution. */
      poisson_gen_type lPoissonDistributionGenerator (lGenerator,
                                                      lPoissonDistribution);

      /** Exponential distribution
          <br>Note: Boost.Math exponential distribution takes lambda as
          the parameter, whereas the GSL (GNU Scientific Library) takes
          mu (== 1/lambda). */
      exponential_dist_type lExponentialDistribution (lambda);

      /** Random generator for the exponential distribution. */
      exponential_gen_type lExponentialDistributionGenerator (lGenerator,
                                                              lExponentialDistribution);

      //
      lLambdaSum += lambda;
        
      // Current time
      boost::posix_time::time_duration lCurrentTime (0, 0, 0, 0);

      // Current number of events
      int lDailyEventNumber = 0;

      // Repeat until the current time exceeds 24h (i.e., 86,400 seconds)
      while (lCurrentTime <= kDay) {
        // Generate a random variate, expressed in (fractional) day
        const double lExponentialVariateInDays =
          lExponentialDistributionGenerator();

        // Convert the variate in a number of seconds
        const int lExponentialVariateInSeconds =
          static_cast<const int> (lExponentialVariateInDays * kDayInSeconds);

        // Convert the variate in a (Boost typedef) time duration
        const boost::posix_time::time_duration lExponentialVariate =
          boost::posix_time::seconds (lExponentialVariateInSeconds);

        // Add an event
        lDailyEventNumber++; lTotalEventNumber++;

        // Add the inter-arrival time to the current time
        lCurrentTime += lExponentialVariate;
        
        // const double lPoissonVariate = lPoissonDistributionGenerator();

        /* DEBUG
           logOutputFile << lCurrentDate << "; " << lTotalEventNumber << "; "
           << lDailyEventNumber << "; " << lCurrentTime << "; "
           << std::endl;
        */
      }

      // When the booking day is over, there's an additional event
      // (the first one made after the booking date)
      lTotalEventNumber--; lDailyEventNumber--;
      
      // DEBUG
      /**
         logOutputFile << i << "; " << lCurrentDate << "; " << lambda << "; "
         << lDailyEventNumber << "; " << lTotalEventNumber << "; "
         << std::endl;
      */
        
      // Add a day
      lCurrentDate += kDayDuration;
    }

    // Generate a Gaussian variate, just in order to compare the final
    // distributions (Gaussian and accumulated Poissonian).
    /** Normal distribution. */
    normal_dist_type lNormalDistribution (lFinalDemandMean,
                                          lFinalDemandStandardDeviation);

    /** Random generator for the normal distribution. */
    normal_gen_type lNormalDistributionGenerator (lGenerator,
                                                  lNormalDistribution);

    const double lGaussianVariate = lNormalDistributionGenerator();
      
    // DEBUG
    logOutputFile << "Simulation#; Sum of Lambdas; Total nb of events; "
                  << "Random draw (following normal law);" << std::endl;
    logOutputFile << i << "; " << lLambdaSum << "; "
                  << lTotalEventNumber << "; "
                  << lGaussianVariate << "; " << std::endl;

    // Update the statistics
    lLambdaSumAcc (lLambdaSum);
    lTotalEventNumberAcc (lTotalEventNumber);
    lGaussianVariateAcc (lGaussianVariate);
  }
    
  // DEBUG
  logOutputFile << "Statistics for sum of Lambdas (min, max, mean, variance);"
                << std::endl;
  logOutputFile << ba::min (lLambdaSumAcc) << ", "
                << ba::max (lLambdaSumAcc) << ", "
                << ba::mean (lLambdaSumAcc) << ", "
                << ba::variance (lLambdaSumAcc) << "; " << std::endl;
  logOutputFile<<"Statistics for total nb of events (min, max, mean, variance);"
                << std::endl;
  logOutputFile << ba::min (lTotalEventNumberAcc) << ", "
                << ba::max (lTotalEventNumberAcc) << ", "
                << ba::mean (lTotalEventNumberAcc) << ", "
                << ba::variance (lTotalEventNumberAcc) << "; " << std::endl;
  logOutputFile << "Statistics for random draws (min, max, mean, variance);"
                << std::endl;
  logOutputFile << ba::min (lGaussianVariateAcc) << ", "
                << ba::max (lGaussianVariateAcc) << ", "
                << ba::mean (lGaussianVariateAcc) << ", "
                << ba::variance (lGaussianVariateAcc) << "; "
                << std::endl;

  // Checking that the number of daily events follows a distribution
  if (ba::mean (lTotalEventNumberAcc)
      < lFinalDemandMean - lFinalDemandStandardDeviation
      || ba::mean (lTotalEventNumberAcc)
      > lFinalDemandMean + lFinalDemandStandardDeviation) {
    throw simulation_exception ("The mean of the total number of events is not in the expected range");
  }

  // Checking that the random draws follow a normal distribution
  if (ba::mean (lGaussianVariateAcc)
      < lFinalDemandMean - lFinalDemandStandardDeviation
      || ba::mean (lGaussianVariateAcc)
      > lFinalDemandMean + lFinalDemandStandardDeviation) {
    throw simulation_exception ("The mean of the total number of events is not in the expected range");
  }
    
  // TODO: check that the average number of events corresponds to the given
  // input
  
  // Close the log file
  logOutputFile.close();
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
