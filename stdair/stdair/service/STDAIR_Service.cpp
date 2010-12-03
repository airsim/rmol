// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/stdair_types.hpp>
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/YieldStore.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/FacSupervisor.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/service/DBSessionManager.hpp>
#include <stdair/STDAIR_Service.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service ()
    : _bomRoot (FacBom<BomRoot>::instance().create()) {
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const STDAIR_Service& iService) 
    : _bomRoot (FacBom<BomRoot>::instance().create()) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const BasLogParams& iLogParams)  
    : _bomRoot (FacBom<BomRoot>::instance().create()) {
    // The root of the BOM tree, on which all of the other BOM objects
    // will be attached, is being created with the STDAIR_Service constructor.

    // Set the log file
    logInit (iLogParams);

    // Initialise the (remaining of the) context
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const BasLogParams& iLogParams,
                                  const BasDBParams& iDBParams) 
    : _bomRoot (FacBom<BomRoot>::instance().create()) { 
    // The root of the BOM tree, on which all of the other BOM objects
    // will be attached, is being created with the STDAIR_Service constructor.

    // Set the log file
    logInit (iLogParams);

    // Create a database session
    dbInit (iDBParams);

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
  void STDAIR_Service::dbInit (const BasDBParams& iDBParams) {
    DBSessionManager::init (iDBParams);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::init () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::finalise () {
    //std::cout << "In STDAIR_Service destructor, before cleaning" << std::endl;
    FacSupervisor::cleanAll();
    //std::cout << "In STDAIR_Service destructor, after cleaning" << std::endl;
  }

}
