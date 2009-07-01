#ifndef __STDAIR_BOM_FLIGHTDATELIST_HPP
#define __STDAIR_BOM_FLIGHTDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>
#include <list>

namespace stdair {

  /** Forward declarations. */
  class FlightDate;

  /** Define lists of Flight-Date objects. */
  typedef std::map<std::string, FlightDate*> FlightDateList_T;
  typedef std::vector<FlightDate*> FlightDateOrderedList_T;
  typedef std::list<const FlightDate*> FlightDateLightList_T;

}
#endif // __STDAIR_BOM_FLIGHTDATELIST_HPP
