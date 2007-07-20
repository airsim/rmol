#ifndef __LATUS_COM_BOM_FLIGHTDATELIST_HPP
#define __LATUS_COM_BOM_FLIGHTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class FlightDate;

    /** Define list of Flight-Date objects. */
    typedef std::map<std::string, FlightDate*> FlightDateList_T;
  }
}
#endif // __LATUS_COM_BOM_FLIGHTDATELIST_HPP
