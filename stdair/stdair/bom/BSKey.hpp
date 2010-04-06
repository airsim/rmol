#ifndef __STDAIR_BOM_BSKEY_HPP
#define __STDAIR_BOM_BSKEY_HPP

namespace stdair {
  struct BSKey_T {

    // /////////// Display support methods /////////
    void toStream (std::ostream& ioOut) const {
      ioOut << "BSKey: " << toString() << std::endl;
    }

    void fromStream (std::istream& ioIn) {
    }

    const std::string toString() const {
      std::ostringstream oStr;
      oStr << " -- STOP -- ";
      return oStr.str();
    }
    
    const std::string describe() const {
      return toString();
    }

  };
}

#endif // __STDAIR_BOM_BSKEY_HPP
