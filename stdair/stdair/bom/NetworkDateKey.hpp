#ifndef __STDAIR_BOM_NETWORKDATEKEY_HPP
#define __STDAIR_BOM_NETWORKDATEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/NetworkKey.hpp>

namespace stdair {
  /** Key of network-date. */
  struct NetworkDateKey_T : public BomKey_T {
    friend struct AirportDateKey_T;

  public:
    // /////////// Typedefs ////////////
    /** Definition allowing to retrieve the parent key type. */
    typedef NetworkKey_T ParentKey_T;
    
  private:
    // /////////// Default constructor //////////
    NetworkDateKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    NetworkDateKey_T (const Date_T& iReferenceDate);
    NetworkDateKey_T (const NetworkDateKey_T&);

    /** Destructor. */
    ~NetworkDateKey_T ();
    
    // /////////// Getters //////////
    /** Get the reference date. */
    const Date_T& getReferenceDate() const {
      return _referenceDate;
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
       marketing classes for the same segment-date. */
    const std::string toString() const;

    /** Display of the key. */
    const std::string describe() const;

    // /////////// Setters ///////////////
    /** Set the parent key. */
    void setParentKey (const ParentKey_T& iParentKey) {
      _parentKey = iParentKey;
    }

  private:
    // Attributes
    /** Network Key.*/
    ParentKey_T _parentKey;

    /** The reference date of the network-date.
        <br> A network-date is a set of flight-dates which are linked together
        by a set of O&D products. Hence, the "dates" of those flight-dates
        are not necessarily the same. That's why we have to choose a date
        as the "reference" one. */
    Date_T _referenceDate;
  };

}

#endif // __STDAIR_BOM_NETWORKDATEKEY_HPP
