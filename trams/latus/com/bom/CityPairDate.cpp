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
#include <latus/com/basic/BasConst_CityPair.hpp>
#include <latus/com/basic/BasConst_GSL.hpp>
#include <latus/com/bom/WTP.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {
  
  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    CityPairDate::CityPairDate (const DateTime_T& iDepartureDate)
      : _cityPair (NULL), _departureDate (iDepartureDate),
        _hasDeparted (false), _currentDTD (0), _rngUniformIntPtr (NULL) {
      initRandomGenerator();
    }

    // //////////////////////////////////////////////////////////////////////
    CityPairDate::~CityPairDate() {
      gsl_rng_free (_rngUniformIntPtr); _rngUniformIntPtr = NULL;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void CityPairDate::initRandomGenerator() {
      // Initialise the Random Generator
      gsl_rng_env_setup ();
      
      _rngUniformIntPtr = gsl_rng_alloc (DEFAULT_LATUS_RANDOM_GENERATOR_TYPE);
      assert (_rngUniformIntPtr != NULL);
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string CityPairDate::describeKey() const {
      assert (_cityPair != NULL);
      
      const std::string& lParentKeyDescription = _cityPair->describeKey();
      std::ostringstream ostr;
      ostr << lParentKeyDescription
           << boost::gregorian::to_iso_extended_string (_departureDate);
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void CityPairDate::display (const bool iIndented) const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();
      
      if (iIndented == true) {
        std::cout << "          ";
      }
      std::cout << _departureDate << "; ";
      
      int k = 1;
      for (WTPList_T::const_iterator itWTP= _wtpList.begin();
           itWTP != _wtpList.end(); itWTP++, k++) {
        const WTP* lWTP_ptr = itWTP->second;
        assert (lWTP_ptr != NULL);

        bool lIndented = (k != 1);
        lWTP_ptr->display (lIndented);
      }

      for (WTPDistribution_T::const_reverse_iterator itWTP =
             _wtpDistribution.rbegin();
           itWTP != _wtpDistribution.rend(); itWTP++) {
        const double lDailyRate = itWTP->first;
        const WTP* lWTP_ptr = itWTP->second;
        assert (lWTP_ptr != NULL);

        std::cout << "                      [ "
                  << lWTP_ptr->describeKey() << " | "
                  << std::setprecision(2) << lDailyRate
                  << " ]" << std::endl;
      }

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    CityPair& CityPairDate::getCityPairRef() const {
      assert (_cityPair != NULL);
      return *_cityPair;
    }
    
    // //////////////////////////////////////////////////////////////////////
    WTP* CityPairDate::getWTP (const PriceValue_T& iWTPValue) const {
      WTP* resultWTP_ptr = NULL;

      // TODO: apply the float::closeTo() method, as floats can not be
      // compared as is.
      
      WTPList_T::const_iterator itWTP = _wtpList.find (iWTPValue);

      if (itWTP != _wtpList.end()) {
        resultWTP_ptr = itWTP->second;
      }

      return resultWTP_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    const AirportCode_T& CityPairDate::getOrigin () const {
      assert (_cityPair != NULL);
      return _cityPair->getOrigin();
    }

    // //////////////////////////////////////////////////////////////////////
    const AirportCode_T& CityPairDate::getDestination () const {
      assert (_cityPair != NULL);
      return _cityPair->getDestination();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& CityPairDate::getCurrentDate () const {
      assert (_cityPair != NULL);
      return _cityPair->getCurrentDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const Duration_T& CityPairDate::getCurrentTime () const {
      assert (_cityPair != NULL);
      return _cityPair->getCurrentTime();
    }

    // //////////////////////////////////////////////////////////////////////
    void CityPairDate::updateDailyRate () {
      double oDailyRate = 0.0;
      
      // Empty the daily rate distribution, as it will be (re-)filled
      // by the below main loop on WTP objects.
      _wtpDistribution.clear();
      
      // Update the daily rate
      for (WTPList_T::const_iterator itWTP = _wtpList.begin();
           itWTP != _wtpList.end(); itWTP++) {
        WTP* lWTP_ptr = itWTP->second;
        assert (lWTP_ptr != NULL);
        
        // By construction, the demand occurs before the departure date.
        const DateTime_T& lCurrentDate = getCurrentDate();
        const DateTime_T& lDepartureDate = getDepartureDate();
        assert (lCurrentDate < lDepartureDate);
      
        // TODO: consider de-activating the weighting by the Weibull
        // distribution, as soon as the distribution of the demand
        // be given according to DTD.
        /** Re-calculate the daily rate (final demand weighted by a modulation,
            e.g., here, according to a Weibull distribution). */
        lWTP_ptr->updateDailyRate();

        const double lWTPDailyRate = lWTP_ptr->getDailyRate();

        // If the daily rate is null, then no event should be generated
        // for the corresponding WTP object: the departure date is
        // probably too far.
        if (gsl_fcmp (lWTPDailyRate, 0.0, 1e-3) == 0) {
          continue;
        }

        // Add up the daily of the WTP to the CityPairDate daily rate.
        oDailyRate += lWTPDailyRate;

        // Insert the current cumulated daily rate within the daily rate
        // distribution vector
        const bool insertSucceeded = _wtpDistribution.
          insert (WTPDistribution_T::value_type (oDailyRate,
                                                 lWTP_ptr)).second;

        if (insertSucceeded == false) {
          LATUS_LOG_ERROR ("Insertion failed for " << oDailyRate
                           << " and " << lWTP_ptr->describeKey());
          assert (insertSucceeded == true);
        }

      }

      setDailyRate (oDailyRate);
    }
    
    // //////////////////////////////////////////////////////////////////////
    WTP* CityPairDate::drawWTP () const {
      WTP* oResult = NULL;
      
      // When the daily rate distribution is empty, there is no more
      // demand event to generate.
      if (_wtpDistribution.empty() == true) {
        return oResult;
      }
      
      // Retrieve the WTP description getting the highest daily rate:
      // since the distribution list (map) is ordered by daily rate,
      // the searched WTP is simply the last item of the list.
      WTPDistribution_T::const_reverse_iterator itHighestRateWTP =
        _wtpDistribution.rbegin();
      assert (itHighestRateWTP != _wtpDistribution.rend());
      const double lHighestDailyRate = itHighestRateWTP->first;

      // Generate a random floating point number, uniformly distributed in the
      // range [0, lHighestDailyRate[ (including 0.0 but not
      // lHighestDailyRate).
      // Note that gsl_rng_uniform() generates a number uniformly distributed
      // in the range [0, 1[.
      const double lVariate =
        gsl_rng_uniform (_rngUniformIntPtr) * lHighestDailyRate;

      // Retrieve, within the distribution list, the WTP getting
      // the closest daily rate (say, lDailyRate),
      // such that lVariate >= lDailyRate.
      WTPDistribution_T::const_iterator itWTP =
        _wtpDistribution.lower_bound (lVariate);
      
      // Return the corresponding WTP
      oResult = itWTP->second;
      assert (oResult != NULL);
      return oResult;
    }

  }
}
