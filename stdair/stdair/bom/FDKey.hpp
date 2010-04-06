#ifndef __STDAIR_BOM_FDKEY_HPP
#define __STDAIR_BOM_FDKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>


namespace stdair {
  struct FDKey_T : public BomKey_T {

    // /////////// Display support methods /////////
    void toStream (std::ostream& ioOut) const {
      ioOut << "FDKey: " << toString() << std::endl;
    }

    void fromStream (std::istream& ioIn) {
    }

    const std::string toString() const {
      std::ostringstream oStr;
      oStr << _flightNumber;
      return oStr.str();
    }
    
    const std::string describe() const {
      return toString();
    }

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    FDKey_T (const int& iFlightNumber) : _flightNumber (iFlightNumber) { }
    FDKey_T (const FDKey_T& iKey)
      : _flightNumber (iKey._flightNumber) { }
    /** Destructor. */
    ~FDKey_T () { }

  private:
    // Attributes
    /** Flight number. */
    int _flightNumber;

  };
}

#endif // __STDAIR_BOM_FDKEY_HPP
