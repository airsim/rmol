#ifndef __LATUS_COM_BOM_OUTBOUNDPATHLIST_HPP
#define __LATUS_COM_BOM_OUTBOUNDPATHLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>
#include <list>
// LATUS Common
#include <latus/com/bom/OutboundPathKey.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class OutboundPath;

    /** Define lists of Outbound-Path objects. */
    typedef std::multimap<std::string, OutboundPath*> OutboundPathList_T;
    typedef std::list<OutboundPath*> OutboundPathLightList_T;

    /** Define a random-access list of list of Outbound-Path objects. */
    typedef std::vector<OutboundPathLightList_T> OutboundPathListList_T;
  }
}
#endif // __LATUS_COM_BOM_OUTBOUNDPATHLIST_HPP
