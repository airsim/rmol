#ifndef __STDAIR_BAS_BASCONST_PERIOD_BOM_HPP
#define __STDAIR_BAS_BASCONST_PERIOD_BOM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_types.hpp>

namespace stdair {

  // //////// (Flight-)Period-related BOM ///////
  /** Default date period (0-length, i.e., it lasts one day).*/
  extern const DatePeriod_T BOOST_DEFAULT_DATE_PERIOD;

  /** Representation of Dow-Of-the-Week */
  extern const std::string DOW_STR[];
    
  /** Default DOW String (e.g., "1111100"). */
  extern const DOW_String_T DEFAULT_DOW_STRING;

  /** Default Date Offset (e.g., 0). */
  extern const DateOffset_T DEFAULT_DATE_OFFSET;

  /** Default Duration in days (e.g., 0). */
  extern const DayDuration_T DEFAULT_DAY_DURATION;

}
#endif // __STDAIR_BAS_BASCONST_PERIOD_BOM_HPP
