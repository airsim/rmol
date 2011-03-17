#ifndef __AIRRAC_AIRRAC_TYPES_HPP
#define __AIRRAC_AIRRAC_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <string>
// StdAir
#include <stdair/stdair_exceptions.hpp>

namespace AIRRAC {

  // ///////// Exceptions ///////////
  class AirportPairNotFoundException : public stdair::ObjectNotFoundException {
  public:
    /** Constructor. */
    AirportPairNotFoundException (const std::string& iWhat)
      : stdair::ObjectNotFoundException (iWhat) {}
  };

  class PosOrChannelNotFoundException : public stdair::ObjectNotFoundException {
  public:
    /** Constructor. */
    PosOrChannelNotFoundException (const std::string& iWhat)
      : stdair::ObjectNotFoundException (iWhat) {}
  };

  class FlightDateNotFoundException : public stdair::ObjectNotFoundException {
  public:
    /** Constructor. */
    FlightDateNotFoundException (const std::string& iWhat)
      : stdair::ObjectNotFoundException (iWhat) {}
  };

  class FlightTimeNotFoundException : public stdair::ObjectNotFoundException {
  public:
    /** Constructor. */
    FlightTimeNotFoundException (const std::string& iWhat)
      : stdair::ObjectNotFoundException (iWhat) {}
  };

  class FeaturesNotFoundException : public stdair::ObjectNotFoundException {
  public:
    /** Constructor. */
    FeaturesNotFoundException (const std::string& iWhat)
      : stdair::ObjectNotFoundException (iWhat) {}
  };
  
  class AirlineNotFoundException : public stdair::ObjectNotFoundException {
  public:
    /** Constructor. */
    AirlineNotFoundException (const std::string& iWhat)
      : stdair::ObjectNotFoundException (iWhat) {}
  };

  class YieldInputFileNotFoundException : public stdair::FileNotFoundException {
  public:
    /** Constructor. */
    YieldInputFileNotFoundException (const std::string& iWhat)
      : stdair::FileNotFoundException (iWhat) {}
  };

  class QuotingException : public stdair::RootException {
  };

  // //////// Type definitions specific to AirRAC /////////
  /** ID for the Fare Quote system. */
  typedef unsigned int YieldID_T;
}
#endif // __AIRRAC_AIRRAC_TYPES_HPP

