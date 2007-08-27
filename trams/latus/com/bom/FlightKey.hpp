#ifndef __LATUS_COM_BOM_FLIGHTKEY_HPP
#define __LATUS_COM_BOM_FLIGHTKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/InventoryKey.hpp>

namespace LATUS {

  namespace COM {

    /** Structure wrapping the key elements of a flight. */
    struct FlightKey_T : public KeyAbstract {
      InventoryKey_T inventoryKey;
      FlightNumber_T flightNumber;

      /** Constructor. */
      FlightKey_T (const InventoryKey_T& iInventoryKey,
                   const FlightNumber_T& iFlightNumber);

      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_FLIGHTKEY_HPP
