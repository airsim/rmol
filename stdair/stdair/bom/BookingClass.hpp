#ifndef __STDAIR_BOM_BOOKINGCLASS_HPP
#define __STDAIR_BOM_BOOKINGCLASS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BookingClassStructure.hpp>
#include <stdair/bom/BookingClassContent.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  class SegmentCabin;
  struct BookingClassKey_T;
  struct BookingClassList_T;
  struct BookingClassMap_T;

  /** Class representing the actual functional/business content for a
      segment-cabin. */
  class BookingClass : public BookingClassContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef SegmentCabin Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BookingClassStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BookingClassKey_T BomKey_T;

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

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _bookingClassStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BookingClass ();
    BookingClass (const BookingClass&);
    BookingClass (BomStructure_T&);

    /** Destructor. */
    virtual ~BookingClass();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _bookingClassStructure;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASS_HPP

