// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/OutboundPath.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    AirportDate::AirportDate (const AirportDateKey_T& iKey)
      : _key (iKey), _networkDate (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    AirportDate::~AirportDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string AirportDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string AirportDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void AirportDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (OutboundPathList_T::const_iterator itPath =
             _outboundPathList.begin();
           itPath != _outboundPathList.end(); ++itPath) {
        const OutboundPath* lOutboundPath_ptr = itPath->second;
        assert (lOutboundPath_ptr != NULL);
        
        lOutboundPath_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    AirportDate* AirportDate::
    getAirportDate (const AirportCode_T& iAirport,
                    const DateTime_T& iReferenceDate) const {
      assert (_networkDate != NULL);
      return _networkDate->getAirportDate (iAirport, iReferenceDate);
    }
    
    // //////////////////////////////////////////////////////////////////////
    OutboundPath* AirportDate::
    getOutboundPathInternal (const std::string& iOutboundPathKey) const {
      OutboundPath* resultOutboundPath_ptr = NULL;
      
      OutboundPathList_T::const_iterator itOutboundPath =
        _outboundPathList.find (iOutboundPathKey);

      if (itOutboundPath != _outboundPathList.end()) {
        resultOutboundPath_ptr = itOutboundPath->second;
      }

      return resultOutboundPath_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    OutboundPath* AirportDate::
    getOutboundPath (const AirportCode_T& iDestination,
                     const Duration_T& iElapsedTime,
                     const SegmentNumber_T& iSegmentNumber,
                     const AirlineNumber_T& iAirlineNumber) const {
      const AirportDateKey_T& lAirportDateKey = getPrimaryKey();
      const OutboundPathKey_T lOutboundPathKey (lAirportDateKey, iDestination,
                                                iElapsedTime, iSegmentNumber,
                                                iAirlineNumber);
      const std::string& lOutboundPathKeyString =
        lOutboundPathKey.describeShort();
      return getOutboundPathInternal (lOutboundPathKeyString);
    }
    
  }
}
