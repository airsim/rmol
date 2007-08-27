#ifndef __LATUS_COM_BOM_NETWORKDATEKEY_HPP
#define __LATUS_COM_BOM_NETWORKDATEKEY_HPP

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

    /** Define the key elements of a Network-Date. */
    struct NetworkDateKey_T : public KeyAbstract {
      DateTime_T referenceDate;

      /** Constructor. */
      NetworkDateKey_T (const DateTime_T&);
      
      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_NETWORKDATEKEY_HPP
