// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/AirportPairKey.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    AirportPairKey_T::AirportPairKey_T (const AirportCode_T& iBoardPoint,
                      const AirportCode_T& iOffPoint)
      : boardPoint (iBoardPoint), offPoint (iOffPoint) {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string AirportPairKey_T::describe() const {
      std::ostringstream ostr;
      ostr << boardPoint << "; " << offPoint << "; ";
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    bool AirportPairKey_T::
    operator== (const AirportPairKey_T& iAirportPairKey) const {
      return (boardPoint == iAirportPairKey.boardPoint
              && offPoint == iAirportPairKey.offPoint);
    }

  }
}
