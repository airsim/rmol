// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
// Airrac
#include <airrac/basic/BasConst_AIRRAC_Service.hpp>
#include <airrac/service/AIRRAC_ServiceContext.hpp>

namespace AIRRAC {
  
  // //////////////////////////////////////////////////////////////////////
  AIRRAC_ServiceContext::
  AIRRAC_ServiceContext (const AIRRAC_ServiceContext&) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_ServiceContext::AIRRAC_ServiceContext () {
  }

  // //////////////////////////////////////////////////////////////////////
  AIRRAC_ServiceContext::~AIRRAC_ServiceContext() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string AIRRAC_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "AIRRAC_ServiceContext: " << std::endl;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string AIRRAC_ServiceContext::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

}
