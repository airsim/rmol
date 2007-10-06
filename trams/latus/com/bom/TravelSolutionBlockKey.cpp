// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/TravelSolutionBlockKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    TravelSolutionBlockKey_T::
    TravelSolutionBlockKey_T (const AirportCode_T& iOrigin,
                              const AirportCode_T& iDestination,
                              const DateTime_T& iDateTime,
                              const SeatNumber_T& iSeatNumber)
      : origin (iOrigin), destination (iDestination),
        dateTime (iDateTime), seatNumber (iSeatNumber) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolutionBlockKey_T::describe() const {
      return describeShort();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolutionBlockKey_T::describeShort() const {
      std::ostringstream ostr;
      ostr << origin << "; " << destination
           << "; "<< dateTime << "; " << seatNumber << "; ";
      return ostr.str();
    }

  }
}
