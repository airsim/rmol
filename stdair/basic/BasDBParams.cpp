// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>
// StdAir
#include <stdair/basic/BasDBParams.hpp>

namespace stdair {  

  // //////////////////////////////////////////////////////////////////////
  BasDBParams::BasDBParams (const std::string& iDBUser,
                            const std::string& iDBPasswd,
                            const std::string& iDBHost,
                            const std::string& iDBPort,
                            const std::string& iDBName)
    : _user (iDBUser), _passwd (iDBPasswd), _host (iDBHost), _port (iDBPort),
      _dbname (iDBName) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  BasDBParams::~BasDBParams() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void BasDBParams::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }

  // //////////////////////////////////////////////////////////////////////
  void BasDBParams::fromStream (std::istream&) {
  }

  // //////////////////////////////////////////////////////////////////////
  std::string BasDBParams::toShortString() const {
    std::ostringstream oStr;
    oStr << _dbname << "." << _user << "@" << _host << ":" << _port;
    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  std::string BasDBParams::toString() const {
    std::ostringstream oStr;
    oStr << _dbname << "." << _user << "@" << _host << ":" << _port;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  bool BasDBParams::check () const {
    if (_user.empty() == true || _passwd.empty() == true
        || _host.empty() == true || _port.empty()
        || _dbname.empty() == true) {
      return false;
    }
    return true;
  }
  
}
