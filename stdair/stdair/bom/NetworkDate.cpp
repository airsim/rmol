// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomSource.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  NetworkDate::NetworkDate (const Key_T& iKey,
                            Structure_T& ioNetworkDateStructure)
    : NetworkDateContent (iKey), _structure (ioNetworkDateStructure) {
    init ();
  }

  // ////////////////////////////////////////////////////////////////////
  NetworkDate::~NetworkDate () {
  }

  // ////////////////////////////////////////////////////////////////////
  void NetworkDate::init () {
    _structure.initChildrenHolder<AirportDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  void NetworkDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void NetworkDate::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  std::string NetworkDate::toString() const {
    std::ostringstream oStr;
    oStr << _key.toString();
    return oStr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string NetworkDate::describeKey() const {
    std::ostringstream oStr;
    oStr << _structure.describeParentKey() << ", " << describeShortKey();
    return oStr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  AirportDateList_T NetworkDate::getAirportDateList () const {
    return _structure.getChildrenHolder<AirportDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  AirportDateMap_T NetworkDate::getAirportDateMap () const {
    return _structure.getChildrenHolder<AirportDate>();
  }

  // ////////////////////////////////////////////////////////////////////
  AirportDate* NetworkDate::getAirportDate (const AirportCode_T& iCode) const {
    return _structure.getChildPtr<AirportDate> (iCode);
  }
  
}

