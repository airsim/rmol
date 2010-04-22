#ifndef __STDAIR_BOM_DEMANDSTREAMKEY_HPP
#define __STDAIR_BOM_DEMANDSTREAMKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/bom/BomKey.hpp>

namespace stdair {

  /** Key of demand-stream. */
  struct DemandStreamKey_T : public BomKey_T {
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    DemandStreamKey_T (const AirportCode_T& iOrigin,
                       const AirportCode_T& iDestination,
                       const Date_T& iPreferredDepartureDate,
                       const CabinCode_T& iPreferredCabin);
    DemandStreamKey_T (const DemandStreamKey_T&);

    /** Destructor. */
    ~DemandStreamKey_T ();
    
  public:
    /** Default constructor */
    // TODO: that constructor should be private
    DemandStreamKey_T ();
    

    // /////////// Getters //////////
    /** Get the origin. */
    const AirportCode_T& getOrigin() const {
      return _origin;
    }

    /** Get the destination. */
    const AirportCode_T& getDestination() const {
      return _destination;
    }

    /** Get the preferred departure date. */
    const Date_T& getPreferredDepartureDate () const {
      return _preferredDepartureDate;
    }
    
    /** Get the preferred cabin. */
    const CabinCode_T& getPreferredCabin() const {
      return _preferredCabin;
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
       marketing classes for the same segment-stream. */
    const std::string toString() const;
    
  private:
    // Attributes
    /** Origin */
    AirportCode_T _origin;
    
    /** Origin */
    AirportCode_T _destination;
    
    /** Preferred departure date */
    Date_T _preferredDepartureDate;

    /** Preferred cabin. */
    CabinCode_T _preferredCabin;
  };

}
#endif // __STDAIR_BOM_DEMANDSTREAMKEY_HPP
