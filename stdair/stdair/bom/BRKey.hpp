#ifndef __STDAIR_BOM_BRKEY_HPP
#define __STDAIR_BOM_BRKEY_HPP

#include <sstream>

namespace stdair {
  struct BRKey_T {

    // /////////// Display support methods /////////
    void toStream (std::ostream& ioOut) const {
      ioOut << "BRKey: " << toString() << std::endl;
    }

    void fromStream (std::istream& ioIn) {
    }

    const std::string toString() const {
      std::ostringstream oStr;
      oStr << " -- ROOT -- ";
      return oStr.str();
    }
    
    const std::string describe() const {
      return toString();
    }

  };
}

#endif // __STDAIR_BOM_BRKEY_HPP
