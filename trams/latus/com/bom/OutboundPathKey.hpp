#ifndef __LATUS_COM_BOM_OUTBOUNDPATHKEY_HPP
#define __LATUS_COM_BOM_OUTBOUNDPATHKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/AirportDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of an Outbound-Path. */
    struct OutboundPathKey_T : public KeyAbstract {
      AirportDateKey_T airportDateKey;
      AirportCode_T destination;
      Duration_T elapsed;
      SegmentNumber_T segmentNumber;
      AirlineNumber_T airlineNumber;

      /** Constructor. */
      OutboundPathKey_T (const AirportDateKey_T&, const AirportCode_T&,
                         const Duration_T&, const SegmentNumber_T&,
                         const AirlineNumber_T&);
      
      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_COM_BOM_OUTBOUNDPATHKEY_HPP
