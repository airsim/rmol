#ifndef __LATUS_COM_BOM_AIRPORTDATELIST_HPP
#define __LATUS_COM_BOM_AIRPORTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class AirportDate;

    /** Define lists of Airport-Date objects. */
    typedef std::map<std::string, AirportDate*> AirportDateList_T;
    typedef std::vector<AirportDate*> AirportDateOrderedList_T;
  }
}
#endif // __LATUS_COM_BOM_AIRPORTDATELIST_HPP
