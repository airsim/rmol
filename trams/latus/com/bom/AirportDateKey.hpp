#ifndef __LATUS_COM_BOM_AIRPORTDATEKEY_HPP
#define __LATUS_COM_BOM_AIRPORTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/NetworkDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of an AirportDate. */
    struct AirportDateKey_T : public KeyAbstract {
      NetworkDateKey_T networkDateKey;
      AirportCode_T origin;

      /** Constructor. */
      AirportDateKey_T (const NetworkDateKey_T&, const AirportCode_T&);
      
      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_AIRPORTDATEKEY_HPP
