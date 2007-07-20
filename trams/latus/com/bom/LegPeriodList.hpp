#ifndef __LATUS_COM_BOM_LEGPERIODLIST_HPP
#define __LATUS_COM_BOM_LEGPERIODLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class LegPeriod;

    /** Define list of Leg-Period objects. */
    typedef std::map<std::string, LegPeriod*> LegPeriodList_T;
  }
}
#endif // __LATUS_COM_BOM_LEGPERIODLIST_HPP
