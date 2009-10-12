#ifndef __STDAIR_BOM_BOOKINGCLASSKEY_HPP
#define __STDAIR_BOM_BOOKINGCLASSKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {

  // Forward declarations
  template <typename BOM_CONTENT>
  class BookingClassStructure;

  /** Key of segment-cabin. */
  template <typename BOM_CONTENT>
  class BookingClassKey : public BomKey {
    friend class FacBomStructure;
    friend class FacBomContent;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BookingClassStructure<BOM_CONTENT> BomStructure_T;

  public:
    // /////////// Construction ///////////
    /** Constructor. */
    BookingClassKey (const ClassCode_T& iClassCode)
      : _classCode (iClassCode) {
    }

    /** Destructor. */
    ~BookingClassKey () { }
    
    // /////////// Getters //////////
    /** Get the cabin code. */
    const ClassCode_T& getClassCode () const {
      return _classCode;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << "BookingClassKey: " << toString() << std::endl;
    }

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-cabin. */
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _classCode;
      return oStr.str();
    }

    
  private:
    // Attributes
    /** Cabin code. */
    ClassCode_T _classCode;
  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSKEY_HPP
