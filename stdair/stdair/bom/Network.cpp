// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/NetworkStructure.hpp>
#include <stdair/bom/Network.hpp>
#include <stdair/bom/NetworkDate.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  Network::Network (const BomKey_T& iKey,
                        BomStructure_T& ioNetworkStructure)
    : NetworkContent (iKey), _networkStructure (ioNetworkStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  Network::~Network () {
  }

  // //////////////////////////////////////////////////////////////////////
  void Network::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void Network::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Network::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string Network::describeKey() const {
    return _networkStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Network::describeShortKey() const {
    return _networkStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  NetworkDateList_T Network::getNetworkDateList () const {
    return _networkStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  NetworkDateMap_T Network::getNetworkDateMap () const {
    return _networkStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  NetworkDate* Network::
  getNetworkDate (const NetworkDateKey_T& iKey) const {
    return _networkStructure.getContentChild (iKey);
  }

}

