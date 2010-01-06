// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/NetworkDateStructure.hpp>
#include <stdair/bom/NetworkDate.hpp>
#include <stdair/bom/AirportDate.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  NetworkDate::NetworkDate (const BomKey_T& iKey,
                        BomStructure_T& ioNetworkDateStructure)
    : NetworkDateContent (iKey), _networkDateStructure (ioNetworkDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  NetworkDate::~NetworkDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void NetworkDate::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string NetworkDate::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string NetworkDate::describeKey() const {
    return _networkDateStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string NetworkDate::describeShortKey() const {
    return _networkDateStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  AirportDateList_T NetworkDate::getAirportDateList () const {
    return _networkDateStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  AirportDateMap_T NetworkDate::getAirportDateMap () const {
    return _networkDateStructure.getChildrenHolder();
  }

}

