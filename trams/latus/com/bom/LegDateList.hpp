#ifndef __LATUS_COM_BOM_LEGDATELIST_HPP
#define __LATUS_COM_BOM_LEGDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class LegDate;

    /** Define list of Leg-Date objects. */
    typedef std::map<std::string, LegDate*> LegDateList_T;
  }
}
#endif // __LATUS_COM_BOM_LEGDATELIST_HPP
