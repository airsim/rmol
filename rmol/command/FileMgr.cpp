// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <ostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <cassert>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/VirtualClassStruct.hpp>
#include <stdair/factory/FacBom.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/command/FileMgr.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void FileMgr::readAndProcessInputFile (const std::string& iInputFileName,
                                         stdair::BomRoot& ioBomRoot) {

    // Retrieve the leg-cabin and the segment-cabin.
    const stdair::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (ioBomRoot);
    stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
    assert (itInv != lInventoryList.end());
    const stdair::Inventory* lInventory_ptr = *itInv;
    assert (lInventory_ptr != NULL);

    const stdair::FlightDateList_T& lFlightDateList =
      stdair::BomManager::getList<stdair::FlightDate> (*lInventory_ptr);
    stdair::FlightDateList_T::const_iterator itFD = lFlightDateList.begin();
    assert (itFD != lFlightDateList.end());
    const stdair::FlightDate* lFD_ptr = *itFD;
    assert (lFD_ptr != NULL);

    const stdair::SegmentDateList_T& lSegmentDateList =
      stdair::BomManager::getList<stdair::SegmentDate> (*lFD_ptr);
    stdair::SegmentDateList_T::const_iterator itSD = lSegmentDateList.begin();
    assert (itSD != lSegmentDateList.end());
    const stdair::SegmentDate* lSD_ptr = *itSD;
    assert (lSD_ptr != NULL);

    const stdair::SegmentCabinList_T& lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
    stdair::SegmentCabinList_T::const_iterator itSegmentCabin =
      lSegmentCabinList.begin();
    assert (itSegmentCabin != lSegmentCabinList.end());
    stdair::SegmentCabin* lSegmentCabin_ptr = *itSegmentCabin;
    assert (lSegmentCabin_ptr != NULL);
    stdair::SegmentCabin& lSegmentCabin = *lSegmentCabin_ptr;

    const stdair::LegDateList_T& lLegDateList =
      stdair::BomManager::getList<stdair::LegDate> (*lFD_ptr);
    stdair::LegDateList_T::const_iterator itLD = lLegDateList.begin();
    assert (itLD != lLegDateList.end());
    const stdair::LegDate* lLD_ptr = *itLD;
    assert (lLD_ptr != NULL);

    const stdair::LegCabinList_T& lLegCabinList =
      stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
    stdair::LegCabinList_T::const_iterator itLegCabin = lLegCabinList.begin();
    assert (itLegCabin != lLegCabinList.end());
    stdair::LegCabin* lLegCabin_ptr = *itLegCabin;
    assert (lLegCabin_ptr != NULL);
    stdair::LegCabin& lLegCabin = *lLegCabin_ptr;
    
    
    // Open the input file
    std::ifstream inputFile (iInputFileName.c_str());
    if (! inputFile) {
      STDAIR_LOG_ERROR ("Can not open input file \"" << iInputFileName << "\"");
      throw new stdair::FileNotFoundException("");
    }
    
    char buffer[80];
    double dval;
    short i = 1;
    bool hasAllPArams = true;
    stdair::Yield_T lYield;
    stdair::MeanValue_T lMean;
    stdair::StdDevValue_T lStdDev;
    stdair::BookingClassKey lBCKey (stdair::DEFAULT_CLASS_CODE);
    
    while (inputFile.getline (buffer, sizeof (buffer), ';')) {
      std::istringstream iStringStr (buffer);

      if (i == 1) {
        hasAllPArams = true;
      }
      
      if (iStringStr >> dval) {
        if (i == 1) {
          lYield = dval;
          // std::cout << "Yield[" << i << "] = '" << dval << "'" << std::endl;

        } else if (i == 2) {
          lMean = dval;
          // std::cout << "Mean[" << i << "] = '" << dval << "'" << std::endl;

        } else if (i == 3) {
          lStdDev = dval;
          //std::cout << "stdDev[" << i << "] = '" << dval << "'" << std::endl;
          i = 0;
        }
        i++;
          
      } else {
        hasAllPArams = false;
      }

      if (hasAllPArams && i == 1) {
        stdair::BookingClass& lBookingClass =
          stdair::FacBom<stdair::BookingClass>::instance().create (lBCKey);
        stdair::FacBomManager::instance().addToList (lSegmentCabin,
                                                     lBookingClass);
        lBookingClass.setYield (lYield);
        lBookingClass.setMean (lMean);
        lBookingClass.setStdDev (lStdDev);

        stdair::VirtualClassStruct lVirtualClass (lBookingClass);
        lVirtualClass.setYield (lYield);
        lVirtualClass.setMean (lMean);
        lVirtualClass.setStdDev (lStdDev);
        lLegCabin.addVirtualClass (lVirtualClass);
      }
    }
    
    if (!inputFile.eof()) {
      std::cerr << "Problem when reading input file \"" << iInputFileName
                << "\"" << std::endl;
    }
  }
  
}
