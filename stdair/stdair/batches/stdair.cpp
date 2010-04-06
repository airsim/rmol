// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/BR.hpp>
#include <stdair/bom/BRKey.hpp>
#include <stdair/bom/BRTypes.hpp>
#include <stdair/bom/IN.hpp>
#include <stdair/bom/INKey.hpp>
#include <stdair/bom/INTypes.hpp>
#include <stdair/factory/FacBomContent.hpp>


// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
   try {

     stdair::BRKey_T lBRKey ();
     stdair::BR& lBR =
       stdair::FacBomContent::instance().testCreate<stdair::BR> (lBRKey);

     
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
