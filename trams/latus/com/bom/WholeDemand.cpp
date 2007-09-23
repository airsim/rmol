// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// GSL
#include <gsl/gsl_math.h>
// LATUS Common
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    WholeDemand::WholeDemand (const DateTime_T& iUpdateDate)
      : _updateDate (iUpdateDate) {
    }

    // //////////////////////////////////////////////////////////////////////
    WholeDemand::~WholeDemand() {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string WholeDemand::describeKey() const {
      std::ostringstream ostr;
      ostr << _updateDate;
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void WholeDemand::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << _updateDate << std::endl;
      
      int j = 1;
      for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
           itCityPair != _cityPairList.end(); ++itCityPair, ++j) {
        const CityPair* lCityPair_ptr = itCityPair->second;
        assert (lCityPair_ptr != NULL);

        lCityPair_ptr->display ();
      }
      
      // DEBUG: Summary
      std::cout << "Total daily rate: " << _dailyRate
                << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    const DateTime_T& WholeDemand::getCurrentDate () const {
      assert (_bookingDay != NULL);
      return _bookingDay->getBookingDate();
    }

    // //////////////////////////////////////////////////////////////////////
    const Duration_T& WholeDemand::getCurrentTime () const {
      assert (_bookingDay != NULL);
      return _bookingDay->getBookingTime();
    }

    // //////////////////////////////////////////////////////////////////////
    CityPair* WholeDemand::
    getCityPairInternal (const std::string& iCityPairKey) const {
      CityPair* resultCityPair_ptr = NULL;
      
      CityPairList_T::const_iterator itCityPair =
        _cityPairList.find (iCityPairKey);

      if (itCityPair != _cityPairList.end()) {
        resultCityPair_ptr = itCityPair->second;
      }

      return resultCityPair_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    CityPair* WholeDemand::
    getCityPair (const AirportCode_T& iOrigin,
                 const AirportCode_T& iDestination) const {
      const AirportPairKey_T lAirportPairKey (iOrigin, iDestination);
      const CityPairKey_T lCityPairKey (lAirportPairKey);
      const std::string& lCityPairKeyString = lCityPairKey.describeShort();
      return getCityPairInternal (lCityPairKeyString);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void WholeDemand::updateDailyRate () {
      double oDailyRate = 0.0;
      
      // Empty the daily rate distribution, as it will be (re-)filled
      // by the below main loop on CityPair objects.
      _cityPairDistribution.clear();
      
      // Update the daily rates
      for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
           itCityPair != _cityPairList.end(); itCityPair++) {
        CityPair* lCityPair_ptr = itCityPair->second;
        assert (lCityPair_ptr != NULL);

        /** Re-calculate the daily rate (final demand weighted by a modulation,
            e.g., here, according to a Weibull distribution). */
        lCityPair_ptr->updateDailyRate();

        const double lCityPairDailyRate = lCityPair_ptr->getDailyRate();

        // If the daily rate is null, then no event should be generated
        // for the corresponding CityPair object: the departure date is
        // probably too far.
        if (gsl_fcmp (lCityPairDailyRate, 0.0, 1e-3) == 0) {
          continue;
        }

        oDailyRate += lCityPairDailyRate;
        
        // Insert the current cumulated daily rate within the daily rate
        // distribution vector
        const bool insertSucceeded = _cityPairDistribution.
          insert (CityPairDistribution_T::
                  value_type (oDailyRate,
                              lCityPair_ptr->describeShortKey())).second;

        if (insertSucceeded == false) {
          LATUS_LOG_ERROR ("Insertion failed for " << oDailyRate
                           << " and " << lCityPair_ptr->describeKey());
          assert (insertSucceeded == true);
        }
      }

      setDailyRate (oDailyRate);
    }

    // //////////////////////////////////////////////////////////////////////
    void WholeDemand::drawEventsForAllCityPairs (EventList_T& ioEventList) {
      for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
           itCityPair != _cityPairList.end(); itCityPair++) {
        CityPair* lCityPair_ptr = itCityPair->second;
        assert (lCityPair_ptr != NULL);

        // Draw the next event corresponding to the CityPair (derived from the
        // CityPair daily rate), and add it to the event queue.
        lCityPair_ptr->drawCityPairNextEvent (ioEventList);
      }
    }

  }
}
