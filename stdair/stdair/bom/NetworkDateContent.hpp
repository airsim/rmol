#ifndef __STDAIR_BOM_NETWORKDATECONTENT_HPP
#define __STDAIR_BOM_NETWORKDATECONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/NetworkDateKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for a network-date. */
  class NetworkDateContent : public BomContent {
  public :
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef NetworkDateKey_T BomKey_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    virtual const std::string describeKey() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    virtual const std::string describeShortKey() const = 0;

  public:
    // ////////// Getters ////////////
    /** Get the network-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

  protected:
    /** Default constructors. */
    NetworkDateContent (const BomKey_T&);
    NetworkDateContent (const NetworkDateContent&);

    /** Destructor. */
    virtual ~NetworkDateContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    BomKey_T _key;
      
  };

}
#endif // __STDAIR_BOM_NETWORKDATECONTENT_HPP

