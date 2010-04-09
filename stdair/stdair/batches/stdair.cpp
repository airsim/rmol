// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BR.hpp>
#include <stdair/bom/BRTypes.hpp>
#include <stdair/bom/IN.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/INTypes.hpp>
#include <stdair/bom/FD.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/FDTypes.hpp>
#include <stdair/bom/ND.hpp>
#include <stdair/bom/NetworkDateKey.hpp>
#include <stdair/bom/NDTypes.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/factory/FacBomContent.hpp>


// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
   try {
     stdair::BR& lBR =
       stdair::FacBomContent::instance().testCreate<stdair::BR> ();

     stdair::InventoryKey_T lINKey ("BA");
     stdair::IN& lIN =
       stdair::FacBomContent::instance().testCreate<stdair::IN> (lINKey);
     stdair::FacBomContent::testLink (lIN, lBR);

     stdair::FlightDateKey_T lFDKey (17, stdair::Date_T (2010, 02, 14));
     stdair::FD& lFD =
       stdair::FacBomContent::instance().testCreate<stdair::FD> (lFDKey);
     stdair::FacBomContent::testLink (lFD, lIN);

     stdair::NetworkDateKey_T lNDKey (stdair::Date_T (2010, 02, 14));
     stdair::ND& lND =
       stdair::FacBomContent::instance().testCreate<stdair::ND> (lNDKey);
     stdair::FacBomContent::testLink (lND, lIN);


     // Browse
     stdair::INList_T lINList = lBR.getINList();
     for (stdair::INList_T::iterator it = lINList.begin();
          it != lINList.end(); ++it) {
       const stdair::IN& lCurrentIN = *it;
       std::cout << "Current IN: " << lCurrentIN.toString() << std::endl;

       stdair::FDList_T lFDList = lIN.getFDList();
       for (stdair::FDList_T::iterator it = lFDList.begin();
            it != lFDList.end(); ++it) {
         const stdair::FD& lCurrentFD = *it;
         std::cout << "Current FD: " << lCurrentFD.toString() << std::endl;
       }
       stdair::NDList_T lNDList = lIN.getNDList();
       for (stdair::NDList_T::iterator it = lNDList.begin();
            it != lNDList.end(); ++it) {
         const stdair::ND& lCurrentND = *it;
         std::cout << "Current ND: " << lCurrentND.toString() << std::endl;
       }
       
     }
     
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
