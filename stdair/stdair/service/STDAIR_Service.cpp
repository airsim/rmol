// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Network.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/service/DBSessionManager.hpp>
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
  STDAIR_Service::STDAIR_Service (const BasLogParams& iLogParams)  
    : _bomRoot (FacBomContent::instance().create<BomRoot>()) {
    // The root of the BOM tree, on which all of the other BOM objects
    // will be attached, is being created with the STDAIR_Service constructor.

    // Initialise the AirlineFeatureSet object, and attach it to the BomRoot
    initAirlineFeatureSet ();
    // Initialise the DemandStreamList object, and attach it to the BomRoot
    initDemandStreamList ();
    
    // Set the log file
    logInit (iLogParams);

    // Initialise the (remaining of the) context
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  STDAIR_Service::STDAIR_Service (const BasLogParams& iLogParams,
                                  const BasDBParams& iDBParams)  
    : _bomRoot (FacBomContent::instance().create<BomRoot>()) {
    // The root of the BOM tree, on which all of the other BOM objects
    // will be attached, is being created with the STDAIR_Service constructor.

    // Initialise the AirlineFeatureSet object, and attach it to the BomRoot
    initAirlineFeatureSet ();
    // Initialise the DemandStreamList object, and attach it to the BomRoot
    initDemandStreamList ();

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
  void STDAIR_Service::initAirlineFeatureSet () {
    // Delegate to the dedicated command
    CmdBomManager::initAirlineFeatureSet (_bomRoot);
  }

  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::initDemandStreamList () {
    // Delegate to the dedicated command
    CmdBomManager::initDemandStreamList (_bomRoot);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  addAirlineFeature (const AirlineCode_T& iAirlineCode) const {
    // Delegate to the dedicated command
    CmdBomManager::addAirlineFeature (_bomRoot, iAirlineCode);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::finalise () {
    //std::cout << "In STDAIR_Service destructor, before cleaning" << std::endl;
    FacSupervisor::cleanAll();
    //std::cout << "In STDAIR_Service destructor, after cleaning" << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  Inventory& STDAIR_Service::
  getInventory (const AirlineCode_T& iAirlineCode) const {

    Inventory* lInventory_ptr = _bomRoot.getInventory (iAirlineCode);
    if (lInventory_ptr == NULL) {
      throw ObjectNotFoundException();
    }
    assert (lInventory_ptr != NULL);
    
    return *lInventory_ptr;
  }
  
  /**
     Note that the AirlineFeature is linked both to the Inventory
     and to the AirlineFeatureSet, which in turn is linked to the BomRoot.
     There is therefore a duplication of the structure links.
  */

  // //////////////////////////////////////////////////////////////////////
  Inventory& STDAIR_Service::
  createInventory (const AirlineCode_T& iAirlineCode) const {
    // Delegate to the dedicated command
    Inventory& oInventory = 
      CmdBomManager::getOrCreateInventory (_bomRoot, iAirlineCode);
    return oInventory;
  }

}
