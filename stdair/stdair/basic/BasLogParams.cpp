// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/basic/BasLogParams.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  BasLogParams::BasLogParams (const LOG::EN_LogLevel iLogLevel,
                              std::ostream& ioLogOutputStream)
    : _logLevel (iLogLevel), _logStream (ioLogOutputStream) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasLogParams::~BasLogParams() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BasLogParams::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }

  // //////////////////////////////////////////////////////////////////////
  void BasLogParams::fromStream (std::istream&) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string BasLogParams::toShortString() const {
    std::ostringstream oStr;
    oStr << LOG::_logLevels[_logLevel];
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  std::string BasLogParams::toString() const {
    std::ostringstream oStr;
    oStr << LOG::_logLevels[_logLevel];
    return oStr.str();
  }
    
}
