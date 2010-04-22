#ifndef __STDAIR_BOM_OUTBOUNDPATHKEY_HPP
#define __STDAIR_BOM_OUTBOUNDPATHKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of OutboundPath. */
  struct OutboundPathKey_T : public BomKey_T {
    
  public:
    // /////////// Construction ///////////
    /** Constructor. */
    OutboundPathKey_T (const AirportCode_T&, const Duration_T&,
                       const NbOfSegments_T&, const NbOfAirlines_T&,
                       const Duration_T&);
    
    /** Destructor. */
    ~OutboundPathKey_T ();
    
    // /////////// Getters //////////
    /** Get off airport. */
    const AirportCode_T& getOffPoint() const {
      return _destination;
    }
    
    /** Get the number of segments. */
    const NbOfSegments_T& getNbOfSegments() const {
      return _nbOfSegments;
    }
    
    /** Get the number of airlines. */
    const NbOfAirlines_T& getNbOfAirlines() const {
      return _nbOfAirlines;
    }

    /** Get the elapsed time. */
    const Duration_T& getElapsedTime() const {
      return _elapsed;
    }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime () const {
      return _boardingTime;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-cabin. */
    const std::string toString() const;
    
  private:
    // Attributes
    /** The off point. */
    AirportCode_T _destination;

    /** The elapsed time of the path. */
    Duration_T _elapsed;

    /** Number of segments included in the path. */
    NbOfSegments_T _nbOfSegments;

    /** Number of airlines included in the path. */
    NbOfAirlines_T _nbOfAirlines;

    /** The boarding time. */
    Duration_T _boardingTime;
  };

}
#endif // __STDAIR_BOM_OUTBOUNDPATHKEY_HPP
