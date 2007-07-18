// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
// LATUS Common
#include <latus/com/basic/BasConst_GSL.hpp>
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {
  
  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    CityPair::CityPair (const std::string& iDescription)
      : _bookingDay (NULL), _description (iDescription),
        _dailyRate (0.0), _dailyEventNumber (0),
        _rngExponentialPtr (NULL), _rngUniformIntPtr (NULL) {
      initRandomGenerator();
    }
    
    // //////////////////////////////////////////////////////////////////////
    CityPair::~CityPair () {
      gsl_rng_free (_rngExponentialPtr); _rngExponentialPtr = NULL;
      gsl_rng_free (_rngUniformIntPtr); _rngUniformIntPtr = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    void CityPair::initRandomGenerator() {
      // Initialise the Random Generator
      gsl_rng_env_setup ();
      
      _rngExponentialPtr = gsl_rng_alloc (DEFAULT_LATUS_RANDOM_GENERATOR_TYPE);
      assert (_rngExponentialPtr != NULL);
      _rngUniformIntPtr = gsl_rng_alloc (DEFAULT_LATUS_RANDOM_GENERATOR_TYPE);
      assert (_rngUniformIntPtr != NULL);
    }
    
    // //////////////////////////////////////////////////////////////////////
    const boost::gregorian::date& CityPair::getCurrentDate () const {
      assert (_bookingDay != NULL);
      return _bookingDay->getBookingDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const boost::posix_time::time_duration& CityPair::getCurrentTime () const {
      assert (_bookingDay != NULL);
      return _bookingDay->getBookingTime();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string CityPair::describeKey() const {
      std::ostringstream ostr;
      ostr << "\"" << _description << "\"";
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    CityPairDate* CityPair::
    getCityPairDate (const boost::gregorian::date& iDepDate) const {
      CityPairDate* resultCityPairDate_ptr = NULL;
      
      CityPairDateList_T::const_iterator itCityPairDate =
        _cityPairDateList.find (iDepDate);

      if (itCityPairDate != _cityPairDateList.end()) {
        resultCityPairDate_ptr = itCityPairDate->second;
      }

      return resultCityPairDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void CityPair::updateDailyRate () {
      double oDailyRate = 0.0;
      
      // Empty the daily rate distribution, as it will be (re-)filled
      // by the below main loop on CityPairDate objects.
      _depDateDistribution.clear();
      
      // Update the total final demand
      for (CityPairDateList_T::const_iterator itCityPairDate =
             _cityPairDateList.begin();
           itCityPairDate != _cityPairDateList.end(); itCityPairDate++) {
        CityPairDate* lCityPairDate_ptr = itCityPairDate->second;
        assert (lCityPairDate_ptr != NULL);

        // When a CityPairDate has got a departure date lower than the current
        // booking date, it means that the corresponding demand has already
        // gone / flown, and its daily rate contribution is therefore
        // disregarded (as it is null, by construction).
        const boost::gregorian::date& lCurrentDate = getCurrentDate();
        const boost::gregorian::date& lDepartureDate =
          lCityPairDate_ptr->getDepartureDate();
        if (lCurrentDate >= lDepartureDate) {
          continue;
        }

        /** Re-calculate the daily rate (final demand weighted by a modulation,
            e.g., here, according to a Weibull distribution). */
        lCityPairDate_ptr->updateDailyRate();

        const double lCityPairDateDailyRate =
          lCityPairDate_ptr->getDailyRate();

        // If the daily rate is null, then no event should be generated
        // for the corresponding CityPairDate object: the departure date is
        // probably too far.
        if (gsl_fcmp (lCityPairDateDailyRate, 0.0, 1e-3) == 0) {
          continue;
        }

        // Add up the daily of the ClassPath to the CityPairDate daily rate.
        oDailyRate += lCityPairDateDailyRate;

        // Insert the current cumulated daily rate within the daily rate
        // distribution vector
        const bool insertSucceeded = _depDateDistribution.
          insert (DepDateDistribution_T::value_type(oDailyRate,
                                                    lCityPairDate_ptr)).second;

        if (insertSucceeded == false) {
          LATUS_LOG_ERROR ("Insertion failed for " << oDailyRate
                           << " and " << lCityPairDate_ptr->describeKey());
          assert (insertSucceeded == true);
        }
      }

      setDailyRate (oDailyRate);
    }

    // //////////////////////////////////////////////////////////////////////
    double CityPair::generateExponentialVariate (const double iLambda) {
      const double lMu = 1/iLambda;
      const double result = gsl_ran_exponential (_rngExponentialPtr, lMu);
      return result;
    }

    // //////////////////////////////////////////////////////////////////////
    CityPairDate* CityPair::drawCityPairDate () const {
      CityPairDate* oResult = NULL;
      
      // When the daily rate distribution is empty, there is no more
      // demand event to generate.
      if (_depDateDistribution.empty() == true) {
        return oResult;
      }
      
      // Retrieve the CityPairDate date getting the highest daily rate:
      // since the distribution list (map) is ordered by daily rate,
      // the searched CityPairDate is simply the last item of the list.
      DepDateDistribution_T::const_reverse_iterator itHighestDailyRateDepDate =
        _depDateDistribution.rbegin();
      assert (itHighestDailyRateDepDate != _depDateDistribution.rend());
      const double lHighestDailyRate = itHighestDailyRateDepDate->first;

      // Generate a random floating point number, uniformly distributed in the
      // range [0, lHighestDailyRate[ (including 0.0 but not
      // lHighestDailyRate).
      // Note that gsl_rng_uniform() generates a number uniformly distributed
      // in the range [0, 1[.
      const double lVariate =
        gsl_rng_uniform (_rngUniformIntPtr) * lHighestDailyRate;

      // Retrieve, within the distribution list, the CityPairDate getting
      // the closest daily rate (say, lDailyRate),
      // such that lVariate >= lDailyRate.
      DepDateDistribution_T::const_iterator itDepDate =
        _depDateDistribution.lower_bound (lVariate);
      
      // Return the corresponding departure date
      oResult = itDepDate->second;
      assert (oResult != NULL);
      return oResult;
    }

    // //////////////////////////////////////////////////////////////////////
    boost::posix_time::time_duration CityPair::drawNextEventTime () {
      // Generate a random variate, expressed in (fractional) day
      const double lExponentialVariateInDays =
        generateExponentialVariate (_dailyRate);
      
      // Convert the variate in a number of seconds
      const int lExponentialVariateInSeconds =
        static_cast<const int> (lExponentialVariateInDays
                                * TIME_DURATION_FOR_A_DAY_IN_SECONDS);
      
      // Convert the variate in a (Boost typedef) time duration
      const boost::posix_time::time_duration lExponentialVariate =
        boost::posix_time::seconds (lExponentialVariateInSeconds);
      
      // Add the inter-arrival time to the current time
      const boost::posix_time::time_duration& lCurrentTime = getCurrentTime();
      const boost::posix_time::time_duration oResult =
        lCurrentTime + lExponentialVariate;

      /*
      LATUS_LOG_DEBUG ("[" << describeKey() << "]: Daily rate: "
                       << _dailyRate << "; Seconds in 1 day: "
                       << TIME_DURATION_FOR_A_DAY_IN_SECONDS
                       << "; Variate (day): "
                       << lExponentialVariateInDays << "; Variate (s): "
                       << lExponentialVariateInSeconds << "; Variate: "
                       << lExponentialVariate << "; Current time: "
                       << "; Result: " << oResult);
      */
      
      return oResult;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void CityPair::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << _description << "; ";
      
      int j = 1;
      for (CityPairDateList_T::const_iterator itCityPairDate =
             _cityPairDateList.begin();
           itCityPairDate != _cityPairDateList.end(); itCityPairDate++, j++) {
        const CityPairDate* lCityPairDate_ptr = itCityPairDate->second;
        assert (lCityPairDate_ptr != NULL);

        bool lIndented = (j != 1);
        lCityPairDate_ptr->display (lIndented);
      }
      
      for (DepDateDistribution_T::const_reverse_iterator itCityPairDate =
             _depDateDistribution.rbegin();
           itCityPairDate != _depDateDistribution.rend(); itCityPairDate++) {
        const double lDailyRate = itCityPairDate->first;
        const CityPairDate* lCityPairDate_ptr = itCityPairDate->second;
        assert (lCityPairDate_ptr != NULL);

        std::cout << "         [ " << lCityPairDate_ptr->describeKey() << " | "
                  << std::setprecision(2) << lDailyRate
                  << " ]" << std::endl;
      }
      
      // Summary
      std::cout << _description
                << "; Total daily rate: " << _dailyRate
                << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void CityPair::displayCurrent() const {
      // DEBUG
      std::ios::fmtflags oldFlags = std::cout.flags();
      LATUS_LOG_DEBUG (_description << "; Daily Rate: " 
                       << std::fixed << std::setprecision(2) << _dailyRate
                       << "; Daily Nb of Events: " << _dailyEventNumber);
      std::cout.flags (oldFlags);
    }

  }
}
