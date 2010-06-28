#ifndef __STDAIR_BOM_SEGMENTPATHPERIODCONTENT_HPP
#define __STDAIR_BOM_SEGMENTPATHPERIODCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/SegmentPathPeriodKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline outbound class. */
  class SegmentPathPeriodContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentPathPeriodKey_T Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the outbound path key. */
    const Key_T& getKey() const {
      return _key;
    }
    /** Get the airline code (from the whole outbound path). */
    const AirlineCode_T& getAirlineCode() const {
      return _airlineCode;
    }

    /** Get the flightPathCode (from the whole outbound path). */
    const FlightPathCode_T& getFlightPathCode() const {
      return _flightPathCode;
    }

    /** Get the current flightPathCode (from the whole outbound path). */
    FlightPathCode_T getCurrentFlightPathCode() {
      return _flightPathCode;
    }

    /** Get the number of segments (part of the primary key). */
    const NbOfSegments_T& getNbOfSegments() const {
      return _key.getNbOfSegments();
    }

    /** Get the elapsed time (part of the primary key). */
    const Duration_T& getElapsedTime() const {
      return _key.getElapsedTime();
    }

    /** Get the number of airlines (part of the primary key). */
    const NbOfAirlines_T& getNbOfAirlines() const {
      return _key.getNbOfAirlines();
    }

    /** Get the boarding time. */
    const Duration_T& getBoardingTime() const {
      return _key.getBoardingTime();
    }
   
  public:
    // /////////// Setters ////////////
    /** Set Airline Code. */
    void setAirlineCode (const AirlineCode_T& iAirlineCode) {
      _airlineCode = iAirlineCode;
    }
    
    /** Set the flight path Code. */
    void setFlightPathCode (const FlightPathCode_T& iFPCode) {
      _flightPathCode = iFPCode;
    }
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeShortKey() const { return _key.toString(); }

    
  protected:
    /** Default constructors. */
    SegmentPathPeriodContent (const Key_T&);
    SegmentPathPeriodContent (const SegmentPathPeriodContent&);
    /** Destructor. */
    ~SegmentPathPeriodContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
    
    /** AirlineCode for the whole outboundPath.*/
    AirlineCode_T _airlineCode;
    
    /** FlightPathCode (AirlineCode + flight numbers of all segments). */
    FlightPathCode_T _flightPathCode;
  };

}
#endif // __STDAIR_BOM_SEGMENTPATHPERIODCONTENT_HPP

