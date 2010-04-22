// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/DemandStreamKey.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  DemandStreamKey_T::DemandStreamKey_T () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  DemandStreamKey_T::DemandStreamKey_T (const AirportCode_T& iOrigin,
                                        const AirportCode_T& iDestination,
                                        const Date_T& iPreferredDepartureDate,
                                        const CabinCode_T& iPreferredCabin)
    : _origin (iOrigin), _destination (iDestination),
      _preferredDepartureDate (iPreferredDepartureDate),
      _preferredCabin (iPreferredCabin) {
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStreamKey_T::DemandStreamKey_T (const DemandStreamKey_T& iKey)
    : _origin (iKey._origin), _destination (iKey._destination),
      _preferredDepartureDate (iKey._preferredDepartureDate),
      _preferredCabin (iKey._preferredCabin) {
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStreamKey_T::~DemandStreamKey_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void DemandStreamKey_T::toStream (std::ostream& ioOut) const {
    ioOut << "DemandStreamKey: " << toString() << std::endl;
  }

  // ////////////////////////////////////////////////////////////////////
  void DemandStreamKey_T::fromStream (std::istream& ioIn) {
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string DemandStreamKey_T::toString() const {
    std::ostringstream oStr;
    oStr << _origin << "-" << _destination << " " << _preferredDepartureDate
         << " " << _preferredCabin;
    return oStr.str();
  }

}
