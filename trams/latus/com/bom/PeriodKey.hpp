#ifndef __LATUS_COM_BOM_PERIODKEY_HPP
#define __LATUS_COM_BOM_PERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    /** Structure wrapping the key elements of a period.
        <br>The period can be defined, for instance, for a flight schedule.
        <br>The DOW field/attribute represents the set of Days-Of-the-Week,
        starting on Monday, for which there is a flight. For example, the
        set 1111100 represents flights departing on business days only. */
    struct PeriodKey_T {
      DateTime_T startDate;
      DateTime_T endDate;
      DOW_T dow;

      /** Constructor. */
      PeriodKey_T (const DateTime_T& iStartDate, const DateTime_T& iEndDate, 
                   const DOW_T& iDow);
      
      /** Display. */
      const std::string describe() const;
    };

  }
}
#endif // __LATUS_COM_BOM_PERIODKEY_HPP
