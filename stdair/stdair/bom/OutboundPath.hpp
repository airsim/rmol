#ifndef __STDAIR_BOM_OUTBOUNDPATH_HPP
#define __STDAIR_BOM_OUTBOUNDPATH_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/AirportDate.hpp>
#include <stdair/bom/OutboundPathStructure.hpp>
#include <stdair/bom/OutboundPathContent.hpp>
#include <stdair/bom/AirportDateTypes.hpp>
#include <stdair/bom/OutboundPathTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct OutboundPathKey_T;

  /** Class representing the actual functional/business content for a
      outbound path. */
  class OutboundPath : public OutboundPathContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef AirportDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef OutboundPathStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef OutboundPathKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef OutboundPath ContentChild_T;

  public:
    // /////////// Getters /////////////
  
  public:
    // ///////// Setters //////////      

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
      return _outboundPathStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    OutboundPath ();
    OutboundPath (const OutboundPath&);
    OutboundPath (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~OutboundPath();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _outboundPathStructure;
  };

}
#endif // __STDAIR_BOM_OUTBOUNDPATH_HPP

