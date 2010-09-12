// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// Local
#include <test/archi_intru/BomRoot.hpp>
#include <test/archi_intru/FlightDate.hpp>
#include <test/archi_intru/FacBom.hpp>
#include <test/archi_intru/FacRelationShipRoot.hpp>
#include <test/archi_intru/BomManager.hpp>
#include <test/archi_intru/TestBomUsage.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

// //////////////////////////////////////////////////////////////////////
TestBomUsage::TestBomUsage() : _bomRoot (NULL) {
  init();
}

// //////////////////////////////////////////////////////////////////////
TestBomUsage::~TestBomUsage() {
  clean();
}

// //////////////////////////////////////////////////////////////////////
void TestBomUsage::init() {
  _bomRoot = &stdair::FacBom<stdair::BomRoot>::instance().create ("BR");
}

// //////////////////////////////////////////////////////////////////////
void TestBomUsage::clean() {
}

// //////////////////////////////////////////////////////////////////////
bool TestBomUsage::testBomBuilding() {
  bool oTestSuccessfull = true;

  // 0. Sanity check
  assert (_bomRoot != NULL);

  // 1. FlightDate level
  // 1.1. BA177
  const std::string fdba117 ("BA117");
  stdair::FlightDate& lFDBA117 =
    stdair::FacBom<stdair::FlightDate>::instance().create (fdba117);

  stdair::FacRelationShipRoot<stdair::BomRoot,
                              stdair::FlightDate>::addToList (*_bomRoot,
                                                              lFDBA117);

  // 1.2. LH434
  const std::string fdlh434 ("LH434");
  stdair::FlightDate& lFDLH434 =
    stdair::FacBom<stdair::FlightDate>::instance().create (fdlh434);

  stdair::FacRelationShipRoot<stdair::BomRoot,
                              stdair::FlightDate>::addToList (*_bomRoot,
                                                              lFDLH434);

  // DEBUG
  std::cout << stdair::BomManager::display (*_bomRoot);
  
  return oTestSuccessfull;
}

// //////////////////////////////////////////////////////////////////////
bool TestBomUsage::testBomSearching() {
  bool oTestSuccessfull = true;

  stdair::FlightDate* lFlightDate_ptr =
    stdair::FacRelationShipRoot<stdair::BomRoot,
                                stdair::FlightDate>::find (*_bomRoot, "BA117");
  
  // DEBUG
  const std::string isFDNullStr = (lFlightDate_ptr == NULL)?"Yes":"No";
  std::cout << "Is FlightDate NULL? " << isFDNullStr << std::endl;
  
  return oTestSuccessfull;
}

// //////////////////////////////////////////////////////////////////////
bool TestBomUsage::test() {
  bool oTestSuccessfull = true;

  //
  TestBomUsage lTestBomUsage;
  
  // Test the building of the BOM tree
  oTestSuccessfull = lTestBomUsage.testBomBuilding();
  if (oTestSuccessfull == false) {
    return oTestSuccessfull;
  }

  // Test searching within the BOM tree
  oTestSuccessfull = lTestBomUsage.testBomSearching();
  if (oTestSuccessfull == false) {
    return oTestSuccessfull;
  }

  return oTestSuccessfull;
}
