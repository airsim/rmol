#ifndef __LATUS_COM_BOM_CLASSPATHDISTRIBUTIONLIST_HPP
#define __LATUS_COM_BOM_CLASSPATHDISTRIBUTIONLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {
  
  namespace COM {

    /** List of distribution objects for each class-path/combination. */
    typedef std::map<std::string, double> ClassPathDistributionList_T;
  }

}
#endif // __LATUS_COM_BOM_CLASSPATHDISTRIBUTIONLIST_HPP
