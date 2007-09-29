#ifndef __LATUS_COM_BOM_TRAVELSOLUTIONKEY_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTIONKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/OutboundPathKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a travel solution. */
    struct TravelSolutionKey_T : public KeyAbstract {
      OutboundPathKey_T outboundPathKey;

      /** Constructor. */
      TravelSolutionKey_T (const OutboundPathKey_T&);
      
      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTIONKEY_HPP
