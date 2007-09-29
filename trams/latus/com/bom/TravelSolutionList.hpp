#ifndef __LATUS_COM_BOM_TRAVELSOLUTIONLIST_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTIONLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>
// LATUS Common
#include <latus/com/bom/TravelSolutionKey.hpp>
#include <latus/com/bom/TravelSolution.hpp>


namespace LATUS {

  namespace COM {

    /** Define a list of travel solutions. */
    typedef std::vector<TravelSolutionKey_T> TravelSolutionKeyList_T;

    /** Define a map linking segmentdate key with classStruct
        for the crrent travel solution.*/
    typedef std::multimap<std::string, TravelSolution*> TravelSolutionList_T;
  }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTIONLIST_HPP
