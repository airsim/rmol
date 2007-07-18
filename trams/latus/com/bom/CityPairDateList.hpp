#ifndef __LATUS_COM_BOM_CITYPAIRDATELIST_HPP
#define __LATUS_COM_BOM_CITYPAIRDATELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class CityPairDate;

    /** List of CityPairDate objects (for each combination of departure date
        and class-path/combination). */
    typedef std::map<boost::gregorian::date, 
                     CityPairDate*> CityPairDateList_T;
  }

}
#endif // __LATUS_COM_BOM_CITYPAIRDATELIST_HPP
