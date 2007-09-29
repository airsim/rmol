#ifndef __LATUS_COM_BOM_OUTBOUNDPATH_HPP
#define __LATUS_COM_BOM_OUTBOUNDPATH_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/OutboundPathKey.hpp>
#include <latus/com/bom/SegmentDateList.hpp>
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {
    
    // Forward declarations
    class AirportDate;
    
    /** Class wrapping the Outbound-Path specific attributes and methods. */
    class OutboundPath : public BomAbstract {
      friend class FacOutboundPath;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      AirportDate* getParent() const {
        return getAirportDate();
      }

      /** Get the AirportDate (parent class). */
      AirportDate* getAirportDate() const {
        return _airportDate;
      }

      /** Get the primary key. */
      const OutboundPathKey_T& getPrimaryKey() const {
        return getOutboundPathKey();
      }

      /** Get the outbound-path key. */
      const OutboundPathKey_T& getOutboundPathKey() const {
        return _key;
      }

      /** Get the number of segments (part of the primary key). */
      const SegmentNumber_T& getSegmentNumber() const {
        return _key.segmentNumber;
      }

      /** Get the destination (part of the primary key). */
      const AirportCode_T& getDestination() const {
        return _key.destination;
      }

      /** Get the elapsed time (part of the primary key). */
      const Duration_T& getElapsedTime() const {
        return _key.elapsed;
      }

      /** Get the number of airlines (part of the primary key). */
      const AirlineNumber_T& getAirlineNumber() const {
        return _key.airlineNumber;
      }

      /** Get the off date (off date of the last segment). */
      const DateTime_T& getOffDate() const;

      /** Get the AirportDate corresponding to the destination of the
          outbound-path, i.e., the off point of the last segment-date
          of the (segment) list.
          <br>Return the NULL pointer if there is no such AirportDate object,
          e.g., when the destination is an end point (i.e., when no other
          SegmentDate is starting from the destination). */
      AirportDate* getDestinationAirportDate() const;

      /** State whether or not the given airline is flown by (at least) one of
          the segments of the internal list. */
      bool isAirlineFlown (const AirlineCode_T&) const;

      /** States whether or not the given OutboundPath may connect with the
          current one.
          <br>Basically, the board time of the given OutboundPath should be
          such as to allow the passenger connecting from the previous flight
          (current OutboundPath object) to the next one (given OutboundPath).
          <br>Note that this method relies on the eponym method of the
          SegmentDate class. */
      bool isConnectable (const OutboundPath&) const;

      /** Method computing the fare associated to the outbound path. */
      void fareQuote (); 
      
      // ///////// Setters //////////
      /** Set the AirportDate (parent class). */
      void setAirportDate (AirportDate* ioAirportDatePtr) {
        _airportDate = ioAirportDatePtr;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full OutboundPath context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      OutboundPath (const OutboundPathKey_T&);

      /** Default constructors. */
      OutboundPath ();
      OutboundPath (const OutboundPath&);

      /** Destructor. */
      virtual ~OutboundPath();


    private:
      /** Get the ordered list of (children) SegmentDate constant objects. */
      const SegmentDateLightList_T& getSegmentDateLightList () const {
        return _segmentDateLightList;
      }
      
      /** Get the first SegmentDate (constant) object of the list.
          <br>Return a NULL pointer if the list is empty. */
      const SegmentDate* getFirstSegmentDate () const;
      
      /** Get the last SegmentDate (constant) object of the list.
          <br>Return a NULL pointer if the list is empty. */
      const SegmentDate* getLastSegmentDate () const;
      
    public:
      // ////////// Business Methods /////////
      /** Calculate the elapsed time according to the segment routing.
          <br>Note that the given segment-date should come at the end of the
          outbound-path. An assertion will fail if the given board point and
          board date do not correspond to the off point and off date of the
          last segment-date of the outbound-path.
          <br>That method is a helper function allowing calculating the
          elapsed time of a to-be-built OutboundPath object. Indeed, the
          elapsed time can not be set after the object creation, as it is
          part of the primary key (needed at the time of object creation).
          <br>Actually, the elapsed time of the outbound path is the sum of the
          elapsed times of the routing segments, plus the stop-over times.
          The stop-over time is the difference between the board time of a
          routing segment, and the off time of the previous segment. That is,
          it is the time spent at the corresponding airport.
          <br>Of course, in case of mono-segment outbound pathes, there is no
          stop-over, and the elapsed time of the outbound-path is equal to the
          elapsed time of the single routing segment. */
      const Duration_T calculateElapsedTimeFromRouting (const SegmentDate&) const;
      

    private:
      // Parent
      /** Parent class: AirportDate. */
      AirportDate* _airportDate;
      
      // Primary Key
      /** Outbound-Path Key is composed of the destination airport, elapsed
          time, number of segments and number of airlines. */
      OutboundPathKey_T _key;

      // Children
      /** Child: Outbound-Path, i.e., an ordered list of SegmentDate constant
          objects. */
      SegmentDateLightList_T _segmentDateLightList;
    };

  }
}
#endif // __LATUS_COM_BOM_OUTBOUNDPATH_HPP
