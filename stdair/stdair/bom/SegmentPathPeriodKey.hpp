#ifndef __STDAIR_BOM_SEGMENTPATHPERIODKEY_HPP
#define __STDAIR_BOM_SEGMENTPATHPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/DoWStruct.hpp>

namespace stdair {
  /** Key of SegmentPathPeriod. */
  struct SegmentPathPeriodKey_T : public BomKey_T {
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    SegmentPathPeriodKey_T ();
    SegmentPathPeriodKey_T (const DatePeriod_T&, const DoWStruct_T&,
                            const Duration_T&,  const Duration_T&,
                            const NbOfSegments_T&, const NbOfAirlines_T&);
    
    /** Destructor. */
    ~SegmentPathPeriodKey_T ();
    
    // /////////// Getters //////////
    /** Get the departure period. */
    const DatePeriod_T& getDeparturePeriod () const {
      return _dateRange;
    }

    /** Get the active days-of-week. */
    const DoWStruct_T& getDoW () const {
      return _dow;
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
    /** Departure peiod. */
    DatePeriod_T _dateRange;

    /** Active days-of-week. */
    DoWStruct_T _dow;
    
    /** The boarding time. */
    Duration_T _boardingTime;

    /** The elapsed time of the path. */
    Duration_T _elapsed;

    /** Number of segments included in the path. */
    NbOfSegments_T _nbOfSegments;

    /** Number of airlines included in the path. */
    NbOfAirlines_T _nbOfAirlines;
  };

}
#endif // __STDAIR_BOM_SEGMENTPATHPERIODKEY_HPP
