#ifndef __RMOL_BOM_STATAGGREGATORSTRUCTLIST_HPP
#define __RMOL_BOM_STATAGGREGATORSTRUCTLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace RMOL {

    /** Forward declarations. */
    struct StatAggregatorStruct_T;

    /** Define list of statistic aggregators. */
    typedef std::map<std::string, StatAggregatorStruct_T> StatAggregatorStructList_T;
}
#endif // __RMOL_BOM_STATAGGREGATORSTRUCTLIST_HPP
