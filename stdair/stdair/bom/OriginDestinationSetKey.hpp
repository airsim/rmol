#ifndef __STDAIR_BOM_ORIGINDESTINATIONSETKEY_HPP
#define __STDAIR_BOM_ORIGINDESTINATIONSETKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>

namespace stdair {
  /** Key of network. */
  struct OriginDestinationSetKey_T : public BomKey_T {

  private:
    // /////////// Default constructor //////////
    OriginDestinationSetKey_T ();

  public:
    // /////////// Construction ///////////
    /** Constructors. */
    OriginDestinationSetKey_T (const AirportCode_T& );
    OriginDestinationSetKey_T (const OriginDestinationSetKey_T&);
    /** Destructor. */
    ~OriginDestinationSetKey_T ();
    
    // /////////// Getters //////////
    /** Get the destination airport code. */
    const AirportCode_T& getOffPoint () const {
      return _destination;
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


  private:
    // Attributes
    /** OriginDestinationSet ID. */
    AirportCode_T _destination;
  };

}
#endif // __STDAIR_BOM_ORIGINDESTINATIONSETKEY_HPP
