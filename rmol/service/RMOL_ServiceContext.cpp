// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/STDAIR_Service.hpp>
// RMOL
#include <rmol/basic/BasConst_RMOL_Service.hpp>
#include <rmol/command/FileMgr.hpp>
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
  void RMOL_ServiceContext::
  readFromInputFile (const std::string& iInputFileName) {
    stdair::STDAIR_Service& lSTDAIR_Service = getSTDAIR_Service();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();
    FileMgr::readAndProcessInputFile (iInputFileName, lBomRoot);
  }

  // ////////////////////////////////////////////////////////////////////
  void RMOL_ServiceContext::reset() {
    if (_ownStdairService == true) {
      _stdairService.reset();
    }
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::LegCabin& RMOL_ServiceContext::getLegCabinSample() const {
    // Bom root
    stdair::STDAIR_Service& lSTDAIR_Service = getSTDAIR_Service ();
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot ();    
    
    // Inventory
    const stdair::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
    assert (itInv != lInventoryList.end());
    const stdair::Inventory* lInventory_ptr = *itInv;
    assert (lInventory_ptr != NULL);

    // Flight-date
    const stdair::FlightDateList_T& lFlightDateList =
      stdair::BomManager::getList<stdair::FlightDate> (*lInventory_ptr);
    stdair::FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
    assert (itFD != lFlightDateList.end());
    const stdair::FlightDate* lFD_ptr = *itFD;
    assert (lFD_ptr != NULL);

    // Leg-date
    const stdair::LegDateList_T& lLegDateList =
      stdair::BomManager::getList<stdair::LegDate> (*lFD_ptr);
    stdair::LegDateList_T::const_iterator itLD = lLegDateList.begin();
    assert (itLD != lLegDateList.end());
    const stdair::LegDate* lLD_ptr = *itLD;
    assert (lLD_ptr != NULL);

    // Leg-cabin
    const stdair::LegCabinList_T& lLegCabinList =
      stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
    stdair::LegCabinList_T::const_iterator itLegCabin = lLegCabinList.begin();
    assert (itLegCabin != lLegCabinList.end());
    stdair::LegCabin* lLegCabin_ptr = *itLegCabin;
    assert (lLegCabin_ptr != NULL);
    
    return *lLegCabin_ptr;
  }

}
