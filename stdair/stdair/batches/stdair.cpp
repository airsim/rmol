// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>

using namespace stdair;
// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
  try {
    // Output log File
    std::string lLogFilename ("stdair.log");
    
    // Set the log parameters
    std::ofstream logOutputFile;
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();

    const BasLogParams lLogParams (LOG::DEBUG, logOutputFile);
    STDAIR_Service stdairService (lLogParams);

    // DEBUG
    STDAIR_LOG_DEBUG ("Welcome to stdair");

    // Create the bom root.
    BomRoot& lBomRoot = FacBom<BomRoot>::instance().create();

    // Create the inventories.
    InventoryKey lBAKey ("BA");
    Inventory& lBAInv = FacBom<Inventory>::instance().create (lBAKey);
    FacBomManager::addToList (lBomRoot, lBAInv);
    InventoryKey lAFKey ("AF");
    Inventory& lAFInv = FacBom<Inventory>::instance().create (lAFKey);
    FacBomManager::addToList (lBomRoot, lAFInv);

    // Display the bom root.
    // const InventoryList_T& lInventoryList = RelationShip<BomRoot, Inventory>::
    //   instance().getChildrenList (lBomRoot);
    const InventoryList_T& lInventoryList =
      BomManager::getList<Inventory> (lBomRoot);
    for (InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const Inventory* lInv_ptr = *itInv; 
      STDAIR_LOG_DEBUG (lInv_ptr->describeKey());
    }
    
    // Close the Log outputFile
    logOutputFile.close();

  } CATCH
  
  return 0;	
}
