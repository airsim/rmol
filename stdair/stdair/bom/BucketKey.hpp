#ifndef __STDAIR_BOM_BUCKETKEY_HPP
#define __STDAIR_BOM_BUCKETKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of booking-class. */
  struct BucketKey_T : public BomKey_T {
    
  public:
    // /////////// Construction ///////////
    /** Constructor. */
    BucketKey_T ();

    /** Destructor. */
    ~BucketKey_T ();
    
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
  };

}
#endif // __STDAIR_BOM_BUCKETKEY_HPP
