// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/STDAIR_Service.hpp>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/service/RMOL_ServiceContext.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::RMOL_ServiceContext() : _ownStdairService (false) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::RMOL_ServiceContext (const RMOL_ServiceContext&) {
    assert (false);
  }
  
  // ////////////////////////////////////////////////////////////////////
  RMOL_ServiceContext::~RMOL_ServiceContext() {
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::STDAIR_Service& RMOL_ServiceContext::getSTDAIR_Service() const {
    assert (_stdairService != NULL);
    return *_stdairService;
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string RMOL_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "RMOL_ServiceContext -- Owns StdAir service: " << _ownStdairService;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string RMOL_ServiceContext::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string RMOL_ServiceContext::describe() const {
    return shortDisplay();
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::reset() {

    // The shared_ptr<>::reset() method drops the refcount by one.
    // If the count result is dropping to zero, the resource pointed to
    // by the shared_ptr<> will be freed.
    
    // Reset the stdair shared pointer
    _stdairService.reset();
  }

}
