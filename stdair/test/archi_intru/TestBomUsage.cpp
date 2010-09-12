// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// Boost
#include <boost/intrusive/list.hpp>
// Local
#include <test/archi_intru/BomRoot.hpp>
#include <test/archi_intru/FlightDate.hpp>
#include <test/archi_intru/FacBom.hpp>
#include <test/archi_intru/FacRelationShipRoot.hpp>
#include <test/archi_intru/TestBomUsage.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

// //////////////////////////////////////////////////////////////////////
TestBomUsage::~TestBomUsage() {
  clean();
}

// //////////////////////////////////////////////////////////////////////
void TestBomUsage::init() {
}

// //////////////////////////////////////////////////////////////////////
void TestBomUsage::clean() {
}

// //////////////////////////////////////////////////////////////////////
bool TestBomUsage::testBomBuilding() {
  bool oTestSuccessfull = true;

  const std::string br0 ("BR");
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create (br0);
  
  const std::string fdba117 ("BA117");
  stdair::FlightDate& lFDBA117 =
    stdair::FacBom<stdair::FlightDate>::instance().create (fdba117);

  stdair::FacRelationShipRoot<stdair::BomRoot,
                              stdair::FlightDate>::addToList(lBomRoot,lFDBA117);

  return oTestSuccessfull;
}

// //////////////////////////////////////////////////////////////////////
bool TestBomUsage::test() {
  bool oTestSuccessfull = true;


  return oTestSuccessfull;
}
