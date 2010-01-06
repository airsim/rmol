#ifndef __STDAIR_BOM_AIRPORTDATE_HPP
#define __STDAIR_BOM_AIRPORTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/AirportDateStructure.hpp>
#include <stdair/bom/AirportDateContent.hpp>
#include <stdair/bom/AirportDateTypes.hpp>
#include <stdair/bom/OutboundPathTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct AirportDateKey_T;
  struct OutboundPathKey_T;

  /** Class representing the actual functional/business content for a
      airport-date. */
  class AirportDate : public AirportDateContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef AirportDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirportDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef OutboundPath ContentChild_T;
    
       
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
    /** Get a OutboundPathList_T for iteration methods. */
    OutboundPathList_T getOutboundPathList () const;

    /** Get a OutboundPathMap_T for iteration methods. */
    OutboundPathMap_T getOutboundPathMap () const;


  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _airportDateStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    AirportDate ();
    AirportDate (const AirportDate&);
    AirportDate (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~AirportDate();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _airportDateStructure;

  };

}
#endif // __STDAIR_BOM_AIRPORTDATE_HPP

