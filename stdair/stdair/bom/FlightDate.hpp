#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomStructureList.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/LegDateTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  class BomStructure;
  class Inventory;
  struct SegmentDateList_T;
  struct SegmentDateMap_T;
  struct LegDateList_T;
  struct LegDateMap_T;
  
  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public BomContent {
    friend class FacBomContent;

  public:
    // Type definitions
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the BomContentRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef SegmentDate ContentChild_T;

        /** Definition allowing to retrieve the associated second
         BOM content child type. */
    typedef LegDate SecondContentChild_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;
    
  public:
    // /////////// Getters /////////////
    /** Get a SegmentDateList_T for iteration methods. */
    SegmentDateList_T getSegmentDateList () const;

    /** Get a SegmentDateMap_T for iteration methods. */
    SegmentDateMap_T getSegmentDateMap () const;

    /** Get a LegDateList_T for iteration methods. */
    LegDateList_T getLegDateList () const;

    /** Get a LegDateMap_T for iteration methods. */
    LegDateMap_T getLegDateMap () const;
  
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _flightDateStructure;
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (BomStructure_T&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _flightDateStructure;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

