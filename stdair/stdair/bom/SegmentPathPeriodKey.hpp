#ifndef __STDAIR_BOM_SEGMENTPATHPERIODKEY_HPP
#define __STDAIR_BOM_SEGMENTPATHPERIODKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/PeriodStruct.hpp>
#include <stdair/bom/SegmentPathPeriodTypes.hpp>

namespace stdair {
  /** Key of SegmentPathPeriod. */
  struct SegmentPathPeriodKey_T : public BomKey_T {
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    SegmentPathPeriodKey_T ();
    SegmentPathPeriodKey_T (const PeriodStruct_T&,
                            const Duration_T&,  const Duration_T&,
                            const DateOffsetList_T&, const NbOfAirlines_T&);
    
    /** Destructor. */
    ~SegmentPathPeriodKey_T ();
    
    // /////////// Getters //////////
    /** Get the active days-of-week. */
    const PeriodStruct_T& getPeriod () const {
      return _period;
    }

    const DateOffsetList_T& getBoardingDateOffsetList () const {
      return _boardingDateOffsetList;
    }
    
    /** Get the number of segments. */
    const NbOfSegments_T getNbOfSegments() const {
      return _boardingDateOffsetList.size();
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

    // /////////// Setters //////////
    /** Set the active days-of-week. */
    void setPeriod (const PeriodStruct_T& iPeriod) {
      _period = iPeriod;
    }

    void setBoardingDateOffsetList (const DateOffsetList_T& iList) {
      _boardingDateOffsetList = iList;
    }
    
    /** Set the number of airlines. */
    void setNbOfAirlines (const NbOfAirlines_T& iNbOfAirlines) {
      _nbOfAirlines = iNbOfAirlines;
    }

    /** Set the elapsed time. */
    void setElapsedTime (const Duration_T& iElapsed) {
      _elapsed = iElapsed;
    }

    /** Set the boarding time. */
    void setBoardingTime (const Duration_T& iBoardingTime) {
      _boardingTime = iBoardingTime;
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

    // /////////// Business methods ////////////
    /** Check if the key is valid (i.e. the departure period is valid). */
    const bool isValid () const {
      return _period.isValid ();
    }
    
  private:
    // Attributes
    /** Departure peiod. */
    PeriodStruct_T _period;
    
    /** The boarding time. */
    Duration_T _boardingTime;

    /** The elapsed time of the path. */
    Duration_T _elapsed;

    /** The list of boarding date offsets of the segments compare to
        the first one. */
    DateOffsetList_T _boardingDateOffsetList;

    /** Number of airlines included in the path. */
    NbOfAirlines_T _nbOfAirlines;
  };

}
#endif // __STDAIR_BOM_SEGMENTPATHPERIODKEY_HPP
