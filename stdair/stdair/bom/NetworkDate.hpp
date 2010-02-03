#ifndef __STDAIR_BOM_NETWORKDATE_HPP
#define __STDAIR_BOM_NETWORKDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/Network.hpp>
#include <stdair/bom/NetworkDateStructure.hpp>
#include <stdair/bom/NetworkDateTypes.hpp>
#include <stdair/bom/AirportDateTypes.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/NetworkDateContent.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct AirportDateKey_T;
  struct NetworkDateKey_T;
  
  /** Class representing the actual functional/business content for
      a network-date. */
  class NetworkDate : public NetworkDateContent {
    friend class FacBomContent;

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Network Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef NetworkDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef NetworkDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated  BOM content child
        type. */
    typedef AirportDate ContentChild_T;
    // /////////////////////////////////////////////////////////////////////////

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
    /** Get a AirportDateList_T for iteration methods. */
    AirportDateList_T getAirportDateList () const;

    /** Get a AirportDateMap_T for iteration methods. */
    AirportDateMap_T getAirportDateMap () const;
    
    /** Retrieve, if existing, the AirportDate corresponding to the
        given airport-date key.
        <br>If not existing, return the NULL pointer. */
    AirportDate* getAirportDate (const AirportDateKey_T&) const;

    /** Retrieve, if existing, the AirportDate corresponding to the
        given airport-code.
        <br>If not existing, return the NULL pointer. */
    AirportDate* getAirportDate (const AirportCode_T&) const;
    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _networkDateStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    NetworkDate ();
    NetworkDate (const NetworkDate&);
    NetworkDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~NetworkDate();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _networkDateStructure;

  };

}
#endif // __STDAIR_BOM_NETWORKDATE_HPP

