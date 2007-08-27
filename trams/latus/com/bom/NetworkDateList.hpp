#ifndef __LATUS_COM_BOM_NETWORKDATELIST_HPP
#define __LATUS_COM_BOM_NETWORKDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class NetworkDate;

    /** Define list of Network-Date objects. */
    typedef std::map<std::string, NetworkDate*> NetworkDateList_T;

  }
}
#endif // __LATUS_COM_BOM_NETWORKDATELIST_HPP
