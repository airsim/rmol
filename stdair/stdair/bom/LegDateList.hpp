#ifndef __STDAIR_BOM_LEGDATELIST_HPP
#define __STDAIR_BOM_LEGDATELIST_HPP

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
  class LegDate;

  /** Define lists of Leg-Date objects. */
  typedef std::map<std::string, LegDate*> LegDateList_T;
  typedef std::vector<LegDate*> LegDateOrderedList_T;
  typedef std::list<const LegDate*> LegDateLightList_T;

}
#endif // __STDAIR_BOM_LEGDATELIST_HPP
