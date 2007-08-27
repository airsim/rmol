// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/OutboundPathKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    OutboundPathKey_T::
    OutboundPathKey_T (const AirportDateKey_T& iAirportDateKey,
                       const AirportCode_T& iDestination,
                       const Duration_T& iElapsedTime,
                       const SegmentNumber_T& iSegmentNumber,
                       const AirlineNumber_T& iAirlineNumber)
      : airportDateKey (iAirportDateKey), destination (iDestination),
        elapsed (iElapsedTime), segmentNumber (iSegmentNumber),
        airlineNumber (iAirlineNumber) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string OutboundPathKey_T::describe() const {
      std::ostringstream ostr;
      const std::string& lShortKey = describeShort();
      ostr << airportDateKey.describe() << lShortKey;
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string OutboundPathKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << destination << "; " << elapsed << "; " << segmentNumber
           << "; " << airlineNumber << "; ";
      return ostr.str();
    }

  }
}
