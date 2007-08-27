#ifndef __LATUS_COM_BOM_INVENTORYKEY_HPP
#define __LATUS_COM_BOM_INVENTORYKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a flight-date. */
    struct InventoryKey_T : public KeyAbstract {
      AirlineCode_T airlineCode;

      /** Constructor. */
      InventoryKey_T (const AirlineCode_T& iAirlineCode);

      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_INVENTORYKEY_HPP
