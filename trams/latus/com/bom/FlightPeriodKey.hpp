#ifndef __LATUS_COM_BOM_FLIGHTPERIODKEY_HPP
#define __LATUS_COM_BOM_FLIGHTPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/bom/FlightKey.hpp>
#include <latus/com/bom/PeriodKey.hpp>

namespace LATUS {

  namespace COM {

    /** Structure wrapping the key elements of a flight-period. */
    struct FlightPeriodKey_T {
      FlightKey_T flightKey;
      PeriodKey_T periodKey;

      /** Constructor. */      
      FlightPeriodKey_T (const FlightKey_T& iFlightKey,
                         const PeriodKey_T& iPeriodKey);

      /** Display of the key. */
      const std::string describe() const;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTPERIODKEY_HPP
