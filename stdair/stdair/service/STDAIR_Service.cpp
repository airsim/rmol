// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service () {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const STDAIR_Service& iService) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const stdair::BasLogParams& iLogParams) {
    // Set the log file
    logInit (iLogParams);

    // Initialise the (remaining of the) context
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::~STDAIR_Service () {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::logInit (const BasLogParams& iLogParams) {
    Logger::init (iLogParams);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::init () {
    // Create the static instance of the FacSupervisor object
    FacSupervisor::instance();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::finalise () {
    // std::cout << "In STDAIR_Service destructor, before cleaning" << std::endl;
    FacSupervisor::cleanAll();
    // std::cout << "In STDAIR_Service destructor, after cleaning" << std::endl;
  }

}
