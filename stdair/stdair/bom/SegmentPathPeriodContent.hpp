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

    /** Get the number of segments (part of the primary key). */
    const NbOfSegments_T getNbOfSegments() const {
      return _key.getNbOfSegments();
    }

    /** Get the boarding date offset list. */
    const DateOffsetList_T& getBoardingDateOffsetList () const {
      return _key.getBoardingDateOffsetList();
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

    /** Get the departure period. */
    const PeriodStruct_T& getDeparturePeriod () const {
      return _key.getPeriod();
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
  };

}
#endif // __STDAIR_BOM_SEGMENTPATHPERIODCONTENT_HPP

