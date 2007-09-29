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

namespace LATUS {

  namespace COM {

    // Forward declarations
    class TravelSolution;

    /** Define a list of travel solutions. */
    typedef std::vector<TravelSolutionKey_T> TravelSolutionKeyList_T;

    /** Define a map linking travelSolution key with travel solutions.*/
    typedef std::multimap<std::string, TravelSolution*> TravelSolutionList_T;

  }
  
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTIONLIST_HPP
