// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
// Inventory: child of BomRoot, needed for creation of BomRoot
#include <stdair/bom/Inventory.hpp>
// Network: child of BomRoot, needed for creation of BomRoot
#include <stdair/bom/Network.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>
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
    // Initialise the set of required airline features
    stdair::AirlineFeatureSet& lAirlineFeatureSet =
      stdair::FacBomContent::instance().create<stdair::AirlineFeatureSet>();
    
    // Set the AirlineFeatureSet for the BomRoot.
    _bomRoot.setAirlineFeatureSet (&lAirlineFeatureSet);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void STDAIR_Service::
  addAirlineFeature (const AirlineCode_T& iAirlineCode) const {
    
    // Initialise an AirlineFeature object
    stdair::AirlineFeatureKey_T lAirlineFeatureKey (iAirlineCode);
    stdair::AirlineFeature& lAirlineFeature = stdair::FacBomContent::
      instance().create<stdair::AirlineFeature> (lAirlineFeatureKey);

    // Retrieve the AirlineFeatureSet object
    stdair::AirlineFeatureSet& lAirlineFeatureSet =
      _bomRoot.getAirlineFeatureSet();

    // Add the AirlineFeature object to its AirlineFeatureSet parent
    stdair::FacBomContent::
      linkWithParent<stdair::AirlineFeature> (lAirlineFeature,
                                              lAirlineFeatureSet);
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
  
  // //////////////////////////////////////////////////////////////////////
  Inventory& STDAIR_Service::
  createInventory (const AirlineCode_T& iAirlineCode) const {
    Inventory* lInventory_ptr = _bomRoot.getInventory (iAirlineCode);

    // If there is no Inventory object for that airline already, create one
    if (lInventory_ptr == NULL) {
      const stdair::InventoryKey_T lInventoryKey (iAirlineCode);

      // Instantiate an Inventory object with the given airline code
      lInventory_ptr =
        &stdair::FacBomContent::instance().
        create<stdair::Inventory> (lInventoryKey);
      assert (lInventory_ptr != NULL);
      
      // Link the created inventory with the bom root.
      stdair::FacBomContent::linkWithParent<stdair::Inventory> (*lInventory_ptr,
                                                                _bomRoot);

      // Set the AirlineFeature for the inventory.
      const stdair::AirlineFeatureSet& lAirlineFeatureSet =
        _bomRoot.getAirlineFeatureSet ();
      const stdair::AirlineFeature* lAirlineFeature_ptr =
        lAirlineFeatureSet.getAirlineFeature (iAirlineCode);

      // TODO: throw an exception?
      if (lAirlineFeature_ptr == NULL) {
        STDAIR_LOG_ERROR (lAirlineFeatureSet.display()
                          << "Needed airline code: " << iAirlineCode);
      }
      
      lInventory_ptr->setAirlineFeature (lAirlineFeature_ptr);
    }
    assert (lInventory_ptr != NULL);

    return *lInventory_ptr;
  }

}
