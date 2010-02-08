// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>

namespace stdair {
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::DemandCharacteristics ()
    : _origin ("") {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::~DemandCharacteristics () {
  }
  
  // /////////////////////////////////////////////////////
  DemandCharacteristics::
  DemandCharacteristics (const DemandCharacteristics& iDemandCharacteristics) {
    _origin = iDemandCharacteristics._origin;
    _preferredDepartureDate = iDemandCharacteristics._preferredDepartureDate;
    _arrivalPattern = iDemandCharacteristics._arrivalPattern;
  }
  
  // /////////////////////////////////////////////////////
  std::string DemandCharacteristics::display() const {
    std::ostringstream oStr;

    //
    oStr << "****************** Demand characteristics ******************";
    oStr << "Origin ........................... : "
             << _origin << std::endl;
    oStr << "Preferred departure date ......... : "
             << _preferredDepartureDate << std::endl;
    oStr << "Arrival pattern (days from departure, proportion):"
             << std::endl;

    //
    oStr << _arrivalPattern.displayCumulativeDistribution();
    
    return oStr.str();
  }
    
}

