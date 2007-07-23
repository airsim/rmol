#ifndef __LATUS_COM_BOM_LEGCABINKEY_HPP
#define __LATUS_COM_BOM_LEGCABINKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/LegDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a leg-cabin. */
    struct LegCabinKey_T {
      LegDateKey_T legDateKey;
      CabinCode_T cabinCode;

      /** Constructor. */
      LegCabinKey_T (const LegDateKey_T& iLegDateKey,
                     const CabinCode_T& iCabinCode);

      /** Display of the key. */
      const std::string describe() const;
    };

  }
}
#endif // __LATUS_COM_BOM_LEGCABINKEY_HPP
