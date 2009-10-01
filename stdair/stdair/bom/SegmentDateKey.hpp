#ifndef __STDAIR_BOM_SEGMENTDATEKEY_HPP
#define __STDAIR_BOM_SEGMENTDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {

  // Forward declarations
  template <typename BOM_CONTENT>
  class SegmentDate;

  /** Key of segment-date. */
  template <typename BOM_CONTENT>
  class SegmentDateKey : public BomKey {
    friend class FacBomStructure;
    friend class FacBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentDate<BOM_CONTENT> BomStructure_T;

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    SegmentDateKey (const AirportCode_T& iBoardPoint,
                    const AirportCode_T& iOffPoint)
      : _boardPoint (iBoardPoint), _offPoint (iOffPoint) {
    }

    /** Destructor. */
    ~SegmentDateKey () { }
    
    // /////////// Getters //////////
    /** Get the boarding point. */
    const AirportCode_T& getBoardPoint() const {
      return _boardPoint;
    }

    /** Get the arrival point. */
    const AirportCode_T& getOffPoint() const {
      return _offPoint;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << "SegmentDateKey: " << toString() << std::endl;
    }

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _boardPoint << "-" << _offPoint;
      return oStr.str();
    }

    
  private:
    // Attributes
    /** Boarding airport. */
    AirportCode_T _boardPoint;

    /** Arrival airport. */
    AirportCode_T _offPoint;
  };

}
#endif // __STDAIR_BOM_SEGMENTDATEKEY_HPP
