#ifndef __STDAIR_BOM_SEGMENTCABIN_HPP
#define __STDAIR_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/SegmentCabinContent.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  class SegmentDate;
  struct BookingClassList_T;
  struct BookingClassMap_T;

  /** Class representing the actual functional/business content for a
      segment-date. */
  class SegmentCabin : public SegmentCabinContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef SegmentDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef SegmentCabinStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef SegmentCabinKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef BookingClass ContentChild_T;
    
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
    /** Get a BookingClassList_T for iteration methods. */
    BookingClassList_T getBookingClassList () const;

    /** Get a BookingClassMap_T for iteration methods. */
    BookingClassMap_T getBookingClassMap () const;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _segmentCabinStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    SegmentCabin ();
    SegmentCabin (const SegmentCabin&);
    SegmentCabin (BomStructure_T&);

    /** Destructor. */
    virtual ~SegmentCabin();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _segmentCabinStructure;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABIN_HPP

