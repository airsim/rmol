// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BR.hpp>
#include <stdair/bom/BRKey.hpp>
#include <stdair/bom/BRTypes.hpp>
#include <stdair/bom/IN.hpp>
#include <stdair/bom/INKey.hpp>
#include <stdair/bom/INTypes.hpp>
#include <stdair/bom/FD.hpp>
#include <stdair/bom/FDKey.hpp>
#include <stdair/bom/FDTypes.hpp>
#include <stdair/bom/ND.hpp>
#include <stdair/bom/NDKey.hpp>
#include <stdair/bom/NDTypes.hpp>
#include <stdair/factory/FacBomContent.hpp>


// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
   try {
     stdair::BRKey_T lBRKey;
     stdair::BR& lBR =
       stdair::FacBomContent::instance().testCreate<stdair::BR> (lBRKey);

     stdair::INKey_T lINKey ("BA");
     stdair::IN& lIN =
       stdair::FacBomContent::instance().testCreate<stdair::IN> (lINKey);
 
     
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
