// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
// Local
#include <test/archi_intru/BomRoot.hpp>
#include <test/archi_intru/FlightDate.hpp>
#include <test/archi_intru/FacRelationShipRoot.hpp>
#include <test/archi_intru/BomManager.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  std::string BomManager::display (const BomRoot& iBomRoot) {
    std::ostringstream oStr;

    // 0. BomRoot level
    oStr << "BR[" << iBomRoot << "]" << std::endl;

    // 1. FlightDate level
    
    return oStr.str();
  }

}
