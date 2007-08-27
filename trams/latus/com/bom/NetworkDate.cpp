// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    NetworkDate::NetworkDate (const NetworkDateKey_T& iKey)
      : _key (iKey), _network (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    NetworkDate::~NetworkDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string NetworkDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string NetworkDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (AirportDateOrderedList_T::const_iterator itAirportDate =
             _airportDateOrderedList.begin();
           itAirportDate != _airportDateOrderedList.end(); ++itAirportDate) {
        const AirportDate* lAirportDate_ptr = *itAirportDate;
        assert (lAirportDate_ptr != NULL);

        lAirportDate_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    NetworkDate* NetworkDate::
    getNetworkDate (const DateTime_T& iReferenceDate) const {
      assert (_network != NULL);
      return _network->getNetworkDate (iReferenceDate);
    }

    // //////////////////////////////////////////////////////////////////////
    AirportDate* NetworkDate::
    getAirportDate (const AirportCode_T& iAirport,
                    const DateTime_T& iReferenceDate) const {
      AirportDate* oAirportDate_ptr = NULL;
      assert (_network != NULL);

      const NetworkDate* lNetworkDate_ptr =
        _network->getNetworkDate (iReferenceDate);
      if (lNetworkDate_ptr != NULL) {
        oAirportDate_ptr = lNetworkDate_ptr->getAirportDate (iAirport);
      }

      return oAirportDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    AirportDate* NetworkDate::
    getAirportDateInternal (const std::string& iAirportDateKey) const {
      AirportDate* resultAirportDate_ptr = NULL;
      
      AirportDateList_T::const_iterator itAirportDate =
        _airportDateList.find (iAirportDateKey);

      if (itAirportDate != _airportDateList.end()) {
        resultAirportDate_ptr = itAirportDate->second;
      }

      return resultAirportDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    AirportDate* NetworkDate::
    getAirportDate (const AirportCode_T& iOrigin) const {
      
      const NetworkDateKey_T& lNetworkDateKey = getPrimaryKey();
      const AirportDateKey_T lAirportDateKey (lNetworkDateKey, iOrigin);
      const std::string& lAirportDateKeyString =
        lAirportDateKey.describeShort();
      return getAirportDateInternal (lAirportDateKeyString);
    }

  }
}
