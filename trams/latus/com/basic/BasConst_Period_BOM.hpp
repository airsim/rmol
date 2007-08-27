#ifndef __LATUS_COM_BAS_BASCONST_PERIOD_BOM_HPP
#define __LATUS_COM_BAS_BASCONST_PERIOD_BOM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    // //////// (Flight-)Period-related BOM ///////
    /** Default date period (0-length, i.e., it lasts one day).*/
    extern const DatePeriod_T BOOST_DEFAULT_DATE_PERIOD;

    /** Representation of Dow-Of-the-Week */
    extern const std::string DOW_STR[];
    
    /** Default DOW String (e.g., "1111100"). */
    extern const DOW_String_T DEFAULT_DOW_STRING;

    /** Default Date OffSet (e.g., 0). */
    extern const DateOffSet_T DEFAULT_DATE_OFFSET;

  }
}
#endif // __LATUS_COM_BAS_BASCONST_PERIOD_BOM_HPP
