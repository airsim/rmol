#ifndef __LATUS_COM_BOM_DEPDATEDISTRIBUTIONLIST_HPP
#define __LATUS_COM_BOM_DEPDATEDISTRIBUTIONLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/bom/ClassPathDistributionList.hpp>

namespace LATUS {
  
  namespace COM {

    /** List of distribution objects for each class-path/combination. */
    typedef std::map<boost::gregorian::date, 
                     ClassPathDistributionList_T> DepDateDistributionList_T;
  }

}
#endif // __LATUS_COM_BOM_DEPDATEDISTRIBUTIONLIST_HPP
