// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp> // Child of BomRoot, needed for creation of BomRoot
#include <stdair/bom/Network.hpp> // Child of BomRoot, needed for creation of BomRoot
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service ()
    : _bomRoot (FacBomContent::instance().create<BomRoot>()) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const STDAIR_Service& iService) 
    : _bomRoot (FacBomContent::instance().create<BomRoot>()) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const stdair::BasLogParams& iLogParams)  
    : _bomRoot (FacBomContent::instance().create<BomRoot>()) {
    // The root of the BOM tree, on which all of the other BOM objects
    // will be attached, is being created with the STDAIR_Service constructor.

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
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::finalise () {
    // std::cout << "In STDAIR_Service destructor, before cleaning" << std::endl;
    FacSupervisor::cleanAll();
    // std::cout << "In STDAIR_Service destructor, after cleaning" << std::endl;
  }

}
