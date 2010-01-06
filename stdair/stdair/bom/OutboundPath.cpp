// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/OutboundPathStructure.hpp>
#include <stdair/bom/OutboundPath.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OutboundPath::OutboundPath (const BomKey_T& iKey,
                              BomStructure_T& ioOutboundPathStructure)
    : OutboundPathContent (iKey),
      _outboundPathStructure (ioOutboundPathStructure) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  OutboundPath::~OutboundPath () {
  }

  // //////////////////////////////////////////////////////////////////////
  void OutboundPath::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void OutboundPath::fromStream (std::istream& ioIn) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string OutboundPath::toString() const {
    std::ostringstream oStr;

    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    // Then, browse the children
    // [...] (no child for now)
    
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string OutboundPath::describeKey() const {
    return _outboundPathStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string OutboundPath::describeShortKey() const {
    return _outboundPathStructure.describeShortKey();
  }
  
}

