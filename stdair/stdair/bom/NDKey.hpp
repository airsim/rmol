#ifndef __STDAIR_BOM_NDKEY_HPP
#define __STDAIR_BOM_NDKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>


namespace stdair {
  struct NDKey_T : public BomKey_T {

    // /////////// Display support methods /////////
    void toStream (std::ostream& ioOut) const {
      ioOut << "NDKey: " << toString() << std::endl;
    }

    void fromStream (std::istream& ioIn) {
    }

    const std::string toString() const {
      std::ostringstream oStr;
      oStr << _networkNumber;
      return oStr.str();
    }
    
    const std::string describe() const {
      return toString();
    }

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    NDKey_T (const int& iNetworkNumber) : _networkNumber (iNetworkNumber) { }
    NDKey_T (const NDKey_T& iKey)
      : _networkNumber (iKey._networkNumber) { }
    /** Destructor. */
    ~NDKey_T () { }

  private:
    // Attributes
    /** Network number. */
    int _networkNumber;

  };
}

#endif // __STDAIR_BOM_NDKEY_HPP
