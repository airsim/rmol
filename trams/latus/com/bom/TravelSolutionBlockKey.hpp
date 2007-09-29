#ifndef __LATUS_COM_BOM_TRAVELSOLUTIONBLOCKKEY_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTIONBLOCKKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/bom/KeyAbstract.hpp>
// LATUS Basic
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a travel solution block. */
    struct TravelSolutionBlockKey_T : public KeyAbstract {
      AirportCode_T origin;
      AirportCode_T destination;
      DateTime_T dateTime;

      /** Constructor. */
      TravelSolutionBlockKey_T (const AirportCode_T&,
                                const AirportCode_T&,
                                const DateTime_T&);
      
      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTIONBLOCKKEY_HPP
