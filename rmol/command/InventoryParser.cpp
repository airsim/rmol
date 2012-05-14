// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <fstream>
#include <cassert>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_exceptions.hpp>
#include <stdair/basic/BasConst_DefaultObject.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomRetriever.hpp>
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
#include <rmol/command/InventoryParser.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool InventoryParser::
  parseInputFileAndBuildBom (const std::string& iInputFileName,
                             stdair::BomRoot& ioBomRoot) {
    bool hasReadBeenSuccessful = false;

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (iInputFileName);
    if (doesExistAndIsReadable == false) {
      std::ostringstream oMessage;
      oMessage << "The input file, '" << iInputFileName
               << "', can not be retrieved on the file-system";
      throw stdair::FileNotFoundException (oMessage.str());
    }

    // Retrieve the (sample) leg-cabin
    stdair::LegCabin& lLegCabin =
      stdair::BomRetriever::retrieveDummyLegCabin (ioBomRoot);

    // Retrieve the (sample) segment-cabin
    stdair::SegmentCabin& lSegmentCabin =
      stdair::BomRetriever::retrieveDummySegmentCabin (ioBomRoot);

    // Open the input file
    std::ifstream inputFile (iInputFileName.c_str());
    if (! inputFile) {
      STDAIR_LOG_ERROR ("Can not open input file '" << iInputFileName << "'");
      throw new stdair::FileNotFoundException ("Can not open input file '"
                                               + iInputFileName + "'");
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
        stdair::FacBomManager::addToList (lSegmentCabin, lBookingClass);
        lBookingClass.setYield (lYield);
        lBookingClass.setMean (lMean);
        lBookingClass.setStdDev (lStdDev);
        stdair::BookingClassList_T lBookingClassList;
        lBookingClassList.push_back(&lBookingClass);
        stdair::VirtualClassStruct lVirtualClass (lBookingClassList);
        lVirtualClass.setYield (lYield);
        lVirtualClass.setMean (lMean);
        lVirtualClass.setStdDev (lStdDev);
        lLegCabin.addVirtualClass (lVirtualClass);
      }
    }
    
    //
    if (!inputFile.eof()) {
      STDAIR_LOG_ERROR ("Problem when reading input file '" << iInputFileName
                        << "'");
      return hasReadBeenSuccessful;
    }

    //
    hasReadBeenSuccessful = true;
    return hasReadBeenSuccessful;
  }
  
}
