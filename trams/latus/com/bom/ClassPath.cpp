// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_cdf.h>
// LATUS Common
#include <latus/com/basic/BasConst_CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/ClassPath.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    ClassPath::ClassPath (const std::string& iDescription,
                          const DistributionDetails_T& iDistributionDetails) :
      _cityPairDate (NULL), _description (iDescription),
      _distributionDetails (iDistributionDetails) {

    }

    // //////////////////////////////////////////////////////////////////////
    ClassPath::~ClassPath() {

    }

    // //////////////////////////////////////////////////////////////////////
    const std::string ClassPath::describeKey() const {
      assert (_cityPairDate != NULL);
      
      const std::string& lParentKeyDescription = _cityPairDate->describeKey();
      std::ostringstream ostr;
      ostr << lParentKeyDescription << "; \"" << _description << "\"";
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ClassPath::display (const bool iIndented) const {
      if (iIndented == true) {
        std::cout << "                      ";
      }
      std::cout << _description << "; ~N (" << getDistributionMean() << ", "
                << getDistributionStdDev() << "); " << std::endl;
    }

    // //////////////////////////////////////////////////////////////////////
    CityPairDate& ClassPath::getCityPairDateRef() const {
      assert (_cityPairDate != NULL);
      return *_cityPairDate;
    }
    
    // //////////////////////////////////////////////////////////////////////
    const AirportCode_T& ClassPath::getOrigin () const {
      assert (_cityPairDate != NULL);
      return _cityPairDate->getOrigin();
    }

    // //////////////////////////////////////////////////////////////////////
    const AirportCode_T& ClassPath::getDestination () const {
      assert (_cityPairDate != NULL);
      return _cityPairDate->getDestination();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& ClassPath::getCurrentDate() const {
      assert (_cityPairDate != NULL);
      return _cityPairDate->getCurrentDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& ClassPath::getDepartureDate() const {
      assert (_cityPairDate != NULL);
      return _cityPairDate->getDepartureDate();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const DateOffSet_T& ClassPath::getCurrentDTD() const {
      assert (_cityPairDate != NULL);
      return _cityPairDate->getCurrentDTD();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ClassPath::updateDailyRate () {
      double oDailyRate = 0.0;
      
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
      oDailyRate = 0.0;
      
      // By construction, the demand occurs before the departure date.
      const DateTime_T& lCurrentDate = getCurrentDate();
      const DateTime_T& lDepartureDate = getDepartureDate();
      assert (lCurrentDate < lDepartureDate);
      
      // Simulation length-time (expressed as a number of days)
      const int lSimulationLengthInDays =
        static_cast<const int>(DEFAULT_FLIGHT_DATE_RESERVATION_DURATION.days());
      
      // DEBUG
      // return (_totalFinalDemand / lSimulationLengthInDays);
      
      // Current length-time (expressed as a number of days)
      const DateOffSet_T lCurrentDuration = lCurrentDate
        - (lDepartureDate - DEFAULT_FLIGHT_DATE_RESERVATION_DURATION);
      const double lCurrentDurationInDays =
        static_cast<const double> (lCurrentDuration.days());
      
      /** Ratio on the x-absciss for the Weibull distribution
          (GSL, Chapter 19, p209 on GSL Reference Manual for GSL v1.7). */
      const double lXRatio = 2.0 / lSimulationLengthInDays;
      
      /** The daily rate is pro-rated/weighted according to the
          Weibull distribution (see above for the reference in the GSL).
          The a and b parameters are taken equal to respectively 2 and 3. */
      const double lCurrentDurationInWeibullX =
        lCurrentDurationInDays * lXRatio;
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
      const double lSimulationLengthInWeibullX = 
        lSimulationLengthInDays * lXRatio;
      const double lNormalisationConstant =
        1 / gsl_cdf_weibull_P (lSimulationLengthInWeibullX, 2, 3);
      
      const double lDailyIncrementalRate = lNormalisationConstant
        * (gsl_cdf_weibull_P (lCurrentDurationInWeibullX, 2, 3)
           - gsl_cdf_weibull_P (lPreviousDurationInWeibullX, 2, 3));
      
      oDailyRate = getDistributionMean() * lDailyIncrementalRate;
      
      setDailyRate (oDailyRate);
    }
    
  }
  
}
