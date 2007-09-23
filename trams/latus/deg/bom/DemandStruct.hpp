#ifndef __LATUS_DEG_BOM_DEMANDSTRUCT_HPP
#define __LATUS_DEG_BOM_DEMANDSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/StructAbstract.hpp>

namespace LATUS {

  namespace DEG {

    /** Utility Structure for the parsing of Demand structures. */
    struct DemandStruct_T : public COM::StructAbstract {
      // Attributes
      COM::AirportCode_T _origin;
      COM::AirportCode_T _destination;
      COM::DateTime_T _departureDate;
      COM::PriceValue_T _wtp;
      COM::PriceCurrency_T _currency;
      COM::MeanValue_T _demandMean;
      COM::StandardDeviationValue_T _demandStdDev;
      
      /** Constructor. */
      DemandStruct_T ();

      /** Set the date from the staging details. */
      COM::DateTime_T getDate() const;

      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;

      /** Staging Date. */
      unsigned int _itYear;
      unsigned int _itMonth;
      unsigned int _itDay;
    };

  }
}
#endif // __LATUS_DEG_BOM_DEMANDSTRUCT_HPP
