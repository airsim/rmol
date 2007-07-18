// STL
#include <iostream>
#include <sstream>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
// LATUS
#include <latus/LATUS_Service.hpp>

// Random Generator Type
const gsl_rng_type* _rngTypePtr = NULL;

// Random Generator
gsl_rng* _rngExponentialPtr = NULL;
gsl_rng* _rngPoissonPtr = NULL;
gsl_rng* _rngGaussianPtr = NULL;


// ///////////////////////////////////////////////////
void init () {
  // Random Generator type
  _rngTypePtr = gsl_rng_default;

  // Initialise the Random Generator
  gsl_rng_env_setup ();

  // Allocate the memory for the random generator
  _rngExponentialPtr = gsl_rng_alloc (_rngTypePtr);
  _rngPoissonPtr = gsl_rng_alloc (_rngTypePtr);
  _rngGaussianPtr = gsl_rng_alloc (_rngTypePtr);
}

// ///////////////////////////////////////////////////
double generateExponentialVariate (const double iLambda) {
  const double lMu = 1/iLambda;
  const double result = gsl_ran_exponential (_rngExponentialPtr, lMu);
  return result;
}

// ///////////////////////////////////////////////////
double generatePoissonVariate (const double iMu) {
  const double result = gsl_ran_poisson (_rngPoissonPtr, iMu);
  return result;
}

// ///////////////////////////////////////////////////
double generateGaussianVariate (const double iMean, const double iStdDev) {
  const double result = iMean + gsl_ran_gaussian (_rngGaussianPtr, iStdDev);
  return result;
}

// ///////////////////////////////////////////////////
void finalise () {
  gsl_rng_free (_rngExponentialPtr);
  gsl_rng_free (_rngPoissonPtr);
  gsl_rng_free (_rngGaussianPtr);
}

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
  double lambda = 0.0;

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
  // return (iFinalDemandMean / lSimulationLengthInDays);
  
  // Current length-time (expressed as a number of days)
  const boost::gregorian::date_duration lCurrentDuration =
    iCurrentDate - iStartDate;
  const double lCurrentDurationInDays =
    static_cast<const double> (lCurrentDuration.days());
  
  /** Ratio on the x-absciss for the Weibull distribution
      (GSL, Chapter 19, p209 on GSL Reference Manual for GSL v1.7). */
  const double lXRatio = 2.0 / lSimulationLengthInDays;

  /** The daily rate is pro-rated/weighted according to the
      Weibull distribution (see above for the reference in the GSL).
      The a and b parameters are taken equal to respectively 2 and 3. */
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
    1 / gsl_cdf_weibull_P (lSimulationLengthInWeibullX, 2, 3);
  
  const double lDailyIncrementalRate = lNormalisationConstant
    * (gsl_cdf_weibull_P (lCurrentDurationInWeibullX, 2, 3)
       - gsl_cdf_weibull_P (lPreviousDurationInWeibullX, 2, 3));

  lambda = iFinalDemandMean * lDailyIncrementalRate;

  return lambda;
}

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    
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
    double lFinalDemandMean = 300.0;
    double lFinalDemandStandardDeviation = 20.0;

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> K;
    }

    if (argc >= 2 && argv[2] != NULL) {
      std::istringstream istr (argv[2]);
      istr >> lFinalDemandMean;
    }

    if (argc >= 3 && argv[3] != NULL) {
      std::istringstream istr (argv[3]);
      istr >> lFinalDemandStandardDeviation;
    }

    // Initialisation of random generators
    init();

    std::cout << "Simulation#; Lambda_Sum; Total_Event#; Gaussian_Variate; "
              << std::endl;
    
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

      // DEBUG
      //std::cout << "Day#; Total_Event#; Daily_Event#; Time; " << std::endl;

      // Reset the total number of events for the current simulation
      lTotalEventNumber = 0;

      // Reset the sum of lambdas
      lLambdaSum = 0.0;
        
      while (lCurrentDate < kEndDate) {
        // Calculate the daily rate of events (bookings)
        const double lambda = calculateDailyRate (kStartDate, lCurrentDate,
                                                  kEndDate, lFinalDemandMean);

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
            generateExponentialVariate (lambda);

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
        
          // const double lPoissonVariate = generatePoissonVariate (lambda);

          /* DEBUG
            std::cout << lCurrentDate << "; " << lTotalEventNumber << "; "
            << lDailyEventNumber << "; " << lCurrentTime << "; "
            << std::endl;
          */
        }

        // When the booking day is over, there's an additional event
        // (the first one made after the booking date)
        lTotalEventNumber--; lDailyEventNumber--;
      
        /* DEBUG
        std::cout << lCurrentDate << "; " << lambda << "; "
                  << lDailyEventNumber << "; " << lTotalEventNumber << "; "
                  << std::endl;
        */
        
        // Add a day
        lCurrentDate += kDayDuration;
      }

      // Generate a Gaussian variate, just in order to compare the final
      // distributions (Gaussian and accumulated Poissonian).
      const double lGaussianVariate =
        generateGaussianVariate (lFinalDemandMean,
                                 lFinalDemandStandardDeviation);
      
      std::cout << i << "; " << lLambdaSum << "; "
                << lTotalEventNumber << "; "
                << lGaussianVariate << "; " << std::endl;
  }

    // Cleaning of random generators
    finalise();
    
    // Initialise the context
    //LATUS::LATUS_Service latusService;

    // Launch a simulation
    //latusService.simulate ();

    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
